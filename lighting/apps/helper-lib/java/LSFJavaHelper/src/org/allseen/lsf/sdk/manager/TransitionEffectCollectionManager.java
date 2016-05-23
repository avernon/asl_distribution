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
package org.allseen.lsf.sdk.manager;

import java.util.Collection;
import java.util.Iterator;

import org.allseen.lsf.sdk.TrackingID;
import org.allseen.lsf.sdk.factory.TransitionEffectFactory;
import org.allseen.lsf.sdk.listener.TransitionEffectCollectionListener;
import org.allseen.lsf.sdk.model.LightingItemFilter;
import org.allseen.lsf.sdk.model.TransitionEffectDataModelV2;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class TransitionEffectCollectionManager<TRANSITIONEFFECT, ERROR> extends LightingItemCollectionManager<TRANSITIONEFFECT, TransitionEffectCollectionListener<? super TRANSITIONEFFECT, ? super ERROR>, TransitionEffectDataModelV2, ERROR> {

    private final TransitionEffectFactory<TRANSITIONEFFECT, ERROR> factory;

    public TransitionEffectCollectionManager(LightingSystemManager<?, ?, ?, TRANSITIONEFFECT, ?, ?, ?, ?, ?, ?, ?> manager, TransitionEffectFactory<TRANSITIONEFFECT, ERROR> factory) {
        super(manager, factory);

        this.factory = factory;
    }

    public TRANSITIONEFFECT addTransitionEffect(String transitionEffectID) {
        return addTransitionEffect(transitionEffectID, factory.createTransitionEffect(transitionEffectID));
    }

    public TRANSITIONEFFECT addTransitionEffect(String transitionEffectID, TRANSITIONEFFECT transistionEffect) {
        return itemAdapters.put(transitionEffectID, transistionEffect);
    }

    public TRANSITIONEFFECT getTransistionEffect(String transitionEffectID) {
        return getAdapter(transitionEffectID);
    }

    public TRANSITIONEFFECT[] getTransitionEffects() {
        return getAdapters().toArray(factory.createTransitionEffects(size()));
    }

    public TRANSITIONEFFECT[] getTransitionEffects(LightingItemFilter<TRANSITIONEFFECT> filter) {
        Collection<TRANSITIONEFFECT> filteredTransitionEffect = getTransitionEffectsCollection(filter);
        return filteredTransitionEffect.toArray(factory.createTransitionEffects(filteredTransitionEffect.size()));
    }

    public Collection<TRANSITIONEFFECT> getTransitionEffectsCollection(LightingItemFilter<TRANSITIONEFFECT> filter) {
        return getAdapters(filter);
    }

    public Iterator<TRANSITIONEFFECT> getTransitionEffectIterator() {
        return getAdapters().iterator();
    }

    public Collection<TRANSITIONEFFECT> removeTransitionEffects() {
        return removeAllAdapters();
    }

    public TRANSITIONEFFECT removeTransitionEffect(String transitionEffectId) {
        return removeAdapter(transitionEffectId);
    }

    @Override
    protected void sendInitializedEvent(TransitionEffectCollectionListener<? super TRANSITIONEFFECT, ? super ERROR> listener, TRANSITIONEFFECT transitionEffect, TrackingID trackingID) {
        listener.onTransitionEffectInitialized(trackingID, transitionEffect);
    }

    @Override
    protected void sendChangedEvent(TransitionEffectCollectionListener<? super TRANSITIONEFFECT, ? super ERROR> listener, TRANSITIONEFFECT transitionEffect) {
        listener.onTransitionEffectChanged(transitionEffect);
    }

    @Override
    protected void sendRemovedEvent(TransitionEffectCollectionListener<? super TRANSITIONEFFECT, ? super ERROR> listener, TRANSITIONEFFECT transitionEffect) {
        listener.onTransitionEffectRemoved(transitionEffect);
    }

    @Override
    protected void sendErrorEvent(TransitionEffectCollectionListener<? super TRANSITIONEFFECT, ? super ERROR> listener, ERROR error) {
        listener.onTransitionEffectError(error);
    }

    @Override
    public TransitionEffectDataModelV2 getModel(String transitionEffectID) {
        return getModel(getAdapter(transitionEffectID));
    }

    @Override
    public TransitionEffectDataModelV2 getModel(TRANSITIONEFFECT transitionEffect) {
        return transitionEffect != null ? factory.findTransitionEffectDataModel(transitionEffect) : null;
    }
}
