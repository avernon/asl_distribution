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
 * {@code UserInputDetails} contains information about the input provided by
 * user for an action.
 * 
 */
public class UserInputDetails
{
    private String title;
    private String message;
    private String positiveButton;
    private String negativeButton;
    private String neutralButton;
    private String[] options;

    /**
     * This constructor can be used to present the user with a notification
     * message. For e.g.<br>
     * <br>
     * 
     * {@code new UserInputDetails("Onboard DUT","Please Onboard the device to the Personal AP and then click Continue", "Continue"); }
     * 
     * @param title
     *            the title of the popup box
     * @param message
     *            the message presented to the user
     * @param dismissButton
     *            name of the dismiss button
     */
    public UserInputDetails(String title, String message, String dismissButton)
    {
        this.title = title;
        this.message = message;
        this.positiveButton = dismissButton;
    }

    /**
     * This constructor can be used to present the user with a dialog and ask
     * the user to confirm some event or action. For e.g.<br>
     * <br>
     * 
     * {@code new UserInputDetails("Message Confirmation","Was the message received", "Yes", "No"); }
     * 
     * @param title
     *            the title of the popup box
     * @param message
     *            the message presented to the user
     * @param positiveButton
     *            name of the positive response button
     * @param negativeButton
     *            name of the negative response button
     */
    public UserInputDetails(String title, String message, String positiveButton, String negativeButton)
    {
        this.title = title;
        this.message = message;
        this.positiveButton = positiveButton;
        this.negativeButton = negativeButton;
    }

    /**
     * This constructor can be used to present the user with a dialog and ask
     * the user to confirm some event or action. For e.g.<br>
     * <br>
     * 
     * {@code new UserInputDetails("Message Confirmation","Was the message received", "Yes", "No", "Not Applicable"); }
     * 
     * @param title
     *            the title of the popup box
     * @param message
     *            the message presented to the user
     * @param positiveButton
     *            name of the positive response button
     * @param negativeButton
     *            name of the negative response button
     * @param neutralButton
     *            name of the neutral response button
     */
    public UserInputDetails(String title, String message, String positiveButton, String negativeButton, String neutralButton)
    {
        this.title = title;
        this.message = message;
        this.positiveButton = positiveButton;
        this.negativeButton = negativeButton;
        this.neutralButton = neutralButton;
    }

    /**
     * This constructor can be used to present the user with a dialog and ask
     * the user to select one of the options presented. For e.g.<br>
     * <br>
     * 
     * {@code String[] msgArray = }{{@code "Priority Message 1", "Priority
     * Message 2", "Priority Message 3" } ; <br>
     * {@code new UserInputDetails("Select the message(s) received", msgArray); }
     * 
     * @param title
     *            the title of the popup box
     * @param options
     *            the array of options presented to the user
     */
    public UserInputDetails(String title, String[] options)
    {
        this.title = title;
        this.options = options;
    }

    /**
     * @return the title of the popup box
     */
    public String getTitle()
    {
        return title;
    }

    /**
     * @param title
     *            the title of the popup box
     */
    public void setTitle(String title)
    {
        this.title = title;
    }

    /**
     * @return the message presented to the user
     */
    public String getMessage()
    {
        return message;
    }

    /**
     * @param message
     *            the message presented to the user
     */
    public void setMessage(String message)
    {
        this.message = message;
    }

    /**
     * @return name of the positive response button
     */
    public String getPositiveButton()
    {
        return positiveButton;
    }

    /**
     * @param positiveButton
     *            name of the positive response button, e.g. {@code Ok}
     */
    public void setPositiveButton(String positiveButton)
    {
        this.positiveButton = positiveButton;
    }

    /**
     * @return name of the negative response button
     */
    public String getNegativeButton()
    {
        return negativeButton;
    }

    /**
     * @param negativeButton
     *            name of the negative response button, e.g. {@code Cancel}
     */
    public void setNegativeButton(String negativeButton)
    {
        this.negativeButton = negativeButton;
    }

    /**
     * @return name of the neutral response button
     */
    public String getNeutralButton()
    {
        return neutralButton;
    }

    /**
     * @param neutralButton
     *            name of the neutral response button
     */
    public void setNeutralButton(String neutralButton)
    {
        this.neutralButton = neutralButton;
    }

    /**
     * @return array of options
     */
    public String[] getOptions()
    {
        return options;
    }

    /**
     * @param options
     */
    public void setOptions(String[] options)
    {
        this.options = options;
    }
}