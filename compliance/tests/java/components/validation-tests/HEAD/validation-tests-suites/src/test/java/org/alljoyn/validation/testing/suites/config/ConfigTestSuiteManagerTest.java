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
package org.alljoyn.validation.testing.suites.config;

import static org.alljoyn.validation.framework.ValidationTestItem.DEFAULT_TEST_TIMEOUT_IN_MILLISECONDS;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import static org.mockito.Mockito.when;

import java.util.ArrayList;
import java.util.List;

import org.alljoyn.config.transport.ConfigTransport;
import org.alljoyn.services.common.BusObjectDescription;
import org.alljoyn.validation.framework.AboutAnnouncement;
import org.alljoyn.validation.framework.AllJoynAnnouncedDevice;
import org.alljoyn.validation.framework.ValidationTestGroup;
import org.alljoyn.validation.framework.ValidationTestItem;
import org.junit.Before;
import org.junit.Test;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;

public class ConfigTestSuiteManagerTest
{
    private ConfigTestSuiteManager configTestSuiteManager;
    @Mock
    private AllJoynAnnouncedDevice allJoynAnnouncedDevice;
    @Mock
    private AboutAnnouncement firstAboutAnnouncement;
    @Mock
    private AboutAnnouncement secondAboutAnnouncement;

    @Before
    public void setup()
    {
        MockitoAnnotations.initMocks(this);
        configTestSuiteManager = new ConfigTestSuiteManager();

        BusObjectDescription[] supportsConfig = new BusObjectDescription[1];
        BusObjectDescription bod = new BusObjectDescription();
        bod.interfaces = new String[]
        { ConfigTransport.INTERFACE_NAME };
        bod.path = "/Config";
        supportsConfig[0] = bod;

        when(firstAboutAnnouncement.getServiceName()).thenReturn("ServiceName1");
        when(secondAboutAnnouncement.getServiceName()).thenReturn("ServiceName2");
        when(firstAboutAnnouncement.getObjectDescriptions()).thenReturn(supportsConfig);
        when(secondAboutAnnouncement.getObjectDescriptions()).thenReturn(supportsConfig);
    }

    @Test
    public void getApplicableTestsReturnsEmptyListWhenNoTestExists()
    {
        when(allJoynAnnouncedDevice.getAnnouncements()).thenReturn(new ArrayList<AboutAnnouncement>());
        List<ValidationTestGroup> testGroups = configTestSuiteManager.getApplicableTests(allJoynAnnouncedDevice);

        assertTrue(testGroups.isEmpty());
    }

    @Test
    public void getApplicableTests()
    {
        List<AboutAnnouncement> aboutAnnouncements = new ArrayList<AboutAnnouncement>();
        aboutAnnouncements.add(firstAboutAnnouncement);
        aboutAnnouncements.add(secondAboutAnnouncement);
        when(allJoynAnnouncedDevice.getAnnouncements()).thenReturn(aboutAnnouncements);
        List<ValidationTestGroup> testGroups = configTestSuiteManager.getApplicableTests(allJoynAnnouncedDevice);

        assertEquals(2, testGroups.size());
        validateValidationTestGroup(testGroups.get(0), firstAboutAnnouncement);
        validateValidationTestGroup(testGroups.get(1), secondAboutAnnouncement);
    }

    private void validateValidationTestGroup(ValidationTestGroup validationTestGroup, AboutAnnouncement aboutAnnouncement)
    {
        assertEquals("Config-v1", validationTestGroup.getTestGroupId());
        assertEquals(aboutAnnouncement.getServiceName(), validationTestGroup.getAboutAnnouncement().getServiceName());
        assertNull(validationTestGroup.getInterfaceName());
        assertNull(validationTestGroup.getObjectPath());

        validateValidationTestItems(validationTestGroup);
    }

    private void validateValidationTestItems(ValidationTestGroup validationTestGroup)
    {
        // expected test order:
        int[] testIdx =
        { 1, 2, 4, 5, 6, 7, 8, 12, 13, 14, 15, 16, 19, 20, 21, 22, 24, 25, 26, 27, 29, 30, 31, 32, 33, 34, 35 };

        List<ValidationTestItem> validationTestItems = validationTestGroup.getTestItems();
        assertEquals(testIdx.length, validationTestItems.size());
        for (int i = 0; i < testIdx.length; i++)
        {
            validateValidationTestItem(validationTestItems.get(i), validationTestGroup, String.format("Config-v1-%02d", testIdx[i]));
        }

    }

    private void validateValidationTestItem(ValidationTestItem validationTestItem, ValidationTestGroup validationTestGroup, String testCaseId)
    {
        assertEquals(validationTestGroup, validationTestItem.getTestGroup());
        assertEquals(testCaseId, validationTestItem.getTestCaseId());
        assertEquals(ConfigTestSuite.class.getName(), validationTestItem.getClassName());
        assertEquals(DEFAULT_TEST_TIMEOUT_IN_MILLISECONDS, validationTestItem.getTimeoutInMilliseconds());
        assertTrue(validationTestItem.isInitiallySelected());
   }

}