/*
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
 */
package org.allseen.lsf.sampleapp;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

import org.allseen.lsf.LampGroup;

public class MemberNamesString {
    // Creates a details string, containing a list of all lamps and subgroups in a lamp group
    public static String format(SampleAppActivity activity, LampGroup members, MemberNamesOptions options, int maxCount, int noMembersID) {
        return format(activity, members, options, maxCount, noMembersID > 0 ? activity.getString(noMembersID) : "");
    }

    public static String format(SampleAppActivity activity, LampGroup members, MemberNamesOptions options, int maxCount, String noMembers) {
        List<String> groupNames = new ArrayList<String>();
        List<String> lampNames = new ArrayList<String>();

        for (String groupID : members.getLampGroups()) {
            GroupDataModel groupModel = activity.groupModels.get(groupID);
            groupNames.add(groupModel != null ? groupModel.getName() : String.format(activity.getString(R.string.member_group_not_found), groupID));
        }

        for (String lampID : members.getLamps()) {
            LampDataModel lampModel = activity.lampModels.get(lampID);
            lampNames.add(lampModel != null ? lampModel.getName() : String.format(activity.getString(R.string.member_lamp_not_found), lampID));
        }

        return format(activity, groupNames, lampNames, options, maxCount, noMembers);
    }

    public static String format(SampleAppActivity activity, List<String> names, MemberNamesOptions options, int maxCount, String noMembers) {
        return format(activity, names, new ArrayList<String>(), options, maxCount, noMembers);
    }

    public static String format(SampleAppActivity activity, List<String> primaryNames, List<String> secondaryNames, MemberNamesOptions options, int maxCount, String noMembers) {
        Collections.sort(primaryNames);
        Collections.sort(secondaryNames);

        String details = noMembers;
        int totalCount = primaryNames.size() + secondaryNames.size();

        if (totalCount > 0) {
            StringBuilder sb = new StringBuilder();
            int nextIndex = 0;

            nextIndex = format(sb, primaryNames.iterator(), nextIndex, totalCount, maxCount, options);
            nextIndex = format(sb, secondaryNames.iterator(), nextIndex, totalCount, maxCount, options);

            if (totalCount > maxCount) {
                sb.append(options.finalSeparator);
                sb.append(String.format(options.andOthersFormat, totalCount - maxCount));
            }

            details = sb.toString();
        }

        return details;
    }

    protected static int format(StringBuilder sb, Iterator<String> it, int nextIndex, int totalCount, int maxCount, MemberNamesOptions options) {
        boolean others = totalCount > maxCount;

        while (nextIndex < maxCount && it.hasNext()) {
            nextIndex++;

            if (nextIndex > 1) {
                if (nextIndex == maxCount && !others) {
                    sb.append(options.finalSeparator);
                } else if (nextIndex == totalCount) {
                    sb.append(options.finalSeparator);
                } else {
                    sb.append(options.innerSeparator);
                }
            }

            sb.append(options.openQuote);
            sb.append(it.next());
            sb.append(options.closeQuote);
        }

        return nextIndex;
    }
}
