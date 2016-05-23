/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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
#include <IniParser.h>
#include <GuidUtil.h>
#include <alljoyn/about/AboutPropertyStoreImpl.h>

static const char versionPreamble[] = "ConfigService version: 1\n"
                                      "Copyright (c) 2009-2013 AllSeen Alliance.\n";

using namespace ajn;
using namespace services;

OptParser::OptParser(int argc, char** argv) :
    argc(argc), argv(argv) {
    port = 900;
    GuidUtil::GetInstance()->GetDeviceIdString(&deviceId);
    GuidUtil::GetInstance()->GenerateGUID(&appGUID);
    deviceName.assign("MyDeviceName");
    defaultLanguage.assign("en");
    factoryConfigFile.assign("FactoryConfigService.conf");
    configFile.assign("ConfigService.conf");
    appName.assign("ConfigServiceApp");
}

qcc::String OptParser::GetAppId() const {
    return appGUID;
}

qcc::String OptParser::GetAppName() const {
    return appName;
}

qcc::String OptParser::GetFactoryConfigFile() const {
    return factoryConfigFile;
}

qcc::String OptParser::GetConfigFile() const {
    return configFile;
}

qcc::String OptParser::GetDeviceId() const {
    return deviceId;
}

qcc::String OptParser::GetDeviceName() const {
    return deviceName;
}

qcc::String OptParser::GetDefaultLanguage() const {
    return defaultLanguage;
}

int OptParser::GetPort() const {
    return port;
}


bool OptParser::ParseExternalXML() {
    std::map<std::string, std::string> data;
    if (!IniParser::ParseFile(configFile.c_str(), data)) {
        std::cerr << "Could not parse configFile" << std::endl;
        return false;
    }

    std::map<std::string, std::string>::iterator iter;

    iter = data.find(AboutPropertyStoreImpl::getPropertyStoreName(DEVICE_ID).c_str());
    if (iter != data.end()) {
        deviceId = iter->second.c_str();
    }

    iter = data.find(AboutPropertyStoreImpl::getPropertyStoreName(DEVICE_NAME).c_str());
    if (iter != data.end()) {
        deviceName = iter->second.c_str();
    }

    iter = data.find(AboutPropertyStoreImpl::getPropertyStoreName(APP_ID).c_str());
    if (iter != data.end()) {
        appGUID = iter->second.c_str();
    }

    iter = data.find(AboutPropertyStoreImpl::getPropertyStoreName(APP_NAME).c_str());
    if (iter != data.end()) {
        appName = iter->second.c_str();
    }

    iter = data.find(AboutPropertyStoreImpl::getPropertyStoreName(DEFAULT_LANG).c_str());
    if (iter != data.end()) {
        defaultLanguage = iter->second.c_str();
    }

    return true;
}

void OptParser::PrintUsage() {
    qcc::String cmd = argv[0];
    cmd = cmd.substr(cmd.find_last_of('/') + 1);

    std::cerr << cmd.c_str() << " [--port=PORT | --factory-config-file=FILE | --config-file=FILE | --language=LANG |  --deviceId=DEVICEID | --appId=APPID | --deviceName=DEVICENAME"
    "]\n"

    "    --port=\n"
    "        used to bind the service.\n\n"
    "    --factory-config-file=FILE\n"
    "        Configuration file with factory settings.\n\n"
    "    --config-file=FILE\n"
    "        Active configuration file that persists user's updates\n\n"
    "    --deviceId\n"
    "        Use the specified DeviceID.\n\n"
    "    --deviceName\n"
    "        Use the specified DeviceName.\n\n"
    "    --appId=\n"
    "        Use the specified it is HexString of 16 bytes (32 chars) \n\n"
    "    --language=\n"
    "       default language for PropertyStore\n\n"
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
        } else if (arg.compare(0, sizeof("--port") - 1, "--port") == 0) {
            port = atoi(arg.substr(sizeof("--port")).c_str());
        } else if (arg.compare(0, sizeof("--deviceId") - 1, "--deviceId") == 0) {
            deviceId = arg.substr(sizeof("--deviceId"));
        } else if (arg.compare(0, sizeof("--deviceName") - 1, "--deviceName") == 0) {
            deviceName = arg.substr(sizeof("--deviceName"));
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
