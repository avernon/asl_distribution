/*
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
*/
package org.alljoyn.dashboard.ui.adapter;


import java.util.ArrayList;

import org.alljoyn.dashboard.R;

import android.app.Activity;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

public abstract class AbstractSpinnerAdapter<T> extends ArrayAdapter<T>
{

    Activity m_activity = null;
    ViewGroup m_rowView = null;

    ArrayList<Boolean> m_isProtectedList;

    public AbstractSpinnerAdapter(Activity activity, int textViewResourceId)
    {
        super(activity, textViewResourceId);

        m_activity = activity;
        m_isProtectedList = new ArrayList<Boolean>();
    }

    @Override
    public View getDropDownView(int position, View convertView, ViewGroup parent) {
        final LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);

        m_rowView = (ViewGroup) inflater.inflate(R.layout.list_item_spinner, parent, false);

        TextView name = (TextView) m_rowView.findViewById(R.id.spinner_item_text);
        name.setText(getTextAt(position));
        if (position < m_isProtectedList.size()) // make sure the data exists
        {
            name.setCompoundDrawablesWithIntrinsicBounds(0, 0, m_isProtectedList.get(position) ? R.drawable.wifi_lock_icon : 0, 0);
        }

        return m_rowView;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        final LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);

        m_rowView = (ViewGroup) inflater.inflate(R.layout.list_item_spinner_selected, parent, false);

        TextView name = (TextView) m_rowView.findViewById(R.id.spinner_item_text);
        name.setText(getTextAt(position));
        name.setCompoundDrawablesWithIntrinsicBounds(0, 0, m_isProtectedList.get(position) ? R.drawable.wifi_lock_icon : 0, 0);

        return m_rowView;
    }

    @Override
    public void add(T t)
    {
        super.add(t);
        // assume it's not protected
        m_isProtectedList.add(false);
    }

    public void add(T t, boolean isProtected)
    {
        super.add(t);
        m_isProtectedList.add(isProtected);
    }

    @Override
    public void clear()
    {
        super.clear();
        m_isProtectedList = new ArrayList<Boolean>();
    }

    public abstract String getTextAt(int position);
}

