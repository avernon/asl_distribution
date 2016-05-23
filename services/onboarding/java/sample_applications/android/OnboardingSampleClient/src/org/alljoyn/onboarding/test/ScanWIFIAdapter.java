/******************************************************************************
 * Copyright (c) 2013, AllSeen Alliance. All rights reserved.
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

package org.alljoyn.onboarding.test;

import android.content.Context;
import android.database.DataSetObserver;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiManager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ListAdapter;
import android.widget.TextView;

/**
 * This class is an adapter to display the list of
 * all the networks we scanned.
 */
public class ScanWIFIAdapter extends ArrayAdapter<ScanResult> implements ListAdapter{

	private static final String TAG = "ScanWIFIAdapter";
	static class ViewHolder {
		public TextView textWifiName;
		public TextView textWifiCapabiliteis;
		public TextView textWifiLevel;
	}
	
	private LayoutInflater m_layoutInflater;
	
	//====================================================================
	/**
	 * Creates the adapter given a context and a text view resource id.
	 * @param context
	 * @param textViewResourceId
	 */
	public ScanWIFIAdapter(Context context, int textViewResourceId) {
		super(context, textViewResourceId);
		m_layoutInflater = (LayoutInflater)context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);  
	}
	
	//====================================================================
	/* (non-Javadoc)
	 * @see android.widget.ArrayAdapter#getCount()
	 */
	@Override
	public int getCount() {
		int c = super.getCount();
		return c;
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
	 * @see android.widget.ArrayAdapter#getView(int, android.view.View, android.view.ViewGroup)
	 */
	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		
		   
		View rowView = convertView;
		if (rowView == null) {		    
			rowView = m_layoutInflater.inflate(R.layout.scan_wifi_property, null);
			ViewHolder viewHolder = new ViewHolder();
			viewHolder.textWifiName = (TextView) rowView.findViewById(R.id.wifi_name_row_textview);				
			viewHolder.textWifiCapabiliteis = (TextView) rowView.findViewById(R.id.wifi_capabilities);				
			viewHolder.textWifiLevel = (TextView) rowView.findViewById(R.id.wifi_level);		      		     
			rowView.setTag(viewHolder);
		}
		
		Log.i(TAG, "Get view [ "+position +" ] "+ " SSID "+getItem(position).SSID + " level " + getItem(position).level);
		ViewHolder holder = (ViewHolder) rowView.getTag();
		holder.textWifiName.setText(getItem(position).SSID);
		holder.textWifiCapabiliteis.setText(getItem(position).capabilities);

		holder.textWifiLevel.setText(Integer.toString(   WifiManager.calculateSignalLevel(getItem(position).level, 100)+1)+"%");		  
		return rowView;		  			
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
}
