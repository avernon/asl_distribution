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

import static org.junit.Assert.assertNotNull;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;
import junit.framework.TestCase;
import junit.framework.TestSuite;

import org.alljoyn.validation.testing.utils.AllJoynLibraryLoader;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;
import org.powermock.api.mockito.PowerMockito;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.util.Log;

@RunWith(PowerMockRunner.class)
@PrepareForTest(
{ Bundle.class, Log.class, AllJoynLibraryLoader.class, InstrumentationTestCaseWrapper.class, TestCase.class })
public class ValidationInstrumentationTestRunnerHelperTest
{
    private static final String PACKAGE_NAME = "packageName";
    private ValidationInstrumentationTestRunnerHelper helper;
    @Mock
    private ValidationInstrumentationTestRunner runner;
    @Mock
    private Context context;
    @Mock
    private Bundle arguments;
    @Mock
    private ValidationInstrumentationApplication application;
    @Mock
    private InstrumentationTestCaseWrapper instrumentationTestCaseWrapper;
    @Mock
    private PackageManager packageManager;
    @Mock
    private PackageInfo packageInfo;

    @Test
    public void testOnCreate() throws Exception
    {
        PowerMockito.mockStatic(Log.class);
        PowerMockito.suppress(PowerMockito.method(AllJoynLibraryLoader.class, "loadLibrary"));

        when(runner.getContext()).thenReturn(context);
        when(context.getApplicationContext()).thenReturn(application);
        when(context.getPackageManager()).thenReturn(packageManager);
        when(context.getPackageName()).thenReturn(PACKAGE_NAME);
        when(packageManager.getPackageInfo(PACKAGE_NAME, 0)).thenReturn(packageInfo);
        helper = new ValidationInstrumentationTestRunnerHelper();

        helper.onCreate(runner, arguments);
        verify(packageManager).getPackageInfo(PACKAGE_NAME, 0);
    }

    @Test
    public void testOnCreateWithNullArguments() throws Exception
    {
        PowerMockito.mockStatic(Log.class);
        PowerMockito.suppress(PowerMockito.method(AllJoynLibraryLoader.class, "loadLibrary"));

        when(runner.getContext()).thenReturn(context);
        when(context.getApplicationContext()).thenReturn(application);
        when(context.getPackageManager()).thenReturn(packageManager);
        when(context.getPackageName()).thenReturn(PACKAGE_NAME);
        when(packageManager.getPackageInfo(PACKAGE_NAME, 0)).thenReturn(packageInfo);
        helper = new ValidationInstrumentationTestRunnerHelper();

        helper.onCreate(runner, null);
        verify(packageManager).getPackageInfo(PACKAGE_NAME, 0);
    }

    @Test
    public void testGetAllTests() throws Exception
    {
        PowerMockito.mockStatic(Log.class);
        PowerMockito.suppress(PowerMockito.method(AllJoynLibraryLoader.class, "loadLibrary"));
        PowerMockito.suppress(PowerMockito.constructor(InstrumentationTestCaseWrapper.class, Class.class, String.class));

        when(runner.getContext()).thenReturn(context);
        when(context.getApplicationContext()).thenReturn(application);
        when(application.getInstrumentParameter(InstrumentationArgKey.TestSuiteList.getValue())).thenReturn(
                "org.alljoyn.validation.testing.suites.config.ConfigTestSuite,org.alljoyn.validation.testing.suites.about.AboutTestSuite");
        when(application.getInstrumentParameter(InstrumentationArgKey.TestCaseName.getValue())).thenReturn("About-v1-01,Config-v1-01");

        helper = new ValidationInstrumentationTestRunnerHelper();

        TestSuite testSuite = helper.getAllTests(runner);
        assertNotNull(testSuite);
    }

    @Test
    public void testGetAllTestsWithTestCaseNameNull() throws Exception
    {
        PowerMockito.mockStatic(Log.class);
        PowerMockito.suppress(PowerMockito.method(AllJoynLibraryLoader.class, "loadLibrary"));

        when(runner.getContext()).thenReturn(context);
        when(context.getApplicationContext()).thenReturn(application);
        when(application.getInstrumentParameter(InstrumentationArgKey.TestSuiteList.getValue())).thenReturn(
                "org.alljoyn.validation.testing.suites.config.ConfigTestSuite,org.alljoyn.validation.testing.suites.about.AboutTestSuite");
        when(application.getInstrumentParameter(InstrumentationArgKey.TestCaseName.getValue())).thenReturn(null);

        helper = new ValidationInstrumentationTestRunnerHelper();

        TestSuite testSuite = helper.getAllTests(runner);
        assertNotNull(testSuite);
    }
}