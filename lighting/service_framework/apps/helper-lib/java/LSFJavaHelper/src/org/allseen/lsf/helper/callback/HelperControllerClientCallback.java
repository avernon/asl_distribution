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
package org.allseen.lsf.helper.callback;

import java.util.Map;

import org.alljoyn.about.AboutKeys;
import org.alljoyn.bus.Variant;
import org.allseen.lsf.ControllerClientCallback;
import org.allseen.lsf.ErrorCode;
import org.allseen.lsf.helper.manager.AboutManager;
import org.allseen.lsf.helper.manager.AllJoynManager;
import org.allseen.lsf.helper.manager.ControllerMaintenance;
import org.allseen.lsf.helper.manager.LightingSystemManager;
import org.allseen.lsf.helper.model.ControllerDataModel;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class HelperControllerClientCallback extends ControllerClientCallback {
    protected LightingSystemManager director;

    public HelperControllerClientCallback(LightingSystemManager director) {
        super();

        this.director = director;
    }

    @Override
    public void connectedToControllerServiceCB(String controllerServiceDeviceID, String controllerServiceName) {
        AllJoynManager.controllerConnected = true;

        postUpdateControllerID(controllerServiceDeviceID, controllerServiceName, true, 0);
        postGetAllLampIDs();
        postGetAllLampGroupIDs();
        postGetAllPresetIDs();
        postGetAllBasicSceneIDs();
        postGetAllMasterSceneIDs();
    }

    @Override
    public void connectToControllerServiceFailedCB(String controllerServiceDeviceID, String controllerServiceName) {
        AllJoynManager.controllerConnected = false;
        postUpdateControllerID(controllerServiceDeviceID, controllerServiceName, false, 0);
    }

    @Override
    public void disconnectedFromControllerServiceCB(String controllerServiceDeviceID, String controllerServiceName) {
        AllJoynManager.controllerConnected = false;
        postUpdateControllerID(controllerServiceDeviceID, controllerServiceName, false, 0);
    }

    @Override
    public void controllerClientErrorCB(ErrorCode[] errorCodes) {
        director.getControllerManager().sendErrorEvent("controllerClientErrorCB", errorCodes);
    }

    public void postUpdateControllerID(final String controllerID, final String controllerName, final boolean connected, int delay) {
        director.getHandler().postDelayed(new Runnable() {
            @Override
            public void run() {
                ControllerDataModel leadModel = director.getControllerManager().getLeadControllerModel();

                if (connected || leadModel.id.equals(controllerID)) {
                    leadModel.id = controllerID;
                    leadModel.setName(controllerName);
                    leadModel.connected = connected;
                    leadModel.updateTime();

                    postSendControllerChanged();
                }
            }
        }, delay);
    }

    public void postUpdateControllerName(final String controllerID, Map<String, Variant> announceData, int delay) {
        final String controllerName = AboutManager.getStringFromAnnounceData(AboutKeys.ABOUT_DEVICE_NAME, announceData, null);

        director.getHandler().postDelayed(new Runnable() {
            @Override
            public void run() {
                ControllerDataModel leadModel = director.getControllerManager().getLeadControllerModel();

                if (leadModel.id.equals(controllerID)) {
                    leadModel.setName(controllerName);
                    leadModel.updateTime();

                    postSendControllerChanged();
                }
            }
        }, delay);
    }

    protected void postGetAllLampIDs() {
        new ControllerMaintenance(director);
    }

    protected void postGetAllLampGroupIDs() {
        director.getHandler().postDelayed(new Runnable() {
            @Override
            public void run() {
                AllJoynManager.groupManager.getAllLampGroupIDs();
            }
        }, 100);
    }

    protected void postGetAllPresetIDs() {
        director.getHandler().postDelayed(new Runnable() {
            @Override
            public void run() {
                AllJoynManager.presetManager.getAllPresetIDs();
            }
        }, 200);
    }

    protected void postGetAllBasicSceneIDs() {
        director.getHandler().postDelayed(new Runnable() {
            @Override
            public void run() {
                AllJoynManager.sceneManager.getAllSceneIDs();
            }
        }, 300);
    }

    protected void postGetAllMasterSceneIDs() {
        director.getHandler().postDelayed(new Runnable() {
            @Override
            public void run() {
                AllJoynManager.masterSceneManager.getAllMasterSceneIDs();
            }
        }, 400);
    }

    protected void postSendControllerChanged() {
        // if connection status is ever changed, then prompt for updating the loading information
        director.getHandler().post(new Runnable() {
            @Override
            public void run() {
                director.getControllerManager().sendLeaderStateChangeEvent();
            }
        });
    }
}
