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
package org.alljoyn.aroundme.Transactions;


import org.alljoyn.aroundme.R;
import org.alljoyn.aroundme.Adapters.FragmentPageAdapter;
import org.alljoyn.aroundme.MainApp.AppConstants;
import org.alljoyn.aroundme.MainApp.TaskControlInterface;
import org.alljoyn.aroundme.Peers.PeerDetailsFragment;
import org.alljoyn.devmodules.api.profilemanager.ProfileManagerAPI;
import org.alljoyn.devmodules.api.profilemanager.ProfileManagerListener;
import org.alljoyn.devmodules.common.MediaTypes;
import org.alljoyn.devmodules.common.ProfileDescriptor;
import org.alljoyn.devmodules.common.Utilities;
import org.alljoyn.storage.MediaTransactionCache;
import org.alljoyn.storage.ProfileCache;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v4.app.Fragment;
import android.support.v4.view.ViewPager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;



/*
 * Fragment that builds the pages for viewing different types of remote media
 */
public class TransactionsPagerFragment extends Fragment {


	private static final String        TAG = "TransactionsPagerFragment";

	private FragmentPageAdapter mAdapter = null;

	private View                mDisplayView = null;
	private ViewPager           mViewPager = null;
	private Context             mContext;
	private Bundle                     mSavedInstanceState=null;



	@Override
	public void onCreate(Bundle savedInstanceState) {

		super.onCreate(savedInstanceState);

		mSavedInstanceState = savedInstanceState;

		if (mSavedInstanceState==null){
			// save context for later use
			mContext = getActivity().getBaseContext();
		}
	}

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

		// inflate the layout
		mDisplayView = inflater.inflate(R.layout.viewpager, container, false);


		// create the adapter for holding the fragments for each page
		mAdapter = new FragmentPageAdapter(getFragmentManager());
		mAdapter.setContext(mContext);

		// get the ViewPager object
		mViewPager = (ViewPager)mDisplayView.findViewById(R.id.viewpager);

		// associate the adapter to the ViewPager
		mViewPager.setAdapter(mAdapter);
		mViewPager.setOffscreenPageLimit(4);

		// add the pages. 
		Bundle bundle = new Bundle();
		bundle.putString(AppConstants.TRANSACTION, MediaTransactionCache.RECEIVED);
		mAdapter.add(MediaTransactionCache.RECEIVED, "PENDING APPROVAL", 
				     TransactionsReceivedFragment.class.getName(), bundle);
		
		bundle = new Bundle();
		bundle.putString(AppConstants.TRANSACTION, MediaTransactionCache.APPROVED);
		mAdapter.add(MediaTransactionCache.APPROVED, "ACCEPTED", 
				     TransactionsGenericFragment.class.getName(), bundle);
		
		bundle = new Bundle();
		bundle.putString(AppConstants.TRANSACTION, MediaTransactionCache.REJECTED);
		mAdapter.add(MediaTransactionCache.REJECTED, "REJECTED", 
				     TransactionsGenericFragment.class.getName(), bundle);
		
		bundle = new Bundle();
		bundle.putString(AppConstants.TRANSACTION, MediaTransactionCache.SENT);
		mAdapter.add(MediaTransactionCache.SENT, "SENT", 
				     TransactionsGenericFragment.class.getName(), bundle);
		
		mAdapter.notifyDataSetChanged();
		
		return mDisplayView;
	} // onCreateView


	@Override
	public void onDestroy() {
		super.onDestroy();
	} //onDestroy


} // TransactionsPagerFragment
