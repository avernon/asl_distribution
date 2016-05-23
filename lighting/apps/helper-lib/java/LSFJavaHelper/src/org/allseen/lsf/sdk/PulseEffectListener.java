/*
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

import org.allseen.lsf.sdk.listener.PulseEffectCollectionListener;

/**
 * Provides an interface for developers to implement and receive all pulse effect related events in the
 * Lighting system. Developers will be notified when pulse effects are added, modified, initialized, and
 * deleted from the lighting controller. Pulse effects are considered initialized when all pulse effect data has
 * been received from the lighting controller.
 * <p>
 * <b>Note: Once implemented, the listener must be registered with the LightingDirector in order
 * to receive PulseEffect callbacks. See {@link LightingDirector#addPulseEffectListener(PulseEffectListener) addPulseEffectListener}
 * for more information.</b>
 */
public interface PulseEffectListener extends PulseEffectCollectionListener<PulseEffect, LightingItemErrorEvent> {

    /**
     * Triggered when all data has been received from the lighting controller for a
     * particular PulseEffect.
     * <p>
     * <b>Note: This callback will fire only once for each PulseEffect when all data has been received from
     * the lighting controller.</b>
     * <p>
     * <b>Note: The tracking ID is only valid for pulse effects created within your application.</b>
     *
     * @param trackingId Reference to TrackingID
     * @param effect Reference to PulseEffect
     */
    @Override
    public void onPulseEffectInitialized(TrackingID trackingId, PulseEffect effect);

    /**
     * Triggered every time new data is received from the lighting controller for a
     * particular PulseEffect.
     *
     * @param effect Reference to PulseEffect
     */
    @Override
    public void onPulseEffectChanged(PulseEffect effect);

    /**
     * Triggered when a particular PulseEffect has been deleted from the lighting controller.
     * <p>
     * <b>Note: This callback will fire only once for each PulseEffect when it is deleted from
     * the lighting controller.</b>
     *
     * @param effect Reference to PulseEffect
     */
    @Override
    public void onPulseEffectRemoved(PulseEffect effect);

    /**
     * Triggered when an error occurs on a PulseEffect operation.
     *
     * @param error Reference to LightingItemErrorEvent
     */
    @Override
    public void onPulseEffectError(LightingItemErrorEvent error);
}
