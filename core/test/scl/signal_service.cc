# Contributed by Qualcomm Connected Experiences, Inc.,
# with authorization from the AllSeen Alliance, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Pursuant to Section 1 of the License, the work of authorship constituting
# a Work and any Contribution incorporated in the Work shall mean only that
# Contributor's code submissions authored by that Contributor.  Any rights
# granted under the License are conditioned upon acceptance of these
# clarifications.
/**
 * @file
 * @brief Sample implementation of an AllJoyn service.
 *
 * This sample will show how to set up an AllJoyn service that will registered with the
 * well-known name 'org.alljoyn.Bus.signal_sample'.  The service will register a signal method 'nameChanged'
 * as well as a property 'name'.
 *
 * When the property 'sampleName' is changed by any client this service will emit the new name using
 * the 'nameChanged' signal.
 *
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
#include <qcc/platform.h>

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <vector>

#include <qcc/String.h>

#include <alljoyn/BusAttachment.h>
#include <alljoyn/Init.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/MsgArg.h>
#include <alljoyn/DBusStd.h>
#include <alljoyn/AllJoynStd.h>
#include <alljoyn/version.h>
#include <alljoyn/Status.h>

using namespace std;
using namespace qcc;
using namespace ajn;

/** Static top level message bus object */
static BusAttachment* s_msgBus = NULL;

static SessionId s_sessionId = 0;

static const char* INTERFACE_NAME = "org.alljoyn.Bus.signal_sample";
//static const char* INTERFACE_NAME_TEST = "org.alljoyn.Bus.signal_sample_test";
static const char* SERVICE_NAME = "org.alljoyn.Bus.signal_sample";
static const char* SERVICE_PATH = "/";
static const SessionPort SERVICE_PORT = 25;

static volatile sig_atomic_t s_interrupt = false;

static void CDECL_CALL SigIntHandler(int sig)
{
    QCC_UNUSED(sig);
    s_interrupt = true;
}

static const char* tags[] = { "en", "de", "hi" };
static const char* objId = "obj";
static const char* objDescription[] =  { "This is the object", "Dies ist das Objekt", "Ye Object hai" };
static const char* ifcId = "ifc";
static const char* ifcDescription[] =  { "This is the first interface", "Dies ist das UNO Schnittstelle", "Ye pehla Interface hai" };
static const char* ifcIdTest = "ifcTest";
static const char* ifcDescriptionTest[] =  { "This is the second interface", "Dies ist das second Schnittstelle", "Ye dusra Interface hai" };
static const char* nameChangedId = "nameChanged";
static const char* nameChangedDescription[] =  { "Emitted when the name changes", "Emittiert, wenn der Name andert", "Naam badalne pe emitte karen" };
static const char* nameChangedIdTest = "nameChangedTest";
static const char* nameChangedDescriptionTest[] =  { "Emitted when the name changes and is sessionless", "Emittiert, wenn der Name andert sessionless", "Naam badalne pe emitte karen aur ye sessionless hai" };
static const char* testMethodId = "testMethod";
static const char* testMethodDescription[] = { "This is first method", "Este es el primer metodo", "Ye pehla method hai" };
static const char* nameChangedId1 = "nameChanged1";
static const char* nameChangedDescription1[] =  { "Emitted when the name changes 2nd interface", "Emittiert, wenn der Name andert 2nd interface", "Naam badalne pe emitte karen 2nd interface" };
static const char* nameChangedIdTest1 = "nameChangedTest1";
static const char* nameChangedDescriptionTest1[] =  { "Emitted when the name changes and is sessionless 2nd interface", "Emittiert, wenn der Name andert sessionless 2nd interface", "Naam badalne pe emitte karen aur ye sessionless hai 2nd interface" };
static const char* testMethodId1 = "testMethod1";
static const char* testMethodDescription1[] = { "This is first method 2nd interface", "Este es el primer metodo 2nd interface", "Ye pehla method hai 2nd interface" };

static const char* argId = "arg";
static const char* nameChangedArgDescription[] =  { "This is the new name", "Dies ist der neue Name", "Ye naya naam hai" };
static const char* propId = "prop";
static const char* namePropDescription[] =  { "This is the actual name", "Dies ist der eigentliche Name", "Ye asli naam hai" };
static int translator_status = 0;

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
        QCC_UNUSED(sourceLanguage);
        size_t i = 0;
        if (targetLanguage && (0 == strcmp(targetLanguage, "de"))) {
            i = 1;
        }

        if (0 == strcmp(source, objId)) {
            return objDescription[i];
        }
        if (0 == strcmp(source, ifcId)) {
            return ifcDescription[i];
        }
        if (0 == strcmp(source, nameChangedId)) {
            return nameChangedDescription[i];
        }
        if (0 == strcmp(source, nameChangedIdTest)) {
            return nameChangedDescriptionTest[i];
        }
        if (0 == strcmp(source, testMethodId)) {
            return testMethodDescription[i];
        }
        if (0 == strcmp(source, ifcIdTest)) {
            return ifcDescriptionTest[i];
        }
        if (0 == strcmp(source, nameChangedId1)) {
            return nameChangedDescription1[i];
        }
        if (0 == strcmp(source, nameChangedIdTest1)) {
            return nameChangedDescriptionTest1[i];
        }
        if (0 == strcmp(source, testMethodId1)) {
            return testMethodDescription1[i];
        }
        if (0 == strcmp(source, argId)) {
            return nameChangedArgDescription[i];
        }
        if (0 == strcmp(source, propId)) {
            return namePropDescription[i];
        }
        return NULL;
    }

};

class MyTranslatorTest1 : public Translator {
  public:

    virtual ~MyTranslatorTest1() { }

    virtual size_t NumTargetLanguages() {
        return 3;
    }

    virtual void GetTargetLanguage(size_t index, qcc::String& ret) {
        ret.assign(tags[index]);
    }

    virtual const char* Translate(const char* sourceLanguage, const char* targetLanguage, const char* source) {
        QCC_UNUSED(sourceLanguage);
        size_t i = 0;
        if (targetLanguage && (0 == strcmp(targetLanguage, "hi"))) {
            i = 2;
        }


        if (0 == strcmp(source, objId)) {
            return objDescription[i];
        }
        if (0 == strcmp(source, ifcId)) {
            return ifcDescription[i];
        }
        if (0 == strcmp(source, nameChangedId)) {
            return nameChangedDescription[i];
        }
        if (0 == strcmp(source, nameChangedIdTest)) {
            return nameChangedDescriptionTest[i];
        }
        if (0 == strcmp(source, testMethodId)) {
            return testMethodDescription[i];
        }
        if (0 == strcmp(source, ifcIdTest)) {
            return ifcDescriptionTest[i];
        }
        if (0 == strcmp(source, nameChangedId1)) {
            return nameChangedDescription1[i];
        }
        if (0 == strcmp(source, nameChangedIdTest1)) {
            return nameChangedDescriptionTest1[i];
        }
        if (0 == strcmp(source, testMethodId1)) {
            return testMethodDescription1[i];
        }
        if (0 == strcmp(source, argId)) {
            return nameChangedArgDescription[i];
        }
        if (0 == strcmp(source, propId)) {
            return namePropDescription[i];
        }
        return NULL;
    }

};

class MyTranslatorTest2 : public Translator {
  public:

    virtual ~MyTranslatorTest2() { }

    virtual size_t NumTargetLanguages() {
        return 3;
    }

    virtual void GetTargetLanguage(size_t index, qcc::String& ret) {
        ret.assign(tags[index]);
    }

    virtual const char* Translate(const char* sourceLanguage, const char* targetLanguage, const char* source) {
        QCC_UNUSED(sourceLanguage);
        /* const char* tag = (*targetLanguage == '\0') ? "en" : targetLanguage;
           size_t i = 0;

           if (0 == strcmp(tag, "en")) {
             i = 0;
           } else if (0 == strcmp(tag, "de")) {
             i = 1;
           } else if (0 == strcmp(tag, "hi")) {
             i = 2;
           } else {
             return NULL;
           }*/
        size_t i = 0;
        if (targetLanguage && (0 == strcmp(targetLanguage, "de"))) {
            i = 1;
        } else if (targetLanguage && (0 == strcmp(targetLanguage, "hi"))) {
            i = 2;
        }

        if (0 == strcmp(source, objId)) {
            return objDescription[i];
        }
        if (0 == strcmp(source, ifcId)) {
            return ifcDescription[i];
        }
        if (0 == strcmp(source, nameChangedId)) {
            return nameChangedDescription[i];
        }
        if (0 == strcmp(source, nameChangedIdTest)) {
            return nameChangedDescriptionTest[i];
        }
        if (0 == strcmp(source, testMethodId)) {
            return testMethodDescription[i];
        }
        if (0 == strcmp(source, ifcIdTest)) {
            return ifcDescriptionTest[i];
        }
        if (0 == strcmp(source, nameChangedId1)) {
            return nameChangedDescription1[i];
        }
        if (0 == strcmp(source, nameChangedIdTest1)) {
            return nameChangedDescriptionTest1[i];
        }
        if (0 == strcmp(source, testMethodId1)) {
            return testMethodDescription1[i];
        }
        if (0 == strcmp(source, argId)) {
            return nameChangedArgDescription[i];
        }
        if (0 == strcmp(source, propId)) {
            return namePropDescription[i];
        }
        return NULL;
    }

};

class BasicSampleObject : public BusObject {
  public:
    BasicSampleObject(BusAttachment& bus, const char* path) :
        BusObject(path),
        nameChangedMember(NULL),
        nameChangedMemberTest(NULL),
        nameChangedMember1(NULL),
        nameChangedMemberTest1(NULL),
        prop_name("Default name"),
        prop_nameTest("Default name Test")
    {
        /* Add org.alljoyn.Bus.signal_sample interface */
        InterfaceDescription* intf = NULL;
        QStatus status = bus.CreateInterface(INTERFACE_NAME, intf);
        if (status == ER_OK) {
            intf->AddSignal("nameChanged", "s", "newName", MEMBER_ANNOTATE_UNICAST);
            intf->AddSignal("nameChangedTest", "s", "newNameTest", MEMBER_ANNOTATE_SESSIONLESS);
            intf->AddMethod("testMethod", "s", "s", "inStr,outStr");
            intf->AddProperty("name", "s", PROP_ACCESS_RW);

            intf->SetDescriptionLanguage("");
            intf->SetDescription(ifcId);
            intf->SetMemberDescription("nameChanged", nameChangedId);
            intf->SetMemberDescription("nameChangedTest", nameChangedIdTest);
            intf->SetMemberDescription("testMethod", testMethodId);
            intf->SetArgDescription("nameChanged", "newName", argId);
            intf->SetPropertyDescription("name", propId);

            if (translator_status == 3) {
                intf->SetDescriptionTranslator(&translator);
            }
            intf->Activate();
        } else {
            printf("Failed to create interface %s\n", INTERFACE_NAME);
        }

        status = AddInterface(*intf);

        if (status == ER_OK) {
            /* Register the signal handler 'nameChanged' with the bus*/
            nameChangedMember = intf->GetMember("nameChanged");
            assert(nameChangedMember);
        } else {
            printf("Failed to Add interface: %s", INTERFACE_NAME);
        }

        /* InterfaceDescription* intfTest = NULL;
           QStatus statusTest = bus.CreateInterface(INTERFACE_NAME_TEST, intfTest);
           if (statusTest == ER_OK) {
             intfTest->AddSignal("nameChanged1", "s", "newName", 0);
             intfTest->AddSignal("nameChangedTest1", "s", "newNameTest", 0);
             intfTest->AddMethod("testMethod1", "s", "s", "inStr,outStr", 0);
             intfTest->AddProperty("name1", "s", PROP_ACCESS_RW);

             intfTest->SetDescriptionLanguage("dig");
             intfTest->SetDescription(ifcIdTest);
             intfTest->SetMemberDescription("nameChanged1", nameChangedId1, 0);
             intfTest->SetMemberDescription("nameChangedTest1", nameChangedIdTest1, 1);
             intfTest->SetMemberDescription("testMethod1", testMethodId1, 1);
             intfTest->SetArgDescription("nameChanged", "newName", argId);
             intfTest->SetPropertyDescription("name", propId);

             intfTest->SetDescriptionTranslator(&translator1);

             intfTest->Activate();
           } else {
             printf("Failed to create interface %s\n", INTERFACE_NAME_TEST);
           }

           statusTest = AddInterface(*intfTest);

           if (statusTest == ER_OK) {
             Register the signal handler 'nameChanged' with the bus
             nameChangedMember = intfTest->GetMember("nameChanged");
             assert(nameChangedMember);
            } else {
             printf("Failed to Add interface: %s", INTERFACE_NAME);
            }*/

        SetDescription("", objId);
        if (translator_status == 2) {
            SetDescriptionTranslator(&translator);
        }
    }

    QStatus EmitNameChangedSignal(qcc::String newName)
    {
        printf("Emiting Name Changed Signal.\n");
        assert(nameChangedMember);
        if (0 == s_sessionId) {
            printf("Sending NameChanged signal without a session id\n");
        }
        MsgArg arg("s", newName.c_str());
        uint8_t flags = ALLJOYN_FLAG_GLOBAL_BROADCAST;
        QStatus status = Signal(NULL, 0, *nameChangedMember, &arg, 1, 0, flags);

        return status;
    }

    QStatus Get(const char* ifcName, const char* propName, MsgArg& val)
    {
        QCC_UNUSED(ifcName);
        printf("Get 'name' property was called returning: %s\n", prop_name.c_str());
        QStatus status = ER_OK;
        if (0 == strcmp("name", propName)) {
            val.typeId = ALLJOYN_STRING;
            val.v_string.str = prop_name.c_str();
            val.v_string.len = prop_name.length();
        } else {
            status = ER_BUS_NO_SUCH_PROPERTY;
        }
        return status;
    }

    QStatus Set(const char* ifcName, const char* propName, MsgArg& val)
    {
        QCC_UNUSED(ifcName);
        QStatus status = ER_OK;
        if ((0 == strcmp("name", propName)) && (val.typeId == ALLJOYN_STRING)) {
            printf("Set 'name' property was called changing name to %s\n", val.v_string.str);
            prop_name = val.v_string.str;
            EmitNameChangedSignal(prop_name);
        } else {
            status = ER_BUS_NO_SUCH_PROPERTY;
        }
        return status;
    }
  private:
    const InterfaceDescription::Member* nameChangedMember;
    const InterfaceDescription::Member* nameChangedMemberTest;
    const InterfaceDescription::Member* nameChangedMember1;
    const InterfaceDescription::Member* nameChangedMemberTest1;
    qcc::String prop_name;
    qcc::String prop_nameTest;

    MyTranslator translator;
    //MyTranslatorTest1 translator1;
    //MyTranslatorTest2 translator2;
};

class MyBusListener : public BusListener, public SessionPortListener {
    void NameOwnerChanged(const char* busName, const char* previousOwner, const char* newOwner)
    {
        if (newOwner && (0 == strcmp(busName, SERVICE_NAME))) {
            printf("NameOwnerChanged: name=%s, oldOwner=%s, newOwner=%s\n",
                   busName,
                   previousOwner ? previousOwner : "<none>",
                   newOwner ? newOwner : "<none>");
        }
    }

    bool AcceptSessionJoiner(SessionPort sessionPort, const char* joiner, const SessionOpts& opts)
    {
        if (sessionPort != SERVICE_PORT) {
            printf("Rejecting join attempt on unexpected session port %d\n", sessionPort);
            return false;
        }
        printf("Accepting join session request from %s (opts.proximity=%x, opts.traffic=%x, opts.transports=%x)\n",
               joiner, opts.proximity, opts.traffic, opts.transports);
        return true;
    }
};

static MyBusListener s_busListener;

/** Start the message bus, report the result to stdout, and return the status code. */
QStatus StartMessageBus(void)
{
    QStatus status = s_msgBus->Start();

    if (ER_OK == status) {
        printf("BusAttachment started.\n");
    } else {
        printf("Start of BusAttachment failed (%s).\n", QCC_StatusText(status));
    }

    return status;
}

/** Register the bus object and connect, report the result to stdout, and return the status code. */
QStatus RegisterBusObjectAndConnect(BasicSampleObject* obj)
{
    printf("Registering the bus object.\n");
    s_msgBus->RegisterBusObject(*obj);

    QStatus status = s_msgBus->Connect();

    if (ER_OK == status) {
        printf("Connected to '%s'.\n", s_msgBus->GetConnectSpec().c_str());
    } else {
        printf("Failed to connect to '%s'.\n", s_msgBus->GetConnectSpec().c_str());
    }

    return status;
}

/** Request the service name, report the result to stdout, and return the status code. */
QStatus RequestName(void)
{
    const uint32_t flags = DBUS_NAME_FLAG_REPLACE_EXISTING | DBUS_NAME_FLAG_DO_NOT_QUEUE;
    QStatus status = s_msgBus->RequestName(SERVICE_NAME, flags);

    if (ER_OK == status) {
        printf("RequestName('%s') succeeded.\n", SERVICE_NAME);
    } else {
        printf("RequestName('%s') failed (status=%s).\n", SERVICE_NAME, QCC_StatusText(status));
    }

    return status;
}

/** Create the session, report the result to stdout, and return the status code. */
QStatus CreateSession(TransportMask mask)
{
    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, mask);
    SessionPort sp = SERVICE_PORT;
    QStatus status = s_msgBus->BindSessionPort(sp, opts, s_busListener);

    if (ER_OK == status) {
        printf("BindSessionPort succeeded.\n");
    } else {
        printf("BindSessionPort failed (%s).\n", QCC_StatusText(status));
    }

    return status;
}

/** Advertise the service name, report the result to stdout, and return the status code. */
QStatus AdvertiseName(TransportMask mask)
{
    QStatus status = s_msgBus->AdvertiseName(SERVICE_NAME, mask);

    if (ER_OK == status) {
        printf("Advertisement of the service name '%s' succeeded.\n", SERVICE_NAME);
    } else {
        printf("Failed to advertise name '%s' (%s).\n", SERVICE_NAME, QCC_StatusText(status));
    }

    return status;
}

/** Wait for SIGINT before continuing. */
void WaitForSigInt(void)
{
    while (s_interrupt == false) {
#ifdef _WIN32
        Sleep(100);
#else
        usleep(100 * 1000);
#endif
    }
}

static void usage(void)
{
    printf("Usage: signal_service [-h <name>] [-g] [-b] [-i] \n\n");
    printf("Options:\n");
    printf("   -h                    = Print this help message\n");
    printf("   -?                    = Print this help message\n");
    printf("   -g                    = Set Global level translator\n");
    printf("   -b                    = Set Bus Attachment level translator\n");
    printf("   -i                    = Set interface level translator\n");
    printf("\n");
}


int TestAppMain(int argc, char** argv, char** envArg)
{
    QCC_UNUSED(envArg);

    printf("AllJoyn Library version: %s.\n", ajn::GetVersion());
    printf("AllJoyn Library build info: %s.\n", ajn::GetBuildInfo());

    /* Install SIGINT handler */
    signal(SIGINT, SigIntHandler);

    /* Parse the command line args */
    for (int i = 1; i < argc; ++i) {
        if (0 == strcmp("-h", argv[i]) || 0 == strcmp("-?", argv[i])) {
            usage();
            exit(0);
        } else if (0 == strcmp("-g", argv[i])) {
            translator_status = 1;
        } else if (0 == strcmp("-b", argv[i])) {
            translator_status = 2;
        } else if (0 == strcmp("-i", argv[i])) {
            translator_status = 3;
        } else {
            printf("Unknown option %s\n", argv[i]);
            usage();
            exit(1);
        }
    }


    QStatus status = ER_OK;

    /* Create message bus */
    s_msgBus = new BusAttachment("myApp", true);

    /* This test for NULL is only required if new() behavior is to return NULL
     * instead of throwing an exception upon an out of memory failure.
     */
    if (!s_msgBus) {
        status = ER_OUT_OF_MEMORY;
    }

    /* Register a bus listener */
    if (ER_OK == status) {
        s_msgBus->RegisterBusListener(s_busListener);
    }

    if (ER_OK == status) {
        status = StartMessageBus();
    }

    BasicSampleObject testObj(*s_msgBus, SERVICE_PATH);

    /*
     * Set Bus Attachment level translator.
     */
    MyTranslator busTranslator;

    if (translator_status == 1) {
        printf("Inside yes\n");
        // MyTranslator busTranslator;
        s_msgBus->SetDescriptionTranslator(&busTranslator);
    }
    if (ER_OK == status) {
        status = RegisterBusObjectAndConnect(&testObj);
    }

    /*
     * Advertise this service on the bus.
     * There are three steps to advertising this service on the bus.
     * 1) Request a well-known name that will be used by the client to discover
     *    this service.
     * 2) Create a session.
     * 3) Advertise the well-known name.
     */
    if (ER_OK == status) {
        status = RequestName();
    }

    const TransportMask SERVICE_TRANSPORT_TYPE = TRANSPORT_ANY;

    if (ER_OK == status) {
        status = CreateSession(SERVICE_TRANSPORT_TYPE);
    }

    if (ER_OK == status) {
        status = AdvertiseName(SERVICE_TRANSPORT_TYPE);
    }

    /* Perform the service asynchronously until the user signals for an exit. */
    if (ER_OK == status) {
        WaitForSigInt();
    }

    /* Clean up msg bus */
    delete s_msgBus;
    s_msgBus = NULL;

    printf("Signal service exiting with status 0x%04x (%s).\n", status, QCC_StatusText(status));

    return (int) status;
}

/** Main entry point */
int CDECL_CALL main(int argc, char** argv, char** envArg)
{
    QStatus status = AllJoynInit();
    if (ER_OK != status) {
        return 1;
    }
#ifdef ROUTER
    status = AllJoynRouterInit();
    if (ER_OK != status) {
        AllJoynShutdown();
        return 1;
    }
#endif

    int ret = TestAppMain(argc, argv, envArg);

#ifdef ROUTER
    AllJoynRouterShutdown();
#endif
    AllJoynShutdown();

    return ret;
}
