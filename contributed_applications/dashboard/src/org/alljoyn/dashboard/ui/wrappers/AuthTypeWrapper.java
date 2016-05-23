/*
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
*/
package org.alljoyn.dashboard.ui.wrappers;

import org.alljoyn.onboarding.OnboardingService.AuthType;

/**
 * A wrapper class for hosting a AuthType inside an ArrayAdapter. So that the
 * label is displayed, while practically the real value is used.
 */
public class AuthTypeWrapper {
    public final AuthType value;

    public AuthTypeWrapper(AuthType value) {
        super();
        this.value = value;
    }

    @Override
    // This does the trick of displaying the label and not the value in the
    // Adapter
    public String toString() {
        if (AuthType.WPA_AUTO.equals(value)
                || AuthType.WPA_CCMP.equals(value)
                || AuthType.WPA_TKIP.equals(value)) {
            return "WPA";
        } else if (AuthType.WPA2_AUTO.equals(value)
                || AuthType.WPA2_CCMP.equals(value)
                || AuthType.WPA2_TKIP.equals(value)) {
            return "WPA2";
        } else if (AuthType.OPEN.equals(value)) {
            return "None";
        }
        return value.toString();
    }
}
