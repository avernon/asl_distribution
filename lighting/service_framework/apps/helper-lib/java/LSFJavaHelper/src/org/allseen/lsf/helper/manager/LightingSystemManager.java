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

import org.allseen.lsf.LampGroupManager;
import org.allseen.lsf.LampManager;
import org.allseen.lsf.MasterSceneManager;
import org.allseen.lsf.NativeLibraryLoader;
import org.allseen.lsf.PresetManager;
import org.allseen.lsf.SceneManager;
import org.allseen.lsf.helper.callback.HelperControllerClientCallback;
import org.allseen.lsf.helper.callback.HelperGroupManagerCallback;
import org.allseen.lsf.helper.callback.HelperLampManagerCallback;
import org.allseen.lsf.helper.callback.HelperMasterSceneManagerCallback;
import org.allseen.lsf.helper.callback.HelperPresetManagerCallback;
import org.allseen.lsf.helper.callback.HelperSceneManagerCallback;
import org.allseen.lsf.helper.listener.ControllerAdapter;
import org.allseen.lsf.helper.model.ControllerDataModel;

import android.os.Handler;
import android.support.v4.app.FragmentManager;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class LightingSystemManager {
    @SuppressWarnings("unused")
    private static final NativeLibraryLoader LIBS = NativeLibraryLoader.LIBS;
    public static final String LANGUAGE = "en";

    public static final int POLLING_DELAY = 10000;
    public static final int LAMP_EXPIRATION = 15000;

    private final Handler handler;

    //TODO-FIX add get...() methods for these
    public final HelperControllerClientCallback controllerClientCB;
    public final HelperLampManagerCallback lampManagerCB;
    public final HelperGroupManagerCallback groupManagerCB;
    public final HelperPresetManagerCallback presetManagerCB;
    public final HelperSceneManagerCallback sceneManagerCB;
    public final HelperMasterSceneManagerCallback masterSceneManagerCB;

    private final LampCollectionManager lampCollectionManager;
    private final GroupCollectionManager groupCollectionManager;
    private final PresetCollectionManager presetCollectionManager;
    private final SceneCollectionManager sceneCollectionManager;
    private final MasterSceneCollectionManager masterSceneCollectionManager;
    private final ControllerManager controllerManager;

    public LightingSystemManager(Handler handler) {
        this.handler = handler;

        controllerClientCB = new HelperControllerClientCallback(this);
        lampManagerCB = new HelperLampManagerCallback(this);
        groupManagerCB = new HelperGroupManagerCallback(this);
        presetManagerCB = new HelperPresetManagerCallback(this);
        sceneManagerCB = new HelperSceneManagerCallback(this);
        masterSceneManagerCB = new HelperMasterSceneManagerCallback(this);

//TODO-IMPL        garbageCollector = new GarbageCollector(this, SampleAppActivity.POLLING_DELAY, SampleAppActivity.LAMP_EXPIRATION);

        lampCollectionManager = new LampCollectionManager(this);
        groupCollectionManager = new GroupCollectionManager(this);
        presetCollectionManager = new PresetCollectionManager(this);
        sceneCollectionManager = new SceneCollectionManager(this);
        masterSceneCollectionManager = new MasterSceneCollectionManager(this);
        controllerManager = new ControllerManager(this);
    }

    public void start(FragmentManager fragmentManager) {
        AboutManager aboutManager = new AboutManager(this);

        AllJoynManager.init(
                fragmentManager,
                controllerClientCB,
                lampManagerCB,
                groupManagerCB,
                presetManagerCB,
                sceneManagerCB,
                masterSceneManagerCB,
                aboutManager);

//TODO-IMPL            garbageCollector.start();
    }

    public void stop(FragmentManager fragmentManager) {
        AllJoynManager.destroy(fragmentManager);
    }

    public Handler getHandler() {
        return handler;
    }

    public LampCollectionManager getLampCollectionManager() {
        return lampCollectionManager;
    }

    public GroupCollectionManager getGroupCollectionManager() {
        return groupCollectionManager;
    }

    public PresetCollectionManager getPresetCollectionManager() {
        return presetCollectionManager;
    }

    public SceneCollectionManager getSceneCollectionManager() {
        return sceneCollectionManager;
    }

    public MasterSceneCollectionManager getMasterSceneCollectionManager() {
        return masterSceneCollectionManager;
    }

    public ControllerManager getControllerManager() {
        return controllerManager;
    }

    public LampManager getLampManager() {
        return AllJoynManager.lampManager;
    }

    public LampGroupManager getGroupManager() {
        return AllJoynManager.groupManager;
    }

    public PresetManager getPresetManager() {
        return AllJoynManager.presetManager;
    }

    public SceneManager getSceneManager() {
        return AllJoynManager.sceneManager;
    }

    public MasterSceneManager getMasterSceneManager() {
        return AllJoynManager.masterSceneManager;
    }

    public void postOnNextControllerConnection(final Runnable task, final int delay) {
        final ControllerManager controllerManager = getControllerManager();

        controllerManager.addListener(new ControllerAdapter() {
            @Override
            public void onLeaderModelChange(ControllerDataModel leaderModel) {
                if (leaderModel.connected) {
                    controllerManager.removeListener(this);
                    getHandler().postDelayed(task, delay);
                }
            }
        });
    }

    public boolean isLampExpired(String lampID) {
        //TODO-IMPL
        return false;
    }
}
