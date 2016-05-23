/**
 * @file
 * Functions required to startup and cleanup AllJoyn.
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
#ifndef _ALLJOYN_INIT_H
#define _ALLJOYN_INIT_H

#include <qcc/platform.h>
#include <alljoyn/Status.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This must be called prior to instantiating or using any AllJoyn
 * functionality.
 *
 * This function is not thread-safe.
 *
 * @return
 *  - #ER_OK on success
 *  - error code indicating failure otherwise
 */
extern AJ_API QStatus AJ_CALL AllJoynInit(void);

/**
 * Call this to release any resources acquired in AllJoynInit().  No AllJoyn
 * functionality may be used after calling this.
 *
 * This function is not thread-safe.
 * @return
 *  - #ER_OK on success
 *  - error code indicating failure otherwise
 */
extern AJ_API QStatus AJ_CALL AllJoynShutdown(void);

/**
 * This must be called before using any AllJoyn router functionality.
 *
 * For an application that is a routing node (either standalone or bundled), the
 * complete initialization sequence is:
 * @code
 * AllJoynInit();
 * AllJoynRouterInit();
 * @endcode
 *
 * This function is not thread-safe.
 *
 * @return
 *  - #ER_OK on success
 *  - error code indicating failure otherwise
 */
extern AJ_API QStatus AJ_CALL AllJoynRouterInit(void);

/**
 * Call this to release any resources acquired in AllJoynRouterInit().
 *
 * For an application that is a routing node (either standalone or bundled), the
 * complete shutdown sequence is:
 * @code
 * AllJoynRouterShutdown();
 * AllJoynShutdown();
 * @endcode
 *
 * This function is not thread-safe.
 *
 * @return
 *  - #ER_OK on success
 *  - error code indicating failure otherwise
 */
extern AJ_API QStatus AJ_CALL AllJoynRouterShutdown(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
