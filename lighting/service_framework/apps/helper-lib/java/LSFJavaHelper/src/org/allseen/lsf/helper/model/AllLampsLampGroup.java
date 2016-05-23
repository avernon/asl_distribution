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
package org.allseen.lsf.helper.model;

import org.allseen.lsf.LampGroup;
import org.allseen.lsf.ResponseCode;
import org.allseen.lsf.helper.manager.LightingSystemManager;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class AllLampsLampGroup extends LampGroup {
    protected LightingSystemManager director;

    public AllLampsLampGroup(LightingSystemManager director) {
        super();
        this.director = director;
    }

    @Override
    public void setLamps(String[] lampIDs) {
        //TODO-FIX Log.w(SampleAppActivity.TAG, "Invalid attempt to set lamp members of the all-lamp lamp group");
    }

    @Override
    public String[] getLamps() {
        return director.getLampCollectionManager().getIDArray();
    }

    @Override
    public void setLampGroups(String[] lampGroupIDs) {
        //TODO-FIX Log.w(SampleAppActivity.TAG, "Invalid attempt to set group members of the all-lamp lamp group");
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
