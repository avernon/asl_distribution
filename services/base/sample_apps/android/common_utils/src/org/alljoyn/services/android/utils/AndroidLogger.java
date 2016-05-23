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

package org.alljoyn.services.android.utils;


import org.alljoyn.services.common.utils.GenericLogger;

import android.util.Log;

/**
 * A default GenericLogger implementation for Android
 */
public class AndroidLogger implements GenericLogger {

	/**
	 * @see org.alljoyn.services.common.utils.GenericLogger#debug(java.lang.String, java.lang.String)
	 */
	@Override
	public void debug(String TAG, String msg) {
		Log.d(TAG, msg);
	}

	/**
	 * @see org.alljoyn.services.common.utils.GenericLogger#info(java.lang.String, java.lang.String)
	 */
	@Override
	public void info(String TAG, String msg) {
		Log.i(TAG, msg);
	}

	/**
	 * @see org.alljoyn.services.common.utils.GenericLogger#warn(java.lang.String, java.lang.String)
	 */
	@Override
	public void warn(String TAG, String msg) {
		Log.w(TAG, msg);
	}

	/**
	 * @see org.alljoyn.services.common.utils.GenericLogger#error(java.lang.String, java.lang.String)
	 */
	@Override
	public void error(String TAG, String msg) {
		Log.e(TAG, msg);
	}

	/**
	 * @see org.alljoyn.services.common.utils.GenericLogger#fatal(java.lang.String, java.lang.String)
	 */
	@Override
	public void fatal(String TAG, String msg) {
		Log.wtf(TAG, msg);
	}
}
