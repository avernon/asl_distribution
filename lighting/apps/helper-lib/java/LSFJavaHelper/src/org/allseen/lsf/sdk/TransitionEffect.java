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

import org.allseen.lsf.sdk.manager.AllJoynManager;
import org.allseen.lsf.sdk.model.ColorItemDataModel;
import org.allseen.lsf.sdk.model.LightingItemUtil;
import org.allseen.lsf.sdk.model.TransitionEffectDataModelV2;

/**
 * This class represents a TransitionEffect definition in the lighting controller. This class
 * provides an interface to perform TransitionEffect operations. Supported operations include
 * modifying the transition effect properties, applying the transition effect to a lamp or group,
 * renaming, and deleting the transition effect. Transition effects gradually changes the color
 * state of a lamp or group over a given duration. Specifying a duration zero will change the
 * lamp or group state immediately. Transition effects are considered fully initialized if the
 * name, color state, and duration have been received. Transition effects are still operational
 * and can be applied to lamps or groups even in the uninitialized state.
 * <p>
 * <b>Note: This class is not meant to be instantiated directly. TransitionEffects should be retrieved
 * from the LightingDirector using the {@link LightingDirector#getTransitionEffects()} method.</b>
 * <p>
 * <b>Note: This class does not support TransitionEffect creation. See {@link LightingDirector#createTransitionEffect(LampState, long, String)}.</b>
 */
public class TransitionEffect extends ColorItem implements Effect {
    /**
     * Specifies the default name of the TransitionEffect.
     *
     * @param defaultName Default name of the TransitionEffect
     */
    public static void setDefaultName(String defaultName) {
        if (defaultName != null) {
            TransitionEffectDataModelV2.defaultName = defaultName;
        }
    }

    protected TransitionEffectDataModelV2 transitionEffectModel;

    /**
     * Constructs a TransitionEffect using the specified ID.
     * <p>
     * <b>WARNING: This method is intended to be used internally. Client software should not instantiate
     * TransitionEffects directly, but should instead get them from the {@link LightingDirector} using the
     * {@link LightingDirector#getTransitionEffects()} method.</b>
     *
     * @param transitionEffectId The ID of the transition effect
     */
    protected TransitionEffect(String transitionEffectId) {
        this(transitionEffectId, null);
    }

    /**
     * Constructs a TransitionEffect using the specified ID and name.
     * <p>
     * <b>WARNING: This method is intended to be used internally. Client software should not instantiate
     * TransitionEffects directly, but should instead get them from the {@link LightingDirector} using the
     * {@link LightingDirector#getTransitionEffects()} method.</b>
     *
     * @param transitionEffectId The ID of the transition effect
     * @param transitionEffectName The name of the transition effect
     */
    protected TransitionEffect(String transitionEffectId, String transitionEffectName) {
        super();

        transitionEffectModel = new TransitionEffectDataModelV2(transitionEffectId, transitionEffectName);
    }

    /**
     * Applies the current TransitionEffect to the specified GroupMember.
     *
     * @param member The GroupMember the TransitionEffect will be applied to.
     */
    @Override
    public void applyTo(GroupMember member) {
        String errorContext = "TransitionEffect.applyTo() error";

        if (postInvalidArgIfNull(errorContext, member)) {
            member.applyEffect(this);
        }
    }

    /**
     * Modifies the current TransitionEffect using the provided lamp state and duration.
     *
     * @param state The new LampState
     * @param duration The new duration, in milliseconds
     */
    public void modify(LampState state, long duration) {
        String errorContext = "TransitionEffect.modify() error";

        if (postInvalidArgIfNull(errorContext, state)) {
            if (state instanceof Preset) {
                postErrorIfFailure(errorContext,
                        AllJoynManager.transitionEffectManager.updateTransitionEffect(transitionEffectModel.id,
                                LightingItemUtil.createTransitionEffect(((Preset)state).getPresetDataModel(), duration)));
            } else {
                postErrorIfFailure(errorContext,
                        AllJoynManager.transitionEffectManager.updateTransitionEffect(transitionEffectModel.id,
                                LightingItemUtil.createTransitionEffect(state.getPowerOn(), state.getColorHsvt(), duration)));
            }
        }
    }

    /**
     * Renames the current TransitionEffect using the provided name.
     *
     * @param effectName The new name for the TransitionEffect
     */
    @Override
    public void rename(String effectName) {
        String errorContext = "TransitionEffect.rename() error";

        if (postInvalidArgIfNull(errorContext, effectName)) {
            postErrorIfFailure(errorContext,
                    AllJoynManager.transitionEffectManager.setTransitionEffectName(transitionEffectModel.id, effectName,
                            LightingDirector.get().getDefaultLanguage()));
        }
    }

    /**
     * Permanently deletes the current TransitionEffect from the lighting controller.
     * <p>
     * <b>Note: You cannot delete a transition effect that is used by a scene element. The dependency
     * must be deleted first.</b>
     */
    @Override
    public void delete() {
        String errorContext = "TransitionEffect.delete() error";

        postErrorIfFailure(errorContext,
                AllJoynManager.transitionEffectManager.deleteTransitionEffect(transitionEffectModel.id));
    }

    /**
     * Returns the Preset associated with the current TransitionEffect.
     * <p>
     * <b>Note: This method may return null if the TransitionEffect was not created
     * using an existing Preset.</b>
     *
     * @return The Preset associated with the TransitionEffect
     */
    public Preset getPreset() {
        return LightingDirector.get().getPreset(getPresetID());
    }

    /**
     * Returns the preset ID associated with the current TransitionEffect.
     * <p>
     * <b>Note: This method may return null if the TransitionEffect was not created
     * using an existing Preset.</b>
     *
     * @return The preset ID
     */
    public String getPresetID() {
        return transitionEffectModel.getPresetID();
    }

    /**
     * Returns the duration of the current TransitionEffect.
     *
     * @return TranstionEffect duration, in milliseconds
     */
    public long getDuration() {
        return transitionEffectModel.getDuration();
    }

    /**
     * Tests to see if the current TransitionEffect contains the provided Lighting item.
     *
     * @param item The Lighting Item to be confirmed a component of the TransitionEffect
     *
     * @return Returns true if the TransitionEffect contains the Lighting item, false otherwise
     */
    @Override
    public boolean hasComponent(LightingItem item) {
        String errorContext = "TransitionEffect.hasComponent() error";
        return postInvalidArgIfNull(errorContext, item) ? hasPreset(item.getId()) : false;
    }

    /**
     * Tests to see if the current TransitionEffect contains the provided Preset.
     *
     * @param preset The Preset to be confirmed a component of the TransitionEffect
     *
     * @return Returns true if the TransitionEffect contains the Preset, false otherwise
     */
    public boolean hasPreset(Preset preset) {
        String errorContext = "TransitionEffect.hasPreset() error";
        return postInvalidArgIfNull(errorContext, preset) ? hasPreset(preset.getId()) : false;
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected boolean hasPreset(String presetID) {
        return transitionEffectModel.containsPreset(presetID);
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected TransitionEffectDataModelV2 getTransitionEffectDataModel() {
        return transitionEffectModel;
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected Collection<LightingItem> getDependentCollection() {
        Collection<LightingItem> dependents = new ArrayList<LightingItem>();

        dependents.addAll(LightingDirector.get().getSceneElementCollectionManager().getSceneElementsCollection(new HasComponentFilter<SceneElement>(TransitionEffect.this)));

        return dependents;
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected ColorItemDataModel getColorDataModel() {
        return getTransitionEffectDataModel();
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
                LightingDirector.get().getTransitionEffectCollectionManager().sendErrorEvent(name, status, getId());
            }
        });
    }
}
