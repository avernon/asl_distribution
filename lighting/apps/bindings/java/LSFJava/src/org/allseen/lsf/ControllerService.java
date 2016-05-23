/*
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
 */
package org.allseen.lsf;

import org.allseen.lsf.sdk.AboutData;
import org.allseen.lsf.sdk.RankAvailability;
import org.allseen.lsf.sdk.RankMobility;
import org.allseen.lsf.sdk.RankNodeType;
import org.allseen.lsf.sdk.RankPower;

public abstract class ControllerService extends DefaultNativeClassWrapper {
    private static final NativeLibraryLoader LIBS = NativeLibraryLoader.LIBS;

    public ControllerService() {
        createNativeObject();
    }

    public abstract void populateDefaultProperties(AboutData aboutData);
    public abstract String getMacAddress(String generatedMacAddress);
    public abstract boolean isNetworkConnected();
    public abstract RankPower getRankPower();
    public abstract RankMobility getRankMobility();
    public abstract RankAvailability getRankAvailability();
    public abstract RankNodeType getRankNodeType();

    public native void start(String keyStorePath);
    public native void stop();
    public native void lightingReset();
    public native void factoryReset();
    public native void sendNetworkConnected();
    public native void sendNetworkDisconnected();
    public native String getName();
    public native boolean isLeader();

    protected void populateDefaultProperties(long nativeAboutDataHandle) {
        populateDefaultProperties(new AboutData(nativeAboutDataHandle));
    }

    @Override
    protected native void createNativeObject();

    @Override
    protected native void destroyNativeObject();
}

