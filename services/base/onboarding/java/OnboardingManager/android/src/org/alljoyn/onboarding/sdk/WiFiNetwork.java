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
package org.alljoyn.onboarding.sdk;

import org.alljoyn.onboarding.OnboardingService.AuthType;

import android.os.Parcel;
import android.os.Parcelable;

/**
 * WiFiNetwork encapsulates information retrieved from a WIFI scan
 */
public class WiFiNetwork implements Parcelable {

    /**
     * WIFI SSID name
     */
    protected String SSID = null;
    /**
     * WIFI authentication type @see org.alljoyn.onboarding.OnboardingService.AuthType
     */
    protected AuthType authType;
    /**
     * WIFI signal strength
     */
    protected int level = 0;

    /**
     * Constructor
     */
    public WiFiNetwork() {
    }

    /**
     * Constructor with SSID
     *
     * @param SSID
     */
    public WiFiNetwork(String SSID) {
        this.SSID = SSID;
    }

    /**
     * Constructor with SSID,capabilities,level
     *
     * @param SSID
     * @param capabilities
     * @param level
     */
    public WiFiNetwork(String SSID, String capabilities, int level) {
        this.SSID = SSID;
        this.authType = capabilitiesToAuthType(capabilities);
        this.level = level;
    }

    /**
     * Constructor from a Parcel
     *
     * @param in
     */
    public WiFiNetwork(Parcel in) {
        this.SSID = in.readString();
        this.authType = AuthType.getAuthTypeById((short) in.readInt());
        this.level = in.readInt();
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    /**
     * write the members to the Parcel
     */
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(SSID);
        dest.writeInt(authType.getTypeId());
        dest.writeInt(level);
    }

    public static final Parcelable.Creator<WiFiNetwork> CREATOR = new Parcelable.Creator<WiFiNetwork>() {

        @Override
        public WiFiNetwork createFromParcel(Parcel in) {
            return new WiFiNetwork(in);
        }

        @Override
        public WiFiNetwork[] newArray(int size) {
            return new WiFiNetwork[size];
        }
    };

    /**
     * Get {@link #SSID}
     *
     * @return the ssid of the Wi-Fi network {@link #SSID}
     */
    public String getSSID() {
        return SSID;
    }

    /**
     * Set {@link #SSID}
     *
     * @param SSID {@link #SSID}
     */
    public void setSSID(String SSID) {
        this.SSID = SSID;
    }

    /**
     * Get {@link #authType}
     *
     * @return the authentication type of the Wi-Fi network {@link #authType}
     */
    public AuthType getAuthType() {
        return authType;
    }

    /**
     * Get  {@link #level}
     *
     * @return the signal level of Wi-Fi network {@link #level}
     */
    public int getLevel() {
        return level;
    }


    /**
     * Converts capabilities string to AuthType
     * @param capabilities string representing the possible Wi-Fi authentication scheme
     * @return authentication type complies to @see org.alljoyn.onboarding.OnboardingService.AuthType
     */
    private AuthType capabilitiesToAuthType(String capabilities) {
        if (capabilities.contains("WPA2")) {
            if (capabilities.contains("TKIP")) {
                return AuthType.WPA2_TKIP;
            } else if (capabilities.contains("CCMP")) {
                return AuthType.WPA2_CCMP;
            } else {
                return AuthType.WPA2_AUTO;
            }
        }
        if (capabilities.contains("WPA")) {
            if (capabilities.contains("TKIP")) {
                return AuthType.WPA_TKIP;
            } else if (capabilities.contains("CCMP")) {
                return AuthType.WPA_CCMP;
            } else {
                return AuthType.WPA_AUTO;
            }
        }
        if (capabilities.contains(AuthType.WEP.name())) {
            return AuthType.WEP;
        }
        return AuthType.OPEN;
    }

}
