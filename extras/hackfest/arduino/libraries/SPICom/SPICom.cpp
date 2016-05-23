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

#include "SPICom.h"
#include "StreamSPI.h"

#define MAX_SEQ_NUMBER 0x3f

#define SPICOM_ACK 0xc0
#define SPICOM_NACK 0x80
#define SPICOM_ACK_MASK (SPICOM_ACK | SPICOM_NACK)
#define SPICOM_SEQ_MASK (~SPICOM_ACK_MASK)

#define RD_TO 20

static int waitRX(long ms)
{
    long expire = (long)millis() + ms;
    while (expire - (long)millis() > 0) {
        if (StreamSPI0.available()) {
            return 1;
        }
    }
    return 0;
}

static void flushRX(void)
{
    while (waitRX(10)) {
        int c = StreamSPI0.read();
        Serial.print(" f");
        Serial.print(c, HEX);
    }
}


static int readTO(long to)
{
    if (waitRX(to)) {
        int c = StreamSPI0.read();
        Serial.print(" r");
        Serial.print(c, HEX);
        return c;
    }
    return -1;
}

static void _write(int c)
{
    StreamSPI0.write(c);
    Serial.print(" w");
    Serial.print(c, HEX);
}


SPICom::SPICom():
    rxseq(0),
    txseq(0)
{
}

SPICom::~SPICom()
{
}

void SPICom::begin(void)
{
    StreamSPI0.begin();
}


int SPICom::read(byte* buf, int len)
{
    int ret;
    do {
        Serial.print("RD:");
        ret = readMsg(buf, len);
        Serial.println();
    } while (ret == 0);
    return ret;
}

int SPICom::write(const byte* buf, int len)
{
    if ((len < 1) || (len > MAX_MSG_LEN)) {
        return 0;
    }

    Serial.print("WR:");
    int ret = writeMsg(buf, len);
    Serial.println();
    return ret;
}


int SPICom::readMsg(byte* buf, int len)
{
    uint16_t sum = 0;
    int pos = 0;
    int ack = SPICOM_NACK | rxseq;
    int plen;
    int pseq;
    int psumbuf;
    int i;

    plen = readTO(RD_TO);
    if (plen < 0) {
        /* no flushing, no acking */
        return 0;
    }

    if ((plen > MAX_MSG_LEN) || (plen > len)) {
        goto exit;
    }
    sum += plen * (++pos);

    pseq = readTO(RD_TO);
    if ((pseq < -1) || (pseq != rxseq)) {
        if ((pseq >= 0) && (pseq <= MAX_SEQ_NUMBER)) {
            rxseq = pseq;  // assume that our rxseq value is wrong.
        }
        goto exit;
    }
    sum += pseq * (++pos);

    for (i = 0; i < plen; ++i) {
        int c;
        c = readTO(RD_TO);
        if (c < 0) {
            goto exit;
        }
        buf[i] = c;
        sum += c * (++pos);
    }

    psumbuf = readTO(RD_TO);
    if ((psumbuf < 0) || (((sum >> 8) & 0xff) != psumbuf)) {
        goto exit;
    }

    psumbuf = readTO(RD_TO);
    if ((psumbuf < 0) || ((sum & 0xff) != psumbuf)) {
        goto exit;
    }

    ack |= SPICOM_ACK;
    ++rxseq;
    rxseq &= MAX_SEQ_NUMBER;

exit:
    flushRX();
    _write(ack);

    return ((ack & SPICOM_ACK_MASK) == SPICOM_ACK) ? plen : -1;
}

int SPICom::writeMsg(const byte* buf, int len)
{
    uint16_t sum = 0;
    byte pos = 0;
    int ack;
    int i;

    sum += ((len) * (++pos));
    _write(len);

    sum += txseq * (++pos);
    _write(txseq);

    for (i = 0; i < len; ++i) {
        sum += buf[i] * (++pos);
        _write(buf[i]);
    }

    _write((sum >> 8) & 0xff);
    _write(sum & 0xff);

    ack = readTO(2 * RD_TO);

    if ((ack < 0) || ((ack & SPICOM_ACK_MASK) != SPICOM_ACK) || ((ack & SPICOM_SEQ_MASK) != txseq)) {
        if ((ack & SPICOM_ACK_MASK) == 0) {
            flushRX();
        }
        return -1;
    }

    ++txseq;
    txseq &= MAX_SEQ_NUMBER;

    return len;
}

