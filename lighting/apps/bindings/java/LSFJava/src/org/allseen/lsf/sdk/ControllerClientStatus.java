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
 * Enum describing the status returned by a controller client function call.
 */
public enum ControllerClientStatus {
    /**
     * Indicates that controller client operation was successful.
     */
    OK,

    /**
     * Indicates that the controller client operation failed because the controller
     * client is not connected to a controller service.
     */
    ERR_NOT_CONNECTED,

    /**
     * Indicates that the controller client operation failed. Look at the error logs
     * to determine why the failure occurred.
     */
    ERR_FAILURE,

    /**
     * Indicates that the controller client operation failed and should be retried.
     */
    ERR_RETRY;

    /** Static lookup, used by the native code */
    @SuppressWarnings("unused")
    private static ControllerClientStatus fromValue(int value) {
        for (ControllerClientStatus c : ControllerClientStatus.values()) {
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
