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
 * WiFiNetwork encapsulates information how to connect to a WIFI network
 *
 */
public class WiFiNetworkConfiguration extends WiFiNetwork implements Parcelable {

    /**
     * WIFI password
     */
    private String password = null;
    /**
     * WIFI SSID hidden
     */
    private boolean hidden = false;

    /**
     * Constructor with SSID,authType,password,cipher
     *
     * @param SSID
     * @param authType
     * @param password
     */
    public WiFiNetworkConfiguration(String SSID, AuthType authType, String password) {
        super.setSSID(SSID);
        this.password = password;
        this.authType = authType;

    }

    public WiFiNetworkConfiguration(String SSID, AuthType authType, String password, boolean isHidden) {
        super.setSSID(SSID);
        this.password = password;
        this.authType = authType;
        this.hidden = isHidden;
    }

    /**
     * Constructor from a Parcel
     *
     * @param in
     */
    public WiFiNetworkConfiguration(Parcel in) {
        SSID = in.readString();
        password = in.readString();
        authType = AuthType.getAuthTypeById((short) in.readInt());
        hidden = (in.readByte() != 0);
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    /**
     *  write the members to the Parcel
     */
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(SSID);
        dest.writeString(password);
        dest.writeInt(authType.getTypeId());
        dest.writeByte((byte) (hidden ? 1 : 0));
    }

    public static final Parcelable.Creator<WiFiNetworkConfiguration> CREATOR = new Parcelable.Creator<WiFiNetworkConfiguration>() {
        @Override
        public WiFiNetworkConfiguration createFromParcel(Parcel in) {
            return new WiFiNetworkConfiguration(in);
        }

        @Override
        public WiFiNetworkConfiguration[] newArray(int size) {
            return new WiFiNetworkConfiguration[size];
        }
    };

    /**
     * Get {@link #password}
     *
     * @return the password of the network {@link #password}
     */
    public String getPassword() {
        return password;
    }

    public boolean isHidden() {
        return hidden;
    }

}
