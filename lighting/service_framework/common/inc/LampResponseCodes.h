# Contributed by Qualcomm Connected Experiences, Inc.,
# with authorization from the AllSeen Alliance, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Pursuant to Section 1 of the License, the work of authorship constituting
# a Work and any Contribution incorporated in the Work shall mean only that
# Contributor's code submissions authored by that Contributor.  Any rights
# granted under the License are conditioned upon acceptance of these
# clarifications.
#ifndef _LAMP_RESPONSE_CODES_H_
#define _LAMP_RESPONSE_CODES_H_
/**
 * @file LSFResponseCodes.h
 * @defgroup LSFResponseCodes Lamp Response Codes
 * @{
 */
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

/**
 * Lamp Response Codes
 * REMINDER: Update LSFResponseCodes.h in standard_core_library/common/inc if adding a new Lamp Response code.
 */
typedef enum {
    LAMP_OK                          = 0,  /**< Success status */
    LAMP_ERR_NULL                    = 1,  /**< Unexpected NULL pointer */
    LAMP_ERR_UNEXPECTED              = 2,  /**< An operation was unexpected at this time */
    LAMP_ERR_INVALID                 = 3,  /**< A value was invalid */
    LAMP_ERR_UNKNOWN                 = 4,  /**< A unknown value */
    LAMP_ERR_FAILURE                 = 5,  /**< A failure has occurred */
    LAMP_ERR_BUSY                    = 6,  /**< An operation failed and should be retried later */
    LAMP_ERR_REJECTED                = 7,  /**< The connection was rejected */
    LAMP_ERR_RANGE                   = 8,  /**< Value provided was out of range */
    LAMP_ERR_INVALID_FIELD           = 10, /**< Invalid param/state field */
    LAMP_ERR_MESSAGE                 = 11, /**< An invalid message was received */
    LAMP_ERR_INVALID_ARGS            = 12, /**< The arguments were invalid */
    LAMP_ERR_EMPTY_NAME              = 13, /**< The name was empty */
    LAMP_ERR_RESOURCES               = 14, /**< Out of memory*/
    LAMP_ERR_REPLY_WITH_INVALID_ARGS = 15, /**< The reply received for a message had invalid arguments */
    LAMP_RESPONSE_CODE_LAST                /**< The last Lamp Response code */
} LampResponseCode;

/**
 * @}
 */
#endif
