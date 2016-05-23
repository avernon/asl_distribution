/**
 * @file HTC layer function declarations
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

#ifndef AJ_WSL_HTC_H_
#define AJ_WSL_HTC_H_

#include <ajtcl/aj_target.h>
#include <ajtcl/aj_buf.h>
#include <ajtcl/aj_debug.h>

#include "aj_wsl_target.h"
#include "aj_wsl_spi_constants.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 1)


void AJ_WSL_HTC_ModuleInit(void);
uint8_t AJ_WSL_IsDriverStarted(void);
/*
 *  Endpoints can be in any of these states
 */
typedef enum _AJ_WSL_HTC_STATE {
    AJ_WSL_HTC_UNINITIALIZED,
    AJ_WSL_HTC_UNINITIALIZED_RECV_READY,
    AJ_WSL_HTC_UNINITIALIZED_SENT_CRED_REQ,
    AJ_WSL_HTC_INITIALIZED,
    AJ_WSL_HTC_NO_CREDS,     /**< no credits available for this endpoint */
    AJ_WSL_HTC_CREDS         /**< okay to send packets to the target */
} AJ_WSL_HTC_STATE;

typedef struct _WSL_HTC_EP {
    uint8_t endpointId;
    uint16_t serviceId;
    uint16_t txCredits;
    AJ_WSL_HTC_STATE state;
} WSL_HTC_EP;

typedef struct _WSL_HTC_CONTEXT {
    uint16_t creditCount;
    uint16_t creditSize;
    uint8_t maxEndpoints;
    uint8_t HTCVersion;
    uint8_t maxMessagesPerBundle;
    WSL_HTC_EP endpoints[AJ_WSL_HTC_ENDPOINT_COUNT_MAX];
    uint8_t started;
} AJ_WSL_HTC_CONTEXT;




/*
 * HTC header flags
 */
#define AJ_WSL_HTC_NEED_CREDIT_UPDATE    (1 << 0)
#define AJ_WSL_HTC_RECV_TRAILER_PRESENT  (1 << 1)

void AJ_WSL_HTC_ProcessInterruptCause(void);
void AJ_WSL_HTC_ProcessIncoming(void);

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* AJ_WSL_HTC_H_ */
