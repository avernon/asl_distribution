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
package org.allseen.lsf.sampleapp;

import java.util.Collection;
import java.util.Iterator;
import java.util.List;

import org.allseen.lsf.LampDetails;
import org.allseen.lsf.LampGroup;
import org.allseen.lsf.sdk.model.ColorStateConverter;
import org.allseen.lsf.sdk.model.GroupDataModel;
import org.allseen.lsf.sdk.model.LampCapabilities;
import org.allseen.lsf.sdk.model.LampDataModel;
import org.allseen.lsf.sdk.model.NoEffectDataModel;

import android.view.Menu;
import android.view.MenuInflater;

public class BasicSceneSelectMembersFragment extends SelectMembersFragment {

    public BasicSceneSelectMembersFragment() {
        super(R.string.label_basic_scene);
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        super.onCreateOptionsMenu(menu, inflater);

        ((SampleAppActivity)getActivity()).updateActionBar(R.string.title_basic_scene_element_add, false, false, true, false, true);
    }

    @Override
    protected String getHeaderText() {
        return getString(R.string.basic_scene_select_members);
    }

    @Override
    protected LampGroup getPendingMembers() {
        return ((SampleAppActivity)getActivity()).pendingBasicSceneElementMembers;
    }

    @Override
    protected String getPendingItemID() {
        return ((SampleAppActivity)getActivity()).pendingBasicSceneModel.id;
    }

    @Override
    protected void processSelection(SampleAppActivity activity, List<String> lampIDs, List<String> groupIDs, List<String> sceneIDs, LampCapabilities capability) {
        activity.pendingBasicSceneElementCapability = capability;
        super.processSelection(activity, lampIDs, groupIDs, sceneIDs, capability);
    }

    @Override
    protected void processSelection(SampleAppActivity activity, List<String> lampIDs, List<String> groupIDs, List<String> sceneIDs) {
        activity.pendingBasicSceneElementMembers.setLamps(lampIDs.toArray(new String[lampIDs.size()]));
        activity.pendingBasicSceneElementMembers.setLampGroups(groupIDs.toArray(new String[groupIDs.size()]));

        activity.pendingBasicSceneElementMembersHaveEffects = false;
        activity.pendingBasicSceneElementMembersMinColorTemp = -1;
        activity.pendingBasicSceneElementMembersMaxColorTemp = -1;

        activity.pendingBasicSceneElementColorTempAverager.reset();

        processGroupSelection(activity, groupIDs);
        processLampSelection(activity, lampIDs);

        if (activity.pendingBasicSceneElementMembersMinColorTemp == -1) {
            activity.pendingBasicSceneElementMembersMinColorTemp = ColorStateConverter.VIEW_COLORTEMP_MIN;
        }

        if (activity.pendingBasicSceneElementMembersMaxColorTemp == -1) {
            activity.pendingBasicSceneElementMembersMaxColorTemp = ColorStateConverter.VIEW_COLORTEMP_MAX;
        }
    }

    protected void processGroupSelection(SampleAppActivity activity, List<String> groupIDs) {
        if (groupIDs.size() > 0) {
            for (Iterator<String> it = groupIDs.iterator(); it.hasNext();) {
                processLampSelection(activity, it.next());
            }
        }
    }

    protected void processLampSelection(SampleAppActivity activity, String groupID) {
        GroupDataModel groupModel = activity.systemManager.getGroupCollectionManager().getModel(groupID);

        if (groupModel != null) {
            processLampSelection(activity, groupModel.getLamps());
        }
    }

    protected void processLampSelection(SampleAppActivity activity, Collection<String> lampIDs) {
        if (lampIDs.size() > 0) {
            for (Iterator<String> it = lampIDs.iterator(); it.hasNext();) {
                LampDataModel lampModel = activity.systemManager.getLampCollectionManager().getModel(it.next());

                if (lampModel != null) {
                    LampDetails lampDetails = lampModel.getDetails();

                    if (lampDetails != null) {
                        boolean lampHasEffects = lampDetails.hasEffects();
                        boolean lampHasVariableColorTemp = lampDetails.hasVariableColorTemp();
                        int lampMinTemperature = lampDetails.getMinTemperature();
                        int lampMaxTemperature = lampHasVariableColorTemp ? lampDetails.getMaxTemperature() : lampMinTemperature;
                        boolean lampValidColorTempMin = lampMinTemperature >= ColorStateConverter.VIEW_COLORTEMP_MIN && lampMinTemperature <= ColorStateConverter.VIEW_COLORTEMP_MAX;
                        boolean lampValidColorTempMax = lampMaxTemperature >= ColorStateConverter.VIEW_COLORTEMP_MIN && lampMaxTemperature <= ColorStateConverter.VIEW_COLORTEMP_MAX;

                        if (lampHasEffects) {
                            activity.pendingBasicSceneElementMembersHaveEffects = true;
                        }

                        if (lampHasVariableColorTemp) {
                            activity.pendingBasicSceneElementColorTempAverager.add(lampModel.state.getColorTemp());
                        } else if (lampValidColorTempMin) {
                            activity.pendingBasicSceneElementColorTempAverager.add(ColorStateConverter.convertColorTempViewToModel(lampMinTemperature));
                        }

                        if (lampValidColorTempMin && lampValidColorTempMax) {
                            if (lampMinTemperature < activity.pendingBasicSceneElementMembersMinColorTemp || activity.pendingBasicSceneElementMembersMinColorTemp == -1) {
                                activity.pendingBasicSceneElementMembersMinColorTemp = lampMinTemperature;
                            }

                            if (lampMaxTemperature < activity.pendingBasicSceneElementMembersMaxColorTemp || activity.pendingBasicSceneElementMembersMaxColorTemp == -1) {
                                activity.pendingBasicSceneElementMembersMaxColorTemp = lampMaxTemperature;
                            }
                        }
                    }
                }
            }
        }
    }

    @Override
    public void onActionNext() {
        SampleAppActivity activity = (SampleAppActivity)getActivity();

        if (processSelection()) {
            if (activity.pendingBasicSceneElementMembersHaveEffects) {
                if (activity.pendingNoEffectModel != null) {
                    showNoEffectChildFragment(activity);
                } else if (activity.pendingTransitionEffectModel != null) {
                    showTransitionEffectChildFragment(activity);
                } else if (activity.pendingPulseEffectModel != null) {
                    showPulseEffectChildFragment(activity);
                } else {
                    showSelectEffectChildFragment(activity);
                }
            } else {
                if (activity.pendingNoEffectModel == null) {
                    activity.pendingNoEffectModel = new NoEffectDataModel();
                }

                showNoEffectChildFragment(activity);
            }
        }
    }

    protected void showSelectEffectChildFragment(SampleAppActivity activity) {
        activity.pendingNoEffectModel = null;
        activity.pendingTransitionEffectModel = null;
        activity.pendingPulseEffectModel = null;

        ((ScenesPageFragment)parent).showSelectEffectChildFragment();
    }

    protected void showNoEffectChildFragment(SampleAppActivity activity) {
        activity.pendingTransitionEffectModel = null;
        activity.pendingPulseEffectModel = null;

        ((ScenesPageFragment)parent).showNoEffectChildFragment();
    }

    protected void showTransitionEffectChildFragment(SampleAppActivity activity) {
        activity.pendingNoEffectModel = null;
        activity.pendingPulseEffectModel = null;

        ((ScenesPageFragment)parent).showTransitionEffectChildFragment();
    }

    protected void showPulseEffectChildFragment(SampleAppActivity activity) {
        activity.pendingNoEffectModel = null;
        activity.pendingTransitionEffectModel = null;

        ((ScenesPageFragment)parent).showPulseEffectChildFragment();
    }

    @Override
    protected int getMixedSelectionMessageID() {
        return R.string.mixing_lamp_types_message_scene;
    }

    @Override
    protected int getMixedSelectionPositiveButtonID() {
        return R.string.create_scene;
    }
}
