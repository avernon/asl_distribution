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
package org.alljoyn.validation.testing.utils;

import org.alljoyn.validation.framework.ValidationBaseTestCase;
import org.alljoyn.validation.testing.utils.log.Logger;
import org.alljoyn.validation.testing.utils.log.LoggerFactory;

public class BaseTestSuite extends ValidationBaseTestCase
{
    private static final String ABOUT_ANNOUNCEMENT_TIMEOUT_PARAMETER_NAME = "aboutAnnouncementTimeoutInSeconds";
    private static final String TAG = "BaseTestSuite";
    private static final Logger logger = LoggerFactory.getLogger(TAG);
    private static final long DEFAULT_ANNOUNCEMENT_TIMEOUT_IN_SECONDS = 60;

    protected long determineAboutAnnouncementTimeout()
    {
        String aboutAnnouncementTimeoutProvided = (String) getValidationTestContext().getTestParameter(ABOUT_ANNOUNCEMENT_TIMEOUT_PARAMETER_NAME);
        long aboutAnnouncementTimeout = DEFAULT_ANNOUNCEMENT_TIMEOUT_IN_SECONDS;

        try
        {
            if (aboutAnnouncementTimeoutProvided != null && !aboutAnnouncementTimeoutProvided.isEmpty())
            {
                logger.debug("About announcement timeout provided: %s seconds", aboutAnnouncementTimeoutProvided);
                aboutAnnouncementTimeout = Long.parseLong(aboutAnnouncementTimeoutProvided);

                if (aboutAnnouncementTimeout < 0)
                {
                    logger.debug("Invalid About announcement timeout value provided");
                    aboutAnnouncementTimeout = DEFAULT_ANNOUNCEMENT_TIMEOUT_IN_SECONDS;
                }
            }
        }
        catch (Exception exception)
        {
            logger.debug("Invalid About announcement timeout value provided");
            aboutAnnouncementTimeout = DEFAULT_ANNOUNCEMENT_TIMEOUT_IN_SECONDS;
        }

        logger.debug("Running test case using About announcement timeout: %s seconds", aboutAnnouncementTimeout);

        return aboutAnnouncementTimeout;
    }
}
