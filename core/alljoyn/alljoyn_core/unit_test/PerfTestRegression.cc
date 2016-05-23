/**
 * @file
 * This program tests the basic features of Alljoyn.It uses google test as the test
 * automation framework.
 */
/******************************************************************************
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
 ******************************************************************************/

#include "ServiceSetup.h"
#include "ServiceTestObject.h"
#include "ajTestCommon.h"

#include <qcc/time.h>
/* Header files included for Google Test Framework */
#include <gtest/gtest.h>

TEST(PerfTestRegression, Security_ALLJOYN_294_AddLogonEntry_Without_EnablePeerSecurity)
{
    Environ*env = qcc::Environ::GetAppEnviron();
    qcc::String clientArgs = env->Find("BUS_ADDRESS", ajn::getConnectArg().c_str());

    /* Create a Bus Attachment Object */
    BusAttachment* serviceBus = new BusAttachment("ALLJOYN-294", true);
    ASSERT_TRUE(serviceBus != NULL);
    serviceBus->Start();

    QStatus status = serviceBus->Connect(clientArgs.c_str());
    ASSERT_EQ(ER_OK, status);

    status = serviceBus->AddLogonEntry("ALLJOYN_SRP_LOGON", "sleepy", "123456");
    ASSERT_EQ(status, ER_BUS_KEYSTORE_NOT_LOADED);

    status = serviceBus->AddLogonEntry("ALLJOYN_SRP_LOGON", "happy", "123456");
    ASSERT_EQ(status, ER_BUS_KEYSTORE_NOT_LOADED);

    /* Clean up msg bus */
    if (serviceBus) {
        BusAttachment* deleteMe = serviceBus;
        serviceBus = NULL;
        delete deleteMe;
    }
}
