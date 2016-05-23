/*
 * @file
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
#define AJ_MODULE SECURE_CLIENT

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <ajtcl/alljoyn.h>
#include <ajtcl/aj_debug.h>
#include <ajtcl/aj_crypto.h>
#include <ajtcl/aj_crypto_ecc.h>
#include <ajtcl/aj_creds.h>
#include <ajtcl/aj_cert.h>
#include <ajtcl/aj_peer.h>
#include <ajtcl/aj_auth_listener.h>
#include <ajtcl/aj_util.h>
#include <ajtcl/aj_security.h>
#include <ajtcl/aj_authorisation.h>

uint8_t dbgSECURE_CLIENT = 0;

/*
 * Default key expiration
 */
static const uint32_t keyexpiration = 0xFFFFFFFF;

static const char ServiceName[] = "org.alljoyn.bus.samples.secure";
static const char InterfaceName[] = "org.alljoyn.bus.samples.secure.SecureInterface";
static const char ServicePath[] = "/SecureService";
static const uint16_t ServicePort = 42;

/*
 * Buffer to hold the full service name. This buffer must be big enough to hold
 * a possible 255 characters plus a null terminator (256 bytes)
 */
static char fullServiceName[AJ_MAX_SERVICE_NAME_SIZE];

static const char* const secureInterface[] = {
    "$org.alljoyn.bus.samples.secure.SecureInterface",
    "?Ping inStr<s outStr>s",
    NULL
};

static const AJ_InterfaceDescription secureInterfaces[] = {
    secureInterface,
    NULL
};

/**
 * Objects implemented by the application
 */
static const AJ_Object ProxyObjects[] = {
    { ServicePath, secureInterfaces },
    { NULL }
};

static AJ_PermissionMember members[] = { { "*", AJ_MEMBER_TYPE_ANY, AJ_ACTION_MODIFY | AJ_ACTION_OBSERVE, NULL } };
static AJ_PermissionRule rules[] = { { ServicePath, InterfaceName, members, NULL } };
static AJ_Manifest manifest = { rules };

#define PRX_PING   AJ_PRX_MESSAGE_ID(0, 0, 0)

/*
 * Let the application do some work
 */
static void AppDoWork()
{
}

/*
 * get a line of input from the file pointer (most likely stdin).
 * This will capture the the num-1 characters or till a newline character is
 * entered.
 *
 * @param[out] str a pointer to a character array that will hold the user input
 * @param[in]  num the size of the character array 'str'
 * @param[in]  fp the file pointer the sting will be read from. (most likely stdin)
 *
 * @return returns the length of the string received from the file.
 */
uint32_t get_line(char* str, int num, FILE* fp)
{
    uint32_t stringLength = 0;
    char* p = fgets(str, num, fp);

    // fgets will capture the '\n' character if the string entered is shorter than
    // num. Remove the '\n' from the end of the line and replace it with nul '\0'.
    if (p != NULL) {
        stringLength = (uint32_t)strlen(str) - 1;
        if (str[stringLength] == '\n') {
            str[stringLength] = '\0';
        }
    }

    return stringLength;
}

static uint32_t PasswordCallback(uint8_t* buffer, uint32_t bufLen)
{
    return 0;
}

#define CONNECT_TIMEOUT    (1000 * 200)
#define UNMARSHAL_TIMEOUT  (1000 * 5)
#define METHOD_TIMEOUT     (100 * 10)

static char pingString[] = "Client AllJoyn Lite says Hello AllJoyn!";

AJ_Status SendPing(AJ_BusAttachment* bus, uint32_t sessionId)
{
    AJ_Status status;
    AJ_Message msg;

    AJ_Printf("Sending ping request '%s'.\n", pingString);

    status = AJ_MarshalMethodCall(bus,
                                  &msg,
                                  PRX_PING,
                                  fullServiceName,
                                  sessionId,
                                  AJ_FLAG_ENCRYPTED,
                                  METHOD_TIMEOUT);
    if (AJ_OK == status) {
        status = AJ_MarshalArgs(&msg, "s", pingString);
    } else {
        AJ_InfoPrintf(("In SendPing() AJ_MarshalMethodCall() status = %d.\n", status));
    }

    if (AJ_OK == status) {
        status = AJ_DeliverMsg(&msg);
    } else {
        AJ_InfoPrintf(("In SendPing() AJ_MarshalArgs() status = %d.\n", status));
    }

    if (AJ_OK != status) {
        AJ_InfoPrintf(("In SendPing() AJ_DeliverMsg() status = %d.\n", status));
    }

    return status;
}

// Copied from alljoyn/alljoyn_core/unit_test/AuthListenerECDHETest.cc with
// newlines removed
static const char pem_prv[] = {
    "-----BEGIN EC PRIVATE KEY-----"
    "MHcCAQEEIBiLw29bf669g7MxMbXK2u8Lp5//w7o4OiVGidJdKAezoAoGCCqGSM49"
    "AwEHoUQDQgAE+A0C9YTghZ1vG7198SrUHxFlhtbSsmhbwZ3N5aQRwzFXWcCCm38k"
    "OzJEmS+venmF1o/FV0W80Mcok9CWlV2T6A=="
    "-----END EC PRIVATE KEY-----"
};

static const char pem_x509[] = {
    "-----BEGIN CERTIFICATE-----"
    "MIIBYTCCAQigAwIBAgIJAOVrhhJOre/7MAoGCCqGSM49BAMCMCQxIjAgBgNVBAoM"
    "GUFsbEpveW5UZXN0U2VsZlNpZ25lZE5hbWUwHhcNMTUwODI0MjAxODQ1WhcNMjkw"
    "NTAyMjAxODQ1WjAgMR4wHAYDVQQKDBVBbGxKb3luVGVzdENsaWVudE5hbWUwWTAT"
    "BgcqhkjOPQIBBggqhkjOPQMBBwNCAAT4DQL1hOCFnW8bvX3xKtQfEWWG1tKyaFvB"
    "nc3lpBHDMVdZwIKbfyQ7MkSZL696eYXWj8VXRbzQxyiT0JaVXZPooycwJTAVBgNV"
    "HSUEDjAMBgorBgEEAYLefAEBMAwGA1UdEwEB/wQCMAAwCgYIKoZIzj0EAwIDRwAw"
    "RAIgevLUXoJBgUr6nVepBHQiv85CGuxu00V4uoARbH6qu1wCIA54iDRh6wit1zbP"
    "kqkBC015LjxucTf3Y7lNGhXuZRsL"
    "-----END CERTIFICATE-----"
    "-----BEGIN CERTIFICATE-----"
    "MIIBdTCCARugAwIBAgIJAJTFhmdwDWsvMAoGCCqGSM49BAMCMCQxIjAgBgNVBAoM"
    "GUFsbEpveW5UZXN0U2VsZlNpZ25lZE5hbWUwHhcNMTUwODI0MjAxODQ1WhcNMjkw"
    "NTAyMjAxODQ1WjAkMSIwIAYDVQQKDBlBbGxKb3luVGVzdFNlbGZTaWduZWROYW1l"
    "MFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEF0nZmkzuK/2CVf7udexLZnlEB5D+"
    "DBsx3POtsRyZWm2QiI1untDTp0uYp51tkP6wI6Gi5gWxB+86lEIPg4ZpTaM2MDQw"
    "IQYDVR0lBBowGAYKKwYBBAGC3nwBAQYKKwYBBAGC3nwBBTAPBgNVHRMBAf8EBTAD"
    "AQH/MAoGCCqGSM49BAMCA0gAMEUCIQDPQ1VRvdBhhneU5e7OvIFHK3d9XPZA7Fw6"
    "VyeW/P5wIAIgD969ks/z9vQ1yCaVaxmVz63toC1ggp4AnBXqbDy8O+4="
    "-----END CERTIFICATE-----"
};

static const char psk_hint[] = "<anonymous>";
static const char psk_char[] = "123456";
static X509CertificateChain* chain = NULL;
static AJ_Status AuthListenerCallback(uint32_t authmechanism, uint32_t command, AJ_Credential*cred)
{
    AJ_Status status = AJ_ERR_INVALID;
    X509CertificateChain* node;

    AJ_AlwaysPrintf(("AuthListenerCallback authmechanism %08X command %d\n", authmechanism, command));

    switch (authmechanism) {
    case AUTH_SUITE_ECDHE_NULL:
        cred->expiration = keyexpiration;
        status = AJ_OK;
        break;

    case AUTH_SUITE_ECDHE_PSK:
        switch (command) {
        case AJ_CRED_PUB_KEY:
            cred->data = (uint8_t*) psk_hint;
            cred->len = strlen(psk_hint);
            cred->expiration = keyexpiration;
            status = AJ_OK;
            break;

        case AJ_CRED_PRV_KEY:
            cred->data = (uint8_t*) psk_char;
            cred->len = strlen(psk_char);
            cred->expiration = keyexpiration;
            status = AJ_OK;
            break;
        }
        break;

    case AUTH_SUITE_ECDHE_ECDSA:
        switch (command) {
        case AJ_CRED_PRV_KEY:
            AJ_ASSERT(sizeof (AJ_ECCPrivateKey) == cred->len);
            status = AJ_DecodePrivateKeyPEM((AJ_ECCPrivateKey*) cred->data, pem_prv);
            cred->expiration = keyexpiration;
            break;

        case AJ_CRED_CERT_CHAIN:
            switch (cred->direction) {
            case AJ_CRED_REQUEST:
                // Free previous certificate chain
                while (chain) {
                    node = chain;
                    chain = chain->next;
                    AJ_Free(node->certificate.der.data);
                    AJ_Free(node);
                }
                chain = AJ_X509DecodeCertificateChainPEM(pem_x509);
                if (NULL == chain) {
                    return AJ_ERR_INVALID;
                }
                cred->data = (uint8_t*) chain;
                cred->expiration = keyexpiration;
                status = AJ_OK;
                break;

            case AJ_CRED_RESPONSE:
                node = (X509CertificateChain*) cred->data;
                status = AJ_X509VerifyChain(node, NULL, AJ_CERTIFICATE_IDN_X509);
                while (node) {
                    AJ_DumpBytes("CERTIFICATE", node->certificate.der.data, node->certificate.der.size);
                    node = node->next;
                }
                status = AJ_OK;
                break;
            }
            break;
        }
        break;

    default:
        break;
    }
    return status;
}

void AuthCallback(const void* context, AJ_Status status)
{
    *((AJ_Status*)context) = status;
}

int AJ_Main(int ac, char** av)
#else
int AJ_Main(void)
#endif
{
    int done = FALSE;
    AJ_Status status = AJ_OK;
    AJ_BusAttachment bus;
    uint8_t connected = FALSE;
    uint32_t sessionId = 0;
    AJ_Status authStatus = AJ_ERR_NULL;
    uint16_t state;
    uint16_t capabilities;
    uint16_t info;

    uint32_t suites[16];
    size_t numsuites = 0;
    uint8_t clearkeys = FALSE;
    X509CertificateChain* node;

    ac--;
    av++;
    /*
     * Enable authentication mechanism by command line
     */
    if (ac) {
        if (0 == strncmp(*av, "-ek", 3)) {
            clearkeys = TRUE;
            ac--;
            av++;
        } else if (0 == strncmp(*av, "-e", 2)) {
            ac--;
            av++;
        }
        if (!ac) {
            AJ_Printf("-e(k) requires an auth mechanism.\n");
            return 1;
        }
        while (ac) {
            if (0 == strncmp(*av, "ECDHE_ECDSA", 11)) {
                suites[numsuites++] = AUTH_SUITE_ECDHE_ECDSA;
            } else if (0 == strncmp(*av, "ECDHE_PSK", 9)) {
                suites[numsuites++] = AUTH_SUITE_ECDHE_PSK;
            } else if (0 == strncmp(*av, "ECDHE_NULL", 10)) {
                suites[numsuites++] = AUTH_SUITE_ECDHE_NULL;
            }
            ac--;
            av++;
        }
    }

    /*
     * One time initialization before calling any other AllJoyn APIs
     */
    AJ_Initialize();

    AJ_PrintXML(ProxyObjects);
    AJ_RegisterObjects(NULL, ProxyObjects);

    while (!done) {
        AJ_Message msg;

        if (!connected) {
            status = AJ_StartClientByName(&bus, NULL, CONNECT_TIMEOUT, FALSE, ServiceName, ServicePort, &sessionId, NULL, fullServiceName);
            if (status == AJ_OK) {
                AJ_InfoPrintf(("StartClient returned %d, sessionId=%u\n", status, sessionId));
                AJ_Printf("StartClient returned %d, sessionId=%u\n", status, sessionId);
                connected = TRUE;
                AJ_BusEnableSecurity(&bus, suites, numsuites);
                AJ_BusSetAuthListenerCallback(&bus, AuthListenerCallback);
                if (clearkeys) {
                    status = AJ_ClearCredentials();
                    if (AJ_OK != status) {
                        AJ_Printf("AJ_ClearCredentials returned %d\n", status);
                        break;
                    }
                }
                AJ_ManifestTemplateSet(&manifest);
                AJ_SecurityGetClaimConfig(&state, &capabilities, &info);
                /* Set app claimable if not already claimed */
                if (APP_STATE_CLAIMED != state) {
                    AJ_SecuritySetClaimConfig(&bus, APP_STATE_CLAIMABLE, CLAIM_CAPABILITY_ECDHE_PSK, 0);
                }

                status = AJ_BusAuthenticatePeer(&bus, fullServiceName, AuthCallback, &authStatus);
                if (status != AJ_OK) {
                    AJ_Printf("AJ_BusAuthenticatePeer returned %d\n", status);
                    break;
                }
            } else {
                AJ_InfoPrintf(("StartClient returned %d\n", status));
                AJ_Printf("StartClient returned %d\n", status);
                break;
            }
        }

        if (authStatus != AJ_ERR_NULL) {
            if (authStatus != AJ_OK) {
                AJ_Disconnect(&bus);
                break;
            }
            authStatus = AJ_ERR_NULL;
            SendPing(&bus, sessionId);
        }

        status = AJ_UnmarshalMsg(&bus, &msg, UNMARSHAL_TIMEOUT);

        if (AJ_ERR_TIMEOUT == status) {
            AppDoWork();
            continue;
        }

        if (AJ_OK == status) {
            switch (msg.msgId) {
            case AJ_REPLY_ID(PRX_PING):
                {
                    AJ_Arg arg;

                    if (AJ_OK == AJ_UnmarshalArg(&msg, &arg)) {
                        AJ_Printf("%s.Ping (path=%s) returned \"%s\".\n", InterfaceName,
                                  ServicePath, arg.val.v_string);

                        if (strcmp(arg.val.v_string, pingString) == 0) {
                            AJ_InfoPrintf(("Ping was successful.\n"));
                        } else {
                            AJ_InfoPrintf(("Ping returned different string.\n"));
                        }
                    } else {
                        AJ_ErrPrintf(("Bad ping response.\n"));
                    }
                    done = TRUE;
                }
                break;

            case AJ_SIGNAL_SESSION_LOST_WITH_REASON:
                /*
                 * Force a disconnect
                 */
                {
                    uint32_t id, reason;
                    AJ_UnmarshalArgs(&msg, "uu", &id, &reason);
                    AJ_AlwaysPrintf(("Session lost. ID = %u, reason = %u", id, reason));
                }
                status = AJ_ERR_SESSION_LOST;
                break;

            default:
                /*
                 * Pass to the built-in handlers
                 */
                status = AJ_BusHandleBusMessage(&msg);
                break;
            }
        }

        /*
         * Messages must be closed to free resources
         */
        AJ_CloseMsg(&msg);

        if ((status == AJ_ERR_READ) || (status == AJ_ERR_WRITE)) {
            AJ_Printf("AllJoyn disconnect.\n");
            AJ_Disconnect(&bus);
            break;
        }
    }

    AJ_Printf("SecureClient EXIT %d.\n", status);

    // Clean up certificate chain
    while (chain) {
        node = chain;
        chain = chain->next;
        AJ_Free(node->certificate.der.data);
        AJ_Free(node);
    }

    return status;
}

#ifdef AJ_MAIN
int main(int argc, char** argv)
{
    return AJ_Main(argc, argv);
}

#endif
