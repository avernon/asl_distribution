/**
 * @file
 * Class for encapsulating Session option information.
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
#include <qcc/Util.h>
#include <alljoyn/MsgArg.h>

#include <assert.h>

#include "SessionInternal.h"

#define QCC_MODULE "ALLJOYN"

using namespace std;

namespace ajn {

/** SessionOpts key values */
#define SESSIONOPTS_TRAFFIC     "traf"
#define SESSIONOPTS_ISMULTICAST "multi"
#define SESSIONOPTS_PROXIMITY   "prox"
#define SESSIONOPTS_TRANSPORTS  "trans"
#define SESSIONOPTS_NAMETRANSFER  "names"

bool SessionOpts::IsCompatible(const SessionOpts& other) const
{
    /* No overlapping transports means opts are not compatible */
    if (0 == (transports & other.transports)) {
        return false;
    }

    /* Not overlapping traffic types means opts are not compatible */
    if (0 == (traffic & other.traffic)) {
        return false;
    }

    /* Not overlapping proximities means opts are not compatible */
    if (0 == (proximity & other.proximity)) {
        return false;
    }

    /* Note that isMultipoint is not a condition of compatibility */

    return true;
}

qcc::String SessionOpts::ToString() const
{
    qcc::String str = "traffic=";
    switch (traffic) {
    case TRAFFIC_MESSAGES:
        str.append("TRAFFIC_MESSAGES");
        break;

    case TRAFFIC_RAW_UNRELIABLE:
        str.append("TRAFFIC_RAW_UNRELIABLE");
        break;

    case TRAFFIC_RAW_RELIABLE:
        str.append("TRAFFIC_RAW_RELIABLE");
        break;

    default:
        str.append("unknown");
        break;
    }

    str.append(", isMultipoint=");
    str.append(isMultipoint ? "true" : "false");

    str.append(", proximity=");
    switch (proximity) {
    case PROXIMITY_ANY:
        str.append("PROXIMITY_ANY");
        break;

    case PROXIMITY_PHYSICAL:
        str.append("PROXIMITY_PHYSICAL");
        break;

    case PROXIMITY_NETWORK:
        str.append("PROXIMITY_NETWORK");
        break;

    default:
        str.append("unknown");
        break;
    }

    str.append(", nameTransfer=");
    switch (nameTransfer) {
    case ALL_NAMES:
        str.append("ALL_NAMES");
        break;

    case SLS_NAMES:
        str.append("SLS_NAMES");
        break;

    case P2P_NAMES:
        str.append("P2P_NAMES");
        break;

    case MP_NAMES:
        str.append("MP_NAMES");
        break;

    default:
        str.append("unknown");
        break;
    }

    str.append(", transports=%X", transports);
    return str;
}
void SessionOpts::SetAllNames()
{
    nameTransfer = ALL_NAMES;
}

void SessionOpts::SetSessionNames()
{
    nameTransfer = (isMultipoint ? MP_NAMES : P2P_NAMES);
}

bool SessionOpts::IsAllNames() const
{
    return nameTransfer == ALL_NAMES;
}

bool SessionOpts::IsSessionNames() const
{
    return (nameTransfer == P2P_NAMES) || (nameTransfer == MP_NAMES);
}

QStatus GetSessionOpts(const MsgArg& msgArg, SessionOpts& opts)
{
    const MsgArg* dictArray;
    size_t numDictEntries;
    QStatus status = msgArg.Get("a{sv}", &numDictEntries, &dictArray);
    if (status == ER_OK) {
        for (size_t n = 0; n < numDictEntries; ++n) {
            const char* key = dictArray[n].v_dictEntry.key->v_string.str;
            const MsgArg* val = dictArray[n].v_dictEntry.val->v_variant.val;

            dictArray[n].Get("{sv}", &key, &val);
            if (::strcmp(SESSIONOPTS_TRAFFIC, key) == 0) {
                uint8_t tmp;
                val->Get("y", &tmp);
                opts.traffic = static_cast<SessionOpts::TrafficType>(tmp);
            } else if (::strcmp(SESSIONOPTS_ISMULTICAST, key) == 0) {
                val->Get("b", &opts.isMultipoint);
            } else if (::strcmp(SESSIONOPTS_PROXIMITY, key) == 0) {
                val->Get("y", &opts.proximity);
            } else if (::strcmp(SESSIONOPTS_TRANSPORTS, key) == 0) {
                val->Get("q", &opts.transports);
            } else if (::strcmp(SESSIONOPTS_NAMETRANSFER, key) == 0) {
                uint8_t tmp;
                val->Get("y", &tmp);
                opts.nameTransfer = static_cast<SessionOpts::NameTransferType>(tmp);
            }
        }
    }
    return status;
}

void SetSessionOpts(const SessionOpts& opts, MsgArg& msgArg)
{
    MsgArg trafficArg("y", opts.traffic);
    MsgArg isMultiArg("b", opts.isMultipoint);
    MsgArg proximityArg("y", opts.proximity);
    MsgArg transportsArg("q", opts.transports);
    MsgArg nameTransferArg("y", opts.nameTransfer);

    MsgArg entries[5];
    entries[0].Set("{sv}", SESSIONOPTS_TRAFFIC, &trafficArg);
    entries[1].Set("{sv}", SESSIONOPTS_ISMULTICAST, &isMultiArg);
    entries[2].Set("{sv}", SESSIONOPTS_PROXIMITY, &proximityArg);
    entries[3].Set("{sv}", SESSIONOPTS_TRANSPORTS, &transportsArg);
    entries[4].Set("{sv}", SESSIONOPTS_NAMETRANSFER, &nameTransferArg);
    QStatus status = msgArg.Set("a{sv}", ArraySize(entries), entries);
    if (status == ER_OK) {
        msgArg.Stabilize();
    } else {
        QCC_LogError(status, ("Failed to set SessionOpts message arg"));
    }

}

}

