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
#include <alljoyn/AuthListener.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/SecurityApplicationProxy.h>
#include <qcc/CertificateHelper.h>
#include <iostream>
#include <map>
#include <memory>

#include "InMemoryKeyStore.h"
#include "PermissionMgmtObj.h"
#include "PermissionMgmtTest.h"

using namespace ajn;
using namespace qcc;
using namespace std;
/*
 * The unit test use many busy wait loops.  The busy wait loops were chosen
 * over thread sleeps because of the ease of understanding the busy wait loops.
 * Also busy wait loops do not require any platform specific threading code.
 */
#define WAIT_MSECS 5

/*
 * String constants used throughout this test file.
 */
static const char* ECHO_STRING = "String that should be Echoed back.";
static const char* CHIRP_STRING = "Chirp this string out in the signal.";
static const char* TEST_OBJ_PATH = "/test";

/**
 * This is a collection of misc. test cases that did not fit into another
 * category but are still related to security2.0 feature.
 * most of the tests are related to backward compatibility.
 */

static void GetAppPublicKey(BusAttachment& bus, ECCPublicKey& publicKey)
{
    KeyInfoNISTP256 keyInfo;
    bus.GetPermissionConfigurator().GetSigningPublicKey(keyInfo);
    publicKey = *keyInfo.GetPublicKey();
}

class SecurityOtherTestSessionPortListener : public SessionPortListener {
  public:
    virtual bool AcceptSessionJoiner(SessionPort sessionPort, const char* joiner, const SessionOpts& opts) {
        QCC_UNUSED(sessionPort);
        QCC_UNUSED(joiner);
        QCC_UNUSED(opts);
        return true;
    }
};

class SecurityOtherTestBusObject : public BusObject {
  public:
    SecurityOtherTestBusObject(BusAttachment& bus, const char* path, const char* interfaceName, bool announce = true)
        : BusObject(path), isAnnounced(announce), prop1(42), prop2(17) {
        const InterfaceDescription* iface = bus.GetInterface(interfaceName);
        EXPECT_TRUE(iface != NULL) << "NULL InterfaceDescription* for " << interfaceName;
        if (iface == NULL) {
            return;
        }

        if (isAnnounced) {
            AddInterface(*iface, ANNOUNCED);
        } else {
            AddInterface(*iface, UNANNOUNCED);
        }

        /* Register the method handlers with the object */
        const MethodEntry methodEntries[] = {
            { iface->GetMember("Echo"), static_cast<MessageReceiver::MethodHandler>(&SecurityOtherTestBusObject::Echo) }
        };
        EXPECT_EQ(ER_OK, AddMethodHandlers(methodEntries, sizeof(methodEntries) / sizeof(methodEntries[0])));
    }

    void Echo(const InterfaceDescription::Member* member, Message& msg) {
        QCC_UNUSED(member);
        const MsgArg* arg((msg->GetArg(0)));
        QStatus status = MethodReply(msg, arg, 1);
        EXPECT_EQ(ER_OK, status) << "Echo: Error sending reply";
    }

    QStatus Get(const char* ifcName, const char* propName, MsgArg& val)
    {
        QCC_UNUSED(ifcName);
        QStatus status = ER_OK;
        if (0 == strcmp("Prop1", propName)) {
            val.Set("i", prop1);
        } else if (0 == strcmp("Prop2", propName)) {
            val.Set("i", prop2);
        } else {
            status = ER_BUS_NO_SUCH_PROPERTY;
        }
        return status;

    }

    QStatus Set(const char* ifcName, const char* propName, MsgArg& val)
    {
        QCC_UNUSED(ifcName);
        QStatus status = ER_OK;
        if ((0 == strcmp("Prop1", propName)) && (val.typeId == ALLJOYN_INT32)) {
            val.Get("i", &prop1);
        } else if ((0 == strcmp("Prop2", propName)) && (val.typeId == ALLJOYN_INT32)) {
            val.Get("i", &prop2);
        } else {
            status = ER_BUS_NO_SUCH_PROPERTY;
        }
        return status;
    }
    int32_t ReadProp1() {
        return prop1;
    }
  private:
    bool isAnnounced;
    int32_t prop1;
    int32_t prop2;
};

class ChirpSignalReceiver : public MessageReceiver {
  public:
    ChirpSignalReceiver() : signalReceivedFlag(false) { }
    void ChirpSignalHandler(const InterfaceDescription::Member* member,
                            const char* sourcePath, Message& msg) {
        QCC_UNUSED(member);
        QCC_UNUSED(sourcePath);
        char* chirpStr;
        EXPECT_EQ(ER_OK, msg->GetArg(0)->Get("s", &chirpStr));
        EXPECT_STREQ(CHIRP_STRING, chirpStr);
        signalReceivedFlag = true;
    }
    bool signalReceivedFlag;
};

QStatus UpdatePolicyWithValuesFromDefaultPolicy(const PermissionPolicy& defaultPolicy,
                                                PermissionPolicy& policy,
                                                bool keepCAentry = true,
                                                bool keepAdminGroupEntry = false,
                                                bool keepInstallMembershipEntry = false) {

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

class SecurityOtherECDHE_ECDSAAuthListener : public AuthListener {
  public:
    SecurityOtherECDHE_ECDSAAuthListener() :
        requestCredentialsCalled(false),
        verifyCredentialsCalled(false),
        authenticationSuccessfull(false),
        securityViolationCalled(false)
    {
        cryptoECC.GenerateDSAKeyPair();
        CertificateX509::ValidPeriod validity;
        validity.validFrom = qcc::GetEpochTimestamp() / 1000;
        validity.validTo = validity.validFrom + 24 * 3600;
        CreateCert("1000",
                   "self",
                   "organization",
                   cryptoECC.GetDSAPrivateKey(),
                   cryptoECC.GetDSAPublicKey(),
                   "self",
                   cryptoECC.GetDSAPublicKey(),
                   validity,
                   false,
                   identityCert);
    }

    QStatus RequestCredentialsAsync(const char* authMechanism, const char* authPeer, uint16_t authCount, const char* userId, uint16_t credMask, void* context)
    {
        QCC_UNUSED(authPeer);
        QCC_UNUSED(authCount);
        QCC_UNUSED(userId);
        QCC_UNUSED(credMask);
        requestCredentialsCalled = true;
        Credentials creds;
        if (strcmp(authMechanism, "ALLJOYN_ECDHE_ECDSA") == 0) {
            if ((credMask& AuthListener::CRED_PRIVATE_KEY) == AuthListener::CRED_PRIVATE_KEY) {
                String pk;
                CertificateX509::EncodePrivateKeyPEM(cryptoECC.GetDSAPrivateKey(), pk);
                creds.SetPrivateKey(pk);
            }
            if ((credMask& AuthListener::CRED_CERT_CHAIN) == AuthListener::CRED_CERT_CHAIN) {
                creds.SetCertChain(identityCert.GetPEM());
            }
            return RequestCredentialsResponse(context, true, creds);
        }
        return RequestCredentialsResponse(context, false, creds);
    }
    QStatus VerifyCredentialsAsync(const char* authMechanism, const char* authPeer, const Credentials& creds, void* context) {
        QCC_UNUSED(authMechanism);
        QCC_UNUSED(authPeer);
        QCC_UNUSED(creds);
        verifyCredentialsCalled = true;
        if (strcmp(authMechanism, "ALLJOYN_ECDHE_ECDSA") == 0) {
            if (creds.IsSet(AuthListener::CRED_CERT_CHAIN)) {
                return VerifyCredentialsResponse(context, true);
            }
        }
        return VerifyCredentialsResponse(context, false);
    }

    void AuthenticationComplete(const char* authMechanism, const char* authPeer, bool success) {
        QCC_UNUSED(authMechanism);
        QCC_UNUSED(authPeer);
        QCC_UNUSED(success);
        if (success) {
            authenticationSuccessfull = true;
        }
    }

    void SecurityViolation(QStatus status, const Message& msg) {
        QCC_UNUSED(status);
        QCC_UNUSED(msg);
        securityViolationCalled = true;
    }

    QStatus CreateCert(const qcc::String& serial,
                       const qcc::String& issuer,
                       const qcc::String& organization,
                       const ECCPrivateKey* issuerPrivateKey,
                       const ECCPublicKey* issuerPublicKey,
                       const qcc::String& subject,
                       const ECCPublicKey* subjectPubKey,
                       CertificateX509::ValidPeriod& validity,
                       bool isCA,
                       CertificateX509& cert)
    {
        QStatus status = ER_CRYPTO_ERROR;

        cert.SetSerial((const uint8_t*)serial.data(), serial.size());
        cert.SetIssuerCN((const uint8_t*) issuer.c_str(), issuer.length());
        cert.SetSubjectCN((const uint8_t*) subject.c_str(), subject.length());
        if (!organization.empty()) {
            cert.SetIssuerOU((const uint8_t*) organization.c_str(), organization.length());
            cert.SetSubjectOU((const uint8_t*) organization.c_str(), organization.length());
        }
        cert.SetSubjectPublicKey(subjectPubKey);
        cert.SetCA(isCA);
        cert.SetValidity(&validity);
        status = cert.SignAndGenerateAuthorityKeyId(issuerPrivateKey, issuerPublicKey);
        return status;
    }

    bool requestCredentialsCalled;
    bool verifyCredentialsCalled;
    bool authenticationSuccessfull;
    bool securityViolationCalled;

    Crypto_ECC cryptoECC;
    IdentityCertificate identityCert;

};

/*
 * Purpose:
 * Two peers are not claimed can make method call over a ECDHE_ECDSA session.
 *
 * Setup:
 * Two peers who are not claimed make method call over an ECDHE_ECDSA session.
 *
 * Verification:
 * Verify that method call is successful. Verify that application provides
 * credentials via RequestCredentials callback.
 *
 * This test helps verify backward compatibility since it is using ECDHE_ECDSA
 * over using Security1.0.
 */
// Currently this is seeing the same issue as already reported for ASACORE-2287
// re-enable and Delete this comment once issue is fixed.
TEST(SecurityOtherTest, methodCallOverECDHE_ECDSASession) {
    BusAttachment peer1Bus("SecurityOtherPeer1", true);
    BusAttachment peer2Bus("SecurityOtherPeer2", true);

    EXPECT_EQ(ER_OK, peer1Bus.Start());
    EXPECT_EQ(ER_OK, peer1Bus.Connect());
    EXPECT_EQ(ER_OK, peer2Bus.Start());
    EXPECT_EQ(ER_OK, peer2Bus.Connect());

    InMemoryKeyStoreListener peer1KeyStoreListener;
    InMemoryKeyStoreListener peer2KeyStoreListener;

    // Register in memory keystore listeners
    EXPECT_EQ(ER_OK, peer1Bus.RegisterKeyStoreListener(peer1KeyStoreListener));
    EXPECT_EQ(ER_OK, peer2Bus.RegisterKeyStoreListener(peer2KeyStoreListener));

    SecurityOtherECDHE_ECDSAAuthListener peer1AuthListener;
    SecurityOtherECDHE_ECDSAAuthListener peer2AuthListener;

    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA", &peer1AuthListener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA", &peer2AuthListener));

    qcc::String interface = "<node>"
                            "<interface name='org.allseen.test.security.other'>"
                            "<annotation name='org.alljoyn.Bus.Secure' value='true'/>"
                            "  <method name='Echo'>"
                            "    <arg name='shout' type='s' direction='in'/>"
                            "    <arg name='reply' type='s' direction='out'/>"
                            "  </method>"
                            "  <signal name='Chirp'>"
                            "    <arg name='tweet' type='s'/>"
                            "  </signal>"
                            "  <property name='Prop1' type='i' access='readwrite'/>"
                            "  <property name='Prop2' type='i' access='readwrite'/>"
                            "</interface>"
                            "</node>";

    EXPECT_EQ(ER_OK, peer1Bus.CreateInterfacesFromXml(interface.c_str()));
    EXPECT_EQ(ER_OK, peer2Bus.CreateInterfacesFromXml(interface.c_str()));

    SecurityOtherTestBusObject peer2BusObject(peer2Bus, TEST_OBJ_PATH, "org.allseen.test.security.other");
    EXPECT_EQ(ER_OK, peer2Bus.RegisterBusObject(peer2BusObject, true));

    SessionOpts opts;
    SessionPort sessionPort = 42;
    SecurityOtherTestSessionPortListener sessionPortListener;
    EXPECT_EQ(ER_OK, peer2Bus.BindSessionPort(sessionPort, opts, sessionPortListener));

    uint32_t sessionId;
    EXPECT_EQ(ER_OK, peer1Bus.JoinSession(peer2Bus.GetUniqueName().c_str(), sessionPort, NULL, sessionId, opts));

    ProxyBusObject proxy(peer1Bus, peer2Bus.GetUniqueName().c_str(), TEST_OBJ_PATH, sessionId, true);
    EXPECT_EQ(ER_OK, proxy.ParseXml(interface.c_str()));
    EXPECT_TRUE(proxy.ImplementsInterface("org.allseen.test.security.other")) << interface.c_str() << "\n";

    MsgArg arg("s", ECHO_STRING);
    Message replyMsg(peer1Bus);
    EXPECT_EQ(ER_OK, proxy.MethodCall("org.allseen.test.security.other", "Echo", &arg, static_cast<size_t>(1), replyMsg));

    char* echoReply;
    EXPECT_EQ(ER_OK, replyMsg->GetArg(0)->Get("s", &echoReply));
    EXPECT_STREQ(ECHO_STRING, echoReply);

    EXPECT_TRUE(peer1AuthListener.requestCredentialsCalled);
    EXPECT_TRUE(peer1AuthListener.verifyCredentialsCalled);
    EXPECT_TRUE(peer1AuthListener.authenticationSuccessfull);
    EXPECT_FALSE(peer1AuthListener.securityViolationCalled);

    EXPECT_TRUE(peer2AuthListener.requestCredentialsCalled);
    EXPECT_TRUE(peer2AuthListener.verifyCredentialsCalled);
    EXPECT_TRUE(peer2AuthListener.authenticationSuccessfull);
    EXPECT_FALSE(peer2AuthListener.securityViolationCalled);
}

/*
 * Purpose:
 * Unsecure messages are not checked against rules. Test for Method calls,
 * get property calls, set property calls, sessionless signals.
 *
 * Setup:
 * Install policies on two peers that denies everything.
 *
 * Peer 1 makes a method call, get property, set property, get all properties call  to app. bus.
 * Peer 1 sends a signal to app. bus.
 * Peer 1 sends a store-and-forward signal to the app. bus
 *
 * Verification:
 * Verify that method call, get property, set property, get all properties call
 * to app. bus. are successful.
 * Verify that the signal is received by the app. bus.
 * Verify that the store-and-forward signal is received by the app. bus.
 */
TEST(SecurityOtherTest, unsecure_messages_not_blocked_by_policies_rules) {
    BusAttachment managerBus("SecurityOtherManager", true);
    BusAttachment peer1Bus("SecurityOtherPeer1", true);
    BusAttachment peer2Bus("SecurityOtherPeer2", true);

    EXPECT_EQ(ER_OK, managerBus.Start());
    EXPECT_EQ(ER_OK, managerBus.Connect());
    EXPECT_EQ(ER_OK, peer1Bus.Start());
    EXPECT_EQ(ER_OK, peer1Bus.Connect());
    EXPECT_EQ(ER_OK, peer2Bus.Start());
    EXPECT_EQ(ER_OK, peer2Bus.Connect());

    InMemoryKeyStoreListener managerKeyStoreListener;
    InMemoryKeyStoreListener peer1KeyStoreListener;
    InMemoryKeyStoreListener peer2KeyStoreListener;

    // Register in memory keystore listeners
    EXPECT_EQ(ER_OK, managerBus.RegisterKeyStoreListener(managerKeyStoreListener));
    EXPECT_EQ(ER_OK, peer1Bus.RegisterKeyStoreListener(peer1KeyStoreListener));
    EXPECT_EQ(ER_OK, peer2Bus.RegisterKeyStoreListener(peer2KeyStoreListener));

    DefaultECDHEAuthListener managerAuthListener;
    DefaultECDHEAuthListener peer1AuthListener;
    DefaultECDHEAuthListener peer2AuthListener;

    EXPECT_EQ(ER_OK, managerBus.EnablePeerSecurity("ALLJOYN_ECDHE_NULL ALLJOYN_ECDHE_ECDSA", &managerAuthListener));
    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_ECDHE_NULL ALLJOYN_ECDHE_ECDSA", &peer1AuthListener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_ECDHE_NULL ALLJOYN_ECDHE_ECDSA", &peer2AuthListener));

    qcc::String interface = "<node>"
                            "<interface name='org.allseen.test.security.other.secure'>"
                            "<annotation name='org.alljoyn.Bus.Secure' value='true'/>"
                            "  <method name='Echo'>"
                            "    <arg name='shout' type='s' direction='in'/>"
                            "    <arg name='reply' type='s' direction='out'/>"
                            "  </method>"
                            "  <signal name='Chirp'>"
                            "    <arg name='tweet' type='s'/>"
                            "  </signal>"
                            "  <property name='Prop1' type='i' access='readwrite'/>"
                            "  <property name='Prop2' type='i' access='readwrite'/>"
                            "</interface>"
                            "<interface name='org.allseen.test.security.other.insecure'>"
                            "<annotation name='org.alljoyn.Bus.Secure' value='false'/>"
                            "  <method name='Echo'>"
                            "    <arg name='shout' type='s' direction='in'/>"
                            "    <arg name='reply' type='s' direction='out'/>"
                            "  </method>"
                            "  <signal name='Chirp'>"
                            "    <arg name='tweet' type='s'/>"
                            "  </signal>"
                            "  <property name='Prop1' type='i' access='readwrite'/>"
                            "  <property name='Prop2' type='i' access='readwrite'/>"
                            "</interface>"
                            "</node>";

    EXPECT_EQ(ER_OK, peer1Bus.CreateInterfacesFromXml(interface.c_str()));
    EXPECT_EQ(ER_OK, peer2Bus.CreateInterfacesFromXml(interface.c_str()));

    SecurityOtherTestBusObject peer1SecureBusObject(peer1Bus, "/test/secure", "org.allseen.test.security.other.secure");
    SecurityOtherTestBusObject peer1InsecureBusObject(peer1Bus, "/test/insecure", "org.allseen.test.security.other.insecure");
    EXPECT_EQ(ER_OK, peer1Bus.RegisterBusObject(peer1SecureBusObject, true));
    EXPECT_EQ(ER_OK, peer1Bus.RegisterBusObject(peer1InsecureBusObject));

    SecurityOtherTestBusObject peer2SecureBusObject(peer2Bus, "/test/secure", "org.allseen.test.security.other.secure");
    SecurityOtherTestBusObject peer2InsecureBusObject(peer2Bus, "/test/insecure", "org.allseen.test.security.other.insecure");
    EXPECT_EQ(ER_OK, peer2Bus.RegisterBusObject(peer2SecureBusObject, true));
    EXPECT_EQ(ER_OK, peer2Bus.RegisterBusObject(peer2InsecureBusObject));

    SessionOpts opts1;
    SessionId managerToManagerSessionId;
    SessionPort managerSessionPort = 42;
    SecurityOtherTestSessionPortListener managerSessionPortListener;
    EXPECT_EQ(ER_OK, managerBus.BindSessionPort(managerSessionPort, opts1, managerSessionPortListener));

    SessionOpts opts2;
    SessionId managerToPeer1SessionId;
    SessionPort peer1SessionPort = 42;
    SecurityOtherTestSessionPortListener peer1SessionPortListener;
    EXPECT_EQ(ER_OK, peer1Bus.BindSessionPort(peer1SessionPort, opts2, peer1SessionPortListener));

    SessionOpts opts3;
    SessionId managerToPeer2SessionId;
    SessionPort peer2SessionPort = 42;
    SecurityOtherTestSessionPortListener peer2SessionPortListener;
    EXPECT_EQ(ER_OK, peer2Bus.BindSessionPort(peer2SessionPort, opts3, peer2SessionPortListener));

    EXPECT_EQ(ER_OK, managerBus.JoinSession(managerBus.GetUniqueName().c_str(), managerSessionPort, NULL, managerToManagerSessionId, opts1));
    EXPECT_EQ(ER_OK, managerBus.JoinSession(peer1Bus.GetUniqueName().c_str(), peer1SessionPort, NULL, managerToPeer1SessionId, opts2));
    EXPECT_EQ(ER_OK, managerBus.JoinSession(peer2Bus.GetUniqueName().c_str(), peer2SessionPort, NULL, managerToPeer2SessionId, opts3));

    //-----------------------Claim each bus Attachments------------------
    SecurityApplicationProxy sapWithManager(managerBus, managerBus.GetUniqueName().c_str(), managerToManagerSessionId);
    SecurityApplicationProxy sapWithPeer1(managerBus, peer1Bus.GetUniqueName().c_str(), managerToPeer1SessionId);
    SecurityApplicationProxy sapWithPeer2(managerBus, peer2Bus.GetUniqueName().c_str(), managerToPeer2SessionId);


    // All Inclusive manifest
    const size_t manifestSize = 1;
    PermissionPolicy::Rule manifest[manifestSize];
    manifest[0].SetObjPath("*");
    manifest[0].SetInterfaceName("*");
    {
        PermissionPolicy::Rule::Member member[1];
        member[0].Set("*",
                      PermissionPolicy::Rule::Member::NOT_SPECIFIED,
                      PermissionPolicy::Rule::Member::ACTION_PROVIDE |
                      PermissionPolicy::Rule::Member::ACTION_MODIFY |
                      PermissionPolicy::Rule::Member::ACTION_OBSERVE);
        manifest[0].SetMembers(1, member);
    }

    //Get manager key
    KeyInfoNISTP256 managerKey;
    PermissionConfigurator& pcManager = managerBus.GetPermissionConfigurator();
    EXPECT_EQ(ER_OK, pcManager.GetSigningPublicKey(managerKey));

    //Create peer1 key
    KeyInfoNISTP256 peer1Key;
    PermissionConfigurator& pcPeer1 = peer1Bus.GetPermissionConfigurator();
    EXPECT_EQ(ER_OK, pcPeer1.GetSigningPublicKey(peer1Key));

    //Create peer2 key
    KeyInfoNISTP256 peer2Key;
    PermissionConfigurator& pcPeer2 = peer2Bus.GetPermissionConfigurator();
    EXPECT_EQ(ER_OK, pcPeer2.GetSigningPublicKey(peer2Key));

    //------------ Claim self(managerBus), Peer1, and Peer2 --------
    //Random GUID used for the SecurityManager
    GUID128 managerGuid;

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

    /* set claimable */
    managerBus.GetPermissionConfigurator().SetApplicationState(PermissionConfigurator::CLAIMABLE);
    EXPECT_EQ(ER_OK, sapWithManager.Claim(managerKey,
                                          managerGuid,
                                          managerKey,
                                          identityCertChainMaster, certChainSize,
                                          manifest, manifestSize));


    ECCPublicKey managerPublicKey;
    GetAppPublicKey(managerBus, managerPublicKey);
    ASSERT_EQ(*managerKey.GetPublicKey(), managerPublicKey);

    //Create peer1 identityCert
    IdentityCertificate identityCertChainPeer1[certChainSize];


    EXPECT_EQ(ER_OK, PermissionMgmtTestHelper::CreateIdentityCert(managerBus,
                                                                  "0",
                                                                  managerGuid.ToString(),
                                                                  peer1Key.GetPublicKey(),
                                                                  "Peer1Alias",
                                                                  3600,
                                                                  identityCertChainPeer1[0],
                                                                  digest, Crypto_SHA256::DIGEST_SIZE)) << "Failed to create identity certificate.";

    //Manager claims Peers
    /* set claimable */
    peer1Bus.GetPermissionConfigurator().SetApplicationState(PermissionConfigurator::CLAIMABLE);
    EXPECT_EQ(ER_OK, sapWithPeer1.Claim(managerKey,
                                        managerGuid,
                                        managerKey,
                                        identityCertChainPeer1, certChainSize,
                                        manifest, manifestSize));

    //Create peer2 identityCert
    IdentityCertificate identityCertChainPeer2[certChainSize];

    EXPECT_EQ(ER_OK, PermissionMgmtTestHelper::CreateIdentityCert(managerBus,
                                                                  "0",
                                                                  managerGuid.ToString(),
                                                                  peer2Key.GetPublicKey(),
                                                                  "Peer2Alias",
                                                                  3600,
                                                                  identityCertChainPeer2[0],
                                                                  digest, Crypto_SHA256::DIGEST_SIZE)) << "Failed to create identity certificate.";
    /* set claimable */
    peer2Bus.GetPermissionConfigurator().SetApplicationState(PermissionConfigurator::CLAIMABLE);
    EXPECT_EQ(ER_OK, sapWithPeer2.Claim(managerKey,
                                        managerGuid,
                                        managerKey,
                                        identityCertChainPeer2, certChainSize,
                                        manifest, manifestSize));

    EXPECT_EQ(ER_OK, managerBus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA", &managerAuthListener));
    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA", &peer1AuthListener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA", &peer2AuthListener));

    //--------- InstallMembership certificates on self, peer1, and peer2

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
    EXPECT_EQ(ER_OK, sapWithManager.InstallMembership(managerMembershipCertificate, 1));

    qcc::MembershipCertificate peer1MembershipCertificate[1];
    EXPECT_EQ(ER_OK, PermissionMgmtTestHelper::CreateMembershipCert(membershipSerial,
                                                                    managerBus,
                                                                    peer1Bus.GetUniqueName(),
                                                                    peer1Key.GetPublicKey(),
                                                                    managerGuid,
                                                                    false,
                                                                    3600,
                                                                    peer1MembershipCertificate[0]
                                                                    ));

    EXPECT_EQ(ER_OK, sapWithPeer1.InstallMembership(peer1MembershipCertificate, 1));

    qcc::MembershipCertificate peer2MembershipCertificate[1];
    EXPECT_EQ(ER_OK, PermissionMgmtTestHelper::CreateMembershipCert(membershipSerial,
                                                                    managerBus,
                                                                    peer2Bus.GetUniqueName(),
                                                                    peer2Key.GetPublicKey(),
                                                                    managerGuid,
                                                                    false,
                                                                    3600,
                                                                    peer2MembershipCertificate[0]
                                                                    ));
    EXPECT_EQ(ER_OK, sapWithPeer2.InstallMembership(peer2MembershipCertificate, 1));

    //----------------Install Policy that denies everything--------------
    // To deny everything we just install a policy that is identical to the
    // default policy but removes the AdminGroup entry and the InstallMembership
    // Entry.  This is a policy that will deny eveything.
    {
        PermissionPolicy policy;
        policy.SetVersion(1);
        PermissionPolicy peer1DefaultPolicy;
        EXPECT_EQ(ER_OK, sapWithPeer1.GetDefaultPolicy(peer1DefaultPolicy));
        UpdatePolicyWithValuesFromDefaultPolicy(peer1DefaultPolicy, policy);
        EXPECT_EQ(ER_OK, sapWithPeer1.UpdatePolicy(policy));
        EXPECT_EQ(ER_OK, sapWithPeer1.SecureConnection(true));
    }
    {
        PermissionPolicy policy;
        policy.SetVersion(1);
        PermissionPolicy peer2DefaultPolicy;
        EXPECT_EQ(ER_OK, sapWithPeer2.GetDefaultPolicy(peer2DefaultPolicy));
        UpdatePolicyWithValuesFromDefaultPolicy(peer2DefaultPolicy, policy);
        EXPECT_EQ(ER_OK, sapWithPeer2.UpdatePolicy(policy));
        EXPECT_EQ(ER_OK, sapWithPeer2.SecureConnection(true));
    }

    uint32_t sessionId;
    EXPECT_EQ(ER_OK, peer1Bus.JoinSession(peer2Bus.GetUniqueName().c_str(), peer2SessionPort, NULL, sessionId, opts2));
    {
        // secure methods should fail
        // Try to make method call, get/set properties and send a signal the
        // policy should deny all interaction with the secure interface.  This
        // is done to verify we have a policy that denies everything.
        ProxyBusObject proxy(peer1Bus, peer2Bus.GetUniqueName().c_str(), "/test/secure", sessionId, true);
        EXPECT_EQ(ER_OK, proxy.ParseXml(interface.c_str()));
        EXPECT_TRUE(proxy.ImplementsInterface("org.allseen.test.security.other.secure")) << interface.c_str() << "\n";
        MsgArg arg("s", ECHO_STRING);
        Message replyMsg(peer1Bus);
        EXPECT_EQ(ER_PERMISSION_DENIED, proxy.MethodCall("org.allseen.test.security.other.secure", "Echo", &arg, static_cast<size_t>(1), replyMsg));

        MsgArg prop1Arg;
        EXPECT_EQ(ER_OK, prop1Arg.Set("i", 513));
        EXPECT_EQ(ER_PERMISSION_DENIED, proxy.SetProperty("org.allseen.test.security.other.secure", "Prop1", prop1Arg));

        EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetProperty("org.allseen.test.security.other.secure", "Prop1", prop1Arg));

        MsgArg props;
        EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetAllProperties("org.allseen.test.security.other.secure", props));

        MsgArg signalArg("s", CHIRP_STRING);
        // Signals are send and forget.  They will always return ER_OK.
        EXPECT_EQ(ER_PERMISSION_DENIED, peer1SecureBusObject.Signal(peer2Bus.GetUniqueName().c_str(),
                                                                    sessionId,
                                                                    *peer1Bus.GetInterface("org.allseen.test.security.other.secure")->GetMember("Chirp"),
                                                                    &signalArg, 1));
    }
    {
        // insecure methods should pass
        // Permission policies should no effect insecure interfaces.
        ProxyBusObject proxy(peer1Bus, peer2Bus.GetUniqueName().c_str(), "/test/insecure", sessionId);
        EXPECT_EQ(ER_OK, proxy.ParseXml(interface.c_str()));
        EXPECT_TRUE(proxy.ImplementsInterface("org.allseen.test.security.other.insecure")) << interface.c_str() << "\n";
        MsgArg arg("s", ECHO_STRING);
        Message replyMsg(peer1Bus);
        EXPECT_EQ(ER_OK, proxy.MethodCall("org.allseen.test.security.other.insecure", "Echo", &arg, static_cast<size_t>(1), replyMsg));

        char* echoReply;
        EXPECT_EQ(ER_OK, replyMsg->GetArg(0)->Get("s", &echoReply));
        EXPECT_STREQ(ECHO_STRING, echoReply);

        MsgArg prop1Arg;
        EXPECT_EQ(ER_OK, prop1Arg.Set("i", 513));
        EXPECT_EQ(ER_OK, proxy.SetProperty("org.allseen.test.security.other.insecure", "Prop1", prop1Arg));

        EXPECT_EQ(513, peer2InsecureBusObject.ReadProp1());

        EXPECT_EQ(ER_OK, proxy.GetProperty("org.allseen.test.security.other.insecure", "Prop1", prop1Arg));

        int32_t prop1;
        prop1Arg.Get("i", &prop1);
        EXPECT_EQ(513, prop1);

        MsgArg props;
        EXPECT_EQ(ER_OK, proxy.GetAllProperties("org.allseen.test.security.other.insecure", props));
        {
            int32_t prop1;
            MsgArg* propArg;
            EXPECT_EQ(ER_OK, props.GetElement("{sv}", "Prop1", &propArg)) << props.ToString().c_str();
            EXPECT_EQ(ER_OK, propArg->Get("i", &prop1)) << propArg->ToString().c_str();
            EXPECT_EQ(513, prop1);
        }
        {
            int32_t prop2;
            MsgArg* propArg;
            EXPECT_EQ(ER_OK, props.GetElement("{sv}", "Prop2", &propArg)) << props.ToString().c_str();
            EXPECT_EQ(ER_OK, propArg->Get("i", &prop2)) << propArg->ToString().c_str();
            EXPECT_EQ(17, prop2);
        }

        ChirpSignalReceiver chirpSignalReceiver;
        EXPECT_EQ(ER_OK, peer2Bus.RegisterSignalHandler(&chirpSignalReceiver,
                                                        static_cast<MessageReceiver::SignalHandler>(&ChirpSignalReceiver::ChirpSignalHandler),
                                                        peer1Bus.GetInterface("org.allseen.test.security.other.insecure")->GetMember("Chirp"),
                                                        NULL));

        MsgArg signalArg("s", CHIRP_STRING);
        // Signals are send and forget.  They will always return ER_OK.
        EXPECT_EQ(ER_OK, peer1InsecureBusObject.Signal(peer2Bus.GetUniqueName().c_str(),
                                                       sessionId,
                                                       *peer1Bus.GetInterface("org.allseen.test.security.other.insecure")->GetMember("Chirp"),
                                                       &signalArg, 1));

        //Wait for a maximum of 2 sec for the Chirp Signal.
        for (int msec = 0; msec < 2000; msec += WAIT_MSECS) {
            if (chirpSignalReceiver.signalReceivedFlag) {
                break;
            }
            qcc::Sleep(WAIT_MSECS);
        }

        EXPECT_TRUE(chirpSignalReceiver.signalReceivedFlag);
    }
}

class SecurityOtherECDHE_NULLAuthListener : public AuthListener {
  public:
    SecurityOtherECDHE_NULLAuthListener() :
        requestCredentialsCalled(false),
        verifyCredentialsCalled(false),
        authenticationSuccessfull(false),
        securityViolationCalled(false)
    {
    }

    QStatus RequestCredentialsAsync(const char* authMechanism, const char* authPeer, uint16_t authCount, const char* userId, uint16_t credMask, void* context)
    {
        QCC_UNUSED(authPeer);
        QCC_UNUSED(authCount);
        QCC_UNUSED(userId);
        QCC_UNUSED(credMask);
        requestCredentialsCalled = true;
        Credentials creds;
        if (strcmp(authMechanism, "ALLJOYN_ECDHE_NULL") == 0) {
            return RequestCredentialsResponse(context, true, creds);
        }
        return RequestCredentialsResponse(context, false, creds);
    }
    QStatus VerifyCredentialsAsync(const char* authMechanism, const char* authPeer, const Credentials& creds, void* context) {
        QCC_UNUSED(authMechanism);
        QCC_UNUSED(authPeer);
        QCC_UNUSED(creds);
        verifyCredentialsCalled = true;
        return VerifyCredentialsResponse(context, false);
    }

    void AuthenticationComplete(const char* authMechanism, const char* authPeer, bool success) {
        QCC_UNUSED(authMechanism);
        QCC_UNUSED(authPeer);
        QCC_UNUSED(success);
        if (success) {
            authenticationSuccessfull = true;
        }
    }

    void SecurityViolation(QStatus status, const Message& msg) {
        QCC_UNUSED(status);
        QCC_UNUSED(msg);
        securityViolationCalled = true;
    }
    bool requestCredentialsCalled;
    bool verifyCredentialsCalled;
    bool authenticationSuccessfull;
    bool securityViolationCalled;

};

/*
 * Purpose:
 * Before Claiming, properties on org.alljoyn.Bus.Security.Application should be
 * accessible via ECDHE_NULL auth .mechanism.
 *
 * Setup:
 * DUT is not claimed.
 *
 * DUT and a peer bus establish an ECDHE_NULL based session.
 * A bus calls GetAll properties on org.alljoyn.Bus.Security.Application interface.
 *
 * Verification:
 * The following properties should be fetched:
 * "Version"  Expected value=1
 * "ApplicationState"  Expected value="Claimable"
 * "ManifestTemplateDigest"  Expected value=Unknown
 * "EccPublicKey"  Expected value=Public key of DUT
 * "ManufacturerCertificate"  Expected value=empty array
 * "ManifestTemplate"  Expected value=Unknown
 * "ClaimCapabilities"  Expected value=Unknown
 */
TEST(SecurityOtherTest, call_security_application_over_ECDHE_NULL) {
    BusAttachment peer1Bus("SecurityOtherPeer1", true);
    BusAttachment peer2Bus("SecurityOtherPeer2", true);

    EXPECT_EQ(ER_OK, peer1Bus.Start());
    EXPECT_EQ(ER_OK, peer1Bus.Connect());
    EXPECT_EQ(ER_OK, peer2Bus.Start());
    EXPECT_EQ(ER_OK, peer2Bus.Connect());

    InMemoryKeyStoreListener peer1KeyStoreListener;
    InMemoryKeyStoreListener peer2KeyStoreListener;

    // Register in memory keystore listeners
    EXPECT_EQ(ER_OK, peer1Bus.RegisterKeyStoreListener(peer1KeyStoreListener));
    EXPECT_EQ(ER_OK, peer2Bus.RegisterKeyStoreListener(peer2KeyStoreListener));

    SecurityOtherECDHE_NULLAuthListener peer1AuthListener;
    SecurityOtherECDHE_NULLAuthListener peer2AuthListener;

    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_ECDHE_NULL", &peer1AuthListener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_ECDHE_NULL", &peer2AuthListener));

    SessionOpts opts;
    SessionPort sessionPort = 42;
    SecurityOtherTestSessionPortListener sessionPortListener;
    EXPECT_EQ(ER_OK, peer2Bus.BindSessionPort(sessionPort, opts, sessionPortListener));

    uint32_t sessionId;
    EXPECT_EQ(ER_OK, peer1Bus.JoinSession(peer2Bus.GetUniqueName().c_str(), sessionPort, NULL, sessionId, opts));

    SecurityApplicationProxy proxy(peer1Bus, peer2Bus.GetUniqueName().c_str(), sessionId);

    // "Version"  Expected value=1
    uint16_t secuirtyApplicaitonVersion = 0;
    EXPECT_EQ(ER_OK, proxy.GetSecurityApplicationVersion(secuirtyApplicaitonVersion));
    EXPECT_EQ(1, secuirtyApplicaitonVersion);

    // "ApplicationState"  Expected value="Not Claimable"
    PermissionConfigurator::ApplicationState applicationState;
    EXPECT_EQ(ER_OK, proxy.GetApplicationState(applicationState));
    EXPECT_EQ(PermissionConfigurator::NOT_CLAIMABLE, applicationState);

    // "ManifestTemplateDigest"  Expected value=Unknown
    uint8_t manifestTemplateDigest[qcc::Crypto_SHA256::DIGEST_SIZE];
    EXPECT_EQ(ER_BAD_ARG_2, proxy.GetManifestTemplateDigest(manifestTemplateDigest, qcc::Crypto_SHA256::DIGEST_SIZE));

    // "EccPublicKey"  Expected value=Public key of DUT
    qcc::ECCPublicKey eccPublicKey;
    EXPECT_EQ(ER_OK, proxy.GetEccPublicKey(eccPublicKey));
    PermissionConfigurator& pcPeer2 = peer2Bus.GetPermissionConfigurator();
    KeyInfoNISTP256 peer2KeyInfo;
    EXPECT_EQ(ER_OK, pcPeer2.GetSigningPublicKey(peer2KeyInfo));
    EXPECT_EQ(*peer2KeyInfo.GetPublicKey(), eccPublicKey);

    // "ManufacturerCertificate"  Expected value=empty array
    MsgArg manufacturerCertificate;
    EXPECT_EQ(ER_OK, proxy.GetManufacturerCertificate(manufacturerCertificate));
    EXPECT_EQ((size_t)0, manufacturerCertificate.v_array.GetNumElements());

    // "ManifestTemplate"  Expected value=Unknown
    MsgArg manifestTemplate;
    EXPECT_EQ(ER_OK, proxy.GetManifestTemplate(manifestTemplate));
    // manifestTemplate should be empty
    EXPECT_EQ((size_t)0, manifestTemplate.v_array.GetNumElements());

    // "ClaimCapabilities"  Expected value=Unknown
    PermissionConfigurator::ClaimCapabilities claimCapabilities;
    EXPECT_EQ(ER_OK, proxy.GetClaimCapabilities(claimCapabilities));
    EXPECT_EQ(PermissionConfigurator::CAPABLE_ECDHE_NULL, claimCapabilities);

    MsgArg props;
    EXPECT_EQ(ER_OK, proxy.GetAllProperties(org::alljoyn::Bus::Security::Application::InterfaceName, props));
    // check GetAllProperties contains the values from org.alljoyn.Bus.Security.Application interface
    // The value of each element was already checked above. Just check the GetAllProperties
    // have an entry for each property we are interested in.
    MsgArg* propArg;
    EXPECT_EQ(ER_OK, props.GetElement("{sv}", "Version", &propArg)) << props.ToString().c_str();
    EXPECT_EQ(ER_OK, props.GetElement("{sv}", "ApplicationState", &propArg)) << props.ToString().c_str();
    EXPECT_EQ(ER_OK, props.GetElement("{sv}", "ManifestTemplateDigest", &propArg)) << props.ToString().c_str();
    EXPECT_EQ(ER_OK, props.GetElement("{sv}", "EccPublicKey", &propArg)) << props.ToString().c_str();
    EXPECT_EQ(ER_OK, props.GetElement("{sv}", "ManufacturerCertificate", &propArg)) << props.ToString().c_str();
    EXPECT_EQ(ER_OK, props.GetElement("{sv}", "ManifestTemplate", &propArg)) << props.ToString().c_str();
    EXPECT_EQ(ER_OK, props.GetElement("{sv}", "ClaimCapabilities", &propArg)) << props.ToString().c_str();

    peer1Bus.Stop();
    peer1Bus.Join();
    peer2Bus.Stop();
    peer2Bus.Join();
}

class SecurityOtherSRPAuthListener : public AuthListener {
  public:
    SecurityOtherSRPAuthListener() :
        requestCredentialsCalled(false),
        verifyCredentialsCalled(false),
        authenticationSuccessfull(false),
        securityViolationCalled(false)
    {
    }

    QStatus RequestCredentialsAsync(const char* authMechanism, const char* authPeer, uint16_t authCount, const char* userId, uint16_t credMask, void* context)
    {
        QCC_UNUSED(userId);
        QCC_UNUSED(authCount);
        QCC_UNUSED(authPeer);
        requestCredentialsCalled = true;
        Credentials creds;
        if (strcmp(authMechanism, "ALLJOYN_SRP_KEYX") == 0) {
            if (credMask & AuthListener::CRED_PASSWORD) {
                creds.SetPassword("123456");
            }
            return RequestCredentialsResponse(context, true, creds);
        }
        return RequestCredentialsResponse(context, false, creds);
    }
    QStatus VerifyCredentialsAsync(const char* authMechanism, const char* authPeer, const Credentials& creds, void* context) {
        QCC_UNUSED(authMechanism);
        QCC_UNUSED(authPeer);
        QCC_UNUSED(creds);
        verifyCredentialsCalled = true;
        return VerifyCredentialsResponse(context, false);
    }

    void AuthenticationComplete(const char* authMechanism, const char* authPeer, bool success) {
        QCC_UNUSED(authMechanism);
        QCC_UNUSED(authPeer);
        QCC_UNUSED(success);
        if (success) {
            authenticationSuccessfull = true;
        }
    }

    void SecurityViolation(QStatus status, const Message& msg) {
        QCC_UNUSED(status);
        QCC_UNUSED(msg);
        securityViolationCalled = true;
    }
    bool requestCredentialsCalled;
    bool verifyCredentialsCalled;
    bool authenticationSuccessfull;
    bool securityViolationCalled;

};

/*
 * Purpose:
 * Before Claiming, properties on org.alljoyn.Bus.Security.Application should be
 * accessible via SRP auth .mechanism.
 *
 * Setup:
 * DUT is not claimed.
 *
 * DUT and a peer bus establish an SRP based session.
 * A bus calls GetAll properties on org.alljoyn.Bus.Security.Application interface.
 *
 * Verification:
 * The following properties should be fetched:
 * "Version"  Expected value=1
 * "ApplicationState"  Expected value="Claimable"
 * "ManifestTemplateDigest"  Expected value=Unknown
 * "EccPublicKey"  Expected value=Public key of DUT
 * "ManufacturerCertificate"  Expected value=empty array
 * "ManifestTemplate"  Expected value=Unknown
 * "ClaimCapabilities"  Expected value=Unknown
 */
TEST(SecurityOtherTest, call_security_application_over_SRP) {
    BusAttachment peer1Bus("SecurityOtherPeer1", true);
    BusAttachment peer2Bus("SecurityOtherPeer2", true);

    EXPECT_EQ(ER_OK, peer1Bus.Start());
    EXPECT_EQ(ER_OK, peer1Bus.Connect());
    EXPECT_EQ(ER_OK, peer2Bus.Start());
    EXPECT_EQ(ER_OK, peer2Bus.Connect());

    InMemoryKeyStoreListener peer1KeyStoreListener;
    InMemoryKeyStoreListener peer2KeyStoreListener;

    // Register in memory keystore listeners
    EXPECT_EQ(ER_OK, peer1Bus.RegisterKeyStoreListener(peer1KeyStoreListener));
    EXPECT_EQ(ER_OK, peer2Bus.RegisterKeyStoreListener(peer2KeyStoreListener));

    SecurityOtherSRPAuthListener peer1AuthListener;
    SecurityOtherSRPAuthListener peer2AuthListener;

    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_SRP_KEYX", &peer1AuthListener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_SRP_KEYX", &peer2AuthListener));

    SessionOpts opts;
    SessionPort sessionPort = 42;
    SecurityOtherTestSessionPortListener sessionPortListener;
    EXPECT_EQ(ER_OK, peer2Bus.BindSessionPort(sessionPort, opts, sessionPortListener));

    uint32_t sessionId;
    EXPECT_EQ(ER_OK, peer1Bus.JoinSession(peer2Bus.GetUniqueName().c_str(), sessionPort, NULL, sessionId, opts));

    SecurityApplicationProxy proxy(peer1Bus, peer2Bus.GetUniqueName().c_str(), sessionId);

    // "Version"  Expected value=1
    uint16_t secuirtyApplicaitonVersion = 0;
    EXPECT_EQ(ER_OK, proxy.GetSecurityApplicationVersion(secuirtyApplicaitonVersion));
    EXPECT_EQ(1, secuirtyApplicaitonVersion);

    // "ApplicationState"  Expected value="Not Claimable"
    PermissionConfigurator::ApplicationState applicationState;
    EXPECT_EQ(ER_OK, proxy.GetApplicationState(applicationState));
    EXPECT_EQ(PermissionConfigurator::NOT_CLAIMABLE, applicationState);

    // "ManifestTemplateDigest"  Expected value=Unknown
    uint8_t manifestTemplateDigest[qcc::Crypto_SHA256::DIGEST_SIZE];
    EXPECT_EQ(ER_BAD_ARG_2, proxy.GetManifestTemplateDigest(manifestTemplateDigest, qcc::Crypto_SHA256::DIGEST_SIZE));

    // "EccPublicKey"  Expected value=Public key of DUT
    qcc::ECCPublicKey eccPublicKey;
    EXPECT_EQ(ER_OK, proxy.GetEccPublicKey(eccPublicKey));
    PermissionConfigurator& pcPeer2 = peer2Bus.GetPermissionConfigurator();
    KeyInfoNISTP256 peer2KeyInfo;
    EXPECT_EQ(ER_OK, pcPeer2.GetSigningPublicKey(peer2KeyInfo));
    EXPECT_EQ(*peer2KeyInfo.GetPublicKey(), eccPublicKey);

    // "ManufacturerCertificate"  Expected value=empty array
    MsgArg manufacturerCertificate;
    EXPECT_EQ(ER_OK, proxy.GetManufacturerCertificate(manufacturerCertificate));
    EXPECT_EQ((size_t)0, manufacturerCertificate.v_array.GetNumElements());

    // "ManifestTemplate"  Expected value=Unknown
    MsgArg manifestTemplate;
    EXPECT_EQ(ER_OK, proxy.GetManifestTemplate(manifestTemplate));
    // manifestTemplate should be empty
    EXPECT_EQ((size_t)0, manifestTemplate.v_array.GetNumElements());

    // "ClaimCapabilities"  Expected value=Unknown
    PermissionConfigurator::ClaimCapabilities claimCapabilities;
    EXPECT_EQ(ER_OK, proxy.GetClaimCapabilities(claimCapabilities));
    EXPECT_EQ(PermissionConfigurator::CAPABLE_ECDHE_NULL, claimCapabilities);

    MsgArg props;
    EXPECT_EQ(ER_OK, proxy.GetAllProperties(org::alljoyn::Bus::Security::Application::InterfaceName, props));
    // check GetAllProperties contains the values from org.alljoyn.Bus.Security.Application interface
    // The value of each element was already checked above. Just check the GetAllProperties
    // have an entry for each property we are interested in.
    MsgArg* propArg;
    EXPECT_EQ(ER_OK, props.GetElement("{sv}", "Version", &propArg)) << props.ToString().c_str();
    EXPECT_EQ(ER_OK, props.GetElement("{sv}", "ApplicationState", &propArg)) << props.ToString().c_str();
    EXPECT_EQ(ER_OK, props.GetElement("{sv}", "ManifestTemplateDigest", &propArg)) << props.ToString().c_str();
    EXPECT_EQ(ER_OK, props.GetElement("{sv}", "EccPublicKey", &propArg)) << props.ToString().c_str();
    EXPECT_EQ(ER_OK, props.GetElement("{sv}", "ManufacturerCertificate", &propArg)) << props.ToString().c_str();
    EXPECT_EQ(ER_OK, props.GetElement("{sv}", "ManifestTemplate", &propArg)) << props.ToString().c_str();
    EXPECT_EQ(ER_OK, props.GetElement("{sv}", "ClaimCapabilities", &propArg)) << props.ToString().c_str();

    peer1Bus.Stop();
    peer1Bus.Join();
    peer2Bus.Stop();
    peer2Bus.Join();
}

/*
 * Purpose:
 * Before Claiming, properties on org.alljoyn.Bus.Security.Application should be
 * accessible via ECDHE_ECDSA auth .mechanism.
 *
 * Setup:
 * DUT is not claimed.
 *
 * DUT and a peer bus establish an ECDHE_ECDSA based session.
 * A bus calls GetAll properties on org.alljoyn.Bus.Security.Application interface.
 *
 * Verification:
 * The following properties should be fetched:
 * "Version"  Expected value=1
 * "ApplicationState"  Expected value="Claimable"
 * "ManifestTemplateDigest"  Expected value=Unknown
 * "EccPublicKey"  Expected value=Public key of DUT
 * "ManufacturerCertificate"  Expected value=empty array
 * "ManifestTemplate"  Expected value=Unknown
 * "ClaimCapabilities"  Expected value=Unknown
 */
TEST(SecurityOtherTest, call_security_application_over_ECDHE_ECDSA) {
    BusAttachment peer1Bus("SecurityOtherPeer1", true);
    BusAttachment peer2Bus("SecurityOtherPeer2", true);

    EXPECT_EQ(ER_OK, peer1Bus.Start());
    EXPECT_EQ(ER_OK, peer1Bus.Connect());
    EXPECT_EQ(ER_OK, peer2Bus.Start());
    EXPECT_EQ(ER_OK, peer2Bus.Connect());

    InMemoryKeyStoreListener peer1KeyStoreListener;
    InMemoryKeyStoreListener peer2KeyStoreListener;

    // Register in memory keystore listeners
    EXPECT_EQ(ER_OK, peer1Bus.RegisterKeyStoreListener(peer1KeyStoreListener));
    EXPECT_EQ(ER_OK, peer2Bus.RegisterKeyStoreListener(peer2KeyStoreListener));

    SecurityOtherECDHE_ECDSAAuthListener peer1AuthListener;
    SecurityOtherECDHE_ECDSAAuthListener peer2AuthListener;

    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA", &peer1AuthListener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA", &peer2AuthListener));

    SessionOpts opts;
    SessionPort sessionPort = 42;
    SecurityOtherTestSessionPortListener sessionPortListener;
    EXPECT_EQ(ER_OK, peer2Bus.BindSessionPort(sessionPort, opts, sessionPortListener));

    uint32_t sessionId;
    EXPECT_EQ(ER_OK, peer1Bus.JoinSession(peer2Bus.GetUniqueName().c_str(), sessionPort, NULL, sessionId, opts));

    SecurityApplicationProxy proxy(peer1Bus, peer2Bus.GetUniqueName().c_str(), sessionId);

    // "Version"  Expected value=1
    uint16_t secuirtyApplicaitonVersion = 0;
    EXPECT_EQ(ER_OK, proxy.GetSecurityApplicationVersion(secuirtyApplicaitonVersion));
    EXPECT_EQ(1, secuirtyApplicaitonVersion);

    // "ApplicationState"  Expected value="Not Claimable"
    PermissionConfigurator::ApplicationState applicationState;
    EXPECT_EQ(ER_OK, proxy.GetApplicationState(applicationState));
    EXPECT_EQ(PermissionConfigurator::NOT_CLAIMABLE, applicationState);

    // "ManifestTemplateDigest"  Expected value=Unknown
    uint8_t manifestTemplateDigest[qcc::Crypto_SHA256::DIGEST_SIZE];
    EXPECT_EQ(ER_BAD_ARG_2, proxy.GetManifestTemplateDigest(manifestTemplateDigest, qcc::Crypto_SHA256::DIGEST_SIZE));

    // "EccPublicKey"  Expected value=Public key of DUT
    qcc::ECCPublicKey eccPublicKey;
    EXPECT_EQ(ER_OK, proxy.GetEccPublicKey(eccPublicKey));
    PermissionConfigurator& pcPeer2 = peer2Bus.GetPermissionConfigurator();
    KeyInfoNISTP256 peer2KeyInfo;
    EXPECT_EQ(ER_OK, pcPeer2.GetSigningPublicKey(peer2KeyInfo));
    EXPECT_EQ(*peer2KeyInfo.GetPublicKey(), eccPublicKey);

    // "ManufacturerCertificate"  Expected value=empty array
    MsgArg manufacturerCertificate;
    EXPECT_EQ(ER_OK, proxy.GetManufacturerCertificate(manufacturerCertificate));
    EXPECT_EQ((size_t)0, manufacturerCertificate.v_array.GetNumElements());

    // "ManifestTemplate"  Expected value=Unknown
    MsgArg manifestTemplate;
    EXPECT_EQ(ER_OK, proxy.GetManifestTemplate(manifestTemplate));
    // manifestTemplate should be empty
    EXPECT_EQ((size_t)0, manifestTemplate.v_array.GetNumElements());

    // "ClaimCapabilities"  Expected value=Unknown
    PermissionConfigurator::ClaimCapabilities claimCapabilities;
    EXPECT_EQ(ER_OK, proxy.GetClaimCapabilities(claimCapabilities));
    EXPECT_EQ(PermissionConfigurator::CAPABLE_ECDHE_NULL, claimCapabilities);

    MsgArg props;
    EXPECT_EQ(ER_OK, proxy.GetAllProperties(org::alljoyn::Bus::Security::Application::InterfaceName, props));
    // check GetAllProperties contains the values from org.alljoyn.Bus.Security.Application interface
    // The value of each element was already checked above. Just check the GetAllProperties
    // have an entry for each property we are interested in.
    MsgArg* propArg;
    EXPECT_EQ(ER_OK, props.GetElement("{sv}", "Version", &propArg)) << props.ToString().c_str();
    EXPECT_EQ(ER_OK, props.GetElement("{sv}", "ApplicationState", &propArg)) << props.ToString().c_str();
    EXPECT_EQ(ER_OK, props.GetElement("{sv}", "ManifestTemplateDigest", &propArg)) << props.ToString().c_str();
    EXPECT_EQ(ER_OK, props.GetElement("{sv}", "EccPublicKey", &propArg)) << props.ToString().c_str();
    EXPECT_EQ(ER_OK, props.GetElement("{sv}", "ManufacturerCertificate", &propArg)) << props.ToString().c_str();
    EXPECT_EQ(ER_OK, props.GetElement("{sv}", "ManifestTemplate", &propArg)) << props.ToString().c_str();
    EXPECT_EQ(ER_OK, props.GetElement("{sv}", "ClaimCapabilities", &propArg)) << props.ToString().c_str();

    peer1Bus.Stop();
    peer1Bus.Join();
    peer2Bus.Stop();
    peer2Bus.Join();
}

class SecurityOtherAuthListener : public DefaultECDHEAuthListener {
  public:
    SecurityOtherAuthListener() {
        uint8_t psk[16] = { 0xfa, 0xaa, 0x0a, 0xf3,
                            0xdd, 0x3f, 0x1e, 0x03,
                            0x79, 0xda, 0x04, 0x6a,
                            0x3a, 0xb6, 0xca, 0x44 };
        SetPSK(psk, 16);
    }

    QStatus RequestCredentialsAsync(const char* authMechanism, const char* authPeer, uint16_t authCount, const char* userId, uint16_t credMask, void* context)
    {
        Credentials creds;
        if (strcmp(authMechanism, "ALLJOYN_SRP_KEYX") == 0) {
            if (credMask & AuthListener::CRED_PASSWORD) {
                creds.SetPassword("123456");
            }
            return RequestCredentialsResponse(context, true, creds);
        }
        return DefaultECDHEAuthListener::RequestCredentialsAsync(authMechanism, authPeer, authCount, userId, credMask, context);
    }
};

class V1ECDHEKeyXListener : public AuthListener {
  public:
    V1ECDHEKeyXListener(BusAttachment& caBus) : caBus(caBus), ecc()
    {
        QStatus status = ER_FAIL;
        status = ecc.GenerateDSAKeyPair();
        EXPECT_EQ(ER_OK, status);
        const size_t manifestSize = 1;
        PermissionPolicy::Rule manifest[manifestSize];
        manifest[0].SetObjPath("*");
        manifest[0].SetInterfaceName("*");
        {
            PermissionPolicy::Rule::Member member[1];
            member[0].Set("*",
                          PermissionPolicy::Rule::Member::NOT_SPECIFIED,
                          PermissionPolicy::Rule::Member::ACTION_PROVIDE |
                          PermissionPolicy::Rule::Member::ACTION_MODIFY |
                          PermissionPolicy::Rule::Member::ACTION_OBSERVE);
            manifest[0].SetMembers(1, member);
        }
        uint8_t digest[Crypto_SHA256::DIGEST_SIZE];
        PermissionMgmtObj::GenerateManifestDigest(caBus, manifest, manifestSize, digest, Crypto_SHA256::DIGEST_SIZE);
        if (ER_OK == status) {
            EXPECT_EQ(ER_OK, PermissionMgmtTestHelper::CreateIdentityCert(caBus, "9010101", "V1Client", ecc.GetDSAPublicKey(), "V1 Client", 3600, identityCert, digest, Crypto_SHA256::DIGEST_SIZE));
        }
    }

    bool RequestCredentials(const char* authMechanism, const char* authPeer, uint16_t authCount, const char* userId, uint16_t credMask, Credentials& creds)
    {
        QCC_UNUSED(authPeer);
        QCC_UNUSED(authCount);
        QCC_UNUSED(userId);

        if (strcmp(authMechanism, "ALLJOYN_ECDHE_ECDSA") == 0) {
            if ((credMask& AuthListener::CRED_PRIVATE_KEY) == AuthListener::CRED_PRIVATE_KEY) {
                String pk;
                EXPECT_EQ(ER_OK, CertificateX509::EncodePrivateKeyPEM(ecc.GetDSAPrivateKey(), pk));
                creds.SetPrivateKey(pk);
            }
            if ((credMask& AuthListener::CRED_CERT_CHAIN) == AuthListener::CRED_CERT_CHAIN) {
                String cert;
                creds.SetCertChain(identityCert.GetPEM());
                creds.SetExpiration(1000);
            }
            return true;
        }
        return false;
    }

    bool VerifyCredentials(const char* authMechanism, const char* authPeer, const Credentials& creds)
    {
        QCC_UNUSED(authPeer);
        QCC_UNUSED(creds);

        /* only the ECDHE_ECDSA calls for peer credential verification */
        if (strcmp(authMechanism, "ALLJOYN_ECDHE_ECDSA") == 0) {
            if (!creds.IsSet(AuthListener::CRED_CERT_CHAIN)) {
                return false; /* there is no cert chain */
            }

            size_t count = 0;
            QStatus status = CertificateHelper::GetCertCount(creds.GetCertChain(), &count);
            if (ER_OK != status) {
                return false;
            }
            std::unique_ptr<CertificateX509[]> certChain(new CertificateX509[count]);
            status = CertificateX509::DecodeCertChainPEM(creds.GetCertChain(), certChain.get(), count);
            if (ER_OK != status) {
                return false;
            }
            bool validated = false;
            qcc::KeyInfoNISTP256 caKeyInfo;
            EXPECT_EQ(ER_OK, caBus.GetPermissionConfigurator().GetSigningPublicKey(caKeyInfo));
            for (size_t i = 0; i < count; i++) {
                if (ER_OK == certChain[i].Verify(caKeyInfo.GetPublicKey())) {
                    validated = true;
                    break;
                }
            }
            return validated;
        }
        return false;
    }

    void AuthenticationComplete(const char* authMechanism, const char* authPeer, bool success)
    {
        QCC_UNUSED(authMechanism);
        QCC_UNUSED(authPeer);
        QCC_UNUSED(success);
    }

  private:
    BusAttachment& caBus;
    Crypto_ECC ecc;
    IdentityCertificate identityCert;
};

class SecurityOther2Test : public testing::Test {
  public:
    SecurityOther2Test() :
        managerBus("SecurityOtherManager", true),
        peer1Bus("SecurityOtherPeer1", true),
        peer2Bus("SecurityOtherPeer2", true),
        managerKeyStoreListener(),
        peer1KeyStoreListener(),
        peer2KeyStoreListener(),
        managerAuthListener(),
        peer1AuthListener(),
        peer2AuthListener(),
        interfaceName("org.allseen.test.security.other.secure"),
        interface(),
        managerSessionPort(42),
        peer1SessionPort(42),
        peer2SessionPort(42),
        opts1(),
        opts2(),
        opts3(),
        managerSessionPortListener(),
        peer1SessionPortListener(),
        peer2SessionPortListener(),
        managerToPeer2SessionId()
    {

    }
    virtual void SetUp() {
        EXPECT_EQ(ER_OK, managerBus.Start());
        EXPECT_EQ(ER_OK, managerBus.Connect());
        EXPECT_EQ(ER_OK, peer1Bus.Start());
        EXPECT_EQ(ER_OK, peer1Bus.Connect());
        EXPECT_EQ(ER_OK, peer2Bus.Start());
        EXPECT_EQ(ER_OK, peer2Bus.Connect());
        // Register in memory keystore listeners
        EXPECT_EQ(ER_OK, managerBus.RegisterKeyStoreListener(managerKeyStoreListener));
        EXPECT_EQ(ER_OK, peer1Bus.RegisterKeyStoreListener(peer1KeyStoreListener));
        EXPECT_EQ(ER_OK, peer2Bus.RegisterKeyStoreListener(peer2KeyStoreListener));

        EXPECT_EQ(ER_OK, managerBus.EnablePeerSecurity("ALLJOYN_ECDHE_NULL ALLJOYN_ECDHE_ECDSA", &managerAuthListener));
        EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_ECDHE_NULL ALLJOYN_ECDHE_ECDSA", &peer1AuthListener));
        EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_ECDHE_NULL ALLJOYN_ECDHE_ECDSA", &peer2AuthListener));

        interface = "<node>"
                    "<interface name='" + interfaceName + "'>"
                    "<annotation name='org.alljoyn.Bus.Secure' value='true'/>"
                    "  <method name='Echo'>"
                    "    <arg name='shout' type='s' direction='in'/>"
                    "    <arg name='reply' type='s' direction='out'/>"
                    "  </method>"
                    "  <signal name='Chirp'>"
                    "    <arg name='tweet' type='s'/>"
                    "  </signal>"
                    "  <property name='Prop1' type='i' access='readwrite'/>"
                    "  <property name='Prop2' type='i' access='readwrite'/>"
                    "</interface>"
                    "</node>";

        EXPECT_EQ(ER_OK, peer1Bus.CreateInterfacesFromXml(interface.c_str()));
        EXPECT_EQ(ER_OK, peer2Bus.CreateInterfacesFromXml(interface.c_str()));

        SessionId managerToManagerSessionId;
        EXPECT_EQ(ER_OK, managerBus.BindSessionPort(managerSessionPort, opts1, managerSessionPortListener));

        EXPECT_EQ(ER_OK, peer1Bus.BindSessionPort(peer1SessionPort, opts2, peer1SessionPortListener));
        EXPECT_EQ(ER_OK, peer2Bus.BindSessionPort(peer2SessionPort, opts3, peer2SessionPortListener));

        EXPECT_EQ(ER_OK, managerBus.JoinSession(managerBus.GetUniqueName().c_str(), managerSessionPort, NULL, managerToManagerSessionId, opts1));
        EXPECT_EQ(ER_OK, managerBus.JoinSession(peer2Bus.GetUniqueName().c_str(), peer2SessionPort, NULL, managerToPeer2SessionId, opts3));

        //-----------------------Claim manager and peer2 bus Attachments------------------
        SecurityApplicationProxy sapWithManager(managerBus, managerBus.GetUniqueName().c_str(), managerToManagerSessionId);
        SecurityApplicationProxy sapWithPeer2(managerBus, peer2Bus.GetUniqueName().c_str(), managerToPeer2SessionId);


        // All Inclusive manifest
        const size_t manifestSize = 1;
        PermissionPolicy::Rule manifest[manifestSize];
        manifest[0].SetObjPath("*");
        manifest[0].SetInterfaceName("*");
        {
            PermissionPolicy::Rule::Member member[1];
            member[0].Set("*",
                          PermissionPolicy::Rule::Member::NOT_SPECIFIED,
                          PermissionPolicy::Rule::Member::ACTION_PROVIDE |
                          PermissionPolicy::Rule::Member::ACTION_MODIFY |
                          PermissionPolicy::Rule::Member::ACTION_OBSERVE);
            manifest[0].SetMembers(1, member);
        }

        //Get manager key
        KeyInfoNISTP256 managerKey;
        PermissionConfigurator& pcManager = managerBus.GetPermissionConfigurator();
        EXPECT_EQ(ER_OK, pcManager.GetSigningPublicKey(managerKey));

        //Create peer2 key
        KeyInfoNISTP256 peer2Key;
        PermissionConfigurator& pcPeer2 = peer2Bus.GetPermissionConfigurator();
        EXPECT_EQ(ER_OK, pcPeer2.GetSigningPublicKey(peer2Key));

        //------------ Claim self(managerBus), Peer1, and Peer2 --------
        //Random GUID used for the SecurityManager
        GUID128 managerGuid;
        PermissionMgmtTestHelper::GetGUID(managerBus, managerGuid);

        GUID128 peer2Guid;
        PermissionMgmtTestHelper::GetGUID(peer2Bus, peer2Guid);

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

        /* set claimable */
        managerBus.GetPermissionConfigurator().SetApplicationState(PermissionConfigurator::CLAIMABLE);
        EXPECT_EQ(ER_OK, sapWithManager.Claim(managerKey,
                                              managerGuid,
                                              managerKey,
                                              identityCertChainMaster, certChainSize,
                                              manifest, manifestSize));


        ECCPublicKey managerPublicKey;
        GetAppPublicKey(managerBus, managerPublicKey);
        ASSERT_EQ(*managerKey.GetPublicKey(), managerPublicKey);

        //Create peer2 identityCert
        IdentityCertificate identityCertChainPeer2[certChainSize];

        EXPECT_EQ(ER_OK, PermissionMgmtTestHelper::CreateIdentityCert(managerBus,
                                                                      "0",
                                                                      peer2Guid.ToString(),
                                                                      peer2Key.GetPublicKey(),
                                                                      "Peer2Alias",
                                                                      3600,
                                                                      identityCertChainPeer2[0],
                                                                      digest, Crypto_SHA256::DIGEST_SIZE)) << "Failed to create identity certificate.";
        /* set claimable */
        EXPECT_EQ(ER_OK, peer2Bus.GetPermissionConfigurator().SetApplicationState(PermissionConfigurator::CLAIMABLE));
        EXPECT_EQ(ER_OK, sapWithPeer2.Claim(managerKey,
                                            managerGuid,
                                            managerKey,
                                            identityCertChainPeer2, certChainSize,
                                            manifest, manifestSize));

        EXPECT_EQ(ER_OK, managerBus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA", &managerAuthListener));
        //    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA", &peer1AuthListener));
        EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA", &peer2AuthListener));

        //--------- InstallMembership certificates on self, peer1, and peer2

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
        EXPECT_EQ(ER_OK, sapWithManager.InstallMembership(managerMembershipCertificate, 1));

        qcc::MembershipCertificate peer2MembershipCertificate[1];
        EXPECT_EQ(ER_OK, PermissionMgmtTestHelper::CreateMembershipCert(membershipSerial,
                                                                        managerBus,
                                                                        peer2Bus.GetUniqueName(),
                                                                        peer2Key.GetPublicKey(),
                                                                        managerGuid,
                                                                        false,
                                                                        3600,
                                                                        peer2MembershipCertificate[0]
                                                                        ));
        EXPECT_EQ(ER_OK, sapWithPeer2.InstallMembership(peer2MembershipCertificate, 1));
    }

    void InstallAnyTrustedPolicy() {
        SecurityApplicationProxy sapWithPeer2(managerBus, peer2Bus.GetUniqueName().c_str(), managerToPeer2SessionId);
        // Permission policy that will be installed on peer2
        PermissionPolicy peer2Policy;
        peer2Policy.SetVersion(1);
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
                                   PermissionPolicy::Rule::Member::ACTION_MODIFY |
                                   PermissionPolicy::Rule::Member::ACTION_OBSERVE |
                                   PermissionPolicy::Rule::Member::ACTION_PROVIDE);
                    rules[0].SetMembers(1, members);
                }
                acls[0].SetRules(1, rules);
            }
            peer2Policy.SetAcls(1, acls);
        }

        {
            PermissionPolicy peer2DefaultPolicy;
            EXPECT_EQ(ER_OK, sapWithPeer2.GetDefaultPolicy(peer2DefaultPolicy));
            UpdatePolicyWithValuesFromDefaultPolicy(peer2DefaultPolicy, peer2Policy);
            EXPECT_EQ(ER_OK, sapWithPeer2.UpdatePolicy(peer2Policy));
            EXPECT_EQ(ER_OK, sapWithPeer2.SecureConnection(true));
        }
    }

    void InstallFromCertificateAuthorityPolicy() {
        SecurityApplicationProxy sapWithPeer2(managerBus, peer2Bus.GetUniqueName().c_str(), managerToPeer2SessionId);
        // Permission policy that will be installed on peer2
        PermissionPolicy peer2Policy;
        peer2Policy.SetVersion(1);
        {
            PermissionPolicy::Acl acls[1];
            {
                PermissionPolicy::Peer peers[1];
                peers[0].SetType(PermissionPolicy::Peer::PEER_FROM_CERTIFICATE_AUTHORITY);
                KeyInfoNISTP256 managerKey;
                EXPECT_EQ(ER_OK, managerBus.GetPermissionConfigurator().GetSigningPublicKey(managerKey));
                peers[0].SetKeyInfo(&managerKey);
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
                                   PermissionPolicy::Rule::Member::ACTION_MODIFY |
                                   PermissionPolicy::Rule::Member::ACTION_OBSERVE |
                                   PermissionPolicy::Rule::Member::ACTION_PROVIDE);
                    rules[0].SetMembers(1, members);
                }
                acls[0].SetRules(1, rules);
            }
            peer2Policy.SetAcls(1, acls);
        }

        {
            PermissionPolicy peer2DefaultPolicy;
            EXPECT_EQ(ER_OK, sapWithPeer2.GetDefaultPolicy(peer2DefaultPolicy));
            UpdatePolicyWithValuesFromDefaultPolicy(peer2DefaultPolicy, peer2Policy);
            EXPECT_EQ(ER_OK, sapWithPeer2.UpdatePolicy(peer2Policy));
            EXPECT_EQ(ER_OK, sapWithPeer2.SecureConnection(true));
        }
    }

    virtual void TearDown() {
        EXPECT_EQ(ER_OK, managerBus.Stop());
        EXPECT_EQ(ER_OK, managerBus.Join());
        EXPECT_EQ(ER_OK, peer1Bus.Stop());
        EXPECT_EQ(ER_OK, peer1Bus.Join());
        EXPECT_EQ(ER_OK, peer2Bus.Stop());
        EXPECT_EQ(ER_OK, peer2Bus.Join());

    }
    BusAttachment managerBus;
    //Peer1 will be the Security 1.0 BusAttachment
    BusAttachment peer1Bus;
    //Peer2 will be the Security 2.0 BusAttachment
    BusAttachment peer2Bus;

    InMemoryKeyStoreListener managerKeyStoreListener;
    InMemoryKeyStoreListener peer1KeyStoreListener;
    InMemoryKeyStoreListener peer2KeyStoreListener;

    SecurityOtherAuthListener managerAuthListener;
    SecurityOtherAuthListener peer1AuthListener;
    SecurityOtherAuthListener peer2AuthListener;

    qcc::String interfaceName;
    qcc::String interface;

    SessionPort managerSessionPort;
    SessionPort peer1SessionPort;
    SessionPort peer2SessionPort;

    SessionOpts opts1;
    SessionOpts opts2;
    SessionOpts opts3;

    SecurityOtherTestSessionPortListener managerSessionPortListener;
    SecurityOtherTestSessionPortListener peer1SessionPortListener;
    SecurityOtherTestSessionPortListener peer2SessionPortListener;

    SessionId managerToPeer2SessionId;
};

/*
 * purpose:
 * Interaction between unclaimed app and claimed app: Security 1.0 peer must be
 * able to send/receive messages to/from Security 2.0 peer in a trusted manner,
 * Security 2.0 peer has an ACL with ANY_TRUSTED peer type.
 *
 * (Security 1.0 peer is an unclaimed application)
 * The DUT is Security 1.0 peer.
 *
 * Setup:
 * Security 2.0 peer is Claimed and has the following policy installed:
 * ACL: ANY_TRUSTED,
 * Rule:  Object path: *, Interface Name: *, Member Name: *,  Action: PROVIDE|MODIFY|OBSERVE
 *
 * Peers establish an ECDHE_NULL based session.
 * Security 1.0 peer makes a method call, get property call and set property call on Security 2.0 peer.
 * Security 1.0 peer sends a signal to Security 2.0 peer.
 * Security 2.0 peer makes a method call, get property call and set property call on Security 1.0 peer.
 * Security 2.0 peer sends a signal to Security 1.0 peer.
 * Method calls will not be received by Security 2.0.
 * Signal will not be received by Security 2.0 peer.
 * Method calls cannot be sent by Security 2.0 peer.
 * Signal will not be sent by Security 1.0 peer.
 * (This is because an ECDHE_NULL based session is not trusted.)
 *
 * Peers establish an SRP based session.
 * Security 1.0 peer makes a method call, get property call and set property call on Security 2.0 peer.
 * Security 1.0 peer sends a signal to Security 2.0 peer.
 * Security 2.0 peer makes a method call, get property call and set property call on Security 1.0 peer.
 * Security 2.0 peer sends a signal to Security 1.0 peer.
 * Method calls and signals will be successful.
 *
 * Peers establish an ECDHE_PSK based session.
 * Security 1.0 peer makes a method call, get property call and set property call on Security 2.0 peer.
 * Security 1.0 peer sends a signal to Security 2.0 peer.
 * Security 2.0 peer makes a method call, get property call and set property call on Security 1.0 peer.
 * Security 2.0 peer sends a signal to Security 1.0 peer.
 * Method calls and signals will be successful.
 *
 * Peers establish an ECDHE_ECDSA based session.
 * Security 1.0 peer makes a method call, get property call and set property call on Security 2.0 peer.
 * Security 1.0 peer sends a signal to Security 2.0 peer.
 * Security 2.0 peer makes a method call, get property call and set property call on Security 1.0 peer.
 * Security 2.0 peer sends a signal to Security 1.0 peer.
 * Authentication between peers should be successful
 * Method calls and signals will not be successful since Security 1.0 peers can not exchange manifest.
 *
 * Verification:
 * Verification as mentioned in the set-up.
 */
TEST_F(SecurityOther2Test, security1_to_security2_over_ECDHE_NULL_acl_peer_ANY_TRUSTED) {
    InstallAnyTrustedPolicy();
    SecurityOtherTestBusObject peer1BusObject(peer1Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer1Bus.RegisterBusObject(peer1BusObject, true));

    SecurityOtherTestBusObject peer2BusObject(peer2Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer2Bus.RegisterBusObject(peer2BusObject, true));

    uint32_t sessionId;
    EXPECT_EQ(ER_OK, peer1Bus.JoinSession(peer2Bus.GetUniqueName().c_str(), peer2SessionPort, NULL, sessionId, opts2));

    //Peers establish an ECDHE_NULL based session.
    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_ECDHE_NULL", &peer1AuthListener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_ECDHE_NULL", &peer2AuthListener));

    ProxyBusObject proxy(peer1Bus, peer2Bus.GetUniqueName().c_str(), TEST_OBJ_PATH, sessionId);
    EXPECT_EQ(ER_OK, proxy.ParseXml(interface.c_str()));
    EXPECT_TRUE(proxy.ImplementsInterface(interfaceName.c_str())) << interface.c_str() << "\n";
    MsgArg arg("s", ECHO_STRING);
    Message replyMsg(peer1Bus);
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.MethodCall(interfaceName.c_str(), "Echo", &arg, static_cast<size_t>(1), replyMsg));


    MsgArg prop1Arg;
    EXPECT_EQ(ER_OK, prop1Arg.Set("i", 513));
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.SetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    // Property should be unchanged.
    EXPECT_EQ(42, peer2BusObject.ReadProp1());

    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    int32_t prop1;
    prop1Arg.Get("i", &prop1);
    EXPECT_EQ(513, prop1);

    MsgArg props;
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetAllProperties(interfaceName.c_str(), props));

    ChirpSignalReceiver chirpSignalReceiver;
    EXPECT_EQ(ER_OK, peer2Bus.RegisterSignalHandler(&chirpSignalReceiver,
                                                    static_cast<MessageReceiver::SignalHandler>(&ChirpSignalReceiver::ChirpSignalHandler),
                                                    peer1Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                    NULL));

    MsgArg signalArg("s", CHIRP_STRING);
    EXPECT_EQ(ER_OK, peer1BusObject.Signal(peer2Bus.GetUniqueName().c_str(),
                                           sessionId,
                                           *peer1Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                           &signalArg, 1));

    //Wait for a maximum of 2 sec for the Chirp Signal.
    for (int msec = 0; msec < 2000; msec += WAIT_MSECS) {
        if (chirpSignalReceiver.signalReceivedFlag) {
            break;
        }
        qcc::Sleep(WAIT_MSECS);
    }

    EXPECT_FALSE(chirpSignalReceiver.signalReceivedFlag);
}

/*
 * See SecurityOther2Test.security1_to_security2_over_ECDHE_NULL_acl_peer_ANY_TRUSTED
 * for full test description.
 */
TEST_F(SecurityOther2Test, security2_to_security1_over_ECDHE_NULL_acl_peer_ANY_TRUSTED) {
    InstallAnyTrustedPolicy();
    SecurityOtherTestBusObject peer1BusObject(peer1Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer1Bus.RegisterBusObject(peer1BusObject, true));

    SecurityOtherTestBusObject peer2BusObject(peer2Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer2Bus.RegisterBusObject(peer2BusObject, true));

    uint32_t sessionId;
    EXPECT_EQ(ER_OK, peer2Bus.JoinSession(peer1Bus.GetUniqueName().c_str(), peer1SessionPort, NULL, sessionId, opts1));

    //Peers establish an ECDHE_NULL based session.
    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_ECDHE_NULL", &peer1AuthListener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_ECDHE_NULL", &peer2AuthListener));

    ProxyBusObject proxy(peer2Bus, peer1Bus.GetUniqueName().c_str(), TEST_OBJ_PATH, sessionId);
    EXPECT_EQ(ER_OK, proxy.ParseXml(interface.c_str()));
    EXPECT_TRUE(proxy.ImplementsInterface(interfaceName.c_str())) << interface.c_str() << "\n";
    MsgArg arg("s", ECHO_STRING);
    Message replyMsg(peer2Bus);
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.MethodCall(interfaceName.c_str(), "Echo", &arg, static_cast<size_t>(1), replyMsg));


    MsgArg prop1Arg;
    EXPECT_EQ(ER_OK, prop1Arg.Set("i", 513));
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.SetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    // Property should be unchanged.
    EXPECT_EQ(42, peer2BusObject.ReadProp1());

    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    int32_t prop1;
    prop1Arg.Get("i", &prop1);
    EXPECT_EQ(513, prop1);

    MsgArg props;
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetAllProperties(interfaceName.c_str(), props));

    ChirpSignalReceiver chirpSignalReceiver;
    EXPECT_EQ(ER_OK, peer1Bus.RegisterSignalHandler(&chirpSignalReceiver,
                                                    static_cast<MessageReceiver::SignalHandler>(&ChirpSignalReceiver::ChirpSignalHandler),
                                                    peer1Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                    NULL));

    MsgArg signalArg("s", CHIRP_STRING);
    EXPECT_EQ(ER_PERMISSION_DENIED, peer2BusObject.Signal(peer1Bus.GetUniqueName().c_str(),
                                                          sessionId,
                                                          *peer2Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                          &signalArg, 1));
}

/*
 * See SecurityOther2Test.security1_to_security2_over_ECDHE_NULL_acl_peer_ANY_TRUSTED
 * for full test description.
 */
TEST_F(SecurityOther2Test, security1_to_security2_over_SRP_KEYX_acl_peer_ANY_TRUSTED) {
    InstallAnyTrustedPolicy();
    SecurityOtherTestBusObject peer1BusObject(peer1Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer1Bus.RegisterBusObject(peer1BusObject, true));

    SecurityOtherTestBusObject peer2BusObject(peer2Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer2Bus.RegisterBusObject(peer2BusObject, true));

    uint32_t sessionId;
    EXPECT_EQ(ER_OK, peer1Bus.JoinSession(peer2Bus.GetUniqueName().c_str(), peer2SessionPort, NULL, sessionId, opts2));

    //Peers establish an ECDHE_NULL based session.
    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_SRP_KEYX", &peer1AuthListener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_SRP_KEYX", &peer2AuthListener));

    ProxyBusObject proxy(peer1Bus, peer2Bus.GetUniqueName().c_str(), TEST_OBJ_PATH, sessionId);
    EXPECT_EQ(ER_OK, proxy.ParseXml(interface.c_str()));
    EXPECT_TRUE(proxy.ImplementsInterface(interfaceName.c_str())) << interface.c_str() << "\n";
    MsgArg arg("s", ECHO_STRING);
    Message replyMsg(peer1Bus);
    EXPECT_EQ(ER_OK, proxy.MethodCall(interfaceName.c_str(), "Echo", &arg, static_cast<size_t>(1), replyMsg));

    char* echoReply;
    EXPECT_EQ(ER_OK, replyMsg->GetArg(0)->Get("s", &echoReply));
    EXPECT_STREQ(ECHO_STRING, echoReply);

    MsgArg prop1Arg;
    EXPECT_EQ(ER_OK, prop1Arg.Set("i", 513));
    EXPECT_EQ(ER_OK, proxy.SetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    EXPECT_EQ(513, peer2BusObject.ReadProp1());

    EXPECT_EQ(ER_OK, proxy.GetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    int32_t prop1;
    prop1Arg.Get("i", &prop1);
    EXPECT_EQ(513, prop1);

    MsgArg props;
    EXPECT_EQ(ER_OK, proxy.GetAllProperties(interfaceName.c_str(), props));
    {
        int32_t prop1;
        MsgArg* propArg;
        EXPECT_EQ(ER_OK, props.GetElement("{sv}", "Prop1", &propArg)) << props.ToString().c_str();
        EXPECT_EQ(ER_OK, propArg->Get("i", &prop1)) << propArg->ToString().c_str();
        EXPECT_EQ(513, prop1);
    }
    {
        int32_t prop2;
        MsgArg* propArg;
        EXPECT_EQ(ER_OK, props.GetElement("{sv}", "Prop2", &propArg)) << props.ToString().c_str();
        EXPECT_EQ(ER_OK, propArg->Get("i", &prop2)) << propArg->ToString().c_str();
        EXPECT_EQ(17, prop2);
    }

    ChirpSignalReceiver chirpSignalReceiver;
    EXPECT_EQ(ER_OK, peer2Bus.RegisterSignalHandler(&chirpSignalReceiver,
                                                    static_cast<MessageReceiver::SignalHandler>(&ChirpSignalReceiver::ChirpSignalHandler),
                                                    peer1Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                    NULL));

    MsgArg signalArg("s", CHIRP_STRING);
    // Signals are send and forget.  They will always return ER_OK.
    EXPECT_EQ(ER_OK, peer1BusObject.Signal(peer2Bus.GetUniqueName().c_str(),
                                           sessionId,
                                           *peer1Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                           &signalArg, 1));

    //Wait for a maximum of 2 sec for the Chirp Signal.
    for (int msec = 0; msec < 2000; msec += WAIT_MSECS) {
        if (chirpSignalReceiver.signalReceivedFlag) {
            break;
        }
        qcc::Sleep(WAIT_MSECS);
    }

    EXPECT_TRUE(chirpSignalReceiver.signalReceivedFlag);
}

/*
 * See SecurityOther2Test.security1_to_security2_over_ECDHE_NULL_acl_peer_ANY_TRUSTED
 * for full test description.
 */
TEST_F(SecurityOther2Test, security2_to_security1_over_SRP_KEYX_acl_peer_ANY_TRUSTED) {
    InstallAnyTrustedPolicy();
    SecurityOtherTestBusObject peer1BusObject(peer1Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer1Bus.RegisterBusObject(peer1BusObject, true));

    SecurityOtherTestBusObject peer2BusObject(peer2Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer2Bus.RegisterBusObject(peer2BusObject, true));

    uint32_t sessionId;
    EXPECT_EQ(ER_OK, peer2Bus.JoinSession(peer1Bus.GetUniqueName().c_str(), peer1SessionPort, NULL, sessionId, opts1));

    //Peers establish an ECDHE_NULL based session.
    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_SRP_KEYX", &peer1AuthListener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_SRP_KEYX", &peer2AuthListener));

    ProxyBusObject proxy(peer2Bus, peer1Bus.GetUniqueName().c_str(), TEST_OBJ_PATH, sessionId);
    EXPECT_EQ(ER_OK, proxy.ParseXml(interface.c_str()));
    EXPECT_TRUE(proxy.ImplementsInterface(interfaceName.c_str())) << interface.c_str() << "\n";
    MsgArg arg("s", ECHO_STRING);
    Message replyMsg(peer2Bus);
    EXPECT_EQ(ER_OK, proxy.MethodCall(interfaceName.c_str(), "Echo", &arg, static_cast<size_t>(1), replyMsg));

    char* echoReply;
    EXPECT_EQ(ER_OK, replyMsg->GetArg(0)->Get("s", &echoReply));
    EXPECT_STREQ(ECHO_STRING, echoReply);

    MsgArg prop1Arg;
    EXPECT_EQ(ER_OK, prop1Arg.Set("i", 513));
    EXPECT_EQ(ER_OK, proxy.SetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    EXPECT_EQ(513, peer1BusObject.ReadProp1());

    EXPECT_EQ(ER_OK, proxy.GetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    int32_t prop1;
    prop1Arg.Get("i", &prop1);
    EXPECT_EQ(513, prop1);

    MsgArg props;
    EXPECT_EQ(ER_OK, proxy.GetAllProperties(interfaceName.c_str(), props));
    {
        int32_t prop1;
        MsgArg* propArg;
        EXPECT_EQ(ER_OK, props.GetElement("{sv}", "Prop1", &propArg)) << props.ToString().c_str();
        EXPECT_EQ(ER_OK, propArg->Get("i", &prop1)) << propArg->ToString().c_str();
        EXPECT_EQ(513, prop1);
    }
    {
        int32_t prop2;
        MsgArg* propArg;
        EXPECT_EQ(ER_OK, props.GetElement("{sv}", "Prop2", &propArg)) << props.ToString().c_str();
        EXPECT_EQ(ER_OK, propArg->Get("i", &prop2)) << propArg->ToString().c_str();
        EXPECT_EQ(17, prop2);
    }

    ChirpSignalReceiver chirpSignalReceiver;
    EXPECT_EQ(ER_OK, peer1Bus.RegisterSignalHandler(&chirpSignalReceiver,
                                                    static_cast<MessageReceiver::SignalHandler>(&ChirpSignalReceiver::ChirpSignalHandler),
                                                    peer2Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                    NULL));

    MsgArg signalArg("s", CHIRP_STRING);
    // Signals are send and forget.  They will always return ER_OK.
    EXPECT_EQ(ER_OK, peer2BusObject.Signal(peer1Bus.GetUniqueName().c_str(),
                                           sessionId,
                                           *peer2Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                           &signalArg, 1));

    //Wait for a maximum of 2 sec for the Chirp Signal.
    for (int msec = 0; msec < 2000; msec += WAIT_MSECS) {
        if (chirpSignalReceiver.signalReceivedFlag) {
            break;
        }
        qcc::Sleep(WAIT_MSECS);
    }

    EXPECT_TRUE(chirpSignalReceiver.signalReceivedFlag);
}

/*
 * See SecurityOther2Test.security1_to_security2_over_ECDHE_NULL_acl_peer_ANY_TRUSTED
 * for full test description.
 */
TEST_F(SecurityOther2Test, security1_to_security2_over_ECDHE_PSK_acl_peer_ANY_TRUSTED) {
    InstallAnyTrustedPolicy();
    SecurityOtherTestBusObject peer1BusObject(peer1Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer1Bus.RegisterBusObject(peer1BusObject, true));

    SecurityOtherTestBusObject peer2BusObject(peer2Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer2Bus.RegisterBusObject(peer2BusObject, true));

    uint32_t sessionId;
    EXPECT_EQ(ER_OK, peer1Bus.JoinSession(peer2Bus.GetUniqueName().c_str(), peer2SessionPort, NULL, sessionId, opts2));

    //Peers establish an ECDHE_NULL based session.
    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_ECDHE_PSK", &peer1AuthListener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_ECDHE_PSK", &peer2AuthListener));

    ProxyBusObject proxy(peer1Bus, peer2Bus.GetUniqueName().c_str(), TEST_OBJ_PATH, sessionId);
    EXPECT_EQ(ER_OK, proxy.ParseXml(interface.c_str()));
    EXPECT_TRUE(proxy.ImplementsInterface(interfaceName.c_str())) << interface.c_str() << "\n";
    MsgArg arg("s", ECHO_STRING);
    Message replyMsg(peer1Bus);
    EXPECT_EQ(ER_OK, proxy.MethodCall(interfaceName.c_str(), "Echo", &arg, static_cast<size_t>(1), replyMsg));

    char* echoReply;
    EXPECT_EQ(ER_OK, replyMsg->GetArg(0)->Get("s", &echoReply));
    EXPECT_STREQ(ECHO_STRING, echoReply);

    MsgArg prop1Arg;
    EXPECT_EQ(ER_OK, prop1Arg.Set("i", 513));
    EXPECT_EQ(ER_OK, proxy.SetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    EXPECT_EQ(513, peer2BusObject.ReadProp1());

    EXPECT_EQ(ER_OK, proxy.GetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    int32_t prop1;
    prop1Arg.Get("i", &prop1);
    EXPECT_EQ(513, prop1);

    MsgArg props;
    EXPECT_EQ(ER_OK, proxy.GetAllProperties(interfaceName.c_str(), props));
    {
        int32_t prop1;
        MsgArg* propArg;
        EXPECT_EQ(ER_OK, props.GetElement("{sv}", "Prop1", &propArg)) << props.ToString().c_str();
        EXPECT_EQ(ER_OK, propArg->Get("i", &prop1)) << propArg->ToString().c_str();
        EXPECT_EQ(513, prop1);
    }
    {
        int32_t prop2;
        MsgArg* propArg;
        EXPECT_EQ(ER_OK, props.GetElement("{sv}", "Prop2", &propArg)) << props.ToString().c_str();
        EXPECT_EQ(ER_OK, propArg->Get("i", &prop2)) << propArg->ToString().c_str();
        EXPECT_EQ(17, prop2);
    }

    ChirpSignalReceiver chirpSignalReceiver;
    EXPECT_EQ(ER_OK, peer2Bus.RegisterSignalHandler(&chirpSignalReceiver,
                                                    static_cast<MessageReceiver::SignalHandler>(&ChirpSignalReceiver::ChirpSignalHandler),
                                                    peer1Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                    NULL));

    MsgArg signalArg("s", CHIRP_STRING);
    // Signals are send and forget.  They will always return ER_OK.
    EXPECT_EQ(ER_OK, peer1BusObject.Signal(peer2Bus.GetUniqueName().c_str(),
                                           sessionId,
                                           *peer1Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                           &signalArg, 1));

    //Wait for a maximum of 2 sec for the Chirp Signal.
    for (int msec = 0; msec < 2000; msec += WAIT_MSECS) {
        if (chirpSignalReceiver.signalReceivedFlag) {
            break;
        }
        qcc::Sleep(WAIT_MSECS);
    }

    EXPECT_TRUE(chirpSignalReceiver.signalReceivedFlag);
}

/*
 * See SecurityOther2Test.security1_to_security2_over_ECDHE_NULL_acl_peer_ANY_TRUSTED
 * for full test description.
 */
TEST_F(SecurityOther2Test, security2_to_security1_over_ECDHE_PSK_acl_peer_ANY_TRUSTED) {
    InstallAnyTrustedPolicy();
    SecurityOtherTestBusObject peer1BusObject(peer1Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer1Bus.RegisterBusObject(peer1BusObject, true));

    SecurityOtherTestBusObject peer2BusObject(peer2Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer2Bus.RegisterBusObject(peer2BusObject, true));

    uint32_t sessionId;
    EXPECT_EQ(ER_OK, peer2Bus.JoinSession(peer1Bus.GetUniqueName().c_str(), peer1SessionPort, NULL, sessionId, opts1));

    //Peers establish an ECDHE_NULL based session.
    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_ECDHE_PSK", &peer1AuthListener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_ECDHE_PSK", &peer2AuthListener));

    ProxyBusObject proxy(peer2Bus, peer1Bus.GetUniqueName().c_str(), TEST_OBJ_PATH, sessionId);
    EXPECT_EQ(ER_OK, proxy.ParseXml(interface.c_str()));
    EXPECT_TRUE(proxy.ImplementsInterface(interfaceName.c_str())) << interface.c_str() << "\n";
    MsgArg arg("s", ECHO_STRING);
    Message replyMsg(peer2Bus);
    EXPECT_EQ(ER_OK, proxy.MethodCall(interfaceName.c_str(), "Echo", &arg, static_cast<size_t>(1), replyMsg));

    char* echoReply;
    EXPECT_EQ(ER_OK, replyMsg->GetArg(0)->Get("s", &echoReply));
    EXPECT_STREQ(ECHO_STRING, echoReply);

    MsgArg prop1Arg;
    EXPECT_EQ(ER_OK, prop1Arg.Set("i", 513));
    EXPECT_EQ(ER_OK, proxy.SetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    EXPECT_EQ(513, peer1BusObject.ReadProp1());

    EXPECT_EQ(ER_OK, proxy.GetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    int32_t prop1;
    prop1Arg.Get("i", &prop1);
    EXPECT_EQ(513, prop1);

    MsgArg props;
    EXPECT_EQ(ER_OK, proxy.GetAllProperties(interfaceName.c_str(), props));
    {
        int32_t prop1;
        MsgArg* propArg;
        EXPECT_EQ(ER_OK, props.GetElement("{sv}", "Prop1", &propArg)) << props.ToString().c_str();
        EXPECT_EQ(ER_OK, propArg->Get("i", &prop1)) << propArg->ToString().c_str();
        EXPECT_EQ(513, prop1);
    }
    {
        int32_t prop2;
        MsgArg* propArg;
        EXPECT_EQ(ER_OK, props.GetElement("{sv}", "Prop2", &propArg)) << props.ToString().c_str();
        EXPECT_EQ(ER_OK, propArg->Get("i", &prop2)) << propArg->ToString().c_str();
        EXPECT_EQ(17, prop2);
    }

    ChirpSignalReceiver chirpSignalReceiver;
    EXPECT_EQ(ER_OK, peer1Bus.RegisterSignalHandler(&chirpSignalReceiver,
                                                    static_cast<MessageReceiver::SignalHandler>(&ChirpSignalReceiver::ChirpSignalHandler),
                                                    peer2Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                    NULL));

    MsgArg signalArg("s", CHIRP_STRING);
    // Signals are send and forget.  They will always return ER_OK.
    EXPECT_EQ(ER_OK, peer2BusObject.Signal(peer1Bus.GetUniqueName().c_str(),
                                           sessionId,
                                           *peer2Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                           &signalArg, 1));

    //Wait for a maximum of 2 sec for the Chirp Signal.
    for (int msec = 0; msec < 2000; msec += WAIT_MSECS) {
        if (chirpSignalReceiver.signalReceivedFlag) {
            break;
        }
        qcc::Sleep(WAIT_MSECS);
    }

    EXPECT_TRUE(chirpSignalReceiver.signalReceivedFlag);
}

/*
 * See SecurityOther2Test.security1_to_security2_over_ECDHE_NULL_acl_peer_ANY_TRUSTED
 * for full test description.
 */
TEST_F(SecurityOther2Test, security1_to_security2_over_ECDHE_ECDSA_acl_peer_ANY_TRUSTED) {
    InstallAnyTrustedPolicy();
    SecurityOtherTestBusObject peer1BusObject(peer1Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer1Bus.RegisterBusObject(peer1BusObject, true));

    SecurityOtherTestBusObject peer2BusObject(peer2Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer2Bus.RegisterBusObject(peer2BusObject, true));

    uint32_t sessionId;
    EXPECT_EQ(ER_OK, peer1Bus.JoinSession(peer2Bus.GetUniqueName().c_str(), peer2SessionPort, NULL, sessionId, opts2));

    V1ECDHEKeyXListener v1Listener(managerBus);
    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA", &v1Listener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA", &peer2AuthListener));

    ProxyBusObject proxy(peer1Bus, peer2Bus.GetUniqueName().c_str(), TEST_OBJ_PATH, sessionId);
    EXPECT_EQ(ER_OK, proxy.SecureConnection(true));

    EXPECT_EQ(ER_OK, proxy.ParseXml(interface.c_str()));
    EXPECT_TRUE(proxy.ImplementsInterface(interfaceName.c_str())) << interface.c_str() << "\n";
    MsgArg arg("s", ECHO_STRING);
    Message replyMsg(peer1Bus);
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.MethodCall(interfaceName.c_str(), "Echo", &arg, static_cast<size_t>(1), replyMsg));

    MsgArg prop1Arg;
    EXPECT_EQ(ER_OK, prop1Arg.Set("i", 513));
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.SetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    EXPECT_EQ(42, peer2BusObject.ReadProp1());

    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    int32_t prop1;
    prop1Arg.Get("i", &prop1);
    EXPECT_EQ(513, prop1);

    MsgArg props;
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetAllProperties(interfaceName.c_str(), props));

    ChirpSignalReceiver chirpSignalReceiver;
    EXPECT_EQ(ER_OK, peer2Bus.RegisterSignalHandler(&chirpSignalReceiver,
                                                    static_cast<MessageReceiver::SignalHandler>(&ChirpSignalReceiver::ChirpSignalHandler),
                                                    peer1Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                    NULL));

    MsgArg signalArg("s", CHIRP_STRING);
    EXPECT_EQ(ER_OK, peer1BusObject.Signal(peer2Bus.GetUniqueName().c_str(),
                                           sessionId,
                                           *peer1Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                           &signalArg, 1));

    //Wait for a maximum of 2 sec for the Chirp Signal.
    for (int msec = 0; msec < 2000; msec += WAIT_MSECS) {
        if (chirpSignalReceiver.signalReceivedFlag) {
            break;
        }
        qcc::Sleep(WAIT_MSECS);
    }

    EXPECT_FALSE(chirpSignalReceiver.signalReceivedFlag);
}

/*
 * See SecurityOther2Test.security1_to_security2_over_ECDHE_NULL_acl_peer_ANY_TRUSTED
 * for full test description.
 */
TEST_F(SecurityOther2Test, security2_to_security1_over_ECDHE_ECDSA_acl_peer_ANY_TRUSTED) {
    InstallAnyTrustedPolicy();
    SecurityOtherTestBusObject peer1BusObject(peer1Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer1Bus.RegisterBusObject(peer1BusObject, true));

    SecurityOtherTestBusObject peer2BusObject(peer2Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer2Bus.RegisterBusObject(peer2BusObject, true));

    uint32_t sessionId;
    EXPECT_EQ(ER_OK, peer2Bus.JoinSession(peer1Bus.GetUniqueName().c_str(), peer1SessionPort, NULL, sessionId, opts1));

    //Peers establish an ECDHE_NULL based session.
    V1ECDHEKeyXListener v1Listener(managerBus);
    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA", &v1Listener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA", &peer2AuthListener));

    ProxyBusObject proxy(peer2Bus, peer1Bus.GetUniqueName().c_str(), TEST_OBJ_PATH, sessionId);
    EXPECT_EQ(ER_OK, proxy.SecureConnection(true));

    EXPECT_EQ(ER_OK, proxy.ParseXml(interface.c_str()));
    EXPECT_TRUE(proxy.ImplementsInterface(interfaceName.c_str())) << interface.c_str() << "\n";
    MsgArg arg("s", ECHO_STRING);
    Message replyMsg(peer2Bus);
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.MethodCall(interfaceName.c_str(), "Echo", &arg, static_cast<size_t>(1), replyMsg));


    MsgArg prop1Arg;
    EXPECT_EQ(ER_OK, prop1Arg.Set("i", 513));
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.SetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    EXPECT_EQ(42, peer1BusObject.ReadProp1());

    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    int32_t prop1;
    prop1Arg.Get("i", &prop1);
    EXPECT_EQ(513, prop1);

    MsgArg props;
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetAllProperties(interfaceName.c_str(), props));

    ChirpSignalReceiver chirpSignalReceiver;
    EXPECT_EQ(ER_OK, peer1Bus.RegisterSignalHandler(&chirpSignalReceiver,
                                                    static_cast<MessageReceiver::SignalHandler>(&ChirpSignalReceiver::ChirpSignalHandler),
                                                    peer2Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                    NULL));

    MsgArg signalArg("s", CHIRP_STRING);
    EXPECT_EQ(ER_PERMISSION_DENIED, peer2BusObject.Signal(peer1Bus.GetUniqueName().c_str(),
                                                          sessionId,
                                                          *peer2Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                          &signalArg, 1));
}

/*
 * purpose:
 * Interaction between unclaimed app and claimed app: Security 1.0 peer must be
 * able to send/receive messages to/from Security 2.0 peer in a trusted manner,
 * Security 2.0 peer has an ACL with FROM_CERTIFICATE_AUTHORITY peer type.
 *
 * (Security 1.0 peer is an unclaimed application.)
 * The DUT is Security 1.0 peer.
 *
 * Setup:
 * Security 2.0 peer is Claimed and has the following policy installed:
 * ACL: WITH_CERTIFICATE_AUTHORITY, Public key: CA public key
 * Rule:  Object path: *, Interface Name: *, Member Name: *,  Action: PROVIDE|MODIFY|OBSERVE
 *
 * Peers establish an ECDHE_NULL based session.
 * Security 1.0 peer makes a method call, get property call and set property call on Security 2.0 peer.
 * Security 1.0 peer sends a signal to Security 2.0 peer.
 * Security 2.0 peer makes a method call, get property call and set property call on Security 1.0 peer.
 * Security 2.0 peer sends a signal to Security 1.0 peer.
 * Messages cannot be sent or received by Security 2.0 peer.
 *
 * Peers establish an SRP based session.
 * Security 1.0 peer makes a method call, get property call and set property call on Security 2.0 peer.
 * Security 1.0 peer sends a signal to Security 2.0 peer.
 * Security 2.0 peer makes a method call, get property call and set property call on Security 1.0 peer.
 * Security 2.0 peer sends a signal to Security 1.0 peer.
 * Messages cannot be sent or received by Security 2.0 peer.
 *
 * Peers establish an ECDHE_PSK based session.
 * Security 1.0 peer makes a method call, get property call and set property call on Security 2.0 peer.
 * Security 1.0 peer sends a signal to Security 2.0 peer.
 * Security 2.0 peer makes a method call, get property call and set property call on Security 1.0 peer.
 * Security 2.0 peer sends a signal to Security 1.0 peer.
 * Messages cannot be sent or received by Security 2.0 peer.
 *
 * Peers establish an ECDHE_ECDSA based session.
 * Security 1.0 peer makes a method call, get property call and set property call on Security 2.0 peer.
 * Security 1.0 peer sends a signal to Security 2.0 peer.
 * Security 2.0 peer makes a method call, get property call and set property call on Security 1.0 peer.
 * Security 2.0 peer sends a signal to Security 1.0 peer.
 * Authentication between peers should be successful
 * Method calls and signals will not be successful since Security 1.0 peers can not exchange manifest.
 *
 * Verification:
 * Verification as mentioned in the set-up.
 */
TEST_F(SecurityOther2Test, security1_to_security2_over_ECDHE_NULL_acl_peer_FROM_CERTIFICATE_AUTHORITY) {
    InstallFromCertificateAuthorityPolicy();
    SecurityOtherTestBusObject peer1BusObject(peer1Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer1Bus.RegisterBusObject(peer1BusObject, true));

    SecurityOtherTestBusObject peer2BusObject(peer2Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer2Bus.RegisterBusObject(peer2BusObject, true));

    uint32_t sessionId;
    EXPECT_EQ(ER_OK, peer1Bus.JoinSession(peer2Bus.GetUniqueName().c_str(), peer2SessionPort, NULL, sessionId, opts2));

    //Peers establish an ECDHE_NULL based session.
    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_ECDHE_NULL", &peer1AuthListener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_ECDHE_NULL", &peer2AuthListener));

    ProxyBusObject proxy(peer1Bus, peer2Bus.GetUniqueName().c_str(), TEST_OBJ_PATH, sessionId);
    EXPECT_EQ(ER_OK, proxy.ParseXml(interface.c_str()));
    EXPECT_TRUE(proxy.ImplementsInterface(interfaceName.c_str())) << interface.c_str() << "\n";
    MsgArg arg("s", ECHO_STRING);
    Message replyMsg(peer1Bus);
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.MethodCall(interfaceName.c_str(), "Echo", &arg, static_cast<size_t>(1), replyMsg));


    MsgArg prop1Arg;
    EXPECT_EQ(ER_OK, prop1Arg.Set("i", 513));
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.SetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    // Property should be unchanged.
    EXPECT_EQ(42, peer2BusObject.ReadProp1());

    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    int32_t prop1;
    prop1Arg.Get("i", &prop1);
    EXPECT_EQ(513, prop1);

    MsgArg props;
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetAllProperties(interfaceName.c_str(), props));

    ChirpSignalReceiver chirpSignalReceiver;
    EXPECT_EQ(ER_OK, peer2Bus.RegisterSignalHandler(&chirpSignalReceiver,
                                                    static_cast<MessageReceiver::SignalHandler>(&ChirpSignalReceiver::ChirpSignalHandler),
                                                    peer1Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                    NULL));

    MsgArg signalArg("s", CHIRP_STRING);
    EXPECT_EQ(ER_OK, peer1BusObject.Signal(peer2Bus.GetUniqueName().c_str(),
                                           sessionId,
                                           *peer1Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                           &signalArg, 1));

    //Wait for a maximum of 2 sec for the Chirp Signal.
    for (int msec = 0; msec < 2000; msec += WAIT_MSECS) {
        if (chirpSignalReceiver.signalReceivedFlag) {
            break;
        }
        qcc::Sleep(WAIT_MSECS);
    }

    EXPECT_FALSE(chirpSignalReceiver.signalReceivedFlag);
}

/*
 * See SecurityOther2Test.security1_to_security2_over_ECDHE_NULL_acl_peer_FROM_CERTIFICATE_AUTHORITY
 * for full test description.
 */
TEST_F(SecurityOther2Test, security2_to_security1_over_ECDHE_NULL_acl_peer_FROM_CERTIFICATE_AUTHORITY) {
    InstallFromCertificateAuthorityPolicy();
    SecurityOtherTestBusObject peer1BusObject(peer1Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer1Bus.RegisterBusObject(peer1BusObject, true));

    SecurityOtherTestBusObject peer2BusObject(peer2Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer2Bus.RegisterBusObject(peer2BusObject, true));

    uint32_t sessionId;
    EXPECT_EQ(ER_OK, peer2Bus.JoinSession(peer1Bus.GetUniqueName().c_str(), peer1SessionPort, NULL, sessionId, opts1));

    //Peers establish an ECDHE_NULL based session.
    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_ECDHE_NULL", &peer1AuthListener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_ECDHE_NULL", &peer2AuthListener));

    ProxyBusObject proxy(peer2Bus, peer1Bus.GetUniqueName().c_str(), TEST_OBJ_PATH, sessionId);
    EXPECT_EQ(ER_OK, proxy.ParseXml(interface.c_str()));
    EXPECT_TRUE(proxy.ImplementsInterface(interfaceName.c_str())) << interface.c_str() << "\n";
    MsgArg arg("s", ECHO_STRING);
    Message replyMsg(peer2Bus);
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.MethodCall(interfaceName.c_str(), "Echo", &arg, static_cast<size_t>(1), replyMsg));


    MsgArg prop1Arg;
    EXPECT_EQ(ER_OK, prop1Arg.Set("i", 513));
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.SetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    // Property should be unchanged.
    EXPECT_EQ(42, peer2BusObject.ReadProp1());

    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    int32_t prop1;
    prop1Arg.Get("i", &prop1);
    EXPECT_EQ(513, prop1);

    MsgArg props;
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetAllProperties(interfaceName.c_str(), props));

    ChirpSignalReceiver chirpSignalReceiver;
    EXPECT_EQ(ER_OK, peer1Bus.RegisterSignalHandler(&chirpSignalReceiver,
                                                    static_cast<MessageReceiver::SignalHandler>(&ChirpSignalReceiver::ChirpSignalHandler),
                                                    peer1Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                    NULL));

    MsgArg signalArg("s", CHIRP_STRING);
    EXPECT_EQ(ER_PERMISSION_DENIED, peer2BusObject.Signal(peer1Bus.GetUniqueName().c_str(),
                                                          sessionId,
                                                          *peer2Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                          &signalArg, 1));
}

/*
 * See SecurityOther2Test.security1_to_security2_over_ECDHE_NULL_acl_peer_FROM_CERTIFICATE_AUTHORITY
 * for full test description.
 */
TEST_F(SecurityOther2Test, security1_to_security2_over_SRP_KEYX_acl_peer_FROM_CERTIFICATE_AUTHORITY) {
    InstallFromCertificateAuthorityPolicy();
    SecurityOtherTestBusObject peer1BusObject(peer1Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer1Bus.RegisterBusObject(peer1BusObject, true));

    SecurityOtherTestBusObject peer2BusObject(peer2Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer2Bus.RegisterBusObject(peer2BusObject, true));

    uint32_t sessionId;
    EXPECT_EQ(ER_OK, peer1Bus.JoinSession(peer2Bus.GetUniqueName().c_str(), peer2SessionPort, NULL, sessionId, opts2));

    //Peers establish an ECDHE_NULL based session.
    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_SRP_KEYX", &peer1AuthListener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_SRP_KEYX", &peer2AuthListener));

    ProxyBusObject proxy(peer1Bus, peer2Bus.GetUniqueName().c_str(), TEST_OBJ_PATH, sessionId);
    EXPECT_EQ(ER_OK, proxy.ParseXml(interface.c_str()));
    EXPECT_TRUE(proxy.ImplementsInterface(interfaceName.c_str())) << interface.c_str() << "\n";
    MsgArg arg("s", ECHO_STRING);
    Message replyMsg(peer1Bus);
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.MethodCall(interfaceName.c_str(), "Echo", &arg, static_cast<size_t>(1), replyMsg));


    MsgArg prop1Arg;
    EXPECT_EQ(ER_OK, prop1Arg.Set("i", 513));
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.SetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    // Property should be unchanged.
    EXPECT_EQ(42, peer2BusObject.ReadProp1());

    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    int32_t prop1;
    prop1Arg.Get("i", &prop1);
    EXPECT_EQ(513, prop1);

    MsgArg props;
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetAllProperties(interfaceName.c_str(), props));

    ChirpSignalReceiver chirpSignalReceiver;
    EXPECT_EQ(ER_OK, peer2Bus.RegisterSignalHandler(&chirpSignalReceiver,
                                                    static_cast<MessageReceiver::SignalHandler>(&ChirpSignalReceiver::ChirpSignalHandler),
                                                    peer1Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                    NULL));

    MsgArg signalArg("s", CHIRP_STRING);
    EXPECT_EQ(ER_OK, peer1BusObject.Signal(peer2Bus.GetUniqueName().c_str(),
                                           sessionId,
                                           *peer1Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                           &signalArg, 1));

    //Wait for a maximum of 2 sec for the Chirp Signal.
    for (int msec = 0; msec < 2000; msec += WAIT_MSECS) {
        if (chirpSignalReceiver.signalReceivedFlag) {
            break;
        }
        qcc::Sleep(WAIT_MSECS);
    }

    EXPECT_FALSE(chirpSignalReceiver.signalReceivedFlag);
}

/*
 * See SecurityOther2Test.security1_to_security2_over_ECDHE_NULL_acl_peer_FROM_CERTIFICATE_AUTHORITY
 * for full test description.
 */
TEST_F(SecurityOther2Test, security2_to_security1_over_SRP_KEYX_acl_peer_FROM_CERTIFICATE_AUTHORITY) {
    InstallFromCertificateAuthorityPolicy();
    SecurityOtherTestBusObject peer1BusObject(peer1Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer1Bus.RegisterBusObject(peer1BusObject, true));

    SecurityOtherTestBusObject peer2BusObject(peer2Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer2Bus.RegisterBusObject(peer2BusObject, true));

    uint32_t sessionId;
    EXPECT_EQ(ER_OK, peer2Bus.JoinSession(peer1Bus.GetUniqueName().c_str(), peer1SessionPort, NULL, sessionId, opts1));

    //Peers establish an ECDHE_NULL based session.
    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_SRP_KEYX", &peer1AuthListener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_SRP_KEYX", &peer2AuthListener));

    ProxyBusObject proxy(peer2Bus, peer1Bus.GetUniqueName().c_str(), TEST_OBJ_PATH, sessionId);
    EXPECT_EQ(ER_OK, proxy.ParseXml(interface.c_str()));
    EXPECT_TRUE(proxy.ImplementsInterface(interfaceName.c_str())) << interface.c_str() << "\n";
    MsgArg arg("s", ECHO_STRING);
    Message replyMsg(peer2Bus);
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.MethodCall(interfaceName.c_str(), "Echo", &arg, static_cast<size_t>(1), replyMsg));


    MsgArg prop1Arg;
    EXPECT_EQ(ER_OK, prop1Arg.Set("i", 513));
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.SetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    // Property should be unchanged.
    EXPECT_EQ(42, peer2BusObject.ReadProp1());

    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    int32_t prop1;
    prop1Arg.Get("i", &prop1);
    EXPECT_EQ(513, prop1);

    MsgArg props;
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetAllProperties(interfaceName.c_str(), props));

    ChirpSignalReceiver chirpSignalReceiver;
    EXPECT_EQ(ER_OK, peer1Bus.RegisterSignalHandler(&chirpSignalReceiver,
                                                    static_cast<MessageReceiver::SignalHandler>(&ChirpSignalReceiver::ChirpSignalHandler),
                                                    peer1Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                    NULL));

    MsgArg signalArg("s", CHIRP_STRING);
    EXPECT_EQ(ER_PERMISSION_DENIED, peer2BusObject.Signal(peer1Bus.GetUniqueName().c_str(),
                                                          sessionId,
                                                          *peer2Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                          &signalArg, 1));
}

/*
 * See SecurityOther2Test.security1_to_security2_over_ECDHE_NULL_acl_peer_FROM_CERTIFICATE_AUTHORITY
 * for full test description.
 */
TEST_F(SecurityOther2Test, security1_to_security2_over_ECDHE_PSK_acl_peer_FROM_CERTIFICATE_AUTHORITY) {
    InstallFromCertificateAuthorityPolicy();
    SecurityOtherTestBusObject peer1BusObject(peer1Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer1Bus.RegisterBusObject(peer1BusObject, true));

    SecurityOtherTestBusObject peer2BusObject(peer2Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer2Bus.RegisterBusObject(peer2BusObject, true));

    uint32_t sessionId;
    EXPECT_EQ(ER_OK, peer1Bus.JoinSession(peer2Bus.GetUniqueName().c_str(), peer2SessionPort, NULL, sessionId, opts2));

    //Peers establish an ECDHE_NULL based session.
    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_ECDHE_PSK", &peer1AuthListener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_ECDHE_PSK", &peer2AuthListener));

    ProxyBusObject proxy(peer1Bus, peer2Bus.GetUniqueName().c_str(), TEST_OBJ_PATH, sessionId);
    EXPECT_EQ(ER_OK, proxy.ParseXml(interface.c_str()));
    EXPECT_TRUE(proxy.ImplementsInterface(interfaceName.c_str())) << interface.c_str() << "\n";
    MsgArg arg("s", ECHO_STRING);
    Message replyMsg(peer1Bus);
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.MethodCall(interfaceName.c_str(), "Echo", &arg, static_cast<size_t>(1), replyMsg));


    MsgArg prop1Arg;
    EXPECT_EQ(ER_OK, prop1Arg.Set("i", 513));
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.SetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    // Property should be unchanged.
    EXPECT_EQ(42, peer2BusObject.ReadProp1());

    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    int32_t prop1;
    prop1Arg.Get("i", &prop1);
    EXPECT_EQ(513, prop1);

    MsgArg props;
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetAllProperties(interfaceName.c_str(), props));

    ChirpSignalReceiver chirpSignalReceiver;
    EXPECT_EQ(ER_OK, peer2Bus.RegisterSignalHandler(&chirpSignalReceiver,
                                                    static_cast<MessageReceiver::SignalHandler>(&ChirpSignalReceiver::ChirpSignalHandler),
                                                    peer1Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                    NULL));

    MsgArg signalArg("s", CHIRP_STRING);
    EXPECT_EQ(ER_OK, peer1BusObject.Signal(peer2Bus.GetUniqueName().c_str(),
                                           sessionId,
                                           *peer1Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                           &signalArg, 1));

    //Wait for a maximum of 2 sec for the Chirp Signal.
    for (int msec = 0; msec < 2000; msec += WAIT_MSECS) {
        if (chirpSignalReceiver.signalReceivedFlag) {
            break;
        }
        qcc::Sleep(WAIT_MSECS);
    }

    EXPECT_FALSE(chirpSignalReceiver.signalReceivedFlag);
}

/*
 * See SecurityOther2Test.security1_to_security2_over_ECDHE_NULL_acl_peer_FROM_CERTIFICATE_AUTHORITY
 * for full test description.
 */
TEST_F(SecurityOther2Test, security2_to_security1_over_ECDHE_PSK_acl_peer_FROM_CERTIFICATE_AUTHORITY) {
    InstallFromCertificateAuthorityPolicy();
    SecurityOtherTestBusObject peer1BusObject(peer1Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer1Bus.RegisterBusObject(peer1BusObject, true));

    SecurityOtherTestBusObject peer2BusObject(peer2Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer2Bus.RegisterBusObject(peer2BusObject, true));

    uint32_t sessionId;
    EXPECT_EQ(ER_OK, peer2Bus.JoinSession(peer1Bus.GetUniqueName().c_str(), peer1SessionPort, NULL, sessionId, opts1));

    //Peers establish an ECDHE_NULL based session.
    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_ECDHE_PSK", &peer1AuthListener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_ECDHE_PSK", &peer2AuthListener));

    ProxyBusObject proxy(peer2Bus, peer1Bus.GetUniqueName().c_str(), TEST_OBJ_PATH, sessionId);
    EXPECT_EQ(ER_OK, proxy.ParseXml(interface.c_str()));
    EXPECT_TRUE(proxy.ImplementsInterface(interfaceName.c_str())) << interface.c_str() << "\n";
    MsgArg arg("s", ECHO_STRING);
    Message replyMsg(peer2Bus);
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.MethodCall(interfaceName.c_str(), "Echo", &arg, static_cast<size_t>(1), replyMsg));


    MsgArg prop1Arg;
    EXPECT_EQ(ER_OK, prop1Arg.Set("i", 513));
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.SetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    // Property should be unchanged.
    EXPECT_EQ(42, peer2BusObject.ReadProp1());

    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    int32_t prop1;
    prop1Arg.Get("i", &prop1);
    EXPECT_EQ(513, prop1);

    MsgArg props;
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetAllProperties(interfaceName.c_str(), props));

    ChirpSignalReceiver chirpSignalReceiver;
    EXPECT_EQ(ER_OK, peer1Bus.RegisterSignalHandler(&chirpSignalReceiver,
                                                    static_cast<MessageReceiver::SignalHandler>(&ChirpSignalReceiver::ChirpSignalHandler),
                                                    peer1Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                    NULL));

    MsgArg signalArg("s", CHIRP_STRING);
    EXPECT_EQ(ER_PERMISSION_DENIED, peer2BusObject.Signal(peer1Bus.GetUniqueName().c_str(),
                                                          sessionId,
                                                          *peer2Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                          &signalArg, 1));
}

/*
 * See SecurityOther2Test.security1_to_security2_over_ECDHE_NULL_acl_peer_FROM_CERTIFICATE_AUTHORITY
 * for full test description.
 */
TEST_F(SecurityOther2Test, security1_to_security2_over_ECDHE_ECDSA_acl_peer_FROM_CERTIFICATE_AUTHORITY) {
    InstallFromCertificateAuthorityPolicy();
    SecurityOtherTestBusObject peer1BusObject(peer1Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer1Bus.RegisterBusObject(peer1BusObject, true));

    SecurityOtherTestBusObject peer2BusObject(peer2Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer2Bus.RegisterBusObject(peer2BusObject, true));

    uint32_t sessionId;
    EXPECT_EQ(ER_OK, peer1Bus.JoinSession(peer2Bus.GetUniqueName().c_str(), peer2SessionPort, NULL, sessionId, opts2));

    //Peers establish an ECDHE_NULL based session.
    V1ECDHEKeyXListener v1Listener(managerBus);
    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA", &v1Listener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA", &peer2AuthListener));

    ProxyBusObject proxy(peer1Bus, peer2Bus.GetUniqueName().c_str(), TEST_OBJ_PATH, sessionId);
    EXPECT_EQ(ER_OK, proxy.SecureConnection(true));

    EXPECT_EQ(ER_OK, proxy.ParseXml(interface.c_str()));
    EXPECT_TRUE(proxy.ImplementsInterface(interfaceName.c_str())) << interface.c_str() << "\n";
    MsgArg arg("s", ECHO_STRING);
    Message replyMsg(peer1Bus);
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.MethodCall(interfaceName.c_str(), "Echo", &arg, static_cast<size_t>(1), replyMsg));


    EXPECT_STREQ("org.alljoyn.Bus.Security.Error.PermissionDenied", replyMsg->GetErrorName());


    MsgArg prop1Arg;
    EXPECT_EQ(ER_OK, prop1Arg.Set("i", 513));
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.SetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    EXPECT_EQ(42, peer2BusObject.ReadProp1());

    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    int32_t prop1;
    prop1Arg.Get("i", &prop1);
    EXPECT_EQ(513, prop1);

    MsgArg props;
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetAllProperties(interfaceName.c_str(), props));

    ChirpSignalReceiver chirpSignalReceiver;
    EXPECT_EQ(ER_OK, peer2Bus.RegisterSignalHandler(&chirpSignalReceiver,
                                                    static_cast<MessageReceiver::SignalHandler>(&ChirpSignalReceiver::ChirpSignalHandler),
                                                    peer1Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                    NULL));

    MsgArg signalArg("s", CHIRP_STRING);
    EXPECT_EQ(ER_OK, peer1BusObject.Signal(peer2Bus.GetUniqueName().c_str(),
                                           sessionId,
                                           *peer1Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                           &signalArg, 1));

    //Wait for a maximum of 2 sec for the Chirp Signal.
    for (int msec = 0; msec < 2000; msec += WAIT_MSECS) {
        if (chirpSignalReceiver.signalReceivedFlag) {
            break;
        }
        qcc::Sleep(WAIT_MSECS);
    }

    EXPECT_FALSE(chirpSignalReceiver.signalReceivedFlag);
}

/*
 * See SecurityOther2Test.security1_to_security2_over_ECDHE_NULL_acl_peer_FROM_CERTIFICATE_AUTHORITY
 * for full test description.
 */
TEST_F(SecurityOther2Test, security2_to_security1_over_ECDHE_ECDSA_acl_peer_FROM_CERTIFICATE_AUTHORITY) {
    InstallFromCertificateAuthorityPolicy();
    SecurityOtherTestBusObject peer1BusObject(peer1Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer1Bus.RegisterBusObject(peer1BusObject, true));

    SecurityOtherTestBusObject peer2BusObject(peer2Bus, TEST_OBJ_PATH, interfaceName.c_str());
    EXPECT_EQ(ER_OK, peer2Bus.RegisterBusObject(peer2BusObject, true));

    uint32_t sessionId;
    EXPECT_EQ(ER_OK, peer2Bus.JoinSession(peer1Bus.GetUniqueName().c_str(), peer1SessionPort, NULL, sessionId, opts1));

    //Peers establish an ECDHE_NULL based session.
    V1ECDHEKeyXListener v1Listener(managerBus);
    EXPECT_EQ(ER_OK, peer1Bus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA", &v1Listener));
    EXPECT_EQ(ER_OK, peer2Bus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA", &peer2AuthListener));

    ProxyBusObject proxy(peer2Bus, peer1Bus.GetUniqueName().c_str(), TEST_OBJ_PATH, sessionId);
    EXPECT_EQ(ER_OK, proxy.SecureConnection(true));
    EXPECT_EQ(ER_OK, proxy.ParseXml(interface.c_str()));
    EXPECT_TRUE(proxy.ImplementsInterface(interfaceName.c_str())) << interface.c_str() << "\n";
    MsgArg arg("s", ECHO_STRING);
    Message replyMsg(peer2Bus);
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.MethodCall(interfaceName.c_str(), "Echo", &arg, static_cast<size_t>(1), replyMsg));


    EXPECT_STREQ("org.alljoyn.Bus.ErStatus", replyMsg->GetErrorName());


    MsgArg prop1Arg;
    EXPECT_EQ(ER_OK, prop1Arg.Set("i", 513));
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.SetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    EXPECT_EQ(42, peer1BusObject.ReadProp1());

    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetProperty(interfaceName.c_str(), "Prop1", prop1Arg));

    int32_t prop1;
    prop1Arg.Get("i", &prop1);
    EXPECT_EQ(513, prop1);

    MsgArg props;
    EXPECT_EQ(ER_PERMISSION_DENIED, proxy.GetAllProperties(interfaceName.c_str(), props));

    ChirpSignalReceiver chirpSignalReceiver;
    EXPECT_EQ(ER_OK, peer1Bus.RegisterSignalHandler(&chirpSignalReceiver,
                                                    static_cast<MessageReceiver::SignalHandler>(&ChirpSignalReceiver::ChirpSignalHandler),
                                                    peer2Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                    NULL));

    MsgArg signalArg("s", CHIRP_STRING);
    EXPECT_EQ(ER_PERMISSION_DENIED, peer2BusObject.Signal(peer1Bus.GetUniqueName().c_str(),
                                                          sessionId,
                                                          *peer2Bus.GetInterface(interfaceName.c_str())->GetMember("Chirp"),
                                                          &signalArg, 1));
}
