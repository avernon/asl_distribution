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
 # commit id: 1c58e5fe2eb9be7b713c3ff9bb09e564f76b4d52 
/**
 * @file
 * The KeyStoreListenerFactory implements the default key store listener to stores key blobs.
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
