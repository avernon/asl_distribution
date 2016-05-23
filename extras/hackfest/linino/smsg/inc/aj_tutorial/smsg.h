/**
 * @file
 * Arduino Yun SPI communications driver.
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


class SMsg {
  public:
    static const uint8_t MAX_MSG_LEN = 31;

    SMsg();
    ~SMsg();

    /**
     * Read a message from the Arduino side of the SPI bus.
     *
     * @param[out] buf  Pointer to a buffer to store the message payload.
     * @param[in]  len  Size of the buffer for storing the message payload.
     *
     * @return  The actual number of bytes read or -1 on error.
     */
    int Read(uint8_t* buf, uint8_t len);

    /**
     * Send a message to the Arduino side of the SPI bus.
     *
     * @param buf   Pointer to a buffer with the message payload to send.
     * @param len   Size of the message payload to send.
     *
     * @return  The actual number of bytes sent or -1 on error.
     */
    int Write(const uint8_t* buf, uint8_t len);

    /**
     * Get access to the underlying file descriptor used to communicate with
     * the joystick driver sketch running on the Arduino.  Only use this file
     * descriptor with select() or epoll().  Use the methods in this class for
     * actual communication.
     */
    int GetFD() const { return fd; }

  private:
    uint8_t txseq;
    uint8_t rxseq;
    int fd;

    int ReadMsg(uint8_t* buf, uint8_t len);
    int WriteMsg(const uint8_t* buf, uint8_t len);
    bool ReadByte(uint8_t* buf);
    bool WriteByte(const uint8_t buf);
    void FlushRead();
    bool WaitForMsg(uint32_t timeout);
};



#endif
