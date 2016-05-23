/**
 * @file
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

/**
 * Per-module definition of the current module for debug logging.  Must be defined
 * prior to first inclusion of aj_debug.h
 */
#define AJ_MODULE CONNECT

#include <ajtcl/aj_target.h>
#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bufio.h>
#include <ajtcl/aj_msg.h>
#include <ajtcl/aj_connect.h>
#include <ajtcl/aj_introspect.h>
#include <ajtcl/aj_net.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/aj_disco.h>
#include <ajtcl/aj_std.h>
#include <ajtcl/aj_debug.h>
#include <ajtcl/aj_config.h>
#include <ajtcl/aj_creds.h>
#include <ajtcl/aj_peer.h>


/**
 * Turn on per-module debug printing by setting this variable to non-zero value
 * (usually in debugger).
 */
#ifndef NDEBUG
AJ_EXPORT uint8_t dbgCONNECT = 0;
#endif
/*
 * Protocol version of the router you have connected to
 */
static uint8_t routingProtoVersion = 0;
/*
 * Minimum accepted protocol version of a router to be connected to
 * Version 10 (14.06) allows for NGNS and untrusted connection to router
 * May be set to earlier version with AJ_SetMinProtoVersion().
 */
static uint8_t minProtoVersion = 10;

/*
 * The amount of time to wait for routing node responses during discovery.
 * May be set to a different value with AJ_SetSelectionTimeout().
 */
static uint32_t selectionTimeout = AJ_SELECTION_TIMEOUT;

static const char daemonService[] = "org.alljoyn.BusNode";

uint8_t AJ_GetMinProtoVersion()
{
    return minProtoVersion;
}
void AJ_SetMinProtoVersion(uint8_t min)
{
    minProtoVersion = min;
}

void AJ_SetSelectionTimeout(uint32_t selection)
{
    selectionTimeout = selection;
}

uint8_t AJ_GetRoutingProtoVersion(void)
{
    return routingProtoVersion;
}

AJ_Status AJ_FindBusAndConnect(AJ_BusAttachment* bus, const char* serviceName, uint32_t timeout)
{
    AJ_Status status;
    AJ_GUID localGuid;
    char guidStr[34];

    AJ_InfoPrintf(("AJ_FindBusAndConnect"));

    /*
     * Clear the bus struct
     */
    memset(bus, 0, sizeof(AJ_BusAttachment));
    /*
     * Clear stale name->GUID mappings
     */
    AJ_GUID_ClearNameMap();
    /*
     * Derive the sender name from the local GUID
     */
    AJ_GetLocalGUID(&localGuid);
    AJ_GUID_ToString(&localGuid, guidStr, sizeof(guidStr));
    guidStr[0] = ':';
    guidStr[AJ_MAX_NAME_SIZE] = 0;
    memcpy(bus->uniqueName, guidStr, AJ_MAX_NAME_SIZE + 1);
    bus->uniqueName[AJ_MAX_NAME_SIZE] = '.';
    bus->uniqueName[AJ_MAX_NAME_SIZE + 1] = '0';
    bus->uniqueName[AJ_MAX_NAME_SIZE + 2] = '\0';

    /*
     * Establish a connection to the MQTT broker
     */
    status = AJ_Connect(bus, serviceName, timeout);
    if (status != AJ_OK) {
        goto ExitConnect;
    }

ExitConnect:

    if (status != AJ_OK) {
        AJ_InfoPrintf(("AJ_FindBusAndConnect(): status=%s\n", AJ_StatusText(status)));
        AJ_Disconnect(bus);
    }
    return status;
}

void AJ_Disconnect(AJ_BusAttachment* bus)
{
    /*
     * We won't be getting any more method replies.
     */
    AJ_ReleaseReplyContexts();
    /*
     * Disconnect the network closing sockets etc.
     */
    AJ_Net_Disconnect(&bus->sock);
    /*
     * Clear auth context
     */
    AJ_ClearAuthContext();
    /*
     * Set the routing nodes proto version to zero (not connected)
     */
    routingProtoVersion = 0;
}

void AJ_InitRoutingNodeResponselist()
{
}

uint8_t AJ_IsRoutingNodeBlacklisted(AJ_Service* service)
{
    return FALSE;
}

void AJ_AddRoutingNodeToResponseList(AJ_Service* service)
{
}

uint8_t AJ_GetRoutingNodeResponseListSize()
{
    return 0;
}

void AJ_InitRoutingNodeBlacklist()
{
}
