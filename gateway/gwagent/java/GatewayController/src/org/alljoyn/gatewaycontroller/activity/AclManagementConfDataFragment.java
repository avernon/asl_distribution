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

import org.alljoyn.gatewaycontroller.R;
import org.alljoyn.gatewaycontroller.adapters.VisualAclConfigurableItem;
import org.alljoyn.gatewaycontroller.sdk.AclRules;
import org.alljoyn.gatewaycontroller.sdk.RemotedApp;

import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.ExpandableListView;
import android.widget.TextView;

/**
 * This fragment includes the name of the exposed services or a
 * {@link RemotedApp} and the rules for their configuration.
 */
public class AclManagementConfDataFragment extends Fragment implements OnCheckedChangeListener {

    /**
     * Fragment arguments key to pass the name of the item that has been
     * selected to be configured
     */
    public static final String CONFIGURED_ITEM_LBL = "CONFIGURED_ITEM_LBL";

    /**
     * The name of the selected item that has been selected to be configured
     */
    private TextView configuredItemLbl;

    /**
     * Allow all checkbox
     */
    private CheckBox allowAllChkBx;

    /**
     * The {@link AclRules} to be configured
     */
    private ExpandableListView configureAclListView;

    /**
     * Configurable item to be presented in this fragment
     */
    private VisualAclConfigurableItem configItem;

    /**
     * !!! IMPORTANT !!! Use this method to create the {@link Fragment} object
     * of this class.
     * 
     * @param configItem
     *            The item to be presented in this fragment
     * @param activityType
     *            The type of the activity
     * @return {@link AclManagementConfDataFragment}
     */
    public static AclManagementConfDataFragment createInstance(VisualAclConfigurableItem configItem) {

        AclManagementConfDataFragment frg = new AclManagementConfDataFragment();
        frg.configItem = configItem;
        return frg;
    }

    /**
     * Constructor
     */
    public AclManagementConfDataFragment() {
    }

    /**
     * @see android.app.Fragment#onCreate(android.os.Bundle)
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setRetainInstance(true);
    }

    /**
     * @see android.app.Fragment#onCreateView(android.view.LayoutInflater,
     *      android.view.ViewGroup, android.os.Bundle)
     */
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        View frgView         = inflater.inflate(R.layout.acl_management_conf_data_fragment, container, false);
        configuredItemLbl    = (TextView) frgView.findViewById(R.id.aclMgmtSelectedItemLbl);
        allowAllChkBx        = (CheckBox) frgView.findViewById(R.id.aclMgmtAllowAllChkBox);
        allowAllChkBx.setOnCheckedChangeListener(this);
        configureAclListView = (ExpandableListView) frgView.findViewById(R.id.aclMgmtConfigureAclListView);

        return frgView;
    }

    /**
     * @see android.app.Fragment#onResume()
     */
    @Override
    public void onResume() {

        super.onResume();
        configuredItemLbl.setText(configItem.getLabel());

        if (configItem.isRemotedApp()) {

            allowAllChkBx.setText(getActivity().getString(R.string.acl_mgmt_allow_remoted_app_lbl));
        }
        // Exposed services
        else {
            allowAllChkBx.setText(getActivity().getString(R.string.acl_mgmt_allow_exp_services_lbl));
        }
        allowAllChkBx.setChecked(configItem.isAllowAllSelected());

        configureAclListView.setAdapter(configItem.getAdapter());
    }

    /**
     * @return Configured item
     */
    public VisualAclConfigurableItem getConfigItem() {
        return configItem;
    }

    /**
     * @see android.widget.CompoundButton.OnCheckedChangeListener#onCheckedChanged(android.widget.CompoundButton,
     *      boolean)
     */
    @Override
    public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {

        if (isChecked) {
            configureAclListView.setVisibility(View.GONE);
        } else {
            configureAclListView.setVisibility(View.VISIBLE);
        }
        configItem.setAllowAllSelected(isChecked);
    }

}
