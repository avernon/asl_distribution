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
#include <iostream>
#include <alljoyn/services_common/GuidUtil.h>
#include <alljoyn/AboutData.h>

static const char versionPreamble[] = "OnboardingService version: 1\n"
                                      "Copyright AllSeen Alliance.\n";

using namespace ajn;
using namespace services;

OptParser::OptParser(int argc, char** argv) :
    argc(argc), argv(argv) {
    GuidUtil::GetInstance()->GetDeviceIdString(&deviceId);
    GuidUtil::GetInstance()->GenerateGUID(&appGUID);
    factoryConfigFile.assign("FactoryOnboardingService.conf");
    configFile.assign("OnboardingService.conf");
}

qcc::String const& OptParser::GetAppId() const {
    return appGUID;
}

qcc::String const& OptParser::GetDeviceId() const {
    return deviceId;
}

qcc::String const& OptParser::GetFactoryConfigFile() const {
    return factoryConfigFile;
}

qcc::String const& OptParser::GetConfigFile() const {
    return configFile;
}

void OptParser::PrintUsage() {
    qcc::String cmd = argv[0];
    cmd = cmd.substr(cmd.find_last_of('/') + 1);

    std::cerr << cmd.c_str() << " [--factory-config-file=FILE | --config-file=FILE |  --appId=APPID"
    "]\n"

    "    --factory-config-file=FILE\n"
    "        Configuration file with factory settings.\n\n"
    "    --config-file=FILE\n"
    "        Active configuration file that persists user's updates\n\n"
    "    --appId=\n"
    "        Use the specified it is HexString of 16 bytes (32 chars) \n\n"
    "    --version\n"
    "        Print the version and copyright string, and exit." << std::endl;
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
        } else if (arg.compare(0, sizeof("--appId") - 1, "--appId") == 0) {
            appGUID = arg.substr(sizeof("--appId"));
            if ((appGUID.length() != 32) || (!IsAllHex(appGUID.c_str()))) {
                result = PR_INVALID_APPID;
                std::cerr << "Invalid appId: \"" << argv[indx] << "\"" << std::endl;
                break;
            }
        } else if (arg.compare(0, sizeof("--factory-config-file") - 1, "--factory-config-file") == 0) {
            factoryConfigFile = arg.substr(sizeof("--factory-config-file"));
        } else if (arg.compare(0, sizeof("--config-file") - 1, "--config-file") == 0) {
            configFile = arg.substr(sizeof("--config-file"));
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
