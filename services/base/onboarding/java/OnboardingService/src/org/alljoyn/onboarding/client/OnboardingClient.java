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

package org.alljoyn.onboarding.client;

import org.alljoyn.bus.BusException;
import org.alljoyn.onboarding.OnboardingService.AuthType;
import org.alljoyn.onboarding.transport.ConnectionResultListener;
import org.alljoyn.onboarding.transport.OBLastError;
import org.alljoyn.onboarding.transport.OnboardingTransport.ConfigureWifiMode;
import org.alljoyn.onboarding.transport.ScanInfo;
import org.alljoyn.services.common.ClientBase;
/**
 * An interface for onboarding a remote IoE device (onboardee). Encapsulates the
 * OnboardingTransport BusInterface
 */
public interface OnboardingClient extends ClientBase {
    /**
     * Returns the configured state of the onboardee
     *
     * @return the onboarding state: 0 - Personal AP Not Configured 1 - Personal
     *         AP Configured/Not Validated 2 - Personal AP Configured/Validating
     *         3 - Personal AP Configured/Validated 4 - Personal AP
     *         Configured/Error 5 - Personal AP Configured/Retry
     * @throws BusException
     */
    public short getState() throws BusException;

    /**
     * Get the last error. During most of the onboarding process, the onboarder
     * and onboardee are on different networks so returning a sync result isn't
     * possible. Especially when there was an error and the onboardee did not
     * connect to the onboarder's network. The onboardee then opens a soft AP to
     * which the onboarder connects, and this method is how the onboarder can
     * query about what happened.
     *
     * @return last error
     * @throws BusException
     */
    public OBLastError GetLastError() throws BusException;



    /**
     * Send the personal AP info to the onboardee. The onboardee doesn't try to
     * connect yet. It waits for {@link #connectWiFi()} When the authType is
     * equal to "any", the onboardee needs to try out all the possible
     * authentication types it supports to connect to the AP.
     *
     * @param ssid
     *            the personal AP SSID
     * @param passphrase
     *            the personal AP passphrase
     * @param authType
     *            the authentication type of the AP
     * @return Wifi mode regular or fast channel
     * @throws BusException
     *             If authType parameter is invalid then the AllJoyn error code
     *             org.alljoyn.Error.OutOfRange will be returned
     */
    public ConfigureWifiMode configureWiFi(String ssid, String passphrase, AuthType  authType) throws BusException;

    /**
     * Tell the onboardee to connect to the Personal AP. The onboardee is
     * recommended to use channel switching feature if it is available. That is,
     * keep the soft AP open with the onboarder, while trying to connect to the
     * personal AP.
     *
     * @throws BusException
     */
    public void connectWiFi() throws BusException;

    /**
     * Tell the onboardee to disconnect from the personal AP, clear the personal
     * AP configuration fields, and start the soft AP mode.
     *
     * @throws BusException
     */
    public void offboard() throws BusException;

    /**
     * Scan all the WiFi access points in the onboardee's proximity, so that the
     * onboarder can select the proper one. Some devices may not support this
     * feature.
     *
     * @return ScanInfo an array of scan results.
     * @throws BusException
     *             If device doesn't support the feature, the AllJoyn error code
     *             org.alljoyn.Error.FeatureNotAvailable will be returned in the
     *             AllJoyn response.
     */
    public ScanInfo getScanInfo() throws BusException;

    /***
     * Register to receive ConnectionResult signal data.
     * This is relevant in fast channel switching mode.
     *
     * @param listener callback class to receive data.
     * @throws BusException if registration fails
     */
    public void registerConnectionResultListener(ConnectionResultListener listener) throws BusException;

    /**
     * Unregister from receiving ConnectionResult signal data.
     * @param listener
     */
    public void unRegisterConnectionResultListener(ConnectionResultListener listener);

}
