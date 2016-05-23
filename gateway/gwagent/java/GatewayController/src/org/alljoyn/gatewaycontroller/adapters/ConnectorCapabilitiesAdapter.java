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

import org.alljoyn.gatewaycontroller.R;
import org.alljoyn.gatewaycontroller.adapters.VisualRuleItem.ItemType;
import org.alljoyn.gatewaycontroller.sdk.RuleObjectDescription.RuleInterface;
import org.alljoyn.gatewaycontroller.sdk.RuleObjectDescription.RuleObjectPath;

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

/**
 * Manages the list of {@link VisualRuleItem}
 */
public class ConnectorCapabilitiesAdapter extends VisualArrayAdapter {

    static class ManifestItemView {

        TextView friendlyName;
        TextView name;
        TextView boolState;
    }

    // ==========================================//

    /**
     * Constructor
     * 
     * @param context
     */
    ConnectorCapabilitiesAdapter(Context context) {

        this(context, -1, null);
    }

    /**
     * Constructor
     * 
     * @param context
     * @param viewItemResId
     * @param itemsList
     */
    public ConnectorCapabilitiesAdapter(Context context, int viewItemResId, List<VisualItem> itemsList) {

        super(context, viewItemResId, itemsList);
    }

    /**
     * @see android.widget.ArrayAdapter#getView(int, android.view.View,
     *      android.view.ViewGroup)
     */
    @Override
    public View getView(int position, View convertView, ViewGroup parent) {

        View row = convertView;
        ManifestItemView manView;

        final VisualRuleItem visItem = (VisualRuleItem) getItem(position);

        manView = new ManifestItemView();

        if (visItem.getType() == ItemType.OBJECT_PATH) {

            row = inflater.inflate(R.layout.connector_manifest_rules_objectpath_item, parent, false);

            manView.friendlyName = (TextView) row.findViewById(R.id.connectorAppManifestRulesObjPathFriendlyName);
            manView.name         = (TextView) row.findViewById(R.id.connectorAppManifestRulesObjPathName);
            manView.boolState    = (TextView) row.findViewById(R.id.connectorAppManifestRulesObjPathIsPrefix);
        } else if (visItem.getType() == ItemType.INTERFACE) {

            row = inflater.inflate(R.layout.connector_manifest_rules_interface_item, parent, false);

            manView.friendlyName = (TextView) row.findViewById(R.id.connectorAppManifestRulesInterfaceFriendlyName);
            manView.name         = (TextView) row.findViewById(R.id.connectorAppManifestRulesInterfaceName);
            manView.boolState    = (TextView) row.findViewById(R.id.connectorAppManifestRulesInterfaceIsSecured);
        }

        populateData(manView, visItem);
        return row;
    }

    /**
     * Populates the {@link ManifestItemView} with the data
     * 
     * @param manView
     * @param visItem
     */
    private void populateData(ManifestItemView manView, VisualRuleItem visItem) {

        if (visItem.getType() == ItemType.OBJECT_PATH) {

            RuleObjectPath objPath = (RuleObjectPath) visItem.getVisualItem();

            manView.friendlyName.setText(objPath.getFriendlyName());
            manView.name.setText(objPath.getPath());

            String prefix = objPath.isPrefix() ? "Prefix" : "Not Prefix";
            manView.boolState.setText(prefix);
        } else if (visItem.getType() == ItemType.INTERFACE) {

            RuleInterface iface = (RuleInterface) visItem.getVisualItem();

            manView.friendlyName.setText(iface.getFriendlyName());
            manView.name.setText(iface.getName());

            String secured = iface.isSecured() ? "Secured" : "Not Secured";
            manView.boolState.setText(secured);
        }

    }
}
