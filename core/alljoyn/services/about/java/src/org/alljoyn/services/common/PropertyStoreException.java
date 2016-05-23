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

package org.alljoyn.services.common;

/**
 * An exception that is thrown by the PropertyStore when illegal arguments are given in set/get methods.
 * @see PropertyStore
 * @deprecated
 */
@Deprecated
public class PropertyStoreException extends Exception {
    private static final long serialVersionUID = -8488311339426012157L;

    /**
     * The given key is not supported
     */
    public final static int UNSUPPORTED_KEY = 0;

    /**
     * The given language is not supported
     */
    public final static int UNSUPPORTED_LANGUAGE = 1;

    /**
     * Trying to set a read-only field
     */
    public final static int ILLEGAL_ACCESS = 2;

    /**
     * Trying to set a field to an invalid
     */
    public final static int INVALID_VALUE = 3;

    private int m_reason;

    @Deprecated
    public PropertyStoreException(int reason)
    {
        m_reason = reason;
    }

    /**
     * The reason for failure
     * @deprecated
     * @return reason for failure
     */
    @Deprecated
    public int getReason()
    {
        return m_reason;
    }
}
