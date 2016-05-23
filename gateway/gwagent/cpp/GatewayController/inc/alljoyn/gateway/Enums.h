/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#ifndef alljoyn_gateway_cpp_Enums_h
#define alljoyn_gateway_cpp_Enums_h

namespace ajn {
namespace gwc {

/**
 * Connection status of the Connector App to the cloud service
 */

typedef enum {
    GW_CS_NOT_INITIALIZED = 0,              //! Not initialized
    GW_CS_IN_PROGRESS = 1,                  //! In progress
    GW_CS_CONNECTED = 2,                    //! Connected
    GW_CS_NOT_CONNECTED = 3,                //! Not connected
    GW_CS_ERROR = 4                         //! Error
} ConnectionStatus;
/**
 * The installation status of the Connector App
 */
typedef enum {
    GW_IS_INSTALLED = 0,                    //!< Installed
    GW_IS_INSTALL_IN_PROGRESS = 1,          //!< Install in progress
    GW_IS_UPGRADE_IN_PROGRESS = 2,          //!< Upgrade in progress
    GW_IS_UNINSTALL_IN_PROGRESS = 3,        //!< Uninstall in progress
    GW_IS_INSTALL_FAILED = 4                //!< Installation failed
} InstallStatus;

/**
 * The operational status of the Connector App
 */
typedef enum {
    GW_OS_RUNNING = 0,                      //!< The application is running
    GW_OS_STOPPED = 1                       //!< The application is stopped
} OperationalStatus;

/**
 * The restart status of the Connector App
 */
typedef enum {
    GW_RESTART_APP_RC_SUCCESS = 0,          //!< The application restarted
    GW_RESTART_APP_RC_INVALID = 1           //!< The application restart failed
} RestartStatus;

/**
 * Access Control List response code.
 * This status is returned as a result of actions applied on the Access Control List
 */
typedef enum {

    GW_ACL_RC_SUCCESS = 0,                  //!< Success
    GW_ACL_RC_INVALID = 1,                  //!< Invalid
    GW_ACL_RC_REGISTER_ERROR = 2,           //!< Register error
    GW_ACL_RC_ACL_NOT_FOUND = 3,            //!< ACL not found
    GW_ACL_RC_PERSISTENCE_ERROR = 4,        //!< ACL persistence error
    GW_ACL_RC_POLICYMANAGER_ERROR = 5,      //!< ACL policy manager error
    GW_ACL_RC_METADATA_ERROR = 6            //!< ACL metadata error
} AclResponseCode;

typedef enum AclStatus {

    GW_AS_INACTIVE = 0,                     //!< Inactive
    GW_AS_ACTIVE = 1                        //!< Active
} AclStatus;
}
}

#endif
