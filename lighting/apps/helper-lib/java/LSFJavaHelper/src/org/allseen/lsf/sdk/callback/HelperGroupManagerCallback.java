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
package org.allseen.lsf.sdk.callback;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import org.allseen.lsf.LampGroup;
import org.allseen.lsf.LampGroupManagerCallback;
import org.allseen.lsf.sdk.LampDetails;
import org.allseen.lsf.sdk.ResponseCode;
import org.allseen.lsf.sdk.TrackingID;
import org.allseen.lsf.sdk.manager.AllJoynManager;
import org.allseen.lsf.sdk.manager.GroupCollectionManager;
import org.allseen.lsf.sdk.manager.LightingSystemManager;
import org.allseen.lsf.sdk.model.AllLampsDataModel;
import org.allseen.lsf.sdk.model.ColorAverager;
import org.allseen.lsf.sdk.model.ColorStateConverter;
import org.allseen.lsf.sdk.model.GroupDataModel;
import org.allseen.lsf.sdk.model.LampCapabilities;
import org.allseen.lsf.sdk.model.LampDataModel;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class HelperGroupManagerCallback<GROUP> extends LampGroupManagerCallback {
    public LightingSystemManager<?, GROUP, ?, ?, ?, ?, ?, ?, ?, ?, ?> manager;

    protected final ColorAverager averageHue = new ColorAverager();
    protected final ColorAverager averageSaturation = new ColorAverager();
    protected final ColorAverager averageBrightness = new ColorAverager();
    protected final ColorAverager averageColorTemp = new ColorAverager();

    protected Set<String> groupIDsWithPendingMembers = new HashSet<String>();
    protected Set<String> groupIDsWithPendingFlatten = new HashSet<String>();
    protected Map<String, TrackingID> creationTrackingIDs;

    public HelperGroupManagerCallback(LightingSystemManager<?, GROUP, ?, ?, ?, ?, ?, ?, ?, ?, ?> manager) {
        super();

        this.manager = manager;
        this.creationTrackingIDs = new HashMap<String, TrackingID>();
    }

    public void refreshAllLampGroupIDs() {
        int count = manager.getGroupCollectionManager().size();

        if (count > 0) {
            getAllLampGroupIDsReplyCB(ResponseCode.OK, manager.getGroupCollectionManager().getIDArray());
        }
    }

    @Override
    public void getAllLampGroupIDsReplyCB(ResponseCode responseCode, String[] groupIDs) {
        if (!responseCode.equals(ResponseCode.OK)) {
            manager.getGroupCollectionManager().sendErrorEvent("getAllLampGroupIDsReplyCB", responseCode);
        }

        for (final String groupID : groupIDs) {
            postProcessLampGroupID(groupID, true, true);
        }
    }

    @Override
    public void getLampGroupNameReplyCB(ResponseCode responseCode, String groupID, String language, String groupName) {
        if (!responseCode.equals(ResponseCode.OK)) {
            manager.getGroupCollectionManager().sendErrorEvent("getLampGroupNameReplyCB", responseCode, groupID);
            AllJoynManager.groupManager.getLampGroupName(groupID, LightingSystemManager.LANGUAGE);
        } else {
            postUpdateLampGroupName(groupID, groupName);
        }
    }

    @Override
    public void setLampGroupNameReplyCB(ResponseCode responseCode, String groupID, String language) {
        if (!responseCode.equals(ResponseCode.OK)) {
            manager.getGroupCollectionManager().sendErrorEvent("setLampGroupNameReplyCB", responseCode, groupID);
        }

        AllJoynManager.groupManager.getLampGroupName(groupID, LightingSystemManager.LANGUAGE);
    }

    @Override
    public void lampGroupsNameChangedCB(final String[] groupIDs) {
        for (String groupID : groupIDs) {
            postProcessLampGroupID(groupID, true, false);
        }
    }

    @Override
    public void createLampGroupReplyCB(ResponseCode responseCode, String groupID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            manager.getGroupCollectionManager().sendErrorEvent("createLampGroupReplyCB", responseCode, groupID);
        }
    }

    @Override
    public void createLampGroupWithTrackingReplyCB(ResponseCode responseCode, String groupID, long trackingID) {
        if (!responseCode.equals(ResponseCode.OK)){
            manager.getGroupCollectionManager().sendErrorEvent("", responseCode, groupID, new TrackingID(trackingID));
        } else {
            creationTrackingIDs.put(groupID,new TrackingID(trackingID));
        }
    }

    @Override
    public void lampGroupsCreatedCB(String[] groupIDs) {
        for (final String groupID : groupIDs) {
            postProcessLampGroupID(groupID, true, true);
        }
    }

    @Override
    public void getLampGroupReplyCB(ResponseCode responseCode, String groupID, LampGroup lampGroup) {
        if (!responseCode.equals(ResponseCode.OK)) {
            manager.getGroupCollectionManager().sendErrorEvent("getLampGroupReplyCB", responseCode, groupID);
            AllJoynManager.groupManager.getLampGroup(groupID);
        } else {
            postUpdateLampGroup(groupID, lampGroup);
        }
    }

    @Override
    public void deleteLampGroupReplyCB(ResponseCode responseCode, String groupID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            manager.getGroupCollectionManager().sendErrorEvent("deleteLampGroupReplyCB", responseCode, groupID);
        }
    }

    @Override
    public void lampGroupsDeletedCB(String[] groupIDs) {
        postDeleteGroups(groupIDs);
    }

    @Override
    public void transitionLampGroupStateOnOffFieldReplyCB(ResponseCode responseCode, String groupID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            manager.getGroupCollectionManager().sendErrorEvent("transitionLampGroupStateOnOffFieldReplyCB", responseCode, groupID);
        }
    }

    @Override
    public void transitionLampGroupStateHueFieldReplyCB(ResponseCode responseCode, String groupID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            manager.getGroupCollectionManager().sendErrorEvent("transitionLampGroupStateHueFieldReplyCB", responseCode, groupID);
        }
    }

    @Override
    public void transitionLampGroupStateSaturationFieldReplyCB(ResponseCode responseCode, String groupID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            manager.getGroupCollectionManager().sendErrorEvent("transitionLampGroupStateSaturationFieldReplyCB", responseCode, groupID);
        }
    }

    @Override
    public void transitionLampGroupStateBrightnessFieldReplyCB(ResponseCode responseCode, String groupID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            manager.getGroupCollectionManager().sendErrorEvent("transitionLampGroupStateBrightnessFieldReplyCB", responseCode, groupID);
        }
    }

    @Override
    public void transitionLampGroupStateColorTempFieldReplyCB(ResponseCode responseCode, String groupID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            manager.getGroupCollectionManager().sendErrorEvent("transitionLampGroupStateColorTempFieldReplyCB", responseCode, groupID);
        }
    }

    @Override
    public void lampGroupsUpdatedCB(String[] groupIDs) {
        for (String groupID : groupIDs) {
            postProcessLampGroupID(groupID, false, true);
        }
    }

    public void postProcessLampGroupID(final String groupID, final boolean needName, final boolean needState) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                boolean getName = needName;
                boolean getState = needState;

                if (!manager.getGroupCollectionManager().hasID(groupID)) {
                    manager.getGroupCollectionManager().addGroup(groupID);

                    getName = true;
                    getState = true;
                }

                if (getName) {
                    AllJoynManager.groupManager.getLampGroupName(groupID, LightingSystemManager.LANGUAGE);
                }

                if (getState) {
                    groupIDsWithPendingMembers.add(groupID);
                    AllJoynManager.groupManager.getLampGroup(groupID);
                }
            }
        });
    }

    protected void postUpdateLampGroupName(final String groupID, final String groupName) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                GroupDataModel groupModel = manager.getGroupCollectionManager().getModel(groupID);

                if (groupModel != null) {
                    boolean wasInitialized = groupModel.isInitialized();
                    groupModel.setName(groupName);
                    if (wasInitialized != groupModel.isInitialized()) {
                        postSendGroupInitialized(groupID);
                    }
                }
            }
        });

        postSendGroupChanged(groupID);
    }

    protected void postUpdateLampGroup(final String groupID, final LampGroup lampGroup) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                GroupDataModel groupModel = manager.getGroupCollectionManager().getModel(groupID);

                groupIDsWithPendingMembers.remove(groupID);

                if (groupModel != null) {
                    boolean wasInitialized = groupModel.isInitialized();
                    groupModel.setMembers(lampGroup);
                    if (wasInitialized != groupModel.isInitialized()) {
                        postSendGroupInitialized(groupID);
                    }
                }

                groupIDsWithPendingFlatten.add(groupID);

                if (groupIDsWithPendingMembers.size() == 0) {
                    for (String groupID : groupIDsWithPendingFlatten) {
                        postFlattenLampGroup(groupID);
                    }

                    groupIDsWithPendingFlatten.clear();

                    if (groupModel != null) {
                        postUpdateLampGroupState(groupModel);
                    }
                }
            }
        });
    }

    protected void postFlattenLampGroup(final String groupID) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                GroupCollectionManager<GROUP, ?> groupCollectionManager = manager.getGroupCollectionManager();
                GROUP group = groupCollectionManager.getGroup(groupID);

                if (group != null) {
                    groupCollectionManager.flattenGroup(group);
                }
            }
        });
    }

    public void postUpdateDependentLampGroups(final String lampID) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                GroupCollectionManager<GROUP, ?> groupManager = manager.getGroupCollectionManager();
                Iterator<GROUP> i = groupManager.getGroupIterator();

                while (i.hasNext()) {
                    GroupDataModel groupModel = groupManager.getModel(i.next());
                    Set<String> lampIDs = groupModel.getLamps();

                    if (lampIDs != null) {
                        if (AllLampsDataModel.ALL_LAMPS_GROUP_ID.equals(groupModel.id)){
                            lampIDs.add(lampID);
                        }

                        if (lampIDs.contains(lampID)) {
                            postUpdateLampGroupState(groupModel);
                        }
                    }
                }
            }
        });
    }

    protected void postUpdateLampGroupState(final GroupDataModel groupModel) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                LampCapabilities capability = new LampCapabilities();
                int countOn = 0;
                int countOff = 0;
                int viewColorTempGroupMin = -1;
                int viewColorTempGroupMax = -1;

                averageHue.reset();
                averageSaturation.reset();
                averageBrightness.reset();
                averageColorTemp.reset();

                Set<String> lamps = groupModel.getLamps();

                // The set of lamps can be null if the group information becomes available
                // before the lamp information is available. This is especially true for the
                // All Lamps Lamp Group, which is actually maintained by the library and not
                // by the controller.
                if (lamps != null) {
                    for (String lampID : lamps) {
                        LampDataModel lampModel = manager.getLampCollectionManager().getModel(lampID);

                        if (lampModel != null) {
                            LampDetails lampDetails = lampModel.getDetails();

                            capability.includeData(lampModel.getCapability());

                            if ( lampModel.getState().getOnOff()) {
                                countOn++;
                            } else {
                                countOff++;
                            }

                            if (lampDetails.hasColor()) {
                                averageHue.add(lampModel.getState().getHue());
                                averageSaturation.add(lampModel.getState().getSaturation());
                            }

                            if (lampDetails.isDimmable()) {
                                averageBrightness.add(lampModel.getState().getBrightness());
                            }

                            boolean hasVariableColorTemp = lampDetails.hasVariableColorTemp();
                            int viewColorTempLampMin = lampDetails.getMinTemperature();
                            int viewColorTempLampMax = hasVariableColorTemp ? lampDetails.getMaxTemperature() : viewColorTempLampMin;
                            boolean validColorTempLampMin = viewColorTempLampMin >= ColorStateConverter.VIEW_COLORTEMP_MIN && viewColorTempLampMin <= ColorStateConverter.VIEW_COLORTEMP_MAX;
                            boolean validColorTempLampMax = viewColorTempLampMax >= ColorStateConverter.VIEW_COLORTEMP_MIN && viewColorTempLampMax <= ColorStateConverter.VIEW_COLORTEMP_MAX;

                            if (hasVariableColorTemp) {
                                averageColorTemp.add(lampModel.getState().getColorTemp());
                            } else if (validColorTempLampMin) {
                                averageColorTemp.add(ColorStateConverter.convertColorTempViewToModel(viewColorTempLampMin));
                            }

                            if (validColorTempLampMin && validColorTempLampMax) {
                                if (viewColorTempGroupMin == -1 || viewColorTempGroupMin > viewColorTempLampMin) {
                                    viewColorTempGroupMin = viewColorTempLampMin;
                                }

                                if (viewColorTempGroupMax == -1 || viewColorTempGroupMax < viewColorTempLampMax) {
                                    viewColorTempGroupMax = viewColorTempLampMax;
                                }
                            }
                        } else {
                            //TODO-FIX Log.d(SampleAppActivity.TAG, "missing lamp: " + lampID);
                        }
                    }
                }

                groupModel.setCapability(capability);

                groupModel.getState().setOnOff(countOn > 0);
                groupModel.getState().setHue(averageHue.getAverage());
                groupModel.getState().setSaturation(averageSaturation.getAverage());
                groupModel.getState().setBrightness(averageBrightness.getAverage());
                groupModel.getState().setColorTemp(averageColorTemp.getAverage());

                groupModel.uniformity.power = countOn == 0 || countOff == 0;
                groupModel.uniformity.hue = averageHue.isUniform();
                groupModel.uniformity.saturation = averageSaturation.isUniform();
                groupModel.uniformity.brightness = averageBrightness.isUniform();
                groupModel.uniformity.colorTemp = averageColorTemp.isUniform();

                groupModel.viewColorTempMin = viewColorTempGroupMin != -1 ? viewColorTempGroupMin : ColorStateConverter.VIEW_COLORTEMP_MIN;
                groupModel.viewColorTempMax = viewColorTempGroupMax != -1 ? viewColorTempGroupMax : ColorStateConverter.VIEW_COLORTEMP_MAX;
            }
        });

        postSendGroupChanged(groupModel.id);
    }

    protected void postDeleteGroups(final String[] groupIDs) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                for (String groupID : groupIDs) {
                    manager.getGroupCollectionManager().removeGroup(groupID);
                }
            }
        });
    }

    protected void postSendGroupChanged(final String groupID) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                manager.getGroupCollectionManager().sendChangedEvent(groupID);
            }
        });
    }

    protected void postSendGroupInitialized(final String groupID) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                manager.getGroupCollectionManager().sendInitializedEvent(groupID, creationTrackingIDs.remove(groupID));
            }
        });
    }
}
