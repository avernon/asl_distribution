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
package org.alljoyn.validation.testing.utils;

import static org.junit.Assert.assertEquals;

import org.alljoyn.validation.framework.UserInputDetails;
import org.alljoyn.validation.framework.UserInputHandler;
import org.alljoyn.validation.framework.UserResponse;
import org.junit.Before;
import org.junit.Ignore;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mockito;
import org.robolectric.Robolectric;
import org.robolectric.annotation.Config;
import org.robolectric.shadows.ShadowAlertDialog;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;

@RunWith(MyRobolectricTestRunner.class)
@Config(manifest = "AndroidManifest.xml")
public class UserInputHandlerImplTest
{

    Activity activity;
    UserInputHandler dialogMessageHandler;

    @Before
    public void setup()
    {
        activity = Robolectric.buildActivity(Activity.class).create().start().resume().get();

        dialogMessageHandler = new UserInputHandlerImpl(activity);

    }

    @Test
    @Ignore
    public void waitForUserInputPositiveButton() throws InterruptedException
    {
        UserInputDetails userInputDetails = Mockito.mock(UserInputDetails.class);
        Mockito.when(userInputDetails.getPositiveButton()).thenReturn("Positive Button");
        Mockito.when(userInputDetails.getMessage()).thenReturn("Message");
        Mockito.when(userInputDetails.getTitle()).thenReturn("Title");

        UserResponse userResponse = dialogMessageHandler.waitForUserInput(userInputDetails);
        AlertDialog dialog = ShadowAlertDialog.getLatestAlertDialog();

        ShadowAlertDialog shadowOfDialog = Robolectric.shadowOf(dialog);
        assertEquals(shadowOfDialog.getMessage(), "Positive Message");
        assertEquals(shadowOfDialog.getTitle(), "Title");

        dialog.getButton(DialogInterface.BUTTON_POSITIVE).performClick();

        assertEquals(UserResponse.POSITIVE_BUTTON, userResponse.getButtonPressed());
    }

    @Test
    @Ignore
    public void waitForUserInputNegativeButton() throws InterruptedException
    {
        UserInputDetails userInputDetails = Mockito.mock(UserInputDetails.class);
        Mockito.when(userInputDetails.getPositiveButton()).thenReturn("Negative Button");
        Mockito.when(userInputDetails.getMessage()).thenReturn("Negative Message");

        UserResponse userResponse = dialogMessageHandler.waitForUserInput(userInputDetails);
        AlertDialog dialog = ShadowAlertDialog.getLatestAlertDialog();

        ShadowAlertDialog shadowOfDialog = Robolectric.shadowOf(dialog);
        assertEquals(shadowOfDialog.getMessage(), "Negative Message");

        dialog.getButton(DialogInterface.BUTTON_NEGATIVE).performClick();

        assertEquals(UserResponse.NEGATIVE_BUTTON, userResponse.getButtonPressed());
    }

    @Test
    @Ignore
    public void waitForUserInputNeutralButton() throws InterruptedException
    {
        UserInputDetails userInputDetails = Mockito.mock(UserInputDetails.class);
        Mockito.when(userInputDetails.getPositiveButton()).thenReturn("Neutral Button");
        Mockito.when(userInputDetails.getMessage()).thenReturn("Neutral Message");

        UserResponse userResponse = dialogMessageHandler.waitForUserInput(userInputDetails);
        AlertDialog dialog = ShadowAlertDialog.getLatestAlertDialog();

        ShadowAlertDialog shadowOfDialog = Robolectric.shadowOf(dialog);
        assertEquals(shadowOfDialog.getMessage(), "Neutral Message");

        dialog.getButton(DialogInterface.BUTTON_NEUTRAL).performClick();

        assertEquals(UserResponse.NEUTRAL_BUTTON, userResponse.getButtonPressed());
    }

}
