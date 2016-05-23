/*******************************************************************************
 *  Copyright AllSeen Alliance. All rights reserved.
 *
 *     Contributed by Qualcomm Connected Experiences, Inc.,
 *     with authorization from the AllSeen Alliance, Inc.
 *     
 *     Licensed under the Apache License, Version 2.0 (the "License");
 *     you may not use this file except in compliance with the License.
 *     You may obtain a copy of the License at
 *     
 *         http://www.apache.org/licenses/LICENSE-2.0
 *     
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 *     
 *     Pursuant to Section 1 of the License, the work of authorship constituting
 *     a Work and any Contribution incorporated in the Work shall mean only that
 *     Contributor's code submissions authored by that Contributor.  Any rights
 *     granted under the License are conditioned upon acceptance of these
 *     clarifications.
 *******************************************************************************/
package org.alljoyn.validation.simulator.config;

import java.util.HashMap;
import java.util.Map;

import org.alljoyn.about.AboutKeys;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.config.server.ConfigChangeListener;
import org.alljoyn.services.common.utils.TransportUtil;
import org.alljoyn.validation.simulator.DUTSimulator;

public class DUTSimulatorConfigChangeListener implements ConfigChangeListener
{
    private DUTSimulator dutSimulator;

    public DUTSimulatorConfigChangeListener(DUTSimulator dutSimulator)
    {
        this.dutSimulator = dutSimulator;
    }

    @Override
    public void onConfigChanged(Map<String, Variant> newConfiguration, String languageTag)
    {
        try
        {
            updateVariantMapAndAnnounce(newConfiguration);
        }
        catch (BusException e)
        {
            throw new RuntimeException(e);
        }

    }

    private void updateVariantMapAndAnnounce(Map<String, Variant> newConfiguration) throws BusException
    {
        dutSimulator.getVariantAboutMap().putAll(newConfiguration);
        dutSimulator.getAnnouncementEmmitter().Announce((short) dutSimulator.getAboutInterface().getVersion(), dutSimulator.CONTACT_PORT,
                dutSimulator.getAboutInterface().GetObjectDescription(), dutSimulator.getVariantAboutMap());
    }

    @Override
    public void onResetConfiguration(String language, String[] fieldNames)
    {
        Map<String, Object> objectMap = new HashMap<String, Object>();
        for (String fieldName : fieldNames)
        {
            if (fieldName.equals(AboutKeys.ABOUT_DEVICE_NAME))
            {
                objectMap.put(fieldName, dutSimulator.getDeviceDetails().getDeviceName());
            }
        }
        Map<String, Variant> newConfiguration = TransportUtil.toVariantMap(objectMap);
        try
        {
            updateVariantMapAndAnnounce(newConfiguration);
        }
        catch (BusException e)
        {
            throw new RuntimeException(e);
        }
    }

}
