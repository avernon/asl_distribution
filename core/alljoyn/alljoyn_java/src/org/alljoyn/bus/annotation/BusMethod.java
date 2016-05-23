/*
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Contributed by Qualcomm Connected Experiences, Inc.,
 *    with authorization from the AllSeen Alliance, Inc.
 *    
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *    
 *        http://www.apache.org/licenses/LICENSE-2.0
 *    
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *    
 *    Pursuant to Section 1 of the License, the work of authorship constituting
 *    a Work and any Contribution incorporated in the Work shall mean only that
 *    Contributor's code submissions authored by that Contributor.  Any rights
 *    granted under the License are conditioned upon acceptance of these
 *    clarifications.
 */

package org.alljoyn.bus.annotation;

import java.lang.annotation.Documented;
import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

/**
 * Indicates that a particular member of an AllJoyn exportable interface
 * is defined to be a AllJoyn method.
 */
@Documented
@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.METHOD)
public @interface BusMethod {

    /**
     * Override of method name.
     * The default AllJoyn method name is the Java method name.
     *
     * @return name specified in the BusMethod annotation
     */
    String name() default "";

    /**
     * Input signature for method.
     *
     * @see Signature
     *
     * @return signature specified in the BusMethod annotation
     */
    String signature() default "";

    /**
     * Output signature for method.
     *
     * @see Signature
     *
     * @return replySignature specified in the BusMethod annotation
     */
    String replySignature() default "";

    /**
     * Description of this method
     *
     * @return description specified in the BusMethod annotation
     */
    String description() default "";

    /** No reply annotate flag. */
    int ANNOTATE_NO_REPLY = 1;

    /** Deprecated annotate flag. */
    int ANNOTATE_DEPRECATED = 2;

    /**
     * Annotate introspection data for method.
     * The annotation is the exclusive OR of the flags ANNOTATE_NO_REPLY and
     * ANNOTATE_DEPRECATED.  See org.freedesktop.DBus.Deprecated and
     * org.freedesktop.DBus.Method.NoReply in the D-Bus Specification.
     *
     * @return annotation annotate flag specified in the BusMethod annotation
     */
    int annotation() default 0;
}
