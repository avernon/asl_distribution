/*
 * Copyright (c) AllSeen Alliance. All rights reserved.
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
package org.allseen.lsf.sdk.manager;

import java.util.Iterator;

import org.allseen.lsf.sdk.ErrorCode;
import org.allseen.lsf.sdk.ResponseCode;
import org.allseen.lsf.sdk.factory.ControllerFactory;
import org.allseen.lsf.sdk.listener.ControllerCollectionListener;
import org.allseen.lsf.sdk.model.ControllerDataModel;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class ControllerCollectionManager<CONTROLLER, ERROR> extends LightingItemListenerManager<ControllerCollectionListener<? super CONTROLLER, ? super ERROR>> {

    protected final ControllerFactory<CONTROLLER, ERROR> factory;
    protected final CONTROLLER leader;

    public ControllerCollectionManager(LightingSystemManager<?, ?, ?, ?, ?, ?, ?, ?, ?, CONTROLLER, ?> manager, ControllerFactory<CONTROLLER, ERROR> factory) {
        super(manager);

        this.factory = factory;
        this.leader = factory.createController("");
    }

    public CONTROLLER getLeader() {
        return leader;
    }

    public ControllerDataModel getLeaderModel() {
        return factory.findControllerDataModel(leader);
    }

    public void sendLeaderStateChangeEvent() {
        processAddedListeners();

        Iterator<ControllerCollectionListener<? super CONTROLLER, ? super ERROR>> i = currentListeners.iterator();
        ControllerCollectionListener<? super CONTROLLER, ? super ERROR> listener = getNext(i);

        while (listener != null) {
            listener.onLeaderChange(leader);
            listener = getNext(i);
        }
    }

    public void sendErrorEvent(String name, ResponseCode responseCode) {
        sendErrorEvent(factory.createError(name, responseCode, null, null, null));
    }

    public void sendErrorEvent(String name, ErrorCode[] errorCodes) {
        sendErrorEvent(factory.createError(name, null, null, null, errorCodes));
    }

    public void sendErrorEvent(ERROR errorEvent) {
        processAddedListeners();

        Iterator<ControllerCollectionListener<? super CONTROLLER, ? super ERROR>> i = currentListeners.iterator();
        ControllerCollectionListener<? super CONTROLLER, ? super ERROR> listener = getNext(i);

        while (listener != null) {
            sendErrorEvent(listener, errorEvent);
            listener = getNext(i);
        }
    }

    protected void sendErrorEvent(ControllerCollectionListener<? super CONTROLLER, ? super ERROR> listener, ERROR error) {
        listener.onControllerErrors(error);
    }
}
