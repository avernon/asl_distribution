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

import java.util.List;

import org.alljoyn.about.AboutKeys;
import org.alljoyn.about.test.AboutApplication.AboutProperty;

import android.content.Context;
import android.database.DataSetObserver;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ListAdapter;
import android.widget.TextView;


/**
 * This class implements a list adapter in order to display the list of
 * all the device about fields.
 */
public class AboutAdapter extends ArrayAdapter<AboutProperty> implements ListAdapter {

    private LayoutInflater m_layoutInflater;
    private List<AboutProperty> m_properties;

    //====================================================================
    /**
     * Creates the adapter given a context and a text view resource id.
     * @param context
     * @param textViewResourceId
     */
    public AboutAdapter(Context context, int textViewResourceId) {
        super(context, textViewResourceId);
    }
    //====================================================================
    /**
     * @param layoutInflater Set a layout inflater.
     * Will be used to inflate the views to display.
     */
    public void setLayoutInflator(LayoutInflater layoutInflater){
        m_layoutInflater = layoutInflater;
    }
    //====================================================================
    /* (non-Javadoc)
     * @see android.widget.ArrayAdapter#getView(int, android.view.View, android.view.ViewGroup)
     */
    @Override
    public View getView(int position, View convertView, ViewGroup parent)
    {
        View row;

        if (convertView == null)
            row = m_layoutInflater.inflate(R.layout.about_property, parent, false);
        else
            row = convertView;

        final AboutProperty property = m_properties.get(position);

        //Property name
        TextView propertyName = (TextView) row.findViewById(R.id.propertyName);
        propertyName.setText(property.key);

        //Property value
        TextView propertyValue = (TextView) row.findViewById(R.id.propertyValue);
        propertyValue.setText(property.value.toString());

        //Handle the case of SupportedLanguages:
        if(property.value instanceof String[] && property.key.equals(AboutKeys.ABOUT_SUPPORTED_LANGUAGES)){
            String[] ss = (String[])property.value;
            String res = "";
            for (int i = 0; i < ss.length; i++) {
                if(!ss[i].equals(""))
                    res += ","+ss[i];
            }
            if(res.length() > 0)
                res = res.substring(1);
            propertyValue.setText(res);
        }
        return row;
    }
    //====================================================================
    /**
     * @param data Sets the adapter data to display.
     */
    public void setData(List<AboutProperty> data) {

        m_properties = data;
    }
    //====================================================================
    /* (non-Javadoc)
     * @see android.widget.ArrayAdapter#getCount()
     */
    @Override
    public int getCount() {
        if (isEmpty())
            return 0;
        return m_properties.size();
    }
    //====================================================================
    /* (non-Javadoc)
     * @see android.widget.ArrayAdapter#getItem(int)
     */
    @Override
    public AboutProperty getItem(int position) {
        if (isEmpty())
            return null;
        return m_properties.get(position);
    }
    //====================================================================
    /* (non-Javadoc)
     * @see android.widget.ArrayAdapter#getItemId(int)
     */
    @Override
    public long getItemId(int position) {
        if (isEmpty())
            return -1;
        return m_properties.get(position).hashCode();
    }
    //====================================================================
    /* (non-Javadoc)
     * @see android.widget.BaseAdapter#getItemViewType(int)
     */
    @Override
    public int getItemViewType(int position) {
        return 1;
    }
    //====================================================================
    /* (non-Javadoc)
     * @see android.widget.BaseAdapter#getViewTypeCount()
     */
    @Override
    public int getViewTypeCount() {
        return 1;
    }
    //====================================================================
    /* (non-Javadoc)
     * @see android.widget.BaseAdapter#hasStableIds()
     */
    @Override
    public boolean hasStableIds() {
        return false;
    }
    //====================================================================
    /* (non-Javadoc)
     * @see android.widget.BaseAdapter#isEmpty()
     */
    @Override
    public boolean isEmpty() {
        return (m_properties == null || m_properties.size()==0);
    }
    //====================================================================
    /* (non-Javadoc)
     * @see android.widget.BaseAdapter#registerDataSetObserver(android.database.DataSetObserver)
     */
    @Override
    public void registerDataSetObserver(DataSetObserver arg0) {

    }
    //====================================================================
    /* (non-Javadoc)
     * @see android.widget.BaseAdapter#unregisterDataSetObserver(android.database.DataSetObserver)
     */
    @Override
    public void unregisterDataSetObserver(DataSetObserver arg0) {

    }
    //====================================================================
    /* (non-Javadoc)
     * @see android.widget.BaseAdapter#areAllItemsEnabled()
     */
    @Override
    public boolean areAllItemsEnabled() {
        return true;
    }
    //====================================================================
    /* (non-Javadoc)
     * @see android.widget.BaseAdapter#isEnabled(int)
     */
    @Override
    public boolean isEnabled(int arg0) {
        return true;
    }
    //====================================================================
    /* (non-Javadoc)
     * @see android.widget.ArrayAdapter#clear()
     */
    @Override
    public void clear() {
        super.clear();
        if(m_properties != null)
            m_properties.clear();
    }
    //====================================================================
}
