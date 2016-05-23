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
#ifndef _ALLJOYN_C_MSGARGC_H
#define _ALLJOYN_C_MSGARGC_H

#include <alljoyn/Message.h>
#include <alljoyn/MsgArg.h>
#include <MsgArgUtils.h>
#include <alljoyn_c/Status.h>
namespace ajn {
/**
 * MsgArgC is used to map 'C' code to the 'C++' MsgArg code where additional handling
 * is needed to convert from a 'C' type to a 'C++' type.
 */
class MsgArgC : public MsgArg {
    friend class MsgArgUtils;
  public:
    /**
     * constructor
     */
    MsgArgC() : MsgArg() { }

    /**
     * copy constructor
     */
    MsgArgC(const MsgArgC& other) : MsgArg(static_cast<MsgArg>(other)) { }

    /**
     * Constructor
     *
     * @param typeId  The type for the MsgArg
     */
    MsgArgC(AllJoynTypeId typeId) : MsgArg(typeId) { }

    static QStatus MsgArgUtilsSetVC(MsgArg* args, size_t& numArgs, const char* signature, va_list* argp);

    static QStatus VBuildArgsC(const char*& signature, size_t sigLen, MsgArg* arg, size_t maxArgs, va_list* argp, size_t* count = NULL);
    static QStatus VParseArgsC(const char*& signature, size_t sigLen, const MsgArg* argList, size_t numArgs, va_list* argp);
};
}
#endif
