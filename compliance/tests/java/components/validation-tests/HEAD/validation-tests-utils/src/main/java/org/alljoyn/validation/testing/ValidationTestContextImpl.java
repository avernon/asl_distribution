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
package org.alljoyn.validation.testing;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.alljoyn.validation.framework.AppUnderTestDetails;
import org.alljoyn.validation.framework.InterfaceAttribute;
import org.alljoyn.validation.framework.TestCaseNoteListener;
import org.alljoyn.validation.framework.UserInputDetails;
import org.alljoyn.validation.framework.UserResponse;
import org.alljoyn.validation.framework.ValidationTestContext;

import android.util.Log;

public class ValidationTestContextImpl implements ValidationTestContext
{
    private AppUnderTestDetails appUnderTestDetails;

    public void setAppUnderTestDetails(AppUnderTestDetails appUnderTestDetails)
    {
        this.appUnderTestDetails = appUnderTestDetails;
    }

    private String testObjectPath;
    private Object context;
    private String keyStorePath;
    private Map<String, Object> testParameterMap = new HashMap<String, Object>();

    private TestCaseNoteListener testCaseNoteListener = new TestCaseNoteListener()
    {
        @Override
        public void addNote(String note)
        {
            Log.i("TEST_CASE_NOTE", String.format("Note added: %s", note));
        }
    };

    @Override
    public AppUnderTestDetails getAppUnderTestDetails()
    {
        return appUnderTestDetails;
    }

    @Override
    public String getTestObjectPath()
    {
        return testObjectPath;
    }

    public void setTestObjectPath(String testObjectPath)
    {
        this.testObjectPath = testObjectPath;
    }

    @Override
    public Object getContext()
    {
        return context;
    }

    public void setContext(Object context)
    {
        this.context = context;
    }

    @Override
    public void addNote(String note)
    {
        testCaseNoteListener.addNote(note);
    }

    public TestCaseNoteListener getTestCaseNoteListener()
    {
        return testCaseNoteListener;
    }

    public void setTestCaseNoteListener(TestCaseNoteListener testCaseNoteListener)
    {
        this.testCaseNoteListener = testCaseNoteListener;
    }

    @Override
    public UserResponse waitForUserInput(UserInputDetails userInputDetails) throws InterruptedException
    {
        return new UserResponse();
    }

    @Override
    public void addInterfaceDetails(String interfaceName, short version, String objectPath, String details, List<InterfaceAttribute> attributes)
    {
    }

    @Override
    public String getKeyStorePath()
    {
        return keyStorePath;
    }

    public void setKeyStorePath(String keyStorePath)
    {
        this.keyStorePath = keyStorePath;
    }

    @Override
    public Object getTestParameter(String parameterName)
    {
        return testParameterMap.get(parameterName);
    }

    public void setTestParameter(String parameterName, Object parameterValue)
    {
        testParameterMap.put(parameterName, parameterValue);
    }
}