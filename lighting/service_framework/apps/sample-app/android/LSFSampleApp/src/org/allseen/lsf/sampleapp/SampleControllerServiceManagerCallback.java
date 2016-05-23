/*
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
 */
package org.allseen.lsf.sampleapp;

import org.allseen.lsf.ControllerServiceManagerCallback;
import org.allseen.lsf.ResponseCode;

import android.os.Handler;
import android.support.v4.app.FragmentManager;
import android.util.Log;

public class SampleControllerServiceManagerCallback extends ControllerServiceManagerCallback {
    protected SampleAppActivity activity;
    protected FragmentManager fragmentManager;
    protected Handler handler;

    public SampleControllerServiceManagerCallback(SampleAppActivity activity, FragmentManager fragmentManager, Handler handler) {
        super();

        this.activity = activity;
        this.fragmentManager = fragmentManager;
        this.handler = handler;
    }

    @Override
    public void getControllerServiceVersionReplyCB(long version) {
        Log.d(SampleAppActivity.TAG, "getControllerServiceVersionReplyCB() :" + version);
    }

    @Override
    public void lightingResetControllerServiceReplyCB(ResponseCode responseCode) {
        Log.d(SampleAppActivity.TAG, "lightingResetControllerServiceReplyCB() :" + responseCode);
    }

    @Override
    public void controllerServiceLightingResetCB() {
        Log.d(SampleAppActivity.TAG, "controllerServiceLightingResetCB()");
    }

    @Override
    public void controllerServiceNameChangedCB(String controllerServiceDeviceID, String controllerServiceName) {
        // This is currently handled by the AboutManager
        Log.d(SampleAppActivity.TAG, "controllerServiceNameChangedCB(): " + controllerServiceDeviceID + ", " + controllerServiceName);
    }
}
