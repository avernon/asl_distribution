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
package org.allseen.lsf.helper.manager;

import java.util.Iterator;

import org.allseen.lsf.helper.facade.Preset;
import org.allseen.lsf.helper.listener.LightingItemErrorEvent;
import org.allseen.lsf.helper.listener.PresetCollectionListener;
import org.allseen.lsf.helper.model.PresetDataModel;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class PresetCollectionManager extends LightingItemCollectionManager<Preset, PresetCollectionListener, PresetDataModel> {

    public PresetCollectionManager(LightingSystemManager director) {
        super(director);
    }

    public Preset addPreset(String presetID) {
        return addPreset(presetID, new Preset(presetID));
    }

    public Preset addPreset(String presetID, Preset preset) {
        return itemAdapters.put(presetID, preset);
    }

    public Preset getPreset(String presetID) {
        return getAdapter(presetID);
    }

    public Preset[] getPresets() {
        return getAdapters().toArray(new Preset[size()]);
    }

    public Iterator<Preset> getPresetIterator() {
        return getAdapters().iterator();
    }

    public Preset removePreset(String presetID) {
        return removeAdapter(presetID);
    }

    @Override
    protected void sendChangedEvent(PresetCollectionListener listener, Iterator<Preset> presets, int count) {
        listener.onPresetsChanged(presets, count);
    }

    @Override
    protected void sendRemovedEvent(PresetCollectionListener listener, Iterator<Preset> presets, int count) {
        listener.onPresetsRemoved(presets, count);
    }

    @Override
    protected void sendErrorEvent(PresetCollectionListener listener, LightingItemErrorEvent errorEvent) {
        listener.onPresetError(errorEvent);
    }

    @Override
    public PresetDataModel getModel(String presetID) {
        Preset preset = getAdapter(presetID);

        return preset != null ? preset.getPresetDataModel() : null;
    }
}
