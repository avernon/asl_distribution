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
package org.allseen.lsf.sdk.callback;

import org.allseen.lsf.ControllerServiceManagerCallback;
import org.allseen.lsf.sdk.ResponseCode;
import org.allseen.lsf.sdk.manager.AllJoynManager;
import org.allseen.lsf.sdk.manager.LightingSystemManager;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class HelperControllerServiceManagerCallback extends ControllerServiceManagerCallback {
    private final LightingSystemManager<?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?> manager;

    public HelperControllerServiceManagerCallback(LightingSystemManager<?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?> manager) {
        super();

        this.manager = manager;
    }

    @Override
    public void getControllerServiceVersionReplyCB(final long version) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                AllJoynManager.controllerServiceLeaderVersion = version;
                manager.getControllerCollectionManager().getLeaderModel().version = version;
                postSendControllerChanged();
            }
        });
    }

    @Override
    public void lightingResetControllerServiceReplyCB(ResponseCode responseCode) {
        // Currently nothing to do
    }

    @Override
    public void controllerServiceLightingResetCB() {
        // Currently nothing to do
    }

    @Override
    public void controllerServiceNameChangedCB(String controllerServiceDeviceID, String controllerServiceName) {
        // This is currently handled by the AboutManager
    }

    protected void postSendControllerChanged() {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                manager.getControllerCollectionManager().sendLeaderStateChangeEvent();
            }
        });
    }
}
