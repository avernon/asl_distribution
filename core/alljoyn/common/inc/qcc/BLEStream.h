# Contributed by Qualcomm Connected Experiences, Inc.,
# with authorization from the AllSeen Alliance, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Pursuant to Section 1 of the License, the work of authorship constituting
# a Work and any Contribution incorporated in the Work shall mean only that
# Contributor's code submissions authored by that Contributor.  Any rights
# granted under the License are conditioned upon acceptance of these
# clarifications.
/**
 * @file
 *
 * This file defines a BLE based physical link for communication.
 */

/******************************************************************************
 *
 *
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

#ifndef _QCC_BLESTREAM_H
#define _QCC_BLESTREAM_H

#include <qcc/platform.h>
#include <qcc/Stream.h>
#include <qcc/Thread.h>
#include <qcc/BLEStreamAccessor.h>

namespace qcc {

/**
 * Opens a serial device at the specified baud rate, 8-N-1, and
 * returns the file descriptor.
 *
 * @param adapterName       name of the device to open (optional)
 * @param[out] remObj	the remote Object string.
 *
 * @return ER_OK - port opened sucessfully, error otherwise.
 */
QStatus BLE(qcc::String& remObj);
QStatus BLE(const qcc::String& adapterName, qcc::String& remObj);

class BLEStream : public NonBlockingStream {
  public:

    BLEStream(BLEStreamAccessor* accessor, qcc::String remObj);

    virtual ~BLEStream();

    /* Close the fd */
    virtual void Close();

    /**
     * Pull bytes from the stream.
     * The source is exhausted when ER_NONE is returned.
     *
     * @param buf          Buffer to store pulled bytes
     * @param reqBytes     Number of bytes requested to be pulled from source.
     * @param actualBytes  Actual number of bytes retrieved from source.
     * @param timeout      Time to wait to pull the requested bytes.
     * Note: Since this is a non-blocking stream, this parameter is ignored.
     * @return   ER_OK if successful. ER_NONE if source is exhausted. Otherwise an error.
     */
    virtual QStatus PullBytes(void* buf, size_t numBytes, size_t& actualBytes, uint32_t timeout = 0);

    /**
     * Push zero or more bytes into the sink with infinite ttl.
     *
     * @param buf          Buffer to store pulled bytes
     * @param numBytes     Number of bytes from buf to send to sink.
     * @param numSent      Number of bytes actually consumed by sink.
     * @return   ER_OK if successful.
     */
    virtual QStatus PushBytes(const void* buf, size_t numBytes, size_t& actualBytes);

    /**
     * Get the Event indicating that data is available.
     *
     * @return Event that is set when data is available.
     */
    virtual Event& GetSourceEvent() { return *sourceEvent; }

    /**
     * Get the Event indicating that sink can accept data.
     *
     * @return Event set when socket can accept more data via PushBytes
     */
    virtual Event& GetSinkEvent() { return *sinkEvent; }

    qcc::String GetRemObj() { return remObj; }
  private:

    /** Private default constructor - does nothing */
    BLEStream();

    /**
     * Private Copy-constructor - does nothing
     *
     * @param other  BLEStream to copy from.
     */
    BLEStream(const BLEStream& other);

    /**
     * Private Assignment operator - does nothing.
     *
     * @param other  BLEStream to assign from.
     */
    BLEStream operator=(const BLEStream& other) { return *this; };

    qcc::String remObj; /**< File descriptor associated with the device */
    BLEStreamAccessor* locAcc; /**< BLE Stream Accessor */
    Event* sourceEvent; /**< Event signaled when data is available */
    Event* sinkEvent;   /**< Event signaled when sink can accept data */
};

class BLEController : public StreamController {
  public:

    BLEController(BLEStream* bleStream, StreamReadListener* readListener);
    ~BLEController() { };
    QStatus Start();
    QStatus Stop();
    QStatus Join();

    /**
     * Push zero or more bytes into the sink with infinite ttl.
     *
     * @param buf          Buffer to store pulled bytes
     * @param numBytes     Number of bytes from buf to send to sink.
     * @param numSent      Number of bytes actually consumed by sink.
     * @return   ER_OK if successful.
     */
    virtual QStatus PushBytes(const void* buf, size_t numBytes, size_t& actualBytes);
    /**
     * Read callback for the stream.
     * @param buffer        buffer containing read bytes
     * @param bytes         number of bytes in buffer
     * @return  ER_OK if successful.
     */
    virtual QStatus ReadCallback(const uint8_t* buffer, size_t bytes);
    BLEStream* m_bleStream;           /**< The BLE stream that this controller reads from */
    int exitCount;                    /**< Count indicating whether the ble stream has exited successfully. */

    void SetConnected(bool connected) { SetOnline(connected); if (connected) { m_bleStream->GoOnline(); } }
    bool IsConnected() { return IsOnline(); }
};
}
#endif
