/*******************************************************************************
 *  Copyright AllSeen Alliance. All rights reserved.
 *
 *     Contributed by Qualcomm Connected Experiences, Inc.,
 *     with authorization from the AllSeen Alliance, Inc.
 *     
 *     Licensed under the Apache License, Version 2.0 (the "License");
 *     you may not use this file except in compliance with the License.
 *     You may obtain a copy of the License at
 *     
 *         http://www.apache.org/licenses/LICENSE-2.0
 *     
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 *     
 *     Pursuant to Section 1 of the License, the work of authorship constituting
 *     a Work and any Contribution incorporated in the Work shall mean only that
 *     Contributor's code submissions authored by that Contributor.  Any rights
 *     granted under the License are conditioned upon acceptance of these
 *     clarifications.
 *******************************************************************************/
package org.alljoyn.validation.simulator;

public class DUTSimulatorErrorCodes
{
    public enum ErrorName
    {
        INVALID_VALUE("org.alljoyn.Error.InvalidValue"), FEATURE_NOT_AVAILABLE("org.alljoyn.Error.FeatureNotAvailable"), MAX_SIZE_EXCEEDED("org.alljoyn.Error.MaxSizeExceeded"), LANGUAGE_NOT_SUPPORTED(
                "org.alljoyn.Error.LanguageNotSupported"), UPDATE_NOT_ALLOWED("org.alljoyn.Error.UpdateNotAllowed"), METHOD_NOT_ALLOWED("org.alljoyn.Error.MethodNotAllowed");

        private String errorName;

        private ErrorName(String errorName)
        {
            this.errorName = errorName;
        }

        public String getErrorName()
        {
            return errorName;
        }

    }

    public enum ErrorMessage
    {
        INVALID_VALUE("Invalid value"), FEATURE_NOT_AVAILABLE("Feature not available"), MAX_SIZE_EXCEEDED("Maximum size exceeded"), LANGUAGE_NOT_SUPPORTED(
                "The language specified is not supported"), UPDATE_NOT_ALLOWED("Update Not Allowed"), METHOD_NOT_ALLOWED("Method Not Allowed");

        private String errorMessage;

        private ErrorMessage(String errorMessage)
        {
            this.errorMessage = errorMessage;
        }

        public String getErrorMessage()
        {
            return errorMessage;
        }

    }

}
