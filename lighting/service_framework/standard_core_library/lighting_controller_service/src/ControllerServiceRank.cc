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

#ifdef LSF_BINDINGS
#include <lsf/controllerservice/ControllerServiceRank.h>
#else
#include <ControllerServiceRank.h>
#endif

#include <qcc/Debug.h>

#define QCC_MODULE "LSF_CONTROLLER_SERVICE_RANK"

namespace lsf {

OPTIONAL_NAMESPACE_CONTROLLER_SERVICE

void ControllerServiceRank::Initialize(void)
{
    QCC_DbgTrace(("%s", __func__));

    uint64_t higherOrderBits = 0, lowerOrderBits = 0;

    if (IsInitialized()) {
        QCC_DbgPrintf(("%s: Rank already initialized to %s", __func__, c_str()));
        return;
    }

    SetInitialized();

    uint64_t temp1 = 0, temp2 = 0;
    temp1 = (OEM_CS_GetMACAddress() & MAC_ADDR_BIT_MASK);
    QCC_DbgPrintf(("%s: Controller Service MAC address = %llu", __func__, temp1));
    temp2 = temp1 << BIT_SHIFT_FOR_MAC_ADDRESS;
    lowerOrderBits |= temp2;

    temp1 = 0;
    temp2 = 0;
    temp1 = CONTROLLER_SERVICE_VERSION;
    if (temp1 > MAX_CONTROLLER_SERVICE_VERSION) {
        QCC_DbgPrintf(("%s: Overriding Controller Service version invalid value %llu to 0", __func__, temp1));
        /*Setting to lowest possible value as the OEM has passed in an incorrect value*/
        temp1 = 0;
    }
    QCC_DbgPrintf(("%s: Controller Service version = %llu", __func__, temp1));
    temp2 = temp1 << BIT_SHIFT_FOR_CONTROLLER_SERVICE_VERSION;
    lowerOrderBits |= temp2;

    temp1 = 0;
    temp2 = 0;
    temp1 = OEM_CS_GetRankParam_NodeType();
    if (temp1 > ACCESS_POINT) {
        QCC_DbgPrintf(("%s: Overriding Node Type invalid value %llu to 0", __func__, temp1));
        /*Setting to lowest possible value as the OEM has passed in an incorrect value*/
        temp1 = 0;
    }
    QCC_DbgPrintf(("%s: Node Type = %llu", __func__, temp1));
    temp2 = temp1 << BIT_SHIFT_FOR_NODE_TYPE;
    lowerOrderBits |= temp2;

    temp1 = 0;
    temp2 = 0;
    temp1 = OEM_CS_GetRankParam_Power();
    if (temp1 > ALWAYS_AC_POWERED) {
        QCC_DbgPrintf(("%s: Overriding Power invalid value %llu to 0", __func__, temp1));
        /*Setting to lowest possible value as the OEM has passed in an incorrect value*/
        temp1 = 0;
    }
    QCC_DbgPrintf(("%s: Power = %llu", __func__, temp1));
    temp2 = temp1 << BIT_SHIFT_FOR_POWER;
    lowerOrderBits |= temp2;

    temp1 = 0;
    temp2 = 0;
    temp1 = OEM_CS_GetRankParam_Availability();
    if (temp1 >= OEM_CS_RANKPARAM_AVAILABILITY_LAST_VALUE) {
        QCC_DbgPrintf(("%s: Overriding Availability invalid value %llu to 0", __func__, temp1));
        /*Setting to lowest possible value as the OEM has passed in an incorrect value*/
        temp1 = 0;
    }
    QCC_DbgPrintf(("%s: Availability = %llu", __func__, temp1));
    temp2 = temp1 << BIT_SHIFT_FOR_AVAILABILITY;
    lowerOrderBits |= temp2;

    temp1 = 0;
    temp1 = OEM_CS_GetRankParam_Mobility();
    if (temp1 >= OEM_CS_RANKPARAM_MOBILITY_LAST_VALUE) {
        QCC_DbgPrintf(("%s: Overriding Mobility invalid value %llu to 0", __func__, temp1));
        /*Setting to lowest possible value as the OEM has passed in an incorrect value*/
        temp1 = 0;
    }
    QCC_DbgPrintf(("%s: Mobility = %llu", __func__, temp1));
    higherOrderBits = temp1;

    Set(higherOrderBits, lowerOrderBits);

    QCC_DbgPrintf(("%s: %s", __func__, c_str()));
}

OPTIONAL_NAMESPACE_CLOSE

}