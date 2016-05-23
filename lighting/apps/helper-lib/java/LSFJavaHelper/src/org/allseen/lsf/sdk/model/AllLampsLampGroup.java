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
package org.allseen.lsf.sdk.model;

import org.allseen.lsf.LampGroup;
import org.allseen.lsf.sdk.ResponseCode;
import org.allseen.lsf.sdk.manager.LightingSystemManager;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class AllLampsLampGroup extends LampGroup {
    public static final AllLampsLampGroup instance = new AllLampsLampGroup();

    protected LightingSystemManager<?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?> manager;

    protected AllLampsLampGroup() {
        super();

        this.manager = null;
    }

    public void setLightingSystemManager(LightingSystemManager<?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?> manager) {
        this.manager = manager;
    }

    @Override
    public void setLamps(String[] lampIDs) {
        // Invalid attempt to set the lamp members of the all-lamp lamp group
        manager.getGroupCollectionManager().sendErrorEvent("AllLampsLampGroup.setLamps", ResponseCode.ERR_INVALID);
    }

    @Override
    public String[] getLamps() {
        return manager != null ? manager.getLampCollectionManager().getIDArray() : LightingItemUtil.NO_ITEM_IDS;
    }

    @Override
    public void setLampGroups(String[] lampGroupIDs) {
        // Invalid attempt to set the group members of the all-lamp lamp group
        manager.getGroupCollectionManager().sendErrorEvent("AllLampsLampGroup.setLampGroups", ResponseCode.ERR_INVALID);
    }

    @Override
    public String[] getLampGroups() {
        return new String[] {};
    }

    @Override
    public ResponseCode isDependentLampGroup(String lampGroupID) {
        // This lamp group does not contain any other group
        return ResponseCode.OK;
    }

}
