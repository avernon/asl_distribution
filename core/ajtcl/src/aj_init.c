/**
 * @file
 */
/******************************************************************************
 * Copyright (c) 2012, 2014-2015, AllSeen Alliance. All rights reserved.
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

/**
 * Per-module definition of the current module for debug logging.  Must be defined
 * prior to first inclusion of aj_debug.h
 */
#define AJ_MODULE INIT

#include <ajtcl/aj_target.h>
#include <ajtcl/aj_init.h>
#include <ajtcl/aj_nvram.h>
#include <ajtcl/aj_creds.h>
#include <ajtcl/aj_guid.h>
#include <ajtcl/aj_crypto.h>
#include <ajtcl/aj_debug.h>
#include <ajtcl/aj_connect.h>

/**
 * Turn on per-module debug printing by setting this variable to non-zero value
 * (usually in debugger).
 */
#ifndef NDEBUG
uint8_t dbgINIT = 0;
#endif

static uint8_t initialized = FALSE;

void AJ_Initialize(void)
{
    AJ_GUID localGuid;
    if (!initialized) {
        initialized = TRUE;
        AJ_NVRAM_Init();
        /*
         * This will seed the random number generator
         */
        AJ_RandBytes(NULL, 0);
        /*
         * This will initialize credentials if needed
         */
        AJ_GetLocalGUID(&localGuid);

        /*
         * Clear the Routing Node black list
         */
        AJ_InitRoutingNodeBlacklist();

        AJ_InitRoutingNodeResponselist();
    }
}
