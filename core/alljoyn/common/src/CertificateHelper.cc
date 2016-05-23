/**
 * @file CertificateHelper.cc
 *
 * Helper class for X.509 Certificates
 */
/******************************************************************************
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
#include <qcc/CertificateHelper.h>
#include <qcc/String.h>
#include <qcc/StringUtil.h>
#include <qcc/Util.h>

#include <Status.h>

using namespace std;
using namespace qcc;

#define QCC_MODULE "CRYPTO"

namespace qcc {

static QStatus CountNumOfChunksFromEncoded(const String& encoded, const char* beginToken, const char* endToken, size_t* count)
{

    size_t pos;

    *count = 0;
    qcc::String remainder = encoded;
    while (true) {
        pos = remainder.find(beginToken);
        if (pos == qcc::String::npos) {
            /* no more */
            return ER_OK;
        }
        remainder = remainder.substr(pos + strlen(beginToken));
        pos = remainder.find(endToken);
        if (pos == qcc::String::npos) {
            return ER_OK;
        }
        *count += 1;
        remainder = remainder.substr(pos + strlen(endToken));
    }
    // Unreachable
}

QStatus CertificateHelper::GetCertCount(const String& encoded, size_t* count)
{
    *count = 0;
    return CountNumOfChunksFromEncoded(encoded,
                                       "-----BEGIN CERTIFICATE-----", "-----END CERTIFICATE-----", count);
}

}
