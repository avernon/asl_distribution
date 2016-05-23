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
package org.allseen.lsf.sampleapp;

import java.util.concurrent.Semaphore;

import org.alljoyn.bus.BusAttachment;
import org.allseen.lsf.ControllerClient;
import org.allseen.lsf.ControllerClientCallback;
import org.allseen.lsf.ControllerClientStatus;
import org.allseen.lsf.ControllerServiceManager;
import org.allseen.lsf.ControllerServiceManagerCallback;
import org.allseen.lsf.LampGroupManager;
import org.allseen.lsf.LampManager;
import org.allseen.lsf.LampManagerCallback;
import org.allseen.lsf.MasterSceneManager;
import org.allseen.lsf.MasterSceneManagerCallback;
import org.allseen.lsf.PresetManager;
import org.allseen.lsf.PresetManagerCallback;
import org.allseen.lsf.SceneManager;
import org.allseen.lsf.SceneManagerCallback;

import android.content.Context;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.util.Log;

public class AllJoynManager {
    private static final String TAG = "TagAlljoynManager";

    public static BusAttachment bus;
    public static ControllerClient controllerClient;
    public static ControllerServiceManager controllerServiceManager;
    public static LampManager lampManager;
    public static LampGroupManager groupManager;
    public static PresetManager presetManager;
    public static SceneManager sceneManager;
    public static MasterSceneManager masterSceneManager;
    public static SampleAppActivity activity;
    public static AboutManager aboutManager;

    public static boolean controllerConnected = false;
    public static boolean controllerStarted = false;
    public static final Semaphore alljoynSemaphore = new Semaphore(1);

    public static void init(
            final FragmentManager fragmentManager,
            final ControllerClientCallback controllerClientCallback,
            final ControllerServiceManagerCallback controllerServiceManagerCallback,
            final LampManagerCallback lampManagerCallback,
            final SampleGroupManagerCallback groupManagerCallback,
            final PresetManagerCallback presetManagerCallback,
            final SceneManagerCallback sceneManagerCallback,
            final MasterSceneManagerCallback masterSceneManagerCallback,
            final AboutManager aboutManager,
            final SampleAppActivity activity) {

        // acquire lock on new thread to prevent deadlock
        new Thread(new Runnable() {
            @Override
            public void run() {
                Log.d(AllJoynManager.TAG, "AllJoynManager.init() - acquiring lock");
                alljoynSemaphore.acquireUninterruptibly();
                Log.d(AllJoynManager.TAG, "AllJoynManager.init() - locked");

                // run business logic back in main UI thread
                activity.handler.post(new Runnable() {
                    @Override
                    public void run() {
                        Log.d(AllJoynManager.TAG, "AllJoynManager.init() - running");

                        AllJoynManager.activity = activity;
                        AllJoynManager.aboutManager = aboutManager;

                        controllerConnected = false;

                        AllJoynManagerFragment alljoynManagerFragment = (AllJoynManagerFragment) fragmentManager.findFragmentByTag(AllJoynManager.TAG);

                        if (alljoynManagerFragment == null) {
                            alljoynManagerFragment = new AllJoynManagerFragment();
                            alljoynManagerFragment.controllerClientCallback = controllerClientCallback;
                            alljoynManagerFragment.controllerServiceManagerCallback = controllerServiceManagerCallback;
                            alljoynManagerFragment.lampManagerCallback = lampManagerCallback;
                            alljoynManagerFragment.groupManagerCallback = groupManagerCallback;
                            alljoynManagerFragment.presetManagerCallback = presetManagerCallback;
                            alljoynManagerFragment.sceneManagerCallback = sceneManagerCallback;
                            alljoynManagerFragment.masterSceneManagerCallback = masterSceneManagerCallback;

                            fragmentManager.beginTransaction().add(alljoynManagerFragment, AllJoynManager.TAG).commit();
                        }
                    }
                });
            }
        }).start();
        Log.d(AllJoynManager.TAG, "AllJoynManager.init() - thread started, resuming");
    }

    public static void restart() {
        Log.d(AllJoynManager.TAG, "AllJoynManager.restart()");

        AllJoynManager.stop();
        AllJoynManager.start();
    }

    public static void start() {
        if (!controllerStarted) {
            Log.d(AllJoynManager.TAG, "AllJoynManager.start()");

            controllerStarted = true;

            activity.handler.post(new Runnable() {
                @Override
                public void run() {
                    if (controllerClient != null) {
                        if (controllerClient.start().equals(ControllerClientStatus.ERR_RETRY)) {
                            Log.d(AllJoynManager.TAG, "AllJoynManager.start(): reposting");
                            activity.handler.postDelayed(this, 5000);
                        }
                    } else {
                        Log.d(AllJoynManager.TAG, "AllJoynManager.start(): no controller client");
                    }
                }
            });
        }
    }

    public static void stop() {
        if (controllerStarted) {
            Log.d(AllJoynManager.TAG, "AllJoynManager.stop()");

            controllerStarted = false;

            activity.handler.post(new Runnable() {
                @Override
                public void run() {
                    if (controllerClient != null) {
                        controllerClient.stop();
                    } else {
                        Log.d(AllJoynManager.TAG, "AllJoynManager.stop(): no controller client");
                    }
                }
            });
        }
    }

    public static void destroy(final FragmentManager fragmentManager) {

        // acquire lock on new thread to prevent deadlock
        new Thread(new Runnable() {
            @Override
            public void run() {
                Log.d(AllJoynManager.TAG, "AllJoynManager.destroy() - acquiring lock");
                alljoynSemaphore.acquireUninterruptibly();
                Log.d(AllJoynManager.TAG, "AllJoynManager.destroy() - locked");

                // run business logic back in main UI thread
                activity.handler.post(new Runnable() {
                    @Override
                    public void run() {
                        Log.d(AllJoynManager.TAG, "AllJoynManager.destroy() - running");

                        AllJoynManagerFragment alljoynManagerFragment = (AllJoynManagerFragment) fragmentManager.findFragmentByTag(AllJoynManager.TAG);

                        if (alljoynManagerFragment != null) {
                            fragmentManager.beginTransaction().remove(alljoynManagerFragment).commit();
                        }
                    }
                });
            }
        }).start();
        Log.d(AllJoynManager.TAG, "AllJoynManager.destroy() - thread started, resuming");
    }

    public static class AllJoynManagerFragment extends Fragment {
        private AllJoynManagerAsyncTask alljoynManagerTask;

        public ControllerClientCallback controllerClientCallback;
        public ControllerServiceManagerCallback controllerServiceManagerCallback;
        public LampManagerCallback lampManagerCallback;
        public SampleGroupManagerCallback groupManagerCallback;
        public PresetManagerCallback presetManagerCallback;
        public SceneManagerCallback sceneManagerCallback;
        public MasterSceneManagerCallback masterSceneManagerCallback;

        public BusAttachment bus;
        public ControllerClient controllerClient;
        public ControllerServiceManager controllerServiceManager;
        public LampManager lampManager;
        public LampGroupManager groupManager;
        public PresetManager presetManager;
        public SceneManager sceneManager;
        public MasterSceneManager masterSceneManager;

        @Override
        public void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);

            setRetainInstance(true);

            Context context = getActivity().getApplicationContext();

            org.alljoyn.bus.alljoyn.DaemonInit.PrepareDaemon(context);

            alljoynManagerTask = new AllJoynManagerAsyncTask(this);
            alljoynManagerTask.execute(context.getPackageName());
        }

        @Override
        public void onDestroy() {
            super.onDestroy();

            Log.d(AllJoynManager.TAG, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            Log.d(AllJoynManager.TAG, "onDestroy()");
            aboutManager.destroy();

            masterSceneManager.destroy();
            sceneManager.destroy();
            presetManager.destroy();
            groupManager.destroy();
            lampManager.destroy();
            controllerServiceManager.destroy();
            controllerClient.destroy();

            bus.disconnect();
            bus.release();

            AllJoynManager.controllerConnected = false;
            AllJoynManager.masterSceneManager = null;
            AllJoynManager.sceneManager = null;
            AllJoynManager.presetManager = null;
            AllJoynManager.groupManager = null;
            AllJoynManager.lampManager = null;
            AllJoynManager.controllerServiceManager = null;
            AllJoynManager.controllerClient = null;
            AllJoynManager.bus = null;

            AllJoynManager.alljoynSemaphore.release();
            Log.d(AllJoynManager.TAG, "AllJoynManager.destroy() - unlocked");
        }
    };

    private static class AllJoynManagerAsyncTask extends AsyncTask<String, Void, Void> {
        private final AllJoynManagerFragment alljoynManagerFragment;

        private AllJoynManagerAsyncTask(AllJoynManagerFragment alljoynManagerFragment) {
            this.alljoynManagerFragment = alljoynManagerFragment;
        }

        @Override
        protected Void doInBackground(String... params) {
            Log.d(AllJoynManager.TAG, "Creating BusAttachment");
            alljoynManagerFragment.bus = new BusAttachment(params[0], BusAttachment.RemoteMessage.Receive);
            alljoynManagerFragment.bus.connect();
            alljoynManagerFragment.bus.setDebugLevel("CONTROLLER_CLIENT", 7);
//            alljoynManagerFragment.bus.setDaemonDebug("ALL", 7);

            alljoynManagerFragment.controllerClient = new ControllerClient(alljoynManagerFragment.bus, alljoynManagerFragment.controllerClientCallback);
            alljoynManagerFragment.controllerServiceManager = new ControllerServiceManager(alljoynManagerFragment.controllerClient, alljoynManagerFragment.controllerServiceManagerCallback);
            alljoynManagerFragment.lampManager = new LampManager(alljoynManagerFragment.controllerClient, alljoynManagerFragment.lampManagerCallback);
            alljoynManagerFragment.groupManager = new SampleGroupManager(alljoynManagerFragment.controllerClient, alljoynManagerFragment.groupManagerCallback);
            alljoynManagerFragment.presetManager = new PresetManager(alljoynManagerFragment.controllerClient, alljoynManagerFragment.presetManagerCallback);
            alljoynManagerFragment.sceneManager = new SceneManager(alljoynManagerFragment.controllerClient, alljoynManagerFragment.sceneManagerCallback);
            alljoynManagerFragment.masterSceneManager = new MasterSceneManager(alljoynManagerFragment.controllerClient, alljoynManagerFragment.masterSceneManagerCallback);

            return null;
        }

        @Override
        protected void onPostExecute(Void response) {
            super.onPostExecute(response);

            AllJoynManager.bus = alljoynManagerFragment.bus;
            AllJoynManager.controllerClient = alljoynManagerFragment.controllerClient;
            AllJoynManager.controllerServiceManager = alljoynManagerFragment.controllerServiceManager;
            AllJoynManager.lampManager = alljoynManagerFragment.lampManager;
            AllJoynManager.groupManager = alljoynManagerFragment.groupManager;
            AllJoynManager.presetManager = alljoynManagerFragment.presetManager;
            AllJoynManager.sceneManager = alljoynManagerFragment.sceneManager;
            AllJoynManager.masterSceneManager = alljoynManagerFragment.masterSceneManager;

            aboutManager.initializeClient(AllJoynManager.bus);

            AllJoynManager.alljoynSemaphore.release();

            activity.onAllJoynManagerInitialized();

            Log.d(AllJoynManager.TAG, "AllJoynManager.init() - unlocked");
       }
    }
}
