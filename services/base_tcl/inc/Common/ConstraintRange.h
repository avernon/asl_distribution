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

#ifndef CONSTRAINTRANGE_H_
#define CONSTRAINTRANGE_H_

/** @defgroup ConstraintRange Contraint Range
 *
 *  @{
 */

#include <ajtcl/services/Definitions.h>
#include <ajtcl/alljoyn.h>

/**
 * ConstraintRange structure
 */
typedef struct {
    const char* const* signature; //!< The Constraint Range value signature
    const void* minValue;         //!< The Minimum constraint value
    const void* maxValue;         //!< The Maximum constraint value
    const void* increment;        //!< The value increment

} ConstraintRange;

/**
 * Initialize the ConstraintRange structure
 * @param constraints - pointer to ConstraintRange structure
 */
void initializeConstraintRange(ConstraintRange* constraints);

/**
 * Marshal ConstraintRange into given reply message
 * @param constraints - constraints to marshal
 * @param reply - message to marshal it into
 * @return aj_status - success/failure
 */
AJ_Status marshalConstraintRange(ConstraintRange* constraints, AJ_Message* reply);

/** @} */
#endif /* CONSTRAINTRANGE_H_ */
