/******************************************************************************
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
 ******************************************************************************/

package org.alljoyn.gatewaycontroller.adapters;

import java.util.List;

import org.alljoyn.gatewaycontroller.GWControllerSampleApplication;
import org.alljoyn.gatewaycontroller.R;
import org.alljoyn.gatewaycontroller.activity.ConnectorAppActivity;
import org.alljoyn.gatewaycontroller.sdk.ConnectorApp;
import org.alljoyn.gatewaycontroller.sdk.ConnectorAppStatus;
import org.alljoyn.gatewaycontroller.sdk.ConnectorAppStatus.ConnectionStatus;
import org.alljoyn.gatewaycontroller.sdk.ConnectorAppStatus.InstallStatus;
import org.alljoyn.gatewaycontroller.sdk.ConnectorAppStatus.OperationalStatus;

import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

/**
 * Manages the list of {@link VisualConnectorApp}s
 */
public class ConnectorAppsAdapter extends VisualArrayAdapter {
    private static final String TAG = "gwcapp" + ConnectorAppsAdapter.class.getSimpleName();

    static class ConnectorAppView {

        Button appName;
        TextView connStatus;
        TextView operStatus;
        TextView installStatus;
    }

    // ======================================//

    /**
     * Constructor
     *
     * @param context
     */
    ConnectorAppsAdapter(Context context) {
        this(context, -1, null);
    }

    /**
     * Constructor
     *
     * @param context
     * @param viewItemResId
     * @param itemsList
     */
    public ConnectorAppsAdapter(Context context, int viewItemResId, List<VisualItem> itemsList) {

        super(context, viewItemResId, itemsList);
    }

    /**
     * @see android.widget.ArrayAdapter#getView(int, android.view.View,
     *      android.view.ViewGroup)
     */
    @Override
    public View getView(int position, View convertView, ViewGroup parent) {

        View row = convertView;
        ConnectorAppView connAppView;

        if (row == null) {

            row = inflater.inflate(viewItemResId, parent, false);

            connAppView               = new ConnectorAppView();
            connAppView.appName       = (Button) row.findViewById(R.id.connectorAppName);
            connAppView.connStatus    = (TextView) row.findViewById(R.id.connectorAppConnStatus);
            connAppView.installStatus = (TextView) row.findViewById(R.id.connectorAppInstallStatus);
            connAppView.operStatus    = (TextView) row.findViewById(R.id.connectorAppOperStatus);

            row.setTag(connAppView);
        } else {
            connAppView = (ConnectorAppView) row.getTag();
        }

        final VisualConnectorApp visConnectorApp = (VisualConnectorApp) getItem(position);

        connAppView.appName.setText(visConnectorApp.getApp().getFriendlyName());
        connAppView.appName.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {

                ConnectorApp selectedConnectorApp = visConnectorApp.getApp();
                Log.d(TAG, "Selected Connector Application, id: '" + selectedConnectorApp.getAppId() + "'");
                ((GWControllerSampleApplication) context.getApplicationContext()).setSelectedConnectorApp(selectedConnectorApp);

                Intent intent = new Intent(context, ConnectorAppActivity.class);
                intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_SINGLE_TOP | Intent.FLAG_ACTIVITY_NEW_TASK);
                context.startActivity(intent);
            }
        });

        ConnectorAppStatus connAppStatus = visConnectorApp.getAppStatus();
        updateStatus(connAppView.connStatus, connAppView.operStatus, connAppView.installStatus, connAppStatus);

        return row;
    }

    /**
     * Updates received {@link TextView} of the statuses with the data received
     * in the {@link ConnectorAppStatus}
     *
     * @param connStatusTv
     * @param operStatusTv
     * @param installStatusTv
     * @param status
     */
    public static void updateStatus(TextView connStatusTv, TextView operStatusTv, TextView installStatusTv, ConnectorAppStatus connAppStatus) {

        final String UNKNOWN_STATUS = "unknown";

        if (connAppStatus == null) {

            connStatusTv.setText(UNKNOWN_STATUS);
            installStatusTv.setText(UNKNOWN_STATUS);
            operStatusTv.setText(UNKNOWN_STATUS);

            return;
        }

        ConnectionStatus connStatus = connAppStatus.getConnectionStatus();
        int color                   = Color.parseColor(VisualConnectorApp.getConnStatusColor(connStatus));
        connStatusTv.setText(connStatus.DESC);
        connStatusTv.setTextColor(color);

        InstallStatus instStatus = connAppStatus.getInstallStatus();
        color                    = Color.parseColor(VisualConnectorApp.getInstallStatusColor(instStatus));
        installStatusTv.setText(instStatus.DESC);
        installStatusTv.setTextColor(color);

        OperationalStatus operStatus = connAppStatus.getOperationalStatus();
        color                        = Color.parseColor(VisualConnectorApp.getOperationalStatusColor(operStatus));
        operStatusTv.setText(operStatus.DESC);
        operStatusTv.setTextColor(color);
    }
}
