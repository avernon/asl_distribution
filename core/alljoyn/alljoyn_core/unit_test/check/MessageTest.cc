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

#include <alljoyn/Message.h>

/* Header files included for Google Test Framework */
#include <gtest/gtest.h>
#include "../ajTestCommon.h"

using namespace std;
using namespace qcc;
using namespace ajn;

class _TestMessage : public _Message {
  public:
    _TestMessage(BusAttachment& bus, const HeaderFields& hdrFields) : _Message(bus, hdrFields) { }
};
typedef ManagedObj<_TestMessage> TestMessage;

/* ASACORE-1111 */
TEST(MessageTest, GetNullHeaderFieldsReturnsEmptyString)
{
    BusAttachment bus(NULL);
    HeaderFields hdrFields;
    hdrFields.field[ALLJOYN_HDR_FIELD_SIGNATURE].Set("g", NULL);
    hdrFields.field[ALLJOYN_HDR_FIELD_PATH].Set("o", NULL);
    hdrFields.field[ALLJOYN_HDR_FIELD_INTERFACE].Set("s", NULL);
    hdrFields.field[ALLJOYN_HDR_FIELD_MEMBER].Set("s", NULL);
    hdrFields.field[ALLJOYN_HDR_FIELD_SENDER].Set("s", NULL);
    hdrFields.field[ALLJOYN_HDR_FIELD_DESTINATION].Set("s", NULL);
    TestMessage msg(bus, hdrFields);

    EXPECT_STREQ("", msg->GetSignature());
    EXPECT_STREQ("", msg->GetObjectPath());
    EXPECT_STREQ("", msg->GetInterface());
    EXPECT_STREQ("", msg->GetMemberName());
    EXPECT_STREQ("", msg->GetSender());
    EXPECT_STREQ("", msg->GetDestination());
}
