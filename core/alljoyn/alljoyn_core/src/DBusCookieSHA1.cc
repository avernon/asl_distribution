# Contributed by Qualcomm Connected Experiences, Inc.,
# with authorization from the AllSeen Alliance, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Pursuant to Section 1 of the License, the work of authorship constituting
# a Work and any Contribution incorporated in the Work shall mean only that
# Contributor's code submissions authored by that Contributor.  Any rights
# granted under the License are conditioned upon acceptance of these
# clarifications.
/**
 * @file
 *
 * This file implements the DBUS_COOKIE_SHA1 authentication mechanism
 */

/******************************************************************************
 *
 *
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Contributed by Qualcomm Connected Experiences, Inc.,
 *    with authorization from the AllSeen Alliance, Inc.
 *    
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *    
 *        http://www.apache.org/licenses/LICENSE-2.0
 *    
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *    
 *    Pursuant to Section 1 of the License, the work of authorship constituting
 *    a Work and any Contribution incorporated in the Work shall mean only that
 *    Contributor's code submissions authored by that Contributor.  Any rights
 *    granted under the License are conditioned upon acceptance of these
 *    clarifications.
 ******************************************************************************/

#include <qcc/platform.h>

#include <qcc/Crypto.h>
#include <qcc/String.h>
#include <qcc/StringUtil.h>
#include <qcc/Debug.h>
#include <qcc/Environ.h>
#include <qcc/FileStream.h>
#include <qcc/Mutex.h>
#include <qcc/Util.h>

#include "AuthMechDBusCookieSHA1.h"


#define QCC_MODULE "ALLJOYN_AUTH"

#define DEFAULT_COOKIE_CONTEXT "org_freedesktop_general"
#define KEY_RINGS              ".dbus-keyrings"

using namespace qcc;
using namespace std;

namespace ajn {

static FileSource* OpenCookieFile(const char* cookieContext, const qcc::String& userName)
{
    FileSource* cookieSrc = NULL;
    Environ* env = Environ::GetAppEnviron();
    qcc::String sep = ER_DIR_SEPARATOR;

    /*
     * Get HOME directory for requested user
     */
    qcc::String home = env->Find("HOME");
    if (!home.empty()) {
        qcc::String cookieFileName = home + sep + KEY_RINGS + sep + cookieContext;
        /*
         * Try to open the cookie file
         */
        cookieSrc = new FileSource(cookieFileName);
        if (!cookieSrc->IsValid()) {
            QCC_LogError(ER_FAIL, ("Unable to open cookie file %s", cookieFileName.c_str()));
            delete cookieSrc;
            cookieSrc = NULL;
        }
    }
    return cookieSrc;
}


/*
 * Try to read the requested cookie from the cookie file identified by cookieContext
 */
static QStatus ReadCookie(const char* cookieContext,
                          const qcc::String& userName,
                          int32_t cookieId,
                          qcc::String& cookie)
{
    FileSource* cookieSrc = OpenCookieFile(cookieContext, userName);
    Environ::const_iterator iter;
    QStatus status = ER_AUTH_FAIL;

    /*
     * AllJoynAuthentication failed if we couldn't open the cookie file
     */
    if (cookieSrc == NULL) {
        QCC_DbgPrintf(("ReadCookie could not open cookie context %s\n", cookieContext));
        return status;
    }
    /*
     * Lines in cookies file look like this: CookieID# Creation-Time Cookie
     */
    qcc::String id = I32ToString(cookieId);
    /*
     * Find line that starts with the requested the cookie id
     */
    qcc::String line;
    while (ER_OK == cookieSrc->GetLine(line)) {
        QCC_DbgPrintf(("ReadCookie: %s\n", line.c_str()));
        if (line.find(id + ' ') == 0) {
            line.erase(0, id.size() + 1);
            uint32_t creationTime = StringToU32(line, 10);
            if (creationTime != 0) {
                line.erase(0, line.find_first_of(' '));
                cookie = line.substr(1);
            }
            if (cookie.empty()) {
                QCC_LogError(status, ("Badly formed cookie file %s", line.c_str()));
            } else {
                status = ER_OK;
            }
            break;
        }
        line.clear();
    }
    delete cookieSrc;
    return status;
}


/*
 * Open the cookie file and choose a cookie.
 *
 * TODO - lock the cookie file and delete stale cookies.
 */
static QStatus ChooseCookie(const char* cookieContext,
                            const qcc::String& userName,
                            int32_t& cookieId,
                            qcc::String& cookie)
{
    QStatus status = ER_AUTH_FAIL;
    FileSource* cookieSrc = OpenCookieFile(cookieContext, userName);
    Environ::const_iterator iter;

    QCC_DbgPrintf(("Choose cookie %s %s\n", userName.c_str(), cookieContext));
    /*
     * AllJoynAuthentication failed if we couldn't open the cookie file
     */
    if (cookieSrc == NULL) {
        QCC_DbgPrintf(("ChooseCookie could not open cookie context %s\n", cookieContext));
        return status;
    }
    /*
     * Choose a cookie
     */
    qcc::String line;
    while (ER_OK == cookieSrc->GetLine(line)) {
        if (line.empty()) {
            break;
        }
        cookieId = StringToI32(line, 10, -1);
        if (cookieId == -1) {
            break;
        }
        line.erase(0, line.find_first_of(' '));
        if (line.empty()) {
            break;
        }
        uint32_t creationTime = StringToU32(line.erase(0, 1), 10);
        /*
         * TODO - discard stale cookies
         */
        if (creationTime != 0) {
            line.erase(0, line.find_first_of(' '));
            cookie = line.substr(1);
            if (!cookie.empty()) {
                status = ER_OK;
                break;
            }
        }
    }
    delete cookieSrc;
    /*
     * TODO - generate new cookies if the cookie file was empty or all the cookies were stale.
     */
    if (status == ER_OK) {
        QCC_DbgPrintf(("Chose cookie %d %s\n", cookieId, cookie.c_str()));
    } else {
        QCC_LogError(status, ("Badly formed cookie file %s", line.c_str()));
    }
    return status;
}


/*
 * Responses flow from clients to servers
 */
qcc::String AuthMechDBusCookieSHA1::InitialResponse(AuthResult& result)
{
    Environ* env = Environ::GetAppEnviron();
    userName = env->Find("USERNAME");
    if (userName.empty()) {
        result = ALLJOYN_AUTH_ERROR;
    } else {
        result = ALLJOYN_AUTH_CONTINUE;
    }
    return userName;
}


#define NONCE_LEN 32

/*
 * Compute SHA1 hash from the cookie , the server's nonce and the client's nonce.
 */
static qcc::String ComputeSHA1(const qcc::String& cookie,
                               const qcc::String& srvNonce,
                               const qcc::String& cliNonce)
{
    uint8_t digest[Crypto_SHA1::DIGEST_SIZE];
    Crypto_SHA1 sha1;
    qcc::String input = srvNonce + ':' + cliNonce + ':' + cookie;

    QCC_DbgPrintf(("ComputeSHA1 %s\n", input.c_str()));
    sha1.Init();
    sha1.Update((const uint8_t*)input.data(), input.length());
    sha1.GetDigest(digest);
    return BytesToHexString(digest, Crypto_SHA1::DIGEST_SIZE, true /*toLower*/);
}


/*
 * Responses flow from clients to servers
 */
qcc::String AuthMechDBusCookieSHA1::Response(const qcc::String& inChallenge,
                                             AuthResult& result)
{
    qcc::String response;
    qcc::String challenge(inChallenge);

    /*
     * Assume the worst
     */
    result = ALLJOYN_AUTH_ERROR;
    /*
     * Parse the challenge into a context, a cookie id, and a nonce.
     */
    size_t pos = challenge.find_first_of(' ');
    if (pos != qcc::String::npos) {
        qcc::String cookieContext = challenge.substr(0, pos);
        challenge = challenge.erase(0, pos + 1);
        int32_t cookieId = StringToU32(challenge, 10);
        pos = challenge.find_first_of(' ');
        if (pos != qcc::String::npos) {
            /*
             * Use the cookie id to find the cookie
             */
            QStatus status = ReadCookie(cookieContext.c_str(), userName, cookieId, cookie);
            if (status == ER_OK) {
                qcc::String& srvNonce = challenge.erase(0, pos + 1);
                qcc::String cliNonce = RandHexString(NONCE_LEN, true /*toLower*/);
                response = cliNonce + ' ' + ComputeSHA1(cookie, srvNonce, cliNonce);
                /*
                 * The client's part is done
                 */
                result = ALLJOYN_AUTH_OK;
            } else {
                response = "No such cookie";
            }
        } else {
            response = "Invalid challenge string";
        }
    }
    QCC_DbgPrintf(("Response: %s", response.c_str()));
    return response;
}


qcc::String AuthMechDBusCookieSHA1::Challenge(const qcc::String& inResponse,
                                              AuthResult& result)
{
    QStatus status = ER_OK;
    qcc::String challenge;
    qcc::String response(inResponse);

    /*
     * Assume the worst
     */
    result = ALLJOYN_AUTH_ERROR;

    if (cookie.empty()) {
        if (response.empty()) {
            challenge = "User name missing";
            QCC_DbgPrintf(("User name missing in initial response"));
            return challenge;
        }
        int32_t cookieId = -1;
        /*
         * Open the requested user's cookie jar and select a cookie to use for this challenge
         */
        userName = response;
        status = ChooseCookie(DEFAULT_COOKIE_CONTEXT, userName, cookieId, cookie);
        if (status == ER_OK) {
            nonce = RandHexString(NONCE_LEN, true /*toLower*/);
            challenge = DEFAULT_COOKIE_CONTEXT;
            challenge += ' ' + I32ToString(cookieId);
            challenge += ' ' + nonce;
            result = ALLJOYN_AUTH_CONTINUE;
        }
    } else {
        size_t pos = response.find_first_of(' ');
        if (pos != qcc::String::npos) {
            qcc::String cliNonce = response.substr(0, pos);
            response = response.erase(0, pos + 1);
            /*
             * Remaining response is the SHA1 hash. Compute our version and compare.
             */
            if (ComputeSHA1(cookie, nonce, cliNonce) == response) {
                result = ALLJOYN_AUTH_OK;
            }
        } else {
            challenge = "Invalid response string";
        }
        cookie.clear();
    }
    QCC_DbgPrintf(("Challenge: %s", challenge.c_str()));
    return challenge;
}

}

