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

#ifndef OPTPARSER_H_
#define OPTPARSER_H_

#include <alljoyn/about/AboutServiceApi.h>

/**
 * Class to parse arguments
 */
class OptParser {
  public:
    enum ParseResultCode {
        PR_OK, PR_EXIT_NO_ERROR, PR_INVALID_OPTION, PR_MISSING_OPTION, PR_INVALID_APPID
    };

    OptParser(int argc, char** argv);

    ParseResultCode ParseResult();

    qcc::String const& GetFactoryConfigFile() const;

    qcc::String const& GetConfigFile() const;

    qcc::String const& GetAppId() const;

    qcc::String const& GetAppName() const;

    qcc::String const& GetDeviceId() const;

    qcc::String const& GetDeviceName() const;

    qcc::String const& GetDefaultLanguage() const;

    qcc::String const& GetScanFile() const;

    qcc::String const& GetStateFile() const;

    qcc::String const& GetErrorFile() const;

    qcc::String const& GetConfigureCmd() const;

    qcc::String const& GetConnectCmd() const;

    qcc::String const& GetOffboardCmd() const;

    int GetConcurrency() const;

    int GetPort() const;

    bool ParseExternalXML();

  private:
    int argc;
    char** argv;

    bool IsAllHex(const char* data);

    void PrintUsage();

    qcc::String factoryConfigFile;
    qcc::String configFile;
    qcc::String appGUID;
    qcc::String appName;
    qcc::String defaultLanguage;
    qcc::String deviceId;
    qcc::String deviceName;
    qcc::String scanFile;
    qcc::String stateFile;
    qcc::String errorFile;
    qcc::String configureCmd;
    qcc::String connectCmd;
    qcc::String offboardCmd;
    int port;
    int concurrency;
};

#endif /* OPTPARSER_H_ */
