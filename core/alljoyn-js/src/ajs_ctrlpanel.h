#ifndef _H_AJS_CTRLPANEL
#define _H_AJS_CTRLPANEL
/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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

#ifdef CONTROLPANEL_SERVICE
#include "ajs.h"

#include <ajtcl/services/ServicesCommon.h>
#include <ajtcl/services/Widgets/ActionWidget.h>
#include <ajtcl/services/Widgets/PropertyWidget.h>
#include <ajtcl/services/Widgets/ContainerWidget.h>
#include <ajtcl/services/Widgets/LabelWidget.h>
#include <ajtcl/services/Widgets/DialogWidget.h>
#include <ajtcl/services/Common/HttpControl.h>
#include <ajtcl/services/Common/DateTimeUtil.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AJS_MAX_HINTS 4

/**
 * Union for property widget values
 */
typedef union {
    int32_t i;
    uint32_t b;
    uint16_t q;
    double d;
    const char* s;
    DatePropertyValue date;
    TimePropertyValue time;
} AJS_WidgetVal;

/**
 * Generic encapsulation for a control panel widget
 */
typedef struct _AJS_Widget {
    /*
     * The union must be the first field so we can easily cast between AJS_Widget instances and from
     * the control panel service widget types. Note this is safe because we always allocate
     * AJS_Widget instances.
     */
    union {
        BaseWidget base;
        ContainerWidget container;
        DialogWidget dialog;
        LabelWidget label;
        struct {
            PropertyWidget wdt;
            AJS_WidgetVal val;
        } property;
        ActionWidget action;
    };
    uint8_t type;
    uint16_t index;
    uint16_t hints[AJS_MAX_HINTS];
#ifndef NDEBUG
    const char* path;
#endif
    duk_context* dukCtx;
} AJS_Widget;

/**
 * Returns the AllJoyn interface for a specified widget type.
 *
 * @param type  The widget type
 * @return  Returns a pointer to the AllJoyn interface description for the specified widget type.
 */
const AJ_InterfaceDescription* AJS_WidgetInterfaces(uint8_t type);

/**
 * Pass a message to the control panel service for possible processing
 */
AJSVC_ServiceStatus AJS_CP_MessageHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, AJ_Status* status);

/**
 * Initialize the control panel service
 *
 * @param cpObjects  The control panel object list to register
 *
 * @return Returns AJ_OK if the control panel service was succesfully initialized or an error
 *         status on failure.
 */
AJ_Status AJS_CP_Init(AJ_Object* cpObjects);

/**
 * Terminate the control panel service
 */
AJ_Status AJS_CP_Terminate();

/**
 * Execute a dialog widget action
 *
 * @param ajsWidget  Widget wrapper structure
 * @param index      Identifies which of the three dialog actions to execute
 * @param sender     Bus name of the sender of the action message
 *
 * @return Returns AJ_OK if the actions succesfully performed or an error status if the action
 *         failed or threw JavaScript exception.
 *
 */
AJ_Status AJS_CP_OnExecuteAction(AJS_Widget* ajsWidget, uint8_t index, const char* sender);

/**
 * Report a changed value on widget
 *
 * @param ajsWidget  Widget wrapper structure with the new value already set.
 * @param sender     Bus name of the sender of the value changed message
 *
 * @return Returns AJ_OK if the value changes was successfully reported or an error status if the
 *         operation failed or threw JavaScript exception.
 */
AJ_Status AJS_CP_OnValueChanged(AJS_Widget* ajsWidget, const char* sender);

/**
 * Send signal to controller indicating a value has changed
 *
 * @param ajsWidget  Widget wrapper structure for the widget that has changed
 */
void AJS_CP_SignalValueChanged(AJ_BusAttachment* aj, AJS_Widget* ajsWidget);

/**
 * Send signal to controller indicating a metadata property has changed
 *
 * @param ajsWidget  Widget wrapper structure for the widget that has changed
 */
void AJS_CP_SignalMetadataChanged(AJ_BusAttachment* aj, AJS_Widget* ajsWidget);

#ifdef __cplusplus
}
#endif

#endif
#endif /* CONTROLPANEL_SERVICE */
