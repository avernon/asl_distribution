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
import org.allseen.lsf.sdk.factory.PulseEffectFactory;
import org.allseen.lsf.sdk.listener.PulseEffectCollectionListener;
import org.allseen.lsf.sdk.model.LightingItemFilter;
import org.allseen.lsf.sdk.model.PulseEffectDataModelV2;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class PulseEffectCollectionManager<PULSEEFFECT, ERROR> extends LightingItemCollectionManager<PULSEEFFECT, PulseEffectCollectionListener<? super PULSEEFFECT, ? super ERROR>, PulseEffectDataModelV2, ERROR> {

    protected final PulseEffectFactory<PULSEEFFECT, ERROR> factory;

    public PulseEffectCollectionManager(LightingSystemManager<?, ?, ?, ?, PULSEEFFECT, ?, ?, ?, ?, ?, ?> manager, PulseEffectFactory<PULSEEFFECT, ERROR> factory) {
        super(manager, factory);

        this.factory = factory;
    }

    public PULSEEFFECT addPulseEffect(String pulseEffectID) {
        return addPulseEffect(pulseEffectID, factory.createPulseEffect(pulseEffectID));
    }

    public PULSEEFFECT addPulseEffect(String pulseEffectID, PULSEEFFECT pulseEffect) {
        return itemAdapters.put(pulseEffectID, pulseEffect);
    }

    public PULSEEFFECT getPulseEffect(String pulseEffectID) {
        return getAdapter(pulseEffectID);
    }

    public PULSEEFFECT[] getPulseEffects() {
        return getAdapters().toArray(factory.createPulseEffects(size()));
    }

    public PULSEEFFECT[] getPulseEffects(LightingItemFilter<PULSEEFFECT> filter) {
        Collection<PULSEEFFECT> filteredPulseEffects = getPulseEffectsCollection(filter);
        return filteredPulseEffects.toArray(factory.createPulseEffects(filteredPulseEffects.size()));
    }

    public Collection<PULSEEFFECT> getPulseEffectsCollection(LightingItemFilter<PULSEEFFECT> filter) {
        return getAdapters(filter);
    }

    public Iterator<PULSEEFFECT> getPulseEffectIterator() {
        return getAdapters().iterator();
    }

    public Collection<PULSEEFFECT> removePulseEffect() {
        return removeAllAdapters();
    }

    public PULSEEFFECT removePulseEffect(String pulseEffectId) {
        return removeAdapter(pulseEffectId);
    }

    @Override
    protected void sendInitializedEvent(PulseEffectCollectionListener<? super PULSEEFFECT, ? super ERROR> listener, PULSEEFFECT pulseEffect, TrackingID trackingID) {
        listener.onPulseEffectInitialized(trackingID, pulseEffect);
    }

    @Override
    protected void sendChangedEvent(PulseEffectCollectionListener<? super PULSEEFFECT, ? super ERROR> listener, PULSEEFFECT pulseEffect) {
        listener.onPulseEffectChanged(pulseEffect);
    }

    @Override
    protected void sendRemovedEvent(PulseEffectCollectionListener<? super PULSEEFFECT, ? super ERROR> listener, PULSEEFFECT pulseEffect) {
        listener.onPulseEffectRemoved(pulseEffect);
    }

    @Override
    protected void sendErrorEvent(PulseEffectCollectionListener<? super PULSEEFFECT, ? super ERROR> listener, ERROR error) {
        listener.onPulseEffectError(error);
    }

    @Override
    public PulseEffectDataModelV2 getModel(String pulseEffectID) {
        return getModel(getAdapter(pulseEffectID));
    }

    @Override
    public PulseEffectDataModelV2 getModel(PULSEEFFECT pulseEffect) {
        return pulseEffect != null ? factory.findPulseEffectDataModel(pulseEffect) : null;
    }

}
