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
 * {@code UserResponse} contains results of an user operation.
 * 
 */
public class UserResponse
{
    public static final int NO_BUTTON = 0;
    public static final int POSITIVE_BUTTON = 1;
    public static final int NEGATIVE_BUTTON = 2;
    public static final int NEUTRAL_BUTTON = 3;
    private int optionSelected = -1;
    private int buttonPressed;

    /**
     * @return number corresponding to the button pressed
     */
    public int getButtonPressed()
    {
        return buttonPressed;
    }

    /**
     * @param buttonPressed
     *            number corresponding to the button pressed
     */
    public void setButtonPressed(int buttonPressed)
    {
        this.buttonPressed = buttonPressed;
    }

    /**
     * @return integer value of the option selected by the user
     */
    public int getOptionSelected()
    {
        return optionSelected;
    }

    /**
     * @param optionSelected
     *            integer value of the option selected by the user
     */
    public void setOptionSelected(int optionSelected)
    {
        this.optionSelected = optionSelected;
    }
}