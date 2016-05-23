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
package org.allseen.lsf.sdk;

import org.allseen.lsf.sdk.listener.PresetCollectionListener;

/**
 * Provides an interface for developers to implement and receive all preset related events in the
 * Lighting system. Developers will be notified when presets are added, modified, initialized, and
 * removed from the lighting controller. Presets are considered initialized when all preset data has
 * been received from the lighting controller.
 * <p>
 * <b>Note: Once implemented, the listener must be registered with the LightingDirector in order
 * to receive Preset callbacks. See {@link LightingDirector#addPresetListener(PresetListener) addPresetListener}
 * for more information.</b>
 */
public interface PresetListener extends PresetCollectionListener<Preset, LightingItemErrorEvent> {

    /**
     * Triggered when all data has been received from the lighting controller for a
     * particular Preset.
     * <p>
     * <b>Note: This callback will fire only once for each Preset when all data has been received from
     * the lighting controller.</b>
     * <p>
     * <b>Note: The tracking ID is only valid for presets created within your application.</b>
     *
     * @param trackingId Reference to TrackingID
     * @param preset Reference to Preset
     */
    @Override
    public void onPresetInitialized(TrackingID trackingId, Preset preset);

    /**
     * Triggered every time new data is received from the lighting controller for a
     * particular Preset.
     *
     * @param preset Reference to Preset
     */
    @Override
    public void onPresetChanged(Preset preset);

    /**
     * Triggered when a particular Preset has been deleted from the Lighting system.
     * <p>
     * <b>Note: This callback will fire only once for each Preset when it is deleted from
     * the Lighting system.</b>
     *
     * @param preset Reference to Preset
     */
    @Override
    public void onPresetRemoved(Preset preset);

    /**
     * Triggered when an error occurs on a Preset operation.
     *
     * @param error Reference to LightingItemErrorEvent
     */
    @Override
    public void onPresetError(LightingItemErrorEvent error);
}
