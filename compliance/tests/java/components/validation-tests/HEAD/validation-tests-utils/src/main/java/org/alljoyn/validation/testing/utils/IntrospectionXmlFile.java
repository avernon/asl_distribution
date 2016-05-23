/*******************************************************************************
 *  Copyright AllSeen Alliance. All rights reserved.
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
package org.alljoyn.validation.testing.utils;

public enum IntrospectionXmlFile
{
    About("introspection-xml/About.xml"), Introspectable("introspection-xml/Introspectable.xml"), Action("introspection-xml/Action.xml"), Audio("introspection-xml/Audio.xml"), Config(
            "introspection-xml/Config.xml"), Container("introspection-xml/Container.xml"), ControlPanel("introspection-xml/ControlPanel.xml"), DeviceIcon(
            "introspection-xml/DeviceIcon.xml"), Dialog("introspection-xml/Dialog.xml"), HTTPControl("introspection-xml/HTTPControl.xml"), LabelProperty(
            "introspection-xml/LabelProperty.xml"), ListProperty("introspection-xml/ListProperty.xml"), Notification("introspection-xml/Notification.xml"), NotificationAction(
            "introspection-xml/NotificationAction.xml"), Onboarding("introspection-xml/Onboarding.xml"), Peer("introspection-xml/Peer.xml"), Property(
            "introspection-xml/Property.xml"), Clock("introspection-xml/Clock.xml"), Alarm("introspection-xml/Alarm.xml"), AlarmFactory("introspection-xml/AlarmFactory.xml"), TimeAuthority(
            "introspection-xml/TimeAuthority.xml"), Timer("introspection-xml/Timer.xml"), TimerFactory("introspection-xml/TimerFactory.xml"), GWAgentCtrlAcl(
            "introspection-xml/GWAgentCtrlAcl.xml"), GWAgentCtrlAclMgmt("introspection-xml/GWAgentCtrlAclMgmt.xml"), GWAgentCtrlApp("introspection-xml/GWAgentCtrlApp.xml"), GWAgentCtrlAppMgmt(
            "introspection-xml/GWAgentCtrlAppMgmt.xml"), GWAgentConnectorApp("introspection-xml/GWAgentConnectorApp.xml");

    private String value;

    IntrospectionXmlFile(String value)
    {
        this.value = value;
    }

    public String getValue()
    {
        return value;
    }
}
