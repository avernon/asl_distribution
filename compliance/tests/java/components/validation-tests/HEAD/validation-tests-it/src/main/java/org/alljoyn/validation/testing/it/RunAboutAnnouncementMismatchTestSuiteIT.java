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
package org.alljoyn.validation.testing.it;

import java.lang.reflect.Method;

import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;

import org.alljoyn.validation.framework.annotation.ValidationTest;
import org.alljoyn.validation.testing.suites.about.AboutTestSuite;

import android.test.AndroidTestCase;

public class RunAboutAnnouncementMismatchTestSuiteIT extends AndroidTestCase
{
    static
    {
        System.loadLibrary("alljoyn_java");
    }

    public static Test suite() throws Exception
    {
        TestSuite testSuite = new TestSuite();
        getTestCasesFromClass(testSuite, AboutTestSuite.class);
        return testSuite;
    }

    private static void getTestCasesFromClass(TestSuite testSuite, Class<? extends TestCase> clazz) throws Exception
    {
        Method[] methods = clazz.getMethods();
        for (Method method : methods)
        {
            ValidationTest validationTest = method.getAnnotation(ValidationTest.class);

            if (method.getName().startsWith("About-v1-04") && (validationTest != null))
            {
                testSuite.addTest(new AboutAnnouncementMismatchTestCaseWrapper(clazz, method.getName()));
            }
        }
    }
}
