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
#include <alljoyn/ApplicationStateListener.h>
#include <alljoyn/SecurityApplicationProxy.h>

#include "PermissionMgmtObj.h"
#include "PermissionMgmtTest.h"
#include "InMemoryKeyStore.h"

#include <queue>
#include <functional>
#include <mutex>
#include <future>

using namespace ajn;
using namespace qcc;
using namespace std;
/*
 * The unit test use many busy wait loops.  The busy wait loops were chosen
 * over thread sleeps because of the ease of understanding the busy wait loops.
 * Also busy wait loops do not require any platform specific threading code.
 */
#define WAIT_MSECS 5
#define WAIT_SIGNAL 10000

static const char argentinaObjPath[] = "/test/argentina";
static const char arabicObjPath[] = "/test/arabic";
static const char* const calciumInterface[] = {
    "$test.calcium",
    "?march",
    "!make",
    "@mayonise=i",
    NULL
};
static const char* const californiaInterface[] = {
    "$test.california",
    "?metal",
    "!mess",
    "@meal=i",
    NULL
};
static const char* const cameraInterface[] = {
    "$test.camera",
    "?mob",
    "!money",
    "@motel=i",
    NULL
};
static const char* const cashewInterface[] = {
    "$test.cashew",
    "?mint",
    "!mits",
    "@mini=i",
    NULL
};
static const AJ_InterfaceDescription testInterfaces1[] = {
    AJ_PropertiesIface,
    calciumInterface,
    californiaInterface,
    NULL
};
static const AJ_InterfaceDescription testInterfaces2[] = {
    AJ_PropertiesIface,
    cameraInterface,
    cashewInterface,
    NULL
};
static AJ_Object AppObjects[] = {
    { argentinaObjPath, testInterfaces1, AJ_OBJ_FLAG_ANNOUNCED },
    { arabicObjPath, testInterfaces2, AJ_OBJ_FLAG_ANNOUNCED },
    { NULL }
};

#define APP_ARG_GET_PROP   AJ_APP_MESSAGE_ID(0, 0, AJ_PROP_GET)
#define APP_ARG_SET_PROP   AJ_APP_MESSAGE_ID(0, 0, AJ_PROP_SET)
#define APP_ARG_CALC_MARCH AJ_APP_MESSAGE_ID(0, 1, 0)
#define APP_ARG_CALC_MAKE  AJ_APP_MESSAGE_ID(0, 1, 1)
#define APP_ARG_CALC_MAYO  AJ_APP_PROPERTY_ID(0, 1, 2)
#define APP_ARG_CALI_METAL AJ_APP_MESSAGE_ID(0, 2, 0)
#define APP_ARG_CALI_MESS  AJ_APP_MESSAGE_ID(0, 2, 1)
#define APP_ARG_CALI_MEAL  AJ_APP_PROPERTY_ID(0, 2, 2)

#define APP_ARA_GET_PROP   AJ_APP_MESSAGE_ID(1, 0, AJ_PROP_GET)
#define APP_ARA_SET_PROP   AJ_APP_MESSAGE_ID(1, 0, AJ_PROP_SET)
#define APP_ARA_CAME_MOB   AJ_APP_MESSAGE_ID(1, 1, 0)
#define APP_ARA_CAME_MONEY AJ_APP_MESSAGE_ID(1, 1, 1)
#define APP_ARA_CAME_MOTEL AJ_APP_PROPERTY_ID(1, 1, 2)
#define APP_ARA_CASH_MINT  AJ_APP_MESSAGE_ID(1, 2, 0)
#define APP_ARA_CASH_MITS  AJ_APP_MESSAGE_ID(1, 2, 1)
#define APP_ARA_CASH_MINI  AJ_APP_PROPERTY_ID(1, 2, 2)

#define PRX_ARG_GET_PROP   AJ_PRX_MESSAGE_ID(0, 0, AJ_PROP_GET)
#define PRX_ARG_SET_PROP   AJ_PRX_MESSAGE_ID(0, 0, AJ_PROP_SET)
#define PRX_ARG_CALC_MARCH AJ_PRX_MESSAGE_ID(0, 1, 0)
#define PRX_ARG_CALC_MAKE  AJ_PRX_MESSAGE_ID(0, 1, 1)
#define PRX_ARG_CALC_MAYO  AJ_PRX_PROPERTY_ID(0, 1, 2)
#define PRX_ARG_CALI_METAL AJ_PRX_MESSAGE_ID(0, 2, 0)
#define PRX_ARG_CALI_MESS  AJ_PRX_MESSAGE_ID(0, 2, 1)
#define PRX_ARG_CALI_MEAL  AJ_PRX_PROPERTY_ID(0, 2, 2)

#define PRX_ARA_GET_PROP   AJ_PRX_MESSAGE_ID(1, 0, AJ_PROP_GET)
#define PRX_ARA_SET_PROP   AJ_PRX_MESSAGE_ID(1, 0, AJ_PROP_SET)
#define PRX_ARA_CAME_MOB   AJ_PRX_MESSAGE_ID(1, 1, 0)
#define PRX_ARA_CAME_MONEY AJ_PRX_MESSAGE_ID(1, 1, 1)
#define PRX_ARA_CAME_MOTEL AJ_PRX_PROPERTY_ID(1, 1, 2)
#define PRX_ARA_CASH_MINT  AJ_PRX_MESSAGE_ID(1, 2, 0)
#define PRX_ARA_CASH_MITS  AJ_PRX_MESSAGE_ID(1, 2, 1)
#define PRX_ARA_CASH_MINI  AJ_PRX_PROPERTY_ID(1, 2, 2)

int32_t arg_calc_mayo;
int32_t arg_cali_meal;
int32_t ara_came_motel;
int32_t ara_cash_mini;
static AJ_Status PropGetHandler(AJ_Message* msg, uint32_t id, void* context)
{
    QCC_UNUSED(context);
    switch (id) {
    case APP_ARG_CALC_MAYO:
        AJ_MarshalArgs(msg, "i", arg_calc_mayo);
        return AJ_OK;

    case APP_ARG_CALI_MEAL:
        AJ_MarshalArgs(msg, "i", arg_cali_meal);
        return AJ_OK;

    case APP_ARA_CAME_MOTEL:
        AJ_MarshalArgs(msg, "i", ara_came_motel);
        return AJ_OK;

    case APP_ARA_CASH_MINI:
        AJ_MarshalArgs(msg, "i", ara_cash_mini);
        return AJ_OK;

    default:
        return AJ_ERR_UNEXPECTED;
    }
}

static AJ_Status PropSetHandler(AJ_Message* msg, uint32_t id, void* context)
{
    QCC_UNUSED(context);
    switch (id) {
    case APP_ARG_CALC_MAYO:
        AJ_UnmarshalArgs(msg, "i", &arg_calc_mayo);
        return AJ_OK;

    case APP_ARG_CALI_MEAL:
        AJ_UnmarshalArgs(msg, "i", &arg_cali_meal);
        return AJ_OK;

    case APP_ARA_CAME_MOTEL:
        AJ_UnmarshalArgs(msg, "i", &ara_came_motel);
        return AJ_OK;

    case APP_ARA_CASH_MINI:
        AJ_UnmarshalArgs(msg, "i", &ara_cash_mini);
        return AJ_OK;

    default:
        return AJ_ERR_UNEXPECTED;
    }
}

class TCWildCardPolicyRulesAttachment : public TCBusAttachment {

  public:

    TCWildCardPolicyRulesAttachment(const char* name) : TCBusAttachment(name) {
        sessionPort = 0;
        arg_calc_mayo = 42;
        arg_cali_meal = 17;
        ara_came_motel = 42;
        ara_cash_mini = 17;
        signalReceivedFlag = FALSE;
        AJ_RegisterObjects(AppObjects, AppObjects);
    }

    /* Application handler */
    void RecvMessage(AJ_Message* msg) {
        AJ_Message reply;
        bool handled = TRUE;

        switch (msg->msgId) {
        /* Methods */
        case APP_ARG_CALC_MARCH:
        case APP_ARG_CALI_METAL:
        case APP_ARA_CAME_MOB:
        case APP_ARA_CASH_MINT:
            AJ_MarshalReplyMsg(msg, &reply);
            AJ_DeliverMsg(&reply);
            break;

        /* Signals */
        case APP_ARG_CALC_MAKE:
        case APP_ARG_CALI_MESS:
        case APP_ARA_CAME_MONEY:
        case APP_ARA_CASH_MITS:
            break;

        /* Properties */
        case APP_ARG_GET_PROP:
        case APP_ARA_GET_PROP:
            AJ_BusPropGet(msg, PropGetHandler, NULL);
            break;

        case APP_ARG_SET_PROP:
        case APP_ARA_SET_PROP:
            AJ_BusPropSet(msg, PropSetHandler, NULL);
            break;

        case AJ_REPLY_ID(PRX_ARG_CALC_MARCH):
        case AJ_REPLY_ID(PRX_ARG_CALI_METAL):
        case AJ_REPLY_ID(PRX_ARA_CAME_MOB):
        case AJ_REPLY_ID(PRX_ARA_CASH_MINT):
            if (AJ_MSG_ERROR == msg->hdr->msgType) {
                SCStatus = ER_BUS_REPLY_IS_ERROR_MESSAGE;
                response = msg->error;
            } else {
                SCStatus = ER_OK;
            }
            break;

        case AJ_REPLY_ID(PRX_ARG_GET_PROP):
        case AJ_REPLY_ID(PRX_ARA_GET_PROP):
            if (AJ_MSG_ERROR == msg->hdr->msgType) {
                SCStatus = ER_BUS_REPLY_IS_ERROR_MESSAGE;
                response = msg->error;
            } else {
                const char* sig;
                AJ_UnmarshalVariant(msg, &sig);
                AJ_UnmarshalArgs(msg, sig, &propval);
                SCStatus = ER_OK;
            }
            break;

        case AJ_REPLY_ID(PRX_ARG_SET_PROP):
        case AJ_REPLY_ID(PRX_ARA_SET_PROP):
            if (AJ_MSG_ERROR == msg->hdr->msgType) {
                SCStatus = ER_BUS_REPLY_IS_ERROR_MESSAGE;
                response = msg->error;
            } else {
                SCStatus = ER_OK;
            }
            break;

        default:
            handled = FALSE;
            break;
        }
        if (handled) {
            HandleMessage(msg);
        } else {
            TCBusAttachment::RecvMessage(msg);
        }
    }

    QStatus JoinSession(const char* host, uint16_t port, uint32_t& id) {
        QStatus status;
        status = TCBusAttachment::JoinSession(host, port, id);
        if (ER_OK == status) {
            status = AuthenticatePeer(host);
        }
        return status;
    }

    bool signalReceivedFlag;
    uint32_t propid;
    int32_t propval;
};

class WildCardPolicyRules_ApplicationStateListener : public ApplicationStateListener {
  public:
    WildCardPolicyRules_ApplicationStateListener() : stateMap() { }

    virtual void State(const char* busName, const qcc::KeyInfoNISTP256& publicKeyInfo, PermissionConfigurator::ApplicationState state) {
        QCC_UNUSED(publicKeyInfo);
        stateMap[busName] = state;
    }

    bool isClaimed(const String& busName) {
        if (stateMap.count(busName) > 0) {
            if (stateMap.find(busName)->second == PermissionConfigurator::ApplicationState::CLAIMED) {
                return true;
            }
        }
        return false;
    }
    map<String, PermissionConfigurator::ApplicationState> stateMap;
};

class WildCardPolicyRulesTestSessionPortListener : public SessionPortListener {
  public:
    virtual bool AcceptSessionJoiner(SessionPort sessionPort, const char* joiner, const SessionOpts& opts) {
        QCC_UNUSED(sessionPort);
        QCC_UNUSED(joiner);
        QCC_UNUSED(opts);
        return true;
    }
};

// String constants associated with the interfaces used for tests
namespace test {
    static const char argentinaObjPath[] = "/test/argentina";
    static const char arabicObjPath[] = "/test/arabic";
    namespace calcium {
        static const char InterfaceName[] = "test.calcium"; // Interface name
        namespace method {
            static const char march[] = "march"; //march method name
        }
        namespace signal {
            static const char make[] = "make"; //make signal name
        }
        namespace property {
            static const char mayonise[] = "mayonise"; //mayonise property name
        }
    }
    namespace california {
        static const char InterfaceName[] = "test.california"; // Interface name
        namespace method {
            static const char metal[] = "metal"; //metal method name
        }
        namespace signal {
            static const char mess[] = "mess"; //mess signal name
        }
        namespace property {
            static const char meal[] = "meal"; //meal property name
        }
    }
    namespace camera {
        static const char InterfaceName[] = "test.camera"; // Interface name
        namespace method {
            static const char mob[] = "mob"; //mob method name
        }
        namespace signal {
            static const char money[] = "money"; //money signal name
        }
        namespace property {
            static const char motel[] = "motel"; //motel property name
        }
    }
    namespace cashew {
        static const char InterfaceName[] = "test.cashew"; // Interface name
        namespace method {
            static const char mint[] = "mint"; //mint method name
        }
        namespace signal {
            static const char mits[] = "mits"; //mits signal name
        }
        namespace property {
            static const char mini[] = "mini"; //mini property name
        }
    }
}

class ArgentinaTestBusObject : public BusObject {
  public:
    ArgentinaTestBusObject(BusAttachment& bus, const char* path, bool announce = true)
        : BusObject(path), isAnnounced(announce), mayonise(42), meal(17) {
        const InterfaceDescription* calciumIface = bus.GetInterface(test::calcium::InterfaceName);
        EXPECT_TRUE(calciumIface != NULL) << "NULL InterfaceDescription* for " << test::calcium::InterfaceName;
        if (calciumIface == NULL) {
            printf("The interfaceDescription pointer for %s was NULL when it should not have been.\n", test::calcium::InterfaceName);
            return;
        }

        if (isAnnounced) {
            AddInterface(*calciumIface, ANNOUNCED);
        } else {
            AddInterface(*calciumIface, UNANNOUNCED);
        }

        /* Register the method handlers with the object */
        const MethodEntry calciumMethodEntries[] = {
            { calciumIface->GetMember(test::calcium::method::march), static_cast<MessageReceiver::MethodHandler>(&ArgentinaTestBusObject::March) }
        };
        EXPECT_EQ(ER_OK, AddMethodHandlers(calciumMethodEntries, sizeof(calciumMethodEntries) / sizeof(calciumMethodEntries[0])));

        const InterfaceDescription* californiaIface = bus.GetInterface(test::california::InterfaceName);
        EXPECT_TRUE(californiaIface != NULL) << "NULL InterfaceDescription* for " << test::california::InterfaceName;
        if (californiaIface == NULL) {
            printf("The interfaceDescription pointer for %s was NULL when it should not have been.\n", test::california::InterfaceName);
            return;
        }

        if (isAnnounced) {
            AddInterface(*californiaIface, ANNOUNCED);
        } else {
            AddInterface(*californiaIface, UNANNOUNCED);
        }

        /* Register the method handlers with the object */
        const MethodEntry californiaMethodEntries[] = {
            { californiaIface->GetMember(test::california::method::metal), static_cast<MessageReceiver::MethodHandler>(&ArgentinaTestBusObject::Metal) }
        };
        EXPECT_EQ(ER_OK, AddMethodHandlers(californiaMethodEntries, sizeof(californiaMethodEntries) / sizeof(californiaMethodEntries[0])));
    }

    void March(const InterfaceDescription::Member* member, Message& msg) {
        QCC_UNUSED(member);
        MsgArg* arg = NULL;
        QStatus status = MethodReply(msg, arg, 0);
        EXPECT_EQ(ER_OK, status) << "Echo: Error sending reply";
    }

    void Metal(const InterfaceDescription::Member* member, Message& msg) {
        QCC_UNUSED(member);
        MsgArg* arg = NULL;
        QStatus status = MethodReply(msg, arg, 0);
        EXPECT_EQ(ER_OK, status) << "Echo: Error sending reply";
    }

    QStatus Get(const char* ifcName, const char* propName, MsgArg& val)
    {
        QCC_UNUSED(ifcName);
        QStatus status = ER_OK;
        if (0 == strcmp(test::calcium::property::mayonise, propName)) {
            val.Set("i", mayonise);
        } else if (0 == strcmp(test::california::property::meal, propName)) {
            val.Set("i", meal);
        } else {
            status = ER_BUS_NO_SUCH_PROPERTY;
        }
        return status;

    }

    QStatus Set(const char* ifcName, const char* propName, MsgArg& val)
    {
        QCC_UNUSED(ifcName);
        QStatus status = ER_OK;
        if ((0 == strcmp(test::calcium::property::mayonise, propName)) && (val.typeId == ALLJOYN_INT32)) {
            val.Get("i", &mayonise);
        } else if ((0 == strcmp(test::california::property::meal, propName)) && (val.typeId == ALLJOYN_INT32)) {
            val.Get("i", &meal);
        } else {
            status = ER_BUS_NO_SUCH_PROPERTY;
        }
        return status;
    }
    int32_t ReadMayoniseProp() {
        return mayonise;
    }
    int32_t ReadMealProp() {
        return meal;
    }
  private:
    bool isAnnounced;
    int32_t mayonise;
    int32_t meal;
};

class SecurityWildCardSignalReceiver : public MessageReceiver {
  public:
    SecurityWildCardSignalReceiver() : signalReceivedFlag(false) { }
    void SignalHandler(const InterfaceDescription::Member* member,
                       const char* sourcePath, Message& msg) {
        QCC_UNUSED(member);
        QCC_UNUSED(sourcePath);
        QCC_UNUSED(msg);
        signalReceivedFlag = true;
    }
    bool signalReceivedFlag;
};

class ArabicTestBusObject : public BusObject {
  public:
    ArabicTestBusObject(BusAttachment& bus, const char* path, bool announce = true)
        : BusObject(path), isAnnounced(announce), motel(42), mini(17) {
        const InterfaceDescription* cameraIface = bus.GetInterface(test::camera::InterfaceName);
        EXPECT_TRUE(cameraIface != NULL) << "NULL InterfaceDescription* for " << test::camera::InterfaceName;
        if (cameraIface == NULL) {
            printf("The interfaceDescription pointer for %s was NULL when it should not have been.\n", test::camera::InterfaceName);
            return;
        }

        if (isAnnounced) {
            AddInterface(*cameraIface, ANNOUNCED);
        } else {
            AddInterface(*cameraIface, UNANNOUNCED);
        }

        /* Register the method handlers with the object */
        const MethodEntry cameraMethodEntries[] = {
            { cameraIface->GetMember(test::camera::method::mob), static_cast<MessageReceiver::MethodHandler>(&ArabicTestBusObject::Mob) }
        };
        EXPECT_EQ(ER_OK, AddMethodHandlers(cameraMethodEntries, sizeof(cameraMethodEntries) / sizeof(cameraMethodEntries[0])));

        const InterfaceDescription* cashewIface = bus.GetInterface(test::cashew::InterfaceName);
        EXPECT_TRUE(cashewIface != NULL) << "NULL InterfaceDescription* for " << test::cashew::InterfaceName;
        if (cashewIface == NULL) {
            printf("The interfaceDescription pointer for %s was NULL when it should not have been.\n", test::cashew::InterfaceName);
            return;
        }

        if (isAnnounced) {
            AddInterface(*cashewIface, ANNOUNCED);
        } else {
            AddInterface(*cashewIface, UNANNOUNCED);
        }

        /* Register the method handlers with the object */
        const MethodEntry cashewMethodEntries[] = {
            { cashewIface->GetMember(test::cashew::method::mint), static_cast<MessageReceiver::MethodHandler>(&ArabicTestBusObject::Mint) }
        };
        EXPECT_EQ(ER_OK, AddMethodHandlers(cashewMethodEntries, sizeof(cashewMethodEntries) / sizeof(cashewMethodEntries[0])));
    }

    void Mob(const InterfaceDescription::Member* member, Message& msg) {
        QCC_UNUSED(member);
        MsgArg* arg = NULL;
        QStatus status = MethodReply(msg, arg, 0);
        EXPECT_EQ(ER_OK, status) << "Echo: Error sending reply";
    }

    void Mint(const InterfaceDescription::Member* member, Message& msg) {
        QCC_UNUSED(member);
        MsgArg* arg = NULL;
        QStatus status = MethodReply(msg, arg, 0);
        EXPECT_EQ(ER_OK, status) << "Echo: Error sending reply";
    }

    QStatus Get(const char* ifcName, const char* propName, MsgArg& val)
    {
        QCC_UNUSED(ifcName);
        QStatus status = ER_OK;
        if (0 == strcmp(test::camera::property::motel, propName)) {
            val.Set("i", motel);
        } else if (0 == strcmp(test::cashew::property::mini, propName)) {
            val.Set("i", mini);
        } else {
            status = ER_BUS_NO_SUCH_PROPERTY;
        }
        return status;

    }

    QStatus Set(const char* ifcName, const char* propName, MsgArg& val)
    {
        QCC_UNUSED(ifcName);
        QStatus status = ER_OK;
        if ((0 == strcmp(test::camera::property::motel, propName)) && (val.typeId == ALLJOYN_INT32)) {
            val.Get("i", &motel);
        } else if ((0 == strcmp(test::cashew::property::mini, propName)) && (val.typeId == ALLJOYN_INT32)) {
            val.Get("i", &mini);
        } else {
            status = ER_BUS_NO_SUCH_PROPERTY;
        }
        return status;
    }
    int32_t ReadMayoniseProp() {
        return motel;
    }
    int32_t ReadMealProp() {
        return mini;
    }
  private:
    bool isAnnounced;
    int32_t motel;
    int32_t mini;
};

static void GetAppPublicKey(BusAttachment& bus, ECCPublicKey& publicKey)
{
    KeyInfoNISTP256 keyInfo;
    bus.GetPermissionConfigurator().GetSigningPublicKey(keyInfo);
    publicKey = *keyInfo.GetPublicKey();
}

class SecurityWildCardPolicyRulesTest : public testing::Test {
  public:
    SecurityWildCardPolicyRulesTest() :
        managerBus("SecurityPolicyRulesManager"),
        SCBus("SecurityPolicyRulesSC"),
        TCBus("SecurityPolicyRulesTC"),
        managerSessionPort(42),
        SCSessionPort(42),
        TCSessionPort(42),
        managerToManagerSessionId(0),
        managerToSCSessionId(0),
        managerToTCSessionId(0),
        calciumInterfaceName("test.calcium"),
        californiaInterfaceName("test.california"),
        cameraInterfaceName("test.camera"),
        cashewInterfaceName("test.cashew"),
        managerAuthListener(NULL),
        SCAuthListener(NULL),
        appStateListener()
    {
    }

    virtual void SetUp();

    virtual void TearDown();
    QStatus UpdatePolicyWithValuesFromDefaultPolicy(const PermissionPolicy& defaultPolicy,
                                                    PermissionPolicy& policy,
                                                    bool keepCAentry = true,
                                                    bool keepAdminGroupEntry = false,
                                                    bool keepInstallMembershipEntry = false);

    BusAttachment managerBus;
    BusAttachment SCBus;
    TCWildCardPolicyRulesAttachment TCBus;

    SessionPort managerSessionPort;
    SessionPort SCSessionPort;
    SessionPort TCSessionPort;

    WildCardPolicyRulesTestSessionPortListener managerSessionPortListener;
    WildCardPolicyRulesTestSessionPortListener SCSessionPortListener;

    SessionId managerToManagerSessionId;
    SessionId managerToSCSessionId;
    SessionId managerToTCSessionId;

    InMemoryKeyStoreListener managerKeyStoreListener;
    InMemoryKeyStoreListener SCKeyStoreListener;

    String interface;
    const char* calciumInterfaceName;
    const char* californiaInterfaceName;
    const char* cameraInterfaceName;
    const char* cashewInterfaceName;
    DefaultECDHEAuthListener* managerAuthListener;
    DefaultECDHEAuthListener* SCAuthListener;

    WildCardPolicyRules_ApplicationStateListener appStateListener;

    //Random GUID used for the SecurityManager
    GUID128 managerGuid;
};

void SecurityWildCardPolicyRulesTest::SetUp()
{
    EXPECT_EQ(ER_OK, managerBus.Start());
    EXPECT_EQ(ER_OK, managerBus.Connect());
    EXPECT_EQ(ER_OK, SCBus.Start());
    EXPECT_EQ(ER_OK, SCBus.Connect());

    // Register in memory keystore listeners
    EXPECT_EQ(ER_OK, managerBus.RegisterKeyStoreListener(managerKeyStoreListener));
    EXPECT_EQ(ER_OK, SCBus.RegisterKeyStoreListener(SCKeyStoreListener));

    managerAuthListener = new DefaultECDHEAuthListener();
    SCAuthListener = new DefaultECDHEAuthListener();

    // To avoid cross-talk, i.e. thin leaf node connect to unintended
    // routing nodes, generate and advertise a random routing node prefix.
    qcc::String routingNodePrefix = "test.rnPrefix.randhex" +
                                    qcc::RandHexString(64);
    qcc::String advertisingPrefix = "quiet@" + routingNodePrefix;
    ASSERT_EQ(ER_OK, managerBus.AdvertiseName(advertisingPrefix.c_str(), ajn::TRANSPORT_ANY));

    TCBus.Connect(routingNodePrefix.c_str());
    TCBus.Start();

    EXPECT_EQ(ER_OK, managerBus.EnablePeerSecurity("ALLJOYN_ECDHE_NULL ALLJOYN_ECDHE_ECDSA", managerAuthListener, NULL, true));
    EXPECT_EQ(ER_OK, SCBus.EnablePeerSecurity("ALLJOYN_ECDHE_NULL ALLJOYN_ECDHE_ECDSA", SCAuthListener));
    EXPECT_EQ(ER_OK, TCBus.EnablePeerSecurity("ALLJOYN_ECDHE_NULL ALLJOYN_ECDHE_ECDSA"));

    interface = "<node name='/test'>"
                "  <node name='/argentina'>"
                "  <interface name='test.calcium'>"
                "  <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
                "    <method name='march'></method>"
                "    <signal name='make'></signal>"
                "    <property name='mayonise' type='i' access='readwrite'/>"
                "  </interface>"
                "  <interface name='test.california'>"
                "  <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
                "    <method name='metal'></method>"
                "    <signal name='mess'></signal>"
                "    <property name='meal' type='i' access='readwrite'/>"
                "  </interface>"
                "  </node>"
                "  <node name='/arabic'>"
                "  <interface name='test.camera'>"
                "  <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
                "    <method name='mob'></method>"
                "    <signal name='money'></signal>"
                "    <property name='motel' type='i' access='readwrite'/>"
                "  </interface>"
                "  <interface name='test.cashew'>"
                "  <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
                "    <method name='mint'></method>"
                "    <signal name='mits'></signal>"
                "    <property name='mini' type='i' access='readwrite'/>"
                "  </interface>"
                "  </node>"
                "</node>";

    EXPECT_EQ(ER_OK, SCBus.CreateInterfacesFromXml(interface.c_str()));

    SessionOpts opts1;
    EXPECT_EQ(ER_OK, managerBus.BindSessionPort(managerSessionPort, opts1, managerSessionPortListener));

    SessionOpts opts2;
    EXPECT_EQ(ER_OK, SCBus.BindSessionPort(SCSessionPort, opts2, SCSessionPortListener));

    SessionOpts opts3;
    EXPECT_EQ(ER_OK, TCBus.BindSessionPort(TCSessionPort));

    EXPECT_EQ(ER_OK, managerBus.JoinSession(managerBus.GetUniqueName().c_str(), managerSessionPort, NULL, managerToManagerSessionId, opts1));
    EXPECT_EQ(ER_OK, managerBus.JoinSession(SCBus.GetUniqueName().c_str(), SCSessionPort, NULL, managerToSCSessionId, opts2));
    EXPECT_EQ(ER_OK, managerBus.JoinSession(TCBus.GetUniqueName().c_str(), TCSessionPort, NULL, managerToTCSessionId, opts3));

    SecurityApplicationProxy sapWithManager(managerBus, managerBus.GetUniqueName().c_str(), managerToManagerSessionId);
    PermissionConfigurator::ApplicationState applicationStateManager;
    EXPECT_EQ(ER_OK, sapWithManager.GetApplicationState(applicationStateManager));
    EXPECT_EQ(PermissionConfigurator::NOT_CLAIMABLE, applicationStateManager);

    SecurityApplicationProxy sapWithSC(managerBus, SCBus.GetUniqueName().c_str(), managerToSCSessionId);
    PermissionConfigurator::ApplicationState applicationStateSC;
    EXPECT_EQ(ER_OK, sapWithSC.GetApplicationState(applicationStateSC));
    EXPECT_EQ(PermissionConfigurator::NOT_CLAIMABLE, applicationStateSC);

    SecurityApplicationProxy sapWithTC(managerBus, TCBus.GetUniqueName().c_str(), managerToTCSessionId);
    PermissionConfigurator::ApplicationState applicationStateTC;
    EXPECT_EQ(ER_OK, sapWithTC.GetApplicationState(applicationStateTC));
    EXPECT_EQ(PermissionConfigurator::NOT_CLAIMABLE, applicationStateTC);

    managerBus.RegisterApplicationStateListener(appStateListener);
    managerBus.AddApplicationStateRule();

    // All Inclusive manifest
    PermissionPolicy::Rule::Member member[1];
    member[0].Set("*", PermissionPolicy::Rule::Member::NOT_SPECIFIED, PermissionPolicy::Rule::Member::ACTION_PROVIDE | PermissionPolicy::Rule::Member::ACTION_MODIFY | PermissionPolicy::Rule::Member::ACTION_OBSERVE);
    const size_t manifestSize = 1;
    PermissionPolicy::Rule manifest[manifestSize];
    manifest[0].SetObjPath("*");
    manifest[0].SetInterfaceName("*");
    manifest[0].SetMembers(1, member);

    //Get manager key
    KeyInfoNISTP256 managerKey;
    PermissionConfigurator& pcManager = managerBus.GetPermissionConfigurator();
    EXPECT_EQ(ER_OK, pcManager.GetSigningPublicKey(managerKey));

    //Create SC key
    KeyInfoNISTP256 SCKey;
    PermissionConfigurator& pcSC = SCBus.GetPermissionConfigurator();
    EXPECT_EQ(ER_OK, pcSC.GetSigningPublicKey(SCKey));

    //Create TC key
    ECCPublicKey TCPublicKey;
    EXPECT_EQ(ER_OK, sapWithTC.GetEccPublicKey(TCPublicKey));

    uint8_t digest[Crypto_SHA256::DIGEST_SIZE];
    EXPECT_EQ(ER_OK, PermissionMgmtObj::GenerateManifestDigest(managerBus,
                                                               manifest, manifestSize,
                                                               digest, Crypto_SHA256::DIGEST_SIZE)) << " GenerateManifestDigest failed.";

    //Create identityCert
    const size_t certChainSize = 1;
    IdentityCertificate identityCertChainMaster[certChainSize];

    EXPECT_EQ(ER_OK, PermissionMgmtTestHelper::CreateIdentityCert(managerBus,
                                                                  "0",
                                                                  managerGuid.ToString(),
                                                                  managerKey.GetPublicKey(),
                                                                  "ManagerAlias",
                                                                  3600,
                                                                  identityCertChainMaster[0],
                                                                  digest, Crypto_SHA256::DIGEST_SIZE)) << "Failed to create identity certificate.";

    SecurityApplicationProxy sapWithManagerBus(managerBus, managerBus.GetUniqueName().c_str());
    /* set claimable */
    managerBus.GetPermissionConfigurator().SetApplicationState(PermissionConfigurator::CLAIMABLE);
    EXPECT_EQ(ER_OK, sapWithManagerBus.Claim(managerKey,
                                             managerGuid,
                                             managerKey,
                                             identityCertChainMaster, certChainSize,
                                             manifest, manifestSize));

    for (int msec = 0; msec < 10000; msec += WAIT_MSECS) {
        if (appStateListener.isClaimed(managerBus.GetUniqueName())) {
            break;
        }
        qcc::Sleep(WAIT_MSECS);
    }

    ECCPublicKey managerPublicKey;
    GetAppPublicKey(managerBus, managerPublicKey);
    ASSERT_EQ(*managerKey.GetPublicKey(), managerPublicKey);

    ASSERT_EQ(PermissionConfigurator::ApplicationState::CLAIMED, appStateListener.stateMap[managerBus.GetUniqueName()]);

    //Create SC identityCert
    IdentityCertificate identityCertChainSC[certChainSize];


    EXPECT_EQ(ER_OK, PermissionMgmtTestHelper::CreateIdentityCert(managerBus,
                                                                  "0",
                                                                  managerGuid.ToString(),
                                                                  SCKey.GetPublicKey(),
                                                                  "SCAlias",
                                                                  3600,
                                                                  identityCertChainSC[0],
                                                                  digest, Crypto_SHA256::DIGEST_SIZE)) << "Failed to create identity certificate.";

    //Manager claims Peers
    /* set claimable */
    SCBus.GetPermissionConfigurator().SetApplicationState(PermissionConfigurator::CLAIMABLE);
    EXPECT_EQ(ER_OK, sapWithSC.Claim(managerKey,
                                        managerGuid,
                                        managerKey,
                                        identityCertChainSC, certChainSize,
                                        manifest, manifestSize));

    for (int msec = 0; msec < 10000; msec += WAIT_MSECS) {
        if (appStateListener.isClaimed(SCBus.GetUniqueName())) {
            break;
        }
        qcc::Sleep(WAIT_MSECS);
    }

    ASSERT_EQ(PermissionConfigurator::ApplicationState::CLAIMED, appStateListener.stateMap[SCBus.GetUniqueName()]);

    //Create TC identityCert
    IdentityCertificate identityCertChainTC[certChainSize];


    EXPECT_EQ(ER_OK, PermissionMgmtTestHelper::CreateIdentityCert(managerBus,
                                                                  "0",
                                                                  managerGuid.ToString(),
                                                                  &TCPublicKey,
                                                                  "TCAlias",
                                                                  3600,
                                                                  identityCertChainTC[0],
                                                                  digest, Crypto_SHA256::DIGEST_SIZE)) << "Failed to create identity certificate.";
    /* set claimable */
    TCBus.SetApplicationState(APP_STATE_CLAIMABLE);
    EXPECT_EQ(ER_OK, sapWithTC.SecureConnection(true));
    EXPECT_EQ(ER_OK, sapWithTC.Claim(managerKey,
                                        managerGuid,
                                        managerKey,
                                        identityCertChainTC, certChainSize,
                                        manifest, manifestSize));

    for (int msec = 0; msec < 10000; msec += WAIT_MSECS) {
        if (appStateListener.isClaimed(TCBus.GetUniqueName())) {
            break;
        }
        qcc::Sleep(WAIT_MSECS);
    }

    ASSERT_EQ(PermissionConfigurator::ApplicationState::CLAIMED, appStateListener.stateMap[TCBus.GetUniqueName()]);

    //Change the managerBus so it only uses ECDHE_ECDSA
    EXPECT_EQ(ER_OK, managerBus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA", managerAuthListener));

    String membershipSerial = "1";
    qcc::MembershipCertificate managerMembershipCertificate[1];
    EXPECT_EQ(ER_OK, PermissionMgmtTestHelper::CreateMembershipCert(membershipSerial,
                                                                    managerBus,
                                                                    managerBus.GetUniqueName(),
                                                                    managerKey.GetPublicKey(),
                                                                    managerGuid,
                                                                    false,
                                                                    3600,
                                                                    managerMembershipCertificate[0]
                                                                    ));
    EXPECT_EQ(ER_OK, sapWithManagerBus.InstallMembership(managerMembershipCertificate, 1));

    qcc::MembershipCertificate SCMembershipCertificate[1];
    EXPECT_EQ(ER_OK, PermissionMgmtTestHelper::CreateMembershipCert(membershipSerial,
                                                                    managerBus,
                                                                    SCBus.GetUniqueName(),
                                                                    SCKey.GetPublicKey(),
                                                                    managerGuid,
                                                                    false,
                                                                    3600,
                                                                    SCMembershipCertificate[0]
                                                                    ));
    EXPECT_EQ(ER_OK, SCBus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA", managerAuthListener, NULL, false));
    EXPECT_EQ(ER_OK, sapWithSC.InstallMembership(SCMembershipCertificate, 1));

    qcc::MembershipCertificate TCMembershipCertificate[1];
    EXPECT_EQ(ER_OK, PermissionMgmtTestHelper::CreateMembershipCert(membershipSerial,
                                                                    managerBus,
                                                                    TCBus.GetUniqueName(),
                                                                    &TCPublicKey,
                                                                    managerGuid,
                                                                    false,
                                                                    3600,
                                                                    TCMembershipCertificate[0]
                                                                    ));
    EXPECT_EQ(ER_OK, TCBus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, sapWithTC.InstallMembership(TCMembershipCertificate, 1));

    // Permission policy that will be installed on SC
    PermissionPolicy SCPolicy;
    SCPolicy.SetVersion(1);
    {
        PermissionPolicy::Acl acls[1];
        {
            PermissionPolicy::Peer peers[1];
            peers[0].SetType(PermissionPolicy::Peer::PEER_ANY_TRUSTED);
            acls[0].SetPeers(1, peers);
        }
        {
            PermissionPolicy::Rule rules[1];
            rules[0].SetObjPath("*");
            rules[0].SetInterfaceName("*");
            {
                PermissionPolicy::Rule::Member members[1];
                members[0].Set("*",
                               PermissionPolicy::Rule::Member::NOT_SPECIFIED,
                               PermissionPolicy::Rule::Member::ACTION_PROVIDE |
                               PermissionPolicy::Rule::Member::ACTION_MODIFY |
                               PermissionPolicy::Rule::Member::ACTION_OBSERVE);
                rules[0].SetMembers(1, members);
            }
            acls[0].SetRules(1, rules);
        }
        SCPolicy.SetAcls(1, acls);
    }

    {
        PermissionPolicy SCDefaultPolicy;
        EXPECT_EQ(ER_OK, sapWithSC.GetDefaultPolicy(SCDefaultPolicy));
        UpdatePolicyWithValuesFromDefaultPolicy(SCDefaultPolicy, SCPolicy);
    }

    EXPECT_EQ(ER_OK, sapWithSC.UpdatePolicy(SCPolicy));
    EXPECT_EQ(ER_OK, sapWithSC.SecureConnection(true));
}

void SecurityWildCardPolicyRulesTest::TearDown()
{
    TCBus.Stop();
    TCBus.Join();
    managerBus.Stop();
    managerBus.Join();
    SCBus.Stop();
    SCBus.Join();
    delete managerAuthListener;
    delete SCAuthListener;
}

QStatus SecurityWildCardPolicyRulesTest::UpdatePolicyWithValuesFromDefaultPolicy(const PermissionPolicy& defaultPolicy,
                                                                                 PermissionPolicy& policy,
                                                                                 bool keepCAentry,
                                                                                 bool keepAdminGroupEntry,
                                                                                 bool keepInstallMembershipEntry) {

    size_t count = policy.GetAclsSize();
    if (keepCAentry) {
        ++count;
    }
    if (keepAdminGroupEntry) {
        ++count;
    }
    if (keepInstallMembershipEntry) {
        ++count;
    }

    PermissionPolicy::Acl* acls = new PermissionPolicy::Acl[count];
    size_t idx = 0;
    for (size_t cnt = 0; cnt < defaultPolicy.GetAclsSize(); ++cnt) {
        if (defaultPolicy.GetAcls()[cnt].GetPeersSize() > 0) {
            if (defaultPolicy.GetAcls()[cnt].GetPeers()[0].GetType() == PermissionPolicy::Peer::PEER_FROM_CERTIFICATE_AUTHORITY) {
                if (keepCAentry) {
                    acls[idx++] = defaultPolicy.GetAcls()[cnt];
                }
            } else if (defaultPolicy.GetAcls()[cnt].GetPeers()[0].GetType() == PermissionPolicy::Peer::PEER_WITH_MEMBERSHIP) {
                if (keepAdminGroupEntry) {
                    acls[idx++] = defaultPolicy.GetAcls()[cnt];
                }
            } else if (defaultPolicy.GetAcls()[cnt].GetPeers()[0].GetType() == PermissionPolicy::Peer::PEER_WITH_PUBLIC_KEY) {
                if (keepInstallMembershipEntry) {
                    acls[idx++] = defaultPolicy.GetAcls()[cnt];
                }
            }
        }

    }
    for (size_t cnt = 0; cnt < policy.GetAclsSize(); ++cnt) {
        assert(idx <= count);
        acls[idx++] = policy.GetAcls()[cnt];
    }
    policy.SetAcls(count, acls);
    delete [] acls;
    return ER_OK;
}

/*
 * Purpose:
 * Verify that wild cards can be used in the Object Path
 * Set-Up:
 * Sender local policy rules
 * Rule 1:  Object path: /test/arg*  Interface: *  Member Name: * Member Type: (NS)  Action: PROVIDE
 *
 * Sender makes method call "march".
 * Sender makes method call "mint".
 *
 * Verification:
 * Verify that "march" method call is successful.
 * Verify that "mint" method call is not sent by the sender.
 */
TEST_F(SecurityWildCardPolicyRulesTest, Wildcard_object_path) {
    ArgentinaTestBusObject SCArgentinaBusObject(SCBus, test::argentinaObjPath);
    EXPECT_EQ(ER_OK, SCBus.RegisterBusObject(SCArgentinaBusObject));
    ArabicTestBusObject SCArabicBusObject(SCBus, test::arabicObjPath);
    EXPECT_EQ(ER_OK, SCBus.RegisterBusObject(SCArabicBusObject));

    // Permission policy that will be installed on TC
    PermissionPolicy TCPolicy;
    TCPolicy.SetVersion(1);
    {
        PermissionPolicy::Acl acls[1];
        {
            PermissionPolicy::Peer peers[1];
            peers[0].SetType(PermissionPolicy::Peer::PEER_ANY_TRUSTED);
            acls[0].SetPeers(1, peers);
        }
        {
            PermissionPolicy::Rule rules[1];
            rules[0].SetObjPath("/test/arg*");
            rules[0].SetInterfaceName("*");
            {
                PermissionPolicy::Rule::Member members[1];
                members[0].SetMemberName("*");
                members[0].SetActionMask(PermissionPolicy::Rule::Member::ACTION_PROVIDE);
                rules[0].SetMembers(1, members);
            }
            acls[0].SetRules(1, rules);
        }
        TCPolicy.SetAcls(1, acls);
    }

    SecurityApplicationProxy sapWithTC(managerBus, TCBus.GetUniqueName().c_str(), managerToTCSessionId);

    {
        PermissionPolicy TCDefaultPolicy;
        EXPECT_EQ(ER_OK, sapWithTC.GetDefaultPolicy(TCDefaultPolicy));
        UpdatePolicyWithValuesFromDefaultPolicy(TCDefaultPolicy, TCPolicy);
    }

    EXPECT_EQ(ER_OK, sapWithTC.UpdatePolicy(TCPolicy));

    SessionOpts opts;
    SessionId TCToSCSessionId;
    EXPECT_EQ(ER_OK, TCBus.JoinSession(SCBus.GetUniqueName().c_str(), SCSessionPort, TCToSCSessionId));

    qcc::String p1policyStr = "\n----TC Policy-----\n" + TCPolicy.ToString();
    SCOPED_TRACE(p1policyStr.c_str());

    /* Create the ProxyBusObject and call the march method on the test.calcium interface */
    EXPECT_EQ(ER_OK, TCBus.MethodCall(SCBus.GetUniqueName().c_str(), PRX_ARG_CALC_MARCH));

    /* Create the ProxyBusObject and call the march method on the test.calcium interface */
    EXPECT_EQ(ER_PERMISSION_DENIED, TCBus.MethodCall(SCBus.GetUniqueName().c_str(), PRX_ARA_CASH_MINT));
}

/*
 * Purpose:
 * Verify that wild cards can be used in the Interface name
 *
 * Set-Up:
 * Sender local policy rules
 * Rule 1:  Object path: *  Interface: test.cal*  Member Name: * Member Type: (NS)  Action: PROVIDE
 *
 * Sender makes method call "march".
 * Sender makes get property call "meal".
 * Sender makes a method call  "mob".
 * Sender makes a get property call "mini".
 *
 * Verification:
 * Verify that "march" method call is successful.
 * Verify that "meal" get property call is successful.
 * Verify that "mob" method call is not sent by the sender.
 * Verify that "mini" get property call is not sent by the sender.
 */
TEST_F(SecurityWildCardPolicyRulesTest, Wildcard_interface_names) {
    ArgentinaTestBusObject SCArgentinaBusObject(SCBus, test::argentinaObjPath);
    EXPECT_EQ(ER_OK, SCBus.RegisterBusObject(SCArgentinaBusObject));
    ArabicTestBusObject SCArabicBusObject(SCBus, test::arabicObjPath);
    EXPECT_EQ(ER_OK, SCBus.RegisterBusObject(SCArabicBusObject));

    // Permission policy that will be installed on TC
    PermissionPolicy TCPolicy;
    TCPolicy.SetVersion(1);
    {
        PermissionPolicy::Acl acls[1];
        {
            PermissionPolicy::Peer peers[1];
            peers[0].SetType(PermissionPolicy::Peer::PEER_ANY_TRUSTED);
            acls[0].SetPeers(1, peers);
        }
        {
            PermissionPolicy::Rule rules[1];
            rules[0].SetObjPath("*");
            rules[0].SetInterfaceName("test.cal*");
            {
                PermissionPolicy::Rule::Member members[1];
                members[0].SetMemberName("*");
                members[0].SetActionMask(PermissionPolicy::Rule::Member::ACTION_PROVIDE);
                rules[0].SetMembers(1, members);
            }
            acls[0].SetRules(1, rules);
        }
        TCPolicy.SetAcls(1, acls);
    }

    SecurityApplicationProxy sapWithTC(managerBus, TCBus.GetUniqueName().c_str(), managerToTCSessionId);

    {
        PermissionPolicy TCDefaultPolicy;
        EXPECT_EQ(ER_OK, sapWithTC.GetDefaultPolicy(TCDefaultPolicy));
        UpdatePolicyWithValuesFromDefaultPolicy(TCDefaultPolicy, TCPolicy);
    }

    EXPECT_EQ(ER_OK, sapWithTC.UpdatePolicy(TCPolicy));

    SessionOpts opts;
    SessionId TCToSCSessionId;
    EXPECT_EQ(ER_OK, TCBus.JoinSession(SCBus.GetUniqueName().c_str(), SCSessionPort, TCToSCSessionId));

    qcc::String p1policyStr = "\n----TC Policy-----\n" + TCPolicy.ToString();
    SCOPED_TRACE(p1policyStr.c_str());

    /* Create the ProxyBusObject and call the march method on the test.calcium interface */
    int32_t val;
    EXPECT_EQ(ER_OK, TCBus.MethodCall(SCBus.GetUniqueName().c_str(), PRX_ARG_CALC_MARCH));
    EXPECT_EQ(ER_OK, TCBus.GetProperty(SCBus.GetUniqueName().c_str(), PRX_ARG_GET_PROP, PRX_ARG_CALI_MEAL, val));

    /* Create the ProxyBusObject and call the march method on the test.camera interface */
    EXPECT_EQ(ER_PERMISSION_DENIED, TCBus.MethodCall(SCBus.GetUniqueName().c_str(), PRX_ARA_CAME_MOB));
    EXPECT_EQ(ER_PERMISSION_DENIED, TCBus.GetProperty(SCBus.GetUniqueName().c_str(), PRX_ARA_GET_PROP, PRX_ARA_CASH_MINI, val));
}

/*
 * Purpose:
 * Verify that wild cards can be used in member names
 *
 * Set-Up:
 * Sender local policy rules
 * Rule 1: Object Path: *  Interface: *  Member Name: mi*  Member Type: (NS)  Action: PROVIDE
 *
 * Sender makes a method call "metal".
 * Sender makes a method call  "mint".
 *
 * Verification:
 * Verify that "mint" method call is successful.
 * Verify that "metal" method call is not sent by the sender.
 */
TEST_F(SecurityWildCardPolicyRulesTest, Wildcard_member_names) {
    ArgentinaTestBusObject SCArgentinaBusObject(SCBus, test::argentinaObjPath);
    EXPECT_EQ(ER_OK, SCBus.RegisterBusObject(SCArgentinaBusObject));
    ArabicTestBusObject SCArabicBusObject(SCBus, test::arabicObjPath);
    EXPECT_EQ(ER_OK, SCBus.RegisterBusObject(SCArabicBusObject));

    // Permission policy that will be installed on TC
    PermissionPolicy TCPolicy;
    TCPolicy.SetVersion(1);
    {
        PermissionPolicy::Acl acls[1];
        {
            PermissionPolicy::Peer peers[1];
            peers[0].SetType(PermissionPolicy::Peer::PEER_ANY_TRUSTED);
            acls[0].SetPeers(1, peers);
        }
        {
            PermissionPolicy::Rule rules[1];
            rules[0].SetObjPath("*");
            rules[0].SetInterfaceName("*");
            {
                PermissionPolicy::Rule::Member members[1];
                members[0].SetMemberName("mi*");
                members[0].SetActionMask(PermissionPolicy::Rule::Member::ACTION_PROVIDE);
                rules[0].SetMembers(1, members);
            }
            acls[0].SetRules(1, rules);
        }
        TCPolicy.SetAcls(1, acls);
    }

    SecurityApplicationProxy sapWithTC(managerBus, TCBus.GetUniqueName().c_str(), managerToTCSessionId);

    {
        PermissionPolicy TCDefaultPolicy;
        EXPECT_EQ(ER_OK, sapWithTC.GetDefaultPolicy(TCDefaultPolicy));
        UpdatePolicyWithValuesFromDefaultPolicy(TCDefaultPolicy, TCPolicy);
    }

    EXPECT_EQ(ER_OK, sapWithTC.UpdatePolicy(TCPolicy));

    SessionOpts opts;
    SessionId TCToSCSessionId;
    EXPECT_EQ(ER_OK, TCBus.JoinSession(SCBus.GetUniqueName().c_str(), SCSessionPort, TCToSCSessionId));

    qcc::String p1policyStr = "\n----TC Policy-----\n" + TCPolicy.ToString();
    SCOPED_TRACE(p1policyStr.c_str());

    /* Create the ProxyBusObject and call the march method on the test.calcium interface */
    EXPECT_EQ(ER_PERMISSION_DENIED, TCBus.MethodCall(SCBus.GetUniqueName().c_str(), PRX_ARG_CALI_METAL));

    /* Create the ProxyBusObject and call the mint method on the test.cashew interface */
    EXPECT_EQ(ER_OK, TCBus.MethodCall(SCBus.GetUniqueName().c_str(), PRX_ARA_CASH_MINT));
}

/*
 * Purpose:
 * Verify that Message type is matched properly in the rule.
 *
 * Set-Up:
 * Sender local policy rules
 * Rule 1: Object Path: *  Interface: *  Member Name: *  Member Type: Method  Action: PROVIDE|OBSERVE
 *
 * Sender sends a signal "money".
 * Sender Sender makes a get property call "motel".
 * Sender Sender makes a method call  "mob".
 *
 * Verification:
 * Verify that "money" signal is not sent by the sender.
 * Verify that "motel" get property call is not sent by the sender.
 * Verify that "mob" method call is successful.
 */
TEST_F(SecurityWildCardPolicyRulesTest, Wildcard_message_type_matched_properly_in_rule) {
    ArgentinaTestBusObject SCArgentinaBusObject(SCBus, test::argentinaObjPath);
    EXPECT_EQ(ER_OK, SCBus.RegisterBusObject(SCArgentinaBusObject));
    ArabicTestBusObject SCArabicBusObject(SCBus, test::arabicObjPath);
    EXPECT_EQ(ER_OK, SCBus.RegisterBusObject(SCArabicBusObject));

    // Permission policy that will be installed on TC
    PermissionPolicy TCPolicy;
    TCPolicy.SetVersion(1);
    {
        PermissionPolicy::Acl acls[1];
        {
            PermissionPolicy::Peer peers[1];
            peers[0].SetType(PermissionPolicy::Peer::PEER_ANY_TRUSTED);
            acls[0].SetPeers(1, peers);
        }
        {
            PermissionPolicy::Rule rules[1];
            rules[0].SetObjPath("*");
            rules[0].SetInterfaceName("*");
            {
                PermissionPolicy::Rule::Member members[1];
                members[0].SetMemberName("*");
                members[0].SetMemberType(PermissionPolicy::Rule::Member::METHOD_CALL);
                members[0].SetActionMask(PermissionPolicy::Rule::Member::ACTION_PROVIDE |
                                         PermissionPolicy::Rule::Member::ACTION_OBSERVE);
                rules[0].SetMembers(1, members);
            }
            acls[0].SetRules(1, rules);
        }
        TCPolicy.SetAcls(1, acls);
    }

    SecurityApplicationProxy sapWithTC(managerBus, TCBus.GetUniqueName().c_str(), managerToTCSessionId);

    {
        PermissionPolicy TCDefaultPolicy;
        EXPECT_EQ(ER_OK, sapWithTC.GetDefaultPolicy(TCDefaultPolicy));
        UpdatePolicyWithValuesFromDefaultPolicy(TCDefaultPolicy, TCPolicy);
    }

    EXPECT_EQ(ER_OK, sapWithTC.UpdatePolicy(TCPolicy));

    SessionOpts opts;
    SessionId TCToSCSessionId;
    EXPECT_EQ(ER_OK, TCBus.JoinSession(SCBus.GetUniqueName().c_str(), SCSessionPort, TCToSCSessionId));

    qcc::String p1policyStr = "\n----TC Policy-----\n" + TCPolicy.ToString();
    SCOPED_TRACE(p1policyStr.c_str());

    /* Create the ProxyBusObject and call the mob method on the test.camera interface */
    int32_t val;
    EXPECT_EQ(ER_OK, TCBus.MethodCall(SCBus.GetUniqueName().c_str(), PRX_ARA_CAME_MOB));
    EXPECT_EQ(ER_PERMISSION_DENIED, TCBus.GetProperty(SCBus.GetUniqueName().c_str(), PRX_ARA_GET_PROP, PRX_ARA_CAME_MOTEL, val));

    SecurityWildCardSignalReceiver moneySignalReceiver;
    EXPECT_EQ(ER_OK, SCBus.RegisterSignalHandler(&moneySignalReceiver,
                                                    static_cast<MessageReceiver::SignalHandler>(&SecurityWildCardSignalReceiver::SignalHandler),
                                                    SCBus.GetInterface(test::camera::InterfaceName)->GetMember(test::camera::signal::money), NULL));

    EXPECT_EQ(ER_PERMISSION_DENIED, TCBus.Signal(SCBus.GetUniqueName().c_str(), PRX_ARA_CAME_MONEY));
}

/*
 * Purpose:
 * Verify that if the action mask is not specified, then the rule is explicitly
 * DENIED. The other rules are not even considered.
 *
 * Set-Up:
 * Sender local policy rules
 * Peer type: WITH_PUBIC_KEY KeyInfo: Peer2 Key
 * Rule 1: Object Path: *  Interface: *  Member Name:  *;   Member Type; NS;  Action: Not Specified
 * Rule 2: Object Path: *  Interface: *  Member Name:  *;   Member Type; NS;  Action: PROVIDE|OBSERVE
 *
 * Sender sends a signal "mess". It should not be sent.
 * Sender makes a get property call "meal". It should not be sent.
 * Sender makes a method call  "metal". It should not be sent.
 *
 * Verification:
 * Verify that "mess" signal is not sent by the sender.
 * Verify that "meal" get property call is not sent by the sender.
 * Verify that "metal" method call is not sent by the sender.
 */
TEST_F(SecurityWildCardPolicyRulesTest, unspecified_action_mask_is_explicitly_DENIED) {
    ArgentinaTestBusObject SCArgentinaBusObject(SCBus, test::argentinaObjPath);
    EXPECT_EQ(ER_OK, SCBus.RegisterBusObject(SCArgentinaBusObject));
    ArabicTestBusObject SCArabicBusObject(SCBus, test::arabicObjPath);
    EXPECT_EQ(ER_OK, SCBus.RegisterBusObject(SCArabicBusObject));

    // Permission policy that will be installed on TC
    PermissionPolicy TCPolicy;
    TCPolicy.SetVersion(1);
    {
        PermissionPolicy::Acl acls[1];
        {
            PermissionPolicy::Peer peers[1];
            peers[0].SetType(PermissionPolicy::Peer::PEER_WITH_PUBLIC_KEY);
            KeyInfoNISTP256 SCKey;
            PermissionConfigurator& pcSC = SCBus.GetPermissionConfigurator();
            EXPECT_EQ(ER_OK, pcSC.GetSigningPublicKey(SCKey));
            peers[0].SetKeyInfo(&SCKey);
            acls[0].SetPeers(1, peers);
        }
        {
            PermissionPolicy::Rule rules[2];
            rules[0].SetObjPath("*");
            rules[0].SetInterfaceName("*");
            {
                PermissionPolicy::Rule::Member members[1];
                members[0].SetMemberName("*");
                rules[0].SetMembers(1, members);
            }
            rules[1].SetObjPath("*");
            rules[1].SetInterfaceName("*");
            {
                PermissionPolicy::Rule::Member members[1];
                members[0].SetMemberName("*");
                members[0].SetActionMask(PermissionPolicy::Rule::Member::ACTION_PROVIDE |
                                         PermissionPolicy::Rule::Member::ACTION_OBSERVE);
                rules[1].SetMembers(1, members);
            }
            acls[0].SetRules(2, rules);
        }
        TCPolicy.SetAcls(1, acls);
    }

    SecurityApplicationProxy sapWithTC(managerBus, TCBus.GetUniqueName().c_str(), managerToTCSessionId);

    {
        PermissionPolicy TCDefaultPolicy;
        EXPECT_EQ(ER_OK, sapWithTC.GetDefaultPolicy(TCDefaultPolicy));
        UpdatePolicyWithValuesFromDefaultPolicy(TCDefaultPolicy, TCPolicy);
    }

    EXPECT_EQ(ER_OK, sapWithTC.UpdatePolicy(TCPolicy));

    SessionOpts opts;
    SessionId TCToSCSessionId;
    EXPECT_EQ(ER_OK, TCBus.JoinSession(SCBus.GetUniqueName().c_str(), SCSessionPort, TCToSCSessionId));

    qcc::String p1policyStr = "\n----TC Policy-----\n" + TCPolicy.ToString();
    SCOPED_TRACE(p1policyStr.c_str());

    /* Create the ProxyBusObject and call the mob method on the test.camera interface */
    int32_t val;
    EXPECT_EQ(ER_PERMISSION_DENIED, TCBus.MethodCall(SCBus.GetUniqueName().c_str(), PRX_ARG_CALI_METAL));
    EXPECT_EQ(ER_PERMISSION_DENIED, TCBus.GetProperty(SCBus.GetUniqueName().c_str(), PRX_ARG_GET_PROP, PRX_ARG_CALI_MEAL, val));

    SecurityWildCardSignalReceiver messSignalReceiver;
    EXPECT_EQ(ER_OK, SCBus.RegisterSignalHandler(&messSignalReceiver,
                                                    static_cast<MessageReceiver::SignalHandler>(&SecurityWildCardSignalReceiver::SignalHandler),
                                                    SCBus.GetInterface(test::california::InterfaceName)->GetMember(test::california::signal::mess), NULL));

    EXPECT_EQ(ER_PERMISSION_DENIED, TCBus.Signal(SCBus.GetUniqueName().c_str(), PRX_ARG_CALI_MESS));
}

/*
 * Purpose:
 * If the Object Path is not specified, then the rule is not considered as a match
 *
 * Set-Up:
 * Sender local policy rules
 * Rule 1: Object Path: NS  Interface: *  Member Name:  *;   Member Type; NS;  Action: PROVIDE
 *
 * Sender sends a method call "march".
 *
 * Verification:
 * Verify that "march" method call is not sent by the sender.
 */
TEST_F(SecurityWildCardPolicyRulesTest, object_path_not_specified_rule_not_considered_as_match) {
    ArgentinaTestBusObject SCArgentinaBusObject(SCBus, test::argentinaObjPath);
    EXPECT_EQ(ER_OK, SCBus.RegisterBusObject(SCArgentinaBusObject));
    ArabicTestBusObject SCArabicBusObject(SCBus, test::arabicObjPath);
    EXPECT_EQ(ER_OK, SCBus.RegisterBusObject(SCArabicBusObject));

    // Permission policy that will be installed on TC
    PermissionPolicy TCPolicy;
    TCPolicy.SetVersion(1);
    {
        PermissionPolicy::Acl acls[1];
        {
            PermissionPolicy::Peer peers[1];
            peers[0].SetType(PermissionPolicy::Peer::PEER_ANY_TRUSTED);
            acls[0].SetPeers(1, peers);
        }
        {
            PermissionPolicy::Rule rules[1];
            rules[0].SetInterfaceName("*");
            rules[0].SetObjPath("");
            {
                PermissionPolicy::Rule::Member members[1];
                members[0].SetMemberName("*");
                members[0].SetActionMask(PermissionPolicy::Rule::Member::ACTION_PROVIDE);
                rules[0].SetMembers(1, members);
            }
            acls[0].SetRules(1, rules);
        }
        TCPolicy.SetAcls(1, acls);
    }

    SecurityApplicationProxy sapWithTC(managerBus, TCBus.GetUniqueName().c_str(), managerToTCSessionId);

    {
        PermissionPolicy TCDefaultPolicy;
        EXPECT_EQ(ER_OK, sapWithTC.GetDefaultPolicy(TCDefaultPolicy));
        UpdatePolicyWithValuesFromDefaultPolicy(TCDefaultPolicy, TCPolicy);
    }

    EXPECT_EQ(ER_OK, sapWithTC.UpdatePolicy(TCPolicy));

    SessionOpts opts;
    SessionId TCToSCSessionId;
    EXPECT_EQ(ER_OK, TCBus.JoinSession(SCBus.GetUniqueName().c_str(), SCSessionPort, TCToSCSessionId));

    qcc::String p1policyStr = "\n----TC Policy-----\n" + TCPolicy.ToString();
    SCOPED_TRACE(p1policyStr.c_str());

    /* Create the ProxyBusObject and call the march method on the test.calcium interface */
    EXPECT_EQ(ER_PERMISSION_DENIED, TCBus.MethodCall(SCBus.GetUniqueName().c_str(), PRX_ARG_CALC_MARCH));
}

/*
 * Purpose:
 * If the Interface name is not specified, then the rule is not considered as a match.
 *
 * Set-Up:
 * Sender local policy rules
 * Rule 1: Object Path: *  Interface: NS  Member Name:  *;   Member Type; NS;  Action: PROVIDE
 *
 * Sender sends a method call "march".
 *
 * Verification:
 * Verify that "march" method call is not sent by the sender.
 */
TEST_F(SecurityWildCardPolicyRulesTest, interface_name_not_specified_rule_not_considered_as_match) {
    ArgentinaTestBusObject SCArgentinaBusObject(SCBus, test::argentinaObjPath);
    EXPECT_EQ(ER_OK, SCBus.RegisterBusObject(SCArgentinaBusObject));
    ArabicTestBusObject SCArabicBusObject(SCBus, test::arabicObjPath);
    EXPECT_EQ(ER_OK, SCBus.RegisterBusObject(SCArabicBusObject));

    // Permission policy that will be installed on TC
    PermissionPolicy TCPolicy;
    TCPolicy.SetVersion(1);
    {
        PermissionPolicy::Acl acls[1];
        {
            PermissionPolicy::Peer peers[1];
            peers[0].SetType(PermissionPolicy::Peer::PEER_ANY_TRUSTED);
            acls[0].SetPeers(1, peers);
        }
        {
            PermissionPolicy::Rule rules[1];
            rules[0].SetObjPath("*");
            {
                PermissionPolicy::Rule::Member members[1];
                members[0].SetMemberName("*");
                members[0].SetActionMask(PermissionPolicy::Rule::Member::ACTION_PROVIDE);
                rules[0].SetMembers(1, members);
            }
            acls[0].SetRules(1, rules);
        }
        TCPolicy.SetAcls(1, acls);
    }

    SecurityApplicationProxy sapWithTC(managerBus, TCBus.GetUniqueName().c_str(), managerToTCSessionId);

    {
        PermissionPolicy TCDefaultPolicy;
        EXPECT_EQ(ER_OK, sapWithTC.GetDefaultPolicy(TCDefaultPolicy));
        UpdatePolicyWithValuesFromDefaultPolicy(TCDefaultPolicy, TCPolicy);
    }

    EXPECT_EQ(ER_OK, sapWithTC.UpdatePolicy(TCPolicy));

    SessionOpts opts;
    SessionId TCToSCSessionId;
    EXPECT_EQ(ER_OK, TCBus.JoinSession(SCBus.GetUniqueName().c_str(), SCSessionPort, TCToSCSessionId));

    qcc::String p1policyStr = "\n----TC Policy-----\n" + TCPolicy.ToString();
    SCOPED_TRACE(p1policyStr.c_str());

    /* Create the ProxyBusObject and call the march method on the test.calcium interface */
    EXPECT_EQ(ER_PERMISSION_DENIED, TCBus.MethodCall(SCBus.GetUniqueName().c_str(), PRX_ARG_CALC_MARCH));
}

/*
 * Purpose:
 * Verify that empty string is not considered as a match.
 *
 * Set-Up:
 * Sender local policy rules
 * Rule 1: Object Path: *  Interface: *  Member Name:  "" (Empty String);   Member Type:  NS;  Action: PROVIDE
 *
 * Sender sends a method call "march".
 *
 * Verification:
 * Verify that "march" method call is not sent by the sender.
 */
TEST_F(SecurityWildCardPolicyRulesTest, empty_string_not_considered_as_match) {
    ArgentinaTestBusObject SCArgentinaBusObject(SCBus, test::argentinaObjPath);
    EXPECT_EQ(ER_OK, SCBus.RegisterBusObject(SCArgentinaBusObject));
    ArabicTestBusObject SCArabicBusObject(SCBus, test::arabicObjPath);
    EXPECT_EQ(ER_OK, SCBus.RegisterBusObject(SCArabicBusObject));

    // Permission policy that will be installed on TC
    PermissionPolicy TCPolicy;
    TCPolicy.SetVersion(1);
    {
        PermissionPolicy::Acl acls[1];
        {
            PermissionPolicy::Peer peers[1];
            peers[0].SetType(PermissionPolicy::Peer::PEER_ANY_TRUSTED);
            acls[0].SetPeers(1, peers);
        }
        {
            PermissionPolicy::Rule rules[1];
            rules[0].SetObjPath("*");
            rules[0].SetInterfaceName("*");
            {
                PermissionPolicy::Rule::Member members[1];
                members[0].SetMemberName("");
                members[0].SetActionMask(PermissionPolicy::Rule::Member::ACTION_PROVIDE);
                rules[0].SetMembers(1, members);
            }
            acls[0].SetRules(1, rules);
        }
        TCPolicy.SetAcls(1, acls);
    }

    SecurityApplicationProxy sapWithTC(managerBus, TCBus.GetUniqueName().c_str(), managerToTCSessionId);

    {
        PermissionPolicy TCDefaultPolicy;
        EXPECT_EQ(ER_OK, sapWithTC.GetDefaultPolicy(TCDefaultPolicy));
        UpdatePolicyWithValuesFromDefaultPolicy(TCDefaultPolicy, TCPolicy);
    }

    EXPECT_EQ(ER_OK, sapWithTC.UpdatePolicy(TCPolicy));

    SessionOpts opts;
    SessionId TCToSCSessionId;
    EXPECT_EQ(ER_OK, TCBus.JoinSession(SCBus.GetUniqueName().c_str(), SCSessionPort, TCToSCSessionId));

    qcc::String p1policyStr = "\n----TC Policy-----\n" + TCPolicy.ToString();
    SCOPED_TRACE(p1policyStr.c_str());

    /* Create the ProxyBusObject and call the march method on the test.calcium interface */
    EXPECT_EQ(ER_PERMISSION_DENIED, TCBus.MethodCall(SCBus.GetUniqueName().c_str(), PRX_ARG_CALC_MARCH));
}
