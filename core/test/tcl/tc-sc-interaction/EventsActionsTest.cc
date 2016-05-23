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
#include "ajtcscTestCommon.h"

#include <qcc/Environ.h>
#include <qcc/StringUtil.h>
#include <qcc/time.h>
#include <qcc/CertificateECC.h>

#include <alljoyn/AllJoynStd.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/DBusStd.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>
#include <alljoyn/Status.h>
#include <ProxyBusObject.h>

using namespace qcc;
using namespace ajn;

/*
 * Global variables specific to unit test.
 */
namespace {

static const char ServiceName[] = "org.alljoyn.Bus.eventaction.sample";
static const char ServicePath[] = "/eventaction";
static const uint16_t ServicePort = 50;
static char buffer[60];

/**
 * The interface name followed by the method signatures.
 *
 * See also .\inc\aj_introspect.h
 */
static const char* const sampleInterface[] = {
    "org.alljoyn.Bus.eventaction.sample",   /* The first entry is the interface name. */
    "?dummyMethod foo<i",             /* This is just a dummy entry at index 0 for illustration purposes. */
    "?joinMethod inStr1<s inStr2<s outStr>s", /* Method at index 1. */
    "!someSignal name>s",
    "!&someSessionlessSignal", /* & indicates that a signal is designated as sessionless so the introspection will describe it as such */
    NULL
};

/**
 * A NULL terminated collection of all interfaces.
 */
static const AJ_InterfaceDescription sampleInterfaces[] = {
    sampleInterface,
    NULL
};

/**
 * Objects implemented by the application. The first member in the AJ_Object structure is the path.
 * The second is the collection of all interfaces at that path.
 */
static const AJ_Object AppObjects[] = {
    { ServicePath, sampleInterfaces, AJ_OBJ_FLAG_DESCRIBED, NULL },
    { NULL }
};

/* All times are expressed in milliseconds. */
#define CONNECT_TIMEOUT     (1000 * 60)
#define UNMARSHAL_TIMEOUT   (1000 * 5)

static const char* const objDesc[] = { "Sample object description", "ES: Sample object description" };
static const char* const intfDesc[] = { "Sample interface", "ES: Sample interface" };
static const char* const joinDesc[] = { "Join two strings and return the result", "ES: Join two strings and return the result" };
static const char* const joinInArg1Desc[] = { "First part of string", "ES: First part of string" };
static const char* const joinInArg2Desc[] = { "Second part of string", "ES: Second part of string" };
static const char* const joinOutArgDesc[] = { "Return result", "ES: Return result" };
static const char* const someSignalArgDesc[] = { "EN: %s", "ES: %s" };
static const char* const someSessionlessSignalDesc[] = { "An example sessionless signal", "ES: An example sessionless signal" };

/*
 * AJ_DESCRIPTION_ID(BusObject base ID, Interface index, Member index, Arg index)
 * Interface, Member, and Arg indexes starts at 1 and represent the readible index in a list.
 * [ a, b, ... ] a would be index 1, b 2, etc.
 */
#define SAMPLE_OBJECT_ID                    0
#define SAMPLE_OBJECT_DESC                  AJ_DESCRIPTION_ID(SAMPLE_OBJECT_ID, 0, 0, 0)
#define SAMPLE_INTERFACE_DESC               AJ_DESCRIPTION_ID(SAMPLE_OBJECT_ID, 1, 0, 0)
#define SAMPLE_JOIN_DESC                    AJ_DESCRIPTION_ID(SAMPLE_OBJECT_ID, 1, 2, 0)
#define SAMPLE_JOIN_ARG_INSTR1_DESC         AJ_DESCRIPTION_ID(SAMPLE_OBJECT_ID, 1, 2, 1)
#define SAMPLE_JOIN_ARG_INSTR2_DESC         AJ_DESCRIPTION_ID(SAMPLE_OBJECT_ID, 1, 2, 2)
#define SAMPLE_JOIN_ARG_OUTSTR_DESC         AJ_DESCRIPTION_ID(SAMPLE_OBJECT_ID, 1, 2, 3)
#define SAMPLE_SOMESIGNAL_ARG_DESC          AJ_DESCRIPTION_ID(SAMPLE_OBJECT_ID, 1, 3, 1)
#define SAMPLE_SOMESESSIONLESSSIGNAL_DESC   AJ_DESCRIPTION_ID(SAMPLE_OBJECT_ID, 1, 4, 0)

static const char* const languages[] = { "en", "es" };

//Unit Test 1 Globals
bool messageReceived = FALSE; //Boolean used as a flag to terminate thin client message loop.
qcc::String buf = ""; //Character buffer used to store the introspected interface.
const InterfaceDescription::Member* introspectMethod;

static const char* MyTranslator(uint32_t descId, const char* lang) {
    uint8_t langIndex;

    /* 
     * Compute the location of lang in our languages array
     * Starting index is 0 (default language index).
     * In the event the language tag passed in is NULL or "",
     * the translator will return strings for index 0.
     */
    langIndex = 0;
    if(lang != NULL && strlen(lang) > 0){
        //Valid string passed as argument.
        while (langIndex < ARRAY_SIZE(languages)) {
            if (strcmp(lang, languages[langIndex]) == 0) {
                break;
            }
            ++langIndex;
        }
    }

    /* If all languages in list did not match, then set index to 0 (default) language */
    if (langIndex >= ARRAY_SIZE(languages)) {
        langIndex = 0;
    }

    /* Return correct lang string for descId */
    switch (descId) {

    case SAMPLE_OBJECT_DESC:
        return objDesc[langIndex];

    case SAMPLE_INTERFACE_DESC:
        return intfDesc[langIndex];

    case SAMPLE_JOIN_DESC:
        return joinDesc[langIndex];

    case SAMPLE_JOIN_ARG_INSTR1_DESC:
        return joinInArg1Desc[langIndex];

    case SAMPLE_JOIN_ARG_INSTR2_DESC:
        return joinInArg2Desc[langIndex];

    case SAMPLE_JOIN_ARG_OUTSTR_DESC:
        return joinOutArgDesc[langIndex];

    case SAMPLE_SOMESIGNAL_ARG_DESC:
        sprintf(buffer, someSignalArgDesc[langIndex], "Some replacement value");
        return buffer;

    case SAMPLE_SOMESESSIONLESSSIGNAL_DESC:
        return someSessionlessSignalDesc[langIndex];

    }
    /* No description set so return NULL */
    return NULL;
}

//Handler for setting the global that terminates the message loop and stores the interface XML in the buf global.
class MyMessageReceiver : public MessageReceiver {
  public:
    void IntrospectResponseHandler(Message& message, void* context)
    {
        QCC_UNUSED(context);
        if (message->GetType() == MESSAGE_METHOD_RET) {
            messageReceived = TRUE;
            buf = message->GetArg(0)->v_string.str;
        }
    }
};

class EventsActionsTest : public testing::Test {
  public:
    EventsActionsTest() :
        scBus("StandardCoreLibraryBus", true)
    {
        remoteObj = NULL;
    };
    void SetUp() {
        ASSERT_EQ(ER_OK, scBus.Start());
        ASSERT_EQ(ER_OK, scBus.Connect());

        // To avoid cross-talk, i.e. thin leaf node connect to unintended
        // routing nodes, generate and advertise a random routing node prefix.
        qcc::String routingNodePrefix = "test.rnPrefix.randhex" + qcc::RandHexString(64);

        qcc::String advertisingPrefix = "quiet@" + routingNodePrefix;

        ASSERT_EQ(ER_OK, scBus.AdvertiseName(advertisingPrefix.c_str(), ajn::TRANSPORT_ANY));

        AJ_Initialize();

        AJ_RegisterObjectListWithDescriptions(AppObjects, 1, MyTranslator);
        // Ensure that a routing node is found as quickly as possible
        AJ_SetSelectionTimeout(0);

        ASSERT_EQ(AJ_OK, AJ_FindBusAndConnect(&tcBus, routingNodePrefix.c_str(), TC_LEAFNODE_CONNECT_TIMEOUT));

        //Instantiate ProxyBusObject on standard client for manipulation of thin client object.
        static SessionId s_sessionId = 0;
        ASSERT_TRUE((remoteObj = new ProxyBusObject(scBus, AJ_GetUniqueName(&tcBus), ServicePath, s_sessionId)) != NULL);

        //Pull in the interface for the remote bus object.
        const InterfaceDescription* ifc = scBus.GetInterface(org::allseen::Introspectable::InterfaceName);
        assert(ifc);
        remoteObj->AddInterface(*ifc);

        //Specify the method to be called Asynchronously.
        introspectMethod = ifc->GetMember("IntrospectWithDescription");
    }

    void TearDown() {
        AJ_Disconnect(&tcBus);

        ASSERT_EQ(ER_OK, scBus.Disconnect());
        ASSERT_EQ(ER_OK, scBus.Stop());
        ASSERT_EQ(ER_OK, scBus.Join());
    }

    ajn::BusAttachment scBus;
    AJ_BusAttachment tcBus;
    ProxyBusObject* remoteObj;
    };

} // end of anonymous namespace

TEST_F(EventsActionsTest, TC_Being_Introspected_With_Empty_Language_Tag) {
    //Local Variables for Unit Test 1
    QStatus status;
    MyMessageReceiver msgReceiver;
    Message reply(scBus);
    messageReceived = FALSE;
    buf = "";

    //set arguments for introspection method call
    MsgArg introspectArgs[1];
    uint32_t numArgs = 1;
    introspectArgs[0].Set("s", ""); // no language tag

    // Message Loop
    AJ_Message tcMsg;
    AJ_Status tcMsgStatus = AJ_UnmarshalMsg(&tcBus, &tcMsg, TC_UNMARSHAL_TIMEOUT);

    //Async Call for Introspection of Interface on tc Object.
    EXPECT_EQ(ER_OK, status = remoteObj->MethodCallAsync(*introspectMethod,
                                        &msgReceiver,
                                        static_cast<MessageReceiver::ReplyHandler>(&MyMessageReceiver::IntrospectResponseHandler),
                                        introspectArgs, numArgs,
                                        const_cast<void*>(static_cast<const void*>(introspectMethod)),
                                        WAIT_TIME));

    // Message Loop
    while (!messageReceived) {
        if (tcMsgStatus != AJ_OK) {
            if (tcMsgStatus == AJ_ERR_TIMEOUT) {
                continue;
            }
        } else {
            tcMsgStatus = AJ_BusHandleBusMessage(&tcMsg);
            AJ_CloseMsg(&tcMsg);
            }

        tcMsgStatus = AJ_UnmarshalMsg(&tcBus, &tcMsg, TC_UNMARSHAL_TIMEOUT);
    }

    const char* expectedResultString =
    "<node name=\"/eventaction\">\n"
    "<description>Sample object description</description>\n"
    "<interface name=\"org.alljoyn.Bus.eventaction.sample\">\n"
    "<description>Sample interface</description>\n"
    "  <method name=\"dummyMethod\">\n"
    "    <arg name=\"foo\" type=\"i\" direction=\"in\"/>\n"
    "  </method>\n"
    "  <method name=\"joinMethod\">\n"
    "    <arg name=\"inStr1\" type=\"s\" direction=\"in\">\n"
    "        <description>First part of string</description>\n"
    "    </arg>\n"
    "    <arg name=\"inStr2\" type=\"s\" direction=\"in\">\n"
    "        <description>Second part of string</description>\n"
    "    </arg>\n"
    "    <arg name=\"outStr\" type=\"s\" direction=\"out\">\n"
    "        <description>Return result</description>\n"
    "    </arg>\n"
    "    <description>Join two strings and return the result</description>\n"
    "  </method>\n"
    "  <signal name=\"someSignal\" sessionless=\"false\">\n"
    "    <arg name=\"name\" type=\"s\">\n"
    "        <description>EN: Some replacement value</description>\n"
    "    </arg>\n"
    "  </signal>\n"
    "  <signal name=\"someSessionlessSignal\" sessionless=\"true\">\n"
    "    <description>An example sessionless signal</description>\n"
    "  </signal>\n</interface>\n</node>\n";

    //Compared XML recieved from the tc object to the expected XML output.
    EXPECT_STREQ(expectedResultString, buf.c_str());

    delete(remoteObj);
}

TEST_F(EventsActionsTest, TC_Being_Introspected_With_Supported_Language_Tag) {

    //Local Variables for Unit Test
    QStatus status;
    MyMessageReceiver msgReceiver;
    Message reply(scBus);
    messageReceived = FALSE;
    buf = "";

    //set arguments for introspection method call
    MsgArg introspectArgs[1];
    uint32_t numArgs = 1;
    introspectArgs[0].Set("s", "es"); // Spanish language tag

    // Message Loop Preparation
    AJ_Message tcMsg;
    AJ_Status tcMsgStatus = AJ_UnmarshalMsg(&tcBus, &tcMsg, TC_UNMARSHAL_TIMEOUT);

    //Async Call for Introspection of Interface on tc Object.
    EXPECT_EQ(ER_OK, status = remoteObj->MethodCallAsync(*introspectMethod,
                                        &msgReceiver,
                                        static_cast<MessageReceiver::ReplyHandler>(&MyMessageReceiver::IntrospectResponseHandler),
                                        introspectArgs, numArgs,
                                        const_cast<void*>(static_cast<const void*>(introspectMethod)),
                                        WAIT_TIME));

    // Message Loop
    while (!messageReceived) {
        if (tcMsgStatus != AJ_OK) {
            if (tcMsgStatus == AJ_ERR_TIMEOUT) {
                continue;
            }
        } else {
            tcMsgStatus = AJ_BusHandleBusMessage(&tcMsg);
            AJ_CloseMsg(&tcMsg);
            }

        tcMsgStatus = AJ_UnmarshalMsg(&tcBus, &tcMsg, TC_UNMARSHAL_TIMEOUT);
    }

    const char* expectedResultString =
    "<node name=\"/eventaction\">\n"
    "<description language=\"es\">ES: Sample object description</description>\n"
    "<interface name=\"org.alljoyn.Bus.eventaction.sample\">\n"
    "<description language=\"es\">ES: Sample interface</description>\n"
    "  <method name=\"dummyMethod\">\n"
    "    <arg name=\"foo\" type=\"i\" direction=\"in\"/>\n"
    "  </method>\n"
    "  <method name=\"joinMethod\">\n"
    "    <arg name=\"inStr1\" type=\"s\" direction=\"in\">\n"
    "        <description language=\"es\">ES: First part of string</description>\n"
    "    </arg>\n"
    "    <arg name=\"inStr2\" type=\"s\" direction=\"in\">\n"
    "        <description language=\"es\">ES: Second part of string</description>\n"
    "    </arg>\n"
    "    <arg name=\"outStr\" type=\"s\" direction=\"out\">\n"
    "        <description language=\"es\">ES: Return result</description>\n"
    "    </arg>\n"
    "    <description language=\"es\">ES: Join two strings and return the result</description>\n"
    "  </method>\n"
    "  <signal name=\"someSignal\" sessionless=\"false\">\n"
    "    <arg name=\"name\" type=\"s\">\n"
    "        <description language=\"es\">ES: Some replacement value</description>\n"
    "    </arg>\n"
    "  </signal>\n"
    "  <signal name=\"someSessionlessSignal\" sessionless=\"true\">\n"
    "    <description language=\"es\">ES: An example sessionless signal</description>\n"
    "  </signal>\n</interface>\n</node>\n";

    //Compared XML recieved from the tc object to the expected XML output.
    EXPECT_STREQ(expectedResultString, buf.c_str());

    delete(remoteObj);
}

TEST_F(EventsActionsTest, TC_Being_Introspected_With_Unsupported_Language_Tag) {
    //Local Variables for Unit Test
    QStatus status;
    MyMessageReceiver msgReceiver;
    Message reply(scBus);
    messageReceived = FALSE;
    buf = "";

    //set arguments for introspection method call
    MsgArg introspectArgs[1];
    uint32_t numArgs = 1;
    introspectArgs[0].Set("s", "fr"); // unsupported language tag

    // Message Loop Preparation
    AJ_Message tcMsg;
    AJ_Status tcMsgStatus = AJ_UnmarshalMsg(&tcBus, &tcMsg, TC_UNMARSHAL_TIMEOUT);

    //Async Call for Introspection of Interface on tc Object.
    EXPECT_EQ(ER_OK, status = remoteObj->MethodCallAsync(*introspectMethod,
                                        &msgReceiver,
                                        static_cast<MessageReceiver::ReplyHandler>(&MyMessageReceiver::IntrospectResponseHandler),
                                        introspectArgs, numArgs,
                                        const_cast<void*>(static_cast<const void*>(introspectMethod)),
                                        WAIT_TIME));

    // Message Loop
    while (!messageReceived) {
        if (tcMsgStatus != AJ_OK) {
            if (tcMsgStatus == AJ_ERR_TIMEOUT) {
                continue;
            }
        } else {
            tcMsgStatus = AJ_BusHandleBusMessage(&tcMsg);
            AJ_CloseMsg(&tcMsg);
            }

        tcMsgStatus = AJ_UnmarshalMsg(&tcBus, &tcMsg, TC_UNMARSHAL_TIMEOUT);
    }

    const char* expectedResultString =
    "<node name=\"/eventaction\">\n"
    "<description>Sample object description</description>\n"
    "<interface name=\"org.alljoyn.Bus.eventaction.sample\">\n"
    "<description>Sample interface</description>\n"
    "  <method name=\"dummyMethod\">\n"
    "    <arg name=\"foo\" type=\"i\" direction=\"in\"/>\n"
    "  </method>\n"
    "  <method name=\"joinMethod\">\n"
    "    <arg name=\"inStr1\" type=\"s\" direction=\"in\">\n"
    "        <description>First part of string</description>\n"
    "    </arg>\n"
    "    <arg name=\"inStr2\" type=\"s\" direction=\"in\">\n"
    "        <description>Second part of string</description>\n"
    "    </arg>\n"
    "    <arg name=\"outStr\" type=\"s\" direction=\"out\">\n"
    "        <description>Return result</description>\n"
    "    </arg>\n"
    "    <description>Join two strings and return the result</description>\n"
    "  </method>\n"
    "  <signal name=\"someSignal\" sessionless=\"false\">\n"
    "    <arg name=\"name\" type=\"s\">\n"
    "        <description>EN: Some replacement value</description>\n"
    "    </arg>\n"
    "  </signal>\n"
    "  <signal name=\"someSessionlessSignal\" sessionless=\"true\">\n"
    "    <description>An example sessionless signal</description>\n"
    "  </signal>\n</interface>\n</node>\n";

    //Compared XML recieved from the tc object to the expected XML output.
    EXPECT_STREQ(expectedResultString, buf.c_str());

    delete(remoteObj);
}

TEST_F(EventsActionsTest, TC_Being_Introspected_With_No_Translator_With_Empty_Language_Tag) {
    //Re-Register without translator.
    AJ_RegisterObjectListWithDescriptions(AppObjects, 1, NULL);

    //Local Variables for Unit Test
    QStatus status;
    MyMessageReceiver msgReceiver;
    Message reply(scBus);
    messageReceived = FALSE;
    buf = "";

    //set arguments for introspection method call
    MsgArg introspectArgs[1];
    uint32_t numArgs = 1;
    introspectArgs[0].Set("s", ""); // no language tag

    // Message Loop Preparation
    AJ_Message tcMsg;
    AJ_Status tcMsgStatus = AJ_UnmarshalMsg(&tcBus, &tcMsg, TC_UNMARSHAL_TIMEOUT);

    //Async Call for Introspection of Interface on tc Object.
    EXPECT_EQ(ER_OK, status = remoteObj->MethodCallAsync(*introspectMethod,
                                        &msgReceiver,
                                        static_cast<MessageReceiver::ReplyHandler>(&MyMessageReceiver::IntrospectResponseHandler),
                                        introspectArgs, numArgs,
                                        const_cast<void*>(static_cast<const void*>(introspectMethod)),
                                        WAIT_TIME));

    // Message Loop
    while (!messageReceived) {
        if (tcMsgStatus != AJ_OK) {
            if (tcMsgStatus == AJ_ERR_TIMEOUT) {
                continue;
            }
        } else {
            tcMsgStatus = AJ_BusHandleBusMessage(&tcMsg);
            AJ_CloseMsg(&tcMsg);
            }

        tcMsgStatus = AJ_UnmarshalMsg(&tcBus, &tcMsg, TC_UNMARSHAL_TIMEOUT);
    }

    const char* expectedResultString =
    "<node name=\"/eventaction\">\n"
    "<interface name=\"org.alljoyn.Bus.eventaction.sample\">\n"
    "  <method name=\"dummyMethod\">\n"
    "    <arg name=\"foo\" type=\"i\" direction=\"in\"/>\n"
    "  </method>\n"
    "  <method name=\"joinMethod\">\n"
    "    <arg name=\"inStr1\" type=\"s\" direction=\"in\"/>\n"
    "    <arg name=\"inStr2\" type=\"s\" direction=\"in\"/>\n"
    "    <arg name=\"outStr\" type=\"s\" direction=\"out\"/>\n"
    "  </method>\n"
    "  <signal name=\"someSignal\" sessionless=\"false\">\n"
    "    <arg name=\"name\" type=\"s\"/>\n"
    "  </signal>\n"
    "  <signal name=\"someSessionlessSignal\" sessionless=\"true\">\n"
    "  </signal>\n</interface>\n</node>\n";
    //Compared XML recieved from the tc object to the expected XML output.
    EXPECT_STREQ(expectedResultString, buf.c_str());

    delete(remoteObj);
}

TEST_F(EventsActionsTest, TC_Being_Introspected_With_No_Translator_With_English_Language_Tag) {
    //Re-Register without translator.
    AJ_RegisterObjectListWithDescriptions(AppObjects, 1, NULL);

    //Local Variables for Unit Test
    QStatus status;
    MyMessageReceiver msgReceiver;
    Message reply(scBus);
    messageReceived = FALSE;
    buf = "";

    //set arguments for introspection method call
    MsgArg introspectArgs[1];
    uint32_t numArgs = 1;
    introspectArgs[0].Set("s", "en"); // english language tag

    // Message Loop Preparation
    AJ_Message tcMsg;
    AJ_Status tcMsgStatus = AJ_UnmarshalMsg(&tcBus, &tcMsg, TC_UNMARSHAL_TIMEOUT);

    //Async Call for Introspection of Interface on tc Object.
    EXPECT_EQ(ER_OK, status = remoteObj->MethodCallAsync(*introspectMethod,
                                        &msgReceiver,
                                        static_cast<MessageReceiver::ReplyHandler>(&MyMessageReceiver::IntrospectResponseHandler),
                                        introspectArgs, numArgs,
                                        const_cast<void*>(static_cast<const void*>(introspectMethod)),
                                        WAIT_TIME));

    // Message Loop
    while (!messageReceived) {
        if (tcMsgStatus != AJ_OK) {
            if (tcMsgStatus == AJ_ERR_TIMEOUT) {
                continue;
            }
        } else {
            tcMsgStatus = AJ_BusHandleBusMessage(&tcMsg);
            AJ_CloseMsg(&tcMsg);
            }

        tcMsgStatus = AJ_UnmarshalMsg(&tcBus, &tcMsg, TC_UNMARSHAL_TIMEOUT);
    }

    const char* expectedResultString =
    "<node name=\"/eventaction\">\n"
    "<interface name=\"org.alljoyn.Bus.eventaction.sample\">\n"
    "  <method name=\"dummyMethod\">\n"
    "    <arg name=\"foo\" type=\"i\" direction=\"in\"/>\n"
    "  </method>\n"
    "  <method name=\"joinMethod\">\n"
    "    <arg name=\"inStr1\" type=\"s\" direction=\"in\"/>\n"
    "    <arg name=\"inStr2\" type=\"s\" direction=\"in\"/>\n"
    "    <arg name=\"outStr\" type=\"s\" direction=\"out\"/>\n"
    "  </method>\n"
    "  <signal name=\"someSignal\" sessionless=\"false\">\n"
    "    <arg name=\"name\" type=\"s\"/>\n"
    "  </signal>\n"
    "  <signal name=\"someSessionlessSignal\" sessionless=\"true\">\n"
    "  </signal>\n</interface>\n</node>\n";
    //Compared XML recieved from the tc object to the expected XML output.
    EXPECT_STREQ(expectedResultString, buf.c_str());

    delete(remoteObj);
}