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

#ifndef DATETIMEUTIL_H_
#define DATETIMEUTIL_H_

/** @defgroup DateTimeUtil Date and Time Utilities
 * details Structs and Functions that assist in Un/Marshaling
 * Date and Time Properties from/to a message.
 *  @{
 */

#include <alljoyn.h>

/**
 * DatePropertyValue structure
 */
typedef struct {
    uint16_t mDay;     //!< The day of the month value i.e. 1 for 1st of the month
    uint16_t month;    //!< The month value i.e. 3 for March
    uint16_t fullYear; //!< The full year value i.e. 2014 and not 14
} DatePropertyValue;

/**
 * TimePropertyValue structure
 */
typedef struct {
    uint16_t hour;   //!< The hour value as 24 hours
    uint16_t minute; //!< The minute value
    uint16_t second; //!< The second valur
} TimePropertyValue;

/**
 * Marshal DatePropertyValue into given reply message
 * @param datePropertyValue
 * @param reply
 * @return aj_status
 */
AJ_Status marshalDatePropertyValue(DatePropertyValue* datePropertyValue, AJ_Message* reply);

/**
 * Marshal TimePropertyValue into given reply message
 * @param timePropertyValue
 * @param reply
 * @return aj_status
 */
AJ_Status marshalTimePropertyValue(TimePropertyValue* timePropertyValue, AJ_Message* reply);

/**
 * Unmarshal DatePropertyValue from given message
 * @param datePropertyValue
 * @param message
 * @return aj_status
 */
AJ_Status unmarshalDatePropertyValue(DatePropertyValue* datePropertyValue, AJ_Message* message);

/**
 * Unmarshal TimePropertyValue from given message
 * @param timePropertyValue
 * @param message
 * @return aj_status
 */
AJ_Status unmarshalTimePropertyValue(TimePropertyValue* timePropertyValue, AJ_Message* message);

/** @} */
#endif /* DATETIMEUTIL_H_ */
