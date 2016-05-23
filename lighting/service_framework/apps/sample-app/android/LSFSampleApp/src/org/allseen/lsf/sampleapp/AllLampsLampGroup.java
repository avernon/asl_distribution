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

import org.allseen.lsf.LampGroup;
import org.allseen.lsf.ResponseCode;

import android.util.Log;

public class AllLampsLampGroup extends LampGroup {
    protected SampleAppActivity activity;

    public AllLampsLampGroup(SampleAppActivity activity) {
        super();
        this.activity = activity;
    }

    @Override
    public void setLamps(String[] lampIDs) {
        Log.w(SampleAppActivity.TAG, "Invalid attempt to set lamp members of the all-lamp lamp group");
    }

    @Override
    public String[] getLamps() {
        return activity.lampModels.keySet().toArray(new String[activity.lampModels.size()]);
    }

    @Override
    public void setLampGroups(String[] lampGroupIDs) {
        Log.w(SampleAppActivity.TAG, "Invalid attempt to set group members of the all-lamp lamp group");
    }

    @Override
    public String[] getLampGroups() {
        return new String[] {};
    }

    @Override
    public ResponseCode isDependentLampGroup(String lampGroupID) {
        //TODO-FIX Not sure what this should be
        return ResponseCode.OK;
    }

}
