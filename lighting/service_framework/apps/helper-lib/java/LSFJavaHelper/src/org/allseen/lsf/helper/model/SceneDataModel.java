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
package org.allseen.lsf.helper.model;

import java.util.ArrayList;
import java.util.List;

import org.allseen.lsf.Scene;
import org.allseen.lsf.StatePulseEffect;
import org.allseen.lsf.StateTransitionEffect;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class SceneDataModel extends LightingItemDataModel {
    public static final char TAG_PREFIX_SCENE = 'S';

    public static String defaultName = "<Loading scene info...>";

    public List<NoEffectDataModel> noEffects;
    public List<TransitionEffectDataModel> transitionEffects;
    public List<PulseEffectDataModel> pulseEffects;

    public SceneDataModel() {
        this("", null);
    }

    public SceneDataModel(String sceneID) {
        this(sceneID, null);
    }

    public SceneDataModel(String sceneID, String sceneName) {
        super(sceneID, TAG_PREFIX_SCENE, sceneName != null ? sceneName : defaultName);

        noEffects = new ArrayList<NoEffectDataModel>();
        transitionEffects = new ArrayList<TransitionEffectDataModel>();
        pulseEffects = new ArrayList<PulseEffectDataModel>();
    }

    public SceneDataModel(SceneDataModel other) {
        super(other);

        this.noEffects = new ArrayList<NoEffectDataModel>(other.noEffects);
        this.transitionEffects = new ArrayList<TransitionEffectDataModel>(other.transitionEffects);
        this.pulseEffects = new ArrayList<PulseEffectDataModel>(other.pulseEffects);
    }

    public void updateNoEffect(NoEffectDataModel elementModel) {
        updateElement(noEffects, elementModel);
    }

    public void updateTransitionEffect(TransitionEffectDataModel elementModel) {
        updateElement(transitionEffects, elementModel);
    }

    public void updatePulseEffect(PulseEffectDataModel elementModel) {
        updateElement(pulseEffects, elementModel);
    }

    public boolean removeElement(String elementID) {
        return removeElement(noEffects, elementID) || removeElement(transitionEffects, elementID) || removeElement(pulseEffects, elementID);
    }

    protected <T extends SceneElementDataModel> void updateElement(List<T> elementModels, T elementModel) {
        int index = elementModels.indexOf(elementModel);

        if (index >= 0) {
            elementModels.set(index, elementModel);
        } else {
            elementModels.add(elementModel);
        }
    }

    protected <T extends SceneElementDataModel> boolean removeElement(List<T> elementModels, String elementID) {
        boolean removed = false;

        for (int i = 0; !removed && i < elementModels.size(); i++) {
            if (elementModels.get(i).equalsID(elementID)){
                elementModels.remove(i);
                removed = true;
            }
        }

        return removed;
   }

    public Scene toScene() {
        Scene scene = new Scene();

        //TODO-FIX handle preset effects properly
        List<StateTransitionEffect> stateTransitionEffects = new ArrayList<StateTransitionEffect>();
        List<StatePulseEffect> statePulseEffects = new ArrayList<StatePulseEffect>();

        for (int i = 0; i < noEffects.size(); i++) {
            NoEffectDataModel elementModel = noEffects.get(i);
            StateTransitionEffect stateTransitionEffect = new StateTransitionEffect();

            stateTransitionEffect.setLamps(elementModel.members.getLamps());
            stateTransitionEffect.setLampGroups(elementModel.members.getLampGroups());
            stateTransitionEffect.setLampState(elementModel.state);
            stateTransitionEffect.setTransitionPeriod(0);

            stateTransitionEffects.add(stateTransitionEffect);
        }

        for (int i = 0; i < transitionEffects.size(); i++) {
            TransitionEffectDataModel elementModel = transitionEffects.get(i);
            StateTransitionEffect stateTransitionEffect = new StateTransitionEffect();

            stateTransitionEffect.setLamps(elementModel.members.getLamps());
            stateTransitionEffect.setLampGroups(elementModel.members.getLampGroups());
            stateTransitionEffect.setLampState(elementModel.state);
            stateTransitionEffect.setTransitionPeriod(elementModel.duration);

            stateTransitionEffects.add(stateTransitionEffect);
        }

        for (int i = 0; i < pulseEffects.size(); i++) {
            PulseEffectDataModel elementModel = pulseEffects.get(i);
            StatePulseEffect statePulseEffect = new StatePulseEffect();

            statePulseEffect.setLamps(elementModel.members.getLamps());
            statePulseEffect.setLampGroups(elementModel.members.getLampGroups());
            statePulseEffect.setFromLampState(elementModel.state);
            statePulseEffect.setToLampState(elementModel.endState);
            statePulseEffect.setPulseDuration(elementModel.duration);
            statePulseEffect.setPulsePeriod(elementModel.period);
            statePulseEffect.setPulseCount(elementModel.count);

            statePulseEffects.add(statePulseEffect);
        }

        scene.setStateTransitionEffects(stateTransitionEffects.toArray(new StateTransitionEffect[stateTransitionEffects.size()]));
        scene.setStatePulseEffects(statePulseEffects.toArray(new StatePulseEffect[statePulseEffects.size()]));

        return scene;
    }

    public void fromScene(Scene scene) {
        StateTransitionEffect[] stateTransitionEffects = scene.getStateTransitionEffects();
        StatePulseEffect[] statePulseEffects = scene.getStatePulseEffects();

        noEffects.clear();
        transitionEffects.clear();
        pulseEffects.clear();

        for (int i = 0; i < stateTransitionEffects.length; i++) {
            StateTransitionEffect stateTransitionEffect = stateTransitionEffects[i];

            if (stateTransitionEffect.getTransitionPeriod() == 0) {
                NoEffectDataModel elementModel = new NoEffectDataModel();

                elementModel.members.setLamps(stateTransitionEffect.getLamps());
                elementModel.members.setLampGroups(stateTransitionEffect.getLampGroups());
                elementModel.state = stateTransitionEffect.getLampState();

                noEffects.add(elementModel);
            } else {
                TransitionEffectDataModel elementModel = new TransitionEffectDataModel();

                elementModel.members.setLamps(stateTransitionEffect.getLamps());
                elementModel.members.setLampGroups(stateTransitionEffect.getLampGroups());
                elementModel.state = stateTransitionEffect.getLampState();
                elementModel.duration = stateTransitionEffect.getTransitionPeriod();

                transitionEffects.add(elementModel);
            }
        }

        for (int i = 0; i < statePulseEffects.length; i++) {
            StatePulseEffect statePulseEffect = statePulseEffects[i];
            PulseEffectDataModel elementModel = new PulseEffectDataModel();

            elementModel.members.setLamps(statePulseEffect.getLamps());
            elementModel.members.setLampGroups(statePulseEffect.getLampGroups());
            elementModel.state = statePulseEffect.getFromLampState();
            elementModel.endState = statePulseEffect.getToLampState();
            elementModel.period = statePulseEffect.getPulsePeriod();
            elementModel.duration = statePulseEffect.getPulseDuration();
            elementModel.count = statePulseEffect.getPulseCount();

            pulseEffects.add(elementModel);
        }
    }
}
