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
# isolated commits:
# --------------------------------------------
 # commit id: e28324502270e7cb76e9ab525d005548363d58c5 
 * Copyright AllSeen Alliance. All rights reserved.
# --------------------------------------------
 # commit id: 427fcbf3eb07c6c4354cbcaf706fe8e49ec26196 

        class BufferSink : public Sink {
          public:
            virtual ~BufferSink() { }

            QStatus PushBytes(const void* buf, size_t numBytes, size_t& numSent)
            {
                const uint8_t* start = static_cast<const uint8_t*>(buf);
                const uint8_t* end = start + numBytes;
                sbuf.reserve(sbuf.size() + numBytes);
                sbuf.insert(sbuf.end(), start, end);
                numSent = numBytes;
                return ER_OK;
            }
            const std::vector<uint8_t>& GetBuffer() const { return sbuf; }
            void SecureClear() { ClearMemory(sbuf.data(), sbuf.size()); }

          private:
            std::vector<uint8_t> sbuf;    /**< storage for byte stream */
        };


        BufferSink buffer;
            status = keyStore.Push(buffer);
                dataIn.pbData = (BYTE*)buffer.GetBuffer().data();
                dataIn.cbData = buffer.GetBuffer().size();
        buffer.SecureClear();
# --------------------------------------------
 # commit id: 0478168837cb4d5d9c695475629c918bb7a623d4 
                 * the CryptUnprotectData step and pass an empty buffer into the KeyStore.
                    if (fileSize > 0) {
                        if (CryptUnprotectData(&dataIn, NULL, NULL, NULL, NULL, 0, &dataOut)) {
                            StringSource bufferSource(dataOut.pbData, dataOut.cbData);
                            status = keyStore.Pull(bufferSource, fileName);
                        } else {
                            status = ER_BUS_CORRUPT_KEYSTORE;
                            QCC_LogError(status, ("CryptUnprotectData reading keystore failed error=(0x%08X) status=(0x%08X)", ::GetLastError(), status));
                        }
                    } else {
                        String empty;
                        StringSource bufferSource(empty);
                        status = keyStore.Pull(bufferSource, fileName);
                    }
# --------------------------------------------
 # commit id: 1c58e5fe2eb9be7b713c3ff9bb09e564f76b4d52 
/**
 * @file
 * The KeyStoreListenerFactory implements the default key store listener to stores key blobs.  This is place holder implementation.  It should be replaced with
 * a windows specific implementation.
 */

/******************************************************************************
 * Copyright (c) 2015, AllSeen Alliance. All rights reserved.
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
#include <qcc/Debug.h>
#include <qcc/String.h>
#include <qcc/FileStream.h>
#include <qcc/Util.h>

#include <alljoyn/KeyStoreListener.h>

#include "KeyStore.h"

#include <alljoyn/Status.h>

#define QCC_MODULE "ALLJOYN_AUTH"

using namespace std;
using namespace qcc;

namespace ajn {

class DefaultKeyStoreListener : public KeyStoreListener {

  public:

    DefaultKeyStoreListener(const qcc::String& application, const char* fname) {
        if (fname) {
            fileName = GetHomeDir() + "/" + fname;
        } else {
            fileName = GetHomeDir() + "/.alljoyn_keystore/" + application;
        }
    }

    QStatus LoadRequest(KeyStore& keyStore) {
        QStatus status;
        /* Try to load the keystore */
        {
            FileSource source(fileName);
            if (source.IsValid()) {
                source.Lock(true);
                status = keyStore.Pull(source, fileName);
                if (status == ER_OK) {
                    QCC_DbgHLPrintf(("Read key store from %s", fileName.c_str()));
                }
                source.Unlock();
                return status;
            }
        }
        /* Create an empty keystore */
        {
            FileSink sink(fileName, FileSink::PRIVATE);
            if (!sink.IsValid()) {
                status = ER_BUS_WRITE_ERROR;
                QCC_LogError(status, ("Cannot initialize key store %s", fileName.c_str()));
                return status;
            }
        }
        /* Load the empty keystore */
        {
            FileSource source(fileName);
            if (source.IsValid()) {
                source.Lock(true);
                status = keyStore.Pull(source, fileName);
                if (status == ER_OK) {
                    QCC_DbgHLPrintf(("Initialized key store %s", fileName.c_str()));
                } else {
                    QCC_LogError(status, ("Failed to initialize key store %s", fileName.c_str()));
                }
                source.Unlock();
            } else {
                status = ER_BUS_READ_ERROR;
            }
            return status;
        }
    }

    QStatus StoreRequest(KeyStore& keyStore) {
        QStatus status;
        FileSink sink(fileName, FileSink::PRIVATE);
        if (sink.IsValid()) {
            sink.Lock(true);
            status = keyStore.Push(sink);
            if (status == ER_OK) {
                QCC_DbgHLPrintf(("Wrote key store to %s", fileName.c_str()));
            }
            sink.Unlock();
        } else {
            status = ER_BUS_WRITE_ERROR;
            QCC_LogError(status, ("Cannot write key store to %s", fileName.c_str()));
        }
        return status;
    }

  private:

    qcc::String fileName;

};

KeyStoreListener* KeyStoreListenerFactory::CreateInstance(const qcc::String& application, const char* fname)
{
    return new DefaultKeyStoreListener(application, fname);
}

}
# --------------------------------------------
 # commit id: 0fac83092e95fdccbc658f68dcec67adc4ae7381 
 * Copyright AllSeen Alliance. All rights reserved.
# --------------------------------------------
 # commit id: 15fe81dd697c99d6a8214d20c9feef858ba63b8d 

        class BufferSink : public Sink {
          public:
            virtual ~BufferSink() { }

            QStatus PushBytes(const void* buf, size_t numBytes, size_t& numSent)
            {
                const uint8_t* start = static_cast<const uint8_t*>(buf);
                const uint8_t* end = start + numBytes;
                sbuf.reserve(sbuf.size() + numBytes);
                sbuf.insert(sbuf.end(), start, end);
                numSent = numBytes;
                return ER_OK;
            }
            const std::vector<uint8_t>& GetBuffer() const { return sbuf; }
            void SecureClear() { ClearMemory(sbuf.data(), sbuf.size()); }

          private:
            std::vector<uint8_t> sbuf;    /**< storage for byte stream */
        };


        BufferSink buffer;
        DATA_BLOB dataIn = { 0 };
        DATA_BLOB dataOut = { 0 };
        size_t pushed = 0;

            status = keyStore.Push(buffer);

            if (status == ER_OK) {
                dataIn.pbData = (BYTE*)buffer.GetBuffer().data();
                dataIn.cbData = buffer.GetBuffer().size();
                if (!CryptProtectData(&dataIn, NULL, NULL, NULL, NULL, 0, &dataOut)) {
                    status = ER_BUS_CORRUPT_KEYSTORE;
                    QCC_LogError(status, ("CryptProtectData writing keystore failed error=(0x%08X) status=(0x%08X)", ::GetLastError(), status));
                }
            }

            if (status == ER_OK) {
                status = sink.PushBytes(dataOut.pbData, dataOut.cbData, pushed);
            }

            if (status == ER_OK && pushed != dataOut.cbData) {
                status = ER_BUS_CORRUPT_KEYSTORE;
            }


        buffer.SecureClear();
        LocalFree(dataOut.pbData);

# --------------------------------------------
 # commit id: e61eead722824b74723a1f630fc5d6665ac08e0d 

                int64_t fileSize = 0;
                size_t pulled = 0;
                status = source.GetSize(fileSize);

                /**
                 * The key store should never be more than 4 GB, check here to prevent an overflow when assigning
                 * the filesize to a 32 bit DWORD.
                 */
                if ((status == ER_OK) && (fileSize >= (int64_t)UINT_MAX)) {
                    status = ER_BUS_CORRUPT_KEYSTORE;
                }

                if (status == ER_OK) {
                    dataIn.cbData = fileSize;
                    dataIn.pbData = new uint8_t[dataIn.cbData];
                    if (dataIn.pbData == NULL) {
                        status = ER_OUT_OF_MEMORY;
                    }
                }

                if (status == ER_OK) {
                    status = source.PullBytes(dataIn.pbData, dataIn.cbData, pulled);
                }

                if ((status == ER_OK) && ((int64_t)pulled != fileSize)) {
                    status = ER_BUS_CORRUPT_KEYSTORE;
                }

                /**
                 * CryptUnprotectData will return an invalid argument error if called with a 0 byte buffer. This happens after
                 * AllJoyn creates the KeyStore file, but hasn't yet written any keys to the store. In this case, just skip
                 * the CryptUnprotectData step and pass an empty buffer into the KeyStore.
                 */
                if (status == ER_OK) {
                    if (fileSize > 0) {
                        if (CryptUnprotectData(&dataIn, NULL, NULL, NULL, NULL, 0, &dataOut)) {
                            StringSource bufferSource(dataOut.pbData, dataOut.cbData);
                            status = keyStore.Pull(bufferSource, fileName);
                        } else {
                            status = ER_BUS_CORRUPT_KEYSTORE;
                            QCC_LogError(status, ("CryptUnprotectData reading keystore failed error=(0x%08X) status=(0x%08X)", ::GetLastError(), status));
                        }
                    } else {
                        String empty;
                        StringSource bufferSource(empty);
                        status = keyStore.Pull(bufferSource, fileName);
                    }
                }

