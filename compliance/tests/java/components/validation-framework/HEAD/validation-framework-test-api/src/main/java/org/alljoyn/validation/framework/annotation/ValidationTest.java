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
package org.alljoyn.validation.framework.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

/**
 * A method needs to be annotated with {@code ValidationTest} annotation to
 * indicate that its a test case method.
 */
@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.METHOD)
public @interface ValidationTest
{
    /**
     * Specify <code>name</code> to provide a mapping to the defined test case
     * name. For e.g. {@code About-v1-01}
     */
    String name();

    /**
     * Optionally specify {@code timeout} in milliseconds to provide a mapping
     * to the defined test case timeout.
     */
    long timeout() default -1;

    /**
     * Optionally specify {@code order} to provide a mapping to the defined test
     * case order.
     * 
     * This allows for modifying the order of test case execution. The test
     * cases are executed within a suite based on sorting by the order and test
     * case name. If the order has a default value of 0, the sorting is just
     * based on the test case name.
     */
    int order() default 0;
}