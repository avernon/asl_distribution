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
#ifndef _CONTROLLER_CLIENT_DEFS_H_
#define _CONTROLLER_CLIENT_DEFS_H_
/**
 * \ingroup ControllerClient
 */

/**
 *  \file  lighting_controller_client/inc/ControllerClientDefs.h
 * This file provides definitions for the Lighting Controller Client
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

#include <LSFTypes.h>
#include <LSFResponseCodes.h>
#include <Mutex.h>

namespace lsf {

/**
 * Error Codes representing any internal errors in the Lighting
 * Controller Client. The Controller Client will invoke the
 * ControllerClientErrorCB with this error code to inform the
 * User Application about an internal error
 * TODO: Any Lighting Controller specific internal error should be
 * defined here
 */
typedef enum _ErrorCode {
    /**< No Error */
    ERROR_NONE = 0,
    /**< Error encountered when trying to register signal handlers */
    ERROR_REGISTERING_SIGNAL_HANDLERS = 1,
    /**< No active Controller Service found */
    ERROR_NO_ACTIVE_CONTROLLER_SERVICE_FOUND = 2,
    /**< AllJoyn Method Call Timeout */
    ERROR_ALLJOYN_METHOD_CALL_TIMEOUT = 3,
    /**< Irrecoverable error */
    ERROR_IRRECOVERABLE = 4,
    /**< Disconnected from the AllJoyn Bus */
    ERROR_DISCONNECTED_FROM_BUS = 5,
    /**< Controller Client is exiting */
    ERROR_CONTROLLER_CLIENT_EXITING = 6,
    /**< Received an AllJoyn message with invalid arguments */
    ERROR_MESSAGE_WITH_INVALID_ARGS = 7,
    /**< Last value */
    ERROR_LAST_VALUE = 8
} ErrorCode;
/**
 * List of enum error codes
 */
typedef std::list<ErrorCode> ErrorCodeList;
/**
 * convert error code enum type to string type
 */
const char* ControllerClientErrorText(ErrorCode errorCode);

/**
 * Status returned by an invoked Controller Client
 * API function call
 */
typedef enum _ControllerClientStatus {
    CONTROLLER_CLIENT_OK = 0,                 /**< Success */
    CONTROLLER_CLIENT_ERR_NOT_CONNECTED = 1,  /**< The Controller Client is not connected to any Controller Service */
    CONTROLLER_CLIENT_ERR_FAILURE = 2,        /**< The requested operation failed. Look at the error logs to understand the underlying issue */
    CONTROLLER_CLIENT_ERR_RETRY = 3,          /**< The requested operation should be re-tried */
    CONTROLLER_CLIENT_LAST_VALUE = 4          /**< Last value */
} ControllerClientStatus;

/**
 * Convert ControllerClientStatus enum type to string type
 */
const char* ControllerClientStatusText(ControllerClientStatus status);

} // namespace lsf

#endif
