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
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.annotation.Position;

@BusInterface(name = "org.allseen.LSF.ControllerService.SceneWithSceneElements")
public interface ControllerServiceSWSEBusInterface
{
    /*
    "   <property name="Version" type="u" access="read" />"
    */
    @BusProperty(signature="u")
    public int getVersion() throws BusException;

    public class SceneWithSceneElementsValues
    {
        @Position(0)
        public int responseCode;
        @Position(1)
        public String sceneWithSceneElementsID;
    }

/*
    "    <method name='CreateSceneWithSceneElements'>"
    "      <arg name='sceneElementIDs' type='as' direction='in'/>"
    "      <arg name='sceneName' type='s' direction='in'/>"
    "      <arg name='language' type='s' direction='in'/>"
    "      <arg name='responseCode' type='u' direction='out'/>"
    "      <arg name='sceneID' type='s' direction='out'/>"
    "    </method>"
 */

    @BusMethod(signature= "asss" , replySignature = "us")
    public SceneWithSceneElementsValues CreateSceneWithSceneElements(String[] sceneElementIDs, String sceneName, String language) throws BusException;

/*
    "    <method name='UpdateSceneWithSceneElements'>"
    "      <arg name='sceneID' type='s' direction='in'/>"
    "      <arg name='sceneElementIDs' type='as' direction='in'/>"
    "      <arg name='responseCode' type='u' direction='out'/>"
    "      <arg name='sceneID' type='s' direction='out'/>"
    "    </method>"
 */

    @BusMethod(signature= "sas" , replySignature = "us")
    public SceneWithSceneElementsValues UpdateSceneWithSceneElements(String sceneID, String[] SceneElementIDs) throws BusException;

/*
    "    <method name='GetSceneWithSceneElements'>"
    "      <arg name='sceneID' type='s' direction='in'/>"
    "      <arg name='responseCode' type='u' direction='out'/>"
    "      <arg name='sceneID' type='s' direction='out'/>"
    "      <arg name='sceneElementIDs' type='as' direction='out'/>"
    "    </method>"
 */

    public class GetSceneWithSceneElementsValues
    {
        @Position(0)
        public int responseCode;
        @Position(1)
        public String sceneID;
        @Position(2)
        public String[] sceneElementIDs;
    }

    @BusMethod(signature= "s" , replySignature = "usas")
    public GetSceneWithSceneElementsValues GetSceneWithSceneElements(String sceneID) throws BusException;

}
