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
package org.alljoyn.validation.testing.utils.onboarding;

import junit.framework.Assert;

public class SoftAPValidator extends Assert
{
    private static final String SOFT_AP_ASSERT_MESSAGE = "Soft AP name must start with AJ_ or end with _AJ string";
    private static final String SOFT_AP_PREFIX = "AJ_";
    private static final String SOFT_AP_SUFFIX = "_AJ";

    public static void validateSoftAP(String softAPName)
    {
        assertTrue(SOFT_AP_ASSERT_MESSAGE, softAPName.startsWith(SOFT_AP_PREFIX) || softAPName.endsWith(SOFT_AP_SUFFIX));
    }
}