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
package org.allseen.lsf.sdk.listener;

import org.allseen.lsf.sdk.TrackingID;

public class AnyCollectionListenerBase
    <   ITEM,
        LAMP extends ITEM,
        GROUP extends ITEM,
        PRESET extends ITEM,
        TRANSITIONEFFECT extends ITEM,
        PULSEEFFECT extends ITEM,
        SCENEELEMENT extends ITEM,
        SCENE extends ITEM,
        MASTERSCENE extends ITEM,
        CONTROLLER extends ITEM,
        ERROR>
    extends AllCollectionListenerBase<
        LAMP,
        GROUP,
        PRESET,
        TRANSITIONEFFECT,
        PULSEEFFECT,
        SCENEELEMENT,
        SCENE,
        MASTERSCENE,
        CONTROLLER,
        ERROR> {

    public void onAnyInitialized(TrackingID trackingId, ITEM item)  { }
    public void onAnyChanged(ITEM item)                             { }
    public void onAnyRemoved(ITEM item)                             { }
    public void onAnyError(ERROR error)                             { }

    @Override
    public void onLampInitialized(LAMP lamp) {
        onAnyInitialized(null, lamp);
    }

    @Override
    public void onLampChanged(LAMP lamp) {
        onAnyChanged(lamp);
    }

    @Override
    public void onLampRemoved(LAMP lamp) {
        onAnyRemoved(lamp);
    }

    @Override
    public void onLampError(ERROR error) {
        onAnyError(error);
    }

    @Override
    public void onGroupInitialized(TrackingID trackingId, GROUP group) {
        onAnyInitialized(trackingId, group);
    }

    @Override
    public void onGroupChanged(GROUP group) {
        onAnyChanged(group);
    }

    @Override
    public void onGroupRemoved(GROUP group) {
        onAnyRemoved(group);
    }

    @Override
    public void onGroupError(ERROR error) {
        onAnyError(error);
    }

    @Override
    public void onPresetInitialized(TrackingID trackingId, PRESET preset) {
        onAnyInitialized(trackingId, preset);
    }

    @Override
    public void onPresetChanged(PRESET preset) {
        onAnyChanged(preset);
    }

    @Override
    public void onPresetRemoved(PRESET preset) {
        onAnyRemoved(preset);
    }

    @Override
    public void onPresetError(ERROR error) {
        onAnyError(error);
    }

    @Override
    public void onTransitionEffectInitialized(TrackingID trackingId, TRANSITIONEFFECT effect) {
        onAnyInitialized(trackingId, effect);
    }

    @Override
    public void onTransitionEffectChanged(TRANSITIONEFFECT effect) {
        onAnyChanged(effect);
    }

    @Override
    public void onTransitionEffectRemoved(TRANSITIONEFFECT effect) {
        onAnyRemoved(effect);
    }

    @Override
    public void onTransitionEffectError(ERROR error) {
        onAnyError(error);
    }

    @Override
    public void onPulseEffectInitialized(TrackingID trackingId, PULSEEFFECT effect) {
        onAnyInitialized(trackingId, effect);
    }

    @Override
    public void onPulseEffectChanged(PULSEEFFECT effect) {
        onAnyChanged(effect);
    }

    @Override
    public void onPulseEffectRemoved(PULSEEFFECT effect) {
        onAnyRemoved(effect);
    }

    @Override
    public void onPulseEffectError(ERROR error) {
        onAnyError(error);
    }

    @Override
    public void onSceneElementInitialized(TrackingID trackingId, SCENEELEMENT element) {
        onAnyInitialized(trackingId, element);
    }

    @Override
    public void onSceneElementChanged(SCENEELEMENT element) {
        onAnyChanged(element);
    }

    @Override
    public void onSceneElementRemoved(SCENEELEMENT element) {
        onAnyRemoved(element);
    }

    @Override
    public void onSceneElementError(ERROR error) {
        onAnyError(error);
    }

    @Override
    public void onSceneInitialized(TrackingID trackingId, SCENE scene) {
        onAnyInitialized(trackingId, scene);
    }

    @Override
    public void onSceneChanged(SCENE scene) {
        onAnyChanged(scene);
    }

    @Override
    public void onSceneRemoved(SCENE scene) {
        onAnyRemoved(scene);
    }

    @Override
    public void onSceneError(ERROR error) {
        onAnyError(error);
    }

    @Override
    public void onMasterSceneInitialized(TrackingID trackingId, MASTERSCENE masterScene) {
        onAnyInitialized(trackingId, masterScene);
    }

    @Override
    public void onMasterSceneChanged(MASTERSCENE masterScene) {
        onAnyChanged(masterScene);
    }

    @Override
    public void onMasterSceneRemoved(MASTERSCENE masterScene) {
        onAnyRemoved(masterScene);
    }

    @Override
    public void onMasterSceneError(ERROR error) {
        onAnyError(error);
    }

    @Override
    public void onLeaderChange(CONTROLLER leader) {
        onAnyChanged(leader);
    }

    @Override
    public void onControllerErrors(ERROR error) {
        onAnyError(error);
    }
}
