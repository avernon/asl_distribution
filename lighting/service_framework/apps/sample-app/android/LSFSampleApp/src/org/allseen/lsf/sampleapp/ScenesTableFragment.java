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

import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.text.Spannable;
import android.text.SpannableStringBuilder;
import android.text.style.ImageSpan;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import android.widget.TextView.BufferType;

public class ScenesTableFragment extends DetailedItemTableFragment {

    public ScenesTableFragment() {
        super();
        type = SampleAppActivity.Type.SCENE;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View root = super.onCreateView(inflater, container, savedInstanceState);

        for (String masterSceneID : ((SampleAppActivity) getActivity()).masterSceneModels.keySet()) {
            addElement(masterSceneID);
        }

        for (String basicSceneID : ((SampleAppActivity) getActivity()).basicSceneModels.keySet()) {
            addElement(basicSceneID);
        }

        return root;
    }

    @Override
    public void removeElement(String id) {
        super.removeElement(id);
        updateLoading();
    }

    @Override
    public void addElement(String id) {
        SampleAppActivity activity = (SampleAppActivity) getActivity();
        BasicSceneDataModel basicSceneModel = activity.basicSceneModels.get(id);
        MasterSceneDataModel masterSceneModel = activity.masterSceneModels.get(id);

        if (basicSceneModel != null) {
            String details = Util.createMemberNamesString(activity, basicSceneModel, ", ");
            insertDetailedItemRow(getActivity(), basicSceneModel.id, basicSceneModel.tag, basicSceneModel.getName(), details, false);
            updateLoading();
        } else if (masterSceneModel != null) {
            String details = Util.createSceneNamesString(activity, masterSceneModel.masterScene);
            insertDetailedItemRow(getActivity(), masterSceneModel.id, masterSceneModel.tag, masterSceneModel.getName(), details, true);
            updateLoading();
        }
    }

    @Override
    public void updateLoading() {
        super.updateLoading();

        if (AllJoynManager.controllerConnected && ((SampleAppActivity) getActivity()).basicSceneModels.size() == 0) {
            // connected but no scenes found; display create scenes screen, hide the scroll table
            layout.findViewById(R.id.scrollLoadingView).setVisibility(View.VISIBLE);
            layout.findViewById(R.id.scrollScrollView).setVisibility(View.GONE);

            View loadingView = layout.findViewById(R.id.scrollLoadingView);

            ((TextView) loadingView.findViewById(R.id.loadingText1)).setText(getActivity().getText(R.string.no_scenes));

            // creates text with the plus icon
            TextView loadingText2 = (TextView) loadingView.findViewById(R.id.loadingText2);
            String createScenesText = getActivity().getText(R.string.create_scenes).toString();
            SpannableStringBuilder ssb = new SpannableStringBuilder(createScenesText);

            // gets the plus icon, and finds where in the text it should go
            // the icon is scaled down slightly to look less "floaty" as it is bottom aligned to the text
            Drawable plusIcon = getResources().getDrawable(R.drawable.nav_add_icon_normal);
            plusIcon.setBounds(0, 0, (int) (plusIcon.getIntrinsicWidth() * 0.8), (int) (plusIcon.getIntrinsicHeight() * 0.8));

            int plusPosition = createScenesText.indexOf('+');
            ssb.setSpan(new ImageSpan(plusIcon, ImageSpan.ALIGN_BOTTOM), plusPosition, plusPosition + 1, Spannable.SPAN_EXCLUSIVE_EXCLUSIVE);
            loadingText2.setText(ssb, BufferType.SPANNABLE);

            loadingView.findViewById(R.id.loadingProgressBar).setVisibility(View.GONE);
        } else {
            View loadingView = layout.findViewById(R.id.scrollLoadingView);
            loadingView.findViewById(R.id.loadingProgressBar).setVisibility(View.VISIBLE);
        }
    }
}
