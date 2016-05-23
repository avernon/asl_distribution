/******************************************************************************
 * Copyright (c) 2013 - 2014, AllSeen Alliance. All rights reserved.
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

#ifndef CONTROLPANELSERVICE_H_
#define CONTROLPANELSERVICE_H_

#include <alljoyn/BusAttachment.h>
#include <alljoyn/controlpanel/ControlPanelControllee.h>
#include <alljoyn/controlpanel/ControlPanelController.h>
#include <alljoyn/controlpanel/ControlPanelBusListener.h>
#include <alljoyn/controlpanel/ControlPanelListener.h>

namespace ajn {
namespace services {

/**
 * ControlPanel Service class. Used to initialize and shutdown the service
 */
class ControlPanelService {

  public:

    /**
     * Get Instance of ControlPanelServiceImpl - singleton implementation
     * @return instance
     */
    static ControlPanelService* getInstance();

    /**
     * Destructor for ControlPanelServiceImpl
     */
    ~ControlPanelService();

    /**
     * Initialize the controllee to be used
     * @param bus - bus used for Controllee
     * @param controlPanelControllee - controllee to initialize
     * @return status - success/failure
     */
    QStatus initControllee(BusAttachment* bus, ControlPanelControllee* controlPanelControllee);

    /**
     * Remove locally stored controllee. Allows a new call to initControllee to be made
     * @return status - success/failure
     */
    QStatus shutdownControllee();

    /**
     * Initialize the controller to be used
     * @param bus - bus used for Controller
     * @param controlPanelController - controller to initialize
     * @param controlPanelListener
     * @return status - success/failure
     */
    QStatus initController(BusAttachment* bus, ControlPanelController* controlPanelController,
                           ControlPanelListener* controlPanelListener);

    /**
     * Remove locally stored controller. Allows a new call to initController to be made
     * @return status - success/failure
     */
    QStatus shutdownController();

    /**
     * Full shutdown - includes removing the current BusAttachment
     * @return status - success/failure
     */
    QStatus shutdown();

    /**
     * Method to get the busAttachment used in the service.
     * @return BusAttachment
     */
    ajn::BusAttachment* getBusAttachment();

    /**
     * Get the BusListener
     * @return ControlPanelBusListener
     */
    ControlPanelBusListener* getBusListener() const;

    /**
     * Get the ControlPanelListener
     * @return ControlPanelListener
     */
    ControlPanelListener* getControlPanelListener() const;

    /**
     * Utility function to split an objectPath based on the / delimeter
     * @param objectPath
     * @return vector of objectPath parts
     */
    static std::vector<qcc::String> SplitObjectPath(qcc::String const& objectPath);

    /**
     * Get the Version of the ControlPanelService
     * @return the ControlPanelService version
     */
    static uint16_t getVersion();

  private:

    /**
     * Default constructor for ControlPanelServiceImpl
     * Private to allow for singleton implementation
     */
    ControlPanelService();

    /**
     * Version of the API
     */
    static uint16_t const CONTROLPANEL_SERVICE_VERSION;

    /**
     * Instance variable - ControlPanelServiceImpl is a singleton
     */
    static ControlPanelService* s_Instance;

    /**
     * BusAttachement used in Service
     */
    BusAttachment* m_Bus;

    /**
     * BusListener used in service
     */
    ControlPanelBusListener* m_BusListener;

    /**
     * ControlPanelControllee of service
     */
    ControlPanelControllee* m_ControlPanelControllee;

    /**
     * ControlPanelController of service
     */
    ControlPanelController* m_ControlPanelController;

    /**
     * ControlPanelListener of service
     */
    ControlPanelListener* m_ControlPanelListener;

};
} //namespace services
} //namespace ajn

#endif /* CONTROLPANELSERVICE_H_ */
