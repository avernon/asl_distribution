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
package org.allseen.lsf;

import org.allseen.lsf.sdk.ResponseCode;

public class PresetManagerCallback extends DefaultNativeClassWrapper {

    public PresetManagerCallback() {
        createNativeObject();
    }

    public void getPresetReplyCB(ResponseCode responseCode, String presetID, LampState preset)                          { }
    public void getAllPresetIDsReplyCB(ResponseCode responseCode, String[] presetIDs)                                   { }
    public void getPresetNameReplyCB(ResponseCode responseCode, String presetID, String language, String presetName)    { }
    public void setPresetNameReplyCB(ResponseCode responseCode, String presetID, String language)                       { }
    public void presetsNameChangedCB(String[] presetIDs)                                                                { }
    public void createPresetReplyCB(ResponseCode responseCode, String presetID)                                         { }
    public void presetsCreatedCB(String[] presetIDs)                                                                    { }
    public void updatePresetReplyCB(ResponseCode responseCode, String presetID)                                         { }
    public void presetsUpdatedCB(String[] presetIDs)                                                                    { }
    public void deletePresetReplyCB(ResponseCode responseCode, String presetID)                                         { }
    public void presetsDeletedCB(String[] presetIDs)                                                                    { }
    public void getDefaultLampStateReplyCB(ResponseCode responseCode, LampState defaultLampState)                       { }
    public void setDefaultLampStateReplyCB(ResponseCode responseCode)                                                   { }
    public void defaultLampStateChangedCB()                                                                             { }
    public void createPresetWithTrackingReplyCB(ResponseCode responseCode, String presetID, long trackingID)            { }

    @Override
    protected native void createNativeObject();

    @Override
    protected native void destroyNativeObject();
}
