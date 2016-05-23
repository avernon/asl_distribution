/* Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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
import java.util.Arrays;
import java.util.Collection;
import java.util.HashSet;
import java.util.Set;

import org.allseen.lsf.LampState;
import org.allseen.lsf.sdk.manager.AllJoynManager;
import org.allseen.lsf.sdk.model.AllLampsDataModel;
import org.allseen.lsf.sdk.model.ColorItemDataModel;
import org.allseen.lsf.sdk.model.ColorStateConverter;
import org.allseen.lsf.sdk.model.GroupDataModel;
import org.allseen.lsf.sdk.model.LightingItemUtil;

/**
 * This class represents a Group definition in the lighting controller. This class
 * provides an interface to perform Group operations. Supported operations include changing
 * color and power state, renaming, applying effects and presets, adding and removing group
 * members, and deleting the group. Groups are considered fully initialized when the name
 * and the groups members have been received. Groups are still operational even in the
 * uninitialized state.
 * <p>
 * <b>Note: This class is not meant to be instantiated directly. Groups should be retrieved
 * from the LightingDirector using the {@link LightingDirector#getGroups()} method.</b>
 * <p>
 * <b>Note: This class does not support Group creation. See {@link LightingDirector#createGroup(GroupMember[], String)}.</b>
 */
public class Group extends GroupMember implements DeletableItem {
    /**
     * Specifies the default name of the Group.
     *
     * @param defaultName Default name of the Group
     */
    public static void setDefaultName(String defaultName) {
        if (defaultName != null) {
            GroupDataModel.defaultName = defaultName;
        }
    }

    protected GroupDataModel groupModel;

    /**
     * Constructs a Group using the specified ID.
     * <p>
     * <b>WARNING: This method is intended to be used internally. Client software should not instantiate
     * Groups directly, but should instead get them from the {@link LightingDirector} using the
     * {@link LightingDirector#getGroups()} method.</b>
     *
     * @param groupID The ID of the group
     */
    protected Group(String groupID) {
        this(groupID, null);
    }

    /**
     * Constructs a Group using the specified ID and name.
     * <p>
     * <b>WARNING: This method is intended to be used internally. Client software should not instantiate
     * Groups directly, but should instead get them from the {@link LightingDirector} using the
     * {@link LightingDirector#getGroups()} method.</b>
     *
     * @param groupID The ID of the group
     * @param groupName The name of the group
     */
    protected Group(String groupID, String groupName) {
        super();

        groupModel = AllLampsDataModel.ALL_LAMPS_GROUP_ID.equals(groupID) ? AllLampsDataModel.instance : new GroupDataModel(groupID, groupName);
    }

    /**
     * Changes the power state of the current Group.
     *
     * @param powerOn True for on, false for off
     */
    @Override
    public void setPowerOn(boolean powerOn) {
        String errorContext = "Group.setPowerOn() error";

        postErrorIfFailure(errorContext,
                AllJoynManager.groupManager.transitionLampGroupStateOnOffField(groupModel.id, powerOn));
    }

    /**
     * Changes the color state of the current Group to the provided HSVT color.
     * <p>
     * <b>Note: If the provided HSVT values are outside the expected range, they will be normalized to the
     * expected range</b>
     *
     * @param hueDegrees The hue component of the desired color (0-360)
     * @param saturationPercent The saturation component of the desired color (0-100)
     * @param brightnessPercent The brightness component of the desired color (0-100)
     * @param colorTempDegrees The color temperature component of the desired color (1000-20000)
     */
    @Override
    public void setColorHsvt(int hueDegrees, int saturationPercent, int brightnessPercent, int colorTempDegrees) {
        LampState lampState = new LampState(groupModel.getState());

        ColorStateConverter.convertViewToModel(hueDegrees, saturationPercent, brightnessPercent, colorTempDegrees, lampState);

        String errorContext = "Group.setColorHsvt() error";

        postErrorIfFailure(errorContext,
                AllJoynManager.groupManager.transitionLampGroupState(groupModel.id, lampState, 0));
    }

    /**
     * Changes the color state of the current Group to the provided hue.
     * <p>
     * <b>Note: If the provided hue values are outside the expected range, they will be normalized to the
     * expected range</b>
     *
     * @param hueDegrees The hue component of the desired color (0-360)
     */
    @Override
    public void setHue(int hueDegrees) {
        String errorContext = "Group.setHue() error";

        long scaledHue = ColorStateConverter.convertHueViewToModel(hueDegrees);

        postErrorIfFailure(errorContext,
                AllJoynManager.groupManager.transitionLampGroupStateHueField(groupModel.id, scaledHue, 0));
    }

    /**
     * Changes the color state of the current Group to the provided saturation.
     * <p>
     * <b>Note: If the provided saturation values are outside the expected range, they will be normalized to the
     * expected range</b>
     *
     * @param saturationPercent The saturation component of the desired color (0-100)
     */
    @Override
    public  void setSaturation(int saturationPercent) {
        String errorContext = "Group.setSaturation() error";

        long scaledSaturation = ColorStateConverter.convertSaturationViewToModel(saturationPercent);

        postErrorIfFailure(errorContext,
                AllJoynManager.groupManager.transitionLampGroupStateSaturationField(groupModel.id, scaledSaturation, 0));
    }

    /**
     * Changes the color state of the current Group to the provided brightness.
     * <p>
     * <b>Note: If the provided brightness values are outside the expected range, they will be normalized to the
     * expected range</b>
     *
     * @param brightnessPercent The brightness component of the desired color (0-100)
     */
    @Override
    public  void setBrightness(int brightnessPercent) {
        String errorContext = "Group.setBrightness() error";

        long scaledBrightness = ColorStateConverter.convertBrightnessViewToModel(brightnessPercent);

        postErrorIfFailure(errorContext,
                AllJoynManager.groupManager.transitionLampGroupStateBrightnessField(groupModel.id, scaledBrightness, 0));
    }

    /**
     * Changes the color state of the current Group to the provided color temperature.
     * <p>
     * <b>Note: If the provided color temperature values are outside the expected range, they will be normalized to the
     * expected range</b>
     *
     * @param colorTempDegrees The color temperature component of the desired color (1000-20000)
     */
    @Override
    public  void setColorTemperature(int colorTempDegrees) {
        String errorContext = "Group.setColorTemp() error";

        long scaledColorTemp = ColorStateConverter.convertColorTempViewToModel(colorTempDegrees);

        postErrorIfFailure(errorContext,
                AllJoynManager.groupManager.transitionLampGroupStateColorTempField(groupModel.id, scaledColorTemp, 0));
    }

    /**
     * Adds a member to the current Group.
     *
     * @param member The GroupMember object to be added to the Group
     */
    public void add(GroupMember member) {
        String errorContext = "Group.add() error";

        if (postInvalidArgIfNull(errorContext, member)) {
            Set<String> lamps = new HashSet<String>(Arrays.asList(groupModel.members.getLamps()));
            Set<String> groups = new HashSet<String>(Arrays.asList(groupModel.members.getLampGroups()));

            if (member instanceof Lamp) {
                lamps.add(member.getId());
            } else if (member instanceof Group) {
                groups.add(member.getId());
            }

            postErrorIfFailure(errorContext,
                    AllJoynManager.groupManager.updateLampGroup(groupModel.id, LightingItemUtil.createLampGroup(
                            lamps.toArray(new String[lamps.size()]), groups.toArray(new String[groups.size()]))));
        }
    }

    /**
     * Removes a member from the current Group.
     *
     * @param member The GroupMember object to be removed from the Group
     */
    public void remove(GroupMember member) {
        String errorContext = "Group.remove() error";

        if (postInvalidArgIfNull(errorContext, member)) {
            Set<String> lamps = new HashSet<String>(Arrays.asList(groupModel.members.getLamps()));
            Set<String> groups = new HashSet<String>(Arrays.asList(groupModel.members.getLampGroups()));


            boolean didRemove = lamps.remove(member.getId()) || groups.remove(member.getId());

            if (didRemove) {
                postErrorIfFailure(errorContext,
                        AllJoynManager.groupManager.updateLampGroup(groupModel.id, LightingItemUtil.createLampGroup(
                                lamps.toArray(new String[lamps.size()]), groups.toArray(new String[groups.size()]))));
            }
        }
    }

    /**
     * Replaces the current Group memebers with the provided GroupMember array.
     *
     * @param members The array of GroupMembers
     */
    public void modify(GroupMember[] members) {
        String errorContext = "Group.modify() error";

        if (postInvalidArgIfNull(errorContext, members)) {
            postErrorIfFailure(errorContext,
                    AllJoynManager.groupManager.updateLampGroup(groupModel.id, GroupMember.createLampGroup(members)));
        }
    }

    /**
     * Permanently deletes the current Group from the lighting controller.
     * <p>
     * <b>Note: You cannot delete a group that is a member of another group. The dependence must
     * be deleted first.</b>
     */
    @Override
    public void delete() {
        String errorContext = "Group.delete() error";

        postErrorIfFailure(errorContext,
                AllJoynManager.groupManager.deleteLampGroup(groupModel.id));
    }

    /**
     * Applies the provided Preset to the current Group.
     *
     * @param preset Preset to apply to the current Group
     */
    @Override
    public void applyPreset(Preset preset) {
        String errorContext = "Group.applyPreset() error";

        if (postInvalidArgIfNull(errorContext, preset)) {
            postErrorIfFailure(errorContext,
                    AllJoynManager.groupManager.transitionLampGroupStateToPreset(groupModel.id, preset.getPresetDataModel().id, 0));
        }
    }

    /**
     * Applies the provided Effect to the current Group.
     *
     * @param effect Effect to apply to the current Group
     */
    @Override
    public void applyEffect(Effect effect) {
        String errorCotext = "Group.applyEffect() error";

        if (postInvalidArgIfNull(errorCotext, effect)) {
            if (effect instanceof Preset) {
                applyPreset((Preset) effect);
            } else if (effect instanceof TransitionEffect) {
                postErrorIfFailure(errorCotext,
                        AllJoynManager.transitionEffectManager.applyTransitionEffectOnLampGroups(effect.getId(), new String [] { groupModel.id }));
            } else if (effect instanceof PulseEffect) {
                postErrorIfFailure(errorCotext,
                        AllJoynManager.pulseEffectManager.applyPulseEffectOnLampGroups(effect.getId(), new String [] { groupModel.id }));
            }
        }
    }

    /**
     * Renames the current Group using the provided name.
     *
     * @param groupName The new name for the Group
     */
    @Override
    public void rename(String groupName) {
        String errorContext = "Group.rename() error";

        if (postInvalidArgIfNull(errorContext, groupName)) {
            postErrorIfFailure(errorContext,
                    AllJoynManager.groupManager.setLampGroupName(groupModel.id, groupName, LightingDirector.get().getDefaultLanguage()));
        }
    }

    /**
     * Tests to see if the current Group contains the specified Lighting item.
     *
     * @param item Lighting item to be confirmed present in the Group
     *
     * @return Returns true if the Group contains the specified Lighting item, false otherwise
     */
    @Override
    public boolean hasComponent(LightingItem item) {
        String errorContext = "Group.hasComponent() error";
        return postInvalidArgIfNull(errorContext, item) ? hasLampID(item.getId()) || hasGroupID(item.getId()) : false;
    }

    /**
     * Tests to see if the current Group contains the specified Lamp.
     *
     * @param lamp The Lamp to be confirmed present in the Group
     *
     * @return Returns true if the Group contains the specified Lamp, false otherwise
     */
    public boolean hasLamp(Lamp lamp) {
        String errorContext = "Group.hasLamp() error";
        return postInvalidArgIfNull(errorContext, lamp) ? hasLampID(lamp.getId()) : false;
    }

    /**
     * Tests to see if the current Group contains the specified Group.
     *
     * @param group The Group to be confirmed present in the Group
     *
     * @return Returns true if the Group contains the specified Group, false otherwise
     */
    public boolean hasGroup(Group group) {
        String errorContext = "Group.hasGroup() error";
        return postInvalidArgIfNull(errorContext, group) ? hasGroupID(group.getId()) : false;
    }

    /**
     * Tests to see if the current Group contains the specified Lamp ID.
     *
     * @param lampID The Lamp ID to be confirmed present in the Group.
     *
     * @return Returns true if the Group contains the specified lamp ID, false otherwise
     */
    public boolean hasLampID(String lampID) {
        return groupModel.containsLamp(lampID);
    }

    /**
     * Tests to see if the current Group contains the specified Group ID.
     *
     * @param groupID The Group ID to be confirmed present in the Group.
     *
     * @return Returns true if the Group contains the specified group ID, false otherwise
     */
    public boolean hasGroupID(String groupID) {
        return groupModel.containsGroup(groupID);
    }

    /**
     * Returns an array of Lamps that are members of the current Group.
     *
     * @return Array of all Lamps in the current Group
     */
    public Lamp[] getLamps() {
        return LightingDirector.get().getLamps(getLampIDs());
    }

    /**
     * Returns an array of Groups that are members of the current Group.
     *
     * @return Array of all Groups in the current Group
     */
    public Group[] getGroups() {
        return LightingDirector.get().getGroups(getGroupIDs());
    }

    /**
     * Returns an array of Lamp IDs that are members of the current Group.
     *
     * @return Array of all Lamp IDs in the current Group
     */
    public Collection<String> getLampIDs() {
        return groupModel.getLamps();
    }

    /**
     * Returns an array of Group IDs that are members of the current Group.
     *
     * @return Array of all Group IDs in the current Group
     */
    public Collection<String> getGroupIDs() {
        return groupModel.getGroups();
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected void addTo(Collection<String> lampIDs, Collection<String> groupIDs) {
        groupIDs.add(getId());
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected Collection<LightingItem> getDependentCollection() {
        LightingDirector director = LightingDirector.get();
        Collection<LightingItem> dependents = new ArrayList<LightingItem>();

        dependents.addAll(director.getGroupCollectionManager().getGroupCollection(new HasComponentFilter<Group>(Group.this)));
        dependents.addAll(director.getSceneCollectionManager().getScenesCollection(new HasComponentFilter<SceneV1>(Group.this)));
        dependents.addAll(director.getSceneElementCollectionManager().getSceneElementsCollection(new HasComponentFilter<SceneElement>(Group.this)));

        return dependents;
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected Collection<LightingItem> getComponentCollection() {
        Collection<LightingItem> components = new ArrayList<LightingItem>();

        components.addAll(Arrays.asList(getLamps()));
        components.addAll(Arrays.asList(getGroups()));

        return components;
    }

    /**
     * Returns the absolute minimum color temperature value supported by the Lamps in the current Group.
     *
     * @return The Lamps minimum color temperature value
     */
    public int getColorTempMin() {
        return getGroupDataModel().viewColorTempMin;
    }

    /**
     * Returns the absolute maximum color temperature value supported by the Lamps in the current Group.
     *
     * @return The Lamps maximum color temperature value
     */
    public int getColorTempMax() {
        return getGroupDataModel().viewColorTempMax;
    }

    /**
     * Tests to see if the current Group is the AllLampsGroup.
     *
     * @return Returns true if the current Group is the AllLampsGroup, false otherwise
     */
    public boolean isAllLampsGroup() {
        return AllLampsDataModel.ALL_LAMPS_GROUP_ID.equals(groupModel.id);
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected ColorItemDataModel getColorDataModel() {
        return getGroupDataModel();
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected GroupDataModel getGroupDataModel() {
        return groupModel;
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected void postError(final String name, final ResponseCode status) {
        LightingDirector.get().getLightingSystemManager().getQueue().post(new Runnable() {
            @Override
            public void run() {
                LightingDirector.get().getGroupCollectionManager().sendErrorEvent(name, status, getId());
            }
        });
    }
}
