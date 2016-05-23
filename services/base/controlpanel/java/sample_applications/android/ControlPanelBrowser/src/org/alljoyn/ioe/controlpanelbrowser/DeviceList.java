package org.alljoyn.ioe.controlpanelbrowser;
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
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.UUID;

import android.os.Parcel;
import android.os.Parcelable;
import android.util.Log;

/**
 * The list of the Devices discovered by Announcements
 */
public class DeviceList {
    private static final String TAG = "cpappDeviceList";

    /**
     * An array of ControlPanelContexts.
     */
    private final List<DeviceContext> contexts = new ArrayList<DeviceContext>();

    public void addItem(DeviceContext item) {

        //If the device with the same deviceId, appId exists, then remove it
        removeExistingDevice(item.getDeviceId(), item.getAppId());
        contexts.add(item);
    }

    public List<DeviceContext> getContexts() {
        return contexts;
    }

    public void onDeviceOffline(String busName) {

        Iterator<DeviceContext> iter = contexts.iterator();
        while ( iter.hasNext() ) {

            DeviceContext context = iter.next();
            if ( context.getBusName().equals(busName) ) {

                Log.d(TAG, "Found the busName to be removed from the list: '" + busName + "'");
                iter.remove();
            }
        }
    }

    /**
     * Check whether the {@link DeviceContext} with the given deviceId and appId exist in the list.
     * If the device is found it's removed from the {@link DeviceList}.
     * @param deviceId
     * @param appId
     * @return {@link DeviceContext} if the device was found and removed from the {@link DeviceList}
     * otherwise NULL is returned
     */
    private DeviceContext removeExistingDevice(String deviceId, UUID appId) {

        Iterator<DeviceContext> iter = contexts.iterator();
        while ( iter.hasNext() ) {

            DeviceContext context = iter.next();
            if ( context.getDeviceId().equals(deviceId) && context.getAppId().equals(appId) ) {

                Log.d(TAG, "The Device with the deviceId: '" + deviceId + "', appId: '" + appId + "' already exists, removing");
                iter.remove();
                return context;
            }
        }

        return null;
    }

    //=========================================================//

    /**
     * An item representing a device.
     */
    public static class DeviceContext implements Parcelable {

        final private String deviceId;
        final private String busName;
        final private String label;
        final private Map<String, String[]> object2Interfaces;
        final private UUID appId;

        /**
         * Constructor
         * @param deviceId
         * @param busName
         * @param deviceName
         * @param appId
         */
        public DeviceContext(String deviceId, String busName, String deviceName, UUID appId) {

            Log.d("DeviceList", String.format("Adding a new device. id='%s', busName='%s', name='%s' appId='%s;",
                                               deviceId, busName, deviceName, appId));

            this.deviceId = deviceId;
            this.busName  = busName;
            this.appId    = appId;
            this.object2Interfaces = new HashMap<String, String[]>(5);
            label = deviceName + '(' + busName + ')';
        }

        public String getDeviceId() {
            return deviceId;
        }

        public String getBusName() {
            return busName;
        }

        public UUID getAppId() {
            return appId;
        }

        public String getLabel() {
            return label;
        }

        public void addObjectInterfaces(String objPath, String[] interfaces) {
            object2Interfaces.put(objPath, interfaces);
        }

        public String[] getInterfaces(String objPath) {
            return object2Interfaces.get(objPath);
        }

        @Override
        public String toString() {
            return label;
        }

        @Override
        public int describeContents() {
            return 0;
        }

        @Override
        public void writeToParcel(Parcel out, int flags) {

            out.writeStringArray(new String[] { deviceId, busName, label, appId.toString() });
            out.writeMap(this.object2Interfaces);
        }

        public static final Parcelable.Creator<DeviceContext> CREATOR = new Parcelable.Creator<DeviceContext>() {
            @Override
            public DeviceContext createFromParcel(Parcel in) {
                return new DeviceContext(in);
            }

            @Override
            public DeviceContext[] newArray(int size) {
                return new DeviceContext[size];
            }
        };

        private DeviceContext(Parcel in) {

            String[] fields = new String[4];

            in.readStringArray(fields);
            this.deviceId   = fields[0];
            this.busName    = fields[1];
            this.label      = fields[2];
            this.appId      = UUID.fromString(fields[3]);

            this.object2Interfaces = new HashMap<String, String[]>(5);
            in.readMap(object2Interfaces, getClass().getClassLoader());
        }

        public Set<String> getBusObjects() {
            return object2Interfaces.keySet();
        }
    }
}
