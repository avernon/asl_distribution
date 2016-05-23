/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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

package org.alljoyn.about.test;

import org.alljoyn.services.common.BusObjectDescription;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;


/**
 * This class is an adapter that displays the bus object description data of the device. 
 */
public class BusDescriptionAdapter extends ArrayAdapter<BusObjectDescription> {

    private LayoutInflater m_layoutInflater;

    //=================================================================
    /**
     * Creates the adapter given a context and a text view resource id.
     * @param context
     * @param resource
     */
    public BusDescriptionAdapter(Context context, int resource) {
        super(context, resource);
    }
    //=================================================================
    /**
     * @param layoutInflater Set a layout inflater.
     * Will be used to inflate the views to display.
     */
    public void setLayoutInflator(LayoutInflater layoutInflater) {
        m_layoutInflater = layoutInflater;
    }
    //=================================================================
    /* (non-Javadoc)
     * @see android.widget.ArrayAdapter#getView(int, android.view.View, android.view.ViewGroup)
     */
    @Override
    public View getView(int position, View convertView, ViewGroup parent) {

        View row;

        if (convertView == null)
            row = m_layoutInflater.inflate(R.layout.bus_description_property, parent, false);
        else
            row = convertView;

        BusObjectDescription busObject = getItem(position);

        //Bus path
        TextView propertyName = (TextView) row.findViewById(R.id.busPath);
        propertyName.setText(busObject.getPath());

        //Bus Interfaces
        TextView propertyValue = (TextView) row.findViewById(R.id.busInterfaces);
        String[] interfaces = busObject.getInterfaces();

        String res = "";
        for(int i = 0; i < interfaces.length; i++){
            res += interfaces[i];
            res += ",";
        }
        if(res.length() > 0){
            res = res.substring(0, res.length()-1);
        }

        propertyValue.setText(res);

        return row;
    }
    //=================================================================

}
