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

package org.alljoyn.config.test;

import java.util.Collection;
import java.util.HashMap;
import java.util.UUID;

import org.alljoyn.config.test.ConfigApplication.Device;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.ActivityInfo;
import android.content.res.Configuration;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnCreateContextMenuListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

/**
 * The DeviceListActivity displays all the devices we received announcements
 * from.
 */
public class MainActivity extends Activity implements OnCreateContextMenuListener {

    protected static final String TAG = ConfigApplication.TAG;
    private BroadcastReceiver m_receiver;
    private Button m_AJConnect;
    private TextView m_currentNetwork;
    ArrayAdapter<Device> deviceAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.main_layout);
        ConfigApplication application = (ConfigApplication) getApplication();

        // ************** AllJoyn Connect/Disconnect Button ******************
        m_AJConnect = (Button) findViewById(R.id.AllJoynConnect);
        m_AJConnect.setOnClickListener(new OnClickListener() {

            @Override
            public void onClick(View v) {

                if (m_AJConnect.getText().equals(getString(R.string.AllJoynConnect))) {
                    allJoynConnect();
                } else if (m_AJConnect.getText().equals(getString(R.string.AllJoynDisconnect))) {
                    allJoynDisconnect();
                }
            }
        });

        // ***************** Current Network *********************
        m_currentNetwork = (TextView) findViewById(R.id.current_network_name);
        String ssid = application.getCurrentSSID();
        m_currentNetwork.setText(getString(R.string.current_network, ssid));

        // ************** Announced names list ******************
        ListView listView = (ListView) findViewById(R.id.device_list);
        deviceAdapter = new ArrayAdapter<Device>(this, android.R.layout.simple_list_item_1);
        listView.setAdapter(deviceAdapter);
        listView.setOnItemClickListener(new OnItemClickListener() {

            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Device selectedDevice = deviceAdapter.getItem(position);
                Intent intent = new Intent(MainActivity.this, ConfigActivity.class);
                intent.putExtra(ConfigApplication.EXTRA_DEVICE_ID, selectedDevice.appId);
                startActivity(intent);
            }

        });

        // ************** Class receiver ******************
        m_receiver = new BroadcastReceiver() {

            @Override
            public void onReceive(Context context, Intent intent) {
                if (ConfigApplication.ACTION_DEVICE_FOUND.equals(intent.getAction()) || ConfigApplication.ACTION_DEVICE_LOST.equals(intent.getAction())) {

                    deviceAdapter.clear();
                    HashMap<UUID, Device> deviceList = ((ConfigApplication) getApplication()).getDeviceList();
                    if (deviceList == null) {
                        return;
                    }

                    Collection<Device> devices = deviceList.values();
                    deviceAdapter.addAll(devices);
                }

                else if (ConfigApplication.ACTION_CONNECTED_TO_NETWORK.equals(intent.getAction())) {

                    String ssid = intent.getStringExtra(ConfigApplication.EXTRA_NETWORK_SSID);
                    m_currentNetwork.setText(getString(R.string.current_network, ssid));

                }
            }
        };
        IntentFilter filter = new IntentFilter();
        filter.addAction(ConfigApplication.ACTION_DEVICE_FOUND);
        filter.addAction(ConfigApplication.ACTION_DEVICE_LOST);
        filter.addAction(ConfigApplication.ACTION_CONNECTED_TO_NETWORK);
        registerReceiver(m_receiver, filter);

    }

    // Connect to AllJoyn
    private void allJoynConnect() {
        AlertDialog.Builder alert = new AlertDialog.Builder(MainActivity.this);
        alert.setTitle(R.string.alert_title_set_daemon_name);

        final EditText input = new EditText(MainActivity.this);
        input.setText("org.alljoyn.BusNode.ConfigClient");
        alert.setView(input);

        alert.setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(final DialogInterface dialog, int whichButton) {

                runOnUiThread(new Runnable() {

                    @Override
                    public void run() {

                        dialog.dismiss();
                        ((ConfigApplication) getApplication()).setRealmName(input.getText().toString());
                        m_AJConnect.setText(R.string.AllJoynDisconnect);
                        ((ConfigApplication) getApplication()).doConnect();
                    }
                });
            }
        });
        alert.setNegativeButton(android.R.string.cancel, null);
        alert.show();
    }

    // Disconnect from AllJoyn
    private void allJoynDisconnect() {
        AlertDialog.Builder alert = new AlertDialog.Builder(this);
        alert.setMessage(R.string.alert_msg_disconnect_from_alljoyn);

        alert.setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(final DialogInterface dialog, int whichButton) {
                runOnUiThread(new Runnable() {

                    @Override
                    public void run() {
                        dialog.dismiss();
                        m_AJConnect.setText(R.string.AllJoynConnect);
                        deviceAdapter.clear();
                        ((ConfigApplication) getApplication()).doDisconnect();
                    }
                });
            }
        });

        alert.setNegativeButton(android.R.string.cancel, null);
        alert.show();

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        ((ConfigApplication) getApplication()).doDisconnect();
        unregisterReceiver(m_receiver);
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
    }

}
