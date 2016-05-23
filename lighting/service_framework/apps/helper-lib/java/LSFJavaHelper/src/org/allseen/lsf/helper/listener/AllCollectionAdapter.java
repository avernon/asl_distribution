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
package org.allseen.lsf.helper.listener;

import java.util.Iterator;

import org.allseen.lsf.helper.facade.Group;
import org.allseen.lsf.helper.facade.Lamp;
import org.allseen.lsf.helper.facade.MasterScene;
import org.allseen.lsf.helper.facade.Preset;
import org.allseen.lsf.helper.facade.Scene;
import org.allseen.lsf.helper.model.ControllerDataModel;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class AllCollectionAdapter implements AllCollectionListener {

    @Override
    public void onLampsChanged(Iterator<Lamp> lamps, int count)                         { }

    @Override
    public void onLampsRemoved(Iterator<Lamp> lamps, int count)                         { }

    @Override
    public void onLampError(LightingItemErrorEvent error)                               { }

    @Override
    public void onGroupsChanged(Iterator<Group> groups, int count)                      { }

    @Override
    public void onGroupsRemoved(Iterator<Group> groups, int count)                      { }

    @Override
    public void onGroupError(LightingItemErrorEvent error)                              { }

    @Override
    public void onPresetsChanged(Iterator<Preset> presets, int count)                   { }

    @Override
    public void onPresetsRemoved(Iterator<Preset> presets, int count)                   { }

    @Override
    public void onPresetError(LightingItemErrorEvent error)                             { }

    @Override
    public void onScenesChanged(Iterator<Scene> scenes, int count)                      { }

    @Override
    public void onScenesRemoved(Iterator<Scene> scenes, int count)                      { }

    @Override
    public void onSceneError(LightingItemErrorEvent error)                              { }

    @Override
    public void onMasterScenesChanged(Iterator<MasterScene> masterScenes, int count)    { }

    @Override
    public void onMasterScenesRemoved(Iterator<MasterScene> masterScenes, int count)    { }

    @Override
    public void onMasterSceneError(LightingItemErrorEvent error)                        { }

    @Override
    public void onLeaderModelChange(ControllerDataModel leadModel) { }

    @Override
    public void onControllerErrors(ControllerErrorEvent errorEvent) { }

    @Override
    public void onWifiConnected(WifiEvent wifiEvent) { }

    @Override
    public void onWifiDisconnected(WifiEvent wifiEvent) { }
}
