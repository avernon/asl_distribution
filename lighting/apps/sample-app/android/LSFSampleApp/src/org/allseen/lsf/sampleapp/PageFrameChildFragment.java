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

import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.CompoundButton;
import android.widget.ImageButton;
import android.widget.SeekBar;
import android.widget.TextView;

public class PageFrameChildFragment extends Fragment {
    protected PageFrameParentFragment parent;
    protected String key;
    protected String key2;
    protected View view;

    public void setParentFragment(PageFrameParentFragment parent) {
        this.parent = parent;
    }

    public void setKeys(String key1, String key2) {
        this.key = key1 != null ? key1 : "";
        this.key2 = key2 != null ? key2 : "";
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setHasOptionsMenu(true);
    }

    @Override
    public void onPause() {
        super.onPause();

        // hide soft keyboard
        InputMethodManager inputManager = (InputMethodManager) getActivity().getSystemService(Context.INPUT_METHOD_SERVICE);
        inputManager.hideSoftInputFromWindow(view.getWindowToken(), 0);
    }

    // Note that this sets the background image. The foreground image
    // may also have been set, either in XML or in code, which could
    // make this call appear to have no effect.
    protected void setImageButtonBackgroundResource(View parent, int viewID, int imageID) {
        ImageButton imageButton = (ImageButton)parent.findViewById(viewID);

        if (imageButton != null) {
            imageButton.setBackgroundResource(imageID);
        } else {
            Log.e(SampleAppActivity.TAG, "Missing image button: " + viewID);
        }
    }

    protected void setTextViewValue(View parent, int viewID, boolean value, int unitsID) {
        setTextViewValue(parent, viewID, getResources().getString(value ? R.string.value_yes : R.string.value_no), unitsID);
    }

    protected void setTextViewValue(View parent, int viewID, Enum value, int unitsID) {
        setTextViewValue(parent, viewID, value != null ? value.name() : null, unitsID);
    }

    protected void setTextViewValue(View parent, int viewID, long value, int unitsID) {
        setTextViewValue(parent, viewID, String.valueOf(value), unitsID);
    }

    protected void setTextViewValue(View parent, int viewID, String value, int unitsID) {
        TextView textView = (TextView)parent.findViewById(viewID);

        if (textView != null) {
            String text;

            if (value != null) {
                if (unitsID > 0) {
                    text = value + getResources().getString(unitsID);
                } else {
                    text = value;
                }
            } else {
                text = "";
            }

            textView.setText(text);
        }
    }

    protected void setSeekBarValue(View parent, int id, int value) {
        SeekBar seekBar = (SeekBar)parent.findViewById(id);

        if (seekBar != null) {
            Log.d(SampleAppActivity.TAG, "Set seek bar to " + value);
            seekBar.setProgress(value);
        }
    }

    protected void setCompoundButtonChecked(View parent, int id, boolean checked) {
        CompoundButton button = (CompoundButton)parent.findViewById(id);

        if (button != null) {
            button.setChecked(checked);
        }
    }

    public void onActionAdd() {
        // Nothing to do by default -- subclasses may override
    }

    public void onActionNext() {
        // Nothing to do by default -- subclasses may override
    }

    public void onActionDone() {
        // Nothing to do by default -- subclasses may override
    }
}
