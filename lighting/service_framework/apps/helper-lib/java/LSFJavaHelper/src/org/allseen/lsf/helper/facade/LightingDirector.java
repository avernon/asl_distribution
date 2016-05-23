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
package org.allseen.lsf.helper.facade;

import org.alljoyn.bus.BusAttachment;
import org.allseen.lsf.helper.facade.Group;
import org.allseen.lsf.helper.facade.Lamp;
import org.allseen.lsf.helper.facade.Scene;
import org.allseen.lsf.helper.manager.AllJoynManager;
import org.allseen.lsf.helper.manager.LightingSystemManager;
import android.os.Handler;
import android.support.v4.app.FragmentManager;

/**
 * LightingDirector is the main class in the facade interface of the Lighting SDK.
 * It provides access to instances of other facade classes that represent active
 * components in the Lighting system.
 * <p>
 * Please see the LSFTutorial project for an example of how to use the LightingDirector
 * class.
 */
public class LightingDirector {
    private final LightingSystemManager lightingManager;

    /**
     * Construct a LightingDirector instance.
     *
     * Note that the start() method must be called at some point after construction when
     * you're ready to begin working with the Lighting system.
     *
     * @param handler A handler which receives tasks to run when certain events occur.
     */
    public LightingDirector(Handler handler) {
        super();
        lightingManager = new LightingSystemManager(handler);
    }

    /**
     * The version number of the interface provided by this class.
     *
     * @return The version number
     */
    public int getVersion() {
        return 1;
    }

    /**
     * Causes the LightingDirector to start interacting with the Lighting system.
     *
     * @param fragmentManager Currently needed for system initialization
     */
    public void start(FragmentManager fragmentManager) {
        lightingManager.start(fragmentManager);
    }

    /**
     * Causes the LightingDirector to start interacting with the Lighting system.
     *
     * @param fragmentManager Must be the same instance passed to start()
     */
    public void stop(FragmentManager fragmentManager) {
        lightingManager.stop(fragmentManager);
    }

    /**
     * Returns the AllJoyn BusAttachment object being used to connect to the Lighting system.
     *
     * The BusAttachment will be null until some time after the call to start().
     *
     * @return The BusAttachment object
     */
    public BusAttachment getBusAttachment() {
        return AllJoynManager.bus;
    }

    /**
     * Returns a snapshot of the active Lamps in the Lighting system.
     *
     * The contents of this array may change in subsequent calls to this method as new lamps
     * are discovered or existing lamps are determined to be offline. This array may be empty.
     *
     * @return An array of active Lamps
     */
    public Lamp[] getLamps() {
        return lightingManager.getLampCollectionManager().getLamps();
    }

    /**
     * Returns a snapshot of the active Group definitions in the Lighting system.
     *
     * The contents of this array may change in subsequent calls to this method as new groups
     * are created or existing groups are deleted. This array may be empty.
     *
     * @return An array of active Groups
     */
    public Group[] getGroups() {
        return lightingManager.getGroupCollectionManager().getGroups();
    }

    /**
     * Returns a snapshot of the active Scene definitions in the Lighting system.
     *
     * The contents of this array may change in subsequent calls to this method as new scenes
     * are created or existing scenes are deleted. This array may be empty.
     *
     * @return An array of active Scenes
     */
    public Scene[] getScenes() {
        return lightingManager.getSceneCollectionManager().getScenes();
    }

    /**
     * Specifies a task to run once a connection to a lighting system has been established.
     *
     * This allows clients of the LightingDirector to be notified once a connection has been
     * established.
     *
     * @param task The task to run on connection
     * @param delay Specifies a delay between when a connection occurs and when the task should be run
     */
    public void postOnNextControllerConnection(Runnable task, int delay) {
        lightingManager.postOnNextControllerConnection(task, delay);
    }

//TODO Untested -- temporarily hidden until after the hackathon
//    public void addLampCollectionListener(LampCollectionListener listener) {
//        getLampCollectionManager().addListener(listener);
//    }
//
//    public LampCollectionManager getLampCollectionManager() {
//        return lightingManager.getLampCollectionManager();
//    }
//
//    public void addGroupCollectionListener(GroupCollectionListener listener) {
//        getGroupCollectionManager().addListener(listener);
//    }
//
//    public GroupCollectionManager getGroupCollectionManager() {
//        return lightingManager.getGroupCollectionManager();
//    }
//
//    public Preset[] getPresets() {
//        return getPresetCollectionManager().getPresets();
//    }
//
//    public void addPresetCollectionListener(PresetCollectionListener listener) {
//        getPresetCollectionManager().addListener(listener);
//    }
//
//    public PresetCollectionManager getPresetCollectionManager() {
//        return lightingManager.getPresetCollectionManager();
//    }
//
//    public void addSceneCollectionListener(SceneCollectionListener listener) {
//        getSceneCollectionManager().addListener(listener);
//    }
//
//    public SceneCollectionManager getSceneCollectionManager() {
//        return lightingManager.getSceneCollectionManager();
//    }
//
//    public MasterScene[] getMasterScenes() {
//        return getMasterSceneCollectionManager().getMasterScenes();
//    }
//
//    public void addMasterSceneCollectionListener(MasterSceneCollectionListener listener) {
//        getMasterSceneCollectionManager().addListener(listener);
//    }
//
//    public MasterSceneCollectionManager getMasterSceneCollectionManager() {
//        return lightingManager.getMasterSceneCollectionManager();
//    }
//
//    public void addControllerListener(ControllerListener listener) {
//        getControllerManager().addListener(listener);
//    }
//
//    public ControllerManager getControllerManager() {
//        return lightingManager.getControllerManager();
//    }
//
//    public LampManager getLampManager() {
//        return AllJoynManager.lampManager;
//    }
//
//    public SceneManager getSceneManager() {
//        return AllJoynManager.sceneManager;
//    }
//
//    public boolean isLampExpired(String lampID) {
//        //TODO-IMPL
//        return false;
//    }
}
