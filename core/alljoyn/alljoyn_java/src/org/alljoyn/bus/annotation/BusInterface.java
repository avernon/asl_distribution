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
 * Indicates that a given Java interface is also an AllJoyn interface.
 * AllJoyn interfaces contain AllJoyn methods and AllJoyn signals which are
 * exposed to external applications.
 */
@Documented
@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.TYPE)
public @interface BusInterface {

    /**
     * Override of the default interface name.
     * The default AllJoyn interface name is the fully qualified name of
     * the Java interface.  The override may be used to specify the
     * explicit AllJoyn interface name.
     *
     * @return name specified by the BusInterface annotation
     */
    String name() default "";

    /**
     * specify if the interface is announced
     * possible values are "true" or "false"
     * defaults to "false"
     *
     * @return announced value specified in the BusInterface annotation
     */
    String announced() default "false";

    /**
     * This interface's description language
     *
     * @return descriptionLangauge specified in the BusInterface annotation
     */
    String descriptionLanguage() default "";

    /**
     * This interface's description
     *
     * @return description specified in the BusInterface annotation
     */
    String description() default "";

    /**
     * Class name of an org.alljoyn.bus.Translator instance used
     * to translate this interface's descriptions
     *
     * @return descriptionTranslator specified in the BusInterface annotation
     */
    String descriptionTranslator() default "";
}
