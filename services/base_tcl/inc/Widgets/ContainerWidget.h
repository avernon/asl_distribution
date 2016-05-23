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

#ifndef CONTAINERWIDGET_H_
#define CONTAINERWIDGET_H_

/** @defgroup ContainerWidget Container Widget
 *
 *  @{
 */

#include <ajtcl/services/Common/BaseWidget.h>

/////////////////////////*     ContainerWidget     *//////////////////////////////////////

/**
 * ContainerWidget structure - widget to represent a Container containing other widgets
 */
typedef struct {
    BaseWidget base; //!< Internal BaseWidget
} ContainerWidget;

/**
 * Initialize the ContainerWidget structure
 * @param widget - pointer to ContainerWidget structure
 */
void initializeContainerWidget(ContainerWidget* widget);

/** @} */
#endif /* CONTAINERWIDGET_H_ */
