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
#include <qcc/platform.h>
#include "alljoyn/services_common/Conversions.h"
#include <alljoyn/MsgArg.h>
#include <qcc/String.h>
#include <alljoyn/BusAttachment.h>
#include <qcc/platform.h>
#include <qcc/String.h>
#include <alljoyn/Status.h>
#include "alljoyn/services_common/ServicesCommonConstants.h"
#include <iostream>
#include <sstream>
#include "alljoyn/services_common/LogModule.h"

using namespace ajn;
using namespace services;
using namespace commonConsts;
using namespace qcc;

QStatus Conversions::MsgArgToArrayOfBytes(const MsgArg* msgArg, uint8_t** byteArray, size_t* len)
{
    QStatus status = ER_OK;
    if (msgArg->typeId != ALLJOYN_BYTE_ARRAY) {
        status = ER_BUS_BAD_VALUE_TYPE;
        QCC_LogError(status, ("ERROR- Problem receiving message: Can not unmarshal this array of bytes argument."));
        return status;
    }

    status = msgArg->Get(AJPARAM_ARR_BYTE.c_str(), len, byteArray);
    if (*len != UUID_LENGTH) {
        status = ER_BUS_BAD_VALUE;
        QCC_LogError(status, ("ERROR- Array of bytes length is not equal to %d  but to %d", UUID_LENGTH * 2, *len));
        return status;
    }
    return status;
}

void Conversions::ArrayOfBytesToString(uint8_t const*const* byteArray, size_t len, qcc::String* byteArrayStr)
{
    uint32_t i;
    static const char* const chars = "0123456789ABCDEF";

    (*byteArrayStr).reserve(2 * len);
    for (i = 0; i < len; ++i) {
        const unsigned char c = (*byteArray)[i];
        (*byteArrayStr).push_back(chars[c >> 4]);
        (*byteArrayStr).push_back(chars[c & 15]);
    }
}

char Conversions::HexToChar(char c)
{
    if ('0' <= c && c <= '9') {
        return c - '0';
    } else if ('a' <= c && c <= 'f') {
        return c + 10 - 'a';
    } else if ('A' <= c && c <= 'F') {
        return c + 10 - 'A';
    }

    return -1;
}

QStatus Conversions::HexStringToBytes(const qcc::String& hex, uint8_t* outBytes, size_t len)
{
    unsigned char achar, bchar;
    for (size_t i = 0; i < len; i++) {

        if ((char) (achar = HexToChar(hex[i * 2])) ==  -1) {
            return ER_FAIL;
        }
        if ((char) (bchar = HexToChar(hex[i * 2 + 1])) == -1) {
            return ER_FAIL;
        }
        outBytes[i] = ((achar << 4) | bchar);
    }
    return ER_OK;
}
