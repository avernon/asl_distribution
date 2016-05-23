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
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

public class ScrollableTableFragment extends PageFrameChildFragment {
    protected TableLayout table = null;
    protected LinearLayout layout = null;
    protected SampleAppActivity.Type type;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        view = inflater.inflate(R.layout.fragment_scrollable_table, container, false);

        table = (TableLayout) view.findViewById(R.id.scrollableTable);
        layout = (LinearLayout) view.findViewById(R.id.scrollLayout);
        updateLoading();

        return view;
    }

    @Override
    public void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
    }

    public void updateLoading() {
        if (!AllJoynManager.controllerConnected) {
            // display loading controller service screen, hide the scroll table
            layout.findViewById(R.id.scrollLoadingView).setVisibility(View.VISIBLE);
            layout.findViewById(R.id.scrollScrollView).setVisibility(View.GONE);

            View loadingView = layout.findViewById(R.id.scrollLoadingView);

            String ssid = ((WifiManager) getActivity().getSystemService(Context.WIFI_SERVICE)).getConnectionInfo().getSSID();

            if (ssid == null) {
                ssid = "<unknown ssid>";
            }
            ((TextView) loadingView.findViewById(R.id.loadingText1)).setText(getActivity().getText(R.string.no_controller) + " " + ssid);
            ((TextView) loadingView.findViewById(R.id.loadingText2)).setText(getActivity().getText(R.string.loading_controller));

        } else {
            // remove the loading view, and resume showing the scroll table
            layout.findViewById(R.id.scrollLoadingView).setVisibility(View.GONE);
            layout.findViewById(R.id.scrollScrollView).setVisibility(View.VISIBLE);
        }
    }

    public void removeElement(String id) {
        final TableRow row = (TableRow) table.findViewWithTag(id);
        if (row != null) {
            getActivity().runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    table.removeView(row);
                    table.postInvalidate();
                }
            });
        }
        ((SampleAppActivity)getActivity()).setTabTitles();
    }
}
