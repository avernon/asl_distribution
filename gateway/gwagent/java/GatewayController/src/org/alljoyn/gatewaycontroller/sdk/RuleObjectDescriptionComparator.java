/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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
 ******************************************************************************/

package org.alljoyn.gatewaycontroller.sdk;

import java.util.Comparator;

import org.alljoyn.gatewaycontroller.sdk.RuleObjectDescription.RuleObjectPath;

/**
 * Allows to compare {@link RuleObjectDescription} according to there
 * {@link RuleObjectPath}. The algorithm performs lexicographical comparison
 * of the object paths with the condition that for equal object paths the object
 * path that is not defined as prefix is less than the object path that is
 * prefix.
 */
class RuleObjectDescriptionComparator implements Comparator<RuleObjectDescription> {

    /**
     * @see java.util.Comparator#compare(java.lang.Object, java.lang.Object)
     */
    @Override
    public int compare(RuleObjectDescription lhs, RuleObjectDescription rhs) {

        String lhsOP = lhs.getObjectPath().getPath();
        String rhsOP = rhs.getObjectPath().getPath();

        int compRes = rhsOP.compareTo(lhsOP);
        if (compRes == 0) {

            if (lhs.getObjectPath().isPrefix()) {
                return 1;
            } else {
                return -1;
            }
        }

        return compRes;
    }

}
