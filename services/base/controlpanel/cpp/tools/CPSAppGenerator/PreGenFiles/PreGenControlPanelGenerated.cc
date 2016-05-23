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

#include "ControlPanelGenerated.h"
#include <alljoyn/controlpanel/LanguageSets.h>
#include <alljoyn/controlpanel/Label.h>
//INCLUDES_GO_HERE


using namespace ajn;
using namespace services;

bool ControlPanelGenerated::languageSetsDone = false;
//STATIC_DECLARATION_HERE

#define CHECK(x) if ((status = x) != ER_OK) { return status; }

void ControlPanelGenerated::PrepareLanguageSets()
{
    if (languageSetsDone) {
        return;
    }

//LANGUAGESET_CODE_HERE    languageSetsDone = true;
}

QStatus ControlPanelGenerated::PrepareWidgets(ControlPanelControllee*& controlPanelControllee)
{
    if (controlPanelControllee) {
        return ER_BAD_ARG_1;
    }

    PrepareLanguageSets();

    QStatus status = ER_OK;
    controlPanelControllee = new ControlPanelControllee();
//INITCODE_GO_HERE
    return status;
}

void ControlPanelGenerated::Shutdown()
{
//SHUTDOWN_GO_HERE
}
