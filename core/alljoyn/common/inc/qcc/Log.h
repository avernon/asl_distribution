/**
 * @file
 *
 * Log control.
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
#ifndef _QCC_LOG_H
#define _QCC_LOG_H

#include <qcc/platform.h>

/**
 * Set AllJoyn debug levels.
 *
 * @param module    name of the module to generate debug output
 * @param level     debug level to set for the module
 */
void QCC_SetDebugLevel(const char* module, uint32_t level);

/**
 * Set AllJoyn logging levels.
 *
 * @param logEnv    A semicolon separated list of KEY=VALUE entries used
 *                  to set the log levels for internal AllJoyn modules.
 *                  (i.e. ALLJOYN=7;ALL=1)
 */
void QCC_SetLogLevels(const char* logEnv);

/**
 * Indicate whether AllJoyn logging goes to OS logger or stdout
 *
 * @param  useOSLog   true iff OS specific logging should be used rather than print for AllJoyn debug messages.
 */
void QCC_UseOSLogging(bool useOSLog);


#endif
