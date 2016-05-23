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

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.bus.annotation.BusProperty;

public class ControllerServiceSceneElementBusObject  implements BusObject, ControllerServiceSceneElementBusInterface
{
    @Override
    @BusProperty(signature="u")
    public int getVersion() throws BusException
    {
        return 0;
    }

    @Override
    @BusMethod(replySignature = "uas")
    public GetAllSceneElementIDsValues GetAllSceneElementIDs() throws BusException
    {
        return null;
    }

    @Override
    @BusMethod(signature = "ss", replySignature = "usss")
    public GetSceneElementNameValues GetSceneElementName(String SceneElementID, String language) throws BusException
    {
        return null;
    }

    @Override
    @BusMethod(signature = "sss", replySignature = "uss")
    public SetSceneElementNameValues SetSceneElementName(String SceneElementID, String SceneElementName, String language) throws BusException
    {
        return null;
    }

    @Override
    @BusMethod(signature = "sasasss", replySignature = "us")
    public SceneElementValues CreateSceneElement(String[] lampList, String[] lampGroupList, String effectID, String SceneElementName, String language) throws BusException
    {
        return null;
    }

    @Override
    @BusMethod(signature = "sasass", replySignature = "us")
    public SceneElementValues UpdateSceneElement(String sceneElementID, String[] lampList, String[] lampGroupList, String effectID) throws BusException
    {
        return null;
    }

    @Override
    @BusMethod(signature = "s", replySignature = "us")
    public SceneElementValues DeleteSceneElement(String SceneElementID) throws BusException
    {
        return null;
    }

    @Override
    @BusMethod(signature = "s", replySignature = "usasass")
    public GetSceneElementValues GetSceneElement(String SceneElementID) throws BusException
    {
        return null;
    }

    @Override
    @BusMethod(signature = "sas", replySignature = "us")
    public SceneElementValues ApplySceneElement(String SceneElementIDs) throws BusException
    {
        return null;
    }

    @BusSignal()
    public void SceneElementsNameChanged(String[] SceneElementIDs) throws BusException
    {
    }

    @BusSignal()
    public void SceneElementsCreated(String[] SceneElementIDs) throws BusException
    {
    }

    @BusSignal()
    public void SceneElementsUpdated(String[] SceneElementIDs) throws BusException
    {
    }

    @BusSignal()
    public void SceneElementsDeleted(String[] SceneElementIDs) throws BusException
    {
    }

    @BusSignal()
    public void SceneElementsApplied(String[] SceneElementIDs) throws BusException
    {
    }
}
