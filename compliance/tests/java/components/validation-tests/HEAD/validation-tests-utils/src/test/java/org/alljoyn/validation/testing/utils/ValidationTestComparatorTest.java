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

import static org.junit.Assert.assertEquals;

import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;

import org.alljoyn.validation.framework.annotation.ValidationTest;
import org.alljoyn.validation.testing.utils.ValidationTestComparator;
import org.junit.Test;

import edu.emory.mathcs.backport.java.util.Collections;

public class ValidationTestComparatorTest
{

    private static class SampleTest
    {
        @ValidationTest(name = "Sample-v1-01", order = -2)
        public void test1()
        {
        }

        @ValidationTest(name = "Sample-v1-02")
        public void test2()
        {
        }

        @ValidationTest(name = "Sample-v1-03")
        public void test3()
        {
        }

        @ValidationTest(name = "Sample-v1-04", order = -1)
        public void test4()
        {
        }
    }

    @Test
    public void testSameOrder() throws Exception
    {
        List<Method> methods = new ArrayList<Method>();
        methods.add(SampleTest.class.getMethod("test1"));
        methods.add(SampleTest.class.getMethod("test2"));
        methods.add(SampleTest.class.getMethod("test3"));
        methods.add(SampleTest.class.getMethod("test4"));
        Collections.sort(methods, ValidationTestComparator.getInstance());
        assertEquals("test1", methods.get(0).getName());
        assertEquals("test4", methods.get(1).getName());
        assertEquals("test2", methods.get(2).getName());
        assertEquals("test3", methods.get(3).getName());
    }
}
