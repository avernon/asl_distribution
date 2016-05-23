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
package org.allseen.lsf;

import org.allseen.lsf.sdk.ResponseCode;

public class TransitionEffectManagerCallback extends DefaultNativeClassWrapper {

    public TransitionEffectManagerCallback() {
        createNativeObject();
    }

    public void getTransitionEffectReplyCB(ResponseCode responseCode, String transitionEffectID, TransitionEffectV2 transitionEffect)                 { }
    public void applyTransitionEffectOnLampsReplyCB(ResponseCode responseCode, String transitionEffectID, String[] lampIDs)                         { }
    public void applyTransitionEffectOnLampGroupsReplyCB(ResponseCode responseCode, String transitionEffectID, String[] lampGroupIDs)               { }
    public void getAllTransitionEffectIDsReplyCB(ResponseCode responseCode, String[] transitionEffectIDs)                                           { }
    public void getTransitionEffectNameReplyCB(ResponseCode responseCode, String transitionEffectID, String language, String transitionEffectName)  { }
    public void setTransitionEffectNameReplyCB(ResponseCode responseCode, String transitionEffectID, String language)                               { }
    public void transitionEffectsNameChangedCB(String[] transitionEffectIDs)                                                                        { }
    public void createTransitionEffectReplyCB(ResponseCode responseCode, String transitionEffectID, long trackingID)                                { }
    public void transitionEffectsCreatedCB(String[] transitionEffectIDs)                                                                            { }
    public void updateTransitionEffectReplyCB(ResponseCode responseCode, String transitionEffectID)                                                 { }
    public void transitionEffectsUpdatedCB(String[] transitionEffectIDs)                                                                            { }
    public void deleteTransitionEffectReplyCB(ResponseCode responseCode, String transitionEffectID)                                                 { }
    public void transitionEffectsDeletedCB(String[] transitionEffectIDs)                                                                            { }

    @Override
    protected native void createNativeObject();

    @Override
    protected native void destroyNativeObject();
}
