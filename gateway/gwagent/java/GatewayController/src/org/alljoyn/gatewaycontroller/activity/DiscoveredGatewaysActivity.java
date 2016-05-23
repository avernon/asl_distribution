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

package org.alljoyn.gatewaycontroller.activity;

import java.util.ArrayList;
import java.util.List;

import org.alljoyn.gatewaycontroller.R;
import org.alljoyn.gatewaycontroller.adapters.DiscoveredGatewaysAdapter;
import org.alljoyn.gatewaycontroller.adapters.VisualGateway;
import org.alljoyn.gatewaycontroller.adapters.VisualItem;
import org.alljoyn.gatewaycontroller.sdk.GatewayController;
import org.alljoyn.gatewaycontroller.sdk.GatewayMgmtApp;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ListView;

/**
 * Discovered gateways activity
 */
public class DiscoveredGatewaysActivity extends BaseActivity implements OnItemClickListener {
    private static final String TAG = "gwcapp" + DiscoveredGatewaysActivity.class.getSimpleName();

    /**
     * Gateway listview
     */
    private ListView gatewayListView;

    /**
     * Gateways adapter
     */
    private DiscoveredGatewaysAdapter adapter;

    /**
     * @see org.alljoyn.gatewaycontroller.activity.BaseActivity#onCreate(android.os.Bundle)
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.discovered_gateways);

        setTitle(R.string.discovered_gateways_activity);
    }

    /**
     * @see android.app.Activity#onStart()
     */
    @Override
    protected void onStart() {

        super.onStart();

        gatewayListView           = (ListView) findViewById(R.id.gatewaysList);
        List<VisualItem> gateways = new ArrayList<VisualItem>();

        adapter = new DiscoveredGatewaysAdapter(this, R.layout.discovered_gateways_item, gateways);
        gatewayListView.setAdapter(adapter);
        gatewayListView.setEmptyView(findViewById(R.id.discoveredGatewayNoItems));
        gatewayListView.setOnItemClickListener(this);

        retrieveGateways();
    }

    /**
     * @see org.alljoyn.gatewaycontroller.activity.BaseActivity#onGatewayMgmtAnnounced()
     */
    @Override
    protected void onGatewayMgmtAppAnnounced() {
        retrieveGateways();
    }

    /**
     * Retrieve the list of gateways
     */
    private void retrieveGateways() {

        List<GatewayMgmtApp> gatewayApps = GatewayController.getInstance().getGatewayMgmtApps();

        adapter.clear();
        for (GatewayMgmtApp gw : gatewayApps) {
            adapter.add(new VisualGateway(gw));
        }

        Log.d(TAG, "Found gateways: '" + gatewayApps + "'");
        adapter.notifyDataSetChanged();
    }

    /**
     * @see android.widget.AdapterView.OnItemClickListener#onItemClick(android.widget.AdapterView,
     *      android.view.View, int, long)
     */
    @Override
    public void onItemClick(AdapterView<?> adapter, View clickedView, int position, long rowId) {

        VisualGateway vg = (VisualGateway) this.adapter.getItem(position);

        app.setSelectedGatewayApp(vg.getGateway());

        // If we have an old session, we need to close it when selecting a new gateway
        app.leaveSession();

        Intent intent = new Intent(this, ConnectorAppsActivity.class);
        intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_SINGLE_TOP | Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(intent);
    }

}
