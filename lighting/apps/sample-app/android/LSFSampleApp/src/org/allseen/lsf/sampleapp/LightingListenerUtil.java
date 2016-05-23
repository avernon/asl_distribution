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
package org.allseen.lsf.sampleapp;

import org.allseen.lsf.sdk.LightingDirector;
import org.allseen.lsf.sdk.LightingItem;
import org.allseen.lsf.sdk.LightingItemErrorEvent;
import org.allseen.lsf.sdk.TrackingID;

public class LightingListenerUtil {

    public static void listenFor(final TrackingID trackingId, final TrackingIDListener listener) {
        LightingDirector.get().addListener(new AnyLightingItemListenerBase() {

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
