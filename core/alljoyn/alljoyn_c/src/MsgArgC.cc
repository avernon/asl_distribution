/**
 * @file
 *
 * This file implements the BusAttachmentC class.
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
#include "MsgArgC.h"
#include <alljoyn_c/Status.h>
#include <alljoyn/MsgArg.h>
#include <qcc/Debug.h>

#define QCC_MODULE "ALLJOYN_C"

namespace ajn {
QStatus MsgArgC::MsgArgUtilsSetVC(MsgArg* args, size_t& numArgs, const char* signature, va_list* argp)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return MsgArgUtils::SetV(args, numArgs, signature, argp);
}

QStatus MsgArgC::VBuildArgsC(const char*& signature, size_t sigLen, MsgArg* arg, size_t maxArgs, va_list* argp, size_t* count)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return VBuildArgs(signature, sigLen, arg, maxArgs, argp, count);
}

QStatus MsgArgC::VParseArgsC(const char*& signature, size_t sigLen, const MsgArg* argList, size_t numArgs, va_list* argp)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return VParseArgs(signature, sigLen, argList, numArgs, argp);
}
}
