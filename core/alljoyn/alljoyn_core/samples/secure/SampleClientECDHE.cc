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
 * @brief  Sample implementation of an AllJoyn client. That has an implmentation
 * of a secure client that uses the ECDHE key exchange.
 */

/******************************************************************************
 *
 *
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

#include <qcc/Log.h>
#include <qcc/String.h>

#include <alljoyn/AllJoynStd.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/Init.h>
#include <alljoyn/Status.h>
#include <alljoyn/version.h>
#include <qcc/time.h>
#include <qcc/CryptoECC.h>
#include <qcc/CertificateECC.h>
#include <qcc/Log.h>
#include <qcc/Crypto.h>
#include <qcc/CertificateECC.h>

using namespace std;
using namespace qcc;
using namespace ajn;

/** Static top level message bus object */
static BusAttachment* g_msgBus = NULL;

/*constants*/
static const char* INTERFACE_NAME = "org.alljoyn.bus.samples.secure.SecureInterface";
static const char* SERVICE_NAME = "org.alljoyn.bus.samples.secure";
static const char* SERVICE_PATH = "/SecureService";
static const char* KEYX_ECDHE_NULL = "ALLJOYN_ECDHE_NULL";
static const char* KEYX_ECDHE_PSK = "ALLJOYN_ECDHE_PSK";
static const char* KEYX_ECDHE_ECDSA = "ALLJOYN_ECDHE_ECDSA";
static const char* ECDHE_KEYX = "ALLJOYN_ECDHE_ECDSA ALLJOYN_ECDHE_PSK ALLJOYN_ECDHE_NULL";
static const SessionPort SERVICE_PORT = 42;

static bool s_joinComplete = false;
static String s_sessionHost;
static SessionId s_sessionId = 0;

static volatile sig_atomic_t s_interrupt = false;

static void SigIntHandler(int sig)
{
    s_interrupt = true;
}


/** AllJoynListener receives discovery events from AllJoyn */
class MyBusListener : public BusListener, public SessionListener {
  public:
    void FoundAdvertisedName(const char* name, TransportMask transport, const char* namePrefix)
    {
        printf("FoundAdvertisedName(name='%s', transport = 0x%x, prefix='%s')\n", name, transport, namePrefix);
        if (0 == strcmp(name, SERVICE_NAME) && s_sessionHost.empty()) {
            /* We found a remote bus that is advertising basic service's  well-known name so connect to it */
            /* Since we are in a callback we must enable concurrent callbacks before calling a synchronous method. */
            s_sessionHost = name;
            g_msgBus->EnableConcurrentCallbacks();
            SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);
            QStatus status = g_msgBus->JoinSession(name, SERVICE_PORT, this, s_sessionId, opts);
            if (ER_OK != status) {
                printf("JoinSession failed (status=%s)\n", QCC_StatusText(status));
            } else {
                printf("JoinSession SUCCESS (Session id=%d)\n", s_sessionId);
            }
            s_joinComplete = true;
        }
    }

};

static const char privateKeyPEM[] = {
    "-----BEGIN PRIVATE KEY-----\n"
    "WvfKW/zzFtv9E+8S752Y9JBbvMjVE3+bd7VQxy/r6kU="
    "-----END PRIVATE KEY-----"
};

static const char publicKeyPEM[] = {
    "-----BEGIN PUBLIC KEY-----\n"
    "k/5HsY/cJYTrDutk/06LlyuEldPyqx53B84QlP8thIzl5Fut/+CwW2DDUWD/infS\n"
    "SCVStzLPL8IJDCJIy9u7Lw==\n"
    "-----END PUBLIC KEY-----"
};

/*
 * This is the local implementation of the an AuthListener.  ECDHEKeyXListener is
 * designed to only handle ECDHE Key Exchange Authentication requests.
 *
 * If any other authMechanism is used other than ECDHE Key Exchange authentication
 * will fail.
 */

class ECDHEKeyXListener : public AuthListener {
  public:

    ECDHEKeyXListener()
    {
    }

    bool RequestCredentials(const char* authMechanism, const char* authPeer, uint16_t authCount, const char* userId, uint16_t credMask, Credentials& creds)
    {
        if (strcmp(authMechanism, KEYX_ECDHE_NULL) == 0) {
            creds.SetExpiration(100);  /* set the master secret expiry time to 100 seconds */
            return true;
        } else if (strcmp(authMechanism, KEYX_ECDHE_PSK) == 0) {
            /*
             * Solicit the Pre shared secret
             */
            if ((credMask& AuthListener::CRED_USER_NAME) == AuthListener::CRED_USER_NAME) {
                printf("RequestCredentials received psk ID %s\n", creds.GetUserName().c_str());
            }
            /*
             * Based on the pre shared secret id, the application can retrieve
             * the pre shared secret from storage or from the end user.
             * In this example, the pre shared secret is a hard coded string
             */
            String psk("123456");
            creds.SetPassword(psk);
            creds.SetExpiration(100);  /* set the master secret expiry time to 100 seconds */
            return true;
        } else if (strcmp(authMechanism, KEYX_ECDHE_ECDSA) == 0) {
            /* generate the private key and certificate */
            String privateKeyPEM;
            String certChainPEM;
            GenKeyAndSelfSignCert(privateKeyPEM, certChainPEM);
            if ((credMask& AuthListener::CRED_PRIVATE_KEY) == AuthListener::CRED_PRIVATE_KEY) {
                creds.SetPrivateKey(privateKeyPEM);
            }
            if ((credMask& AuthListener::CRED_CERT_CHAIN) == AuthListener::CRED_CERT_CHAIN) {
                creds.SetCertChain(certChainPEM);
            }
            creds.SetExpiration(100);  /* set the master secret expiry time to 100 seconds */
            return true;
        }
        return false;
    }

    bool VerifyCredentials(const char* authMechanism, const char* authPeer, const Credentials& creds)
    {
        /* only the ECDHE_ECDSA calls for peer credential verification */
        if (strcmp(authMechanism, KEYX_ECDHE_ECDSA) == 0) {
            if (creds.IsSet(AuthListener::CRED_CERT_CHAIN)) {
                /*
                 * AllJoyn sends back the certificate chain for the application to verify.
                 * The application has to option to verify the certificate
                 * chain.  If the cert chain is validated and trusted then return true; otherwise, return false.
                 */
                return true;
            }
            return true;
        }
        return false;
    }

    void AuthenticationComplete(const char* authMechanism, const char* authPeer, bool success) {
        printf("AuthenticationComplete auth mechanism %s success %d\n", authMechanism, success);
    }

  private:
    void MakePEM(qcc::String& der, qcc::String& pem)
    {
        qcc::String tag1 = "-----BEGIN CERTIFICATE-----\n";
        qcc::String tag2 = "-----END CERTIFICATE-----";
        Crypto_ASN1::EncodeBase64(der, pem);
        pem = tag1 + pem + tag2;
    }

    QStatus CreateCert(const qcc::String& serial, const qcc::GUID128& issuer, const ECCPrivateKey* issuerPrivateKey, const ECCPublicKey* issuerPubKey, const qcc::GUID128& subject, const ECCPublicKey* subjectPubKey, qcc::String& der)
    {
        QStatus status = ER_CRYPTO_ERROR;
        CertificateX509 x509(CertificateX509::IDENTITY_CERTIFICATE);

        x509.SetSerial(serial);
        x509.SetIssuer(issuer);
        x509.SetSubject(subject);
        x509.SetSubjectPublicKey(subjectPubKey);
        status = x509.Sign(issuerPrivateKey);
        if (ER_OK != status) {
            return status;
        }
        printf("Certificate: %s\n", x509.ToString().c_str());
        return x509.EncodeCertificateDER(der);
    }

    QStatus CreateIdentityCert(qcc::GUID128& issuer, const qcc::String& serial, const char* issuerPrivateKeyPEM, const char* issuerPublicKeyPEM, bool selfSign, qcc::String& der)
    {
        qcc::GUID128 userGuid;
        Crypto_ECC userECC;

        ECCPrivateKey issuerPrivateKey;
        CertECCUtil_DecodePrivateKey(issuerPrivateKeyPEM, (uint32_t*) &issuerPrivateKey, sizeof(ECCPrivateKey));
        ECCPublicKey issuerPublicKey;
        CertECCUtil_DecodePublicKey(issuerPublicKeyPEM, (uint32_t*) &issuerPublicKey, sizeof(ECCPublicKey));

        const ECCPublicKey* subjectPublicKey;
        if (selfSign) {
            subjectPublicKey = &issuerPublicKey;
        } else {
            userECC.GenerateDSAKeyPair();
            subjectPublicKey = userECC.GetDSAPublicKey();
        }
        return CreateCert(serial, issuer, &issuerPrivateKey, &issuerPublicKey, userGuid, subjectPublicKey, der);
    }

  private:

    QStatus GenKeyAndSelfSignCert(String& privateKeyPEM, String& certPEM)
    {
        //Create a dsa key pair.
        Crypto_ECC ecc;
        ecc.GenerateDSAKeyPair();
        //Encode the private key to PEM
        QStatus status = CertificateX509::EncodePrivateKeyPEM((uint8_t*) ecc.GetDSAPrivateKey(), sizeof(ECCPrivateKey), privateKeyPEM);
        if (ER_OK != status) {
            return status;
        }
        //Generate a self-signed cert
        CertificateX509 cert;
        String issuerCN("Sample Code");

        cert.SetSerial("10001000");
        cert.SetIssuerCN((const uint8_t*) issuerCN.c_str(), issuerCN.size());
        cert.SetSubjectCN((const uint8_t*) issuerCN.c_str(), issuerCN.size());
        cert.SetSubjectPublicKey(ecc.GetDSAPublicKey());
        cert.SetCA(false);
        CertificateX509::ValidPeriod validity;
        validity.validFrom = qcc::GetEpochTimestamp() / 1000;
        validity.validTo = validity.validFrom + 7200;
        cert.SetValidity(&validity);
        status = cert.Sign(ecc.GetDSAPrivateKey());
        if (ER_OK != status) {
            return status;
        }
        certPEM = cert.GetPEM();
        return ER_OK;
    }
};

/** Static bus listener */
static MyBusListener g_busListener;
static char clientName[] = "Client%u";

void MakeClientName(void)
{
#ifndef CLIENT
#define CLIENT 0
#endif

    int client = CLIENT;

    // Prevent overwriting the client name buffer.
    if (client < 0 || client > 99) {
        client = 0;
    }

    sprintf(clientName, clientName, client);
}

/** Create the interface, report the result to stdout, and return the result status. */
QStatus CreateInterface(void)
{
    /* Add org.alljoyn.Bus.method_sample interface */
    InterfaceDescription* testIntf = NULL;
    QStatus status = g_msgBus->CreateInterface(INTERFACE_NAME, testIntf, AJ_IFC_SECURITY_REQUIRED);

    if (status == ER_OK) {
        printf("Interface '%s' created.\n", INTERFACE_NAME);
        testIntf->AddMethod("Ping", "s",  "s", "inStr,outStr", 0);
        testIntf->Activate();
    } else {
        printf("Failed to create interface '%s'.\n", INTERFACE_NAME);
    }

    return status;
}

/** Start the message bus, report the result to stdout, and return the result status. */
QStatus StartMessageBus(void)
{
    QStatus status = g_msgBus->Start();

    if (ER_OK == status) {
        printf("BusAttachment started.\n");
    } else {
        printf("BusAttachment::Start failed.\n");
    }

    return status;
}

/** Enable security, report the result to stdout, and return the result status. */
QStatus EnableSecurity()
{
    QCC_SetDebugLevel("ALLJOYN", 3);
    QCC_SetDebugLevel("ALLJOYN_AUTH", 3);
    QCC_SetDebugLevel("CRYPTO", 3);
    QCC_SetDebugLevel("AUTH_KEY_EXCHANGER", 3);

    /*
     * note the location of the keystore file has been specified and the
     * isShared parameter is being set to true. So this keystore file can
     * be used by multiple applications.
     */
    QStatus status = g_msgBus->EnablePeerSecurity(ECDHE_KEYX, new ECDHEKeyXListener(), "/.alljoyn_keystore/c_ecdhe.ks", true);

    if (ER_OK == status) {
        printf("BusAttachment::EnablePeerSecurity successful.\n");
    } else {
        printf("BusAttachment::EnablePeerSecurity failed (%s).\n", QCC_StatusText(status));
    }

    return status;
}

/** Handle the connection to the bus, report the result to stdout, and return the result status. */
QStatus ConnectToBus(void)
{
    QStatus status = g_msgBus->Connect();

    if (ER_OK == status) {
        printf("BusAttachment connected to '%s'.\n", g_msgBus->GetConnectSpec().c_str());
    } else {
        printf("BusAttachment::Connect('%s') failed.\n", g_msgBus->GetConnectSpec().c_str());
    }

    return status;
}

/** Register a bus listener in order to get discovery indications and report the event to stdout. */
void RegisterBusListener(void)
{
    /* Static bus listener */
    static MyBusListener s_busListener;

    g_msgBus->RegisterBusListener(s_busListener);
    printf("BusListener Registered.\n");
}

/** Begin discovery on the well-known name of the service to be called, report the result to
   stdout, and return the result status. */
QStatus FindAdvertisedName(void)
{
    /* Begin discovery on the well-known name of the service to be called */
    QStatus status = g_msgBus->FindAdvertisedName(SERVICE_NAME);

    if (status == ER_OK) {
        printf("org.alljoyn.Bus.FindAdvertisedName ('%s') succeeded.\n", SERVICE_NAME);
    } else {
        printf("org.alljoyn.Bus.FindAdvertisedName ('%s') failed (%s).\n", SERVICE_NAME, QCC_StatusText(status));
    }

    return status;
}

/** Wait for join session to complete, report the event to stdout, and return the result status. */
QStatus WaitForJoinSessionCompletion(void)
{
    unsigned int count = 0;

    while (!s_joinComplete && !s_interrupt) {
        if (0 == (count++ % 10)) {
            printf("Waited %u seconds for JoinSession completion.\n", count / 10);
        }

#ifdef _WIN32
        Sleep(100);
#else
        usleep(100 * 1000);
#endif
    }

    return s_joinComplete && !s_interrupt ? ER_OK : ER_ALLJOYN_JOINSESSION_REPLY_CONNECT_FAILED;
}

/** Do a method call, report the result to stdout, and return the result status. */
QStatus MakeMethodCall(void)
{
    ProxyBusObject remoteObj(*g_msgBus, SERVICE_NAME, SERVICE_PATH, s_sessionId);
    const InterfaceDescription* alljoynTestIntf = g_msgBus->GetInterface(INTERFACE_NAME);

    assert(alljoynTestIntf);
    remoteObj.AddInterface(*alljoynTestIntf);

    Message reply(*g_msgBus);
    MsgArg inputs[1];
    char buffer[80];

    sprintf(buffer, "%s says Hello AllJoyn!", clientName);

    inputs[0].Set("s", buffer);

    QStatus status = remoteObj.MethodCall(INTERFACE_NAME, "Ping", inputs, 1, reply, 5000);

    if (ER_OK == status) {
        printf("%s.Ping (path=%s) returned \"%s\".\n", INTERFACE_NAME,
               SERVICE_PATH, reply->GetArg(0)->v_string.str);
    } else {
        printf("MethodCall on %s.Ping failed.\n", INTERFACE_NAME);
    }

    return status;
}

/** Main entry point */
int main(int argc, char** argv, char** envArg)
{
    if (AllJoynInit() != ER_OK) {
        return 1;
    }
#ifdef ROUTER
    if (AllJoynRouterInit() != ER_OK) {
        AllJoynShutdown();
        return 1;
    }
#endif

    printf("AllJoyn Library version: %s.\n", ajn::GetVersion());
    printf("AllJoyn Library build info: %s.\n", ajn::GetBuildInfo());


    /* Install SIGINT handler */
    signal(SIGINT, SigIntHandler);

    MakeClientName();

    QStatus status = ER_OK;

    /* Create the application name. */
    char buffer[40];

    sprintf(buffer, "ECDHESecurity%s", clientName);

    /* Create message bus */
    g_msgBus = new BusAttachment(buffer, true);

    /* This test for NULL is only required if new() behavior is to return NULL
     * instead of throwing an exception upon an out of memory failure.
     */
    if (!g_msgBus) {
        status = ER_OUT_OF_MEMORY;
    }

    if (ER_OK == status) {
        status = CreateInterface();
    }

    if (ER_OK == status) {
        status = StartMessageBus();
    }

    if (ER_OK == status) {
        status = EnableSecurity();
    }

    if (ER_OK == status) {
        status = ConnectToBus();
    }

    if (ER_OK == status) {
        RegisterBusListener();
        status = FindAdvertisedName();
    }

    if (ER_OK == status) {
        status = WaitForJoinSessionCompletion();
    }

    if (ER_OK == status) {
        status = MakeMethodCall();
    }

    /* Deallocate bus */
    delete g_msgBus;
    g_msgBus = NULL;

    printf("Basic client exiting with status 0x%04x (%s).\n", status, QCC_StatusText(status));

#ifdef ROUTER
    AllJoynRouterShutdown();
#endif
    AllJoynShutdown();
    return (int) status;
}
