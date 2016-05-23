////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2014, AllSeen Alliance. All rights reserved.
//
//    Contributed by Qualcomm Connected Experiences, Inc.,
//    with authorization from the AllSeen Alliance, Inc.
//    
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//    
//        http://www.apache.org/licenses/LICENSE-2.0
//    
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//    
//    Pursuant to Section 1 of the License, the work of authorship constituting
//    a Work and any Contribution incorporated in the Work shall mean only that
//    Contributor's code submissions authored by that Contributor.  Any rights
//    granted under the License are conditioned upon acceptance of these
//    clarifications.
////////////////////////////////////////////////////////////////////////////////

#import "AJGWCEnums.h"
@interface AJGWCEnums ()
@end

@implementation AJGWCEnums

+ (NSString*)AJGWCConnectionStatusToString:(AJGWCConnectionStatus) connectionStatus
{
    NSString* connectionStatusStr;

    switch (connectionStatus) {
        case GW_CS_NOT_INITIALIZED:
            connectionStatusStr = @"Not initialized";
            break;

        case GW_CS_IN_PROGRESS:
            connectionStatusStr = @"In progress";
            break;

        case GW_CS_CONNECTED:
            connectionStatusStr = @"Connected";
            break;

        case GW_CS_NOT_CONNECTED:
            connectionStatusStr = @"Not connected";
            break;

        case GW_CS_ERROR:
            connectionStatusStr = @"Error";
            break;

        default:
            break;
    }

    return connectionStatusStr;
}

+ (NSString*)AJGWCInstallStatusToString:(AJGWCInstallStatus) installStatus
{
    NSString* installStatusStr;

    switch (installStatus) {
        case GW_IS_INSTALLED:
            installStatusStr = @"Installed";
            break;

        case GW_IS_INSTALL_IN_PROGRESS:
            installStatusStr = @"Install in progress";
            break;

        case GW_IS_UPGRADE_IN_PROGRESS:
            installStatusStr = @"Upgrade in progress";

            break;

        case GW_IS_UNINSTALL_IN_PROGRESS:
            installStatusStr = @"Uninstall in progress";
            break;

        case GW_IS_INSTALL_FAILED:
            installStatusStr = @"Installation failed";
            break;

        default:
            break;
    }

    return installStatusStr;
}

+ (NSString*)AJGWCOperationalStatusToString:(AJGWCOperationalStatus) operationalStatus
{
    NSString* operationalStatusStr;

    switch (operationalStatus) {
        case GW_OS_RUNNING:
            operationalStatusStr = @"Running";
            break;

        case GW_OS_STOPPED:
            operationalStatusStr = @"Stopped";
            break;
        default:
            break;
    }

    return operationalStatusStr;
}

+ (NSString*)AJGWCRestartStatusToString:(AJGWCRestartStatus) restartStatus
{
    NSString* restartStatusStr;

    switch (restartStatus) {
        case GW_RESTART_APP_RC_SUCCESS:
            restartStatusStr = @"Restarted";
            break;

        case GW_RESTART_APP_RC_INVALID:
            restartStatusStr = @"Restart failed";
            break;

        default:
            break;
    }

    return restartStatusStr;
}

+ (NSString*)AJGWCAclResponseCodeToString:(AJGWCAclResponseCode) aclResponseCode
{
    NSString* aclResponseCodeStr;

    switch (aclResponseCode) {
        case GW_ACL_RC_SUCCESS:
            aclResponseCodeStr = @"Success";
            break;

        case GW_ACL_RC_INVALID:
            aclResponseCodeStr = @"Invalid";
            break;

        case GW_ACL_RC_REGISTER_ERROR:
            aclResponseCodeStr = @"Register error";
            break;

        case GW_ACL_RC_ACL_NOT_FOUND:
            aclResponseCodeStr = @"Not found";
            break;

        case GW_ACL_RC_PERSISTENCE_ERROR:
            aclResponseCodeStr = @"Persistence error";
            break;

        case GW_ACL_RC_POLICYMANAGER_ERROR:
            aclResponseCodeStr = @"Policy manager error";

        default:
            break;
    }

    return aclResponseCodeStr;
}

+ (NSString*)AJGWCAclStatusToString:(AJGWCAclStatus) aclStatus
{
    NSString* aclStatusStr;

    switch (aclStatus) {
        case GW_AS_INACTIVE:
            aclStatusStr = @"Inactive";
            break;

        case GW_AS_ACTIVE:
            aclStatusStr = @"Active";

        default:
            break;
    }

    return aclStatusStr;
}
@end
