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

#include "BrowseCommand.h"
#include "CommandUtil.h"

#include <qcc/Debug.h>
#include <qcc/Log.h>
#include <vector>
#include <string>

#define QCC_MODULE "BrowseCommand"

namespace mdf {
using namespace std;
using namespace qcc;

BrowseCommand::BrowseCommand(ContentSourceTracker*contentSourceTracker) : m_CSTracker(contentSourceTracker) {
}

bool BrowseCommand::Execute() {

    const ContentSource* cs = m_CSTracker->GetSelectedContentSource();
    if (!cs) {
        cout << "You must select a content source to browse it!\n" << endl;
        return true;
    }

    //Let's do the initial browse for the user
    MsgArg* arg = new MsgArg();

    std::vector<SortBy> listTosortBy;
    SortBy sortA;
    sortA.propertyToSortBy = "id";
    sortA.order = 0;
    listTosortBy.push_back(sortA);

    const QueryResponse* resp = cs->Browse("0", *arg, 0, 100, listTosortBy);
    if (resp != NULL) {
        const vector<Node*> nodes = resp->GetItems();
        cout << "\nBrowse returned " << nodes.size() << " items.\n" << endl;
        CommandUtil::PrintNodes(nodes);
        bool displayMenu = true;
        while (displayMenu) {
            cout << "Please enter the itemID of the node you want to browse into or 0 to exit:" << endl;
            string input;
            cin >> input;
            if (cin.fail()) {
                cin.clear();
                cin.ignore();
                cout << "Invalid ID entered!" << endl;
            } else {
                if (input.compare("0") == 0) {
                    displayMenu = false;
                } else {
                    String id(input.c_str());
                    resp = cs->Browse(id, *arg, 0, 100, listTosortBy);
                    if (resp != NULL) {
                        cout << "\nBrowse returned " << nodes.size() << " items.\n" << endl;
                        CommandUtil::PrintNodes(nodes);
                    } else {
                        cout << "\nBrowse returned NULL!\n" << endl;
                    }
                }
            }
        }

        delete resp;
        cout << "\n\n" << endl;
    } else {
        cout << "Browse returned NULL!\n" << endl;
    }

    if (arg) {
        delete arg;
    }

    return true;
}

const char* BrowseCommand::GetMenuText() {
    return "Browse";
}
}


