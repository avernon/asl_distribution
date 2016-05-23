/*
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
 */

package org.allseen.lsf.sdk;

/**
 * Enum describing Error Codes that represent any internal errors in the Lighting
 * controller client. The controller client will invoke the ControllerClientErrorCB
 * with this error code to inform the user about an internal error.
 */
public enum ErrorCode {
    /**
     * Indicates no error in the controller client.
     */
    NONE,

    /**
     * Indicates an error registering the AllJoyn signal handlers.
     */
    ERR_REGISTERING_SIGNAL_HANDLERS,

    /**
     * Indicates that no controller service was found.
     */
    ERR_NO_ACTIVE_CONTROLLER_SERVICE_FOUND,

    /**
     * Indicates that an AllJoyn method call timed out.
     */
    ERR_ALLJOYN_METHOD_CALL_TIMEOUT,

    /**
     * Indicates an irrecoverable error.
     */
    ERR_IRRECOVERABLE,

    /**
     * Indicates that the AllJoyn bus attachment is not connected.
     */
    ERR_DISCONNECTED_FROM_BUS,

    /**
     * Indicates an error occurred while the controller client is shutting down.
     */
    ERR_CONTROLLER_CLIENT_EXITING,

    /**
     * Indicates that an AllJoyn message was sent to the controller service with invalid args.
     */
    ERR_MESSAGE_WITH_INVALID_ARGS,

    /**
     * Indicates that the same error occurred.
     */
    ERROR_CODE_LAST;

    /** Static lookup, used by the native code */
    @SuppressWarnings("unused")
    private static ErrorCode fromValue(int value) {
        for (ErrorCode c : ErrorCode.values()) {
            if (c.getValue() == value) {
                return c;
            }
        }

        return null;
    }

    /**
     * Gets the integer value of the enum.
     *
     * @return the integer value
     */
    public int getValue() { return ordinal(); }
}
