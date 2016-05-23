/*
 * Copyright (c) AllSeen Alliance. All rights reserved.
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
import org.allseen.lsf.sdk.Scene;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TableLayout;
import android.widget.TextView;

public class BasicSceneV2InfoFragment extends SceneItemInfoFragment {
    public static PendingSceneV2 pendingSceneV2 = null;

    public static int indexOfElementID(String elementID) {
        int index = -1;

        for (int i = 0; index < 0 && i < pendingSceneV2.current.size(); i++) {
            if (elementID.equals(pendingSceneV2.current.get(i).id)) {
                index = i;
            }
        }

        return index;
    }

    public static void onPendingSceneElementDone() {
        int index = indexOfElementID(SceneElementV2InfoFragment.pendingSceneElement.id);

        if (index >= 0) {
            BasicSceneV2InfoFragment.pendingSceneV2.current.set(index, SceneElementV2InfoFragment.pendingSceneElement);
        } else {
            BasicSceneV2InfoFragment.pendingSceneV2.current.add(SceneElementV2InfoFragment.pendingSceneElement);
        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        view = inflater.inflate(R.layout.fragment_basic_scene_info, container, false);

        View statusView = view.findViewById(R.id.infoStatusRow);

        setImageButtonBackgroundResource(statusView, R.id.statusButtonPower, R.drawable.scene_set_icon);

        // Name
        TextView nameLabel = (TextView)statusView.findViewById(R.id.statusLabelName);
        nameLabel.setText(R.string.basic_scene_info_name);
        nameLabel.setClickable(true);
        nameLabel.setOnClickListener(this);

        TextView nameText = (TextView)statusView.findViewById(R.id.statusTextName);
        nameText.setClickable(true);
        nameText.setOnClickListener(this);

        updateInfoFields();

        return view;
    }

    @Override
    public void updateInfoFields() {
        SampleAppActivity activity = (SampleAppActivity)getActivity();
        TableLayout elementsTable = (TableLayout) view.findViewById(R.id.sceneInfoElementTable);

        elementsTable.removeAllViews();

        setTextViewValue(view, R.id.statusTextName, pendingSceneV2.name, 0);

        for (PendingSceneElementV2 sceneElement : pendingSceneV2.current) {
            int iconID;
            int textID;

            if (sceneElement.pendingPresetEffect != null) {
                iconID = R.drawable.list_constant_icon;
                textID = R.string.effect_name_preset;
            } else if (sceneElement.pendingTransitionEffect != null) {
                iconID = R.drawable.list_transition_icon;
                textID = R.string.effect_name_transition;
            } else if (sceneElement.pendingPulseEffect != null) {
                iconID = R.drawable.list_pulse_icon;
                textID = R.string.effect_name_pulse;
            } else {
                Log.w(SampleAppActivity.TAG, "Unknown effect type");

                iconID = R.drawable.list_constant_icon;
                textID = R.string.effect_name_unknown;
            }

            addElementRow(activity, elementsTable, iconID, sceneElement.id, Util.createMemberNamesString(activity, sceneElement, ", ", R.string.scene_element_members_none), textID);
        }

    }

    @Override
    public void onClick(View view) {
        int viewID = view.getId();

        if (viewID == R.id.statusLabelName || viewID == R.id.statusTextName) {
            onHeaderClick();
        } else if (viewID == R.id.detailedItemRowTextHeader || viewID == R.id.detailedItemRowTextDetails) {
            onElementTextClick(view.getTag().toString());
        } else if (viewID == R.id.detailedItemButtonMore) {
            onElementMoreClick(view, view.getTag().toString());
        }
    }

    protected void onHeaderClick() {
        SampleAppActivity activity = (SampleAppActivity)getActivity();
        Scene basicScene = LightingDirector.get().getScene(key);

        activity.showItemNameDialog(R.string.title_basic_scene_rename, new UpdateBasicSceneNameAdapter(basicScene, activity));
    }

    protected void onElementTextClick(String elementID) {
        int index = indexOfElementID(elementID);

        if (index >= 0) {
            SceneElementV2InfoFragment.pendingSceneElement = new PendingSceneElementV2(pendingSceneV2.current.get(index));

            ((ScenesPageFragment)parent).showSelectMembersChildFragment();
        } else {
            Log.e(SampleAppActivity.TAG, "Missing scene element ID " + elementID);
        }
    }

    @Override
    public void onActionAdd() {
        SceneElementV2InfoFragment.pendingSceneElement = new PendingSceneElementV2();

        ((PageMainContainerFragment)parent).showSelectMembersChildFragment();
    }

    protected void onElementMoreClick(View anchor, String elementID) {
        ((SampleAppActivity)getActivity()).onItemButtonMore(parent, SampleAppActivity.Type.ELEMENT, anchor, key, elementID, pendingSceneV2.current.size() > 1);
    }

    @Override
    public void onActionDone() {
        new BasicSceneV2TransactionManager(pendingSceneV2).start();

        parent.clearBackStack();
    }
}
