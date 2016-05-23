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
import org.alljoyn.gatewaycontroller.adapters.ConnectorCapabilitiesAdapter;
import org.alljoyn.gatewaycontroller.adapters.VisualItem;
import org.alljoyn.gatewaycontroller.adapters.VisualRuleItem;
import org.alljoyn.gatewaycontroller.adapters.VisualRuleItem.ItemType;
import org.alljoyn.gatewaycontroller.sdk.ConnectorApp;
import org.alljoyn.gatewaycontroller.sdk.ConnectorCapabilities;
import org.alljoyn.gatewaycontroller.sdk.RuleObjectDescription;
import org.alljoyn.gatewaycontroller.sdk.RuleObjectDescription.RuleInterface;

import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ListView;

/**
 * The class presents the {@link ConnectorApp} capabilities {@link Fragment} of the
 * {@link ConnectorAppCapabilitiesActivity}
 */
public class ConnectorAppCapabilitiesFragment extends Fragment {

    /**
     * Exposed services to be presented
     */
    private ListView exposedServicesListView;

    /**
     * Remoted services to presented
     */
    private ListView remotedServicesListView;

    /**
     * Exposed services adapter
     */
    private ConnectorCapabilitiesAdapter exposedServicesAdapter;

    /**
     * Remoted services adapter
     */
    private ConnectorCapabilitiesAdapter remotedServicesAdapter;

    /**
     * {@link ConnectorCapabilities} to be presented
     */
    private ConnectorCapabilities connectorCapabilities;

    /**
     * Constructor
     */
    public ConnectorAppCapabilitiesFragment() {
    }

    /**
     * !!! IMPORTANT !!! Use this method to create the {@link Fragment} object
     * of this class.
     *
     * @param connectorCapabilities
     *            {@link ConnectorCapabilities}
     * @return {@link ConnectorAppCapabilitiesFragment}
     */
    public static ConnectorAppCapabilitiesFragment createInstance(ConnectorCapabilities connectorCapabilities) {

        ConnectorAppCapabilitiesFragment frg = new ConnectorAppCapabilitiesFragment();
        frg.connectorCapabilities            = connectorCapabilities;

        return frg;
    }

    /**
     * @see android.app.Fragment#onCreate(android.os.Bundle)
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        this.setRetainInstance(true);
    }

    /**
     * @see android.app.Fragment#onCreateView(android.view.LayoutInflater,
     *      android.view.ViewGroup, android.os.Bundle)
     */
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        View frgView = inflater.inflate(R.layout.connector_manifest_rules_fragment, container, false);

        exposedServicesListView = (ListView) frgView.findViewById(R.id.connectorAppManifestRulesExpServicesRules);
        remotedServicesListView = (ListView) frgView.findViewById(R.id.connectorAppManifestRulesRemServicesRules);

        exposedServicesListView.setEmptyView(frgView.findViewById(R.id.connectorAppManifestRulesExpServicesRulesNotFound));

        remotedServicesListView.setEmptyView(frgView.findViewById(R.id.connectorAppManifestRulesRemServicesRulesNotFound));

        exposedServicesAdapter = new ConnectorCapabilitiesAdapter(getActivity(), R.layout.connector_manifest_rules_objectpath_item, new ArrayList<VisualItem>());

        exposedServicesListView.setAdapter(exposedServicesAdapter);

        remotedServicesAdapter = new ConnectorCapabilitiesAdapter(getActivity(), R.layout.connector_manifest_rules_objectpath_item, new ArrayList<VisualItem>());

        remotedServicesListView.setAdapter(remotedServicesAdapter);

        populateVisualData();

        return frgView;
    }

    /**
     * Fills the adapters
     */
    private void populateVisualData() {

        fillAdapter(exposedServicesAdapter, connectorCapabilities.getExposedServices());
        exposedServicesAdapter.notifyDataSetChanged();

        fillAdapter(remotedServicesAdapter, connectorCapabilities.getRemotedServices());
        remotedServicesAdapter.notifyDataSetChanged();
    }

    /**
     * Fills the given adapter with the given rules
     *
     * @param adapter
     * @param manRules
     */
    private void fillAdapter(ConnectorCapabilitiesAdapter adapter, List<RuleObjectDescription> manRules) {

        for (RuleObjectDescription rule : manRules) {

            adapter.add(new VisualRuleItem(rule.getObjectPath(), ItemType.OBJECT_PATH));

            for (RuleInterface iface : rule.getInterfaces()) {

                adapter.add(new VisualRuleItem(iface, ItemType.INTERFACE));
            }
        }
    }// fillAdapter

}
