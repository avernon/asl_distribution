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

import org.junit.Test;
import org.junit.runner.RunWith;
import org.powermock.api.mockito.PowerMockito;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;

import android.os.Bundle;
import android.test.InstrumentationTestRunner;

@RunWith(PowerMockRunner.class)
@PrepareForTest(
{ ValidationInstrumentationTestRunner.class, ValidationInstrumentationTestRunnerHelper.class, InstrumentationTestRunner.class })
public class ValidationInstrumentationTestRunnerTest
{
    private ValidationInstrumentationTestRunner instrumentTestRunner;

    @Test
    public void testOnCreate() throws Exception
    {
        PowerMockito.suppress(PowerMockito.constructor(InstrumentationTestRunner.class));
        PowerMockito.suppress(PowerMockito.method(ValidationInstrumentationTestRunnerHelper.class, "onCreate", ValidationInstrumentationTestRunner.class, Bundle.class));
        instrumentTestRunner = new ValidationInstrumentationTestRunner()
        {
            @Override
            public void callingSuperOnCreate(Bundle arguments)
            {
            }
        };

        instrumentTestRunner.onCreate(null);
    }

    @Test
    public void testGetAllTests() throws Exception
    {
        PowerMockito.suppress(PowerMockito.constructor(InstrumentationTestRunner.class));
        PowerMockito.suppress(PowerMockito.method(ValidationInstrumentationTestRunnerHelper.class, "getAllTests", ValidationInstrumentationTestRunner.class));
        instrumentTestRunner = new ValidationInstrumentationTestRunner();

        instrumentTestRunner.getAllTests();
    }
}
