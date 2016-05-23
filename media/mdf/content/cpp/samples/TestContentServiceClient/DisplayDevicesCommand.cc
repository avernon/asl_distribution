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

#include "DisplayDevicesCommand.h"
#include <map>

namespace mdf {

using namespace std;
using namespace qcc;

DisplayDevicesCommand::DisplayDevicesCommand(ContentSourceTracker* contentSourceTracker) :
    m_CSTracker(contentSourceTracker)
{

}

bool DisplayDevicesCommand::Execute()
{
    bool showMenu = true;
    ContentSource* cs = m_CSTracker->GetSelectedContentSource();
    String selectedID = (cs ? cs->GetID() : "");

    cout << "\n**************** Content Sources ******************" << endl;
    map<String, ContentSource*> contentSources = m_CSTracker->GetContentSources();
    for (std::map<String, ContentSource*>::iterator iter = contentSources.begin(); iter != contentSources.end(); ++iter) {
        String id = (*iter).first;
        const ContentSource* contentSource = (*iter).second;
        if (selectedID.compare(id) == 0) {
            cout << "*(" << id << ") " << contentSource->GetDisplayName() << endl;
        } else {
            cout << "(" << id << ") " << contentSource->GetDisplayName() << endl;
        }
    }
    cout << "***************************************************\n" << endl;
    return showMenu;
}

const char* DisplayDevicesCommand::GetMenuText()
{
    return "Display Devices";
}
}

