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
import org.alljoyn.gatewaycontroller.sdk.Acl;

import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;

/**
 * This fragment includes the button to create or update the
 * {@link Acl}
 */
public class AclManagementButtonFragment extends Fragment implements OnClickListener {

    /**
     * The interface is used to notify when the action button has been clicked.
     */
    public static interface ActionButtonListener {

        void onActionButtonClicked();
    }

    // =======================================================//

    /**
     * Fragment arguments key to pass the button label
     */
    public static final String ACTION_BUTTON_LBL = "ACTION_BUTTON_LABEL";

    /**
     * Fragment arguments key to pass the button enable state
     */
    public static final String ACTION_BUTTON_ENABLE = "ACTION_BUTTON_ENABLE";

    /**
     * The button to create or update the {@link Acl}
     */
    private Button actionButton;

    /**
     * Listener to the action button onClick events
     */
    private ActionButtonListener listener;

    /**
     * Constructor
     */
    public AclManagementButtonFragment() {
    }

    /**
     * @see android.app.Fragment#onCreateView(android.view.LayoutInflater,
     *      android.view.ViewGroup, android.os.Bundle)
     */
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        View frgView = inflater.inflate(R.layout.acl_management_button_fragment, container, false);

        listener      = (ActionButtonListener) getActivity();
        actionButton  = (Button) frgView.findViewById(R.id.aclMgmtActionButton);

        Bundle args   = getArguments();
        actionButton.setText(args.getString(ACTION_BUTTON_LBL));
        actionButton.setEnabled(args.getBoolean(ACTION_BUTTON_ENABLE));
        actionButton.setOnClickListener(this);

        return frgView;
    }

    /**
     * Set state of the action button
     */
    public void enableActionButton(boolean enabled) {

        actionButton.setEnabled(enabled);
    }

    /**
     * @see android.view.View.OnClickListener#onClick(android.view.View)
     */
    @Override
    public void onClick(View v) {

        listener.onActionButtonClicked();
    }
}
