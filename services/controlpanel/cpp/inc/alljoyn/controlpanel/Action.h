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

#ifndef ACTION_H_
#define ACTION_H_

#include <alljoyn/controlpanel/Widget.h>

namespace ajn {
namespace services {

/**
 * Action Class. Used to display a Button.
 * This is an abstract class. The executeCallback function needs to be overridden.
 */
class Action : public Widget {
  public:

    /**
     * Constructor for Action class
     * @param name - name of Widget
     * @param rootWidget - the RootWidget of the widget
     */
    Action(qcc::String const& name, Widget* rootWidget);

    /**
     * Constructor for Action class
     * @param name - name of Widget
     * @param rootWidget - the RootWidget of the widget
     * @param device - the Device that contains this Action
     */
    Action(qcc::String const& name, Widget* rootWidget, ControlPanelDevice* device);


    /**
     * Destructor for Action Class
     */
    virtual ~Action();

    /**
     * creates and returns the appropriate BusObject for this Widget
     * @param bus - the bus used to create the widget
     * @param objectPath - the objectPath of the widget
     * @param langIndx - the language Indx
     * @param status - the status indicating success or failure
     * @return a newly created WidgetBusObject
     */
    WidgetBusObject* createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
                                           uint16_t langIndx, QStatus& status);

    /**
     * Call to execute this Action remotely
     * @return status - success/failure
     */
    QStatus executeAction();

    /**
     * Callback for when Action is executed.
     * Virtual function that needs to be implemented.
     * @return success/failure
     */
    virtual bool executeCallBack();
};
} //namespace services
} //namespace ajn

#endif /* ACTION_H_ */
