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

#ifndef DIALOGWIDGET_H_
#define DIALOGWIDGET_H_

/** @defgroup DialogWidget Dialog Widget
 * details Dialog Widget Struct and Functions that assist in Un/Marshaling
 * Dialog Widget from/to a message.
 *  @{
 */

#include <ajtcl/services/Common/BaseWidget.h>

/////////////////////////* DialogWidget OptParams *//////////////////////////////////////

struct DialogWidget;

/**
 * DialogOptParams structure
 */
typedef struct DialogOptParams {
    const char* const* labelAction1;                                           //!< The first action's label text
    const char* (*getLabelAction1)(struct DialogWidget* thisWidget, uint16_t); //!< Getter for the first action's label text
    const char* const* labelAction2;                                           //!< The second action's label text
    const char* (*getLabelAction2)(struct DialogWidget* thisWidget, uint16_t); //!< Getter for the second action's label text
    const char* const* labelAction3;                                           //!< The third action's label text
    const char* (*getLabelAction3)(struct DialogWidget* thisWidget, uint16_t); //!< Getter for the third action's label text

} DialogOptParams;

/**
 * Initialize the DialogOptParams structure
 * @param optParam - pointer to DialogOptParams structure
 */
void initializeDialogOptParam(DialogOptParams* optParam);

/////////////////////////*     DialogWidget     *//////////////////////////////////////

/**
 * DialogWidget structure
 */
typedef struct DialogWidget {
    BaseWidget base;                                                      //!< Internal BaseWidget

    const char* const* message;                                           //!< The Dialog's message text
    const char* (*getMessage)(struct DialogWidget* thisWidget, uint16_t); //!< Getter to the Dialog's message text
    uint16_t numActions;                                                  //!< The number of Actions

    DialogOptParams optParams;                                            //!< Dialog optional parameters

} DialogWidget;

/**
 * Initialize the DialogWidget structure
 * @param widget - pointer to DialogWidget structure
 */
void initializeDialogWidget(DialogWidget* widget);

/**
 * Marshal DialogMessage of given widget into given reply message
 * @param widget - pointer to widget
 * @param reply - message to marshal into
 * @param language - language requested
 * @return aj_status - success/failure
 */
AJ_Status marshalDialogMessage(DialogWidget* widget, AJ_Message* reply, uint16_t language);

/**
 * Marshal DialogNumActions of given widget into given reply message
 * @param widget - pointer to widget
 * @param reply - message to marshal into
 * @param language - language requested
 * @return aj_status - success/failure
 */
AJ_Status marshalDialogNumActions(DialogWidget* widget, AJ_Message* reply, uint16_t language);

/**
 * Marshal DialogOptParam of given widget into given reply message
 * @param widget - pointer to widget
 * @param reply - message to marshal into
 * @param language - language requested
 * @return aj_status - success/failure
 */
AJ_Status marshalDialogOptParam(BaseWidget* widget, AJ_Message* reply, uint16_t language);

/**
 * Marshal All DialogProperties of given widget into given reply message
 * @param widget - pointer to widget
 * @param reply - message to marshal into
 * @param language - language requested
 * @return aj_status - success/failure
 */
AJ_Status marshalAllDialogProperties(BaseWidget* widget, AJ_Message* reply, uint16_t language);

/** @} */
#endif /* DIALOGWIDGET_H_ */

