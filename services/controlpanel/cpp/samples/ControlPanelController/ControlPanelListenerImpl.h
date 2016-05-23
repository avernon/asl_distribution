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

#ifndef CONTROLPANELLISTENERIMPL_H_
#define CONTROLPANELLISTENERIMPL_H_

#include <alljoyn/controlpanel/ControlPanelListener.h>
#include <alljoyn/controlpanel/ControlPanelController.h>

/*
 *
 */
class ControlPanelListenerImpl : public ajn::services::ControlPanelListener {
  public:

    ControlPanelListenerImpl(ajn::services::ControlPanelController* controller);

    ~ControlPanelListenerImpl();

    void sessionEstablished(ajn::services::ControlPanelDevice* device);

    void sessionLost(ajn::services::ControlPanelDevice* device);

    void errorOccured(ajn::services::ControlPanelDevice* device, QStatus status,
                      ajn::services::ControlPanelTransaction transaction, qcc::String const& error);

    void signalPropertiesChanged(ajn::services::ControlPanelDevice* device, ajn::services::Widget* widget);

    void signalPropertyValueChanged(ajn::services::ControlPanelDevice* device, ajn::services::Property* property);

    void signalDismiss(ajn::services::ControlPanelDevice* device, ajn::services::NotificationAction* notificationAction);

  private:

    ajn::services::ControlPanelController* m_Controller;

    std::vector<qcc::String> m_ConnectedDevices;

};

#endif /* CONTROLPANELLISTENERIMPL_H_ */
