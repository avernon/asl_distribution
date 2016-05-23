/******************************************************************************
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
 ******************************************************************************/

#ifndef AJGWCConnectorAppStatusSignalHandlerAdapter_H
#define AJGWCConnectorAppStatusSignalHandlerAdapter_H

#import "alljoyn/gateway/ConnectorAppStatusSignalHandler.h"
#import "alljoyn/gateway/ConnectorAppStatus.h"
#import "AJGWCConnectorAppStatusSignalHandler.h"
/**
 AJGWCConnectorAppStatusSignalHandlerAdapter class
 */

class AJGWCConnectorAppStatusSignalHandlerAdapter : public ajn::gwc::ConnectorAppStatusSignalHandler {
public:
    /**
     Constructor
     @param handle {@link AJGWCConnectorAppStatusSignalHandler} handle
     */
    AJGWCConnectorAppStatusSignalHandlerAdapter(id <AJGWCConnectorAppStatusSignalHandler> handle);

    /**
     * Destructor for AJGWCSessionListenerAdapter
     */
    ~AJGWCConnectorAppStatusSignalHandlerAdapter();

    /**
     * The event is emitted when the status of the Connector App
     * changes. Avoid blocking the thread on which the method is called.
     * @param appId The application id
     * @param status {@link ajn::gwc::ConnectorAppStatus}
     */
    void onStatusSignal(const qcc::String &appId, const ajn::gwc::ConnectorAppStatus *ConnectorAppStatus);

    void onError(const qcc::String& appId, const QStatus &status);

private:
    /**
     {@link AJGWCConnectorAppStatusSignalHandlerAdapter} handle
     */
    id <AJGWCConnectorAppStatusSignalHandler> connectorAppStatusSignalHandler;
};

#endif
