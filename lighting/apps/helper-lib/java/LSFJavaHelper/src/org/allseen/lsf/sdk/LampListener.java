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

import org.allseen.lsf.sdk.listener.LampCollectionListener;

/**
 * Provides an interface for developers to implement and receive all Lamp related events in the
 * Lighting system. Developers will be notified when lamps are found, modified, initialized, and
 * lost from the lighting controller. Lamps are considered initialized when all lamp data has
 * been received from the lighting controller.
 * <p>
 * <b>Note: Once implemented, the listener must be registered with the LightingDirector in order
 * to receive Lamp callbacks. See {@link LightingDirector#addLampListener(LampListener) addLampListener}
 * for more information.</b>
 */
public interface LampListener extends LampCollectionListener<Lamp, LightingItemErrorEvent> {

    /**
     * Triggered when all data has been received from the lighting controller for a
     * particular Lamp.
     * <p>
     * <b>Note: This callback will fire only once for each Lamp when all data has been received from
     * the lighting controller.</b>
     *
     * @param lamp Reference to Lamp
     */
    @Override
    public void onLampInitialized(Lamp lamp);

    /**
     * Triggered every time new data is received from the lighting controller for a
     * particular Lamp.
     *
     * @param lamp Reference to Lamp
     */
    @Override
    public void onLampChanged(Lamp lamp);

    /**
     * Triggered when a particular Lamp has been lost from the lighting controller.
     * <p>
     * <b>Note: This callback will fire only once for each Lamp when it is lost from
     * the lighting controller.</b>
     *
     * @param lamp Reference to Lamp
     */
    @Override
    public void onLampRemoved(Lamp lamp);

    /**
     * Triggered when an error occurs on a Lamp operation.
     *
     * @param error Reference to LightingItemErrorEvent
     */
    @Override
    public void onLampError(LightingItemErrorEvent error);
}
