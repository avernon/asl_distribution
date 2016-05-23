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

#ifndef CONSTRAINTLIST_H_
#define CONSTRAINTLIST_H_

/** @defgroup ConstraintList Contraint List
 *
 *  @{
 */

#include <ajtcl/services/Definitions.h>
#include <ajtcl/services/Common/BaseWidget.h>
#include <ajtcl/alljoyn.h>

/**
 * ConstraintList structure
 */
typedef struct {
    const void* value;                            //!< The constraint value
    const char* const* display;                   //!< The constraint display text
    const char* (*getDisplay)(uint16_t language); //!< Getter for the display text

} ConstraintList;

/**
 * Marshal ConstraintList into given reply message
 * @param widget - pointer to the widget structure
 * @param constraints - the constraints array
 * @param reply - the message to marshal into
 * @param numConstraints - the number of constraints
 * @param signature - signature of value
 * @param language - language requested
 */
AJ_Status marshalConstraintList(BaseWidget* widget, ConstraintList* constraints, AJ_Message* reply, uint16_t numConstraints,
                                const char* signature, uint16_t language);

/** @} */
#endif /* CONTRAINTVALUES_H_ */
