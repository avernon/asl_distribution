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

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class AllCollectionListenerBase<LAMP, GROUP, PRESET, TRANSITIONEFFECT, PULSEEFFECT, SCENEELEMENT, SCENE, MASTERSCENE, CONTROLLER, ERROR>
    implements AllCollectionListener<LAMP, GROUP, PRESET, TRANSITIONEFFECT, PULSEEFFECT, SCENEELEMENT, SCENE, MASTERSCENE, CONTROLLER, ERROR> {

    @Override
    public void onLampInitialized(LAMP lamp)                                                        { }

    @Override
    public void onLampChanged(LAMP lamp)                                                            { }

    @Override
    public void onLampRemoved(LAMP lamp)                                                            { }

    @Override
    public void onLampError(ERROR error)                                                            { }

    @Override
    public void onGroupInitialized(TrackingID trackingId, GROUP group)                              { }

    @Override
    public void onGroupChanged(GROUP group)                                                         { }

    @Override
    public void onGroupRemoved(GROUP group)                                                         { }

    @Override
    public void onGroupError(ERROR error)                                                           { }

    @Override
    public void onPresetInitialized(TrackingID trackingId, PRESET preset)                           { }

    @Override
    public void onPresetChanged(PRESET preset)                                                      { }

    @Override
    public void onPresetRemoved(PRESET preset)                                                      { }

    @Override
    public void onPresetError(ERROR error)                                                          { }

    @Override
    public void onTransitionEffectInitialized(TrackingID trackingId, TRANSITIONEFFECT effect)       { }

    @Override
    public void onTransitionEffectChanged(TRANSITIONEFFECT effect)                                  { }

    @Override
    public void onTransitionEffectRemoved(TRANSITIONEFFECT effect)                                  { }

    @Override
    public void onTransitionEffectError(ERROR error)                                                { }

    @Override
    public void onPulseEffectInitialized(TrackingID trackingId, PULSEEFFECT effect)                 { }

    @Override
    public void onPulseEffectChanged(PULSEEFFECT effect)                                            { }

    @Override
    public void onPulseEffectRemoved(PULSEEFFECT effect)                                            { }

    @Override
    public void onPulseEffectError(ERROR error)                                                     { }

    @Override
    public void onSceneElementInitialized(TrackingID trackingId, SCENEELEMENT element)              { }

    @Override
    public void onSceneElementChanged(SCENEELEMENT element)                                         { }

    @Override
    public void onSceneElementRemoved(SCENEELEMENT element)                                         { }

    @Override
    public void onSceneElementError(ERROR error)                                                    { }

    @Override
    public void onSceneInitialized(TrackingID trackingId, SCENE scene)                              { }

    @Override
    public void onSceneChanged(SCENE scene)                                                         { }

    @Override
    public void onSceneRemoved(SCENE scene)                                                         { }

    @Override
    public void onSceneError(ERROR error)                                                           { }

    @Override
    public void onMasterSceneInitialized(TrackingID trackingId, MASTERSCENE masterScene)            { }

    @Override
    public void onMasterSceneChanged(MASTERSCENE masterScene)                                       { }

    @Override
    public void onMasterSceneRemoved(MASTERSCENE masterScene)                                       { }

    @Override
    public void onMasterSceneError(ERROR error)                                                     { }

    @Override
    public void onLeaderChange(CONTROLLER leader)                                                   { }

    @Override
    public void onControllerErrors(ERROR errorEvent)                                                { }
}
