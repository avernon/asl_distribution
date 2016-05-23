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
package org.allseen.lsf.helper.manager;

import java.util.Iterator;

import org.allseen.lsf.ControllerClient;
import org.allseen.lsf.ControllerClientStatus;
import org.allseen.lsf.LampGroupManager;
import org.allseen.lsf.LampState;
import org.allseen.lsf.ResponseCode;
import org.allseen.lsf.helper.callback.HelperGroupManagerCallback;
import org.allseen.lsf.helper.model.AllLampsLampGroup;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class SampleGroupManager extends LampGroupManager {
    public static final String ALL_LAMPS_GROUP_ID = "!!all_lamps!!";
    public static final String ALL_LAMPS_GROUP_NAME_DEFAULT= "All Lamps";

    protected HelperGroupManagerCallback callback;
    protected AllLampsLampGroup allLampsLampGroup;
    protected String allLampsGroupName;

    public SampleGroupManager(ControllerClient controller, HelperGroupManagerCallback callback) {
        this(controller, callback, ALL_LAMPS_GROUP_NAME_DEFAULT);
    }

    public SampleGroupManager(ControllerClient controller, HelperGroupManagerCallback callback, String allLampsGroupName) {
        super(controller, callback);

        this.callback = callback;
        this.allLampsLampGroup = new AllLampsLampGroup(callback.director);
        this.allLampsGroupName = allLampsGroupName;
    }

    @Override
    public ControllerClientStatus getLampGroupName(String groupID, String language) {
        ControllerClientStatus status = ControllerClientStatus.OK;

        if (ALL_LAMPS_GROUP_ID.equals(groupID)) {
            callback.getLampGroupNameReplyCB(ResponseCode.OK, ALL_LAMPS_GROUP_ID, language, allLampsGroupName);
        } else {
            status = super.getLampGroupName(groupID, language);
        }

        return status;
    }

    @Override
    public ControllerClientStatus getLampGroup(String groupID) {
        ControllerClientStatus status = ControllerClientStatus.OK;

        if (ALL_LAMPS_GROUP_ID.equals(groupID)) {
            callback.getLampGroupReplyCB(ResponseCode.OK, ALL_LAMPS_GROUP_ID, allLampsLampGroup);
        } else {
            status = super.getLampGroup(groupID);
        }

        return status;
    }

    @Override
    public ControllerClientStatus transitionLampGroupState(String groupID, LampState state, long duration) {
        ControllerClientStatus status = ControllerClientStatus.OK;

        if (ALL_LAMPS_GROUP_ID.equals(groupID)) {
            Iterator<String> i = getLampIDs();

            while(status == ControllerClientStatus.OK && i.hasNext()) {
                status = AllJoynManager.lampManager.transitionLampState(i.next(), state, duration);
            }
        } else {
            status = super.transitionLampGroupState(groupID, state, duration);
        }

        return status;
    }

    @Override
    public ControllerClientStatus pulseLampGroupWithState(String groupID, LampState toState, long period, long duration, long count, LampState fromState) {
        ControllerClientStatus status = ControllerClientStatus.OK;

        if (ALL_LAMPS_GROUP_ID.equals(groupID)) {
            Iterator<String> i = getLampIDs();

            while(status == ControllerClientStatus.OK && i.hasNext()) {
//TODO-FIX bindings need to be updated
//                status = AllJoynManager.lampManager.pulseLampWithState(i.next(), toState, period, duration, count, fromState);
            }
        } else {
            status = super.pulseLampGroupWithState(groupID, toState, period, duration, count, fromState);
        }

        return status;
    }

    @Override
    public ControllerClientStatus pulseLampGroupWithPreset(String groupID, String toPresetID, long period, long duration, long count, String fromPresetID) {
        ControllerClientStatus status = ControllerClientStatus.OK;

        if (ALL_LAMPS_GROUP_ID.equals(groupID)) {
            Iterator<String> i = getLampIDs();

            while(status == ControllerClientStatus.OK && i.hasNext()) {
//TODO-FIX bindings need to be updated
//                status = AllJoynManager.lampManager.pulseLampWithPreset(i.next(), toPresetID, period, duration, count, fromPresetID);
            }
        } else {
            status = super.pulseLampGroupWithPreset(groupID, toPresetID, period, duration, count, fromPresetID);
        }

        return status;
    }

    @Override
    public ControllerClientStatus transitionLampGroupStateOnOffField(String groupID, boolean onOff) {
        ControllerClientStatus status = ControllerClientStatus.OK;

        if (ALL_LAMPS_GROUP_ID.equals(groupID)) {
            Iterator<String> i = getLampIDs();

            while(status == ControllerClientStatus.OK && i.hasNext()) {
                status = AllJoynManager.lampManager.transitionLampStateOnOffField(i.next(), onOff);
            }
        } else {
            status = super.transitionLampGroupStateOnOffField(groupID, onOff);
        }

        return status;
    }

    @Override
    public ControllerClientStatus transitionLampGroupStateHueField(String groupID, long hue, long duration) {
        ControllerClientStatus status = ControllerClientStatus.OK;

        if (ALL_LAMPS_GROUP_ID.equals(groupID)) {
            Iterator<String> i = getLampIDs();

            while(status == ControllerClientStatus.OK && i.hasNext()) {
                status = AllJoynManager.lampManager.transitionLampStateHueField(i.next(), hue, duration);
            }
        } else {
            status = super.transitionLampGroupStateHueField(groupID, hue, duration);
        }

        return status;
    }

    @Override
    public ControllerClientStatus transitionLampGroupStateSaturationField(String groupID, long saturation, long duration) {
        ControllerClientStatus status = ControllerClientStatus.OK;

        if (ALL_LAMPS_GROUP_ID.equals(groupID)) {
            Iterator<String> i = getLampIDs();

            while(status == ControllerClientStatus.OK && i.hasNext()) {
                status = AllJoynManager.lampManager.transitionLampStateSaturationField(i.next(), saturation, duration);
            }
        } else {
            status = super.transitionLampGroupStateSaturationField(groupID, saturation, duration);
        }

        return status;
    }

    @Override
    public ControllerClientStatus transitionLampGroupStateBrightnessField(String groupID, long brightness, long duration) {
        ControllerClientStatus status = ControllerClientStatus.OK;

        if (ALL_LAMPS_GROUP_ID.equals(groupID)) {
            Iterator<String> i = getLampIDs();

            while(status == ControllerClientStatus.OK && i.hasNext()) {
                status = AllJoynManager.lampManager.transitionLampStateBrightnessField(i.next(), brightness, duration);
            }
        } else {
            status = super.transitionLampGroupStateBrightnessField(groupID, brightness, duration);
        }

        return status;
    }

    @Override
    public ControllerClientStatus transitionLampGroupStateColorTempField(String groupID, long colorTemp, long duration) {
        ControllerClientStatus status = ControllerClientStatus.OK;

        if (ALL_LAMPS_GROUP_ID.equals(groupID)) {
            Iterator<String> i = getLampIDs();

            while(status == ControllerClientStatus.OK && i.hasNext()) {
                status = AllJoynManager.lampManager.transitionLampStateColorTempField(i.next(), colorTemp, duration);
            }
        } else {
            status = super.transitionLampGroupStateColorTempField(groupID, colorTemp, duration);
        }

        return status;
    }

    @Override
    public ControllerClientStatus transitionLampGroupStateToPreset(String groupID, String presetID, long duration) {
        ControllerClientStatus status = ControllerClientStatus.OK;

        if (ALL_LAMPS_GROUP_ID.equals(groupID)) {
            Iterator<String> i = getLampIDs();

            while(status == ControllerClientStatus.OK && i.hasNext()) {
                status = AllJoynManager.lampManager.transitionLampStateToPreset(i.next(), presetID, duration);
            }
        } else {
            status = super.transitionLampGroupStateToPreset(groupID, presetID, duration);
        }

        return status;
    }

    @Override
    public ControllerClientStatus resetLampGroupState(String groupID) {
        ControllerClientStatus status = ControllerClientStatus.OK;

        if (ALL_LAMPS_GROUP_ID.equals(groupID)) {
            Iterator<String> i = getLampIDs();

            while(status == ControllerClientStatus.OK && i.hasNext()) {
                status = AllJoynManager.lampManager.resetLampState(i.next());
            }
        } else {
            status = super.resetLampGroupState(groupID);
        }

        return status;
    }

    @Override
    public ControllerClientStatus resetLampGroupStateOnOffField(String groupID) {
        ControllerClientStatus status = ControllerClientStatus.OK;

        if (ALL_LAMPS_GROUP_ID.equals(groupID)) {
            Iterator<String> i = getLampIDs();

            while(status == ControllerClientStatus.OK && i.hasNext()) {
                status = AllJoynManager.lampManager.resetLampStateOnOffField(i.next());
            }
        } else {
            status = super.resetLampGroupStateOnOffField(groupID);
        }

        return status;
    }

    @Override
    public ControllerClientStatus resetLampGroupStateHueField(String groupID) {
        ControllerClientStatus status = ControllerClientStatus.OK;

        if (ALL_LAMPS_GROUP_ID.equals(groupID)) {
            Iterator<String> i = getLampIDs();

            while(status == ControllerClientStatus.OK && i.hasNext()) {
                status = AllJoynManager.lampManager.resetLampStateHueField(i.next());
            }
        } else {
            status = super.resetLampGroupStateHueField(groupID);
        }

        return status;
    }

    @Override
    public ControllerClientStatus resetLampGroupStateSaturationField(String groupID) {
        ControllerClientStatus status = ControllerClientStatus.OK;

        if (ALL_LAMPS_GROUP_ID.equals(groupID)) {
            Iterator<String> i = getLampIDs();

            while(status == ControllerClientStatus.OK && i.hasNext()) {
                status = AllJoynManager.lampManager.resetLampStateSaturationField(i.next());
            }
        } else {
            status = super.resetLampGroupStateSaturationField(groupID);
        }

        return status;
    }

    @Override
    public ControllerClientStatus resetLampGroupStateBrightnessField(String groupID) {
        ControllerClientStatus status = ControllerClientStatus.OK;

        if (ALL_LAMPS_GROUP_ID.equals(groupID)) {
            Iterator<String> i = getLampIDs();

            while(status == ControllerClientStatus.OK && i.hasNext()) {
                status = AllJoynManager.lampManager.resetLampStateBrightnessField(i.next());
            }
        } else {
            status = super.resetLampGroupStateBrightnessField(groupID);
        }

        return status;
    }

    @Override
    public ControllerClientStatus resetLampGroupStateColorTempField(String groupID) {
        ControllerClientStatus status = ControllerClientStatus.OK;

        if (ALL_LAMPS_GROUP_ID.equals(groupID)) {
            Iterator<String> i = getLampIDs();

            while(status == ControllerClientStatus.OK && i.hasNext()) {
                status = AllJoynManager.lampManager.resetLampStateColorTempField(i.next());
            }
        } else {
            status = super.resetLampGroupStateColorTempField(groupID);
        }

        return status;
    }

    protected Iterator<String> getLampIDs() {
        return callback.director.getLampCollectionManager().getIDIterator();
    }
}
