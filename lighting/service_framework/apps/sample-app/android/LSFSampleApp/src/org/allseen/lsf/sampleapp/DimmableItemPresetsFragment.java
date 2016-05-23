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

import java.util.Map;

import org.allseen.lsf.LampState;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.TextView;

public abstract class DimmableItemPresetsFragment extends SelectableItemTableFragment implements ItemNameAdapter{

    protected boolean allowApply = false;
    protected String currentName = null;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View root = super.onCreateView(inflater, container, savedInstanceState);

        TextView headerView = (TextView)view.findViewById(R.id.selectHeader);
        headerView.setClickable(true);
        headerView.setOnClickListener(this);

        onUpdateView(inflater, root);

        return root;
    }

    public void onUpdateView() {
        onUpdateView(getActivity().getLayoutInflater(), view);
    }

    public void onUpdateView(LayoutInflater inflater, View root) {
        SampleAppActivity activity = (SampleAppActivity)getActivity();

        table.removeAllViews();

        for (PresetDataModel presetModel : activity.presetModels.values()) {
            updateSelectableItemRow(inflater, root, presetModel.id, presetModel.tag, R.drawable.nav_more_menu_icon, presetModel.getName(), false);
        }
    }

    @Override
    protected void updateTableRows() {
        allowApply = false;
        super.updateTableRows();
        allowApply = true;
    }

    @Override
    protected String getHeaderText() {
        return getString(R.string.title_presets_save_new);
    }

    @Override
    protected boolean isItemSelected(String presetID) {
        return isItemSelected(((SampleAppActivity)getActivity()).presetModels.get(presetID));
    }

    protected boolean isItemSelected(PresetDataModel presetModel) {
        return presetModel.stateEquals(getDimmableItemDataModel().state);
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        super.onCreateOptionsMenu(menu, inflater);

        ((SampleAppActivity)getActivity()).updateActionBar(R.string.title_presets, false, false, false, false, true);
    }

    @Override
    protected int getTableRowLayout() {
        return R.layout.view_selectable_preset_row;
    }

    @Override
    protected int getSelectButtonDrawableID() {
        return R.drawable.checkbox;
    }

    @Override
    protected boolean isExclusive() {
        return true;
    }

    @Override
    public void onClick(View view) {
        final ItemNameAdapter adapter = this;

        if (view.getId() == R.id.selectHeader) {
            currentName = null;
            ((SampleAppActivity)getActivity()).showItemNameDialog(R.string.title_presets_save_new, adapter);
        } else if (view.getId() == R.id.selectableItemButtonIcon) {
            ((SampleAppActivity)getActivity()).showPresetMorePopup(view, view.getTag().toString());
        } else {
            super.onClick(view);
        }
    }

    @Override
    public String getCurrentName() {
        SampleAppActivity activity = (SampleAppActivity)getActivity();

        // Default new preset name suffix is next available index (number of preset models + 1 for now)
        return currentName == null ? String.format(activity.getString(R.string.presets_new_name), activity.presetModels.size() + 1) : currentName;
    }

    @Override
    public void onClick(DialogInterface dialog, int id) {
        EditText nameText = (EditText) (((AlertDialog) dialog).findViewById(R.id.itemNameText));
        final ItemNameAdapter adapter = this;

        currentName = nameText.getText().toString();

        if (duplicateName(currentName)) {
            AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
            builder.setTitle(R.string.duplicate_name);
            builder.setMessage(String.format(getString(R.string.duplicate_name_message_preset), currentName));
            builder.setPositiveButton(R.string.dialog_ok, new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    doSavePreset(currentName);
                }
            });
            builder.setNegativeButton(R.string.dialog_cancel, new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    dialog.cancel();
                    ((SampleAppActivity)getActivity()).showItemNameDialog(R.string.title_presets_save_new, adapter);
                }
            });
            builder.create().show();
        } else {
            doSavePreset(currentName);
        }
    }

    private boolean duplicateName(String presetName) {
        boolean isDuplicate = false;
        Map<String, PresetDataModel> currentPresets = ((SampleAppActivity) getActivity()).presetModels;
        for (String currentPresetName : currentPresets.keySet()) {
            if (currentPresets.get(currentPresetName).getName().equals(presetName)) {
                isDuplicate = true;
            }
        }
        return isDuplicate;
    }

    @Override
    public void onCheckedChanged(CompoundButton selectButton, boolean checked) {
        super.onCheckedChanged(selectButton, checked);

        if (checked && allowApply) {
            doApplyPreset(selectButton.getTag().toString());
        }
    }

    protected void doSavePreset(String presetName) {
        DimmableItemDataModel itemModel = getDimmableItemDataModel();

        if ((presetName != null) && (!presetName.isEmpty()) && (itemModel != null)) {
            doSavePreset(presetName, itemModel.state);
        }
    }

    protected void doSavePreset(String presetName, LampState presetState) {
        if ((presetName != null) && (!presetName.isEmpty()) && (presetState != null)) {
            AllJoynManager.presetManager.createPreset(presetState, presetName, SampleAppActivity.LANGUAGE);
        }
        if (getActivity() != null) {
            ((SampleAppActivity)getActivity()).onBackPressed();
        }
    }

    protected void doApplyPreset(String presetID) {
        doApplyPreset(((SampleAppActivity)getActivity()).presetModels.get(presetID));

        ((SampleAppActivity)getActivity()).onBackPressed();
    }

    protected abstract void doApplyPreset(PresetDataModel presetModel);
    protected abstract DimmableItemDataModel getDimmableItemDataModel();
}
