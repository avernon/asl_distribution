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
import org.allseen.lsf.ControllerClient;
import org.allseen.lsf.ControllerClientCallback;
import org.allseen.lsf.ControllerServiceManager;
import org.allseen.lsf.ControllerServiceManagerCallback;
import org.allseen.lsf.LampGroupManager;
import org.allseen.lsf.LampManager;
import org.allseen.lsf.LampManagerCallback;
import org.allseen.lsf.MasterSceneManager;
import org.allseen.lsf.MasterSceneManagerCallback;
import org.allseen.lsf.PresetManager;
import org.allseen.lsf.PresetManagerCallback;
import org.allseen.lsf.PulseEffectManager;
import org.allseen.lsf.PulseEffectManagerCallback;
import org.allseen.lsf.SceneElementManager;
import org.allseen.lsf.SceneElementManagerCallback;
import org.allseen.lsf.SceneManager;
import org.allseen.lsf.SceneManagerCallback;
import org.allseen.lsf.TransitionEffectManager;
import org.allseen.lsf.TransitionEffectManagerCallback;
import org.allseen.lsf.sdk.ControllerClientStatus;
import org.allseen.lsf.sdk.callback.HelperGroupManagerCallback;
import org.allseen.lsf.sdk.listener.AllJoynListener;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class AllJoynManager {
    //private static final String TAG = "TagAlljoynManager";
    public static long controllerServiceLeaderVersion = 0;

    public static BusAttachment bus;
    public static ControllerClient controllerClient;
    public static ControllerServiceManager controllerServiceManager;
    public static LampManager lampManager;
    public static LampGroupManager groupManager;
    public static PresetManager presetManager;
    public static TransitionEffectManager transitionEffectManager;
    public static PulseEffectManager pulseEffectManager;
    public static SceneElementManager sceneElementManager;
    public static SceneManager sceneManager;
    public static MasterSceneManager masterSceneManager;
    public static AboutManager aboutManager;

    public static boolean controllerConnected = false;
    private static boolean controllerStarted = false;
    private static boolean disconnectBusOnDestroy = false;

    public static void init(
        final String applicationName,
        final ControllerClientCallback controllerClientCallback,
        final ControllerServiceManagerCallback controllerServiceManagerCallback,
        final LampManagerCallback lampManagerCallback,
        final HelperGroupManagerCallback<?> groupManagerCallback,
        final PresetManagerCallback presetManagerCallback,
        final TransitionEffectManagerCallback transitionEffectManagerCallback,
        final PulseEffectManagerCallback pulseEffectManagerCallback,
        final SceneElementManagerCallback sceneElementManagerCallback,
        final SceneManagerCallback sceneManagerCallback,
        final MasterSceneManagerCallback masterSceneManagerCallback,
        final AboutManager aboutManager,
        final AllJoynListener alljoynListener) {

        AllJoynManager.init(
            new BusAttachment(applicationName != null ? applicationName : "AllJoynManager", BusAttachment.RemoteMessage.Receive),
            controllerClientCallback,
            controllerServiceManagerCallback,
            lampManagerCallback,
            groupManagerCallback,
            presetManagerCallback,
            transitionEffectManagerCallback,
            pulseEffectManagerCallback,
            sceneElementManagerCallback,
            sceneManagerCallback,
            masterSceneManagerCallback,
            aboutManager,
            alljoynListener);
    }

    public static void init(
        final BusAttachment busAttachment,
        final ControllerClientCallback controllerClientCallback,
        final ControllerServiceManagerCallback controllerServiceManagerCallback,
        final LampManagerCallback lampManagerCallback,
        final HelperGroupManagerCallback<?> groupManagerCallback,
        final PresetManagerCallback presetManagerCallback,
        final TransitionEffectManagerCallback transitionEffectManagerCallback,
        final PulseEffectManagerCallback pulseEffectManagerCallback,
        final SceneElementManagerCallback sceneElementManagerCallback,
        final SceneManagerCallback sceneManagerCallback,
        final MasterSceneManagerCallback masterSceneManagerCallback,
        final AboutManager aboutManager,
        final AllJoynListener alljoynListener) {

        new Thread() {
            @Override
            public void run() {
                System.out.println("AllJoynManager.init() - thread starting");

                AllJoynManager.aboutManager = aboutManager;
                AllJoynManager.controllerConnected = false;
                AllJoynManager.bus = busAttachment;

                if (!AllJoynManager.bus.isConnected()) {
                    AllJoynManager.bus.connect();
                    AllJoynManager.disconnectBusOnDestroy = true;
                }
//                AllJoynManager.bus.setDebugLevel("ALL", 7);
//                AllJoynManager.bus.setDaemonDebug("ALL", 7);

                AllJoynManager.controllerClient = new ControllerClient(bus, controllerClientCallback);
                AllJoynManager.controllerServiceManager = new ControllerServiceManager(controllerClient, controllerServiceManagerCallback);
                AllJoynManager.lampManager = new LampManager(controllerClient, lampManagerCallback);
                AllJoynManager.groupManager = new SampleGroupManager(controllerClient, groupManagerCallback);
                AllJoynManager.presetManager = new PresetManager(controllerClient, presetManagerCallback);
                AllJoynManager.transitionEffectManager = new TransitionEffectManager(controllerClient, transitionEffectManagerCallback);
                AllJoynManager.pulseEffectManager = new PulseEffectManager(controllerClient, pulseEffectManagerCallback);
                AllJoynManager.sceneElementManager = new SceneElementManager(controllerClient, sceneElementManagerCallback);
                AllJoynManager.sceneManager = new SceneManager(controllerClient, sceneManagerCallback);
                AllJoynManager.masterSceneManager = new MasterSceneManager(controllerClient, masterSceneManagerCallback);

                AllJoynManager.aboutManager.start(bus);

                if (alljoynListener != null) {
                    alljoynListener.onAllJoynInitialized();
                }

                System.out.println("AllJoynManager.init() - thread stopping");
            }}.start();
    }

    public static void restart(LightingSystemQueue queue) {
        System.out.println("AllJoynManager.restart()");

        AllJoynManager.stop(queue);
        AllJoynManager.start(queue);
    }

    public static void start(final LightingSystemQueue queue) {
        queue.post(new Runnable() {
            @Override
            public void run() {
                if (controllerClient != null) {
                    if (!controllerStarted) {
                        ControllerClientStatus status = controllerClient.start();

                        if (status.equals(ControllerClientStatus.OK)) {
                            System.out.println("AllJoynManager.start(): succeeded");

                            aboutManager.start(AllJoynManager.bus);

                            controllerStarted = true;
                        } else {
                            System.out.println("AllJoynManager.start(): reposting");

                            queue.postDelayed(this, 5000);
                        }
                    }
                } else {
                    System.err.println("AllJoynManager.start(): no controller client");
                }
            }
        });
    }

    public static void stop(final LightingSystemQueue queue) {
        queue.post(new Runnable() {
            @Override
            public void run() {
                if (controllerClient != null) {
                    if (controllerStarted) {
                        System.out.println("AllJoynManager.stop(): succeeded");

                        controllerClient.stop();
                        aboutManager.stop();

                        controllerStarted = false;
                    }
                } else {
                    System.err.println("AllJoynManager.stop(): no controller client");
                }
            }
        });
    }

    public static void destroy(final LightingSystemQueue queue) {
        queue.post(new Runnable() {
            @Override
            public void run() {
                System.out.println("AllJoynManager.destroy()");

                AllJoynManager.aboutManager.destroy();

                AllJoynManager.masterSceneManager.destroy();
                AllJoynManager.sceneManager.destroy();
                AllJoynManager.presetManager.destroy();
                AllJoynManager.groupManager.destroy();
                AllJoynManager.lampManager.destroy();
                AllJoynManager.transitionEffectManager.destroy();
                AllJoynManager.pulseEffectManager.destroy();
                AllJoynManager.sceneElementManager.destroy();
                AllJoynManager.controllerServiceManager.destroy();
                AllJoynManager.controllerClient.destroy();

                if (AllJoynManager.disconnectBusOnDestroy) {
                    AllJoynManager.bus.disconnect();
                    AllJoynManager.bus.release();
                }

                //TODO-DEL?
//              AllJoynManager.controllerConnected = false;
//              AllJoynManager.disconnectBusOnDestroy = false;
//              AllJoynManager.masterSceneManager = null;
//              AllJoynManager.sceneManager = null;
//              AllJoynManager.presetManager = null;
//              AllJoynManager.groupManager = null;
//              AllJoynManager.lampManager = null;
//              AllJoynManager.controllerServiceManager = null;
//              AllJoynManager.controllerClient = null;
//              AllJoynManager.bus = null;
            }
        });
    }

    public static boolean isControllerServiceLeaderV1() {
        return AllJoynManager.controllerServiceLeaderVersion < 2;
    }
}
