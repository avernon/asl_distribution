/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.ProxyBusObject;
import org.alljoyn.bus.Status;
import org.alljoyn.bus.annotation.BusSignalHandler;
import org.alljoyn.onboarding.OnboardingService.AuthType;
import org.alljoyn.onboarding.transport.ConnectionResult;
import org.alljoyn.onboarding.transport.ConnectionResult.ConnectionResponseType;
import org.alljoyn.onboarding.transport.ConnectionResultAJ;
import org.alljoyn.onboarding.transport.ConnectionResultListener;
import org.alljoyn.onboarding.transport.OBLastError;
import org.alljoyn.onboarding.transport.OnboardingTransport;
import org.alljoyn.onboarding.transport.OnboardingTransport.ConfigureWifiMode;
import org.alljoyn.onboarding.transport.ScanInfo;
import org.alljoyn.services.common.ClientBaseImpl;
import org.alljoyn.services.common.ServiceAvailabilityListener;

/**
 * A default implementation of the OnboardingClient interface
 */
public class OnboardingClientImpl extends ClientBaseImpl implements OnboardingClient {

    /**
     * Used to register the bus object upon the bus attachment
     */
    private final static String CONNECTION_RESULT_PATH = "/OnboardingTranport/ConnectionResult";

    /**
     * Stores instance  of ConnectionResultReceiver
     */
    private ConnectionResultReceiver receiver = null;

    /**
     * Stores instance of ConnectionResultListener {@link ConnectionResultListener}
     */
    private ConnectionResultListener connectionResultListener = null;

    /**
     * Internal class  used for receiving ConnectionResult signal .
     * Calls onConnectionResult to the CallBack  ConnectionResultListener to deliver the signal data.
     */
    private class ConnectionResultReceiver implements BusObject {
        @BusSignalHandler(iface = OnboardingTransport.INTERFACE_NAME, signal = "ConnectionResult")
        public void ConnectionResult(ConnectionResultAJ connectionResultAJ) {
            ConnectionResult.ConnectionResponseType  connectionResponseType =ConnectionResult.ConnectionResponseType.getConnectionResponseTypeByValue(connectionResultAJ.code);
            if (connectionResponseType==null){
                connectionResponseType=ConnectionResponseType.ERROR_MESSAGE;
            }
            if (connectionResultListener!=null){
                connectionResultListener.onConnectionResult(new ConnectionResult(connectionResponseType, connectionResultAJ.message));
            }
        }
    }

    @SuppressWarnings("deprecation")
    public OnboardingClientImpl(String m_deviceName, BusAttachment bus, ServiceAvailabilityListener serviceAvailabilityListener, short port) {
        super(m_deviceName, bus, serviceAvailabilityListener, OnboardingTransport.OBJ_PATH, OnboardingTransport.class, port);
    }

    @Override
    public short getVersion() throws BusException {
        ProxyBusObject proxyObj = getProxyObject();
        /*
         * We make calls to the methods of the AllJoyn object through one of its
         * interfaces.
         */
        OnboardingTransport onboardingTransport = proxyObj.getInterface(OnboardingTransport.class);
        return onboardingTransport.getVersion();
    }

    @Override
    public void connectWiFi() throws BusException {
        ProxyBusObject proxyObj = getProxyObject();
        // We make calls to the methods of the AllJoyn object through one of its
        // interfaces.
        OnboardingTransport onboardingTransport = proxyObj.getInterface(OnboardingTransport.class);
        onboardingTransport.Connect();
    }

    @Override
    public ConfigureWifiMode configureWiFi(String ssid, String passphrase, AuthType  authType) throws BusException {
        ProxyBusObject proxyObj = getProxyObject();
        // We make calls to the methods of the AllJoyn object through one of its
        // interfaces.
        OnboardingTransport onboardingTransport = proxyObj.getInterface(OnboardingTransport.class);

        short val=onboardingTransport.ConfigureWiFi(ssid, passphrase, authType.getTypeId());
        ConfigureWifiMode ret=ConfigureWifiMode.getConfigureWifiModeByValue(val);
        //in case the result of the ConfigureWiFi is not REGULAR /FAST_CHANNNEL set it to be REGULAR.
        if (ret==null){
            ret=ConfigureWifiMode.REGULAR;
        }
        return ret;
    }

    @Override
    public void offboard() throws BusException {
        ProxyBusObject proxyObj = getProxyObject();
        // We make calls to the methods of the AllJoyn object through one of its
        // interfaces.
        OnboardingTransport onboardingTransport = proxyObj.getInterface(OnboardingTransport.class);
        onboardingTransport.Offboard();
    }

    @Override
    public ScanInfo getScanInfo() throws BusException {
        ProxyBusObject proxyObj = getProxyObject();
        // We make calls to the methods of the AllJoyn object through one of its
        // interfaces.
        OnboardingTransport onboardingTransport = proxyObj.getInterface(OnboardingTransport.class);
        return onboardingTransport.GetScanInfo();
    }

    @Override
    public short getState() throws BusException {
        ProxyBusObject proxyObj = getProxyObject();
        // We make calls to the methods of the AllJoyn object through one of its
        // interfaces.
        OnboardingTransport onboardingTransport = proxyObj.getInterface(OnboardingTransport.class);
        return onboardingTransport.getState();
    }

    @Override
    public OBLastError GetLastError() throws BusException {
        ProxyBusObject proxyObj = getProxyObject();
        // We make calls to the methods of the AllJoyn object through one of its
        // interfaces.
        OnboardingTransport onboardingTransport = proxyObj.getInterface(OnboardingTransport.class);
        return onboardingTransport.getLastError();
    }

    @Override
    public void registerConnectionResultListener(ConnectionResultListener listener) throws BusException {

        if (receiver == null) {
            receiver = new ConnectionResultReceiver();
        }

        Status status = this.m_bus.registerBusObject(receiver, CONNECTION_RESULT_PATH);
        if (status != Status.OK) {
            throw new BusException("registerBusObject  " + CONNECTION_RESULT_PATH + " signal handler has failed, Status: '" + status + "'");
        }

        status = this.m_bus.registerSignalHandlers(receiver);
        if (status != Status.OK) {
            throw new BusException("registerSignalHandlers  " + CONNECTION_RESULT_PATH + " signal handler has failed, Status: '" + status + "'");
        }

        this.connectionResultListener = listener;
    }

    @Override
    public void unRegisterConnectionResultListener(ConnectionResultListener listener) {
        if (receiver != null) {
            this.connectionResultListener=null;
            this.m_bus.unregisterSignalHandlers(receiver);
            this.m_bus.unregisterBusObject(receiver);
        }
    }

}
