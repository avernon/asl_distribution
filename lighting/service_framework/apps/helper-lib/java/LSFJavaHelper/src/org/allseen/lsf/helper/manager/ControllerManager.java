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
package org.allseen.lsf.helper.manager;

import org.allseen.lsf.ErrorCode;
import org.allseen.lsf.helper.listener.ControllerErrorEvent;
import org.allseen.lsf.helper.listener.ControllerListener;
import org.allseen.lsf.helper.model.ControllerDataModel;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class ControllerManager extends LightingItemListenerManager<ControllerListener> {

    protected ControllerDataModel leadModel = new ControllerDataModel();

    public ControllerManager(LightingSystemManager director) {
        super(director);
    }

    public ControllerDataModel getLeadControllerModel() {
        return leadModel;
    }

    public void sendLeaderStateChangeEvent() {
        for (ControllerListener listener : itemListeners) {
            listener.onLeaderModelChange(leadModel);
        }
    }

    public void sendErrorEvent(String name, ErrorCode[] errorCodes) {
        sendErrorEvent(new ControllerErrorEvent(name, errorCodes));
    }

    public void sendErrorEvent(ControllerErrorEvent errorEvent) {
        for (ControllerListener listener : itemListeners) {
            sendErrorEvent(listener, errorEvent);
        }
    }

    protected void sendErrorEvent(ControllerListener listener, ControllerErrorEvent errorEvent) {
        listener.onControllerErrors(errorEvent);
    }
}
