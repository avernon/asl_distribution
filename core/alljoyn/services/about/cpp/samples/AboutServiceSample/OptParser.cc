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

#include "OptParser.h"
#include <stdio.h>
#include <ctype.h>
#include <iostream>

static const char versionPreamble[] = "AboutService version: 1\n"
                                      "Copyright AllSeen Alliance.\n";

using namespace ajn;

OptParser::OptParser(int argc, char** argv) :
    argc(argc), argv(argv) {
    port = 900;
    appGUID.assign("000102030405060708090A0B0C0D0E0C");
    deviceId.assign("1231232145667745675477");
    defaultLanguage.assign("en");
}

qcc::String OptParser::GetAppId() const {
    return appGUID;
}

qcc::String OptParser::GetDeviceId() const {
    return deviceId;
}

qcc::String OptParser::GetDefaultLanguage() const {
    return defaultLanguage;
}

int OptParser::GetPort() const {
    return port;
}

void OptParser::PrintUsage() {
    qcc::String cmd = argv[0];
    cmd = cmd.substr(cmd.find_last_of('/') + 1);

    std::cerr << cmd.c_str()
              << " [--port=PORT  | --language=LANG |  --deviceId=DEVICEID | --appId=APPID"
              << "]\n"
              << "    --port=\n"
              << "        used to bind the service.\n\n"
              << "    --deviceId\n"
              << "        Use the specified DeviceID.\n\n"
              << "    --appId=\n"
              << "        Use the specified it is HexString of 16 bytes (32 chars) \n\n"
              << "    --language=\n"
              << "       default language for PropertyStore\n\n"
              << "    --version\n"
              << "        Print the version and copyright string, and exit." << std::endl;
}

bool OptParser::IsAllHex(const char* data) {

    for (size_t index = 0; index < strlen(data); ++index) {
        if (!isxdigit(data[index])) {
            return false;
        }
    }
    return true;
}

OptParser::ParseResultCode OptParser::ParseResult() {
    ParseResultCode result = PR_OK;

    if (argc == 1) {
        return result;
    }

    int indx;
    for (indx = 1; indx < argc; indx++) {
        qcc::String arg(argv[indx]);
        if (arg.compare("--version") == 0) {
            std::cout << versionPreamble << std::endl;
            result = PR_EXIT_NO_ERROR;
            break;
        } else if (arg.compare(0, sizeof("--port") - 1, "--port") == 0) {
            port = atoi(arg.substr(sizeof("--port")).c_str());
        } else if (arg.compare(0, sizeof("--deviceId") - 1, "--deviceId") == 0) {
            deviceId = arg.substr(sizeof("--deviceId"));
        } else if (arg.compare(0, sizeof("--appId") - 1, "--appId") == 0) {
            appGUID = arg.substr(sizeof("--appId"));
            if ((appGUID.length() != 32) || (!IsAllHex(appGUID.c_str()))) {
                result = PR_INVALID_APPID;
                std::cerr << "Invalid appId: \"" << argv[indx] << "\"" << std::endl;
                break;
            }
        } else if (arg.compare(0, sizeof("--language") - 1, "--language") == 0) {
            defaultLanguage = arg.substr(sizeof("--language"));
        } else if ((arg.compare("--help") == 0) || (arg.compare("-h") == 0)) {
            PrintUsage();
            result = PR_EXIT_NO_ERROR;
            break;
        } else {
            result = PR_INVALID_OPTION;
            std::cerr << "Invalid option: \"" << argv[indx] << "\"" << std::endl;
            break;
        }
    }
    return result;
}
