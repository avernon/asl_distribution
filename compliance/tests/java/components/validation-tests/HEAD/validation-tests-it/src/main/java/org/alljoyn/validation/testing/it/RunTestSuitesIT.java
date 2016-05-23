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

import java.util.ArrayList;
import java.util.List;

import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;

import org.alljoyn.validation.testing.instrument.ValidationTestCaseBuilder;
import org.alljoyn.validation.testing.suites.about.AboutTestSuite;
import org.alljoyn.validation.testing.suites.config.ConfigTestSuite;
//import org.alljoyn.validation.testing.suites.controlpanel.ControlPanelTestSuite;
//import org.alljoyn.validation.testing.suites.gwagent.GWAgentTestSuite;
import org.alljoyn.validation.testing.suites.notification.NotificationConsumerTestSuite;
import org.alljoyn.validation.testing.suites.notification.NotificationProducerTestSuite;

import android.test.AndroidTestCase;
import android.util.Log;

public class RunTestSuitesIT extends AndroidTestCase
{
    public static Test suite() throws Exception
    {
        TestSuite testSuite = new TestSuite();

        TestCase startup = new AllJoynInitializer();
        startup.setName("testStartup");
        testSuite.addTest(startup);

        getTestCasesFromClass(testSuite, AboutTestSuite.class);
        getTestCasesFromClass(testSuite, ConfigTestSuite.class);
        getTestCasesFromClass(testSuite, NotificationProducerTestSuite.class);
        getTestCasesFromClass(testSuite, NotificationConsumerTestSuite.class);
        //getTestCasesFromClass(testSuite, ControlPanelTestSuite.class);
        //getTestCasesFromClass(testSuite, GWAgentTestSuite.class);

        return testSuite;
    }

    private static void getTestCasesFromClass(TestSuite testSuite, Class<? extends TestCase> clazz) throws Exception
    {
        getTestCasesFromClass(testSuite, clazz, new ArrayList<String>());
    }

    private static void getTestCasesFromClass(TestSuite testSuite, Class<? extends TestCase> clazz, List<String> excludedTests) throws Exception
    {
        for (TestCase testCase : ValidationTestCaseBuilder.allTestCasesFromClass(clazz).build())
        {
            if (!excludedTests.contains(testCase.getName()))
            {
                Log.d("RunTestSuitesIT", "Adding test case for: " + testCase.getClass() + "; " + testCase.getName());
                testSuite.addTest(new TestCaseWrapper(testCase));
            }
        }
    }
}
