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

import static org.alljoyn.validation.testing.utils.audio.AudioServiceInterfaceName.Stream;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;

import org.alljoyn.validation.framework.ValidationTestCase;
import org.alljoyn.validation.framework.ValidationTestGroup;
import org.alljoyn.validation.framework.ValidationTestSuite;
import org.alljoyn.validation.testing.suites.BaseTestSuiteManager;
import org.alljoyn.validation.testing.utils.about.AboutAnnouncementDetails;

public class AudioTestSuiteManager extends BaseTestSuiteManager implements ValidationTestSuite
{
    @Override
    protected Class<? extends ValidationTestCase> getTestSuiteClass()
    {
        return AudioTestSuite.class;
    }

    @Override
    protected List<ValidationTestGroup> createTestGroupsWithPathInformation(AboutAnnouncementDetails aboutAnnouncement)
    {
        Set<String> objectPaths = aboutAnnouncement.getObjectPaths(Stream.getValue());
        List<ValidationTestGroup> validationTestGroups = new ArrayList<ValidationTestGroup>();

        for (String objectPath : objectPaths)
        {
            ValidationTestGroup validationTestGroup = createTestGroup(aboutAnnouncement);
            validationTestGroup.setObjectPath(objectPath);
            validationTestGroups.add(validationTestGroup);
        }

        return validationTestGroups;
    }

    @Override
    protected boolean addTestGroupForApplication(AboutAnnouncementDetails aboutAnnouncement)
    {
        return aboutAnnouncement.supportsInterface(Stream.getValue());
    }

    @Override
    protected boolean addTestGroupWithPathInformation()
    {
        return true;
    }
}