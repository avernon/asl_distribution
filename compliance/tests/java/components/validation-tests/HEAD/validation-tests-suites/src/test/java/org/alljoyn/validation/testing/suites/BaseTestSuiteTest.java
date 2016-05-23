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
package org.alljoyn.validation.testing.suites;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.fail;
import junit.framework.AssertionFailedError;

import org.alljoyn.bus.BusException;

public abstract class BaseTestSuiteTest
{
    public interface TestWrapper
    {
        void executeTestMethod() throws Exception;
    }

    protected void executeTestMethod(TestWrapper testWrapper, BusException expectedException) throws AssertionFailedError, Exception
    {
        BusException actualException = null;
        try
        {
            executeTestMethod(testWrapper);
            fail(String.format("No Exception thrown, expecting BusException: %s", expectedException.toString()));
        }
        catch (BusException e)
        {
            actualException = e;
        }
        assertEquals(expectedException, actualException);
    }

    protected void executeTestMethodThrowsException(TestWrapper testWrapper, String expectedExceptionMessage) throws AssertionFailedError, Exception
    {
        String actualExceptionMessage = null;
        try
        {
            executeTestMethod(testWrapper);
            fail(String.format("No Exception thrown, expecting Exception with message: %s", expectedExceptionMessage));
        }
        catch (Exception e)
        {
            actualExceptionMessage = e.getMessage();
        }
        assertEquals(expectedExceptionMessage, actualExceptionMessage);
    }

    protected void executeTestMethodFailsAssertion(TestWrapper testWrapper, String expectedAssertionFailure) throws Exception
    {
        String assertionFailureMessage = null;
        try
        {
            executeTestMethod(testWrapper);
            fail(String.format("No assertion failure, expecting assertionFailure with message: %s", expectedAssertionFailure));
        }
        catch (AssertionFailedError e)
        {
            assertionFailureMessage = e.getMessage();
        }
        assertEquals(expectedAssertionFailure, assertionFailureMessage);
    }

    abstract protected void executeTestMethod(TestWrapper testWrapper) throws Exception;

}
