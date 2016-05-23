/******************************************************************************
 * Copyright (c) AllSeen Alliance. All rights reserved.
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
 *
 ******************************************************************************/

#ifndef LSF_JNI_XCONTROLLERSERVICE_H_
#define LSF_JNI_XCONTROLLERSERVICE_H_

#include <jni.h>

#include "lsf/controllerservice/OEM_CS_Config.h"

using namespace lsf::controllerservice;

namespace lsf {

class XControllerService {
public:
    static XControllerService* getActive() { return cActive; }

    XControllerService(jobject jobj);
    virtual ~XControllerService();

    // Methods called from Java
    void Start(const LSFString &keyStorePath);
    void Stop();
    void LightingReset();
    void FactoryReset();

    void SendNetworkConnected();
    void SendNetworkDisconnected();
    jstring GetName();
    jboolean IsLeader();

    // Methods calling into Java
    void PopulateDefaultProperties(const AboutData *aboutData);
    LSFString GetMacAddress(const LSFString &defaultMacAddress);
    bool IsNetworkConnected(const bool &defaultIsNetworkConnected);
    OEM_CS_RankParam_Power GetRankPower(const OEM_CS_RankParam_Power &defaultRankPower);
    OEM_CS_RankParam_Mobility GetRankMobility(const OEM_CS_RankParam_Mobility &defaultRankMobility);
    OEM_CS_RankParam_Availability GetRankAvailability(const OEM_CS_RankParam_Availability &defaultRankAvailability);
    OEM_CS_RankParam_NodeType GetRankNodeType(const OEM_CS_RankParam_NodeType &defaultRankNodeType);

    OEM_CS_NetworkCallback* cNetworkCallback;
protected:
    static XControllerService* cActive;

    jweak jdelegate;
 };

} /* namespace lsf */
#endif /* LSF_JNI_XCONTROLLERSERVICE_H_ */
