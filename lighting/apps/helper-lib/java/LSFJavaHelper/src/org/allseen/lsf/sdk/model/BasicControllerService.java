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
package org.allseen.lsf.sdk.model;

import org.allseen.lsf.ControllerService;
import org.allseen.lsf.sdk.AboutData;
import org.allseen.lsf.sdk.LightingControllerConfiguration;
import org.allseen.lsf.sdk.RankAvailability;
import org.allseen.lsf.sdk.RankMobility;
import org.allseen.lsf.sdk.RankNodeType;
import org.allseen.lsf.sdk.RankPower;

public class BasicControllerService extends ControllerService {

    protected LightingControllerConfiguration controllerConfiguration;

    public BasicControllerService(LightingControllerConfiguration configuration) {
        controllerConfiguration = configuration;
    }

    public LightingControllerConfiguration getLightingControllerConfiguration() {
        return controllerConfiguration;
    }

    @Override
    public void populateDefaultProperties(AboutData aboutData) {
        controllerConfiguration.populateDefaultProperties(aboutData);
    }

    @Override
    public String getMacAddress(String generatedMacAddress) {
        return controllerConfiguration.getMacAddress(generatedMacAddress);
    }

    @Override
    public boolean isNetworkConnected() {
        return controllerConfiguration.isNetworkConnected();
    }

    @Override
    public RankMobility getRankMobility() {
        return controllerConfiguration.getRankMobility();
    }

    @Override
    public RankPower getRankPower() {
        return controllerConfiguration.getRankPower();
    }

    @Override
    public RankAvailability getRankAvailability() {
        return controllerConfiguration.getRankAvailability();
    }

    @Override
    public RankNodeType getRankNodeType() {
        return controllerConfiguration.getRankNodeType();
    }
}

