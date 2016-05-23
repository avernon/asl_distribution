/**
 * @file
 *
 * Debug control
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
#ifndef _QCC_DEBUGCONTROL_H
#define _QCC_DEBUGCONTROL_H

#include <qcc/Mutex.h>
#include <map>

namespace qcc {

class DebugControl {
  public:

    static void Init();
    static void Shutdown();

    DebugControl();

    void AddTagLevelPair(const char* tag, uint32_t level);

    void SetAllLevel(uint32_t level);

    void WriteDebugMessage(DbgMsgType type, const char* module, const qcc::String msg);

    void Register(QCC_DbgMsgCallback cb, void* context);

    bool Check(DbgMsgType type, const char* module);

    bool PrintThread() const;

  private:
    Mutex mutex;
    QCC_DbgMsgCallback cb;
    void* context;
    uint32_t allLevel;
    std::map<const qcc::String, uint32_t> modLevels;
    bool printThread;
};

}

#endif

