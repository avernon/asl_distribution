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

import org.allseen.lsf.PresetPulseEffect;
import org.allseen.lsf.sdk.model.EffectType;

/**
 * Base interface implemented by all Lighting items that are effects.
 */
public interface Effect extends LightingItemInterface, DeletableItem {

    /**
     * Constant specifying preset effect type.
     */
    public static final String EFFECT_TYPE_PRESET = EffectType.None.toString();

    /**
     * Constant specifying transition effect type.
     */
    public static final String EFFECT_TYPE_TRANSITION = EffectType.Transition.toString();

    /**
     * Constant specifying pulse effect type.
     */
    public static final String EFFECT_TYPE_PULSE = EffectType.Pulse.toString();

    /**
     * Constant specifying preset to use current state of GroupMember as starting state.
     */
    public static final String PRESET_ID_USE_CURRENT_STATE = PresetPulseEffect.PRESET_ID_CURRENT_STATE;

    /**
     * Applies the current effect to the provided Lighting item.
     *
     * @param member Lighting item to apply the effect
     */
    public void applyTo(GroupMember member);
}
