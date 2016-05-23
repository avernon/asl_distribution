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

#include <iostream>
#include <map>
#include "Menu.h"
#include "Command.h"
#include "ExitCommand.h"
#include "DisplayDevicesCommand.h"
#include "SelectContentSource.h"
#include "BrowseCommand.h"
#include "AdvancedBrowseCommand.h"
#include "SearchCommand.h"
#include "GetItemCommand.h"
#include "GetSortableFieldsCommand.h"
#include "GetContentSourceInfoCommand.h"

namespace mdf {

using namespace std;

Menu::Menu(ContentSourceTracker* csTracker) : m_CSTracker(csTracker)
{
    int i = 1;
    DisplayDevicesCommand* displayDevices = new DisplayDevicesCommand(m_CSTracker);
    m_Commands.insert(std::pair<int, Command*>(i++, displayDevices));

    SelectContentSource* selectContentSource = new SelectContentSource(m_CSTracker);
    m_Commands.insert(std::pair<int, Command*>(i++, selectContentSource));

    BrowseCommand* browseCommand = new BrowseCommand(m_CSTracker);
    m_Commands.insert(std::pair<int, Command*>(i++, browseCommand));

    AdvancedBrowseCommand* advancedBrowseCommand = new AdvancedBrowseCommand(m_CSTracker);
    m_Commands.insert(std::pair<int, Command*>(i++, advancedBrowseCommand));

    SearchCommand* searchCommand = new SearchCommand(m_CSTracker);
    m_Commands.insert(std::pair<int, Command*>(i++, searchCommand));

    GetItemCommand* getItemCommand = new GetItemCommand(m_CSTracker);
    m_Commands.insert(std::pair<int, Command*>(i++, getItemCommand));

    GetSortableFieldsCommand* getSortableFieldsCommand = new GetSortableFieldsCommand(m_CSTracker);
    m_Commands.insert(std::pair<int, Command*>(i++, getSortableFieldsCommand));

    GetContentSourceInfoCommand* getContentSourceInfoCommand = new GetContentSourceInfoCommand(m_CSTracker);
    m_Commands.insert(std::pair<int, Command*>(i++, getContentSourceInfoCommand));

    ExitCommand* exitCommand = new ExitCommand();
    m_Commands.insert(std::pair<int, Command*>(i++, exitCommand));
}

Menu::~Menu()
{
    for (std::map<int, Command*>::iterator iter = m_Commands.begin(); iter != m_Commands.end(); ++iter) {
        delete (*iter).second;
    }
    m_Commands.clear();
}

bool Menu::DisplayMenu()
{
    bool showMenu = true;
    int myChoice = 0;

    const ContentSource* cs = m_CSTracker->GetSelectedContentSource();

    cout << "\n******************** Main Menu ********************" << std::endl;
    cout << "Selected ContentSource: " << (cs ?  cs->GetDisplayName() : "No ContentSource found.") << "\n" << std::endl;
    int maxMenuOption;
    for (std::map<int, Command*>::iterator iter = m_Commands.begin(); iter != m_Commands.end(); ++iter) {
        maxMenuOption = (*iter).first;
        cout << "(" << maxMenuOption << "): " << (*iter).second->GetMenuText() << endl;
    }

    cin >> myChoice;
    if (cin.fail()) {
        //Someone did not enter a number!
        myChoice = 999;
        cin.clear();
        cin.ignore();
    }

    if (myChoice > maxMenuOption) {
        cout << "ERROR! You have selected an invalid choice." << endl;
    } else {
        showMenu = GetCommand(myChoice)->Execute();
    }

    return showMenu;
}

Command* Menu::GetCommand(int key)
{
    Command* value;
    for (std::map<int, Command*>::iterator iter = m_Commands.find(key); iter != m_Commands.end(); ++iter) {
        value = (*iter).second;
        break;
    }
    return value;
}
}

