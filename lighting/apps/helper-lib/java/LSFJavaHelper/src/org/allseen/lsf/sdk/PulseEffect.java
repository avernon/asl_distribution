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
import org.allseen.lsf.sdk.model.PulseEffectDataModelV2;

/**
 * This class represents a PulseEffect definition in the lighting controller. This class
 * provides an interface to perform PulseEffect operations. Supported operations include
 * modifying the pulse effect properties, applying the pulse effect to a lamp or group,
 * renaming, and deleting the pulse effect. Pulse effects alternate between two color states
 * for a given duration and then return to their original state. Pulse effects are considered
 * fully initialized when their name, start and end color state, duration, period, and number
 * of pulses have been received. Pulse effects are still operational and can be applied to
 * lamps or groups even in the uninitialized state.
 * <p>
 * <b>Note: This class is not meant to be instantiated directly. PulseEffects should be retrieved
 * from the LightingDirector using the {@link LightingDirector#getPulseEffects()} method.</b>
 * <p>
 * <b>Note: This class does not support PulseEffect creation. See {@link LightingDirector#createPulseEffect(LampState, LampState, long, long, long, String)}.</b>
 */
public class PulseEffect extends ColorItem implements Effect {
    /**
     * Specifies the default name of the PulseEffect.
     *
     * @param defaultName Default name of the PulseEffect
     */
    public static void setDefaultName(String defaultName) {
        if (defaultName != null) {
            PulseEffectDataModelV2.defaultName = defaultName;
        }
    }

    protected PulseEffectDataModelV2 pulseEffectModel;

    /**
     * Constructs a PulseEffect using the specified ID.
     * <p>
     * <b>WARNING: This method is intended to be used internally. Client software should not instantiate
     * PulseEffects directly, but should instead get them from the {@link LightingDirector} using the
     * {@link LightingDirector#getPulseEffects()} method.</b>
     *
     * @param pulseEffectId The ID of the pulse effect
     */
    protected PulseEffect(String pulseEffectId) {
        this(pulseEffectId, null);
    }

    /**
     * Constructs a PulseEffect using the specified ID and name.
     * <p>
     * <b>WARNING: This method is intended to be used internally. Client software should not instantiate
     * PulseEffects directly, but should instead get them from the {@link LightingDirector} using the
     * {@link LightingDirector#getPulseEffects()} method.</b>
     *
     * @param pulseEffectId The ID of the pulse effect
     * @param pulseEffectName The name of the pulse effect
     */
    protected PulseEffect(String pulseEffectId, String pulseEffectName) {
        super();

        pulseEffectModel = new PulseEffectDataModelV2(pulseEffectId, pulseEffectName);
    }

    /**
     * Applies the current PulseEffect to the specified GroupMember.
     *
     * @param member The GroupMember the PulseEffect will be applied to.
     */
    @Override
    public void applyTo(GroupMember member) {
        String errorContext = "PulseEffect.applyTo() error";

        if (postInvalidArgIfNull(errorContext, member)) {
            member.applyEffect(this);
        }
    }

    /**
     * Modifies the current PulseEffect using the provided parameters.
     *
     * @param fromState The new fromState
     * @param toState The new toState
     * @param period The new period
     * @param duration The new duration, in milliseconds
     * @param count The new count
     */
    public void modify(LampState fromState, LampState toState, long period, long duration, long count) {
        String errorContext = "PulseEffect.modify() error";

        if (postInvalidArgIfNull(errorContext, fromState) && postInvalidArgIfNull(errorContext, toState)) {
            if (fromState instanceof Preset && toState instanceof Preset) {
                postErrorIfFailure(errorContext,
                        AllJoynManager.pulseEffectManager.updatePulseEffect(pulseEffectModel.id,
                                LightingItemUtil.createPulseEffect(((Preset)fromState).getPresetDataModel(), ((Preset)toState).getPresetDataModel(), period, duration, count)));
            } else {
                postErrorIfFailure(errorContext,
                        AllJoynManager.pulseEffectManager.updatePulseEffect(pulseEffectModel.id,
                                LightingItemUtil.createPulseEffect(fromState.getPowerOn(), fromState.getColorHsvt(), toState.getPowerOn(), toState.getColorHsvt(), period, duration, count)));
            }
        }
    }

    /**
     * Renames the current PulseEffect using the provided name.
     *
     * @param effectName The new name for the TransitionEffect
     */
    @Override
    public void rename(String effectName) {
        String errorContext = "PulseEffect.rename() error";

        if (postInvalidArgIfNull(errorContext, effectName)) {
            postErrorIfFailure(errorContext,
                    AllJoynManager.pulseEffectManager.setPulseEffectName(pulseEffectModel.id, effectName, LightingDirector.get().getDefaultLanguage()));
        }
    }

    /**
     * Permanently deletes the current PulseEffect from the lighting controller.
     * <p>
     * <b>Note: You cannot delete a pulse effect that is used by a scene element. The dependency
     * must be deleted first.</b>
     */
    @Override
    public void delete() {
        String errorContext = "PulseEffect.delete() error";

        postErrorIfFailure(errorContext,
                AllJoynManager.pulseEffectManager.deletePulseEffect(pulseEffectModel.id));
    }

    /**
     * Returns a boolean that indicates whether the current PulseEffect using the current
     * state as its starting state.
     *
     * @return Return true if the PulseEffect uses the current state as its starting state, false otherwise
     */
    public boolean isStartWithCurrent() {
        return pulseEffectModel.isStartWithCurrent();
    }

    /**
     * Returns the PulseEffect starting lamp state.
     *
     * @return Reference to MyLampState object
     */
    public MyLampState getStartState() {
        return getState();
    }

    /**
     * Returns the PulseEffect ending lamp state.
     *
     * @return Reference to MyLampState object
     */
    public MyLampState getEndState() {
        return new MyLampState(pulseEffectModel.getEndState());
    }

    /**
     * Returns the Preset associated with the PulseEffect's start state.
     *
     * @return Reference to Preset object
     */
    public Preset getStartPreset() {
        return LightingDirector.get().getPreset(getStartPresetID());
    }

    /**
     * Returns the Preset associated with the PulseEffect's end state.
     *
     * @return Reference to Preset object
     */
    public Preset getEndPreset() {
        return LightingDirector.get().getPreset(getEndPresetID());
    }

    /**
     * Returns the preset ID associated with the PulseEffect's start state.
     *
     * @return ID of the Preset
     */
    public String getStartPresetID() {
        return pulseEffectModel.getStartPresetID();
    }

    /**
     * Returns the preset ID associated with the PulseEffect's end state.
     *
     * @return ID of the Preset
     */
    public String getEndPresetID() {
        return pulseEffectModel.getEndPresetID();
    }

    /**
     * Returns the period of the PulseEffect.
     *
     * @return Period of the PulseEffect, in milliseconds
     */
    public long getPeriod() {
        return pulseEffectModel.getPeriod();
    }

    /**
     * Returns the duration of the PulseEffect.
     *
     * @return Duration of the PulseEffect, in milliseconds
     */
    public long getDuration() {
        return pulseEffectModel.getDuration();
    }

    /**
     * Returns the number of pulses in the PulseEffect.
     *
     * @return Number of pulses in the PulseEffect
     */
    public long getCount() {
        return pulseEffectModel.getCount();
    }

    /**
     * Tests to see if the current PulseEffect contains the provided Lighting item.
     *
     * @param item The Lighting Item to be confirmed a component of the PulseEffect
     *
     * @return Returns true if the PulseEffect contains the Lighting item, false otherwise
     */
    @Override
    public boolean hasComponent(LightingItem item) {
        String errorContext = "PulseEffect.hasComponent() error";
        return postInvalidArgIfNull(errorContext, item) ? hasPreset(item.getId()) : false;
    }

    /**
     * Tests to see if the current PulseEffect contains the provided Preset.
     *
     * @param preset The Preset to be confirmed a component of the PulseEffect
     *
     * @return Returns true if the PulseEffect contains the Preset, false otherwise
     */
    public boolean hasPreset(Preset preset) {
        String errorContext = "PulseEffect.hasPreset() error";
        return postInvalidArgIfNull(errorContext, preset) ? hasPreset(preset.getId()) : false;
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected boolean hasPreset(String presetID) {
        return pulseEffectModel.containsPreset(presetID);
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected Collection<LightingItem> getDependentCollection() {
        Collection<LightingItem> dependents = new ArrayList<LightingItem>();

        dependents.addAll(LightingDirector.get().getSceneElementCollectionManager().getSceneElementsCollection(new HasComponentFilter<SceneElement>(PulseEffect.this)));

        return dependents;
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected PulseEffectDataModelV2 getPulseEffectDataModel() {
        return pulseEffectModel;
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected ColorItemDataModel getColorDataModel() {
        return getPulseEffectDataModel();
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
                LightingDirector.get().getPulseEffectCollectionManager().sendErrorEvent(name, status, getId());
            }
        });
    }
}
