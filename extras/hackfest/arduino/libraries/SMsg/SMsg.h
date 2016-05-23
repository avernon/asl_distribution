/**
 * @file
 * Arduino Yun SPI communications driver - Arduino side.
 */

/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#ifndef _SMSG_H_
#define _SMSG_H_

#include "Arduino.h"

class SMsg
{
  public:
    static const int MAX_MSG_LEN = 31;

    SMsg();
    ~SMsg();

    /**
     * This must be called in setup().
     */
    void begin();

    void waitLinuxBoot();
    byte linuxRebooting() { return rebooting; }

    int available() { return Serial1.available(); }

    /**
     * This reads a message in to buf provided that the message payload is
     * less than or equal to len in size.  The memory pointed to by buf must
     * be at least len in size.  If the message size is too large the sender
     * will receive a NACK response.
     *
     * @param buf      Buffer to hold the message payload
     * @param len      Size of the buffer (and largest acceptable payload)
     *
     * @returns  number of bytes read on success, -1 otherwise (contents of buf may be altered)
     */
    int read(byte* buf, int len);

    /**
     * This writes a message using the contents of buf as the payload.
     *
     * @param buf      Buffer with the message payload
     * @param len      Number of bytes to send
     *
     * @returns  number of bytes sent on success, -1 otherwise
     */
    int write(const byte* buf, int len);

  private:
    byte rebooting;

    int readMsg(byte* buf, int len);
    int writeMsg(const byte* buf, int len);
    int readTO(long to);
    void flushRX(void);
    void detectReboot(uint8_t c);

};


#endif
