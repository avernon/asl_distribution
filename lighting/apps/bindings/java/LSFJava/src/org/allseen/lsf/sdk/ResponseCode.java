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
 * Enum describing the response codes that will be returned by a controller
 * client operation.
 */
public enum ResponseCode {
    /**
     * Indicates a success status.
     */
    OK(0),

    /**
     * Indicates an unexpected null pointer.
     */
    ERR_NULL(1),

    /**
     * Indictes an operation was unexpected.
     */
    ERR_UNEXPECTED(2),

    /**
     * Indicates a value was invalid.
     */
    ERR_INVALID(3),

    /**
     * Indicates a value was unknown.
     */
    ERR_UNKNOWN(4),

    /**
     * Indicates that the operation failed.
     */
    ERR_FAILURE(5),

    /**
     * Indicates that the operation failed and should be retried later.
     */
    ERR_BUSY(6),

    /**
     * Indicates that the operation request was rejected.
     */
    ERR_REJECTED(7),

    /**
     * Indicates that the value provided was out of range.
     */
    ERR_RANGE(8),

    /**
     * Indicates an undefined response code.
     */
    ERR_UNDEFINED1(9),

    /**
     * Indicates that the parameter or field was invalid.
     */
    ERR_INVALID_FIELD(10),

    /**
     * Indicates that the message sent was invalid.
     */
    ERR_MESSAGE(11),

    /**
     * Indicates that the arguments sent were invalid.
     */
    ERR_INVALID_ARGS(12),

    /**
     * Indicates that the name is empty.
     */
    ERR_EMPTY_NAME(13),

    /**
     * Indicates that the operation failed due to lack of resources.
     */
    ERR_RESOURCES(14),

    /**
     * Indicates that the reply received contained invalid arguments.
     */
    ERR_REPLY_WITH_INVALID_ARGS(15),

    /**
     * Indicates that the operation was only partially successful.
     */
    ERR_PARTIAL(16),

    /**
     * Indicates that entity of interest was not found.
     */
    ERR_NOT_FOUND(17),

    /**
     * Indicates that there is no slot to send the message.
     */
    ERR_NO_SLOT(18),

    /**
     * Indicates that there is a dependency for the entity for which a delete request was received.
     */
    ERR_DEPENDENCY(19),

    /**
     * The last LSF response code.
     */
    RESPONSE_CODE_LAST(20);

    /** Integer value */
    private int value;

    /** Constructor */
    private ResponseCode(int value) {
        this.value = value;
    }

    /** Static lookup, used by the native code */
    @SuppressWarnings("unused")
    private static ResponseCode fromValue(int value) {
        for (ResponseCode c : ResponseCode.values()) {
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
    public int getValue() { return value; }
}
