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

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

/**
 * Manages the list of {@link VisualAclConfigurableItem}
 */
public class AclMgmtConfigurableItemsAdapter extends VisualArrayAdapter {

    /**
     * Constructor
     * 
     * @param context
     */
    AclMgmtConfigurableItemsAdapter(Context context) {
        this(context, -1, null);
    }

    /**
     * Constructor
     * 
     * @param context
     * @param viewItemResId
     * @param itemsList
     */
    public AclMgmtConfigurableItemsAdapter(Context context, int viewItemResId, List<VisualItem> itemsList) {

        super(context, viewItemResId, itemsList);
    }

    /**
     * @see android.widget.ArrayAdapter#getView(int, android.view.View,
     *      android.view.ViewGroup)
     */
    @Override
    public View getView(int position, View convertView, ViewGroup parent) {

        View row = convertView;
        TextView configurableItemTv;

        if (row == null) {

            row                = inflater.inflate(viewItemResId, parent, false);
            configurableItemTv = (TextView) row.findViewById(R.id.aclDrawerItem);
            row.setTag(configurableItemTv);
        } else {

            configurableItemTv = (TextView) row.getTag();
        }

        final VisualAclConfigurableItem confItem = (VisualAclConfigurableItem) getItem(position);
        configurableItemTv.setText(confItem.getLabel());

        return row;
    }
}
