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
 * This file defines the signal hash table class
 *
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

#include <qcc/platform.h>
#include <qcc/Debug.h>
#include <qcc/String.h>

#include <list>

#include "SignalTable.h"

/** @internal */
#define QCC_MODULE "ALLJOYN"

using namespace std;

namespace ajn {

void SignalTable::Add(MessageReceiver* receiver,
                      MessageReceiver::SignalHandler handler,
                      const InterfaceDescription::Member* member,
                      const qcc::String& sourcePath)
{
    QCC_DbgTrace(("SignalTable::Add(iface = {%s}, member = {%s}, sourcePath = \"%s\")",
                  member->iface->GetName(),
                  member->name.c_str(),
                  sourcePath.c_str()));
    Entry entry(handler, receiver, member);
    Key key(sourcePath, member->iface->GetName(), member->name);
    lock.Lock(MUTEX_CONTEXT);
    hashTable.insert(pair<const Key, Entry>(key, entry));
    lock.Unlock(MUTEX_CONTEXT);
}

void SignalTable::Remove(MessageReceiver* receiver,
                         MessageReceiver::SignalHandler handler,
                         const InterfaceDescription::Member* member,
                         const char* sourcePath)
{
    Key key(sourcePath, member->iface->GetName(), member->name.c_str());
    iterator iter;
    pair<iterator, iterator> range;

    lock.Lock(MUTEX_CONTEXT);
    range = hashTable.equal_range(key);
    iter = range.first;
    while (iter != range.second) {
        if ((iter->second.object == receiver) && (iter->second.handler == handler)) {
            hashTable.erase(iter);
            break;
        } else {
            ++iter;
        }
    }
    lock.Unlock(MUTEX_CONTEXT);
}

void SignalTable::RemoveAll(MessageReceiver* receiver)
{
    bool removed;
    lock.Lock(MUTEX_CONTEXT);
    do {
        removed = false;
        for (iterator iter = hashTable.begin(); iter != hashTable.end(); ++iter) {
            if (iter->second.object == receiver) {
                hashTable.erase(iter);
                removed = true;
                break;
            }
        }
    } while (removed);
    lock.Unlock(MUTEX_CONTEXT);
}

pair<SignalTable::const_iterator, SignalTable::const_iterator> SignalTable::Find(const char* sourcePath,
                                                                                 const char* iface,
                                                                                 const char* signalName)
{
    Key key(sourcePath, iface, signalName);
    return hashTable.equal_range(key);
}

}

