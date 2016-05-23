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

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.alljoyn.about.AboutKeys;
import org.alljoyn.services.common.PropertyStore;
import org.alljoyn.services.common.PropertyStoreException;

public class ConfigPropertyStoreImpl implements PropertyStore
{
    Map<String, Object> configDataMap = new HashMap<String, Object>();
    List<String> supportedLanguages = new ArrayList<String>();
    String defaultLang = "en";

    public String getDefaultLang()
    {
        return defaultLang;
    }

    public void setDefaultLang(String defaultLang)
    {
        this.defaultLang = defaultLang;
    }

    public ConfigPropertyStoreImpl()
    {
        configDataMap.put(AboutKeys.ABOUT_DEFAULT_LANGUAGE, "en");
        configDataMap.put(AboutKeys.ABOUT_DEVICE_NAME, "DUTSimulator");
        supportedLanguages.add(getDefaultLang());
    }

    @Override
    public void readAll(String languageTag, Filter filter, Map<String, Object> dataMap) throws PropertyStoreException
    {
        if ("".equals(languageTag))
        {
            languageTag = getDefaultLang();
        }

        if (supportedLanguages.contains(languageTag))
        {
            dataMap.putAll(configDataMap);
        }
        else
        {
            throw new PropertyStoreException(PropertyStoreException.UNSUPPORTED_LANGUAGE);
        }

    }

    @Override
    public void update(String key, String languageTag, Object newValue) throws PropertyStoreException
    {
        if ("".equals(languageTag))
        {
            languageTag = getDefaultLang();
        }

        if (supportedLanguages.contains(languageTag))
        {
            configDataMap.remove(key);
            configDataMap.put(key, newValue);
        }
        else
        {
            throw new PropertyStoreException(PropertyStoreException.UNSUPPORTED_LANGUAGE);
        }
    }

    @Override
    public void reset(String key, String languageTag) throws PropertyStoreException
    {
    }

    @Override
    public void resetAll() throws PropertyStoreException
    {
    }
}