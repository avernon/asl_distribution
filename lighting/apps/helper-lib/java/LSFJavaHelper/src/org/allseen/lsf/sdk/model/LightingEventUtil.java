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
package org.allseen.lsf.sdk.model;

import org.allseen.lsf.sdk.Controller;
import org.allseen.lsf.sdk.Group;
import org.allseen.lsf.sdk.Lamp;
import org.allseen.lsf.sdk.LightingDirector;
import org.allseen.lsf.sdk.LightingItem;
import org.allseen.lsf.sdk.LightingItemErrorEvent;
import org.allseen.lsf.sdk.MasterScene;
import org.allseen.lsf.sdk.Preset;
import org.allseen.lsf.sdk.PulseEffect;
import org.allseen.lsf.sdk.Scene;
import org.allseen.lsf.sdk.SceneElement;
import org.allseen.lsf.sdk.TrackingID;
import org.allseen.lsf.sdk.TransitionEffect;
import org.allseen.lsf.sdk.listener.AnyCollectionListenerBase;
import org.allseen.lsf.sdk.listener.TrackingIDListener;

// TODO-REN: This class should probably be called ListenerUtil and moved to the listener package
public class LightingEventUtil {

    public static void listenFor(final TrackingID trackingId, final TrackingIDListener<LightingItem, LightingItemErrorEvent> listener) {
        LightingDirector.get().addListener(new AnyCollectionListenerBase<LightingItem, Lamp, Group, Preset, TransitionEffect, PulseEffect, SceneElement, Scene, MasterScene, Controller, LightingItemErrorEvent>() {

            @Override
            public void onAnyInitialized(TrackingID tid, LightingItem item) {
                if (tid != null && tid.value == trackingId.value) {
                    LightingDirector.get().removeListener(this);
                    listener.onTrackingIDReceived(tid, item);
                }
            }

            @Override
            public void onAnyError(LightingItemErrorEvent error) {
                if (error.trackingID != null && error.trackingID.value == trackingId.value) {
                    LightingDirector.get().removeListener(this);
                    listener.onTrackingIDError(error);
                }
            }
        });
    }
}
