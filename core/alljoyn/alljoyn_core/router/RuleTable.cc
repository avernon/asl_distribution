/**
 * @file
 * MsgRouter is responsible for taking inbound messages and routing them
 * to an appropriate set of endpoints.
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

#include <algorithm>
#include <cstring>

#include "BusUtil.h"
#include "RuleTable.h"

#include <qcc/Debug.h>
#include <qcc/String.h>
#include <qcc/StringUtil.h>
#include <alljoyn/Message.h>

#define QCC_MODULE "ALLJOYN"

using namespace std;
using namespace qcc;

namespace ajn {

Rule::Rule(const char* ruleSpec, QStatus* outStatus) : type(MESSAGE_INVALID), sessionless(SESSIONLESS_NOT_SPECIFIED)
{
    QStatus status = ER_OK;
    const char* pos = ruleSpec;
    const char* finalPos = pos + strlen(ruleSpec);

    while (pos < finalPos) {
        const char* endPos = strchr(pos, ',');
        if (NULL == endPos) {
            endPos = finalPos;
        }
        const char* eqPos = strchr(pos, '=');
        if ((NULL == eqPos) || (eqPos >= endPos)) {
            status = ER_FAIL;
            QCC_LogError(status, ("Premature end of ruleSpec \"%s\"", ruleSpec));
            break;
        }
        ++eqPos;
        const char* begQuotePos = strchr(eqPos, '\'');
        const char* endQuotePos = NULL;
        if (begQuotePos && (++begQuotePos < finalPos)) {
            endQuotePos = strchr(begQuotePos, '\'');
        }
        if (!endQuotePos) {
            status = ER_FAIL;
            QCC_LogError(status, ("Quote mismatch in ruleSpec \"%s\"", ruleSpec));
            break;
        }
        if (0 == strncmp("type", pos, 4)) {
            if (0 == strncmp("signal", begQuotePos, endQuotePos - begQuotePos)) {
                type = MESSAGE_SIGNAL;
            } else if (0 == strncmp("method_call", begQuotePos, endQuotePos - begQuotePos)) {
                type = MESSAGE_METHOD_CALL;
            } else if (0 == strncmp("method_return", begQuotePos, endQuotePos - begQuotePos)) {
                type = MESSAGE_METHOD_RET;
            } else if (0 == strncmp("error", begQuotePos, endQuotePos - begQuotePos)) {
                type = MESSAGE_ERROR;
            } else {
                status = ER_FAIL;
                QCC_LogError(status, ("Invalid type value in ruleSpec \"%s\"", ruleSpec));
                break;
            }
        } else if (0 == strncmp("sender", pos, 6)) {
            sender = qcc::String(begQuotePos, endQuotePos - begQuotePos);
        } else if (0 == strncmp("interface", pos, 9)) {
            iface = qcc::String(begQuotePos, endQuotePos - begQuotePos);
        } else if (0 == strncmp("member", pos, 6)) {
            member = qcc::String(begQuotePos, endQuotePos - begQuotePos);
        } else if (0 == strncmp("path", pos, 4)) {
            path = qcc::String(begQuotePos, endQuotePos - begQuotePos);
        } else if (0 == strncmp("destination", pos, 11)) {
            destination = qcc::String(begQuotePos, endQuotePos - begQuotePos);
        } else if (0 == strncmp("sessionless", pos, 11)) {
            sessionless = ((begQuotePos[0] == 't') || (begQuotePos[0] == 'T')) ? SESSIONLESS_TRUE : SESSIONLESS_FALSE;
        } else if (0 == strncmp("arg", pos, 3)) {
            /*
             * Some explanation of the indices used here:
             *   arg10='foo'
             *   ^  ^ ^^
             *   |  | ||
             *   |  | |+-- eqPos (eqPos is incremented one past the '=' above)
             *   |  | +-- eqPos - 1
             *   |  +-- pos + 3
             *   +-- pos
             * So (pos + 3) is the start of the numeric portion, and
             * (eqPos - 1) - (pos + 3) is the length of number portion.
             */
            uint32_t argIndex = qcc::StringToU32(qcc::String(pos + 3, (eqPos - 1) - (pos + 3)), 10, 64);
            if (argIndex < 64) {
                if (endQuotePos > begQuotePos) {
                    args[argIndex] = qcc::String(begQuotePos, endQuotePos - begQuotePos);
                } else {
                    args[argIndex] = qcc::String();
                }
            } else {
                status = ER_FAIL;
                QCC_LogError(status, ("Invalid argument index in ruleSpec \"%s\"", ruleSpec));
                break;
            }
        } else if (0 == strncmp("implements", pos, 10)) {
            implements.insert(qcc::String(begQuotePos, endQuotePos - begQuotePos));
        } else {
            status = ER_FAIL;
            QCC_LogError(status, ("Invalid key in ruleSpec \"%s\"", ruleSpec));
            break;
        }
        pos = endPos + 1;
    }
    if (outStatus) {
        *outStatus = status;
    }
}

bool Rule::IsMatch(Message& msg) const
{
    /* The fields of a rule (if specified) are logically anded together */
    if ((type != MESSAGE_INVALID) && (type != msg->GetType())) {
        return false;
    }
    if (!sender.empty() && (0 != strcmp(sender.c_str(), msg->GetSender()))) {
        return false;
    }
    if (!iface.empty() && (0 != strcmp(iface.c_str(), msg->GetInterface()))) {
        return false;
    }
    if (!member.empty() && (0 != strcmp(member.c_str(), msg->GetMemberName()))) {
        return false;
    }
    if (!path.empty() && (0 != strcmp(path.c_str(), msg->GetObjectPath()))) {
        return false;
    }
    if (!destination.empty() && (0 != strcmp(destination.c_str(), msg->GetDestination()))) {
        return false;
    }
    if (!args.empty()) {
        /*
         * Clone the message since this message is unmarshalled by the
         * LocalEndpoint too and the process of unmarshalling is not
         * thread-safe.
         */
        Message clone = Message(msg, true);
        QStatus status = clone->UnmarshalArgs(clone->GetSignature());
        if (status != ER_OK) {
            return false;
        }
        for (map<uint32_t, String>::const_iterator it = args.begin(); it != args.end(); ++it) {
            const MsgArg* arg = clone->GetArg(it->first);
            if (!arg) {
                return false;
            }
            if (ALLJOYN_STRING != arg->typeId) {
                return false;
            }
            if (it->second != arg->v_string.str) {
                return false;
            }
        }
    }
    if (!implements.empty()) {
        if (strcmp(msg->GetInterface(), "org.alljoyn.About") || strcmp(msg->GetMemberName(), "Announce")) {
            return false;
        }
        /*
         * Clone the message since this message is unmarshalled by the
         * LocalEndpoint too and the process of unmarshalling is not
         * thread-safe.
         */
        Message clone = Message(msg, true);
        QStatus status = clone->UnmarshalArgs("qqa(oas)a{sv}");
        if (status != ER_OK) {
            return false;
        }

        const MsgArg* arg = clone->GetArg(2);
        if (!arg) {
            return false;
        }
        size_t numObjectDescriptions;
        MsgArg* objectDescriptions;
        status = arg->Get("a(oas)", &numObjectDescriptions, &objectDescriptions);
        if (status != ER_OK) {
            return false;
        }
        set<String> interfaces;
        for (size_t ob = 0; ob < numObjectDescriptions; ++ob) {
            char* path;
            size_t numIntfs;
            MsgArg* intfs;
            status = objectDescriptions[ob].Get("(oas)", &path, &numIntfs, &intfs);
            if (status != ER_OK) {
                return false;
            }
            for (size_t in = 0; in < numIntfs; ++in) {
                char* intf;
                status = intfs[in].Get("s", &intf);
                if (status != ER_OK) {
                    return false;
                }
                interfaces.insert(intf);
            }
        }
        size_t numMatches = 0;
        for (set<String>::const_iterator im = implements.begin(); im != implements.end(); ++im) {
            for (set<String>::const_iterator in = interfaces.begin(); in != interfaces.end(); ++in) {
                if (WildcardMatch(*in, *im) == 0) {
                    ++numMatches;
                    break;
                }
            }
        }
        if (numMatches != implements.size()) {
            return false;
        }
    }
    if (((sessionless == SESSIONLESS_TRUE) && !msg->IsSessionless()) ||
        ((sessionless == SESSIONLESS_FALSE) && msg->IsSessionless())) {
        return false;
    }

    return true;
}

qcc::String Rule::ToString() const
{
    const char* typeStr[] = { NULL, "method_call", "method_return", "error", "signal" };

    String rule;
    if (type != MESSAGE_INVALID) {
        rule += String("type='") + typeStr[type] + "'";
    }
    if (!sender.empty()) {
        if (!rule.empty()) {
            rule += ",";
        }
        rule += "sender='" + sender + "'";
    }
    if (!iface.empty()) {
        if (!rule.empty()) {
            rule += ",";
        }
        rule += "interface='" + iface + "'";
    }
    if (!member.empty()) {
        if (!rule.empty()) {
            rule += ",";
        }
        rule += "member='" + member + "'";
    }
    if (!path.empty()) {
        if (!rule.empty()) {
            rule += ",";
        }
        rule += "path='" + path + "'";
    }
    if (!destination.empty()) {
        if (!rule.empty()) {
            rule += ",";
        }
        rule += "destination='" + destination + "'";
    }
    for (map<uint32_t, String>::const_iterator it = args.begin(); it != args.end(); ++it) {
        if (!rule.empty()) {
            rule += ",";
        }
        rule += "arg" + U32ToString(it->first) + "='" + it->second + "'";
    }
    for (set<String>::const_iterator it = implements.begin(); it != implements.end(); ++it) {
        if (!rule.empty()) {
            rule += ",";
        }
        rule += "implements='" + *it + "'";
    }
    if (sessionless != SESSIONLESS_NOT_SPECIFIED) {
        if (!rule.empty()) {
            rule += ",";
        }
        rule += String("sessionless='") + (sessionless ? "t" : "f") + "'";
    }
    return rule;
}

QStatus RuleTable::AddRule(BusEndpoint& endpoint, const Rule& rule)
{
    QCC_DbgPrintf(("AddRule for endpoint %s\n  %s", endpoint->GetUniqueName().c_str(), rule.ToString().c_str()));
    lock.Lock(MUTEX_CONTEXT);
    rules.insert(std::pair<BusEndpoint, Rule>(endpoint, rule));
    lock.Unlock(MUTEX_CONTEXT);
    return ER_OK;
}

QStatus RuleTable::RemoveRule(BusEndpoint& endpoint, Rule& rule)
{
    QStatus status = ER_BUS_MATCH_RULE_NOT_FOUND;
    lock.Lock(MUTEX_CONTEXT);
    std::pair<RuleIterator, RuleIterator> range = rules.equal_range(endpoint);
    while (range.first != range.second) {
        if (range.first->second == rule) {
            const RuleIterator begin = range.first;
            const RuleIterator end = ++range.first;
            rules.erase(begin, end);
            status = ER_OK;
            break;
        }
        ++range.first;
    }
    lock.Unlock(MUTEX_CONTEXT);
    return status;
}

QStatus RuleTable::RemoveAllRules(BusEndpoint& endpoint)
{
    lock.Lock(MUTEX_CONTEXT);
    std::pair<RuleIterator, RuleIterator> range = rules.equal_range(endpoint);
    if (range.first != rules.end()) {
        rules.erase(range.first, range.second);
    }
    lock.Unlock(MUTEX_CONTEXT);
    return ER_OK;
}

bool RuleTable::OkToSend(const Message& msg, BusEndpoint& endpoint) const
{
    bool match = false;
    lock.Lock(MUTEX_CONTEXT);
    pair<RuleConstIterator, RuleConstIterator> range = rules.equal_range(endpoint);
    for (RuleConstIterator it = range.first; !match && (it != range.second); ++it) {
        match = it->second.IsMatch(msg);

        /*
         * This little hack is to make DaemonRouter::PushMessage() work with the
         * same behavior as it did previously which is that sessionless messages
         * that match rules for the endpoint that include sessionless='t' as
         * part of the rule will not be delivered by DaemonRouter::PushMessage()
         * directly, but rather the message will be delivered via
         * SessionlessObj.  It exists in this function so that DaemonRouter does
         * not need to know the internal gory details of Rules or the RuleTable.
         *
         * This hack imposes a hidden direct coupling with
         * DaemonRouter::PushMessage() that needs to be cleaned up at some point
         * in the future.  This will likely require that the interaction between
         * SessionlessObj and DaemonRouter change.
         */
        if (match && (it->second.sessionless == Rule::SESSIONLESS_TRUE)) {
            match = false;
            break;
        }
    }
    lock.Unlock(MUTEX_CONTEXT);
    return match;
}


}
