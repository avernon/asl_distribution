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
package org.alljoyn.validation.testing.utils.log;

import static org.junit.Assert.assertEquals;

import org.alljoyn.validation.testing.utils.log.LoggerProvider;
import org.alljoyn.validation.testing.utils.log.LoggerProviderLoader;
import org.alljoyn.validation.testing.utils.log.android.AndroidLoggerProvider;
import org.junit.Test;

public class LoggerProviderLoaderTest
{

    @Test
    public void testLoadLoggerProvider() throws InstantiationException, IllegalAccessException, ClassNotFoundException
    {
        LoggerProviderLoader loggerProviderLoader = new LoggerProviderLoader();
        LoggerProvider loggerProvider = loggerProviderLoader.loadLoggerProvider();
        assertEquals(AndroidLoggerProvider.class, loggerProvider.getClass());
    }

    @Test(expected = RuntimeException.class)
    public void testLoadLoggerProviderThrowsException() throws InstantiationException, IllegalAccessException, ClassNotFoundException
    {
        LoggerProviderLoader loggerProviderLoader = new LoggerProviderLoader()
        {
            @Override
            LoggerProvider loadAndroidLoggerProvider() throws InstantiationException, IllegalAccessException, ClassNotFoundException
            {
                throw new ClassNotFoundException();
            }
        };
        LoggerProvider loggerProvider = loggerProviderLoader.loadLoggerProvider();
        assertEquals(AndroidLoggerProvider.class, loggerProvider.getClass());
    }

}
