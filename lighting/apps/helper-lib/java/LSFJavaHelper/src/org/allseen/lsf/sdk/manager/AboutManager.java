/*
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
 */
package org.allseen.lsf.sdk.manager;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.alljoyn.bus.AboutKeys;
import org.alljoyn.bus.AboutListener;
import org.alljoyn.bus.AboutObjectDescription;
import org.alljoyn.bus.AboutProxy;
import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Mutable;
import org.alljoyn.bus.SessionListener;
import org.alljoyn.bus.SessionOpts;
import org.alljoyn.bus.Status;
import org.alljoyn.bus.Variant;
import org.allseen.lsf.sdk.ResponseCode;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class AboutManager implements AboutListener {
    private BusAttachment bus;
    private final LightingSystemManager<?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?> manager;

    private static final String[] LAMP_SERVICE_INTERFACE_NAMES = {
        "org.allseen.LSF.LampService",
        "org.allseen.LSF.LampState",
        "org.allseen.LSF.LampParameters",
        "org.allseen.LSF.LampDetails" };
    private static final String[] CONTROLLER_SERVICE_INTERFACE_NAMES = {
        "org.allseen.LSF.ControllerService.Lamp",
        "org.allseen.LSF.ControllerService.LampGroup",
        "org.allseen.LSF.ControllerService.Preset",
        "org.allseen.LSF.ControllerService.Scene",
        "org.allseen.LSF.ControllerService.MasterScene" };

    public AboutManager(LightingSystemManager<?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?> manager) {
        this.bus = null;
        this.manager = manager;
    }

    public void start(BusAttachment ba) {
        if (bus == null) {
            bus = ba;

            bus.registerAboutListener(this);

            bus.whoImplements(AboutManager.LAMP_SERVICE_INTERFACE_NAMES);
            bus.whoImplements(AboutManager.CONTROLLER_SERVICE_INTERFACE_NAMES);
        }
    }

    public void stop() {
        if (bus != null) {
            bus.unregisterAboutListener(this);

            bus.cancelWhoImplements(AboutManager.LAMP_SERVICE_INTERFACE_NAMES);
            bus.cancelWhoImplements(AboutManager.CONTROLLER_SERVICE_INTERFACE_NAMES);

            bus = null;
        }
    }

    public void destroy() {
        if (bus != null) {
            stop();
        }
    }

    @Override
    public void announced(String busName, int version, short port, AboutObjectDescription[] aboutObjects, Map<String, Variant> announcedData) {
        //Log.d("AboutManager", "Announcement received from AboutService");

        // Flatten the interfaces
        List<String> allInterfaces = new ArrayList<String>();
        for (AboutObjectDescription aboutObject : aboutObjects) {
            for (String iface : aboutObject.interfaces) {
                allInterfaces.add(iface);
            }
        }

        if (containsLampInterfaces(allInterfaces)) {
            //Log.d("AboutManager", "announcement: lamp ifaces found");
            addLampAnnouncedAboutData(busName, port, announcedData);
        } else if (containsControllerInterfaces(allInterfaces)) {
            //Log.d("AboutManager", "announcement: controller ifaces found");
            addControllerAnnouncedAboutData(announcedData);
        }
    }

    protected boolean containsLampInterfaces(List<String> allInterfaces) {
        for (String iface : AboutManager.LAMP_SERVICE_INTERFACE_NAMES) {
            if (!allInterfaces.contains(iface)) {
                // This does not have a necessary lamp interface
                //Log.d("AboutManager", "containsLampInterfaces: iface missing");
                return false;
            }
        }

        return true;
    }

    protected boolean containsControllerInterfaces(List<String> allInterfaces) {
        for (String iface : AboutManager.CONTROLLER_SERVICE_INTERFACE_NAMES) {
            if (!allInterfaces.contains(iface)) {
                // This does not have a necessary controller interface
                //Log.d("AboutManager", "containsControllerInterfaces: iface missing");
                return false;
            }
        }

        return true;
    }

    protected void addLampAnnouncedAboutData(String busName, short port, final Map<String, Variant> announcedData) {
        String lampID = getStringFromVariantMap(AboutKeys.ABOUT_DEVICE_ID, announcedData, null);

        if (lampID != null) {
            //Log.d("AboutManager", "Announce received: " + lampID);
            manager.lampManagerCB.postOnLampAnnouncedAboutData(lampID, busName, port, announcedData, 0);
        } else {
            //Log.e("AboutManager", "Announcement lacks device ID");
        }
    }

    public void getLampQueriedAboutData(String lampID, String busName, short port) {
        Mutable.IntegerValue sessionId = new Mutable.IntegerValue();;

        try {
            SessionOpts sessionOpts = new SessionOpts();
            sessionOpts.traffic = SessionOpts.TRAFFIC_MESSAGES;
            sessionOpts.isMultipoint = false;
            sessionOpts.proximity = SessionOpts.PROXIMITY_ANY;
            sessionOpts.transports = SessionOpts.TRANSPORT_ANY;

            Status status = bus.joinSession(busName, port, sessionId, sessionOpts, new SessionListener() {
                @Override
                public void sessionLost(int sessionId, int reason) {
                    //Log.d("AboutManager", "Session Lost : " + sessionId + " reason: " + reason);
                }});

            //Log.d("AboutManager", "bus " + busName + ", port " + port + ", session " + sessionId.value);

            if (status == Status.OK) {
                //Log.d("AboutManager", "join session success");
                AboutProxy aboutProxy = new AboutProxy(bus, busName, sessionId.value);
                Map<String, Variant> queriedData = aboutProxy.getAboutData(LightingSystemManager.LANGUAGE);

                manager.lampManagerCB.postOnLampQueriedAboutData(lampID, queriedData, 0);
            } else {
                manager.getLampCollectionManager().sendErrorEvent("getLampQueriedAboutData(): " + status.name(), ResponseCode.ERR_FAILURE, lampID);
            }
        } catch (BusException e) {
            manager.getLampCollectionManager().sendErrorEvent("getLampQueriedAboutData(): " + e.getMessage(), ResponseCode.ERR_FAILURE, lampID);
        } finally {
            bus.leaveSession(sessionId.value);
        }
    }

    protected void addControllerAnnouncedAboutData(final Map<String, Variant> announceData) {
        String controllerID = getStringFromVariantMap(AboutKeys.ABOUT_DEVICE_ID, announceData, null);
        String controllerName = getStringFromVariantMap(AboutKeys.ABOUT_DEVICE_NAME, announceData, null);

        manager.controllerClientCB.postOnControllerAnnouncedAboutData(controllerID, controllerName, 200);
    }

    public static String getStringFromVariantMap(String key, Map<String, Variant> variantMap, String defaultValue) {
        String value = defaultValue;

        if (variantMap != null) {
            try {
                Variant variant = variantMap.get(key);

                if (variant != null) {
                    value = variant.getObject(String.class);
                }
            } catch (BusException e) {
                value = defaultValue;
                //TODO-FIX Log.e(SampleAppActivity.TAG, "Announce parsing failed: key: " + key + ": " + e.getMessage());
            }
        }

        return value;
    }

    public static String getByteArrayHexStringFromVariantMap(String key, Map<String, Variant> variantMap, String defaultValue) {
        String value = defaultValue;

        if (variantMap != null) {
            try {
                Variant variant = variantMap.get(key);

                if (variant != null) {
                    byte[] bytes = variant.getObject(byte[].class);

                    value = bytesToHexString(bytes);
                }
            } catch (BusException e) {
                value = defaultValue;
                //TODO-FIX Log.e(SampleAppActivity.TAG, "Announce parsing failed: key: " + key + ": " + e.getMessage());
            }
        }

       return value;
    }

    public static String bytesToHexString(byte[] bytes) {
        StringBuilder sb = new StringBuilder("0x");

        for (int i = 0; i < bytes.length; i++) {
            sb.append(String.format("%02X", bytes[i]));

            // group the bytes into groups of 4
            if((i + 1) % 4 == 0) {
                sb.append(" ");
            }
        }

        return sb.toString();
    }
}
