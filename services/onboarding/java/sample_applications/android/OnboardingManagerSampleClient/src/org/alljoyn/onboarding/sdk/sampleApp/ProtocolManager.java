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

package org.alljoyn.onboarding.sdk.sampleApp;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.UUID;

import org.alljoyn.about.AboutKeys;
import org.alljoyn.about.AboutService;
import org.alljoyn.about.AboutServiceImpl;
import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.PasswordManager;
import org.alljoyn.bus.SessionOpts;
import org.alljoyn.bus.Status;
import org.alljoyn.bus.Variant;
import org.alljoyn.bus.alljoyn.DaemonInit;
import org.alljoyn.onboarding.sdk.OnboardingIllegalArgumentException;
import org.alljoyn.onboarding.sdk.OnboardingIllegalStateException;
import org.alljoyn.onboarding.sdk.OnboardingManager;
import org.alljoyn.services.android.security.AuthPasswordHandler;
import org.alljoyn.services.android.security.SrpAnonymousKeyListener;
import org.alljoyn.services.android.utils.AndroidLogger;
import org.alljoyn.services.common.AnnouncementHandler;
import org.alljoyn.services.common.BusObjectDescription;
import org.alljoyn.services.common.utils.TransportUtil;

import android.content.Context;
import android.util.Log;

/**
 * Initializes an Alljoyn daemon and manages a list of AllJoyn devices the
 * daemon is announced on. This class will also enable the user to connect
 * Alljoyn bus attachment and disconnect from it.
 */
public class ProtocolManager implements AnnouncementHandler {

    private final String TAG = this.getClass().getSimpleName();

    /**
     * Default password for daemon and the Alljoyn devices
     */
    private final static String DEFAULT_PINCODE = "000000";

    /**
     * List of AllJoyn devices the daemon is announced on.
     */
    List<Device> deviceList;

    /**
     * The session less match rule to be used by the bus attachment.
     */
    private static final String SESSIONLESS_MATCH_RULE = "sessionless='t',type='error'";

    /**
     * Unique prefix indicated that this daemon will be advertised quietly.
     */
    private static final String DAEMON_QUIET_PREFIX = "quiet@";

    /**
     * AllJoynManager singleton.
     */
    private static ProtocolManager instance = null;

    /**
     * Android application context.
     */
    private Context context = null;

    /**
     * Alljoyn bus attachment.
     */
    private static BusAttachment busAttachment = null;

    /**
     * Alljoyn about service, needed to receive announcements from available
     * Alljoyn devices.
     */
    private AboutService aboutService = null;

    /**
     * String for Alljoyn daemon to be advertised with.
     */
    private static String daemonName = null;

    /**
     * Class represents onboarded device.
     */
    public class Device {

        /**
         * Bus attachment name
         */
        public String serviceName;

        /**
         * Alljoyn port for this device
         */
        public short port;

        /**
         * This device unique application id, taken from metadataMap map.
         */
        public UUID appId;

        /**
         * This device friendly name, taken from metadataMap map.
         */
        public String name;

        public Device(String serviceName, short port, UUID appId, String name) {
            this.serviceName = serviceName;
            this.port = port;
            this.appId = appId;
            this.name = name;
        }

        public void update(String serviceName, short port, String name) {
            this.serviceName = serviceName;
            this.port = port;
            this.name = name;
        }
    }

    public static ProtocolManager getInstance() {
        if (instance == null) {
            instance = new ProtocolManager();
        }
        return instance;
    }

    /**
     * Initialize the device list and starts the Alljoyn daemon.
     *
     * @param context
     *            Android application context
     */
    protected void init(Context context) {
        Log.i(TAG, "init");
        this.context = context;
        deviceList = new ArrayList<Device>();
        boolean prepareDaemonResult = DaemonInit.PrepareDaemon(context.getApplicationContext());
        Log.i(TAG, "PrepareDaemon returned " + prepareDaemonResult);
        connectToBus();
    }


    /**
     * Listen to aboutService onAnnouncement call and manage the DeviceList
     * accordingly.
     */
    @Override
    public void onAnnouncement(final String serviceName, final short port, final BusObjectDescription[] objectDescriptions, final Map<String, Variant> serviceMetadata) {
        UUID appId;
        String deviceName;

        // serviceMetadata map analysis
        try {
            Map<String, Object> fromVariantMap = TransportUtil.fromVariantMap(serviceMetadata);
            if (fromVariantMap == null) {
                Log.e(TAG, "onAnnouncement: serviceMetadata map = null !! ignoring.");
                return;
            }
            appId = (UUID) fromVariantMap.get(AboutKeys.ABOUT_APP_ID);
            deviceName = (String) fromVariantMap.get(AboutKeys.ABOUT_DEVICE_NAME);
            Log.i(TAG, "onAnnouncement: ServiceName = " + serviceName + " port = " + port + " deviceId = " + appId.toString() + " deviceName = " + deviceName);
        } catch (BusException e) {
            e.printStackTrace();
            return;
        }

        // update device list
        Device oldDevice = null;
        boolean deviceAdded = false;
        for (int i = 0; i < deviceList.size(); i++) {
            oldDevice = deviceList.get(i);
            if (oldDevice.appId.equals(appId)) {
                deviceList.remove(oldDevice);
                deviceList.add(new Device(serviceName, port, appId, deviceName));
                deviceAdded = true;
            }
        }
        if (!deviceAdded) {
            deviceList.add(new Device(serviceName, port, appId, deviceName));
        }
    }


    /**
     * Listen to aboutService onDeviceLost call and manage the DeviceList
     * accordingly.
     */
    @Override
    public void onDeviceLost(String serviceName) {
        Log.d(TAG, "onDeviceLost serviceName = " + serviceName);
        Device device = null;
        for (int i = 0; i < deviceList.size(); i++) {
            device = deviceList.get(i);
            if (device.serviceName.equals(serviceName)) {
                Log.i(TAG, "remove device from list, friendly name = " + device.name);
                deviceList.remove(device);
                break;
            }
        }
    }


    public List<Device> getDeviceList() {
        return deviceList;
    }


    /**
     * Creates new busAttachment, connect, register authListener and add
     * addMatch rule to it. Starts about service. Update the OnboardingManager with
     * the new busAttachment aboutClient objects.
     */
    public void connectToBus() {
        Log.i(TAG, "connectToBus");
        if (context == null) {
            Log.e(TAG, "Failed to connect AJ, m_context == null !!");
            return;
        }
        // prepare bus attachment
        busAttachment = new BusAttachment(context.getPackageName(), BusAttachment.RemoteMessage.Receive);
        // Set password for this daemon
        Status pasStatus = PasswordManager.setCredentials("ALLJOYN_PIN_KEYX", DEFAULT_PINCODE);
        if (pasStatus != Status.OK) {
            Log.e(TAG, "Failed to set password for daemon, Error: " + pasStatus);
        }
        busAttachment.connect();

        // request the name for the daemon and advertise it.
        daemonName = "org.alljoyn.BusNode.d" + busAttachment.getGlobalGUIDString();
        int flag = BusAttachment.ALLJOYN_REQUESTNAME_FLAG_DO_NOT_QUEUE;
        Status reqStatus = busAttachment.requestName(daemonName, flag);
        if (reqStatus == Status.OK) {
            // advertise the name with a quite prefix for devices to find it
            Status adStatus = busAttachment.advertiseName(DAEMON_QUIET_PREFIX + daemonName, SessionOpts.TRANSPORT_ANY);
            if (adStatus != Status.OK) {
                busAttachment.releaseName(daemonName);
                Log.w(TAG, "failed to advertise daemon name " + daemonName);
            } else {
                Log.d(TAG, "Succefully advertised daemon name " + daemonName);
            }
        }

        try {
            aboutService = AboutServiceImpl.getInstance();
            aboutService.startAboutClient(busAttachment);
            aboutService.addAnnouncementHandler(this);

            // Add auth listener - needed for OnboardingService secure calls
            String keyStoreFileName = context.getFileStreamPath("alljoyn_keystore").getAbsolutePath();
            SrpAnonymousKeyListener m_authListener = new SrpAnonymousKeyListener(new AuthPasswordHandler() {
                private final String TAG = "AlljoynOnAuthPasswordHandler";

                @Override
                public char[] getPassword(String peerName) {
                    return DEFAULT_PINCODE.toCharArray();
                }

                @Override
                public void completed(String mechanism, String authPeer, boolean authenticated) {
                    Log.d(TAG, "Auth completed: mechanism = " + mechanism + " authPeer= " + authPeer + " --> " + authenticated);
                }

            }, new AndroidLogger());
            Status authStatus = busAttachment.registerAuthListener("ALLJOYN_SRP_KEYX ALLJOYN_PIN_KEYX", m_authListener, keyStoreFileName);
            if (authStatus != Status.OK) {
                Log.e(TAG, "Failed to connectToBus");
            }
        } catch (Exception e) {
            Log.e(TAG, "fail to connectToBus", e);
        }

        try {
            OnboardingManager.getInstance().init(context, aboutService, busAttachment);
        } catch (OnboardingIllegalArgumentException e) {
            e.printStackTrace();
        } catch (OnboardingIllegalStateException e) {
            e.printStackTrace();
        }

        // DO the AJ addMatch after all AnnouncementHandlers was added.
        busAttachment.addMatch(SESSIONLESS_MATCH_RULE);
        Log.i(TAG, " connectToBus Done");
    }


    /**
     * Remove Match from Alljoyn bus attachment, Stop about client and cancel
     * bus advertise name.
     */
    public void disconnectFromBus() {
        Log.i(TAG, "disconnectFromBus");
        /*
         * It is important to unregister the BusObject before disconnecting from
         * the bus. Failing to do so could result in a resource leak.
         */
        try {
            if (busAttachment != null && busAttachment.isConnected()) {
                busAttachment.removeMatch(SESSIONLESS_MATCH_RULE);
                if (aboutService != null) {
                    aboutService.stopAboutClient();
                }
                busAttachment.cancelAdvertiseName(DAEMON_QUIET_PREFIX + daemonName, SessionOpts.TRANSPORT_ANY);
                busAttachment.releaseName(daemonName);
                busAttachment.disconnect();
                busAttachment = null;
            }
        } catch (Exception e) {
            Log.e(TAG, "Error when disconnectFromAJ ");
            e.printStackTrace();
        }
        Log.i(TAG, "bus disconnected");
        deviceList.clear();
    }


    public boolean isConnectedToBus() {
        if (busAttachment == null) {
            return false;
        }
        boolean isConnected = busAttachment.isConnected();
        Log.i(TAG, "isConnectToBus = " + isConnected);
        return isConnected;
    }
}
