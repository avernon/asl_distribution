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

#include "GetItemCommand.h"
#include "CommandUtil.h"

namespace mdf {

using namespace std;
using namespace qcc;

GetItemCommand::GetItemCommand(ContentSourceTracker* contentSourceTracker) :
    m_CSTracker(contentSourceTracker)
{

}

bool GetItemCommand::Execute()
{
    bool showMenu = true;
    ContentSource* cs = m_CSTracker->GetSelectedContentSource();
    if (!cs) {
        cout << "You must select a content source to call GetItem!\n" << endl;
        return true;
    }

    bool displayMenu = true;
    while (displayMenu) {
        cout << "Please enter the itemID of the node you want to fetch or 0 to exit:" << endl;
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
                Node* node = cs->GetItem(id);
                if (node != NULL) {
                    cout << "\n" << endl;
                    CommandUtil::PrintNode(node);
                    cout << "\n" << endl;
                    delete node;
                } else {
                    cout << "\nGetItem returned NULL!\n" << endl;
                }
            }
        }
    }

    return showMenu;
}

const char* GetItemCommand::GetMenuText()
{
    return "GetItem";
}
}

