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
/**
 * @file
 * This file redefines __dllexport or __dllimport on relevant platforms
 *
 * This file also defines the deferred callback mechanism used to make sure the
 * callbacks occur on the same thread that registered for the callback.
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
#ifndef _ALLJOYN_C_AJAPI_H
#define _ALLJOYN_C_AJAPI_H

#include <qcc/platform.h>

/**
 * This @#define allows for setting of visibility support on relevant platforms
 */
#ifndef AJ_API
#  if defined(QCC_OS_GROUP_WINDOWS)
#    define AJ_API __declspec(dllexport)
#  elif defined(QCC_OS_GROUP_POSIX)
#    define AJ_API __attribute__((visibility("default")))
#  else
#    define AJ_API
#  endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Used to specify if an interface is part of an About announcement or not.
 */
typedef enum {
    UNANNOUNCED, ///< The interface is not announced
    ANNOUNCED    ///< The interface is announced
} alljoyn_about_announceflag;

/**
 * Unity-specific function to process alternate-thread callbacks on the main thread.
 *
 * @return the number of callbacks processed.
 */
extern AJ_API int alljoyn_unity_deferred_callbacks_process();

/**
 * Enable/disable main thread callback behavior.
 */
extern AJ_API void alljoyn_unity_set_deferred_callback_mainthread_only(QCC_BOOL mainthread_only);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
