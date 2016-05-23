/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

#ifndef SERVICES_COMMON_CONSTANTS_H_
#define SERVICES_COMMON_CONSTANTS_H_

#include <qcc/String.h>

/*
 * Common Macros
 */

namespace ajn {
namespace services {
namespace commonConsts {

static const uint16_t UUID_LENGTH = 16;

static const qcc::String AJPARAM_BOOL = "b";
static const qcc::String AJPARAM_UINT16 = "q";
static const qcc::String AJPARAM_STR = "s";
static const qcc::String AJPARAM_INT = "i";
static const qcc::String AJPARAM_ARR_BYTE = "ay";
static const qcc::String AJPARAM_VAR = "v";
static const qcc::String AJPARAM_INT16 = "n";
static const qcc::String AJPARAM_UINT32 = "u";
static const qcc::String AJPARAM_UINT64 = "t";
static const qcc::String AJPARAM_INT64 = "x";
static const qcc::String AJPARAM_DOUBLE = "d";


}         //namespace commonConsts
}     //namespace services
} //namespace ajn


#endif /* SERVICES_COMMON_CONSTANTS_H_ */

