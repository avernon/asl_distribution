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
#include <qcc/platform.h>

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <vector>

#include <qcc/String.h>
#include <qcc/Util.h>

#include <alljoyn/BusAttachment.h>
#include <alljoyn/DBusStd.h>
#include <alljoyn/AllJoynStd.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/MsgArg.h>
#include <alljoyn/version.h>

#include <alljoyn/Status.h>

/* Header files included for Google Test Framework */
#include <gtest/gtest.h>
#include "ajTestCommon.h"
//#include <qcc/time.h>

using namespace std;
using namespace qcc;
using namespace ajn;
class AlljoynObjTest : public testing::Test {
  public:
    BusAttachment gbus;

    AlljoynObjTest() : gbus("testAlljoynObj", false) { };

    virtual void SetUp() {
        QStatus status = ER_OK;
        status = gbus.Start();
        ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
        status = gbus.Connect(getConnectArg().c_str());
        ASSERT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
    }

    virtual void TearDown() {
        gbus.Stop();
        gbus.Join();
    }

};

TEST_F(AlljoynObjTest, ReloadConfig) {
    QStatus status = ER_OK;
    bool reloaded = false;

    const ProxyBusObject& alljoynObj = gbus.GetAllJoynProxyObj();

    Message reply(gbus);

    status = alljoynObj.MethodCall(org::alljoyn::Bus::InterfaceName,
                                   "ReloadConfig",
                                   NULL,
                                   0,
                                   reply);

    ASSERT_EQ(ER_OK, status) << "  AlljoynObj::ReloadConfig: " << QCC_StatusText(status);



    status = reply->GetArgs("b", &reloaded);

    ASSERT_EQ(ER_OK, status) << "  AlljoynObj::GetReturn: " << QCC_StatusText(status);

    ASSERT_EQ(true, reloaded) << "  Reload fail! ";

}

TEST_F(AlljoynObjTest, DenyOwnName) {
    QStatus status = ER_OK;
    /* Preload deny own gov.a rule  */

    status = gbus.RequestName("gov.a", DBUS_NAME_FLAG_REPLACE_EXISTING | DBUS_NAME_FLAG_DO_NOT_QUEUE);
    cout << "RequestName gov.a should fail " << endl;
    ASSERT_NE(ER_OK, status) << " Unexpected ok to request gov.a as expected " << QCC_StatusText(status);

    status = gbus.RequestName("gov.b", DBUS_NAME_FLAG_REPLACE_EXISTING | DBUS_NAME_FLAG_DO_NOT_QUEUE);
    cout << "RequestName gov.b should succeed " << endl;
    ASSERT_EQ(ER_OK, status) << " Unexpected fail to request gov.b " << QCC_StatusText(status);


}
