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
package org.alljoyn.validation.testing.instrument;

import java.util.UUID;

import junit.framework.TestCase;

import org.alljoyn.validation.framework.AppUnderTestDetails;
import org.alljoyn.validation.framework.TestCaseNoteListener;
import org.alljoyn.validation.framework.UserInputDetails;
import org.alljoyn.validation.framework.UserInputHandler;
import org.alljoyn.validation.framework.UserResponse;
import org.alljoyn.validation.framework.ValidationBaseTestCase;
import org.alljoyn.validation.framework.ValidationTestCase;
import org.alljoyn.validation.testing.ValidationTestContextImpl;

import android.test.ActivityInstrumentationTestCase2;
import android.util.Log;

public class InstrumentationTestCaseWrapper extends ActivityInstrumentationTestCase2<ValidationInstrumentationTestActivity>
{
    protected ValidationBaseTestCase testCase;

    public InstrumentationTestCaseWrapper(Class<? extends TestCase> clazz, String methodName) throws Exception
    {
        super(ValidationInstrumentationTestActivity.class);

        if (!ValidationTestCase.class.isAssignableFrom(clazz))
        {
            throw new RuntimeException("Class must implement ValidationTestCase");
        }

        testCase = (ValidationBaseTestCase) clazz.newInstance();
        testCase.setName(methodName);
        setName(methodName);
    }

    @Override
    protected void setUp() throws Exception
    {
        Log.d("InstrumentationTest", "Setting up test");
        String absolutePath = getInstrumentation().getContext().getFileStreamPath("alljoyn_keystore").getAbsolutePath();
        final ValidationInstrumentationApplication instrumentApp = (ValidationInstrumentationApplication) getInstrumentation().getContext().getApplicationContext();

        ValidationTestContextImpl testContext = null;
        boolean useGui = Boolean.parseBoolean(instrumentApp.getInstrumentParameter(InstrumentationArgKey.EnableInteractive.getValue()));

        if (useGui)
        {
            testContext = createTestContextWhichUsesGuiToHandleUserInput();
        }
        else
        {
            testContext = createTestContext(instrumentApp);
        }

        for (InstrumentationArgKey argKey : InstrumentationArgKey.values())
        {
            String paramkey = argKey.getValue();
            String paramValue = instrumentApp.getInstrumentParameter(paramkey);
            testContext.setTestParameter(paramkey, paramValue);
        }

        testContext.setAppUnderTestDetails(new AppUnderTestDetails(UUID.fromString(instrumentApp.getInstrumentParameter(InstrumentationArgKey.AppId.getValue())), instrumentApp
                .getInstrumentParameter(InstrumentationArgKey.DeviceId.getValue())));

        testContext.setContext(getInstrumentation().getContext());
        testContext.setKeyStorePath(absolutePath);
        testContext.setTestCaseNoteListener(new TestCaseNoteListener()
        {
            @Override
            public void addNote(String note)
            {
                Log.d("InstrumentationTest", String.format("Note added: %s", note));
            }
        });

        String audioStreamObjectPath = instrumentApp.getInstrumentParameter(InstrumentationArgKey.AudioStreamObjectPath.getValue());

        if (audioStreamObjectPath != null && !audioStreamObjectPath.isEmpty())
        {
            testContext.setTestObjectPath(audioStreamObjectPath);
        }

        testCase.setValidationTestContext(testContext);
    }

    @Override
    protected void runTest() throws Throwable
    {
        testCase.runBare();
    }

    private ValidationTestContextImpl createTestContext(final ValidationInstrumentationApplication instrumentApp)
    {
        ValidationTestContextImpl testContext = new ValidationTestContextImpl()
        {
            @Override
            public UserResponse waitForUserInput(UserInputDetails userInputDetails) throws InterruptedException
            {
                String userInputTimeoutValueInMS = instrumentApp.getInstrumentParameter(InstrumentationArgKey.UserInputTimeoutValueInMS.getValue());
                Long timeoutValue = 5000l;

                try
                {
                    timeoutValue = Long.valueOf(userInputTimeoutValueInMS);
                }
                catch (NumberFormatException e)
                {
                    Log.w("error on parsing userInputTimeoutValueInMS.", e);
                }

                Thread.sleep(timeoutValue);

                return new UserResponse();
            }
        };

        return testContext;
    }

    private ValidationTestContextImpl createTestContextWhichUsesGuiToHandleUserInput()
    {
        final UserInputHandler userInputHandler = getActivity().getUserInputHandler();

        ValidationTestContextImpl testContext = new ValidationTestContextImpl()
        {
            @Override
            public UserResponse waitForUserInput(UserInputDetails userInputDetails) throws InterruptedException
            {
                return userInputHandler.waitForUserInput(userInputDetails);
            }
        };

        return testContext;
    }
}