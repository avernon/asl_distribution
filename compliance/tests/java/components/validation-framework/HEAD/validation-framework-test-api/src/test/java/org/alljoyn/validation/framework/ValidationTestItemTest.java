/*******************************************************************************
 *  Copyright (c) 2013 - 2014, AllSeen Alliance. All rights reserved.
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

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;
import static org.mockito.Mockito.mock;

import org.junit.Test;

public class ValidationTestItemTest
{
    private static final int TIMEOUT_IN_MILLISECONDS = 500;
    private static final int DEFAULT_TIMEOUT_IN_MILLISECONDS = 120000;
    private static final String METHOD_NAME = "methodName";
    private static final String CLASS_NAME = "className";
    private static final String TEST_CASE_ID = "testCaseId";

    @Test
    public void constructWithoutTimeout()
    {
        ValidationTestItem validationTestItem = new ValidationTestItem(TEST_CASE_ID, CLASS_NAME, METHOD_NAME);

        validate(validationTestItem, DEFAULT_TIMEOUT_IN_MILLISECONDS);
        assertNull(validationTestItem.getTestGroup());
    }

    @Test
    public void constructWithTimeout()
    {
        ValidationTestItem validationTestItem = new ValidationTestItem(TEST_CASE_ID, CLASS_NAME, METHOD_NAME, TIMEOUT_IN_MILLISECONDS);

        validate(validationTestItem, TIMEOUT_IN_MILLISECONDS);
        assertNull(validationTestItem.getTestGroup());
    }

    @Test
    public void setTestGroup()
    {
        ValidationTestGroup testGroup = mock(ValidationTestGroup.class);
        ValidationTestItem validationTestItem = new ValidationTestItem(TEST_CASE_ID, CLASS_NAME, METHOD_NAME, TIMEOUT_IN_MILLISECONDS);
        validationTestItem.setTestGroup(testGroup);

        validate(validationTestItem, TIMEOUT_IN_MILLISECONDS);
        assertEquals(testGroup, validationTestItem.getTestGroup());
    }

    private void validate(ValidationTestItem validationTestItem, int timeout)
    {
        assertEquals(TEST_CASE_ID, validationTestItem.getTestCaseId());
        assertEquals(CLASS_NAME, validationTestItem.getClassName());
        assertEquals(METHOD_NAME, validationTestItem.getMethodName());
        assertEquals(timeout, validationTestItem.getTimeoutInMilliseconds());
    }
}