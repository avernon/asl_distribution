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

package org.alljoyn.about;

/**
 * The exception is thrown when an internal error has occurred in the {@link AboutService}
 * @deprecated
 */
@Deprecated
public class AboutServiceException extends RuntimeException {
    private static final long serialVersionUID = -6407441278632848769L;

    @Deprecated
    public AboutServiceException() {
    }

    /**
     * @deprecated
     * @param message user-defined message
     */
    @Deprecated
    public AboutServiceException(String message) {
        super(message);
    }

    /**
     * @deprecated
     * @param cause the cause of this exception
     */
    @Deprecated
    public AboutServiceException(Throwable cause) {
        super(cause);
    }

    /**
     * @deprecated
     * @param message user-defined message
     * @param cause the cause of this exception
     */
    @Deprecated
    public AboutServiceException(String message, Throwable cause) {
        super(message, cause);
    }

}
