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
package org.alljoyn.validation.testing.suites.audio;

import static org.alljoyn.validation.framework.ValidationTestItem.DEFAULT_TEST_TIMEOUT_IN_MILLISECONDS;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import static org.mockito.Mockito.when;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import org.alljoyn.about.transport.AboutTransport;
import org.alljoyn.services.common.BusObjectDescription;
import org.alljoyn.validation.framework.AboutAnnouncement;
import org.alljoyn.validation.framework.AllJoynAnnouncedDevice;
import org.alljoyn.validation.framework.ValidationTestGroup;
import org.alljoyn.validation.framework.ValidationTestItem;
import org.alljoyn.validation.testing.utils.about.AboutAnnouncementDetails;
import org.junit.Before;
import org.junit.Test;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;

public class AudioTestSuiteManagerTest
{
    private static final String OBJECT_PATH = "OBJECT_PATH";
    private static final String STREAM_INTERFACE_NAME = "org.alljoyn.Stream";
    private AudioTestSuiteManager audioTestSuiteManager;
    @Mock
    private AllJoynAnnouncedDevice allJoynAnnouncedDevice;
    @Mock
    private AboutAnnouncementDetails firstAboutAnnouncement;
    @Mock
    private AboutAnnouncementDetails secondAboutAnnouncement;
    @Mock
    private AboutAnnouncementDetails thirdAboutAnnouncement;

    @Before
    public void setup()
    {
        MockitoAnnotations.initMocks(this);
        Set<String> objectPaths = new HashSet<String>();
        objectPaths.add(OBJECT_PATH);
        when(firstAboutAnnouncement.supportsInterface(STREAM_INTERFACE_NAME)).thenReturn(true);
        when(firstAboutAnnouncement.getObjectPaths(STREAM_INTERFACE_NAME)).thenReturn(objectPaths);
        when(secondAboutAnnouncement.supportsInterface(STREAM_INTERFACE_NAME)).thenReturn(true);
        when(secondAboutAnnouncement.getObjectPaths(STREAM_INTERFACE_NAME)).thenReturn(objectPaths);
        audioTestSuiteManager = new AudioTestSuiteManager();

        when(firstAboutAnnouncement.getServiceName()).thenReturn("ServiceName1");
        when(secondAboutAnnouncement.getServiceName()).thenReturn("ServiceName2");
        when(thirdAboutAnnouncement.getServiceName()).thenReturn("ServiceName2");

        BusObjectDescription[] supportsStream = new BusObjectDescription[1];
        BusObjectDescription bod = new BusObjectDescription();
        bod.interfaces = new String[]
        { STREAM_INTERFACE_NAME };
        bod.path = OBJECT_PATH;
        supportsStream[0] = bod;

        when(firstAboutAnnouncement.getObjectDescriptions()).thenReturn(supportsStream);
        when(secondAboutAnnouncement.getObjectDescriptions()).thenReturn(supportsStream);

        BusObjectDescription[] supportsAbout = new BusObjectDescription[1];
        bod = new BusObjectDescription();
        bod.interfaces = new String[]
        { AboutTransport.INTERFACE_NAME };
        bod.path = "/About";
        supportsAbout[0] = bod;
        when(thirdAboutAnnouncement.getObjectDescriptions()).thenReturn(supportsAbout);

    }

    @Test
    public void getApplicableTestsReturnsEmptyListWhenNoTestExists()
    {
        when(allJoynAnnouncedDevice.getAnnouncements()).thenReturn(new ArrayList<AboutAnnouncement>());
        List<ValidationTestGroup> testGroups = audioTestSuiteManager.getApplicableTests(allJoynAnnouncedDevice);

        assertTrue(testGroups.isEmpty());
    }

    @Test
    public void getApplicableTests()
    {
        List<AboutAnnouncement> aboutAnnouncements = new ArrayList<AboutAnnouncement>();
        aboutAnnouncements.add(firstAboutAnnouncement);
        aboutAnnouncements.add(secondAboutAnnouncement);
        aboutAnnouncements.add(thirdAboutAnnouncement);
        when(allJoynAnnouncedDevice.getAnnouncements()).thenReturn(aboutAnnouncements);
        List<ValidationTestGroup> testGroups = audioTestSuiteManager.getApplicableTests(allJoynAnnouncedDevice);

        assertEquals(2, testGroups.size());
        validateValidationTestGroup(testGroups.get(0), firstAboutAnnouncement);
        validateValidationTestGroup(testGroups.get(1), secondAboutAnnouncement);
    }

    private void validateValidationTestGroup(ValidationTestGroup validationTestGroup, AboutAnnouncementDetails aboutAnnouncement)
    {
        assertEquals("Audio-v1", validationTestGroup.getTestGroupId());
        assertEquals(aboutAnnouncement.getServiceName(), validationTestGroup.getAboutAnnouncement().getServiceName());
        assertNull(validationTestGroup.getInterfaceName());
        assertEquals(OBJECT_PATH, validationTestGroup.getObjectPath());
        validateValidationTestItems(validationTestGroup);
    }

    private void validateValidationTestItems(ValidationTestGroup validationTestGroup)
    {
        int[] testIdx =
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 25, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 26, 27, 28 };

        List<ValidationTestItem> validationTestItems = validationTestGroup.getTestItems();
        assertEquals(testIdx.length, validationTestItems.size());
        for (int i = 0; i < testIdx.length; i++)
        {
            validateValidationTestItem(validationTestItems.get(i), validationTestGroup, String.format("Audio-v1-%02d", testIdx[i]));
        }
    }

    private void validateValidationTestItem(ValidationTestItem validationTestItem, ValidationTestGroup validationTestGroup, String testCaseId)
    {
        assertEquals(validationTestGroup, validationTestItem.getTestGroup());
        assertEquals(testCaseId, validationTestItem.getTestCaseId());
        assertEquals(AudioTestSuite.class.getName(), validationTestItem.getClassName());
        assertEquals(DEFAULT_TEST_TIMEOUT_IN_MILLISECONDS, validationTestItem.getTimeoutInMilliseconds());
        assertTrue(validationTestItem.isInitiallySelected());
    }
}