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
package org.alljoyn.validation.framework;

/**
 * This interface defines methods that provide information between the tests and
 * framework classes.
 */
public interface ValidationTestContext extends TestCaseNoteListener, UserInputHandler, InterfaceDetailsListener
{
    /**
     * @return Android test context
     */
    Object getContext();

    /**
     * @return object that contains details about the app that is being tested
     */
    AppUnderTestDetails getAppUnderTestDetails();

    /**
     * @return path of the object being tested on the Alljoyn bus, e.g.
     *         {@code /About}
     */
    String getTestObjectPath();

    /**
     * @return path of the KeyStore location
     */
    String getKeyStorePath();

    /**
     * Provides the value of the provided parameter name
     * 
     * @param parameterName
     *            name of the parameter, e.g.
     *            {@code org.alljoyn.Onboarding.PersonalApSsid}
     * @return value of parameter
     */
    Object getTestParameter(String parameterName);
}