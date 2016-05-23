/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

#ifndef COMMANDLINECONTROLLER_H_
#define COMMANDLINECONTROLLER_H_

#include <alljoyn/controlpanel/ControlPanelListener.h>
#include <alljoyn/controlpanel/ControlPanelController.h>
#include <alljoyn/about/AnnouncementRegistrar.h>
#include <alljoyn/controlpanel/ControlPanelService.h>
#include <alljoyn/controlpanel/ControlPanelController.h>
#include <alljoyn/controlpanel/Container.h>
#include <alljoyn/controlpanel/Property.h>
#include <alljoyn/controlpanel/Dialog.h>
#include <alljoyn/controlpanel/Action.h>
#include <alljoyn/services_common/GenericLogger.h>
#include <SrpKeyXListener.h>
#include <CommonSampleUtil.h>
#include <AnnounceHandlerImpl.h>

typedef struct NearbyDeviceStruct {
    
    qcc::String busName;
    unsigned short version;
    unsigned short port;
    ajn::services::AnnounceHandler::ObjectDescriptions objectDescs;
    ajn::services::AnnounceHandler::AboutData aboutData;

    //NearbyDeviceStruct(qcc::String const& mBusName, unsigned short mVersion, unsigned short mPort, const AnnounceHandler::ObjectDescriptions& mObjectDescs, const AnnounceHandler::AboutData& mAboutData) : busName(mBusName), version(mVersion), port(mPort), objectDescs(mObjectDescs), aboutData(mAboutData) {}

} NearbyDeviceStruct;

/*
 *
 */
class CommandLineController : public ajn::services::ControlPanelListener, public ajn::services::AnnounceHandler {
  public:

    CommandLineController();

    ~CommandLineController();

    void initialize();

    void showNearbyDevices();

    void showUnits();

    void showControlPanels();

    void showControlPanel();

    void interactWithPropertyWidget();

    void interactWithActionWidget();

    void shutdown();

    virtual void Announce(unsigned short version, unsigned short port, const char* busName, const ObjectDescriptions& objectDescs,
                          const AboutData& aboutData);

    //START ControlPanelListener Callbacks
    void sessionEstablished(ajn::services::ControlPanelDevice* device);

    void sessionLost(ajn::services::ControlPanelDevice* device);

    void errorOccured(ajn::services::ControlPanelDevice* device, QStatus status,
                      ajn::services::ControlPanelTransaction transaction, qcc::String const& error);

    void signalPropertiesChanged(ajn::services::ControlPanelDevice* device, ajn::services::Widget* widget);

    void signalPropertyValueChanged(ajn::services::ControlPanelDevice* device, ajn::services::Property* property);

    void signalDismiss(ajn::services::ControlPanelDevice* device, ajn::services::NotificationAction* notificationAction);
    //END ControlPanelListener Callbacks

  private:

    void getNewValueConstraintRange(ajn::services::ConstraintRange* constraintRange, ajn::services::PropertyType propertyType);

    void getNewValueConstraintList(const std::vector<ajn::services::ConstraintList>& constraintList, ajn::services::PropertyType propertyType);

    void printRootWidget(ajn::services::RootWidget* rootWidget);

    void printPropertyValue(ajn::services::PropertyValue propertyValue, ajn::services::PropertyType propertyType, qcc::String const& indent = "  ");

    void printErrorWidget(ajn::services::Widget* widget, qcc::String const& indent);

    void printBasicWidget(ajn::services::Widget* widget, qcc::String const& widgetType, qcc::String const& indent);

    void printContainer(ajn::services::Container* rootContainer, std::vector<ajn::services::Action*>& actionsToExecute,
                               std::vector<ajn::services::Dialog*>& dialogsToExecute, std::vector<ajn::services::Property*>& propertiesToChange,
                               qcc::String const& indent = "");

    void printProperty(ajn::services::Property* property, qcc::String const& indent);

    void printDialog(ajn::services::Dialog* dialog, qcc::String const& indent);

    void printConstraintRange(ajn::services::ConstraintRange* constraintRange, ajn::services::PropertyType propertyType,
                                     qcc::String const& indent);

    void printConstraintList(const std::vector<ajn::services::ConstraintList>& constraintList, ajn::services::PropertyType propertyType,
                                    qcc::String const& indent);

    ajn::services::ControlPanelController* m_Controller;

    std::vector<qcc::String> m_ConnectedDevices;

    ajn::BusAttachment* bus;
    ajn::services::ControlPanelService* controlPanelService;
    ajn::services::ControlPanelController* controlPanelController;
    SrpKeyXListener* srpKeyXListener;
    AnnounceHandlerImpl* announceHandler;
    qcc::String ControlPanelPrefix;

    std::vector<NearbyDeviceStruct> nearbyDevices;
    ajn::services::ControlPanelDevice* currentCPDevice;
    ajn::services::ControlPanelControllerUnit* currentCPUnit;
    ajn::services::ControlPanel* currentCP;
    qcc::String currentLanguage;

    int currentState;

    std::vector<ajn::services::Action*> actionsToExecute;
    std::vector<ajn::services::Property*> propertiesToChange;
    std::vector<ajn::services::Dialog*> dialogsToExecute;

    ajn::services::Property* propertyToInteract;
    ajn::services::Action* actionToInteract;

};

#endif /* COMMANDLINECONTROLLER_H_ */
