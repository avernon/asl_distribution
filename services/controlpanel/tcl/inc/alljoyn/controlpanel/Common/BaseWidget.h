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

#ifndef BASEWIDGET_H_
#define BASEWIDGET_H_

/** @defgroup BaseWidget Base Widget
 * details Base Widget struct and Functions that assist in Un/Marshaling
 * Widgets from/to a message.
 *  @{
 */

#include <alljoyn.h>

#ifndef UINT32_MAX
#define UINT32_MAX      (4294967295U) //!< Maximum integer value
#endif

struct BaseWidget;

/////////////////////////* BaseWidget OptParams *//////////////////////////////////////

/**
 * BaseOptParams structure
 */
typedef struct {
    const char* const* label;                                         //!< The url of the Http control
    const char* (*getLabel)(struct BaseWidget* thisWidget, uint16_t); //!< The url of the Http control

    uint32_t bgColor;                                                 //!< The url of the Http control
    uint32_t (*getBgColor)(struct BaseWidget* thisWidget);            //!< The url of the Http control

    uint16_t numHints;                                                //!< The url of the Http control
    const uint16_t* hints;                                            //!< The url of the Http control

} BaseOptParams;

/**
 * Initialize BaseOptParam
 * @param optParam
 */
void initializeBaseOptParam(BaseOptParams* optParam);

/////////////////////////*     BaseWidget     *//////////////////////////////////////

/**
 * Funtion pointer for marshaling a given widget structure
 */
typedef AJ_Status (*MarshalWidgetFptr)(struct BaseWidget*, AJ_Message*, uint16_t language);

/**
 * BaseWidget structure
 */
typedef struct BaseWidget {
    uint16_t interfaceVersion;                             //!< Version of the widget interface
    uint32_t states;                                       //!< States bitmap
    uint8_t (*getEnabled)(struct BaseWidget* thisWidget);  //!< Getter for Enabled attribute of widget
    uint8_t (*getWritable)(struct BaseWidget* thisWidget); //!< Getter for Writable attribute of widget

    uint16_t numLanguages;                                 //!< Number of languages
    BaseOptParams optParams;                               //!< Base optional parameters

    MarshalWidgetFptr marshalVersion;                      //!< Funtion pointer to marshal the Version
    MarshalWidgetFptr marshalStates;                       //!< Funtion pointer to marshal the States
    MarshalWidgetFptr marshalOptParam;                     //!< Funtion pointer to marshal the OptParam
    MarshalWidgetFptr marshalAllProp;                      //!< Funtion pointer to marshal All the Properties

} BaseWidget;

/**
 * Initialize BaseWidget
 * @param widget
 */
void initializeBaseWidget(BaseWidget* widget);

/**
 * Set Enabled state of widget
 * @param widget
 * @param enabled
 */
void setBaseEnabled(BaseWidget* widget, uint8_t enabled);

/**
 * Set Writable state of widget
 * @param widget
 * @param writeable
 */
void setBaseWritable(BaseWidget* widget, uint8_t writeable);

/**
 * Marshal BaseVersion into given reply message
 * @param widget
 * @param reply
 * @param language
 * @return aj_status
 */
AJ_Status marshalBaseVersion(BaseWidget* widget, AJ_Message* reply, uint16_t language);

/**
 * Marshal BaseStates into given reply message
 * @param widget
 * @param reply
 * @param language
 * @return aj_status
 */
AJ_Status marshalBaseStates(BaseWidget* widget, AJ_Message* reply, uint16_t language);

/**
 * Marshal Only the BaseOptParam of the given widget into given reply message
 * @param widget
 * @param reply
 * @param language
 * @return aj_status
 */
AJ_Status marshalOnlyBaseOptParam(BaseWidget* widget, AJ_Message* reply, uint16_t language);

/**
 * Marshal BaseOptParam into given reply message
 * @param widget
 * @param reply
 * @param language
 * @return aj_status
 */
AJ_Status marshalBaseOptParam(BaseWidget* widget, AJ_Message* reply, uint16_t language);

/**
 * Marshal All BaseProperties of given widget into given reply message
 * @param widget
 * @param reply
 * @param language
 * @return aj_status
 */
AJ_Status marshalAllBaseProperties(BaseWidget* widget, AJ_Message* reply, uint16_t language);

/**
 * Marshal All the BaseProperties of a given widget into given reply message
 * @param widget
 * @param reply
 * @param language
 * @return aj_status
 */
AJ_Status marshalAllOnlyBaseProperties(BaseWidget* widget, AJ_Message* reply, uint16_t language);

/** @} */
#endif /* BASEWIDGET_H_ */
