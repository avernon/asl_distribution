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

package org.allseen.lsf;

public enum ResponseCode {
    OK(0),                      /* Success status */
    ERR_NULL(1),                /* Unexpected NULL pointer */
    ERR_UNEXPECTED(2),          /* An operation was unexpected at this time */
    ERR_INVALID(3),             /* A value was invalid */
    ERR_UNKNOWN(4),             /* A unknown value */
    ERR_FAILURE(5),             /* A failure has occurred */
    ERR_BUSY(6),                /* An operation failed and should be retried later */
    ERR_REJECTED(7),            /* The request was rejected */
    ERR_RANGE(8),               /* Value provided was out of range */
    ERR_UNDEFINED1(9),          /* [This response code is not defined] */
    ERR_INVALID_FIELD(10),      /* Invalid param/state field */
    ERR_MESSAGE(11),            /* Invalid message */
    ERR_INVALID_ARGS(12),       /* The arguments were invalid */
    ERR_EMPTY_NAME(13),         /* The name is empty */
    ERR_RESOURCES(14),          /* not enough resources */
    ERR_PARTIAL(15),            /* The requested operation was only partially successful */
    ERR_NOT_FOUND(16),          /* The entity of interest was not found */
    ERR_NO_SLOT(17),            /* There is no slot for new entry */
    ERR_DEPENDENCY(18),         /* There is a dependency of the entity for which a delete request was received */
    RESPONSE_CODE_LAST(19);     /* The last LSF response code */

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
     * Gets the integer value.
     *
     * @return the integer value
     */
    public int getValue() { return value; }
}
