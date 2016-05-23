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

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.util.HashSet;
import java.util.Set;

import org.alljoyn.validation.testing.utils.SetValidator;
import org.alljoyn.validation.testing.utils.ValidationResult;
import org.junit.Before;
import org.junit.Test;

public class SetValidatorTest
{
    private SetValidator<String> setValidator;
    private Set<String> expectedSet;
    private Set<String> foundSet;

    @Before
    public void setup()
    {
        expectedSet = new HashSet<String>();
        foundSet = new HashSet<String>();
        setValidator = new SetValidator<String>();
    }

    @Test
    public void validIfBothSetsAreEmpty()
    {
        ValidationResult validationResult = setValidator.validate(new HashSet<String>(), new HashSet<String>());

        assertTrue(validationResult.isValid());
        assertTrue(validationResult.getFailureReason().isEmpty());
    }

    @Test
    public void validIfSetsAreEqual()
    {
        expectedSet.add("string1");
        foundSet.add("string1");
        ValidationResult validationResult = setValidator.validate(expectedSet, foundSet);

        assertTrue(validationResult.isValid());
        assertTrue(validationResult.getFailureReason().isEmpty());
    }

    @Test
    public void invalidIfExpectedSetHasExtraElement()
    {
        expectedSet.add("string1");
        expectedSet.add("string2");
        foundSet.add("string1");
        ValidationResult validationResult = setValidator.validate(expectedSet, foundSet);

        assertFalse(validationResult.isValid());
        assertTrue(validationResult.getFailureReason().contains("Missing string2"));
    }

    @Test
    public void invalidIfFoundSetHasExtraElement()
    {
        expectedSet.add("string1");
        foundSet.add("string1");
        foundSet.add("string2");
        ValidationResult validationResult = setValidator.validate(expectedSet, foundSet);

        assertFalse(validationResult.isValid());
        assertTrue(validationResult.getFailureReason().contains("Undefined string2"));
    }

    @Test
    public void invalidIfExpectedSetHasExtraElementAndFoundSetHasExtraElement()
    {
        expectedSet.add("string1");
        expectedSet.add("string2");
        foundSet.add("string1");
        foundSet.add("string3");
        ValidationResult validationResult = setValidator.validate(expectedSet, foundSet);

        assertFalse(validationResult.isValid());
        assertTrue(validationResult.getFailureReason().contains("Missing string2"));
        assertTrue(validationResult.getFailureReason().contains("Undefined string3"));
    }
}