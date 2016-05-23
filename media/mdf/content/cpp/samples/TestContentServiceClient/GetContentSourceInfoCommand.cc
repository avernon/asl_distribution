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

#include "GetContentSourceInfoCommand.h"
#include "CommandUtil.h"
#include <vector>
#include <MsgArg.h>

namespace mdf {

using namespace std;
using namespace qcc;

GetContentSourceInfoCommand::GetContentSourceInfoCommand(ContentSourceTracker* contentSourceTracker) :
    m_CSTracker(contentSourceTracker)
{

}

bool GetContentSourceInfoCommand::Execute()
{
    bool showMenu = true;
    ContentSource* cs = m_CSTracker->GetSelectedContentSource();
    if (!cs) {
        cout << "You must select a content source to call GetContentSourceInfo!\n" << endl;
        return true;
    }

    const MsgArg contentArg = cs->GetContentSourceInfo();
    size_t count;
    MsgArg* info;
    QStatus err = contentArg.Get("a{sv}", &count, &info);
    if (err == ER_OK) {
        for (int i = 0; i < count; i++) {
            char* name;
            MsgArg* valueArg;
            err = info[i].Get("{sv}", &name, &valueArg);

            if (err == ER_OK) {
                if (name != NULL) {
                    String nameString(name);
                    if (nameString.compare("mimeTypes") == 0) {
                        size_t numberOfMimetypes;
                        MsgArg* mimes;
                        err = valueArg->Get("as", &numberOfMimetypes, &mimes);
                        if (err == ER_OK) {
                            cout << "\n******************** Supported MIMETypes ********************" << endl;
                            for (int j = 0; j < numberOfMimetypes; j++) {
                                cout << mimes[j].v_string.str << endl;
                            }
                            cout << "******************** END Supported MIMETypes ****************" << endl;
                        } else {
                            cout << "\nError extracting mime types" << endl;
                        }
                    } else if (nameString.compare("transports") == 0) {
                        size_t numberOfTransports;
                        MsgArg* transports;
                        err = valueArg->Get("aq", &numberOfTransports, &transports);
                        if (err == ER_OK) {
                            cout << "\n******************** Supported Transports ********************" << endl;
                            for (int j = 0; j < numberOfTransports; j++) {
                                cout << transports[j].v_uint16 << endl;
                            }
                            cout << "******************** END Supported Transports ****************" << endl;
                        } else {
                            cout << "\nError extracting transports" << endl;
                        }
                    } else {
                        cout << "Unknown value for " << nameString << endl;
                    }
                } else {
                    cout << "The name of the property at " << i << " was null." << endl;
                }
            } else {
                cout << "There was a problem getting the content info for " << i << endl;
            }
        }
    } else {
        cout << "\nError opening the content info object: " << err << endl;
    }

    return showMenu;
}

const char* GetContentSourceInfoCommand::GetMenuText()
{
    return "GetContentSourceInfo";
}
}

