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

#ifndef _RULE_INFO_
#define _RULE_INFO_

#include <qcc/String.h>
#include <stdio.h>

class RuleInfo {
  public:
    RuleInfo(const char* uniqueName, const char* path, const char* iface,
             const char* member, const char* sig)
        : mUniqueName(uniqueName), mPath(path), mIfaceName(iface),
        mMember(member), mSignature(sig), mDeviceId(qcc::String::Empty), mAppId(qcc::String::Empty), mPort(0)
    { };

    RuleInfo(const char* uniqueName, const char* path, const char* iface,
             const char* member, const char* sig, const char* deviceId, const char* appId, short port)
        : mUniqueName(uniqueName), mPath(path), mIfaceName(iface),
        mMember(member), mSignature(sig), mDeviceId(deviceId), mAppId(appId), mPort(port)
    { };

    virtual ~RuleInfo() { };

    void setSenderInfo(qcc::String deviceId, qcc::String appId) {
        mDeviceId = deviceId;
        mAppId = appId;
    }

    virtual qcc::String toString() {
        qcc::String ret = "";
        ret.append(mUniqueName);
        ret.append(",");
        ret.append(mPath);
        ret.append(",");
        ret.append(mIfaceName);
        ret.append(",");
        ret.append(mMember);
        ret.append(",");
        ret.append(mSignature);
        ret.append(",");
        ret.append(mDeviceId);
        ret.append(",");
        ret.append(mAppId);
        ret.append(",");
        char temp[16];
        sprintf(temp, "%d", mPort);
        ret.append(temp);
        return ret;
    }

//private:
    qcc::String mUniqueName;
    qcc::String mPath;
    qcc::String mIfaceName;
    qcc::String mMember;
    qcc::String mSignature;
    qcc::String mDeviceId;
    qcc::String mAppId;
    short mPort;
};

#endif //_RULE_INFO_

