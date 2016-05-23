/**
 * @file
 * Arduino Yun SPI communications driver - Linino side.
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


#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include <aj_tutorial/smsg.h>

#define RD_TO 500

#define BAUDRATE B230400


#if !defined(HOST_BUILD)
#define TTY_DEV "/dev/ttyATH0"
#endif

class CheckSum {
  public:
    CheckSum() : sum(0), pos(0) { }

    void AddByte(uint8_t b) { sum += (++pos * b); }
    uint8_t GetSumMSB() const { return (sum >> 8) & 0xff; }
    uint8_t GetSumLSB() const { return sum & 0xff; }

  private:
    uint16_t sum;
    uint8_t pos;
};


SMsg::SMsg(void): fd(-1)
{
#if !defined(HOST_BUILD)
    fd = open(TTY_DEV, O_RDWR | O_NONBLOCK | O_NOCTTY);
    if (fd < 0) {
        perror("opening " TTY_DEV);
    } else {
        struct termios tio;
        memset(&tio, 0, sizeof(tio));
        tio.c_iflag = 0;
        tio.c_oflag = 0;
        tio.c_cflag = CS8 | CREAD | CLOCAL;
        tio.c_lflag = 0;
        tio.c_cc[VMIN] = 0;
        tio.c_cc[VTIME] = 5;
        cfsetspeed(&tio, BAUDRATE);
        tcsetattr(fd, TCSANOW, &tio);
    }
#endif

    while (WaitForMsg(10 * RD_TO)) {
        FlushRead();
    }
}

SMsg::~SMsg(void)
{
    if (fd > 0) {
        close(fd);
    }
}


int SMsg::Read(uint8_t* buf, uint8_t len)
{
    int ret = -1;

    if (fd > 0) {
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);
        ret = select(fd + 1, &rfds, NULL, NULL, NULL);

        if (ret > 0) {
            ret = ReadMsg(buf, len);
        }
    }
    return ret;
}

int SMsg::Write(const uint8_t* buf, uint8_t len)
{
    if ((len < 1) || (len > MAX_MSG_LEN)) {
        return -1;
    }
    int ret = WriteMsg(buf, len);
    return ret;
}

int SMsg::ReadMsg(uint8_t* buf, uint8_t len)
{
    uint8_t plen;
    uint8_t psumbuf;
    CheckSum sum;
    uint8_t i;


    if (!ReadByte(&plen)) {
        return 0;
    }
    if ((plen > MAX_MSG_LEN) || (plen > len)) {
        return -1;
    }
    sum.AddByte(plen);

    for (i = 0; i < plen; ++i) {
        if (!ReadByte(&buf[i])) {
            return -1;
        }
        sum.AddByte(buf[i]);
    }

    if (!ReadByte(&psumbuf)) {
        return -1;
    }
    if (sum.GetSumMSB() != psumbuf) {
        return -1;
    }

    if (!ReadByte(&psumbuf)) {
        return -1;
    }
    if (sum.GetSumLSB() != psumbuf) {
        return -1;
    }

    FlushRead();

    return plen;
}


int SMsg::WriteMsg(const uint8_t* buf, uint8_t len)
{
    CheckSum sum;
    uint8_t sumbuf;
    uint8_t i;

    if (!WriteByte(len)) {
        return -1;
    }
    sum.AddByte(len);

    for (i = 0; i < len; ++i) {
        if (!WriteByte(buf[i])) {
            return -3;
        }
        sum.AddByte(buf[i]);
    }

    sumbuf = sum.GetSumMSB();
    if (!WriteByte(sumbuf)) {
        return -4;
    }

    sumbuf = sum.GetSumLSB();
    if (!WriteByte(sumbuf)) {
        return -5;
    }

    usleep(RD_TO * 2);

    return len;
}


bool SMsg::ReadByte(uint8_t* buf)
{
    if (WaitForMsg(RD_TO)) {
        if (fd > 0) {
            ssize_t ret = read(fd, buf, 1);
            if (ret > 0) {
                //printf(" r%02x", *buf); fflush(stdout);
                return true;
            }
        }
    }
    return false;
}

bool SMsg::WriteByte(const uint8_t buf)
{
    if (fd > 0) {
        //printf(" w%02x", buf); fflush(stdout);
        ssize_t ret = write(fd, &buf, 1);
        return (ret > 0);
    }
    return false;
}


void SMsg::FlushRead()
{
    uint8_t buf;

    while (WaitForMsg(RD_TO)) {
        if (fd > 0) {
            ssize_t ret = read(fd, &buf, 1);
            ret++; // suppress compiler warning.
            //printf(" f%02x", buf); fflush(stdout);
        }
    }
}


bool SMsg::WaitForMsg(uint32_t timeout)
{
    if (fd > 0) {
        fd_set rfds;
        struct timeval to = { 0, timeout };
        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);
        return (select(fd + 1, &rfds, NULL, NULL, &to) > 0);
    }
    return false;
}
