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
#include <alljoyn/MsgArg.h>
#include <alljoyn/DBusStd.h>
#include <alljoyn/AllJoynStd.h>
#include <alljoyn/version.h>
#include <alljoyn/Status.h>

#include <gtest/gtest.h>
#include "ajTestCommon.h"
#include <alljoyn/Message.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/BusListener.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/ProxyBusObject.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/DBusStd.h>
#include <qcc/Debug.h>
#include <qcc/Thread.h>

using namespace std;
using namespace qcc;
using namespace ajn;

static const char* INTERFACE_NAME = "org.alljoyn.Bus.DescriptionInterface";
static const char* SERVICE_PATH = "/";

static const char* tags[] = { "en", "de" };
static const char* objId = "obj";
static const char* objDescription[] = { "This is the object", "DE: This is the object" };
static const char* ifcId = "ifc";
static const char* ifcDescription[] = { "This is the interface", "<bold>DE:</bold> This is the interface" };
static const char* propId = "prop";
static const char* namePropDescription[] = { "This is the actual name", "DE: This is the actual name" };

static const char* IntrospectWithDescriptionString1[] = {
    "<!DOCTYPE node PUBLIC \"-//allseen//DTD ALLJOYN Object Introspection 1.0//EN\"\n"
    "\"http://www.allseen.org/alljoyn/introspect-1.0.dtd\">\n"
    "<node>\n"
    "  <description>This is the object</description>\n"
    "  <node name=\"org\"/>\n"
    "  <interface name=\"org.alljoyn.Bus.DescriptionInterface\">\n"
    "    <description>This is the interface</description>\n"
    "    <property name=\"name\" type=\"s\" access=\"readwrite\">\n"
    "      <description>This is the actual name</description>\n"
    "    </property>\n"
    "  </interface>\n"
    "  <interface name=\"org.freedesktop.DBus.Introspectable\">\n"
    "    <method name=\"Introspect\">\n"
    "      <arg name=\"data\" type=\"s\" direction=\"out\"/>\n"
    "    </method>\n"
    "  </interface>\n"
    "  <interface name=\"org.allseen.Introspectable\">\n"
    "    <method name=\"GetDescriptionLanguages\">\n"
    "      <arg name=\"languageTags\" type=\"as\" direction=\"out\"/>\n"
    "    </method>\n"
    "    <method name=\"IntrospectWithDescription\">\n"
    "      <arg name=\"languageTag\" type=\"s\" direction=\"in\"/>\n"
    "      <arg name=\"data\" type=\"s\" direction=\"out\"/>\n"
    "    </method>\n"
    "    <annotation name=\"org.alljoyn.Bus.Secure\" value=\"off\"/>\n"
    "  </interface>\n"
    "</node>\n"
    ,

    "<!DOCTYPE node PUBLIC \"-//allseen//DTD ALLJOYN Object Introspection 1.0//EN\"\n"
    "\"http://www.allseen.org/alljoyn/introspect-1.0.dtd\">\n"
    "<node>\n"
    "  <description>DE: This is the object</description>\n"
    "  <node name=\"org\"/>\n"
    "  <interface name=\"org.alljoyn.Bus.DescriptionInterface\">\n"
    "    <description>&lt;bold&gt;DE:&lt;/bold&gt; This is the interface</description>\n"
    "    <property name=\"name\" type=\"s\" access=\"readwrite\">\n"
    "      <description>DE: This is the actual name</description>\n"
    "    </property>\n"
    "  </interface>\n"
    "  <interface name=\"org.freedesktop.DBus.Introspectable\">\n"
    "    <method name=\"Introspect\">\n"
    "      <arg name=\"data\" type=\"s\" direction=\"out\"/>\n"
    "    </method>\n"
    "  </interface>\n"
    "  <interface name=\"org.allseen.Introspectable\">\n"
    "    <method name=\"GetDescriptionLanguages\">\n"
    "      <arg name=\"languageTags\" type=\"as\" direction=\"out\"/>\n"
    "    </method>\n"
    "    <method name=\"IntrospectWithDescription\">\n"
    "      <arg name=\"languageTag\" type=\"s\" direction=\"in\"/>\n"
    "      <arg name=\"data\" type=\"s\" direction=\"out\"/>\n"
    "    </method>\n"
    "    <annotation name=\"org.alljoyn.Bus.Secure\" value=\"off\"/>\n"
    "  </interface>\n"
    "</node>\n"
};

static const char* IntrospectWithDescriptionString2[] = {
    "<!DOCTYPE node PUBLIC \"-//allseen//DTD ALLJOYN Object Introspection 1.0//EN\"\n"
    "\"http://www.allseen.org/alljoyn/introspect-1.0.dtd\">\n"
    "<node>\n"
    "  <node name=\"org\"/>\n"
    "  <interface name=\"org.alljoyn.Bus.DescriptionInterface\">\n"
    "    <description>This is the interface</description>\n"
    "    <property name=\"name\" type=\"s\" access=\"readwrite\">\n"
    "      <description>This is the actual name</description>\n"
    "    </property>\n"
    "  </interface>\n"
    "  <interface name=\"org.freedesktop.DBus.Introspectable\">\n"
    "    <method name=\"Introspect\">\n"
    "      <arg name=\"data\" type=\"s\" direction=\"out\"/>\n"
    "    </method>\n"
    "  </interface>\n"
    "  <interface name=\"org.allseen.Introspectable\">\n"
    "    <method name=\"GetDescriptionLanguages\">\n"
    "      <arg name=\"languageTags\" type=\"as\" direction=\"out\"/>\n"
    "    </method>\n"
    "    <method name=\"IntrospectWithDescription\">\n"
    "      <arg name=\"languageTag\" type=\"s\" direction=\"in\"/>\n"
    "      <arg name=\"data\" type=\"s\" direction=\"out\"/>\n"
    "    </method>\n"
    "    <annotation name=\"org.alljoyn.Bus.Secure\" value=\"off\"/>\n"
    "  </interface>\n"
    "</node>\n"
    ,

    "<!DOCTYPE node PUBLIC \"-//allseen//DTD ALLJOYN Object Introspection 1.0//EN\"\n"
    "\"http://www.allseen.org/alljoyn/introspect-1.0.dtd\">\n"
    "<node>\n"
    "  <node name=\"org\"/>\n"
    "  <interface name=\"org.alljoyn.Bus.DescriptionInterface\">\n"
    "    <description>&lt;bold&gt;DE:&lt;/bold&gt; This is the interface</description>\n"
    "    <property name=\"name\" type=\"s\" access=\"readwrite\">\n"
    "      <description>DE: This is the actual name</description>\n"
    "    </property>\n"
    "  </interface>\n"
    "  <interface name=\"org.freedesktop.DBus.Introspectable\">\n"
    "    <method name=\"Introspect\">\n"
    "      <arg name=\"data\" type=\"s\" direction=\"out\"/>\n"
    "    </method>\n"
    "  </interface>\n"
    "  <interface name=\"org.allseen.Introspectable\">\n"
    "    <method name=\"GetDescriptionLanguages\">\n"
    "      <arg name=\"languageTags\" type=\"as\" direction=\"out\"/>\n"
    "    </method>\n"
    "    <method name=\"IntrospectWithDescription\">\n"
    "      <arg name=\"languageTag\" type=\"s\" direction=\"in\"/>\n"
    "      <arg name=\"data\" type=\"s\" direction=\"out\"/>\n"
    "    </method>\n"
    "    <annotation name=\"org.alljoyn.Bus.Secure\" value=\"off\"/>\n"
    "  </interface>\n"
    "</node>\n"
};

static const char* IntrospectWithDescriptionString3[] = {
    "<!DOCTYPE node PUBLIC \"-//allseen//DTD ALLJOYN Object Introspection 1.0//EN\"\n"
    "\"http://www.allseen.org/alljoyn/introspect-1.0.dtd\">\n"
    "<node>\n"
    "  <description>This is the object</description>\n"
    "  <node name=\"org\"/>\n"
    "  <interface name=\"org.alljoyn.Bus.DescriptionInterface\">\n"
    "    <description>ifc</description>\n"
    "    <property name=\"name\" type=\"s\" access=\"readwrite\"/>\n"
    "  </interface>\n"
    "  <interface name=\"org.freedesktop.DBus.Introspectable\">\n"
    "    <method name=\"Introspect\">\n"
    "      <arg name=\"data\" type=\"s\" direction=\"out\"/>\n"
    "    </method>\n"
    "  </interface>\n"
    "  <interface name=\"org.allseen.Introspectable\">\n"
    "    <method name=\"GetDescriptionLanguages\">\n"
    "      <arg name=\"languageTags\" type=\"as\" direction=\"out\"/>\n"
    "    </method>\n"
    "    <method name=\"IntrospectWithDescription\">\n"
    "      <arg name=\"languageTag\" type=\"s\" direction=\"in\"/>\n"
    "      <arg name=\"data\" type=\"s\" direction=\"out\"/>\n"
    "    </method>\n"
    "    <annotation name=\"org.alljoyn.Bus.Secure\" value=\"off\"/>\n"
    "  </interface>\n"
    "</node>\n"
    ,

    "<!DOCTYPE node PUBLIC \"-//allseen//DTD ALLJOYN Object Introspection 1.0//EN\"\n"
    "\"http://www.allseen.org/alljoyn/introspect-1.0.dtd\">\n"
    "<node>\n"
    "  <description>DE: This is the object</description>\n"
    "  <node name=\"org\"/>\n"
    "  <interface name=\"org.alljoyn.Bus.DescriptionInterface\">\n"
    "    <description>ifc</description>\n"
    "    <property name=\"name\" type=\"s\" access=\"readwrite\"/>\n"
    "  </interface>\n"
    "  <interface name=\"org.freedesktop.DBus.Introspectable\">\n"
    "    <method name=\"Introspect\">\n"
    "      <arg name=\"data\" type=\"s\" direction=\"out\"/>\n"
    "    </method>\n"
    "  </interface>\n"
    "  <interface name=\"org.allseen.Introspectable\">\n"
    "    <method name=\"GetDescriptionLanguages\">\n"
    "      <arg name=\"languageTags\" type=\"as\" direction=\"out\"/>\n"
    "    </method>\n"
    "    <method name=\"IntrospectWithDescription\">\n"
    "      <arg name=\"languageTag\" type=\"s\" direction=\"in\"/>\n"
    "      <arg name=\"data\" type=\"s\" direction=\"out\"/>\n"
    "    </method>\n"
    "    <annotation name=\"org.alljoyn.Bus.Secure\" value=\"off\"/>\n"
    "  </interface>\n"
    "</node>\n"
};

class MyTranslator : public Translator {
  public:

    virtual ~MyTranslator() { }

    virtual size_t NumTargetLanguages() {
        return 2;
    }

    virtual void GetTargetLanguage(size_t index, qcc::String& ret) {
        ret.assign(tags[index]);
    }

    virtual const char* Translate(const char* sourceLanguage, const char* targetLanguage, const char* source) {
        const char* tag = (*targetLanguage == '\0') ? "en" : targetLanguage;
        size_t i = 0;

        if (0 == strcmp(tag, "en")) {
            i = 0;
        } else if (0 == strcmp(tag, "de")) {
            i = 1;
        } else {
            return NULL;
        }

        if (0 == strcmp(source, objId)) {
            return objDescription[i];
        }
        if (0 == strcmp(source, ifcId)) {
            return ifcDescription[i];
        }
        if (0 == strcmp(source, propId)) {
            return namePropDescription[i];
        }
        return NULL;
    }

};

class DescriptionObject : public BusObject {
  public:
    DescriptionObject(InterfaceDescription& intf, const char* path) :
        BusObject(path),
        prop_name("Default name")
    {
        EXPECT_EQ(ER_OK, AddInterface(intf));
        SetDescription("", objId);
    }

  private:
    qcc::String prop_name;

};

class DescriptionObjectNoTranslate : public BusObject {
  public:
    DescriptionObjectNoTranslate(InterfaceDescription& intf, const char* path) :
        BusObject(path),
        prop_name("Default name")
    {
        EXPECT_EQ(ER_OK, AddInterface(intf));
        SetDescription("", objId);
    }

  private:
    qcc::String prop_name;
};

class DescriptionObjectNoIntfTranslate : public BusObject {
  public:
    DescriptionObjectNoIntfTranslate(InterfaceDescription& intf, const char* path) :
        BusObject(path),
        prop_name("Default name")
    {
        EXPECT_EQ(ER_OK, AddInterface(intf));
        SetDescription("", objId);
        SetDescriptionTranslator(&translator);
    }

  private:
    qcc::String prop_name;
    MyTranslator translator;
};

class DescriptionTest : public::testing::Test {
  protected:
    DescriptionTest() {
        m_remoteObj = NULL;
        s_msgBusServer = NULL;
        s_msgBusClient = NULL;
        m_testObj = NULL;
    }

    virtual void SetUp() {
        ASSERT_TRUE((s_msgBusServer = new BusAttachment("serviceMyApp", true)) != NULL);
        ASSERT_EQ(ER_OK, s_msgBusServer->Start());

        // Client part
        ASSERT_TRUE((s_msgBusClient = new BusAttachment("clientMyApp", true)) != NULL);
        ASSERT_EQ(ER_OK, s_msgBusClient->Start());
        ASSERT_EQ(ER_OK, s_msgBusClient->Connect());
    }

    virtual void TearDown() {
        delete m_remoteObj;
        m_remoteObj = NULL;

        delete s_msgBusClient;
        s_msgBusClient = NULL;

        delete s_msgBusServer;
        s_msgBusServer = NULL;

        delete m_testObj;
        m_testObj = NULL;
    }

    BusAttachment* s_msgBusServer;
    BusAttachment* s_msgBusClient;
    BusObject* m_testObj;
    ProxyBusObject* m_remoteObj;

    void DescriptionLanguages(ProxyBusObject* remoteObj)
    {
        const InterfaceDescription* testIntf = remoteObj->GetInterface("org.allseen.Introspectable");
        ASSERT_TRUE(testIntf != 0);
        const InterfaceDescription::Member* member = testIntf->GetMember("GetDescriptionLanguages");
        ASSERT_TRUE(member != 0);

        MyTranslator translator;

        Message replyMsg(*s_msgBusClient);
        EXPECT_EQ(ER_OK, remoteObj->MethodCall("org.allseen.Introspectable", "GetDescriptionLanguages", NULL, 0, replyMsg));
        MsgArg* asArray;
        size_t las;
        EXPECT_EQ(ER_OK, replyMsg->GetArg(0)->Get("as", &las, &asArray));

        ASSERT_EQ(translator.NumTargetLanguages(), las) << "Number of langugages not as expected.";
        for (size_t i = 0; i < las; ++i) {
            char* pas;
            EXPECT_EQ(ER_OK, asArray[i].Get("s", &pas));
            ASSERT_STREQ(tags[1 - i], pas);
        }
    }

    void IntrospectWithDescription(ProxyBusObject* remoteObj, const char* languageTag, const char* IntrospectWithDescriptionStr)
    {
        const InterfaceDescription* testIntf = remoteObj->GetInterface("org.allseen.Introspectable");
        ASSERT_TRUE(testIntf != 0);
        const InterfaceDescription::Member* member = testIntf->GetMember("IntrospectWithDescription");
        ASSERT_TRUE(member != 0);

        MsgArg msgArg("s", languageTag);
        Message replyMsg(*s_msgBusClient);
        EXPECT_EQ(ER_OK, remoteObj->MethodCall("org.allseen.Introspectable", "IntrospectWithDescription", &msgArg, 1, replyMsg));
        char* str = NULL;
        EXPECT_EQ(ER_OK, replyMsg->GetArg(0)->Get("s", &str));
        ASSERT_STREQ(IntrospectWithDescriptionStr, str);
    }
};

TEST_F(DescriptionTest, IntrospectableDescriptionObject) {
    // Service part
    InterfaceDescription* intf = NULL;
    MyTranslator translator;
    EXPECT_EQ(ER_OK, s_msgBusServer->CreateInterface(INTERFACE_NAME, intf));
    ASSERT_TRUE(intf != NULL);

    intf->AddProperty("name", "s", PROP_ACCESS_RW);
    intf->SetDescriptionLanguage("");
    intf->SetDescription(ifcId);
    intf->SetPropertyDescription("name", propId);
    intf->SetDescriptionTranslator(&translator);
    intf->Activate();

    ASSERT_TRUE((m_testObj = new DescriptionObject(*intf, SERVICE_PATH)) != NULL);
    m_testObj->SetDescriptionTranslator(&translator);
    ASSERT_EQ(ER_OK, s_msgBusServer->RegisterBusObject(*m_testObj));
    ASSERT_EQ(ER_OK, s_msgBusServer->Connect());

    ASSERT_TRUE((m_remoteObj = new ProxyBusObject(*s_msgBusClient, s_msgBusServer->GetUniqueName().c_str(), SERVICE_PATH, 0)) != NULL);
    EXPECT_EQ(ER_OK, m_remoteObj->IntrospectRemoteObject());

    DescriptionLanguages(m_remoteObj);
    IntrospectWithDescription(m_remoteObj, "en", IntrospectWithDescriptionString1[0]);
    IntrospectWithDescription(m_remoteObj, "de", IntrospectWithDescriptionString1[1]);
}

TEST_F(DescriptionTest, IntrospectableDescriptionObjectNoTranslate) {
    // Service part
    MyTranslator translator;
    InterfaceDescription* intf = NULL;
    EXPECT_EQ(ER_OK, s_msgBusServer->CreateInterface(INTERFACE_NAME, intf));
    ASSERT_TRUE(intf != NULL);

    intf->AddProperty("name", "s", PROP_ACCESS_RW);
    intf->SetDescriptionLanguage("");
    intf->SetDescription(ifcId);
    intf->SetPropertyDescription("name", propId);
    intf->SetDescriptionTranslator(&translator);
    intf->Activate();

    ASSERT_TRUE((m_testObj = new DescriptionObjectNoTranslate(*intf, SERVICE_PATH)) != NULL);

    ASSERT_EQ(ER_OK, s_msgBusServer->RegisterBusObject(*m_testObj));
    ASSERT_EQ(ER_OK, s_msgBusServer->Connect());

    ASSERT_TRUE((m_remoteObj = new ProxyBusObject(*s_msgBusClient, s_msgBusServer->GetUniqueName().c_str(), SERVICE_PATH, 0)) != NULL);
    EXPECT_EQ(ER_OK, m_remoteObj->IntrospectRemoteObject());

    DescriptionLanguages(m_remoteObj);
    IntrospectWithDescription(m_remoteObj, "en", IntrospectWithDescriptionString2[0]);
    IntrospectWithDescription(m_remoteObj, "de", IntrospectWithDescriptionString2[1]);
}

TEST_F(DescriptionTest, IntrospectableDescriptionObjectNoIntfTranslate) {
    // Service part
    InterfaceDescription* intf = NULL;
    EXPECT_EQ(ER_OK, s_msgBusServer->CreateInterface(INTERFACE_NAME, intf));
    ASSERT_TRUE(intf != NULL);

    intf->AddProperty("name", "s", PROP_ACCESS_RW);
    intf->SetDescriptionLanguage("");
    intf->SetDescription(ifcId);
    intf->SetPropertyDescription("name", propId);
    intf->Activate();

    ASSERT_TRUE((m_testObj = new DescriptionObjectNoIntfTranslate(*intf, SERVICE_PATH)) != NULL);

    ASSERT_EQ(ER_OK, s_msgBusServer->RegisterBusObject(*m_testObj));
    ASSERT_EQ(ER_OK, s_msgBusServer->Connect());

    ASSERT_TRUE((m_remoteObj = new ProxyBusObject(*s_msgBusClient, s_msgBusServer->GetUniqueName().c_str(), SERVICE_PATH, 0)) != NULL);
    EXPECT_EQ(ER_OK, m_remoteObj->IntrospectRemoteObject());

    IntrospectWithDescription(m_remoteObj, "en", IntrospectWithDescriptionString3[0]);
    IntrospectWithDescription(m_remoteObj, "de", IntrospectWithDescriptionString3[1]);
}

TEST_F(DescriptionTest, SignalTypes)
{
    InterfaceDescription* intf = NULL;
    EXPECT_EQ(ER_OK, s_msgBusServer->CreateInterface(INTERFACE_NAME, intf));
    ASSERT_TRUE(intf != NULL);

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#if defined(QCC_OS_GROUP_WINDOWS)
#pragma warning(push)
#pragma warning(disable: 4996)
#endif
    ASSERT_EQ(ER_OK, intf->AddSignal("legacySignal", "s", NULL));

    intf->SetDescriptionLanguage("en");
    ASSERT_EQ(ER_OK, intf->AddSignal("legacyNonSessionlessSignal", "s", NULL));
    ASSERT_EQ(ER_OK, intf->SetMemberDescription("legacyNonSessionlessSignal", "legacy non-sessionless signal", false));

    ASSERT_EQ(ER_OK, intf->AddSignal("legacySessionlessSignal", "s", NULL));
    ASSERT_EQ(ER_OK, intf->SetMemberDescription("legacySessionlessSignal", "legacy sessionless signal", true));
#if defined(QCC_OS_GROUP_WINDOWS)
#pragma warning(pop)
#endif
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

    ASSERT_EQ(ER_OK, intf->AddSignal("sessioncastSignal", "s", NULL, MEMBER_ANNOTATE_SESSIONCAST));
    ASSERT_EQ(ER_OK, intf->AddSignal("sessionlessSignal", "s", NULL, MEMBER_ANNOTATE_SESSIONLESS));
    ASSERT_EQ(ER_OK, intf->AddSignal("unicastSignal", "s", NULL, MEMBER_ANNOTATE_UNICAST));
    ASSERT_EQ(ER_OK, intf->AddSignal("globalBroadcastSignal", "s", NULL, MEMBER_ANNOTATE_GLOBAL_BROADCAST));

    MyTranslator translator;
    intf->SetDescriptionTranslator(&translator);
    intf->Activate();

    ASSERT_TRUE((m_testObj = new DescriptionObject(*intf, SERVICE_PATH)) != NULL);
    m_testObj->SetDescriptionTranslator(&translator);
    ASSERT_EQ(ER_OK, s_msgBusServer->RegisterBusObject(*m_testObj));
    ASSERT_EQ(ER_OK, s_msgBusServer->Connect());

    ASSERT_TRUE((m_remoteObj = new ProxyBusObject(*s_msgBusClient, s_msgBusServer->GetUniqueName().c_str(), SERVICE_PATH, 0)) != NULL);
    EXPECT_EQ(ER_OK, m_remoteObj->IntrospectRemoteObject());

    IntrospectWithDescription(m_remoteObj, "en", IntrospectWithDescriptionString4);
}
