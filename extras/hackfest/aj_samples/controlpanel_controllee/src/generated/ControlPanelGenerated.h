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

#ifndef CONTROLPANELGENERATED_H_
#define CONTROLPANELGENERATED_H_

#include <alljoyn/controlpanel/ControlPanelControllee.h>
#include <alljoyn/controlpanel/Container.h>
#include <alljoyn/controlpanel/Label.h>
#include <alljoyn/controlpanel/ActionWithDialog.h>
#include "../generated/MyDeviceSelected_message.h"
#include "../generated/MyDevicePrintMessage.h"
#include "../generated/MyDeviceCounterValueStringProperty.h"


/**
 * Generated Class - do not change code
 */
class ControlPanelGenerated {
  public:

    static QStatus PrepareWidgets(ajn::services::ControlPanelControllee*& controlPanelControllee);

    static void PrepareLanguageSets();

    static void Shutdown();

    static bool languageSetsDone;

    static ajn::services::ControlPanelControlleeUnit* myDeviceUnit;

    static ajn::services::ControlPanel* myDeviceRootContainerControlPanel;

    static ajn::services::Container* myDeviceRootContainer;

    static ajn::services::Container* myDeviceMessageContainer;

    static ajn::services::MyDeviceSelected_message* myDeviceSelected_message;

    static ajn::services::MyDevicePrintMessage* myDevicePrintMessage;

    static ajn::services::Container* myDeviceCounterContainer;

    static ajn::services::MyDeviceCounterValueStringProperty* myDeviceCounterValueStringProperty;


};

#endif /* CONTROLPANELGENERATED_H_ */
