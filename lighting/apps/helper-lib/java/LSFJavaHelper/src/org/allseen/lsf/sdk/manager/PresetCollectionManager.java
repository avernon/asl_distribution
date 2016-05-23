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
package org.allseen.lsf.sdk.manager;

import java.util.Collection;
import java.util.Iterator;

import org.allseen.lsf.sdk.TrackingID;
import org.allseen.lsf.sdk.factory.PresetFactory;
import org.allseen.lsf.sdk.listener.PresetCollectionListener;
import org.allseen.lsf.sdk.model.LightingItemFilter;
import org.allseen.lsf.sdk.model.PresetDataModel;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class PresetCollectionManager<PRESET, ERROR> extends LightingItemCollectionManager<PRESET, PresetCollectionListener<? super PRESET, ? super ERROR>, PresetDataModel, ERROR> {

    private final PresetFactory<PRESET, ERROR> factory;

    public PresetCollectionManager(LightingSystemManager<?, ?, PRESET, ?, ?, ?, ?, ?, ?, ?, ?> manager, PresetFactory<PRESET, ERROR> factory) {
        super(manager, factory);

        this.factory = factory;
    }

    public PRESET addPreset(String presetID) {
        return addPreset(presetID, factory.createPreset(presetID));
    }

    public PRESET addPreset(String presetID, PRESET preset) {
        return itemAdapters.put(presetID, preset);
    }

    public PRESET getPreset(String presetID) {
        return getAdapter(presetID);
    }

    public PRESET[] getPresets() {
        return getAdapters().toArray(factory.createPresets(size()));
    }

    public PRESET[] getPresets(LightingItemFilter<PRESET> filter) {
        Collection<PRESET> filteredPresets = getPresetsCollection(filter);
        return filteredPresets.toArray(factory.createPresets(filteredPresets.size()));
    }

    public Collection<PRESET> getPresetsCollection(LightingItemFilter<PRESET> filter) {
        return getAdapters(filter);
    }

    public Iterator<PRESET> getPresetIterator() {
        return getAdapters().iterator();
    }

    public Collection<PRESET> removePresets() {
        return removeAllAdapters();
    }

    public PRESET removePreset(String presetID) {
        return removeAdapter(presetID);
    }

    @Override
    protected void sendInitializedEvent(PresetCollectionListener<? super PRESET, ? super ERROR> listener, PRESET preset, TrackingID trackingID) {
        listener.onPresetInitialized(trackingID, preset);
    }

    @Override
    protected void sendChangedEvent(PresetCollectionListener<? super PRESET, ? super ERROR> listener, PRESET preset) {
        listener.onPresetChanged(preset);
    }

    @Override
    protected void sendRemovedEvent(PresetCollectionListener<? super PRESET, ? super ERROR> listener, PRESET preset) {
        listener.onPresetRemoved(preset);
    }

    @Override
    protected void sendErrorEvent(PresetCollectionListener<? super PRESET, ? super ERROR> listener, ERROR error) {
        listener.onPresetError(error);
    }

    @Override
    public PresetDataModel getModel(String presetID) {
        return getModel(getAdapter(presetID));
    }

    @Override
    public PresetDataModel getModel(PRESET preset) {
        return preset != null ? factory.findPresetDataModel(preset) : null;
    }
}
