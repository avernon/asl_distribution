/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#include "CommandUtil.h"
#include <qcc/Debug.h>
#include <qcc/Log.h>
#include <limits>

#define QCC_MODULE "CommandUtil"

namespace mdf {

void CommandUtil::PrintNodes(const vector<Node*> nodes)
{
    for (int i = 0; i < nodes.size(); i++) {
        CommandUtil::PrintNode(nodes.at(i));
    }
    cout << "\n\n" << endl;
}

void CommandUtil::PrintNode(Node* node) {
    if (!node) {
        cout << "\n\nInval node submitted!\n\n" << endl;
    }

    String* props = GetProperties(node);
    cout << "[ItemId: " << node->GetItemID() <<
    ", title: " << node->GetTitle() <<
    ", type:" << node->GetTypeAsString() <<
    ", \nproperties {\n" << props->c_str() <<
    "\n}" <<
    "]" << endl;
    delete props;
}

String* CommandUtil::GetProperties(Node* node)
{
    String* resp = new String();
    size_t count;
    MsgArg* items;
    QStatus err = node->GetProperties().Get("a{sv}", &count, &items);
    if (err == ER_OK) {
        for (int i = 0; i < count; i++) {
            char* name;
            MsgArg* valueArg;
            err = items[i].Get("{sv}", &name, &valueArg);

            if (err == ER_OK) {
                if (name != NULL) {
                    String nameString(name);
                    String value;
                    if (valueArg != NULL) {
                        //TODO This may not be a string!
                        value = valueArg->v_string.str;
                    } else {
                        value = "";
                    }
                    if (i > 0) {
                        resp->append("\n");
                    }
                    resp->append(nameString);
                    resp->append("=");
                    resp->append(value);
                } else {
                    QCC_LogError(err, ("The name of the item at %d was null", i));
                }
            } else {
                QCC_LogError(err, ("There was a problem getting the item %i in the properties object", i));
            }
        }
    } else {
        QCC_LogError(err, ("There was a problem opening the properties object"));
    }

    return resp;
}

bool CommandUtil::CINValid() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}
}

