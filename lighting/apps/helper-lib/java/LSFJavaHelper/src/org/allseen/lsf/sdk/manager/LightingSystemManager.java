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

import org.alljoyn.bus.BusAttachment;
import org.allseen.lsf.LampGroupManager;
import org.allseen.lsf.LampManager;
import org.allseen.lsf.MasterSceneManager;
import org.allseen.lsf.NativeLibraryLoader;
import org.allseen.lsf.PresetManager;
import org.allseen.lsf.PulseEffectManager;
import org.allseen.lsf.SceneElementManager;
import org.allseen.lsf.SceneManager;
import org.allseen.lsf.TransitionEffectManager;
import org.allseen.lsf.sdk.callback.HelperControllerClientCallback;
import org.allseen.lsf.sdk.callback.HelperControllerServiceManagerCallback;
import org.allseen.lsf.sdk.callback.HelperGroupManagerCallback;
import org.allseen.lsf.sdk.callback.HelperLampManagerCallback;
import org.allseen.lsf.sdk.callback.HelperMasterSceneManagerCallback;
import org.allseen.lsf.sdk.callback.HelperPresetManagerCallback;
import org.allseen.lsf.sdk.callback.HelperPulseEffectManagerCallback;
import org.allseen.lsf.sdk.callback.HelperSceneElementManagerCallback;
import org.allseen.lsf.sdk.callback.HelperSceneManagerCallback;
import org.allseen.lsf.sdk.callback.HelperTransitionEffectManagerCallback;
import org.allseen.lsf.sdk.factory.AllLightingItemsFactory;
import org.allseen.lsf.sdk.listener.AllJoynListener;
import org.allseen.lsf.sdk.listener.ControllerCollectionListenerBase;
import org.allseen.lsf.sdk.listener.LampCollectionListenerBase;
import org.allseen.lsf.sdk.listener.NextControllerConnectionListener;
import org.allseen.lsf.sdk.model.AllLampsDataModel;
import org.allseen.lsf.sdk.model.AllLampsLampGroup;
import org.allseen.lsf.sdk.model.ControllerDataModel;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class LightingSystemManager
    <   LAMP,
        GROUP,
        PRESET,
        TRANSITIONEFFECT,
        PULSEEFFECT,
        SCENEELEMENT,
        SCENEV1,
        SCENEV2,
        MASTERSCENE,
        CONTROLLER,
        ERROR> {

    @SuppressWarnings("unused")
    private static final NativeLibraryLoader LIBS = NativeLibraryLoader.LIBS;
    public static final String LANGUAGE = "en";

    public static final int POLLING_DELAY = 10000;
    public static final int LAMP_EXPIRATION = 15000;

    private LightingSystemQueue queue;
    private LightingSystemQueue helperQueue;

    //TODO-FIX add get...() methods for these
    public final HelperControllerClientCallback<CONTROLLER> controllerClientCB;
    public final HelperControllerServiceManagerCallback controllerServiceManagerCB;
    public final HelperLampManagerCallback<LAMP> lampManagerCB;
    public final HelperGroupManagerCallback<GROUP> groupManagerCB;
    public final HelperPresetManagerCallback<PRESET> presetManagerCB;
    public final HelperTransitionEffectManagerCallback<TRANSITIONEFFECT> transitionEffectManagerCB;
    public final HelperPulseEffectManagerCallback<PULSEEFFECT> pulseEffectManagerCB;
    public final HelperSceneElementManagerCallback<SCENEELEMENT> sceneElementManagerCB;
    public final HelperSceneManagerCallback<SCENEV1, SCENEV2> sceneManagerCB;
    public final HelperMasterSceneManagerCallback<MASTERSCENE> masterSceneManagerCB;

    private final LampCollectionManager<LAMP, ERROR> lampCollectionManager;
    private final GroupCollectionManager<GROUP, ERROR> groupCollectionManager;
    private final PresetCollectionManager<PRESET, ERROR> presetCollectionManager;
    private final TransitionEffectCollectionManager<TRANSITIONEFFECT, ERROR> transitionEffectCollectionManager;
    private final PulseEffectCollectionManager<PULSEEFFECT, ERROR> pulseEffectCollectionManager;
    private final SceneElementCollectionManager<SCENEELEMENT, ERROR> sceneElementCollectionManager;
    private final SceneCollectionManagerV1<SCENEV1, ERROR> sceneCollectionManagerV1;
    private final SceneCollectionManagerV2<SCENEV2, ERROR> sceneCollectionManager;
    private final MasterSceneCollectionManager<MASTERSCENE, ERROR> masterSceneCollectionManager;
    private final ControllerCollectionManager<CONTROLLER, ERROR> controllerCollectionManager;
    private boolean isAllLampsGroupCreated = false;

    public LightingSystemManager(final AllLightingItemsFactory<LAMP, GROUP, PRESET, TRANSITIONEFFECT, PULSEEFFECT, SCENEELEMENT, SCENEV1, SCENEV2, MASTERSCENE, CONTROLLER, ERROR> factory) {
        AllLampsLampGroup.instance.setLightingSystemManager(this);

        controllerClientCB = new HelperControllerClientCallback<CONTROLLER>(this);
        controllerServiceManagerCB = new HelperControllerServiceManagerCallback(this);
        lampManagerCB = new HelperLampManagerCallback<LAMP>(this);
        groupManagerCB = new HelperGroupManagerCallback<GROUP>(this);
        presetManagerCB = new HelperPresetManagerCallback<PRESET>(this);
        transitionEffectManagerCB = new HelperTransitionEffectManagerCallback<TRANSITIONEFFECT>(this);
        pulseEffectManagerCB = new HelperPulseEffectManagerCallback<PULSEEFFECT>(this);
        sceneElementManagerCB = new HelperSceneElementManagerCallback<SCENEELEMENT>(this);
        masterSceneManagerCB = new HelperMasterSceneManagerCallback<MASTERSCENE>(this);
        sceneManagerCB = new HelperSceneManagerCallback<SCENEV1, SCENEV2>(this);

        lampCollectionManager = new LampCollectionManager<LAMP, ERROR>(this, factory);
        groupCollectionManager = new GroupCollectionManager<GROUP, ERROR>(this, factory);
        presetCollectionManager = new PresetCollectionManager<PRESET, ERROR>(this, factory);
        transitionEffectCollectionManager = new TransitionEffectCollectionManager<TRANSITIONEFFECT, ERROR>(this, factory);
        pulseEffectCollectionManager = new PulseEffectCollectionManager<PULSEEFFECT, ERROR>(this, factory);
        sceneElementCollectionManager = new SceneElementCollectionManager<SCENEELEMENT, ERROR>(this, factory);
        sceneCollectionManagerV1 = new SceneCollectionManagerV1<SCENEV1, ERROR>(this, factory);
        sceneCollectionManager = new SceneCollectionManagerV2<SCENEV2, ERROR>(this, factory);
        masterSceneCollectionManager = new MasterSceneCollectionManager<MASTERSCENE, ERROR>(this, factory);
        controllerCollectionManager = new ControllerCollectionManager<CONTROLLER, ERROR>(this, factory);

        lampCollectionManager.addListener(new LampCollectionListenerBase<LAMP, ERROR>() {
            @Override
            public void onLampChanged(final LAMP lamp) {
                groupManagerCB.postUpdateDependentLampGroups(factory.findLampDataModel(lamp).id);

                if (!isAllLampsGroupCreated) {
                    isAllLampsGroupCreated = true;
                    groupManagerCB.postProcessLampGroupID(AllLampsDataModel.ALL_LAMPS_GROUP_ID, true, true);
                }
            }

            @Override
            public void onLampRemoved(final LAMP lamp) {
                if (lampCollectionManager.getLamps().length == 0) {
                    groupManagerCB.lampGroupsDeletedCB(new String [] {AllLampsDataModel.ALL_LAMPS_GROUP_ID});
                    isAllLampsGroupCreated = false;
                }
            }
        });

        controllerCollectionManager.addListener(new ControllerCollectionListenerBase<CONTROLLER, ERROR>() {
            @Override
            public void onLeaderChange(CONTROLLER leader) {
                ControllerDataModel leaderModel = factory.findControllerDataModel(leader);

                if (!leaderModel.connected) {
                    clearModels();
                }
            }
        });
    }

    public void init(String applicationName, LightingSystemQueue queue, AllJoynListener alljoynListener) {
        setQueue(queue);

        AllJoynManager.init(
            applicationName,
            controllerClientCB,
            controllerServiceManagerCB,
            lampManagerCB,
            groupManagerCB,
            presetManagerCB,
            transitionEffectManagerCB,
            pulseEffectManagerCB,
            sceneElementManagerCB,
            sceneManagerCB,
            masterSceneManagerCB,
            new AboutManager(this),
            alljoynListener);
    }

    public void init(BusAttachment busAttachment, LightingSystemQueue queue, AllJoynListener alljoynListener) {
        setQueue(queue);

        AllJoynManager.init(
            busAttachment,
            controllerClientCB,
            controllerServiceManagerCB,
            lampManagerCB,
            groupManagerCB,
            presetManagerCB,
            transitionEffectManagerCB,
            pulseEffectManagerCB,
            sceneElementManagerCB,
            sceneManagerCB,
            masterSceneManagerCB,
            new AboutManager(this),
            alljoynListener);
    }

    public void start() {
        clearModels();

        helperQueue = new DefaultLightingSystemQueue();

        AllJoynManager.start(queue);
    }

    public void stop() {
        clearModels();

        if (helperQueue != null) {
            helperQueue.stop();
            helperQueue = null;
        }

        AllJoynManager.stop(queue);
    }

    public void destroy() {
        stop();

        AllJoynManager.destroy(queue);

        queue.post(new Runnable() {
            @Override
            public void run() {
                queue.stop();
            }
        });
    }

    protected void setQueue(LightingSystemQueue queue) {
        if (queue == null) {
            queue = new DefaultLightingSystemQueue();
        }

        if (this.queue != null) {
            this.queue.stop();
        }

        this.queue = queue;
    }

    public LightingSystemQueue getQueue() {
        return queue;
    }

    public LightingSystemQueue getHelperQueue() {
        return helperQueue;
    }

    public LampCollectionManager<LAMP, ERROR> getLampCollectionManager() {
        return lampCollectionManager;
    }

    public GroupCollectionManager<GROUP, ERROR> getGroupCollectionManager() {
        return groupCollectionManager;
    }

    public PresetCollectionManager<PRESET, ERROR> getPresetCollectionManager() {
        return presetCollectionManager;
    }

    public TransitionEffectCollectionManager<TRANSITIONEFFECT, ERROR> getTransitionEffectCollectionManager() {
        return transitionEffectCollectionManager;
    }

    public PulseEffectCollectionManager<PULSEEFFECT, ERROR> getPulseEffectCollectionManager() {
        return pulseEffectCollectionManager;
    }

    public SceneElementCollectionManager<SCENEELEMENT, ERROR> getSceneElementCollectionManager() {
        return sceneElementCollectionManager;
    }

    public SceneCollectionManagerV1<SCENEV1, ERROR> getSceneCollectionManagerV1() {
        return sceneCollectionManagerV1;
    }

    public SceneCollectionManagerV2<SCENEV2, ERROR> getSceneCollectionManagerV2() {
        return sceneCollectionManager;
    }

    public MasterSceneCollectionManager<MASTERSCENE, ERROR> getMasterSceneCollectionManager() {
        return masterSceneCollectionManager;
    }

    public ControllerCollectionManager<CONTROLLER, ERROR> getControllerCollectionManager() {
        return controllerCollectionManager;
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

    public TransitionEffectManager getTransitionEffectManager() {
        return AllJoynManager.transitionEffectManager;
    }

    public PulseEffectManager getPulseEffectManager() {
        return AllJoynManager.pulseEffectManager;
    }

    public SceneElementManager getSceneElementManager() {
        return AllJoynManager.sceneElementManager;
    }

    public SceneManager getSceneManager() {
        return AllJoynManager.sceneManager;
    }

    public MasterSceneManager getMasterSceneManager() {
        return AllJoynManager.masterSceneManager;
    }

    public void postOnNextControllerConnection(final NextControllerConnectionListener listener, final int delay) {
        postOnNextControllerConnection(new Runnable() {
            @Override
            public void run() {
                listener.onControllerConnected();
            }}, delay);
    }

    public void postOnNextControllerConnection(final Runnable task, final int delay) {
        final ControllerCollectionManager<CONTROLLER, ERROR> controllerManager = getControllerCollectionManager();

        controllerManager.addListener(new ControllerCollectionListenerBase<CONTROLLER, ERROR>() {
            @Override
            public void onLeaderChange(CONTROLLER leader) {
                ControllerDataModel leaderModel = controllerManager.getLeaderModel();

                if (leaderModel.connected) {
                    controllerManager.removeListener(this);
                    getQueue().postDelayed(task, delay);
                }
            }
        });
    }

    private void clearModels() {
        lampCollectionManager.removeAllAdapters();
        groupCollectionManager.removeAllAdapters();
        presetCollectionManager.removeAllAdapters();
        transitionEffectCollectionManager.removeAllAdapters();
        pulseEffectCollectionManager.removeAllAdapters();
        sceneElementCollectionManager.removeAllAdapters();
        sceneCollectionManagerV1.removeAllAdapters();
        sceneCollectionManager.removeAllAdapters();
        masterSceneCollectionManager.removeAllAdapters();
    }
}
