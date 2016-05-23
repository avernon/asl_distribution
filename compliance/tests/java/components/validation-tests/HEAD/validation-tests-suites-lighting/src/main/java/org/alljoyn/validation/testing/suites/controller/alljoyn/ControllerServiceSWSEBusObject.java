/*******************************************************************************
*  Copyright (c) AllSeen Alliance. All rights reserved.
*
*     Contributed by Qualcomm Connected Experiences, Inc.,
*     with authorization from the AllSeen Alliance, Inc.
*     
*     Licensed under the Apache License, Version 2.0 (the "License");
*     you may not use this file except in compliance with the License.
*     You may obtain a copy of the License at
*     
*         http://www.apache.org/licenses/LICENSE-2.0
*     
*     Unless required by applicable law or agreed to in writing, software
*     distributed under the License is distributed on an "AS IS" BASIS,
*     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*     See the License for the specific language governing permissions and
*     limitations under the License.
*     
*     Pursuant to Section 1 of the License, the work of authorship constituting
*     a Work and any Contribution incorporated in the Work shall mean only that
*     Contributor's code submissions authored by that Contributor.  Any rights
*     granted under the License are conditioned upon acceptance of these
*     clarifications.
*******************************************************************************/
package org.alljoyn.validation.testing.suites.controller.alljoyn;

import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusProperty;

public class ControllerServiceSWSEBusObject implements BusObject, ControllerServiceSWSEBusInterface
{
    @Override
    @BusProperty(signature="u")
    public int getVersion() throws BusException
    {
        return 0;
    }

    @BusMethod(signature= "asss" , replySignature = "us")
    public SceneWithSceneElementsValues CreateSceneWithSceneElements(String[] sceneElementIDs, String sceneName, String language) throws BusException
    {
        return null;
    }

    @BusMethod(signature= "sas" , replySignature = "us")
    public SceneWithSceneElementsValues UpdateSceneWithSceneElements(String sceneID, String[] SceneElementIDs) throws BusException
    {
        return null;
    }

    @BusMethod(signature= "s" , replySignature = "usas")
    public GetSceneWithSceneElementsValues GetSceneWithSceneElements(String sceneID) throws BusException
    {
        return null;
    }
}
