/* Copyright (c) AllSeen Alliance. All rights reserved.
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
package org.allseen.lsf.sdk;

import org.allseen.lsf.sdk.model.ControllerDataModel;
import org.allseen.lsf.sdk.model.LightingItemDataModel;

/**
 * This class provides an interface to retrieve information about a given controller
 * in the Lighting system.
 */
public class Controller extends LightingItem {
    /**
     * Specifies the default name of the Controller.
     *
     * @param defaultName Default name of the Controller
     */
    public static void setDefaultName(String defaultName) {
        if (defaultName != null) {
            ControllerDataModel.defaultName = defaultName;
        }
    }
    protected ControllerDataModel controllerModel;

    /**
     * Constructs a Controller.
     * <p>
     * <b>WARNING: This method is intended to be used internally. Client software should not instantiate
     * the Controller directly, but should instead get it from the {@link LightingDirector} using the
     * {@link LightingDirector#getLeadController()} method.</b>
     */
    protected Controller() {
        controllerModel = new ControllerDataModel();
    }

    /**
     * Renames the lead controller in the Lighting system.
     * <p>
     * <b>WARNING: This method is not yet implemented and could change in future releases.</b>
     */
    @Override
    public void rename(String name) {
        // This method is not yet implemented
        postError(ResponseCode.ERR_FAILURE);
    }

    /**
     * Returns a boolean that indicates if it is the lead controller in the Lighting system.
     *
     * @return Return true if this is the lead controller, false otherwise
     */
    public boolean isConnected() {
        return getControllerDataModel().connected;
    }

    /**
     * Returns the version of the controller.
     *
     * @return Version of the controller.
     */
    public long getVersion() {
        return getControllerDataModel().version;
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected ControllerDataModel getControllerDataModel() {
        return controllerModel;
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected LightingItemDataModel getItemDataModel() {
        return getControllerDataModel();
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected void postError(final String name, final ResponseCode status) {
        LightingDirector.get().getLightingSystemManager().getQueue().post(new Runnable() {
            @Override
            public void run() {
                LightingDirector.get().getControllerManager().sendErrorEvent(name, status);
            }
        });
    }
}
