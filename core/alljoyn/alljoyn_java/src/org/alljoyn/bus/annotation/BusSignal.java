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
 * is defined to be a AllJoyn signal.
 */
@Documented
@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.METHOD)
public @interface BusSignal {

    /**
     * Override of signal name.
     * The default AllJoyn signal name is the Java method name.
     *
     * @return name specified in the BusSignal annotation
     */
    String name() default "";

    /**
     * Input signature for signal.
     *
     * @see Signature
     *
     * @return signature specified in the BusSignal annotation
     */
    String signature() default "";

    /**
     * Output signature for signal.
     *
     * @see Signature
     *
     * @return replySignature specified in the BusSignal annotation
     */
    String replySignature() default "";

    /**
     * Description for this signal
     *
     * @return description specified in the BusSignal annotation
     */
    String description() default "";

    /**
     * Set to true to document that this signal will be sent sessionless.
     * Note that this does not cause the signal to be sent sessionless,
     * just documents it as such.
     *
     * @return sessionless indicator specified in the BusSignal annotation
     */
    boolean sessionless() default false;

    /** Deprecated annotate flag. */
    int ANNOTATE_DEPRECATED = 2;

    /**
     * Annotate introspection data for method.
     * The annotation may be the flag ANNOTATE_DEPRECATED.  See
     * org.freedesktop.DBus.Deprecated in the D-Bus Specification.
     *
     * @return annotation specifying if this signal is deprecated according to the BusSignal annotation
     */
    int annotation() default 0;
}
