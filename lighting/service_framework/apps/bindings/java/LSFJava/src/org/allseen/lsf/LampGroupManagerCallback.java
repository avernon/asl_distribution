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

public class LampGroupManagerCallback extends DefaultNativeClassWrapper {

    public LampGroupManagerCallback() {
        createNativeObject();
    }

    public void getAllLampGroupIDsReplyCB(ResponseCode responseCode, String[] lampGroupIDs)                                     { }
    public void getLampGroupNameReplyCB(ResponseCode responseCode, String lampGroupID, String language, String lampGroupName)   { }
    public void setLampGroupNameReplyCB(ResponseCode responseCode, String lampGroupID, String language)                         { }
    public void lampGroupsNameChangedCB(String[] lampGroupIDs)                                                                  { }
    public void createLampGroupReplyCB(ResponseCode responseCode, String lampGroupID)                                           { }
    public void lampGroupsCreatedCB(String[] lampGroupIDs)                                                                      { }
    public void getLampGroupReplyCB(ResponseCode responseCode, String lampGroupID, LampGroup lampGroup)                         { }
    public void deleteLampGroupReplyCB(ResponseCode responseCode, String lampGroupID)                                           { }
    public void lampGroupsDeletedCB(String[] lampGroupIDs)                                                                      { }
    public void transitionLampGroupStateReplyCB(ResponseCode responseCode, String lampGroupID)                                  { }
    public void pulseLampGroupWithStateReplyCB(ResponseCode responseCode, String lampGroupID)                                   { }
    public void pulseLampGroupWithPresetReplyCB(ResponseCode responseCode, String lampGroupID)                                  { }
    public void transitionLampGroupStateOnOffFieldReplyCB(ResponseCode responseCode, String lampGroupID)                        { }
    public void transitionLampGroupStateHueFieldReplyCB(ResponseCode responseCode, String lampGroupID)                          { }
    public void transitionLampGroupStateSaturationFieldReplyCB(ResponseCode responseCode, String lampGroupID)                   { }
    public void transitionLampGroupStateBrightnessFieldReplyCB(ResponseCode responseCode, String lampGroupID)                   { }
    public void transitionLampGroupStateColorTempFieldReplyCB(ResponseCode responseCode, String lampGroupID)                    { }
    public void resetLampGroupStateReplyCB(ResponseCode responseCode, String lampGroupID)                                       { }
    public void resetLampGroupStateOnOffFieldReplyCB(ResponseCode responseCode, String lampGroupID)                             { }
    public void resetLampGroupStateHueFieldReplyCB(ResponseCode responseCode, String lampGroupID)                               { }
    public void resetLampGroupStateSaturationFieldReplyCB(ResponseCode responseCode, String lampGroupID)                        { }
    public void resetLampGroupStateBrightnessFieldReplyCB(ResponseCode responseCode, String lampGroupID)                        { }
    public void resetLampGroupStateColorTempFieldReplyCB(ResponseCode responseCode, String lampGroupID)                         { }
    public void updateLampGroupReplyCB(ResponseCode responseCode, String lampGroupID)                                           { }
    public void lampGroupsUpdatedCB(String[] lampGroupIDs)                                                                      { }
    public void transitionLampGroupStateToPresetReplyCB(ResponseCode responseCode, String lampGroupID)                          { }

    // @Override
    @Override
    protected native void createNativeObject();

    // @Override
    @Override
    protected native void destroyNativeObject();
}
