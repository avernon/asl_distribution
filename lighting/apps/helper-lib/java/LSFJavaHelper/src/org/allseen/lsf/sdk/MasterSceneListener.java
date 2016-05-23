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

import org.allseen.lsf.sdk.listener.MasterSceneCollectionListener;

/**
 * Provides an interface for developers to implement and receive all master scene related events in the
 * Lighting system. Developers will be notified when master scenes are added, modified, initialized, and
 * deleted from the lighting controller. Master scenes are considered initialized when all master scene
 * data has been received from the lighting controller.
 * <p>
 * <b>Note: Once implemented, the listener must be registered with the LightingDirector in order
 * to receive MasterScene callbacks. See {@link LightingDirector#addMasterSceneListener(MasterSceneListener) addMasterSceneListener}
 * for more information.</b>
 */
public interface MasterSceneListener extends MasterSceneCollectionListener<MasterScene, LightingItemErrorEvent> {

    /**
     * Triggered when all data has been received from the lighting controller for a
     * particular MasterScene.
     * <p>
     * <b>Note: This callback will fire only once for each MasterScene when all data has been received from
     * the lighting controller.</b>
     * <p>
     * <b>Note: The tracking ID is only valid for master scenes created within your application.</b>
     *
     * @param trackingId Reference to TrackingID
     * @param masterScene Reference to MasterScene
     */
    @Override
    public void onMasterSceneInitialized(TrackingID trackingId, MasterScene masterScene);

    /**
     * Triggered every time new data is received from the lighting controller for a
     * particular MasterScene.
     *
     * @param masterScene Reference to MasterScene
     */
    @Override
    public void onMasterSceneChanged(MasterScene masterScene);

    /**
     * Triggered when a particular MasterScene has been deleted from the lighting controller.
     * <p>
     * <b>Note: This callback will fire only once for each MasterScene when it is deleted from
     * the lighting controller.</b>
     *
     * @param masterScene Reference to MasterScene
     */
    @Override
    public void onMasterSceneRemoved(MasterScene masterScene);

    /**
     * Triggered when an error occurs on a MasterScene operation.
     *
     * @param error Reference to LightingItemErrorEvent
     */
    @Override
    public void onMasterSceneError(LightingItemErrorEvent error);
}
