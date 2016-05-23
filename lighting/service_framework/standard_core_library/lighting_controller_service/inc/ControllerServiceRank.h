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
#ifndef LSF_CONTROLLER_SERVICE_RANK_H
#define LSF_CONTROLLER_SERVICE_RANK_H
/**
 * \defgroup ControllerService
 * ControllerService code
 */
/**
 * \ingroup ControllerService
 */
/**
 * @file
 * This file provides definitions for the ControllerServiceRank class
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

#ifdef LSF_BINDINGS
#include <lsf/controllerservice/OEM_CS_Config.h>
#else
#include <OEM_CS_Config.h>
#endif

#include <Rank.h>
#include "LSFNamespaceSpecifier.h"

namespace lsf {

OPTIONAL_NAMESPACE_CONTROLLER_SERVICE

/**
 * Bit mask for MAC address rank parameter
 */
        #define MAC_ADDR_BIT_MASK 0x0000FFFFFFFFFFFF

/**
 * Number of bit positions to left shift for MAC Address rank parameter
 */
        #define BIT_SHIFT_FOR_MAC_ADDRESS 1

/**
 * Number of bit positions to left shift for Controller Service Version rank parameter
 */
        #define BIT_SHIFT_FOR_CONTROLLER_SERVICE_VERSION 49

/**
 * Number of bit positions to left shift for Network Config rank parameter
 */
        #define BIT_SHIFT_FOR_NODE_TYPE 57

/**
 * Number of bit positions to left shift for Power rank parameter
 */
        #define BIT_SHIFT_FOR_POWER 59

/**
 * Number of bit positions to left shift for Availability rank parameter
 */
        #define BIT_SHIFT_FOR_AVAILABILITY 61

/**
 * Max value of the Controller Service version allowed in rank encoding
 */
        #define MAX_CONTROLLER_SERVICE_VERSION 255

/**
 * Controller service version
 */
        #define CONTROLLER_SERVICE_VERSION 2

class ControllerServiceRank : public Rank {
  public:
    /**
     * Initializes the rank by reading values from the firmware
     */
    void Initialize(void);


  private:

};

OPTIONAL_NAMESPACE_CLOSE

} //lsf

#endif
