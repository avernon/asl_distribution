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

import java.util.ArrayList;
import java.util.Collection;

import org.alljoyn.bus.BusAttachment;
import org.allseen.lsf.LampGroupManager;
import org.allseen.lsf.MasterSceneManager;
import org.allseen.lsf.PresetManager;
import org.allseen.lsf.PulseEffectManager;
import org.allseen.lsf.SceneElementManager;
import org.allseen.lsf.TransitionEffectManager;
import org.allseen.lsf.sdk.factory.AllLightingItemsFactory;
import org.allseen.lsf.sdk.listener.AllJoynListener;
import org.allseen.lsf.sdk.listener.LightingListener;
import org.allseen.lsf.sdk.listener.NextControllerConnectionListener;
import org.allseen.lsf.sdk.manager.AllJoynManager;
import org.allseen.lsf.sdk.manager.ControllerCollectionManager;
import org.allseen.lsf.sdk.manager.GroupCollectionManager;
import org.allseen.lsf.sdk.manager.LampCollectionManager;
import org.allseen.lsf.sdk.manager.LightingSystemManager;
import org.allseen.lsf.sdk.manager.LightingSystemQueue;
import org.allseen.lsf.sdk.manager.MasterSceneCollectionManager;
import org.allseen.lsf.sdk.manager.PresetCollectionManager;
import org.allseen.lsf.sdk.manager.PulseEffectCollectionManager;
import org.allseen.lsf.sdk.manager.SceneCollectionManagerV1;
import org.allseen.lsf.sdk.manager.SceneCollectionManagerV2;
import org.allseen.lsf.sdk.manager.SceneElementCollectionManager;
import org.allseen.lsf.sdk.manager.TransitionEffectCollectionManager;
import org.allseen.lsf.sdk.model.ColorStateConverter;
import org.allseen.lsf.sdk.model.ControllerDataModel;
import org.allseen.lsf.sdk.model.GroupDataModel;
import org.allseen.lsf.sdk.model.LampDataModel;
import org.allseen.lsf.sdk.model.LightingItemFilter;
import org.allseen.lsf.sdk.model.LightingItemUtil;
import org.allseen.lsf.sdk.model.MasterSceneDataModel;
import org.allseen.lsf.sdk.model.PresetDataModel;
import org.allseen.lsf.sdk.model.PulseEffectDataModelV2;
import org.allseen.lsf.sdk.model.SceneDataModel;
import org.allseen.lsf.sdk.model.SceneDataModelV2;
import org.allseen.lsf.sdk.model.SceneElementDataModelV2;
import org.allseen.lsf.sdk.model.TransitionEffectDataModelV2;

/**
 * LightingDirector is the main entry point to the Lighting SDK and provides access to the
 * components in the Lighting system. This includes the lamps connected to the lighting controller
 * and all group, preset, effect, and scene definitions stored in the lighting controller. The
 * LightingDirector also provides an interface to create groups, presets, effects, and scenes as
 * well as add/remove callbacks that will be notified when events occur in the Lighting system.
 * <p>
 * <b>Note: The LightingController requires a WiFi or Ethernet network connection.</b>
 * <p>
 * Please see the LSFTutorial project for an example of how to use the LightingDirector class.
 */
public class LightingDirector {
    /**
     * Specifies the max number of groups that can be created in the controller.
     */
    public static final int MAX_GROUPS = LampGroupManager.MAX_LAMP_GROUPS;

    /**
     * Specifies the max number of presets that can be created in the controller.
     */
    public static final int MAX_PRESETS = PresetManager.MAX_PRESETS;

    /**
     * Specifies the max number of transition effects that can be created in the controller.
     */
    public static final int MAX_TRANSITION_EFFECTS = TransitionEffectManager.MAX_TRANSITION_EFFECTS;

    /**
     * Specifies the max number of pulse effects that can be created in the controller.
     */
    public static final int MAX_PULSE_EFFECTS = PulseEffectManager.MAX_PULSE_EFFECTS;

    /**
     * Specifies the max number of scene elements that can be created in the controller.
     */
    public static final int MAX_SCENE_ELEMENTS = SceneElementManager.MAX_SCENE_ELEMENTS;

    /**
     * Specifies the max number of scenes that can be created in the controller.
     */
    public static final int MAX_SCENES = MasterSceneManager.MAX_MASTER_SCENES;

    /**
     * Specifies the max number of master scenes that can be created in the controller.
     */
    public static final int MAX_MASTER_SCENES = MasterSceneManager.MAX_MASTER_SCENES;

    /**
     * Specifies the minimum hue
     */
    public static final int HUE_MIN = ColorStateConverter.VIEW_HUE_MIN;

    /**
     * Specifies the maximum hue
     */
    public static final int HUE_MAX = ColorStateConverter.VIEW_HUE_MAX;

    /**
     * Specifies the minimum saturation
     */
    public static final int SATURATION_MIN = ColorStateConverter.VIEW_SATURATION_MIN;

    /**
     * Specifies the maximum saturation
     */
    public static final int SATURATION_MAX = ColorStateConverter.VIEW_SATURATION_MAX;

    /**
     * Specifies the minimum brightness
     */
    public static final int BRIGHTNESS_MIN = ColorStateConverter.VIEW_BRIGHTNESS_MIN;

    /**
     * Specifies the maximum brightness
     */
    public static final int BRIGHTNESS_MAX = ColorStateConverter.VIEW_BRIGHTNESS_MAX;

    /**
     * Specifies the minimum color temperature
     */
    public static final int COLORTEMP_MIN = ColorStateConverter.VIEW_COLORTEMP_MIN;

    /**
     * Specifies the maximum color temperature
     */
    public static final int COLORTEMP_MAX = ColorStateConverter.VIEW_COLORTEMP_MAX;

    private static final String LANGUAGE_DEFAULT = "en";
    private static final LightingDirector instance = new LightingDirector();

    private final LightingSystemManager<Lamp, Group, Preset, TransitionEffect, PulseEffect, SceneElement, SceneV1, SceneV2, MasterScene, Controller, LightingItemErrorEvent> lightingManager;
    private String defaultLanguage;

    private boolean alljoynInitialized;
    private boolean networkConnected;

    private static class LightingItemFactory implements AllLightingItemsFactory<Lamp, Group, Preset, TransitionEffect, PulseEffect, SceneElement, SceneV1, SceneV2, MasterScene, Controller, LightingItemErrorEvent> {

        @Override
        public Lamp createLamp(String lampID) {
            return new Lamp(lampID);
        }

        @Override
        public Lamp[] createLamps(int size) {
            return new Lamp[size];
        }

        @Override
        public LampDataModel findLampDataModel(Lamp lamp) {
            return lamp != null ? lamp.getLampDataModel() : null;
        }

        @Override
        public Group createGroup(String groupID) {
            return new Group(groupID);
        }

        @Override
        public Group[] createGroups(int size) {
            return new Group[size];
        }

        @Override
        public GroupDataModel findGroupDataModel(Group group) {
            return group != null ? group.getGroupDataModel() : null;
        }

        @Override
        public Preset createPreset(String presetID) {
            return new Preset(presetID);
        }

        @Override
        public Preset[] createPresets(int size) {
            return new Preset[size];
        }

        @Override
        public PresetDataModel findPresetDataModel(Preset preset) {
            return preset != null ? preset.getPresetDataModel() : null;
        }

        @Override
        public TransitionEffect createTransitionEffect(String transitionEffectID) {
            return new TransitionEffect(transitionEffectID);
        }

        @Override
        public TransitionEffect[] createTransitionEffects(int size) {
            return new TransitionEffect[size];
        }

        @Override
        public TransitionEffectDataModelV2 findTransitionEffectDataModel(TransitionEffect transitionEffect) {
            return transitionEffect != null ? transitionEffect.getTransitionEffectDataModel() : null;
        }

        @Override
        public PulseEffect createPulseEffect(String pulseEffectID) {
            return new PulseEffect(pulseEffectID);
        }

        @Override
        public PulseEffect[] createPulseEffects(int size) {
            return new PulseEffect[size];
        }

        @Override
        public PulseEffectDataModelV2 findPulseEffectDataModel(PulseEffect pulseEffect) {
            return pulseEffect != null ? pulseEffect.getPulseEffectDataModel() : null;
        }

        @Override
        public SceneElement createSceneElement(String sceneElementID) {
            return new SceneElement(sceneElementID);
        }

        @Override
        public SceneElement[] createSceneElements(int size) {
            return new SceneElement[size];
        }

        @Override
        public SceneElementDataModelV2 findSceneElementDataModel(SceneElement sceneElement) {
            return sceneElement != null ? sceneElement.getSceneElementDataModel() : null;
        }

        @Override
        public SceneV1 createSceneV1(String sceneID) {
            return new SceneV1(sceneID);
        }

        @Override
        public SceneV1[] createScenesV1(int size) {
            return new SceneV1[size];
        }

        @Override
        public SceneDataModel findSceneDataModelV1(SceneV1 scene) {
            return scene.getSceneDataModel();
        }

        @Override
        public SceneV2 createSceneV2(String sceneID) {
            return new SceneV2(sceneID);
        }

        @Override
        public SceneV2[] createScenesV2(int size) {
            return new SceneV2[size];
        }

        @Override
        public SceneDataModelV2 findSceneDataModelV2(SceneV2 scene) {
            return scene.getSceneDataModel();
        }

        @Override
        public MasterScene createMasterScene(String masterSceneID) {
            return new MasterScene(masterSceneID);
        }

        @Override
        public MasterScene[] createMasterScenes(int size) {
            return new MasterScene[size];
        }

        @Override
        public MasterSceneDataModel findMasterSceneDataModel(MasterScene masterScene) {
            return masterScene.getMasterSceneDataModel();
        }

        @Override
        public Controller createController(String controllerID) {
            return new Controller();
        }

        @Override
        public Controller[] createControllers(int size) {
            return new Controller[size];
        }

        @Override
        public ControllerDataModel findControllerDataModel(Controller controller) {
            return controller.getControllerDataModel();
        }

        @Override
        public LightingItemErrorEvent createError(String name, ResponseCode responseCode, String itemID, TrackingID trackingID, ErrorCode[] errorCodes) {
            return new LightingItemErrorEvent(name, responseCode, itemID, trackingID, errorCodes);
        }
    };

    private class ItemIDCollectionFilter<ITEM extends LightingItem> implements LightingItemFilter<ITEM> {
        protected Collection<String> itemIDs;

        public ItemIDCollectionFilter(Collection<String> itemIDs) {
            this.itemIDs = itemIDs;
        }

        @Override
        public boolean passes(ITEM item) {
            return itemIDs.contains(item.getId());
        }
    }

    private class InitializedFilter<ITEM extends LightingItem> implements LightingItemFilter<ITEM> {
        @Override
        public boolean passes(ITEM item) {
            return item.isInitialized();
        }
    }

    /**
     * Returns a LightingDirector instance.
     * <p>
     * <b>Note: The {@link #start()} method must be called at some point when you're ready
     * to begin working with the Lighting system.</b>
     *
     * @return Reference to LightingDirector
     */
    public static LightingDirector get() {
        return LightingDirector.instance;
    }

    /*
     * Construct a LightingDirector instance with the default queue.
     *
     * Note that this is private since LightingDirector is a singleton. See
     * LightingDirector.get()
     */
    private LightingDirector() {
        super();
        lightingManager    = new LightingSystemManager<Lamp, Group, Preset, TransitionEffect, PulseEffect, SceneElement, SceneV1, SceneV2, MasterScene, Controller, LightingItemErrorEvent>(new LightingItemFactory());
        defaultLanguage    = LANGUAGE_DEFAULT;
        networkConnected   = false;
        alljoynInitialized = false;
    }

    /**
     * Returns the version number of the Lighting SDK.
     *
     * @return Version number of the Lighting SDK
     */
    public int getVersion() {
        return 2;
    }

    /**
     * Causes the LightingDirector to start interacting with the Lighting system. The LightingDirector
     * will try to connect to a lighting controller. This method will create its own BusAttachment and
     * default LightingSystemQueue.
     * <p>
     * <b>Note: This method should be called before interacting with the LightingDirector.
     * Subsequent calls to this method must each be preceded by a call to stop().</b>
     * <p>
     * <b>Note: You should ensure WiFi or Ethernet connection is available before
     * calling this method.</b>
     */
    public void start() {
        start("LightingDirector");
    }

    /**
     * Causes the LightingDirector to start interacting with the Lighting system using the
     * specified application name. The LightingDirector will try to connect to a lighting
     * controller. This method uses the application name when creating the AllJoyn bus
     * attachment and creates its own default LightingSystemQueue.
     * <p>
     * <b>Note: This method should be called before interacting with the LightingDirector.
     * Subsequent calls to this method must each be preceded by a call to stop().</b>
     * <p>
     * <b>Note: You should ensure WiFi or Ethernet connection is available before
     * calling this method.</b>
     *
     * @param applicationName
     *            Name for the AllJoyn BusAttachment. See the AllJoyn core documentation for
     *            more information on bus attachments.
     */
    public void start(String applicationName) {
        start(applicationName, null);
    }

    /**
     * Causes the LightingDirector to start interacting with the Lighting system using the
     * specified AllJoyn bus attachment. The LightingDirector will try to connect to a lighting
     * controller. This also method creates its own default LightingSystemQueue.
     * <p>
     * <b>Note: This method should be called before interacting with the LightingDirector.
     * Subsequent calls to this method must each be preceded by a call to stop().</b>
     * <p>
     * <b>Note: You should ensure WiFi or Ethernet connection is available before
     * calling this method.</b>
     *
     * @param busAttachment
     *            AllJoyn BusAttachment to be used for the Lighting systen. See the AllJoyn
     *            core documentation for more information on bus attachments.
     */
    public void start(BusAttachment busAttachment) {
        start(busAttachment, null);
    }

    /**
     * Causes the LightingDirector to start interacting with the Lighting system using the
     * specified application name and queue. The LightingDirector will try to connect to a
     * lighting controller. This method uses the application name when creating the AllJoyn
     * bus attachment.
     * <p>
     * <b>Note: This method should be called before interacting with the LightingDirector.
     * Subsequent calls to this method must each be preceded by a call to stop().</b>
     * <p>
     * <b>Note: You should ensure WiFi or Ethernet connection is available before
     * calling this method.</b>
     *
     * @param applicationName
     *            Name for the AllJoyn BusAttachment. See the AllJoyn core documentation for
     *            more information on bus attachments.
     *
     * @param queue
     *            Serial queue that will handle all lighting events on the provided thread. The
     *            SDK will process internal tasks and invoke all client listeners from the thread
     *            associated with this queue.
     */
    public void start(String applicationName, LightingSystemQueue queue) {
        lightingManager.init(applicationName, queue, createAllJoynListener());
    }

    /**
     * Causes the LightingDirector to start interacting with the Lighting system using the
     * specified AllJoyn bus attachment and queue. The LightingDirector will try to connect
     * to a lighting controller.
     * <p>
     * <b>Note: This method should be called before interacting with the LightingDirector.
     * Subsequent calls to this method must each be preceded by a call to stop().</b>
     * <p>
     * <b>Note: You should ensure WiFi or Ethernet connection is available before
     * calling this method.</b>
     *
     * @param busAttachment
     *            AllJoyn BusAttachment to be used for the Lighting system. See the AllJoyn
     *            core documentation for more information on bus attachments.
     * @param queue
     *            Instance of serial queue that will handle all lighting events on the provided
     *            thread. The SDK will process internal tasks and invoke all client listeners
     *            from the thread associated with this queue.
     */
    public void start(BusAttachment busAttachment, LightingSystemQueue queue) {
        lightingManager.init(busAttachment, queue, createAllJoynListener());
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected AllJoynListener createAllJoynListener() {
        return new AllJoynListener() {
            @Override
            public void onAllJoynInitialized() {
                alljoynInitialized = true;

                if (networkConnected) {
                    lightingManager.start();
                }
            }
        };
    }

    /**
     * Causes the LightingDirector to stop interacting with the Lighting system. The LightingDirector
     * will disconnect from the lighting controller, if a connection exists.
     * <p>
     * <b>Note: This method must be preceded by a call to {@link start()}.</b>
     */
    public void stop() {
        lightingManager.destroy();
    }

    /**
     * Specifies if there is an active network connection for the Lighting System.
     * This method must be called every time there is a major change to the underlying
     * WiFi or Ethernet connection. Set this method to false when the WiFi or Ethernet connection
     * disappears. Set this method back to true when the WiFi or Ethernet connection is
     * reestablished.</b>
     * <p>
     * <b>This method must be called and set to true for the LightingDirector to
     * successfully connect to a lighting controller.</b>
     *
     * @param isConnected
     *            boolean that specifies true if there is an active WiFi or Ethernet connection, false
     *            otherwise.
     */
    public void setNetworkConnectionStatus(boolean isConnected) {
        if (alljoynInitialized) {
            if (!isConnected) {
                lightingManager.stop();
            } else if (!networkConnected) {
                lightingManager.stop();
                lightingManager.start();
            }
        }

        networkConnected = isConnected;
    }

    /**
     * Returns the AllJoyn BusAttachment being used by the Lighting system.
     * <p>
     * The BusAttachment will be <code>null</code> until some time after the call to start().
     *
     * @return AllJoyn BusAttachment being used by the Lighting system.
     */
    public BusAttachment getBusAttachment() {
        return AllJoynManager.bus;
    }

    /**
     * Returns the number of Lamps stored in the Lighting controller.
     *
     * @return Number of active Lamps
     */
    public int getLampCount() {
        return getLampCollectionManager().size();
    }

    /**
     * Returns a snapshot of all the Lamps connected to the Lighting controller including
     * lamps that may not have received all data.
     * <p>
     * <b>Note: The contents of this array may change in subsequent calls to this method
     * as new lamps are discovered or existing lamps are determined to be offline. This
     * array may also be empty.</b>
     *
     * @return Array of Lamps
     */
    public Lamp[] getLamps() {
        return getLampCollectionManager().getLamps();
    }

    /**
     * Returns the Lamps connected to the Lighting controller corresponding to the set of
     * lamp IDs. Any ID that is not matched to a Lamp will be skipped. The returned
     * array may be empty.
     *
     * @param lampIDs The IDs of the Lamps to retrieve
     *
     * @return Array of Lamps
     */
    public Lamp[] getLamps(Collection<String> lampIDs) {
        return getLampCollectionManager().getLamps(new ItemIDCollectionFilter<Lamp>(lampIDs));
    }

    /**
     * Returns a snapshot of all the Lamps connected to the Lighting controller that have received all
     * their data.
     * <p>
     * <b>Note: The contents of this array may change in subsequent calls to this method
     * as new lamps are discovered or existing lamps are determined to be offline. This
     * array may also be empty.</b>
     *
     * @return Array of initialized Lamps
     */
    public Lamp[] getInitializedLamps() {
        return getLampCollectionManager().getLamps(new InitializedFilter<Lamp>());
    }

    /**
     * Returns a reference to a Lamp with the corresponding ID. If a match is not found for the
     * ID, this method will return null.
     *
     * @param lampId The ID of the Lamp
     *
     * @return Reference to a Lamp or null.
     */
    public Lamp getLamp(String lampId) {
        return getLampCollectionManager().getLamp(lampId);
    }

    /**
     * Returns the number of Groups stored in the Lighting controller.
     *
     * @return Number of active Groups
     */
    public int getGroupCount() {
        return getGroupCollectionManager().size();
    }

    /**
     * Returns a snapshot of all the Groups stored in the Lighting controller including
     * groups that may not have received all data.
     * <p>
     * <b>Note: The contents of this array may change in subsequent calls to this method as new
     * groups are created or existing groups are deleted. This array may also be empty.</b>
     *
     * @return Array of Groups
     */
    public Group[] getGroups() {
        return getGroupCollectionManager().getGroups();
    }

    /**
     * Returns the Groups stored in the Lighting controller corresponding to the set of
     * group IDs. Any ID that is not matched to a Group will be skipped. The returned
     * array may be empty.
     *
     * @param groupIDs The IDs of the Groups to retrieve
     *
     * @return Array of Groups
     */
    public Group[] getGroups(Collection<String> groupIDs) {
        return getGroupCollectionManager().getGroups(new ItemIDCollectionFilter<Group>(groupIDs));
    }

    /**
     * Returns a snapshot of all the Groups stored in the Lighting controller that have received all
     * their data.
     * <p>
     * <b>Note: The contents of this array may change in subsequent calls to this method as new
     * groups are created or existing groups are deleted. This array may also be empty.</b>
     *
     * @return Array of initialized Groups
     */
    public Group[] getInitializedGroups() {
        return getGroupCollectionManager().getGroups(new InitializedFilter<Group>());
    }

    /**
     * Returns a reference to a Group with the corresponding ID. If a match is not found for the
     * ID, this method will return null.
     *
     * @param groupId The ID of the Group
     *
     * @return Reference to a Group or null.
     */
    public Group getGroup(String groupId) {
        return getGroupCollectionManager().getGroup(groupId);
    }

    /**
     * Returns the number of Presets stored in the Lighting controller.
     *
     * @return Number of active Presets
     */
    public int getPresetCount() {
        return getPresetCollectionManager().size();
    }

    /**
     * Returns a snapshot of all the Presets stored in the Lighting controller including
     * presets that may not have received all data.
     * <p>
     * <b>Note: The contents of this array may change in subsequent calls to this method as new
     * presets are created or existing presets are deleted. This array may also be empty.</b>
     *
     * @return Array of Presets
     */
    public Preset[] getPresets() {
        return getPresetCollectionManager().getPresets();
    }

    /**
     * Returns the Presets stored in the Lighting controller corresponding to the set of
     * preset IDs. Any ID that is not matched to a Preset will be skipped. The returned
     * array may be empty.
     *
     * @param presetIDs The IDs of the Presets to retrieve
     *
     * @return Array of Presets
     */
    public Preset[] getPresets(Collection<String> presetIDs) {
        return getPresetCollectionManager().getPresets(new ItemIDCollectionFilter<Preset>(presetIDs));
    }

    /**
     * Returns a snapshot of all the Presets stored in the Lighting controller that have received all
     * their data.
     * <p>
     * <b>Note: The contents of this array may change in subsequent calls to this method as new
     * presets are created or existing presets are deleted. This array may also be empty.</b>
     *
     * @return Array of initialized Presets
     */
    public Preset[] getInitializedPresets() {
        return getPresetCollectionManager().getPresets(new InitializedFilter<Preset>());
    }

    /**
     * Returns a reference to a Preset with the corresponding ID. If a match is not found for the
     * ID, this method will return null.
     *
     * @param presetId The ID of the Preset
     *
     * @return Reference to a Preset or null.
     */
    public Preset getPreset(String presetId) {
        return getPresetCollectionManager().getPreset(presetId);
    }

    /**
     * Returns the number of TransitionEffects stored in the Lighting controller.
     *
     * @return Number of active TransitionEffects
     */
    public int getTransitionEffectCount() {
        return getTransitionEffectCollectionManager().size();
    }

    /**
     * Returns a snapshot of all the TransitionEffects stored in the Lighting controller including
     * transition effects that may not have received all data.
     * <p>
     * <b>Note: The contents of this array may change in subsequent calls to this method as new
     * transition effects are created or existing transition effects are deleted. This array may
     * also be empty.</b>
     *
     * @return Array of TransitionEffects
     */
    public TransitionEffect[] getTransitionEffects() {
        return getTransitionEffectCollectionManager().getTransitionEffects();
    }

    /**
     * Returns the TransitionEffects stored in the Lighting controller corresponding to the set of
     * transition effect IDs. Any ID that is not matched to a TransitionEffect will be skipped. The
     * returned array may be empty.
     *
     * @param transitionEffectIDs The IDs of the TransitionEffects to retrieve
     *
     * @return Array of TransitionEffects
     */
    public TransitionEffect[] getTransitionEffects(Collection<String> transitionEffectIDs) {
        return getTransitionEffectCollectionManager().getTransitionEffects(new ItemIDCollectionFilter<TransitionEffect>(transitionEffectIDs));
    }

    /**
     * Returns a snapshot of all the TransitionEffects stored in the Lighting controller that have received all
     * their data.
     * <p>
     * <b>Note: The contents of this array may change in subsequent calls to this method as new
     * transition effects are created or existing transition effects are deleted. This array may
     * also be empty.</b>
     *
     * @return Array of initialized TransitionEffects
     */
    public TransitionEffect[] getInitializedTransitionEffects() {
        return getTransitionEffectCollectionManager().getTransitionEffects(new InitializedFilter<TransitionEffect>());
    }

    /**
     * Returns a reference to a TransitionEffect with the corresponding ID. If a match is not found for the
     * ID, this method will return null.
     *
     * @param transitionEffectId The ID of the TransitionEffect
     *
     * @return Reference to a TransitionEffect or null.
     */
    public TransitionEffect getTransitionEffect(String transitionEffectId) {
        return getTransitionEffectCollectionManager().getTransistionEffect(transitionEffectId);
    }

    /**
     * Returns the number of PulseEffects stored in the Lighting controller.
     *
     * @return Number of active PulseEffects
     */
    public int getPulseEffectCount() {
        return getPulseEffectCollectionManager().size();
    }

    /**
     * Returns a snapshot of all the PulseEffects stored in the Lighting controller including
     * pulse effects that may not have received all data.
     * <p>
     * <b>Note: The contents of this array may change in subsequent calls to this method as new
     * pulse effects are created or existing pulse effects are deleted. This array may
     * also be empty.</b>
     *
     * @return Array of PulseEffects
     */
    public PulseEffect[] getPulseEffects() {
        return getPulseEffectCollectionManager().getPulseEffects();
    }

    /**
     * Returns the PulseEffects stored in the Lighting controller corresponding to the set of
     * pulse effect IDs. Any ID that is not matched to a PulseEffect will be skipped. The returned
     * array may be empty.
     *
     * @param pulseEffectIDs The IDs of the PulseEffects to retrieve
     *
     * @return Array of PulseEffects
     */
    public PulseEffect[] getPulseEffects(Collection<String> pulseEffectIDs) {
        return getPulseEffectCollectionManager().getPulseEffects(new ItemIDCollectionFilter<PulseEffect>(pulseEffectIDs));
    }

    /**
     * Returns a snapshot of all the PulseEffects stored in the Lighting controller that have received all
     * their data.
     * <p>
     * <b>Note: The contents of this array may change in subsequent calls to this method as new
     * pulse effects are created or existing pulse effects are deleted. This array may also be
     * empty.</b>
     *
     * @return Array of initialized PulseEffects
     */
    public PulseEffect[] getInitializedPulseEffects() {
        return getPulseEffectCollectionManager().getPulseEffects(new InitializedFilter<PulseEffect>());
    }

    /**
     * Returns a reference to a PulseEffect with the corresponding ID. If a match is not found for the
     * ID, this method will return null.
     *
     * @param pulseEffectId The ID of the PulseEffect
     *
     * @return Reference to a PulseEffect or null.
     */
    public PulseEffect getPulseEffect(String pulseEffectId) {
        return getPulseEffectCollectionManager().getPulseEffect(pulseEffectId);
    }

    /**
     * Returns the number of Scenes stored in the Lighting controller.
     *
     * @return Number of SceneElements
     */
    public int getSceneElementCount() {
        return getSceneElementCollectionManager().size();
    }

    /**
     * Returns a snapshot of all the SceneElements stored in the Lighting controller including
     * scene elements that may not have received all data.
     * <p>
     * <b>Note: The contents of this array may change in subsequent calls to this method as new
     * scene elements are created or existing scene elements are deleted. This array may also be
     * empty.</b>
     *
     * @return Array of SceneElements
     */
    public SceneElement[] getSceneElements() {
        return getSceneElementCollectionManager().getSceneElements();
    }

    /**
     * Returns the SceneElements stored in the Lighting controller corresponding to the set of
     * scene element IDs. Any ID that is not matched to a SceneElement will be skipped. The returned
     * array may be empty.
     *
     * @param sceneElementIDs The IDs of the SceneElements to retrieve
     *
     * @return Array of SceneElements
     */
    public SceneElement[] getSceneElements(Collection<String> sceneElementIDs) {
        return getSceneElementCollectionManager().getSceneElements(new ItemIDCollectionFilter<SceneElement>(sceneElementIDs));
    }

    /**
     * Returns a snapshot of all the SceneElements stored in the Lighting controller that have received all
     * their data.
     * <p>
     * <b>Note: The contents of this array may change in subsequent calls to this method as new
     * scene elements are created or existing scene elements are deleted. This array may also be
     * empty.</b>
     *
     * @return Array of initialized SceneElements
     */
    public SceneElement[] getInitializedSceneElements() {
        return getSceneElementCollectionManager().getSceneElements(new InitializedFilter<SceneElement>());
    }

    /**
     * Returns a reference to the SceneElement with the corresponding ID. If a match is not found for
     * the ID, this method will return null.
     *
     * @param sceneElementId The ID of the SceneElement
     *
     * @return Reference to a SceneElement or null.
     */
    public SceneElement getSceneElement(String sceneElementId) {
        return getSceneElementCollectionManager().getSceneElement(sceneElementId);
    }

    /**
     * Returns the number of Scenes stored in the Lighting controller.
     *
     * @return Number of Scenes
     */
    public int getSceneCount() {
        int count = getSceneCollectionManagerV2().size();

        if (count == 0) {
            count = getSceneCollectionManager().size();
        }

        return count;
    }

    /**
     * Returns a snapshot of all the Scenes stored in the Lighting controller including
     * scene that may not have received all data.
     * <p>
     * <b>Note: The contents of this array may change in subsequent calls to this method as new
     * scenes are created or existing scenes are deleted. This array may also be empty.</b>
     *
     * @return Array of Scenes
     */
    public Scene[] getScenes() {
        Collection<Scene> scenes = new ArrayList<Scene>(getSceneCount());

        scenes.addAll(getSceneCollectionManagerV2().getScenesCollection(null));

        if (scenes.size() == 0) {
            scenes.addAll(getSceneCollectionManager().getScenesCollection(null));
        }

        return scenes.toArray(new Scene[scenes.size()]);
    }

    /**
     * Returns the Scenes stored in the Lighting controller corresponding to the set of
     * scene IDs. Any ID that is not matched to a Scene will be skipped. The returned
     * array may be empty.
     *
     * @param sceneIDs The IDs of the Scenes to retrieve
     *
     * @return Array of Scenes
     */
    public Scene[] getScenes(Collection<String> sceneIDs) {
        Scene[] scenes = getSceneCollectionManagerV2().getScenes(new ItemIDCollectionFilter<SceneV2>(sceneIDs));

        if (scenes == null || scenes.length == 0) {
            scenes = getSceneCollectionManager().getScenes(new ItemIDCollectionFilter<SceneV1>(sceneIDs));
        }

        return scenes;
    }

    /**
     * Returns a snapshot of all the Scenes stored in the Lighting controller that have received all
     * their data.
     * <p>
     * <b>Note: The contents of this array may change in subsequent calls to this method as new
     * scenes are created or existing scenes are deleted. This array may also be empty.</b>
     *
     * @return Array of initialized Scenes
     */
    public Scene[] getInitializedScenes() {
        Collection<Scene> scenes = new ArrayList<Scene>(getSceneCount());

        scenes.addAll(getSceneCollectionManager().getScenesCollection(new InitializedFilter<SceneV1>()));

        if (scenes.size() == 0) {
            scenes.addAll(getSceneCollectionManagerV2().getScenesCollection(new InitializedFilter<SceneV2>()));
        }

        return scenes.toArray(new Scene[scenes.size()]);
    }

    /**
     * Returns a reference to the Scene with the corresponding ID. If a match is not found for
     * the ID, this method will return null.
     *
     * @param sceneId The ID of the Scene
     *
     * @return Reference to a Scene or null.
     */
    public Scene getScene(String sceneId) {
        Scene scene = getSceneCollectionManagerV2().getScene(sceneId);

        return scene == null ? getSceneCollectionManager().getScene(sceneId) : scene;
    }

    /**
     * Returns the number of MasterScenes stored in the Lighting controller.
     *
     * @return Number of MasterScenes
     */
    public int getMasterSceneCount() {
        return getMasterSceneCollectionManager().size();
    }

    /**
     * Returns a snapshot of all the MasterScenes stored in the Lighting controller including master
     * scene that may not have received all data.
     * <p>
     * <b>Note: The contents of this array may change in subsequent calls to this method as new
     * master scenes are created or existing master scenes are deleted. This array may also be
     * empty.</b>
     *
     * @return Array of MasterScenes
     */
    public MasterScene[] getMasterScenes() {
        return getMasterSceneCollectionManager().getMasterScenes();
    }

    /**
     * Returns the MasterScenes stored in the Lighting controller corresponding to the set of
     * master scene IDs. Any ID that is not matched to a MasterScene will be skipped. The
     * returned array may be empty.
     *
     * @param masterSceneIDs The IDs of the MasterScenes to retrieve
     *
     * @return Array of MasterScenes
     */
    public MasterScene[] getMasterScenes(Collection<String> masterSceneIDs) {
        return getMasterSceneCollectionManager().getMasterScenes(new ItemIDCollectionFilter<MasterScene>(masterSceneIDs));
    }

    /**
     * Returns a snapshot of all the MasterScenes stored in the Lighting controller that have received all
     * their data.
     * <p>
     * <b>Note: The contents of this array may change in subsequent calls to this method as new
     * master scenes are created or existing master scenes are deleted. This array may also be
     * empty.</b>
     *
     * @return Array of initialized MasterScenes
     */
    public MasterScene[] getInitializedMasterScenes() {
        return getMasterSceneCollectionManager().getMasterScenes(new InitializedFilter<MasterScene>());
    }

    /**
     * Returns a reference to the MasterScene with the corresponding ID. If a match is not found for
     * the ID, this method will return null.
     *
     * @param masterSceneId The ID of the MasterScene
     *
     * @return Reference to a MasterScene or null.
     */
    public MasterScene getMasterScene(String masterSceneId) {
        return getMasterSceneCollectionManager().getMasterScene(masterSceneId);
    }

    /**
    * Returns the number of Effects (presets, transition effects, and pulse effects) stored in the
    * Lighting controller.
    *
    * @return Number of Effects
    */
    public int getEffectCount() {
        return getPresetCount() + getTransitionEffectCount() + getPulseEffectCount();
    }

    /**
     * Returns a snapshot of all the Effects (presets, transition effects, and pulse effects) stored in the
     * Lighting controller including effects that may not have received all data.
     * <p>
     * <b>Note: The contents of this array may change in subsequent calls to this method as new
     * effects are created or existing effects are deleted. This array may also be empty.</b>
     *
     * @return Array of Effects
     */
    public Effect[] getEffects() {
        return getEffects(null);
    }

    /**
     * Returns the Effects (presets, transition effects, and pulse effects) stored in the Lighting controller
     * corresponding to the set of effect IDs. Any ID that is not matched to an effect will be skipped.
     * The returned array may be empty.
     *
     * @param effectIDs The IDs of the Effects to retrieve
     *
     * @return Array of Effects
     */
    public Effect[] getEffects(Collection<String> effectIDs) {
        return getEffects(new ItemIDCollectionFilter<Preset>(effectIDs), new ItemIDCollectionFilter<TransitionEffect>(effectIDs), new ItemIDCollectionFilter<PulseEffect>(effectIDs));
    }

    /**
     * Returns a snapshot of all the Effects (presets, transition effects, and pulse effects) stored in the
     * Lighting controller that have received all their data.
     * <p>
     * <b>Note: The contents of this array may change in subsequent calls to this method as new
     * effects are created or existing effects are deleted. This array may also be empty.</b>
     *
     * @return Array of initialized Effects
     */
    public Effect[] getInitializedEffects() {
        return getEffects(new InitializedFilter<Preset>(), new InitializedFilter<TransitionEffect>(), new InitializedFilter<PulseEffect>());
    }

    /**
     * Returns a reference to the Effect (preset, transition effect, or pulse effect) with the corresponding
     * effect ID. If a match is not found for the ID, this method will return null.
     *
     * @param effectID The ID of the Effect
     *
     * @return Reference to an Effect or null.
     */
    public Effect getEffect(String effectID) {
        Effect effect = getPreset(effectID);

        if (effect == null) {
            effect = getTransitionEffect(effectID);
        }

        if (effect == null) {
            effect = getPulseEffect(effectID);
        }

        return effect;
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected Effect[] getEffects(LightingItemFilter<Preset> presetFilter, LightingItemFilter<TransitionEffect> transitionEffectFilter, LightingItemFilter<PulseEffect> pulseEffectFilter) {
        Collection<Effect> effects = new ArrayList<Effect>();

        effects.addAll(getPresetCollectionManager().getPresetsCollection(presetFilter));
        effects.addAll(getTransitionEffectCollectionManager().getTransitionEffectsCollection(transitionEffectFilter));
        effects.addAll(getPulseEffectCollectionManager().getPulseEffectsCollection(pulseEffectFilter));

        return effects.toArray(new Effect[effects.size()]);
    }

    /**
     * Returns reference to the lead controller in the Lighting system.
     *
     * @return Reference to lead lighting controller
     */
    public Controller getLeadController() {
        return getControllerManager().getLeader();
    }

    /**
     * Returns true if the lead controller service only supports the
     * lighting controller interface version 1.
     *
     * @return true for a V1 controller service, false for V2 or later
     */
    public boolean isControllerServiceLeaderV1() {
        return AllJoynManager.isControllerServiceLeaderV1();
    }

    /**
     * Specifies a listener to invoke once a connection to a lighting controller has been established.
     * After a connection is established, this listener will be invoked only one time.
     *
     * @param listener Listener to invoke on connection
     * @param delay Specifies a delay to wait before invoking the listener
     */
    public void postOnNextControllerConnection(final NextControllerConnectionListener listener, final int delay) {
        lightingManager.postOnNextControllerConnection(listener, delay);
    }

    /**
     * Specifies a runnable task to execute once a connection to a lighting controller has been
     * established. After a connection is established, this task will execute only one time.
     *
     * @param task Runnable task to run after connection
     * @param delay Specifies a delay to wait before executing the runnable
     */
    public void postOnNextControllerConnection(Runnable task, int delay) {
        lightingManager.postOnNextControllerConnection(task, delay);
    }

    /**
     * Asynchronously creates a Group on the Lighting controller. Once the group is successfully
     * created, the {@link GroupListener#onGroupInitialized(TrackingID, Group)} method will be
     * invoked and the tracking IDs will match.
     *
     * @param members Specifies the group's members
     * @param groupName Name of the Group
     *
     * @return TrackingID associated with the creation of the Group
     */
    public TrackingID createGroup(GroupMember[] members, String groupName) {
        TrackingID trackingId = new TrackingID(TrackingID.UNDEFINED);

        AllJoynManager.groupManager.createLampGroupWithTracking(
                trackingId,
                GroupMember.createLampGroup(members),
                groupName,
                getDefaultLanguage());

        return trackingId;
    }

    /**
     * Asynchronously creates a Preset on the Lighting controller. Once the preset is successfully
     * created, the {@link PresetListener#onPresetInitialized(TrackingID, Preset)} method will be
     * invoked and the tracking IDs will match.
     *
     * @param power Specifies the Power of the Preset's lamp state
     * @param color Specifies the Color of the Preset's lamp state
     * @param presetName Name of the Preset
     *
     * @return TrackingID associated with the creation of the Preset
     */
    public TrackingID createPreset(Power power, Color color, String presetName) {
        TrackingID trackingId = new TrackingID(TrackingID.UNDEFINED);

        AllJoynManager.presetManager.createPresetWithTracking(trackingId, LightingItemUtil.createLampStateFromView(
                power == Power.ON, color.getHue(), color.getSaturation(), color.getBrightness(), color.getColorTemperature()),
                presetName, getDefaultLanguage());

        return trackingId;
    }


    /**
     * Asynchronously creates a TransitionEffect on the Lighting controller. Once the transition
     * effects is successfully created, the {@link TransitionEffectListener#onTransitionEffectInitialized(TrackingID, TransitionEffect)}
     * method will be invoked and the tracking IDs will match.
     *
     * @param state Specifies the lamp state of the TransitionEffect
     * @param duration Specifies how long the TransitionEffect will take
     * @param effectName Name of the TransitionEffect
     *
     * @return TrackingID associated with the creation of the TransitionEffect
     */
    public TrackingID createTransitionEffect(LampState state, long duration, String effectName) {
        TrackingID trackingId = new TrackingID(TrackingID.UNDEFINED);

        if (state instanceof Preset) {
            AllJoynManager.transitionEffectManager.createTransitionEffect(trackingId,
                    LightingItemUtil.createTransitionEffect(((Preset)state).getPresetDataModel(), duration), effectName, getDefaultLanguage());
        } else {
            AllJoynManager.transitionEffectManager.createTransitionEffect(trackingId,
                    LightingItemUtil.createTransitionEffect(state.getPowerOn(), state.getColorHsvt(), duration),
                    effectName, getDefaultLanguage());
        }

        return trackingId;
    }


    /**
     * Asynchronously creates a PulseEffect on the Lighting controller. Once the pulse
     * effect is successfully created, the {@link PulseEffectListener#onPulseEffectInitialized(TrackingID, PulseEffect)}
     * method will be invoked and the tracking IDs will match.
     *
     * @param fromState Specifies the starting LampState of the PulseEffect
     * @param toState Specifies the ending LampState of the PulseEffect
     * @param period Specifies the period of the pulse effect (in ms). Period refers to the time duration between the start of two pulses
     * @param duration Specifies the duration of a single pulse (in ms). This must be less than the period
     * @param count Specifies the number of pulses
     * @param effectName Name of the PulseEffect
     *
     * @return TrackingID associated with the creation of the PulseEffect
     */
    public TrackingID createPulseEffect(LampState fromState, LampState toState, long period, long duration, long count, String effectName) {
        TrackingID trackingId = new TrackingID(TrackingID.UNDEFINED);

        if (fromState instanceof Preset && toState instanceof Preset) {
            AllJoynManager.pulseEffectManager.createPulseEffect(trackingId,
                    LightingItemUtil.createPulseEffect(((Preset)fromState).getPresetDataModel(), ((Preset)toState).getPresetDataModel(), period, duration, count),
                    effectName, getDefaultLanguage());
        } else {
            AllJoynManager.pulseEffectManager.createPulseEffect(trackingId,
                    LightingItemUtil.createPulseEffect(fromState.getPowerOn(), fromState.getColorHsvt(), toState.getPowerOn(), toState.getColorHsvt(), period, duration, count),
                    effectName, getDefaultLanguage());
        }

        return trackingId;
    }


    /**
     * Asynchronously creates a SceneElement on the Lighting controller. Once the scene
     * element is successfully created, the {@link SceneElementListener#onSceneElementInitialized(TrackingID, SceneElement)}
     * method will be invoked and the tracking IDs will match.
     *
     * @param effect Specifies the SceneElement's effect
     * @param members Specifies the GroupMembers for which the effect will be applied
     * @param sceneElementName Name of the SceneElement
     *
     * @return TrackingID associated with the creation of the SceneElement
     */
    public TrackingID createSceneElement(Effect effect, GroupMember[] members, String sceneElementName) {
        TrackingID trackingId = new TrackingID(TrackingID.UNDEFINED);

        AllJoynManager.sceneElementManager.createSceneElement(
                trackingId,
                LightingItemUtil.createSceneElement(effect.getId(), GroupMember.createLampGroup(members)),
                sceneElementName,
                getDefaultLanguage());

        return trackingId;
    }


    /**
     * Asynchronously creates a Scene on the Lighting controller. Once the scene
     * is successfully created, the {@link SceneListener#onSceneInitialized(TrackingID, Scene)}
     * method will be invoked and the tracking IDs will match.
     *
     * @param sceneElements Specifies the SceneElements that belong to the Scene
     * @param sceneName Name of the Scene
     *
     * @return TrackingID associated with the creation of the Scene
     */
    public TrackingID createScene(SceneElement[] sceneElements, String sceneName) {
        TrackingID trackingId = new TrackingID(TrackingID.UNDEFINED);

        String[] sceneElementIds = new String[sceneElements.length];
        for (int i = 0; i < sceneElements.length; i++) {
            sceneElementIds[i] = sceneElements[i].getId();
        }

        AllJoynManager.sceneManager.createSceneWithSceneElements(trackingId, LightingItemUtil.createSceneWithSceneElements(sceneElementIds), sceneName, getDefaultLanguage());

        return trackingId;
    }


    /**
     * Asynchronously creates a MasterScene on the Lighting controller. Once the master
     * scene is successfully created, the {@link MasterSceneListener#onMasterSceneInitialized(TrackingID, MasterScene)}
     * method will be invoked and the tracking IDs will match.
     *
     * @param scenes Specifies the Scenes that belong to the MasterScene
     * @param masterSceneName Name of the MasterScene
     *
     * @return TrackingID associated with the creation of the MasterScene
     */
    public TrackingID createMasterScene(Scene[] scenes, String masterSceneName) {
        TrackingID trackingId = new TrackingID(TrackingID.UNDEFINED);

        String[] sceneIds = new String[scenes.length];
        for (int i = 0; i < scenes.length; i++) {
            sceneIds[i] = scenes[i].getId();
        }

        AllJoynManager.masterSceneManager.createMasterSceneWithTracking(trackingId, LightingItemUtil.createMasterScene(sceneIds), masterSceneName, getDefaultLanguage());

        return trackingId;
    }


    /**
     * Adds a global listener to receive all Lighting system events associated with the provided
     * listener's type. Adding multiple listeners of various types is supported.
     * <p>
     * @param listener Listener that will receive all Lighting system events.
     */
    public void addListener(LightingListener listener) {
        if (listener instanceof LampListener) {
            addLampListener((LampListener) listener);
        }

        if (listener instanceof GroupListener) {
            addGroupListener((GroupListener) listener);
        }

        if (listener instanceof PresetListener) {
            addPresetListener((PresetListener) listener);
        }

        if (listener instanceof TransitionEffectListener) {
            addTransitionEffectListener((TransitionEffectListener) listener);
        }

        if (listener instanceof PulseEffectListener) {
            addPulseEffectListener((PulseEffectListener) listener);
        }

        if (listener instanceof SceneElementListener) {
            addSceneElementListener((SceneElementListener) listener);
        }

        if (listener instanceof SceneListener) {
            addSceneListener((SceneListener) listener);
        }

        if (listener instanceof MasterSceneListener) {
            addMasterSceneListener((MasterSceneListener) listener);
        }

        if (listener instanceof ControllerListener) {
            addControllerListener((ControllerListener) listener);
        }
    }


    /**
     * Adds a global listener to receive all Lamp events.
     *
     * @param listener Listener that will receive all Lamp events.
     */
    public void addLampListener(LampListener listener) {
        getLampCollectionManager().addListener(listener);
    }


    /**
     * Adds a global listener to receive all Group events.
     *
     * @param listener Listener that will receive all Group events.
     */
    public void addGroupListener(GroupListener listener) {
        getGroupCollectionManager().addListener(listener);
    }


    /**
     * Adds a global listener to receive all Preset events.
     *
     * @param listener Listener that will receive all Preset events.
     */
    public void addPresetListener(PresetListener listener) {
        getPresetCollectionManager().addListener(listener);
    }


    /**
     * Adds a global listener to receive all TransitionEffect events.
     *
     * @param listener Listener that will receive all TransitionEffect events.
     */
    public void addTransitionEffectListener(TransitionEffectListener listener) {
        getTransitionEffectCollectionManager().addListener(listener);
    }


    /**
     * Adds a global listener to receive all PulseEffect events.
     *
     * @param listener Listener that will receive all PulseEffect events.
     */
    public void addPulseEffectListener(PulseEffectListener listener) {
        getPulseEffectCollectionManager().addListener(listener);
    }


    /**
     * Adds a global listener to receive all SceneElement events.
     *
     * @param listener Listener that will receive all SceneElement events.
     */
    public void addSceneElementListener(SceneElementListener listener) {
        getSceneElementCollectionManager().addListener(listener);
    }


    /**
     * Adds a global listener to receive all Scene events.
     *
     * @param listener Listener that will receive all Scene events.
     */
    public void addSceneListener(SceneListener listener) {
        getSceneCollectionManager().addListener(listener);
        getSceneCollectionManagerV2().addListener(listener);
    }


    /**
     * Adds a global listener to receive all MasterScene events.
     *
     * @param listener Listener that will receive all MasterScene events.
     */
    public void addMasterSceneListener(MasterSceneListener listener) {
        getMasterSceneCollectionManager().addListener(listener);
    }


    /**
     * Adds a global listener to receive all Controller events.
     *
     * @param listener Listener that will receive all Controller events.
     */
    public void addControllerListener(ControllerListener listener) {
        getControllerManager().addListener(listener);
    }


    /**
     * Removes a global listener that receives all Lighting System events associated with the
     * provided listener's type.
     *
     * @param listener Listener that receives all Lighting System events.
     */
    public void removeListener(LightingListener listener) {
        if (listener instanceof LampListener) {
            removeLampListener((LampListener) listener);
        }

        if (listener instanceof GroupListener) {
            removeGroupListener((GroupListener) listener);
        }

        if (listener instanceof PresetListener) {
            removePresetListener((PresetListener) listener);
        }

        if (listener instanceof TransitionEffectListener) {
            removeTransitionEffectListener((TransitionEffectListener) listener);
        }

        if (listener instanceof PulseEffectListener) {
            removePulseEffectListener((PulseEffectListener) listener);
        }

        if (listener instanceof SceneElementListener) {
            removeSceneElementListener((SceneElementListener) listener);
        }

        if (listener instanceof SceneListener) {
            removeSceneListener((SceneListener) listener);
        }

        if (listener instanceof MasterSceneListener) {
            removeMasterSceneListener((MasterSceneListener) listener);
        }

        if (listener instanceof ControllerListener) {
            removeControllerListener((ControllerListener) listener);
        }
    }


    /**
     * Removes a global listener that receives all Lamp events.
     *
     * @param listener Listener that receives all Lamp events.
     */
    public void removeLampListener(LampListener listener) {
        getLampCollectionManager().removeListener(listener);
    }


    /**
     * Removes a global listener that receives all Group events.
     *
     * @param listener Listener that receives all Group events.
     */
    public void removeGroupListener(GroupListener listener) {
        getGroupCollectionManager().removeListener(listener);
    }


    /**
     * Removes a global listener that receives all Preset events.
     *
     * @param listener Listener that receives all Preset events.
     */
    public void removePresetListener(PresetListener listener) {
        getPresetCollectionManager().removeListener(listener);
    }


    /**
     * Removes a global listener that receives all TransitionEffect events.
     *
     * @param listener Listener that receives all TransitionEffect events.
     */
    public void removeTransitionEffectListener(TransitionEffectListener listener) {
        getTransitionEffectCollectionManager().removeListener(listener);
    }


    /**
     * Removes a global listener that receives all PulseEffect events.
     *
     * @param listener Listener that receives all PulseEffect events.
     */
    public void removePulseEffectListener(PulseEffectListener listener) {
        getPulseEffectCollectionManager().removeListener(listener);
    }


    /**
     * Removes a global listener that receives all SceneElement events.
     *
     * @param listener Listener that receives all SceneElement events.
     */
    public void removeSceneElementListener(SceneElementListener listener) {
        getSceneElementCollectionManager().removeListener(listener);
    }


    /**
     * Removes a global listener that receives all Scene events.
     *
     * @param listener Listener that receives all Scene events.
     */
    public void removeSceneListener(SceneListener listener) {
        getSceneCollectionManager().removeListener(listener);
        getSceneCollectionManagerV2().removeListener(listener);
    }


    /**
     * Removes a global listener that receives all MasterScene events.
     *
     * @param listener Listener that receives all MasterScene events.
     */
    public void removeMasterSceneListener(MasterSceneListener listener) {
        getMasterSceneCollectionManager().removeListener(listener);
    }


    /**
     * Removes a global listener that receives all Controller events.
     *
     * @param listener Listener that receives all Controller events.
     */
    public void removeControllerListener(ControllerListener listener) {
        getControllerManager().removeListener(listener);
    }


    /**
     * Specifies the default language used by the Lighting system.
     * <p>
     * <b>Note: If this method is never called, the default language is English ("en").</b>
     *
     * @param language Language tag specifying the default language for the Lighting system
     */
    public void setDefaultLanguage(String language) {
        if (language != null) {
            defaultLanguage = language;
        }
    }


    /**
     * Returns the default language used by the Lighting system.
     *
     * @return Language tag specifying the default language for the Lighting system
     */
    public String getDefaultLanguage() {
        return defaultLanguage;
    }


    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected LampCollectionManager<Lamp, LightingItemErrorEvent> getLampCollectionManager() {
        return lightingManager.getLampCollectionManager();
    }


    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected GroupCollectionManager<Group, LightingItemErrorEvent> getGroupCollectionManager() {
        return lightingManager.getGroupCollectionManager();
    }


    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected PresetCollectionManager<Preset, LightingItemErrorEvent> getPresetCollectionManager() {
        return lightingManager.getPresetCollectionManager();
    }


    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected TransitionEffectCollectionManager<TransitionEffect, LightingItemErrorEvent> getTransitionEffectCollectionManager() {
        return lightingManager.getTransitionEffectCollectionManager();
    }


    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected PulseEffectCollectionManager<PulseEffect, LightingItemErrorEvent> getPulseEffectCollectionManager() {
        return lightingManager.getPulseEffectCollectionManager();
    }


    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected SceneElementCollectionManager<SceneElement, LightingItemErrorEvent> getSceneElementCollectionManager() {
        return lightingManager.getSceneElementCollectionManager();
    }


    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected SceneCollectionManagerV1<SceneV1, LightingItemErrorEvent> getSceneCollectionManager() {
        return lightingManager.getSceneCollectionManagerV1();
    }


    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected SceneCollectionManagerV2<SceneV2, LightingItemErrorEvent> getSceneCollectionManagerV2() {
        return lightingManager.getSceneCollectionManagerV2();
    }


    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected MasterSceneCollectionManager<MasterScene, LightingItemErrorEvent> getMasterSceneCollectionManager() {
        return lightingManager.getMasterSceneCollectionManager();
    }


    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected ControllerCollectionManager<Controller, LightingItemErrorEvent> getControllerManager() {
        return lightingManager.getControllerCollectionManager();
    }


    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected LightingSystemManager<Lamp, Group, Preset, TransitionEffect, PulseEffect, SceneElement, SceneV1, SceneV2, MasterScene, Controller, LightingItemErrorEvent> getLightingSystemManager() {
        return lightingManager;
    }}
