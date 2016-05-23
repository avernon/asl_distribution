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

import java.util.Map;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.annotation.Position;

@BusInterface(name = "org.allseen.LSF.ControllerService.DataSet")
public interface ControllerServiceDataSetBusInterface
{
/*
    <property name="Version" type="u" access="read"/>
*/
    @BusProperty(signature="u")
    public int getVersion() throws BusException;

/*
    <method name="GetLampDataSet">
        <arg name="lampID" type="s" direction="in"/>
        <arg name="language" type="s" direction="in"/>
        <arg name="responseCode" type="u" direction="out"/>
        <arg name="lampID" type="s" direction="out"/>
        <arg name="language" type="s" direction="out"/>
        <arg name="lampName" type="s" direction="out"/>
        <arg name="lampDetails" type="a{sv}" direction="out"/>
        <arg name="lampState" type="a{sv}" direction="out"/>
        <arg name="lampParameters" type="a{sv}" direction="out"/>
    </method>
*/
    public class GetLampDataSetValues
    {
        @Position(0)
        public int responseCode;
        @Position(1)
        public String lampID;
        @Position(2)
        public String language;
        @Position(3)
        public String lampName;
        @Position(4)
        public Map<String, Variant> lampDetails;
        @Position(5)
        public Map<String, Variant> lampState;
        @Position(6)
        public Map<String, Variant> lampParameters;
    }

    @BusMethod(signature = "ss", replySignature = "usssa{sv}a{sv}a{sv}")
    public GetLampDataSetValues GetLampDataSet(String lampID, String language);
}
