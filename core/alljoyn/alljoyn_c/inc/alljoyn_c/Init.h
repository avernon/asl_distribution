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
#ifndef _ALLJOYN_C_INIT_H
#define _ALLJOYN_C_INIT_H

#include <qcc/platform.h>

#include <alljoyn_c/AjAPI.h>
#include <alljoyn_c/Status.h>

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
extern AJ_API QStatus AJ_CALL alljoyn_init(void);

/**
 * Call this to release any resources acquired in alljoyn_init().  No AllJoyn
 * functionality may be used after calling this.
 *
 * This function is not thread-safe.
 *
 * @return
 *  - #ER_OK on success
 *  - error code indicating failure otherwise
 */
extern AJ_API QStatus AJ_CALL alljoyn_shutdown(void);

#ifdef DOXYGEN_DOC

/**
 * This must be called before using any AllJoyn router functionality.
 *
 * For an application that is a routing node (either standalone or bundled), the
 * complete initialization sequence is:
 * @code
 * alljoyn_init();
 * alljoyn_routerinit();
 * @endcode
 *
 * This function is not thread-safe.
 *
 * @return
 *  - #ER_OK on success
 *  - error code indicating failure otherwise
 */
extern AJ_API QStatus AJ_CALL alljoyn_routerinit(void);

/**
 * Call this to release any resources acquired in alljoyn_routerinit().
 *
 * For an application that is a routing node (either standalone or bundled), the
 * complete shutdown sequence is:
 * @code
 * alljoyn_routershutdown();
 * alljoyn_shutdown();
 * @endcode
 *
 * This function is not thread-safe.
 *
 * @return
 *  - #ER_OK on success
 *  - error code indicating failure otherwise
 */
extern AJ_API QStatus AJ_CALL alljoyn_routershutdown(void);

#else

/*
 * For usage, see the docs above for alljoyn_routerinit() and
 * alljoyn_routershutdown().
 *
 * The macro magic here is to allow compilation with or without router support.
 *
 * When router support is not compiled in, alljoyn_routerinit is not used and
 * there is no undefined reference to AllJoynRouterInit.  When router support is
 * compiled in, alljoyn_routerinit is used and the reference to
 * AllJoynRouterInit is contained in the router library.
 */
extern AJ_API QStatus AJ_CALL AllJoynRouterInit(void);
#define alljoyn_routerinit AllJoynRouterInit
extern AJ_API QStatus AJ_CALL AllJoynRouterShutdown(void);
#define alljoyn_routershutdown AllJoynRouterShutdown

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
