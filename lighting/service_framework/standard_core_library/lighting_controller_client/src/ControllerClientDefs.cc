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

#include <ControllerClientDefs.h>
#include <LSFTypes.h>

namespace lsf {

const char* ControllerClientErrorText(ErrorCode errorCode)
{
    switch (errorCode) {
        LSF_CASE(ERROR_NONE);
        LSF_CASE(ERROR_REGISTERING_SIGNAL_HANDLERS);
        LSF_CASE(ERROR_NO_ACTIVE_CONTROLLER_SERVICE_FOUND);
        LSF_CASE(ERROR_ALLJOYN_METHOD_CALL_TIMEOUT);
        LSF_CASE(ERROR_IRRECOVERABLE);
        LSF_CASE(ERROR_DISCONNECTED_FROM_BUS);
        LSF_CASE(ERROR_CONTROLLER_CLIENT_EXITING);
        LSF_CASE(ERROR_MESSAGE_WITH_INVALID_ARGS);
        LSF_CASE(ERROR_LAST_VALUE);

    default:
        return "<unknown>";
    }
}

const char* ControllerClientStatusText(ControllerClientStatus status)
{
    switch (status) {
        LSF_CASE(CONTROLLER_CLIENT_OK);
        LSF_CASE(CONTROLLER_CLIENT_ERR_NOT_CONNECTED);
        LSF_CASE(CONTROLLER_CLIENT_ERR_FAILURE);
        LSF_CASE(CONTROLLER_CLIENT_ERR_RETRY);
        LSF_CASE(CONTROLLER_CLIENT_LAST_VALUE);

    default:
        return "<unknown>";
    }
}

}
