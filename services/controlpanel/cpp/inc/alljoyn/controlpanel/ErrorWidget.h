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

#ifndef ERRORWIDGET_H_
#define ERRORWIDGET_H_

#include <alljoyn/controlpanel/Widget.h>

namespace ajn {
namespace services {

/**
 * ErrorWidget class - used when there's an in error retrieving widget information
 */
class ErrorWidget : public Widget {

  public:

    /**
     * Constructor for Error Eisget
     * @param name - name of Widget
     * @param rootWidget - the RootWidget of the widget
     * @param originalWidget - pointer to original widget that received the error
     * @param device - the device containing this Widget
     */
    ErrorWidget(qcc::String const& name, Widget* rootWidget, Widget* originalWidget, ControlPanelDevice* device);

    /**
     *
     */
    virtual ~ErrorWidget();

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
     * Register the BusObjects for this Widget
     * @param bus - the bus used to register the busObject
     * @param objectPath - the objectPath of the busObject
     * @return
     */
    QStatus registerObjects(BusAttachment* bus, qcc::String const& objectPath);

    /**
     * Unregister the BusObjects for this widget
     * @param bus
     * @return status - success/failure
     */
    QStatus unregisterObjects(BusAttachment* bus);

    /**
     * Get the Original Widget
     */
    Widget* getOriginalWidget() const;

  private:

    /**
     * the widget that was originally created unsuccessfully resulting in the creation if the ErrorWidget
     */
    Widget* m_OriginalWidget;
};
} //namespace services
} //namespace ajn

#endif /* ERRORWIDGET_H_ */
