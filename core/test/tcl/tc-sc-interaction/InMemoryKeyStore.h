/**
 * @file
 * In-memory keystore implementation
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
#ifndef _INMEMORYKEYSTORE_H
#define _INMEMORYKEYSTORE_H

#include <qcc/platform.h>
#include <qcc/GUID.h>
#include <qcc/StringSink.h>
#include <qcc/StringSource.h>
#include <qcc/StringUtil.h>

#include <alljoyn/KeyStoreListener.h>
#include <alljoyn/Status.h>
#include "KeyStore.h"

namespace ajn {

class InMemoryKeyStoreListener : public KeyStoreListener {

  public:

    InMemoryKeyStoreListener() : KeyStoreListener()
    {
        qcc::GUID128 guid;
        pwd = guid.ToString();
    }

    InMemoryKeyStoreListener(qcc::String& source, qcc::String& pwd) : KeyStoreListener(), pwd(pwd)
    {
        CopySink(source);
    }

    QStatus LoadRequest(KeyStore& keyStore) {
        lock.Lock(MUTEX_CONTEXT);
        qcc::StringSource source(sink.GetString());
        QStatus status = keyStore.Pull(source, pwd);
        lock.Unlock(MUTEX_CONTEXT);
        return status;
    }

    QStatus StoreRequest(KeyStore& keyStore) {
        qcc::StringSink newSink;
        QStatus status = keyStore.Push(newSink);
        if (ER_OK != status) {
            return status;
        }
        lock.Lock(MUTEX_CONTEXT);
        sink.Clear();
        status = CopySink(newSink.GetString());
        lock.Unlock(MUTEX_CONTEXT);
        return status;
    }

    /**
     * Assignment operator
     */
    InMemoryKeyStoreListener& operator=(const InMemoryKeyStoreListener& other)
    {
        if (this != &other) {
            pwd = other.pwd;
            CopySink(other.sink);
        }
        return *this;
    }

    /**
     * Copy constructor
     */
    InMemoryKeyStoreListener(const InMemoryKeyStoreListener& other)
    {
        pwd = other.pwd;
        CopySink(other.sink);
    }

  private:

    QStatus CopySink(qcc::String& other)
    {
        size_t numSent = 0;
        return sink.PushBytes(other.data(), other.length(), numSent);
    }

    QStatus CopySink(const qcc::StringSink& other)
    {
        return CopySink(((qcc::StringSink&) other).GetString());
    }

    qcc::Mutex lock;
    qcc::StringSink sink;
    qcc::String pwd;
};

}

#endif // _INMEMORYKEYSTORE_H
