/* Copyright (c) AllSeen Alliance. All rights reserved.
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
package org.allseen.lsf.sdk;

/**
 * This class encapsulates the AllJoyn about data of a Lamp in the Lighting System.
 * <p>
 * See the AllJoyn core documentation for more information on the AllJoyn about data.
 */
public class LampAbout extends org.allseen.lsf.sdk.model.LampAbout {

    /**
     * Specifies the string to use when an AllJoyn about field is indeterminate.
     *
     * @param dataNotFound String to use for indeterminate fields
     */
    public static void setDataNotFound(String dataNotFound) {
        if (dataNotFound != null) {
            org.allseen.lsf.sdk.model.LampAbout.dataNotFound = dataNotFound;
        }
    }

    /**
     * Constructs a LampAbout object using the provided LampAbout object.
     *
     * @param that A LampAbout object
     */
    public LampAbout(org.allseen.lsf.sdk.model.LampAbout that) {
        super(that);
    }
}
