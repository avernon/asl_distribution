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

import android.app.Fragment;
import android.os.Bundle;
import android.text.method.ScrollingMovementMethod;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

/**
 * The class presents the manifest file {@link Fragment} of the
 * {@link ConnectorAppCapabilitiesActivity}
 */
public class ConnectorAppCapabilitiesFileFragment extends Fragment {

    /**
     * Manifest text file {@link TextView}
     */
    private TextView manifestText;

    /**
     * Manifest text file content
     */
    private String manifestTextContent;

    /**
     * Constructor
     */
    public ConnectorAppCapabilitiesFileFragment() {
    }

    /**
     * !!! IMPORTANT !!! Use this method to create the {@link Fragment} object
     * of this class.
     *
     * @param manifestTextContent
     *            Manifest file content
     *
     * @return {@link ConnectorAppCapabilitiesFragment}
     */
    public static ConnectorAppCapabilitiesFileFragment createInstance(String manifestTextContent) {

        ConnectorAppCapabilitiesFileFragment frg = new ConnectorAppCapabilitiesFileFragment();
        frg.manifestTextContent = manifestTextContent;

        return frg;
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

        View frgView = inflater.inflate(R.layout.connector_manifest_file_fragment, container, false);
        manifestText = (TextView) frgView.findViewById(R.id.connectorAppManifestFile);
        manifestText.setMovementMethod(new ScrollingMovementMethod());
        manifestText.setText(manifestTextContent);

        return frgView;
    }
}
