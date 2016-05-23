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

import java.lang.reflect.Method;
import java.util.Comparator;

import org.alljoyn.validation.framework.annotation.ValidationTest;

public class ValidationTestComparator implements Comparator<Method>
{
    private static final ValidationTestComparator INSTANCE = new ValidationTestComparator();

    private ValidationTestComparator()
    {
    }

    public static ValidationTestComparator getInstance()
    {
        return INSTANCE;
    }

    @Override
    public int compare(Method o1, Method o2)
    {
        ValidationTest validationTest1 = o1.getAnnotation(ValidationTest.class);
        ValidationTest validationTest2 = o2.getAnnotation(ValidationTest.class);
        if (validationTest1.order() == validationTest2.order())
        {
            return validationTest1.name().compareTo(validationTest2.name());
        }
        else
        {
            return Integer.valueOf(validationTest1.order()).compareTo(validationTest2.order());
        }
    }
}