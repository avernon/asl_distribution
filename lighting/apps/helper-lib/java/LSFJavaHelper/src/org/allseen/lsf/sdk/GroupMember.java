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
package org.allseen.lsf.sdk;

import java.util.Collection;
import java.util.HashSet;
import java.util.Set;

import org.allseen.lsf.LampGroup;
import org.allseen.lsf.sdk.model.LightingItemUtil;

/**
 * Abstract base class for Lighting items that can be included in a Lighting Group.
 */
public abstract class GroupMember extends MutableColorItem {

    /**
     * Returns a boolean indicating if the GroupMember is a Lamp.
     *
     * @return boolean Returns a default value of false
     */
    public boolean isLamp() {
        return false;
    }

    /**
     * Returns a boolean indicating if the GroupMember is a Group.
     *
     * @return boolean Returns a default value of false
     */
    public boolean isGroup() {
        return false;
    }

    /**
     * Applies the provided Preset to the current GroupMember.
     *
     * @param preset Preset to apply to the current GroupMember
     */
    public abstract void applyPreset(Preset preset);

    /**
     * Applies the provided Effect to the current GroupMember.
     *
     * @param effect Effect to apply to the current GroupMember
     */
    public abstract void applyEffect(Effect effect);

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected abstract void addTo(Collection<String> lampIDs, Collection<String> groupIDs);

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected static LampGroup createLampGroup(GroupMember[] groupMembers) {
        Set<String> lampIDs = new HashSet<String>();
        Set<String> groupIDs = new HashSet<String>();

        if (groupMembers != null) {
            for (GroupMember member : groupMembers) {
                member.addTo(lampIDs, groupIDs);
            }
        }

        return LightingItemUtil.createLampGroup(
                lampIDs.toArray(new String[lampIDs.size()]),
                groupIDs.toArray(new String[groupIDs.size()]));
    }
}
