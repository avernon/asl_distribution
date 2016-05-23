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

#ifndef LABELWIDGET_H_
#define LABELWIDGET_H_

/** @defgroup LabelWidget Label Widget
 *
 *  @{
 */

#include <alljoyn/controlpanel/Common/BaseWidget.h>

/////////////////////////*     LabelWidget     *//////////////////////////////////////

/**
 * LabelWidget structure
 */
typedef struct LabelWidget {
    BaseWidget base;                                                   //!< Internal BaseWidget

    const char* const* label;                                          //!< The label text
    const char* (*getLabel)(struct LabelWidget* thisWidget, uint16_t); //!< Getter to the label text
} LabelWidget;

/**
 * Initialize LabelWidget
 * @param widget - assumed to be a LabelWidget
 */
void initializeLabelWidget(LabelWidget* widget);

/**
 * Marshal Label of given widget into given reply message
 * @param widget - assumed to be a LabelWidget
 * @param reply
 * @param language
 * @return aj_status
 */
AJ_Status marshalLabelLabel(LabelWidget* widget, AJ_Message* reply, uint16_t language);

/**
 * Marshal All LabelProperties of given widget into given reply message
 * @param widget
 * @param reply
 * @param language
 * @return aj_status
 */
AJ_Status marshalAllLabelProperties(BaseWidget* widget, AJ_Message* reply, uint16_t language);

/** @} */
#endif /* LABELWIDGET_H_ */

