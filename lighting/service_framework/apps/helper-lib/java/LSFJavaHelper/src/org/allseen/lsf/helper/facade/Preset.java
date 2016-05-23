/* Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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
package org.allseen.lsf.helper.facade;

import org.allseen.lsf.helper.manager.AllJoynManager;
import org.allseen.lsf.helper.model.LightingItemDataModel;
import org.allseen.lsf.helper.model.PresetDataModel;

/**
 * A Preset object represents a predefined color state in a lighting system.
 * <p>
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class Preset extends LightingItem {

    protected PresetDataModel presetModel;

    public Preset(String presetID) {
        this(presetID, null);
    }

    public Preset(String presetID, String presetName) {
        super();

        presetModel = new PresetDataModel(presetID, presetName);
    }

    public void applyTo(Lamp lamp) {
        applyToLamp(lamp.getLampDataModel().id);
    }

    public void applyTo(Group group) {
        applyToGroup(group.getGroupDataModel().id);
    }

    protected void applyToLamp(String lampID) {
        AllJoynManager.lampManager.transitionLampStateToPreset(lampID, presetModel.id, 0);
    }

    protected void applyToGroup(String groupID) {
        AllJoynManager.groupManager.transitionLampGroupStateToPreset(groupID, presetModel.id, 0);
    }

    @Override
    protected LightingItemDataModel getItemDataModel() {
        return getPresetDataModel();
    }

    public PresetDataModel getPresetDataModel() {
        return presetModel;
    }
}
