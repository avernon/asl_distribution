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

import org.alljoyn.gatewaycontroller.GWControllerSampleApplication;
import org.alljoyn.gatewaycontroller.R;
import org.alljoyn.gatewaycontroller.sdk.Acl;
import org.alljoyn.gatewaycontroller.sdk.ConnectorApp;

import android.app.Activity;
import android.app.Application;
import android.app.Fragment;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.TextView;

/**
 * This fragment includes the {@link ConnectorApp} name and the the name
 * of the selected {@link Acl}
 */
public class AclManagementHeaderFragment extends Fragment implements TextWatcher {

    /**
     * The interface is used to notify about changes of the ACL name
     * {@link EditText} value.
     */
    public static interface AclNameListener {

        /**
         * The ACL name was changed.
         *
         * @param aclName
         *            The text content of the ACL name {@link EditText}
         */
        void onTextChanged(String aclName);
    }

    // =======================================================//

    /**
     * The {@link Application} object
     */
    private GWControllerSampleApplication app;

    /**
     * The listener of the ACL name change events
     */
    private AclNameListener listener;

    /**
     * The name of the selected {@link ConnectorApp}
     */
    private TextView connAppName;

    /**
     * The name of the {@link Acl} that is created or updated
     */
    private EditText aclName;

    /**
     * Constructor
     */
    public AclManagementHeaderFragment() {
    }

    /**
     * @see android.app.Fragment#onCreateView(android.view.LayoutInflater,
     *      android.view.ViewGroup, android.os.Bundle)
     */
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        Activity act = getActivity();
        app          = (GWControllerSampleApplication) act.getApplicationContext();
        listener     = (AclNameListener) act;

        View frgView = inflater.inflate(R.layout.acl_management_header_fragment, container, false);

        connAppName  = (TextView) frgView.findViewById(R.id.aclMgmtConnAppNameTv);
        aclName      = (EditText) frgView.findViewById(R.id.aclMgmtAclNameEt);

        connAppName.setText(app.getSelectedConnectorApp().getFriendlyName());

        Acl acl = app.getSelectedAcl();
        if (acl != null) {

            aclName.setText(acl.getName());
        }

        aclName.addTextChangedListener(this);

        return frgView;
    }

    /**
     * @see android.text.TextWatcher#afterTextChanged(android.text.Editable)
     */
    @Override
    public void afterTextChanged(Editable s) {

        listener.onTextChanged(s.toString());
    }

    /**
     * @see android.text.TextWatcher#beforeTextChanged(java.lang.CharSequence,
     *      int, int, int)
     */
    @Override
    public void beforeTextChanged(CharSequence s, int start, int count, int after) {
    }

    /**
     * @see android.text.TextWatcher#onTextChanged(java.lang.CharSequence, int,
     *      int, int)
     */
    @Override
    public void onTextChanged(CharSequence s, int start, int before, int count) {
    }

    /**
     * @return Return the {@link Acl} name
     */
    public String getAclName() {

        return aclName.getText().toString();
    }
}
