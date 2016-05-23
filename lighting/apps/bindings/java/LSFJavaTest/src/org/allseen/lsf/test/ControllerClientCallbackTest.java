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
package org.allseen.lsf.test;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import junit.framework.TestCase;

import org.allseen.lsf.ControllerClientCallback;
import org.allseen.lsf.sdk.ErrorCode;

public class ControllerClientCallbackTest extends TestCase {
    // Load the native library on application start
    static {
        System.loadLibrary("gnustl_shared");
        System.loadLibrary("alljoyn_java");
        System.loadLibrary("alljoyn_lsf_java");
        System.loadLibrary("alljoyn_lsf_java_test");
    }

    private static String lampStateFieldKey = "lampStateFieldKey";
    private List<Object> results;
    private ControllerClientCallback callback;

    @Override
    protected void setUp() throws Exception
    {
        results = new ArrayList<Object>();
        callback = new ControllerClientCallback() {
            @Override
            public void connectedToControllerServiceCB(String controllerServiceDeviceID, String controllerServiceName) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(controllerServiceDeviceID);
                results.add(controllerServiceName);
            }

            @Override
            public void connectToControllerServiceFailedCB(String controllerServiceDeviceID, String controllerServiceName) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(controllerServiceDeviceID);
                results.add(controllerServiceName);
            }

            @Override
            public void disconnectedFromControllerServiceCB(String controllerServiceDeviceID, String controllerServiceName) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(controllerServiceDeviceID);
                results.add(controllerServiceName);
            }

            @Override
            public void controllerClientErrorCB(ErrorCode[] errorCodeList) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(errorCodeList);
            }
        };

        super.setUp();
    }

    @Override
    protected void tearDown() throws Exception
    {
        results = null;
        callback = null;

        super.tearDown();
    }

    private native String connectedToControllerServiceCB(ControllerClientCallback cc, String deviceID, String serviceName);
    public void testConnectedToControllerServiceCB()
    {
        String deviceID = "ID-1";
        String serviceName = "Name-1";
        String method = connectedToControllerServiceCB(callback, deviceID, serviceName);

        assertTrue(Arrays.equals(new Object[] {method, deviceID, serviceName}, results.toArray()));
    }

    private native String connectToControllerServiceFailedCB(ControllerClientCallback cc, String deviceID, String serviceName);
    public void testconnectToControllerServiceFailedCB()
    {
        String deviceID = "ID-2";
        String serviceName = "Name-2";
        String method = connectToControllerServiceFailedCB(callback, deviceID, serviceName);

        assertTrue(Arrays.equals(new Object[] {method, deviceID, serviceName}, results.toArray()));
    }

    private native String disconnectedFromControllerServiceCB(ControllerClientCallback cc, String deviceID, String serviceName);
    public void testDisconnectedFromControllerServiceCB()
    {
        String deviceID = "ID-3";
        String serviceName = "Name-3";
        String method = disconnectedFromControllerServiceCB(callback, deviceID, serviceName);

        assertTrue(Arrays.equals(new Object[] {method, deviceID, serviceName}, results.toArray()));
    }

    private native String controllerClientErrorCB(ControllerClientCallback cc, ErrorCode[] ecl);
    public void testControllerClientErrorCB()
    {
        ErrorCode[] ecl = new ErrorCode[] {ErrorCode.NONE, ErrorCode.ERR_REGISTERING_SIGNAL_HANDLERS};
        String method = controllerClientErrorCB(callback, ecl);
        assertTrue(Arrays.deepEquals(new Object[] {method, ecl}, results.toArray()));
    }
}
