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

package org.alljoyn.validation.testing.suites.eventsactions;

import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.ifaces.AllSeenIntrospectable;
import org.alljoyn.validation.framework.ValidationTestCase;
import org.alljoyn.validation.framework.ValidationTestSuite;
import org.alljoyn.validation.testing.suites.BaseTestSuiteManager;
import org.alljoyn.validation.testing.utils.about.AboutAnnouncementDetails;
import org.alljoyn.validation.testing.utils.log.Logger;
import org.alljoyn.validation.testing.utils.log.LoggerFactory;

public class EventsActionsTestSuiteManager extends BaseTestSuiteManager implements ValidationTestSuite
{

    private static final String TAG = "EventsActionsTestSuiteManager";
    private static final Logger logger = LoggerFactory.getLogger(TAG);

    /**
     * @see org.alljoyn.validation.testing.suites.BaseTestSuiteManager#getTestSuiteClass()
     */
    @Override
    protected Class<? extends ValidationTestCase> getTestSuiteClass()
    {

        return EventsActionsTestSuite.class;
    }

    /**
     * @see org.alljoyn.validation.testing.suites.BaseTestSuiteManager#addTestGroupForApplication(org.alljoyn.validation.testing.utils.about.AboutAnnouncementDetails)
     */
    @Override
    protected boolean addTestGroupForApplication(AboutAnnouncementDetails aboutAnnouncement)
    {

        logger.info("Received announcement deviceId: '%s', appId: '%s', busName: '%s'", aboutAnnouncement.getDeviceId(), aboutAnnouncement.getAppId(),
                aboutAnnouncement.getServiceName());

        // Retrieve the AJ name of the introspection interface
        BusInterface ifaceName = AllSeenIntrospectable.class.getAnnotation(BusInterface.class);
        String ajIfaceName = ifaceName.name();

        return aboutAnnouncement.supportsInterface(ajIfaceName);
    }
}
