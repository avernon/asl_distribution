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

public class PulseEffectManagerCallback extends DefaultNativeClassWrapper {

    public PulseEffectManagerCallback() {
        createNativeObject();
    }

    public void getPulseEffectReplyCB(ResponseCode responseCode, String pulseEffectID, PulseEffectV2 pulseEffect)                     { }
    public void applyPulseEffectOnLampsReplyCB(ResponseCode responseCode, String pulseEffectID, String[] lampIDs)                   { }
    public void applyPulseEffectOnLampGroupsReplyCB(ResponseCode responseCode, String pulseEffectID, String[] lampGroupIDs)         { }
    public void getAllPulseEffectIDsReplyCB(ResponseCode responseCode, String[] pulseEffectIDs)                                     { }
    public void getPulseEffectNameReplyCB(ResponseCode responseCode, String pulseEffectID, String language, String pulseEffectName) { }
    public void setPulseEffectNameReplyCB(ResponseCode responseCode, String pulseEffectID, String language)                         { }
    public void pulseEffectsNameChangedCB(String[] pulseEffectIDs)                                                                  { }
    public void createPulseEffectReplyCB(ResponseCode responseCode, String pulseEffectID, long trackingID)                          { }
    public void pulseEffectsCreatedCB(String[] pulseEffectIDs)                                                                      { }
    public void updatePulseEffectReplyCB(ResponseCode responseCode, String pulseEffectID)                                           { }
    public void pulseEffectsUpdatedCB(String[] pulseEffectIDs)                                                                      { }
    public void deletePulseEffectReplyCB(ResponseCode responseCode, String pulseEffectID)                                           { }
    public void pulseEffectsDeletedCB(String[] pulseEffectIDs)                                                                      { }

    @Override
    protected native void createNativeObject();

    @Override
    protected native void destroyNativeObject();
}
