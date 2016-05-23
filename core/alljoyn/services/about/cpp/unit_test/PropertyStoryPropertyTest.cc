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
#include <gtest/gtest.h>
#include <alljoyn/MsgArg.h>
#include <alljoyn/about/PropertyStoreProperty.h>

using namespace ajn;
using namespace ajn::services;

TEST(PropertyStorePropertyTest, constructor_one_param) {
    PropertyStoreProperty prop("Foo");
    EXPECT_STREQ("Foo", prop.getPropertyName().c_str());
    EXPECT_TRUE(prop.getIsPublic());
    EXPECT_FALSE(prop.getIsWritable());
    EXPECT_TRUE(prop.getIsAnnouncable());
    EXPECT_STREQ("", prop.getLanguage().c_str());
}

TEST(PropertyStorePropertyTest, constructor_two_param) {
    MsgArg arg("s", "TestMsg");
    PropertyStoreProperty prop("Foo", arg);
    EXPECT_STREQ("Foo", prop.getPropertyName().c_str());
    EXPECT_TRUE(prop.getIsPublic());
    EXPECT_FALSE(prop.getIsWritable());
    EXPECT_TRUE(prop.getIsAnnouncable());
    EXPECT_STREQ("", prop.getLanguage().c_str());
    MsgArg out = prop.getPropertyValue();
    const char* outStr;
    out.Get("s", &outStr);
    EXPECT_STREQ("TestMsg", outStr);
}

TEST(PropertyStorePropertyTest, constructor_five_param) {
    MsgArg arg("s", "TestMsg");
    PropertyStoreProperty prop("Foo", arg, false, true, false);
    EXPECT_STREQ("Foo", prop.getPropertyName().c_str());
    EXPECT_FALSE(prop.getIsPublic());
    EXPECT_TRUE(prop.getIsWritable());
    EXPECT_FALSE(prop.getIsAnnouncable());
    EXPECT_STREQ("", prop.getLanguage().c_str());
    MsgArg out = prop.getPropertyValue();
    const char* outStr;
    out.Get("s", &outStr);
    EXPECT_STREQ("TestMsg", outStr);
}

TEST(PropertyStorePropertyTest, constructor_six_param) {
    MsgArg arg("s", "TestMsg");
    PropertyStoreProperty prop("Foo", arg, "es", true, true, true);
    EXPECT_STREQ("Foo", prop.getPropertyName().c_str());
    EXPECT_TRUE(prop.getIsPublic());
    EXPECT_TRUE(prop.getIsWritable());
    EXPECT_TRUE(prop.getIsAnnouncable());
    EXPECT_STREQ("es", prop.getLanguage().c_str());
    MsgArg out = prop.getPropertyValue();
    const char* outStr;
    out.Get("s", &outStr);
    EXPECT_STREQ("TestMsg", outStr);
}


TEST(PropertyStorePropertyTest, setFlags) {
    PropertyStoreProperty prop("Foo");

    prop.setFlags(false, true, false);
    EXPECT_FALSE(prop.getIsPublic());
    EXPECT_TRUE(prop.getIsWritable());
    EXPECT_FALSE(prop.getIsAnnouncable());
}

TEST(PropertyStorePropertyTest, setLanguage) {
    PropertyStoreProperty prop("Foo");

    prop.setLanguage("fr");
    EXPECT_STREQ("fr", prop.getLanguage().c_str());
}

TEST(PropertyStorePropertyTest, setIsPublic) {
    PropertyStoreProperty prop("Foo");

    prop.setIsPublic(false);
    EXPECT_FALSE(prop.getIsPublic());
}


TEST(PropertyStorePropertyTest, setIsWritable) {
    PropertyStoreProperty prop("Foo");

    prop.setIsWritable(true);
    EXPECT_TRUE(prop.getIsWritable());
}

TEST(PropertyStorePropertyTest, setIsAnnouncable) {
    PropertyStoreProperty prop("Foo");

    prop.setIsAnnouncable(false);
    EXPECT_FALSE(prop.getIsAnnouncable());
}

// Why is it the only way to set the value is through a constructor?
