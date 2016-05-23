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

#ifndef CONVERSIONS_H_
#define CONVERSIONS_H_

#include <qcc/platform.h>
#include <alljoyn/Status.h>
#include <qcc/String.h>

namespace ajn {

class MsgArg;

namespace services {
/**
 * class contains methods for conversion needs
 */
class Conversions {
  public:
    /**
     * Convert MsgArg to array of bytes
     *
     * @param msgArg    An array of MsgArgs to unpack.
     * @param byteArray    pointer to ponter to uint8_t to return.
     * @param len       The length of byte array.
     * @return status ER_BUS_BAD_VALUE_TYPE in case of failure
     */
    static QStatus MsgArgToArrayOfBytes(const MsgArg* msgArg, uint8_t** byteArray, size_t* len);
    /**
     * Convert MsgArg to array of bytes
     *
     * @param msgBin   An array of bytes
     * @param len      The length of byte array.
     * @param byteArrayStr    String to receive.
     *
     */
    static void ArrayOfBytesToString(uint8_t const*const* msgBin, size_t len, qcc::String* byteArrayStr);
    /**
     * Convert hex to char
     *
     * @param hex string
     * @param outBytes
     * @param len - expected len of outbytes
     * @return status
     */
    static QStatus HexStringToBytes(const qcc::String& hex, uint8_t* outBytes, size_t len);

  private:
    Conversions();
    ~Conversions();
    /**
     * Convert hex to char
     *
     * @param c        hex
     * @return
     *    expected char
     *    -1 on error
     */

    static char HexToChar(char c);

};

} //services
} //ajn

#endif /* CONVERSIONS_H_ */
