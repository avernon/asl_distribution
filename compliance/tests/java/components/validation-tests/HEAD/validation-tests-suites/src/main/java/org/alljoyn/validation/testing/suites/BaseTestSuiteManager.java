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
package org.alljoyn.validation.testing.suites;

import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import org.alljoyn.bus.BusException;
import org.alljoyn.validation.framework.AboutAnnouncement;
import org.alljoyn.validation.framework.AllJoynAnnouncedDevice;
import org.alljoyn.validation.framework.ValidationTestCase;
import org.alljoyn.validation.framework.ValidationTestGroup;
import org.alljoyn.validation.framework.ValidationTestItem;
import org.alljoyn.validation.framework.ValidationTestSuite;
import org.alljoyn.validation.framework.annotation.Disabled;
import org.alljoyn.validation.framework.annotation.ValidationSuite;
import org.alljoyn.validation.framework.annotation.ValidationTest;
import org.alljoyn.validation.testing.utils.ValidationTestComparator;
import org.alljoyn.validation.testing.utils.about.AboutAnnouncementDetails;
import org.alljoyn.validation.testing.utils.log.Logger;
import org.alljoyn.validation.testing.utils.log.LoggerFactory;

public abstract class BaseTestSuiteManager implements ValidationTestSuite
{
    private static final String TAG = "BaseTestSuiteManager";
    private static final Logger logger = LoggerFactory.getLogger(TAG);

    @Override
    public List<ValidationTestGroup> getApplicableTests(AllJoynAnnouncedDevice allJoynAnnouncedDevice)
    {
        List<ValidationTestGroup> testGroups = new ArrayList<ValidationTestGroup>();

        for (AboutAnnouncement aboutAnnouncement : allJoynAnnouncedDevice.getAnnouncements())
        {
            AboutAnnouncementDetails aboutAnnouncementDetails = getAboutAnnouncementDetails(aboutAnnouncement);

            if (addTestGroupForApplication(aboutAnnouncementDetails))
            {
                if (addTestGroupWithPathInformation())
                {
                    testGroups.addAll(createTestGroupsWithPathInformation(aboutAnnouncementDetails));
                }
                else
                {
                    testGroups.add(createTestGroup(aboutAnnouncementDetails));
                }
            }
        }

        return testGroups;
    }

    protected String getTestGroupIdFromClass(Class<? extends ValidationTestCase> clazz)
    {
        ValidationSuite validationSuite = clazz.getAnnotation(ValidationSuite.class);
        return validationSuite.name();
    }

    protected AboutAnnouncementDetails getAboutAnnouncementDetails(AboutAnnouncement aboutAnnouncement)
    {
        AboutAnnouncementDetails aboutAnnouncementDetails = new AboutAnnouncementDetails(aboutAnnouncement);
        try
        {
            aboutAnnouncementDetails.convertAboutMap();
        }
        catch (BusException e)
        {
            logger.debug("Exception convertingAboutMap", e);
        }
        return aboutAnnouncementDetails;
    }

    protected void addTestItemToGroup(ValidationTestGroup testGroup, String testCaseId, String testSuiteClassName, String methodName, boolean selectedInitially,
            long timeoutInMilliseconds)
    {
        ValidationTestItem testItem;
        if (timeoutInMilliseconds >= 0)
        {
            testItem = new ValidationTestItem(testCaseId, testSuiteClassName, methodName, timeoutInMilliseconds);
        }
        else
        {
            testItem = new ValidationTestItem(testCaseId, testSuiteClassName, methodName);
        }
        testItem.setInitiallySelected(selectedInitially);
        testGroup.addTestItem(testItem);
    }

    protected void addTestItemToGroup(ValidationTestGroup testGroup, String testCaseId, String testSuiteClassName, String methodName)
    {
        addTestItemToGroup(testGroup, testCaseId, testSuiteClassName, methodName, true, -1);
    }

    protected void addTestItemToGroup(ValidationTestGroup testGroup, String testCaseId, String testSuiteClassName, String methodName, long timeoutInMilliseconds)
    {
        ValidationTestItem testItem = new ValidationTestItem(testCaseId, testSuiteClassName, methodName, timeoutInMilliseconds);
        testGroup.addTestItem(testItem);
    }

    protected void addTestItemsToGroupFromAnnotations(ValidationTestGroup testGroup, Class<? extends ValidationTestCase> clazz)
    {
        Method[] methods = clazz.getMethods();
        List<Method> methodList = new ArrayList<Method>();
        for (Method method : methods)
        {
            ValidationTest validationTest = method.getAnnotation(ValidationTest.class);
            Disabled disabled = method.getAnnotation(Disabled.class);

            if ((validationTest != null) && (disabled == null) && method.getName().startsWith("test"))
            {
                methodList.add(method);
            }
        }

        Collections.sort(methodList, ValidationTestComparator.getInstance());

        for (Method method : methodList)
        {
            ValidationTest validationTest = method.getAnnotation(ValidationTest.class);
            Disabled disabled = method.getAnnotation(Disabled.class);

            if ((validationTest != null) && (disabled == null))
            {
                addTestItemToGroup(testGroup, validationTest.name(), clazz.getName(), method.getName(), isSelectedInitially(), validationTest.timeout());
            }
        }
    }

    protected boolean isSelectedInitially()
    {
        return true;
    }

    protected boolean addTestGroupWithPathInformation()
    {
        return false;
    }

    protected List<ValidationTestGroup> createTestGroupsWithPathInformation(AboutAnnouncementDetails aboutAnnouncement)
    {
        return null;
    }

    protected boolean addTestGroupForApplication(AboutAnnouncementDetails aboutAnnouncement)
    {
        return false;
    }

    protected ValidationTestGroup createTestGroup(AboutAnnouncementDetails aboutAnnouncement)
    {
        Class<? extends ValidationTestCase> clazz = getTestSuiteClass();

        ValidationTestGroup testGroup = new ValidationTestGroup(getTestGroupIdFromClass(clazz), aboutAnnouncement);

        addTestItemsToGroupFromAnnotations(testGroup, clazz);

        return testGroup;
    }

    protected abstract Class<? extends ValidationTestCase> getTestSuiteClass();

}
