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

package org.alljoyn.ns.transport.interfaces;

import java.util.Map;

import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.Variant;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.ns.transport.TransportNotificationText;

/**
 * The interface used to send and receive "session less" notification signals
 */
@BusInterface(name = NotificationTransport.IF_NAME, announced = "true")
public interface NotificationTransport extends BusObject
{

    /**
     * AllJoyn interface name
     */
    public static final String IF_NAME = "org.alljoyn.Notification";

    /**
     * The interface version
     */
    public static final short VERSION = 1;

    /**
     * Use the method to send or receive AJ session less signal
     * 
     * @param version
     *            The version of the message signature
     * @param msgId
     *            The notification message id
     * @param messageType
     *            Notification message type id
     * @param deviceId
     *            Device Id
     * @param deviceName
     *            Device Name
     * @param appId
     *            App Id
     * @param appName
     *            App Name
     * @param attributes
     *            Attributes key-value pair
     * @param customAttributes
     *            customAttributes
     * @param text
     *            Array of NotificationText objects
     */
    @BusSignal(signature = "qiqssaysa{iv}a{ss}ar")
    public void notify(int version, int msgId, short messageType, String deviceId, String deviceName, byte[] appId, String appName, Map<Integer, Variant> attributes,
            Map<String, String> customAttributes, TransportNotificationText[] text);
}
