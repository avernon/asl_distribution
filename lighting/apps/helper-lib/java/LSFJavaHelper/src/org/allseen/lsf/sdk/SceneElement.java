/*
 * Copyright AllSeen Alliance. All rights reserved.
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
import java.util.HashSet;
import java.util.Set;

import org.allseen.lsf.sdk.manager.AllJoynManager;
import org.allseen.lsf.sdk.model.LightingItemDataModel;
import org.allseen.lsf.sdk.model.LightingItemUtil;
import org.allseen.lsf.sdk.model.SceneElementDataModel;
import org.allseen.lsf.sdk.model.SceneElementDataModelV2;

/**
 * This class represents a SceneElement definition in the lighting controller. This class
 * provides an interface to perform SceneElement operations. Supported operations include
 * modifying the scene element members and effect, applying the scene element, renaming, and
 * deleting the scene element. Scene elements encapsulate an effect and a set of lamps and/or
 * groups. Scene elements apply their effect to their lamps and groups. Scene elements are
 * considered fully initialized when the name, lamp and group members, and the effect have been
 * received. Scene elements are still operational and can still be applied even in the
 * uninitialized state.
 * <p>
 * <b>Note: This class is not meant to be instantiated directly. SceneElements should be retrieved
 * from the LightingDirector using the {@link LightingDirector#getSceneElements()} method.</b>
 * <p>
 * <b>Note: This class does not support SceneElement creation. See {@link LightingDirector#createSceneElement(Effect, GroupMember[], String)}.</b>
 */
public class SceneElement extends SceneItem {
    public static void setDefaultName(String defaultName) {
        if (defaultName != null) {
            SceneElementDataModel.defaultName = defaultName;
        }
    }

    protected SceneElementDataModelV2 sceneElementModel;

    /**
     * Constructs a SceneElement using the specified ID.
     * <p>
     * <b>WARNING: This method is intended to be used internally. Client software should not instantiate
     * SceneElements directly, but should instead get them from the {@link LightingDirector} using the
     * {@link LightingDirector#getSceneElements()} method.</b>
     *
     * @param sceneElementId The ID of the scene element
     */
    protected SceneElement(String sceneElementId) {
        this(sceneElementId, null);
    }

    /**
     * Constructs a SceneElement using the specified ID and name.
     * <p>
     * <b>WARNING: This method is intended to be used internally. Client software should not instantiate
     * SceneElements directly, but should instead get them from the {@link LightingDirector} using the
     * {@link LightingDirector#getSceneElements()} method.</b>
     *
     * @param sceneElementId The ID of the scene element
     * @param sceneElementName The name of the scene element
     */
    protected SceneElement(String sceneElementId, String sceneElementName) {
        super();

        sceneElementModel = new SceneElementDataModelV2(sceneElementId, sceneElementName);
    }

    /**
     * Applies the current SceneElement in the Lighting system.
     */
    @Override
    public void apply() {
        String errorContext = "SceneElement.apply() error";

        postErrorIfFailure(errorContext,
                AllJoynManager.sceneElementManager.applySceneElement(sceneElementModel.id));
    }

    /**
     * Modifies the Effect and GroupMembers of the current SceneElement using the provided parameters
     *
     * @param effect The new Effect.
     * @param members The new GroupMembers.
     */
    public void modify(Effect effect, GroupMember[] members) {
        String errorContext = "SceneElement.modify() error";

        if (postInvalidArgIfNull(errorContext, effect) && postInvalidArgIfNull(errorContext, members)) {
            postErrorIfFailure(errorContext,
                    AllJoynManager.sceneElementManager.updateSceneElement(sceneElementModel.id, LightingItemUtil.createSceneElement(effect.getId(), GroupMember.createLampGroup(members))));
        }
    }

    /**
     * Adds a member to the current SceneElement.
     *
     * @param member The GroupMember object to be added to the SceneElement
     */
    public void add(GroupMember member) {
        String errorContext = "SceneElement.add() error";

        if (postInvalidArgIfNull(errorContext, member)) {
            Set<String> lamps = new HashSet<String>(sceneElementModel.getLamps());
            Set<String> groups = new HashSet<String>(sceneElementModel.getGroups());

            if (member instanceof Lamp) {
                lamps.add(member.getId());
            } else if (member instanceof Group) {
                groups.add(member.getId());
            }

            postErrorIfFailure(errorContext,
                    AllJoynManager.sceneElementManager.updateSceneElement(sceneElementModel.id, LightingItemUtil.createSceneElement(
                            sceneElementModel.getEffectId(), lamps.toArray(new String[lamps.size()]), groups.toArray(new String[groups.size()]))));

        }
    }

    /**
     * Removes a member from the current SceneElement.
     *
     * @param member The GroupMember object to be removed from the SceneElement
     */
    public void remove(GroupMember member) {
        String errorContext = "SceneElement.remove() error";

        if (postInvalidArgIfNull(errorContext, member)) {
            Set<String> lamps = new HashSet<String>(sceneElementModel.getLamps());
            Set<String> groups = new HashSet<String>(sceneElementModel.getGroups());

            boolean didRemove = lamps.remove(member.getId()) || groups.remove(member.getId());

            if (didRemove) {
                postErrorIfFailure(errorContext,
                        AllJoynManager.sceneElementManager.updateSceneElement(sceneElementModel.id, LightingItemUtil.createSceneElement(
                                sceneElementModel.getEffectId(), lamps.toArray(new String[lamps.size()]), groups.toArray(new String[groups.size()]))));
            }
        }
    }

    /**
     * Renames the current SceneElement using the provided name.
     *
     * @param sceneElementName The new name for the SceneElement
     */
    @Override
    public void rename(String sceneElementName) {
        String errorContext = "SceneElement.rename() error";

        if (postInvalidArgIfNull(errorContext, sceneElementName)) {
            postErrorIfFailure(errorContext,
                    AllJoynManager.sceneElementManager.setSceneElementName(sceneElementModel.id, sceneElementName, LightingDirector.get().getDefaultLanguage()));
        }
    }

    /**
     * Permanently deletes the current SceneElement from the lighting controller.
     * <p>
     * <b>Note: You cannot delete a scene element that is used by a scene. The dependency
     * must be deleted first.</b>
     */
    @Override
    public void delete() {
        String errorContext = "SceneElement.delete() error";

        postErrorIfFailure(errorContext,
                AllJoynManager.sceneElementManager.deleteSceneElement(sceneElementModel.id));
    }

    /**
     * Returns the effect associated with the current SceneElement.
     *
     * @return Reference to Effect
     */
    public Effect getEffect() {
        return LightingDirector.get().getEffect(sceneElementModel.getEffectId());
    }

    /**
     * Returns the Lamps associated with the current SceneElement.
     *
     * @return Arrays of Lamps associated with the SceneElement
     */
    public Lamp[] getLamps() {
        return LightingDirector.get().getLamps(sceneElementModel.getLamps());
    }

    /**
     * Returns the Groups associated with the current SceneElement.
     *
     * @return Arrays of Groups associated with the SceneElement
     */
    public Group[] getGroups() {
        return LightingDirector.get().getGroups(sceneElementModel.getGroups());
    }

    /**
     * Returns the ID of the Effect associated with the current SceneElement.
     *
     * @return ID of the SceneElement Effect
     */
    public String getEffectID() {
        return sceneElementModel.getEffectId();
    }

    /**
     * Returns the lamp IDs associated with the current SceneElement.
     *
     * @return Arrays of lamp IDs associated with the SceneElement
     */
    public Collection<String> getLampIDs() {
        return sceneElementModel.getLamps();
    }

    /**
     * Returns the group IDs associated with the current SceneElement.
     *
     * @return Arrays of group IDs associated with the SceneElement
     */
    public Collection<String> getGroupIDs() {
        return sceneElementModel.getGroups();
    }

    /**
     * Tests to see if the current SceneElement contains the provided Lighting item.
     *
     * @param item Lighting item to be confirmed present in the SceneElement
     *
     * @return Returns true if the SceneElement contains Lighting item, false otherwise
     */
    @Override
    public boolean hasComponent(LightingItem item) {
        String errorContext = "SceneElement.hasComponent() error";
        return postInvalidArgIfNull(errorContext, item) ? hasEffect(item.getId()) || hasLamp(item.getId()) || hasGroup(item.getId()) : false;
    }

    /**
     * Tests to see if the current SceneElement contains the specified Effect.
     *
     * @param effect The Effect to be confirmed a component of the SceneElement.
     *
     * @return Return true if the SceneElement contains Effect, false otherwise.
     */
    public boolean hasEffect(Effect effect) {
        String errorContext = "SceneElement.hasEffect() error";
        return postInvalidArgIfNull(errorContext, effect) ? hasEffect(effect.getId()) : false;
    }

    /**
     * Tests to see if the current SceneElement contains the specified Lamp.
     *
     * @param lamp The Lamp to be confirmed a component of the SceneElement.
     *
     * @return Return true if the SceneElement contains Lamp, false otherwise.
     */
    public boolean hasLamp(Lamp lamp) {
        String errorContext = "Group.hasLamp() error";
        return postInvalidArgIfNull(errorContext, lamp) ? hasLamp(lamp.getId()) : false;
    }

    /**
     * Tests to see if the current SceneElement contains the specified Group.
     *
     * @param group The Group to be confirmed a component of the SceneElement.
     *
     * @return Return true if the SceneElement contains Group, false otherwise.
     */
    public boolean hasGroup(Group group) {
        String errorContext = "SceneElement.hasGroup() error";
        return postInvalidArgIfNull(errorContext, group) ? hasGroup(group.getId()) : false;
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected boolean hasEffect(String effectID) {
        return sceneElementModel.containsEffect(effectID);
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected boolean hasLamp(String lampID) {
        return sceneElementModel.containsLamp(lampID);
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected boolean hasGroup(String groupID) {
        return sceneElementModel.containsGroup(groupID);
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected Collection<LightingItem> getDependentCollection() {
        LightingDirector director = LightingDirector.get();
        Collection<LightingItem> dependents = new ArrayList<LightingItem>();

        dependents.addAll(director.getSceneCollectionManagerV2().getScenesCollection(new HasComponentFilter<SceneV2>(SceneElement.this)));

        return dependents;
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected SceneElementDataModelV2 getSceneElementDataModel() {
        return sceneElementModel;
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected LightingItemDataModel getItemDataModel() {
        return getSceneElementDataModel();
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
                LightingDirector.get().getSceneElementCollectionManager().sendErrorEvent(name, status, getId());
            }
        });
    }
}
