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
#include <gtest/gtest.h>
#include <qcc/GUID.h>
#include <qcc/StringUtil.h>
#include <qcc/Thread.h>

#include <alljoyn/KeyStoreListener.h>
#include <alljoyn/Status.h>
#include <alljoyn/Message.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/ProxyBusObject.h>
#include <alljoyn/InterfaceDescription.h>
#include <qcc/Log.h>
#include "KeyStore.h"
#include "InMemoryKeyStore.h"

using namespace ajn;
using namespace qcc;

static const char* ONOFF_IFC_NAME = "org.allseenalliance.control.OnOff";

class AuthListenerECDHETest : public testing::Test, public BusObject {
  public:

    class ECDHEKeyXListener : public AuthListener {
      public:
        ECDHEKeyXListener(bool server) :
            sendKeys(true),
            sendExpiry(true),
            sendPrivateKey(true),
            sendCertChain(true),
            sendEmptyCertChain(false),
            sendExpiredChain(false),
            sendInvalidChain(false),
            sendInvalidChainNoCA(false),
            failVerifyCertChain(false),
            authComplete(false),
            pskName("<anonymous>"),
            psk("123456"),
            server(server)
        {
        }

        bool RequestCredentials(const char* authMechanism, const char* authPeer, uint16_t authCount, const char* userId, uint16_t credMask, Credentials& creds)
        {
            if (strcmp(authMechanism, "ALLJOYN_ECDHE_NULL") == 0) {
                if (!sendKeys) {
                    return false;
                }
                if (sendExpiry) {
                    creds.SetExpiration(100);  /* set the master secret expiry time to 100 seconds */
                }
                return true;
            } else if (strcmp(authMechanism, "ALLJOYN_ECDHE_PSK") == 0) {
                /*
                 * Solicit the Pre shared secret
                 * Based on the pre shared secret id, the application can retrieve
                 * the pre shared secret from storage or from the end user.
                 * In this example, the pre shared secret is a hard coded string
                 */
                if (!sendKeys) {
                    return false;
                }
                if ((credMask& AuthListener::CRED_USER_NAME) == AuthListener::CRED_USER_NAME) {
                    if (pskName != creds.GetUserName()) {
                        return false;
                    }
                }
                if (pskName != "<anonymous>") {
                    creds.SetUserName(pskName);
                }
                creds.SetPassword(psk);
                if (sendExpiry) {
                    creds.SetExpiration(100);  /* set the master secret expiry time to 100 seconds */
                }
                return true;
            } else if (strcmp(authMechanism, "ALLJOYN_ECDHE_ECDSA") == 0) {
                /* the server key and certificate are generated the unit test common/unit_test/CertificateECCTest::GenSelfSignECCX509CertForBBservice */
                static const char serverPrivateKeyPEM[] = {
                    "-----BEGIN EC PRIVATE KEY-----\n"
                    "MDECAQEEIICSqj3zTadctmGnwyC/SXLioO39pB1MlCbNEX04hjeioAoGCCqGSM49\n"
                    "AwEH\n"
                    "-----END EC PRIVATE KEY-----"
                };

                const char* serverPrivateKeyPEM;
                const char* serverCertChainX509PEM;
                const char* clientPrivateKeyPEM;
                const char* clientCertChainX509PEM;

                if (useCAPICerts == false) {
                    /* the server key and certificate are generated the unit test common/unit_test/CertificateECCTest::GenSelfSignECCX509CertForBBservice */
                    serverPrivateKeyPEM =
                        "-----BEGIN EC PRIVATE KEY-----\n"
                        "MDECAQEEII9KTdqfje8CzLnQ0asUaVdW1hmjQrP1AINRd03fdTAloAoGCCqGSM49\n"
                        "AwEH\n"
                        "-----END EC PRIVATE KEY-----";

                    serverCertChainX509PEM =
                        "-----BEGIN CERTIFICATE-----\n"
                        "MIIBtTCCAVugAwIBAgIHMTAxMDEwMTAKBggqhkjOPQQDAjBCMRUwEwYDVQQLDAxv\n"
                        "cmdhbml6YXRpb24xKTAnBgNVBAMMIDAyMzRjYjFhMmRlYmY5OTBmZGQ0NGJmZjlh\n"
                        "MjhjZDUxMB4XDTE1MDgyMTIyMjEwNloXDTI1MDgxODIyMjEwNlowQjEVMBMGA1UE\n"
                        "CwwMb3JnYW5pemF0aW9uMSkwJwYDVQQDDCBjN2UzYmRmNzhlOWRmNmRkOTk3N2Q4\n"
                        "NGUwMTE0MDYwMzBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABEjL84d4YPMMH5g9\n"
                        "kq5ErdTO4ouaGWLz7ikerB+HLPAu+aTekMxoA7uIejr5iekcWXxryJIxFwsdGh34\n"
                        "hl9YQKGjPDA6MAwGA1UdEwQFMAMBAf8wFQYDVR0lBA4wDAYKKwYBBAGC3nwBATAT\n"
                        "BgNVHSMEDDAKoAhCmX6GR09OkTAKBggqhkjOPQQDAgNIADBFAiEA026qDcGfTife\n"
                        "D75dbuT6MFz+sT8xuEkYNxyshK8vBMECIAa5lvbBATlTHSrb0FHg+jwFnQ2yYUE/\n"
                        "aFFhPrtFbwHn\n"
                        "-----END CERTIFICATE-----";

                    /* the client key and certificate are generated using openssl */

                    clientPrivateKeyPEM =
                        "-----BEGIN EC PRIVATE KEY-----\n"
                        "MDECAQEEIODvgKxWCGICBr+8EuqjdJ6km+u/6bU5dGSbJYUkZUPyoAoGCCqGSM49\n"
                        "AwEH\n"
                        "-----END EC PRIVATE KEY-----";

                    clientCertChainX509PEM =
                        "-----BEGIN CERTIFICATE-----\n"
                        "MIIBtDCCAVugAwIBAgIHMTAxMDEwMTAKBggqhkjOPQQDAjBCMRUwEwYDVQQLDAxv\n"
                        "cmdhbml6YXRpb24xKTAnBgNVBAMMIGRiODc2NjFiMDdmYTk5MTZkMmVmZjQ2OGQ0\n"
                        "ZmM2YjQ3MB4XDTE1MDgyMTIyMjMwOVoXDTI1MDgxODIyMjMwOVowQjEVMBMGA1UE\n"
                        "CwwMb3JnYW5pemF0aW9uMSkwJwYDVQQDDCBkZmY5ZWYxNDAxM2Y5MWI4ZmY1NDkw\n"
                        "MGY2YjkxZDM5NzBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABLS7W0+/OSGsyHdd\n"
                        "ygOH3Fa314dGWBptURbTCdHEULD//h2v3OqNNtD4a3A1KO73w9rTaWiAdqgqR/Pd\n"
                        "DYtG3WmjPDA6MAwGA1UdEwQFMAMBAf8wFQYDVR0lBA4wDAYKKwYBBAGC3nwBATAT\n"
                        "BgNVHSMEDDAKoAhErIVAya6ktjAKBggqhkjOPQQDAgNHADBEAiBZTJY2LEH4QuXU\n"
                        "Nxr6T1O/HHfFvrnZVaQsXoYUD+TH4QIgbHowpPfcf6tXGfgO6G7I3zRTJKpVVpGI\n"
                        "8AJMTO7lccs=\n"
                        "-----END CERTIFICATE-----\n";
                } else {
                    /*
                     * Use server and client certificates generated with the Windows
                     * Cryptography APIs (CAPI2 and CNG).
                     * See alljoyn_core\test\scripts\CAPI_Test_Cert_Generation.cmd and
                     * pfx2pem.cmd.
                     */
                    serverPrivateKeyPEM =
                        "-----BEGIN EC PRIVATE KEY-----\n"
                        "MHcCAQEEICZ4ITrSMWazoGPBCjxcv7goxSGvfOWAgSsebNq822JPoAoGCCqGSM49\n"
                        "AwEHoUQDQgAEp+fTvMjkcXZsE6h6i3JtBiO5N5kiOjXvGMHPhmPH70YLB3lw7tZK\n"
                        "E2im95nQWWOno9g5sdJOhZ1jftT1ksXKng==\n"
                        "-----END EC PRIVATE KEY-----";

                    serverCertChainX509PEM =
                        "-----BEGIN CERTIFICATE-----"
                        "MIIBhjCCASygAwIBAgIQXiWpM8rMappGXsKSElFtNzAKBggqhkjOPQQDAjAgMR4w\n"
                        "HAYDVQQDDBVBbGxKb3luVGVzdFNlcnZlck5hbWUwHhcNMTUwNzI4MTkzNjA4WhcN\n"
                        "MjkwNDA1MTk0NjA4WjAgMR4wHAYDVQQDDBVBbGxKb3luVGVzdFNlcnZlck5hbWUw\n"
                        "WTATBgcqhkjOPQIBBggqhkjOPQMBBwNCAASn59O8yORxdmwTqHqLcm0GI7k3mSI6\n"
                        "Ne8Ywc+GY8fvRgsHeXDu1koTaKb3mdBZY6ej2Dmx0k6FnWN+1PWSxcqeo0gwRjAO\n"
                        "BgNVHQ8BAf8EBAMCB4AwFQYDVR0lBA4wDAYKKwYBBAGC3nwBATAdBgNVHQ4EFgQU\n"
                        "vgKPPyMDzPUyW+t+q2krMQm5UUwwCgYIKoZIzj0EAwIDSAAwRQIhAKwlQpn74JbA\n"
                        "rYfeZcXyuPkXh733BxYprQlEkRbnYJzrAiBuzBFeuc812oCBUGSdHbp4kAJSEtAc\n"
                        "Cj7u3Pnwi1XLpg==\n"
                        "-----END CERTIFICATE-----";

                    clientPrivateKeyPEM =
                        "-----BEGIN EC PRIVATE KEY-----\n"
                        "MHcCAQEEIMEI3eVg2wJu9vteb8HA9rPZWznDpYy9daaDt5MFoAAeoAoGCCqGSM49\n"
                        "AwEHoUQDQgAEI63hx/KJK4CB4hexkkliN8NLWypIHd1sy8qcJgzGgHGlLzgTiPL1\n"
                        "V8vI7NQj3tL1oeuhlAuCgp6gZrYG+qbZIQ==\n"
                        "-----END EC PRIVATE KEY-----";

                    clientCertChainX509PEM =
                        "-----BEGIN CERTIFICATE-----\n"
                        "MIIBrDCCAVGgAwIBAgIQNwCHFovV/4FOTrJFpn6vKTAKBggqhkjOPQQDAjAkMSIw\n"
                        "IAYDVQQDDBlBbGxKb3luVGVzdFNlbGZTaWduZWROYW1lMB4XDTE1MDcyODE5Mzcw\n"
                        "NVoXDTI5MDQwNTE5NDcwNVowIDEeMBwGA1UEAwwVQWxsSm95blRlc3RDbGllbnRO\n"
                        "YW1lMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEI63hx/KJK4CB4hexkkliN8NL\n"
                        "WypIHd1sy8qcJgzGgHGlLzgTiPL1V8vI7NQj3tL1oeuhlAuCgp6gZrYG+qbZIaNp\n"
                        "MGcwDgYDVR0PAQH/BAQDAgeAMBUGA1UdJQQOMAwGCisGAQQBgt58AQEwHwYDVR0j\n"
                        "BBgwFoAUg4ZsZU12ghreVKZ0u2eyYHkiqeUwHQYDVR0OBBYEFFKYyjampcsD5WSv\n"
                        "+6EmxXIhXlOHMAoGCCqGSM49BAMCA0kAMEYCIQC8+DwrriZ4P/Mj+O4WUsIBiXNx\n"
                        "0Elf/P5YsoTnT3ycPgIhAMmIBBZTE+Xg7Hnpc8paraTlvvdBlsvyrYir9JalL0jy\n"
                        "-----END CERTIFICATE-----\n"
                        "\n"
                        "-----BEGIN CERTIFICATE-----\n"
                        "MIIBqzCCAVGgAwIBAgIQXlRHtjYelopJmcl8ZqvOXzAKBggqhkjOPQQDAjAkMSIw\n"
                        "IAYDVQQDDBlBbGxKb3luVGVzdFNlbGZTaWduZWROYW1lMB4XDTE1MDcyODE5MzYw\n"
                        "N1oXDTI5MDQwNTE5NDYwN1owJDEiMCAGA1UEAwwZQWxsSm95blRlc3RTZWxmU2ln\n"
                        "bmVkTmFtZTBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABFd3KMaxDMpXEkunL/my\n"
                        "LKou5xLNIJdSoMatDjC0Z8YMo9Ipk6hyIRoomZ1y0NvzPuvxW/HSiHuk91aTsQAS\n"
                        "iYijZTBjMA4GA1UdDwEB/wQEAwIBhjAhBgNVHSUEGjAYBgorBgEEAYLefAEBBgor\n"
                        "BgEEAYLefAEFMA8GA1UdEwEB/wQFMAMBAf8wHQYDVR0OBBYEFIOGbGVNdoIa3lSm\n"
                        "dLtnsmB5IqnlMAoGCCqGSM49BAMCA0gAMEUCIQDs7425v9snEPXNDQpP6JDWY0E4\n"
                        "fH4qVDQmeI0hisytZgIgINH4bxNiXXEL7V9cHOnm3gYdVTNpArbQvRjhwCuhX+M=\n"
                        "-----END CERTIFICATE-----\n";
                }

                static const char clientPrivateKeyPEM[] = {
                    "-----BEGIN EC PRIVATE KEY-----\n"
                    "MHcCAQEEIAqN6AtyOAPxY5k7eFNXAwzkbsGMl4uqvPrYkIj0LNZBoAoGCCqGSM49\n"
                    "AwEHoUQDQgAEvnRd4fX9opwgXX4Em2UiCMsBbfaqhB1U5PJCDZacz9HumDEzYdrS\n"
                    "MymSxR34lL0GJVgEECvBTvpaHP2bpTIl6g==\n"
                    "-----END EC PRIVATE KEY-----"
                };

                static const char clientCertChainX509PEM[] = {
                    "-----BEGIN CERTIFICATE-----\n"
                    "MIIBtDCCAVmgAwIBAgIJAMlyFqk69v+OMAoGCCqGSM49BAMCMFYxKTAnBgNVBAsM\n"
                    "IDdhNDhhYTI2YmM0MzQyZjZhNjYyMDBmNzdhODlkZDAyMSkwJwYDVQQDDCA3YTQ4\n"
                    "YWEyNmJjNDM0MmY2YTY2MjAwZjc3YTg5ZGQwMjAeFw0xNTAyMjYyMTUxMjVaFw0x\n"
                    "NjAyMjYyMTUxMjVaMFYxKTAnBgNVBAsMIDZkODVjMjkyMjYxM2IzNmUyZWVlZjUy\n"
                    "NzgwNDJjYzU2MSkwJwYDVQQDDCA2ZDg1YzI5MjI2MTNiMzZlMmVlZWY1Mjc4MDQy\n"
                    "Y2M1NjBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABL50XeH1/aKcIF1+BJtlIgjL\n"
                    "AW32qoQdVOTyQg2WnM/R7pgxM2Ha0jMpksUd+JS9BiVYBBArwU76Whz9m6UyJeqj\n"
                    "EDAOMAwGA1UdEwQFMAMBAf8wCgYIKoZIzj0EAwIDSQAwRgIhAKfmglMgl67L5ALF\n"
                    "Z63haubkItTMACY1k4ROC2q7cnVmAiEArvAmcVInOq/U5C1y2XrvJQnAdwSl/Ogr\n"
                    "IizUeK0oI5c=\n"
                    "-----END CERTIFICATE-----"
                    "\n"
                    "-----BEGIN CERTIFICATE-----\n"
                    "MIIBszCCAVmgAwIBAgIJAILNujb37gH2MAoGCCqGSM49BAMCMFYxKTAnBgNVBAsM\n"
                    "IDdhNDhhYTI2YmM0MzQyZjZhNjYyMDBmNzdhODlkZDAyMSkwJwYDVQQDDCA3YTQ4\n"
                    "YWEyNmJjNDM0MmY2YTY2MjAwZjc3YTg5ZGQwMjAeFw0xNTAyMjYyMTUxMjNaFw0x\n"
                    "NjAyMjYyMTUxMjNaMFYxKTAnBgNVBAsMIDdhNDhhYTI2YmM0MzQyZjZhNjYyMDBm\n"
                    "NzdhODlkZDAyMSkwJwYDVQQDDCA3YTQ4YWEyNmJjNDM0MmY2YTY2MjAwZjc3YTg5\n"
                    "ZGQwMjBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABGEkAUATvOE4uYmt/10vkTcU\n"
                    "SA0C+YqHQ+fjzRASOHWIXBvpPiKgHcINtNFQsyX92L2tMT2Kn53zu+3S6UAwy6yj\n"
                    "EDAOMAwGA1UdEwQFMAMBAf8wCgYIKoZIzj0EAwIDSAAwRQIgKit5yeq1uxTvdFmW\n"
                    "LDeoxerqC1VqBrmyEvbp4oJfamsCIQDvMTmulW/Br/gY7GOP9H/4/BIEoR7UeAYS\n"
                    "4xLyu+7OEA==\n"
                    "-----END CERTIFICATE-----"
                };

                static const char pkWithInvalidChain[] = {
                    "-----BEGIN EC PRIVATE KEY-----\n"
                    "MHcCAQEEIJxWUY1L8fnEMZlo6uFoGxBm/uIOZV6rpOoXXg5Tv01EoAoGCCqGSM49\n"
                    "AwEHoUQDQgAE4bEJQIGst7py9SpK1R//hhPsm7BVHLuHptbxdhudE7bM9kI7y3Uh\n"
                    "XLBHSSxEW7soqXqtJcKFrOzWPRTlF3bFjA==\n"
                    "-----END EC PRIVATE KEY-----"
                };
                static const char invalidChainCert2HasCA[] = {
                    "-----BEGIN CERTIFICATE-----\n"
                    "MIIBsTCCAVagAwIBAgIJAIgT+FrlL1qVMAoGCCqGSM49BAMCMFYxKTAnBgNVBAsM\n"
                    "IDEyMEFGQTU2Q0MwNjZFRkM5QUNCOEVBRTcyNjgxRDI5MSkwJwYDVQQDDCAxMjBB\n"
                    "RkE1NkNDMDY2RUZDOUFDQjhFQUU3MjY4MUQyOTAeFw0xNTAzMDQxNzA2MThaFw0x\n"
                    "NjAzMDMxNzA2MThaMFYxKTAnBgNVBAsMIDEyMEFGQTU2Q0MwNjZFRkM5QUNCOEVB\n"
                    "RTcyNjgxRDI5MSkwJwYDVQQDDCAxMjBBRkE1NkNDMDY2RUZDOUFDQjhFQUU3MjY4\n"
                    "MUQyOTBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABOGxCUCBrLe6cvUqStUf/4YT\n"
                    "7JuwVRy7h6bW8XYbnRO2zPZCO8t1IVywR0ksRFu7KKl6rSXChazs1j0U5Rd2xYyj\n"
                    "DTALMAkGA1UdEwQCMAAwCgYIKoZIzj0EAwIDSQAwRgIhAKKDBhCn9ZqYVtJDU6Tw\n"
                    "xwq8BXPzoDrQySHXtDvVpB5pAiEApGStoG974xGLfsIGeMWpUoiOTNe3FIYNmsEW\n"
                    "v6praiU=\n"
                    "-----END CERTIFICATE-----"
                    "\n"
                    "-----BEGIN CERTIFICATE-----\n"
                    "MIIBszCCAVmgAwIBAgIJALDTHYnf6i6VMAoGCCqGSM49BAMCMFYxKTAnBgNVBAsM\n"
                    "IDdhNDhhYTI2YmM0MzQyZjZhNjYyMDBmNzdhODlkZDAyMSkwJwYDVQQDDCA3YTQ4\n"
                    "YWEyNmJjNDM0MmY2YTY2MjAwZjc3YTg5ZGQwMjAeFw0xNTAzMDQxNzA2MjBaFw0x\n"
                    "NjAzMDMxNzA2MjBaMFYxKTAnBgNVBAsMIDdhNDhhYTI2YmM0MzQyZjZhNjYyMDBm\n"
                    "NzdhODlkZDAyMSkwJwYDVQQDDCA3YTQ4YWEyNmJjNDM0MmY2YTY2MjAwZjc3YTg5\n"
                    "ZGQwMjBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABANqoKVY9sET8YCj4gjTeYql\n"
                    "GXwLEK4I2aI0SxHZVNj+SQdGltEpnPRHO4jd/tGMnNpwGx0O6acOLrLGH/RIc3Cj\n"
                    "EDAOMAwGA1UdEwQFMAMBAf8wCgYIKoZIzj0EAwIDSAAwRQIgPY25+ozlDxgXVJ6T\n"
                    "Uh/vcIUonFt3pqqKtIe99Sc8AdMCIQC8VrFHBFp38e6UkY+Azuikrqi8tXDz8cr3\n"
                    "noKTwIxMpw==\n"
                    "-----END CERTIFICATE-----"
                };
                static const char invalidChainCert2HasNoCA[] = {
                    "-----BEGIN CERTIFICATE-----\n"
                    "MIIBsTCCAVagAwIBAgIJAIgT+FrlL1qVMAoGCCqGSM49BAMCMFYxKTAnBgNVBAsM\n"
                    "IDEyMEFGQTU2Q0MwNjZFRkM5QUNCOEVBRTcyNjgxRDI5MSkwJwYDVQQDDCAxMjBB\n"
                    "RkE1NkNDMDY2RUZDOUFDQjhFQUU3MjY4MUQyOTAeFw0xNTAzMDQxNzA2MThaFw0x\n"
                    "NjAzMDMxNzA2MThaMFYxKTAnBgNVBAsMIDEyMEFGQTU2Q0MwNjZFRkM5QUNCOEVB\n"
                    "RTcyNjgxRDI5MSkwJwYDVQQDDCAxMjBBRkE1NkNDMDY2RUZDOUFDQjhFQUU3MjY4\n"
                    "MUQyOTBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABOGxCUCBrLe6cvUqStUf/4YT\n"
                    "7JuwVRy7h6bW8XYbnRO2zPZCO8t1IVywR0ksRFu7KKl6rSXChazs1j0U5Rd2xYyj\n"
                    "DTALMAkGA1UdEwQCMAAwCgYIKoZIzj0EAwIDSQAwRgIhAKKDBhCn9ZqYVtJDU6Tw\n"
                    "xwq8BXPzoDrQySHXtDvVpB5pAiEApGStoG974xGLfsIGeMWpUoiOTNe3FIYNmsEW\n"
                    "v6praiU=\n"
                    "-----END CERTIFICATE-----"
                    "\n"
                    "-----BEGIN CERTIFICATE-----\n"
                    "MIIBsDCCAVagAwIBAgIJAP0No5ho6xiVMAoGCCqGSM49BAMCMFYxKTAnBgNVBAsM\n"
                    "IDZkODVjMjkyMjYxM2IzNmUyZWVlZjUyNzgwNDJjYzU2MSkwJwYDVQQDDCA2ZDg1\n"
                    "YzI5MjI2MTNiMzZlMmVlZWY1Mjc4MDQyY2M1NjAeFw0xNTAzMDQxNzA2MjFaFw0x\n"
                    "NjAzMDMxNzA2MjFaMFYxKTAnBgNVBAsMIDZkODVjMjkyMjYxM2IzNmUyZWVlZjUy\n"
                    "NzgwNDJjYzU2MSkwJwYDVQQDDCA2ZDg1YzI5MjI2MTNiMzZlMmVlZWY1Mjc4MDQy\n"
                    "Y2M1NjBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABA5Xe+uAlcKzCNfFylIEnggx\n"
                    "F6Gq9tmtLY9mxdyOvTsYwpYuirZAQ2wA+wKBPP7zh7+a3plbedd9GDZ8gow8KCmj\n"
                    "DTALMAkGA1UdEwQCMAAwCgYIKoZIzj0EAwIDSAAwRQIhAIOU2n6o8QXXbbJVEQe+\n"
                    "n5VkU6DybD3lnsjXSH+1PQVZAiBPCpi8p5xwlBUcFZI1EMPHoLi9XHZtchiJHEo/\n"
                    "OkxLog==\n"
                    "-----END CERTIFICATE-----"
                };
                static const char pkForExpiredChain[] = {
                    "-----BEGIN EC PRIVATE KEY-----\n"
                    "MHcCAQEEICpnmYJ+rYZyCB2GEbg4waemxF1edz1qGaSnbDFZwwmeoAoGCCqGSM49\n"
                    "AwEHoUQDQgAEl3JuZdX4Pd7APz2FKlHnpgK7pTkuwXlNM2U7krA8uDFTcY0TNEHV\n"
                    "94RlsWApksy4DJrjmOI9SIrQawMemG4IRw==\n"
                    "-----END EC PRIVATE KEY-----"
                };
                static const char expiredChain[] = {
                    "-----BEGIN CERTIFICATE-----\n"
                    "MIIBrzCCAVagAwIBAgIJAIfm4O/IwDXyMAoGCCqGSM49BAMCMFYxKTAnBgNVBAsM\n"
                    "IDdhNDhhYTI2YmM0MzQyZjZhNjYyMDBmNzdhODlkZDAyMSkwJwYDVQQDDCA3YTQ4\n"
                    "YWEyNmJjNDM0MmY2YTY2MjAwZjc3YTg5ZGQwMjAeFw0xNTAyMDEwMDAwMDBaFw0x\n"
                    "NTAyMjEwMDAwMDBaMFYxKTAnBgNVBAsMIDZkODVjMjkyMjYxM2IzNmUyZWVlZjUy\n"
                    "NzgwNDJjYzU2MSkwJwYDVQQDDCA2ZDg1YzI5MjI2MTNiMzZlMmVlZWY1Mjc4MDQy\n"
                    "Y2M1NjBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABJdybmXV+D3ewD89hSpR56YC\n"
                    "u6U5LsF5TTNlO5KwPLgxU3GNEzRB1feEZbFgKZLMuAya45jiPUiK0GsDHphuCEej\n"
                    "DTALMAkGA1UdEwQCMAAwCgYIKoZIzj0EAwIDRwAwRAIgAIGsd9RKxw2JDGcwYV9d\n"
                    "EGA4ZUBEXoZqMhRaIw6EjSECIGqablZqrDDzOr6ZGDG6f5X1/HWLOLmHStfHNA/1\n"
                    "BoXu\n"
                    "-----END CERTIFICATE-----"
                    "\n"
                    "-----BEGIN CERTIFICATE-----\n"
                    "MIIBszCCAVmgAwIBAgIJAMPSLBBoNwQIMAoGCCqGSM49BAMCMFYxKTAnBgNVBAsM\n"
                    "IDdhNDhhYTI2YmM0MzQyZjZhNjYyMDBmNzdhODlkZDAyMSkwJwYDVQQDDCA3YTQ4\n"
                    "YWEyNmJjNDM0MmY2YTY2MjAwZjc3YTg5ZGQwMjAeFw0xNTAzMjQxNzA0MTlaFw0x\n"
                    "NjAzMjMxNzA0MTlaMFYxKTAnBgNVBAsMIDdhNDhhYTI2YmM0MzQyZjZhNjYyMDBm\n"
                    "NzdhODlkZDAyMSkwJwYDVQQDDCA3YTQ4YWEyNmJjNDM0MmY2YTY2MjAwZjc3YTg5\n"
                    "ZGQwMjBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABOZknbv1si4H58TcDniPnlKm\n"
                    "zxR2xVh1VsZ7anvgSNlxzsiF/Y7qRXeE3G+3sBFjPhrWG63DZuGn96Y+u7qTbcCj\n"
                    "EDAOMAwGA1UdEwQFMAMBAf8wCgYIKoZIzj0EAwIDSAAwRQIgL7NAi2iY0fHaFtIC\n"
                    "d58shzZcoR8IMN3uZ1r+9UFboP8CIQDca5XNPYXn+IezASVqdGfs6KodmVIFK2IO\n"
                    "vAx+KmwF4Q==\n"
                    "-----END CERTIFICATE-----"
                };

                if (!sendKeys) {
                    return false;
                }
                if (sendPrivateKey && ((credMask& AuthListener::CRED_PRIVATE_KEY) == AuthListener::CRED_PRIVATE_KEY)) {
                    if (sendInvalidChain || sendInvalidChainNoCA) {
                        String pk(pkWithInvalidChain);
                        creds.SetPrivateKey(pk);
                    } else if (sendExpiredChain) {
                        String pk(pkForExpiredChain);
                        creds.SetPrivateKey(pk);
                    } else if (server) {
                        String pk(serverPrivateKeyPEM);
                        creds.SetPrivateKey(pk);
                    } else {
                        String pk(clientPrivateKeyPEM);
                        creds.SetPrivateKey(pk);
                    }
                }
                if (sendCertChain && ((credMask& AuthListener::CRED_CERT_CHAIN) == AuthListener::CRED_CERT_CHAIN)) {
                    if (sendEmptyCertChain) {
                        String cert;
                        creds.SetCertChain(cert);
                    } else if (sendInvalidChain) {
                        String cert(invalidChainCert2HasCA);
                        creds.SetCertChain(cert);
                    } else if (sendInvalidChainNoCA) {
                        String cert(invalidChainCert2HasNoCA);
                        creds.SetCertChain(cert);
                    } else if (sendExpiredChain) {
                        String cert(expiredChain);
                        creds.SetCertChain(cert);
                    } else if (server) {
                        String cert(serverCertChainX509PEM);
                        creds.SetCertChain(cert);
                    } else {
                        String cert(clientCertChainX509PEM);
                        creds.SetCertChain(cert);
                    }
                }
                if (sendExpiry) {
                    creds.SetExpiration(100);  /* set the master secret expiry time to 100 seconds */
                }
                return true;

            }
            return false;
        }

        bool VerifyCredentials(const char* authMechanism, const char* authPeer, const Credentials& creds)
        {
            /* only the ECDHE_ECDSA calls for peer credential verification */
            if (strcmp(authMechanism, "ALLJOYN_ECDHE_ECDSA") == 0) {
                if (failVerifyCertChain) {
                    return false;
                }
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
            authComplete = success;
            chosenMechanism = authMechanism;
        }

        bool sendKeys;
        bool sendExpiry;
        bool sendPrivateKey;
        bool sendCertChain;
        bool sendEmptyCertChain;
        bool sendExpiredChain;
        bool sendInvalidChain;
        bool sendInvalidChainNoCA;
        bool failVerifyCertChain;
        bool authComplete;
        qcc::String pskName;
        qcc::String psk;
        qcc::String chosenMechanism;
      private:
        bool server;
    };

    class SRPKeyXListener : public AuthListener {
      public:
        SRPKeyXListener()
        {
            pwd = "1a5dc770e6654144a9fac34281d3dc51";
        }

        bool RequestCredentials(const char* authMechanism, const char* authPeer, uint16_t authCount, const char* userId, uint16_t credMask, Credentials& creds)
        {
            QCC_UNUSED(authPeer);
            QCC_UNUSED(authCount);
            QCC_UNUSED(userId);

            if (strcmp(authMechanism, "ALLJOYN_SRP_KEYX") == 0) {
                if (credMask & AuthListener::CRED_PASSWORD) {
                    creds.SetPassword(pwd);
                    return true;
                }
            }
            return false;
        }

        bool VerifyCredentials(const char* authMechanism, const char* authPeer, const Credentials& creds)
        {
            QCC_UNUSED(authPeer);

            /* only the ECDHE_ECDSA calls for peer credential verification */
            if (strcmp(authMechanism, "ALLJOYN_SRP_KEYX") == 0) {
                return (creds.GetPassword() == pwd);
            }
            return false;
        }

        void AuthenticationComplete(const char* authMechanism, const char* authPeer, bool success)
        {
            QCC_UNUSED(authPeer);
            authComplete = success;
            chosenMechanism = authMechanism;
        }

        bool authComplete;
        qcc::String chosenMechanism;
      private:
        bool server;
        const char* pwd;
    };

    AuthListenerECDHETest() : BusObject("/AuthListenerECDHETest"),
        clientBus("AuthListenerECDHETestClient", false),
        serverBus("AuthListenerECDHETestServer", false),
        clientAuthListener(false),
        serverAuthListener(true)
    {
    }

    void SetUp()
    {
        EXPECT_EQ(ER_OK, clientBus.Start());
        EXPECT_EQ(ER_OK, clientBus.Connect());
        EXPECT_EQ(ER_OK, clientBus.RegisterKeyStoreListener(clientKeyStoreListener));
        CreateOnOffAppInterface(clientBus, false);
        EXPECT_EQ(ER_OK, serverBus.Start());
        EXPECT_EQ(ER_OK, serverBus.Connect());
        EXPECT_EQ(ER_OK, serverBus.RegisterKeyStoreListener(serverKeyStoreListener));
        CreateOnOffAppInterface(serverBus, true);
    }

    void TearDown()
    {
        clientBus.UnregisterKeyStoreListener();
        clientBus.UnregisterBusObject(*this);
        EXPECT_EQ(ER_OK, clientBus.Disconnect());
        EXPECT_EQ(ER_OK, clientBus.Stop());
        EXPECT_EQ(ER_OK, clientBus.Join());
        serverBus.UnregisterKeyStoreListener();
        serverBus.UnregisterBusObject(*this);
        EXPECT_EQ(ER_OK, serverBus.Disconnect());
        EXPECT_EQ(ER_OK, serverBus.Stop());
        EXPECT_EQ(ER_OK, serverBus.Join());
    }

    QStatus EnableSecurity(bool server, const char* keyExchange)
    {
        if (server) {
            return serverBus.EnablePeerSecurity(keyExchange, &serverAuthListener, NULL, false);
        } else {
            return clientBus.EnablePeerSecurity(keyExchange, &clientAuthListener, NULL, false);
        }
    }

    void CreateOnOffAppInterface(BusAttachment& bus, bool addService)
    {
        InterfaceDescription* ifc = NULL;
        QStatus status = bus.CreateInterface(ONOFF_IFC_NAME, ifc, AJ_IFC_SECURITY_REQUIRED);
        EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
        EXPECT_TRUE(ifc != NULL);
        if (ifc != NULL) {
            status = ifc->AddMember(MESSAGE_METHOD_CALL, "On", NULL, NULL, NULL);
            EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
            status = ifc->AddMember(MESSAGE_METHOD_CALL, "Off", NULL, NULL, NULL);
            EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
            ifc->Activate();

            if (!addService) {
                return;  /* done */
            }
            status = AddInterface(*ifc);
            EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
            AddMethodHandler(ifc->GetMember("On"), static_cast<MessageReceiver::MethodHandler>(&AuthListenerECDHETest::OnOffOn));
            AddMethodHandler(ifc->GetMember("Off"), static_cast<MessageReceiver::MethodHandler>(&AuthListenerECDHETest::OnOffOff));
            status = bus.RegisterBusObject(*this);
            EXPECT_EQ(ER_OK, status) << "  Actual Status: " << QCC_StatusText(status);
        }
    }

    BusAttachment clientBus;
    BusAttachment serverBus;
    ECDHEKeyXListener clientAuthListener;
    ECDHEKeyXListener serverAuthListener;

    void OnOffOn(const InterfaceDescription::Member* member, Message& msg)
    {
        MethodReply(msg, ER_OK);
    }
    void OnOffOff(const InterfaceDescription::Member* member, Message& msg)
    {
        MethodReply(msg, ER_OK);
    }

    QStatus ExerciseOn()
    {
        ProxyBusObject proxyObj(clientBus, serverBus.GetUniqueName().c_str(), GetPath(), 0, false);
        const InterfaceDescription* itf = clientBus.GetInterface(ONOFF_IFC_NAME);
        proxyObj.AddInterface(*itf);
        Message reply(clientBus);

        return proxyObj.MethodCall(ONOFF_IFC_NAME, "On", NULL, 0, reply, 5000);
    }

  private:
    InMemoryKeyStoreListener clientKeyStoreListener;
    InMemoryKeyStoreListener serverKeyStoreListener;
};

TEST_F(AuthListenerECDHETest, ECDHE_NULL_Success)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_NULL"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_NULL"));
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_NULL_Fail)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_NULL"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_NULL"));
    clientAuthListener.sendKeys = false;
    serverAuthListener.sendKeys = false;
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(clientAuthListener.authComplete);
    EXPECT_FALSE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_NULL_Success_DoNotSendExpiry)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_NULL"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_NULL"));
    clientAuthListener.sendExpiry = false;
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_PSK_Success_SendKeys)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_PSK"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_PSK"));
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_PSK_Success_DoNotSendExpiry)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_PSK"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_PSK"));
    clientAuthListener.sendExpiry = false;
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_PSK_Fail_DoNotSendKeys)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_PSK"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_PSK"));
    clientAuthListener.sendKeys = false;
    serverAuthListener.sendKeys = false;
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(clientAuthListener.authComplete);
    EXPECT_FALSE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_PSK_Fail_ServerDoNotSendKeys)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_PSK"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_PSK"));
    serverAuthListener.sendKeys = false;
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(clientAuthListener.authComplete);
    EXPECT_FALSE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_PSK_Fail_ClientDoNotSendKeys)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_PSK"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_PSK"));
    clientAuthListener.sendKeys = false;
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(clientAuthListener.authComplete);
    EXPECT_FALSE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_PSK_Fail_DifferentPSK)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_PSK"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_PSK"));
    clientAuthListener.psk = "123456789";
    serverAuthListener.psk = "nada";
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(clientAuthListener.authComplete);
    EXPECT_FALSE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_PSK_Success_PSKName)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_PSK"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_PSK"));
    clientAuthListener.pskName = "abc";
    serverAuthListener.pskName = "abc";
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_PSK_Fail_DifferentPSKName)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_PSK"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_PSK"));
    clientAuthListener.pskName = "abc";
    serverAuthListener.pskName = "dfe";
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(clientAuthListener.authComplete);
    EXPECT_FALSE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_Success)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_Success_DoNotSendExpiry)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    clientAuthListener.sendExpiry = false;
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_Fail_DoNotSendKeys)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    clientAuthListener.sendKeys = false;
    serverAuthListener.sendKeys = false;
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(clientAuthListener.authComplete);
    EXPECT_FALSE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_Fail_ServerDoNotSendKeys)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    serverAuthListener.sendKeys = false;
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(clientAuthListener.authComplete);
    EXPECT_FALSE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_Fail_ClientDoNotSendKeys)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    clientAuthListener.sendKeys = false;
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(clientAuthListener.authComplete);
    EXPECT_FALSE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_Fail_DoNotSendPrivateKey)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    clientAuthListener.sendPrivateKey = false;
    serverAuthListener.sendPrivateKey = false;
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(clientAuthListener.authComplete);
    EXPECT_FALSE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_Fail_ServerDoNotSendPrivateKey)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    serverAuthListener.sendPrivateKey = false;
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(clientAuthListener.authComplete);
    EXPECT_FALSE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_Fail_ClientDoNotSendPrivateKey)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    clientAuthListener.sendPrivateKey = false;
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(clientAuthListener.authComplete);
    EXPECT_FALSE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_Fail_DoNotSendCertChain)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    clientAuthListener.sendCertChain = false;
    serverAuthListener.sendCertChain = false;
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(clientAuthListener.authComplete);
    EXPECT_FALSE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_Fail_ServerDoNotSendCertChain)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    serverAuthListener.sendCertChain = false;
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(clientAuthListener.authComplete);
    EXPECT_FALSE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_Fail_ClientDoNotSendCertChain)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    clientAuthListener.sendCertChain = false;
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(clientAuthListener.authComplete);
    EXPECT_FALSE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_Fail_SendEmptyCertChain)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    clientAuthListener.sendEmptyCertChain = true;
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(clientAuthListener.authComplete);
    EXPECT_FALSE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_Fail_SendExpiredCertChain)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    clientAuthListener.sendExpiredChain = true;
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(clientAuthListener.authComplete);
    EXPECT_FALSE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_Fail_SendInvalidCertChainWithCA)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    clientAuthListener.sendInvalidChain = true;
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(clientAuthListener.authComplete);
    EXPECT_FALSE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_Fail_SendInvalidCertChainWithNoCA)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    clientAuthListener.sendInvalidChainNoCA = true;
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(clientAuthListener.authComplete);
    EXPECT_FALSE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_Fail_FailVerification)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    clientAuthListener.failVerifyCertChain = true;
    serverAuthListener.failVerifyCertChain = true;
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(clientAuthListener.authComplete);
    EXPECT_FALSE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_Fail_ServerFailVerification)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    serverAuthListener.failVerifyCertChain = true;
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(serverAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_Fail_ClientFailVerification)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    clientAuthListener.failVerifyCertChain = true;
    EXPECT_NE(ER_OK, ExerciseOn());
    EXPECT_FALSE(clientAuthListener.authComplete);
}

TEST_F(AuthListenerECDHETest, ECDHE_PSK_ECDSA_SuccessChosenByServer)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_PSK ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
    EXPECT_STREQ(clientAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_ECDSA");
    EXPECT_STREQ(serverAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_ECDSA");
}

TEST_F(AuthListenerECDHETest, ECDHE_PSK_ECDSA_SuccessChosenByClient)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_PSK ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
    EXPECT_STREQ(clientAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_ECDSA");
    EXPECT_STREQ(serverAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_ECDSA");
}

TEST_F(AuthListenerECDHETest, ECDHE_NULL_ECDSA_SuccessChosenByServer)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_NULL ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
    EXPECT_STREQ(clientAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_ECDSA");
    EXPECT_STREQ(serverAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_ECDSA");
}

TEST_F(AuthListenerECDHETest, ECDHE_NULL_ECDSA_SuccessChosenByClient)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_NULL ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
    EXPECT_STREQ(clientAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_ECDSA");
    EXPECT_STREQ(serverAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_ECDSA");
}

TEST_F(AuthListenerECDHETest, ECDHE_NULL_PSK_SuccessChosenByServer)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_PSK"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_NULL ALLJOYN_ECDHE_PSK"));
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
    EXPECT_STREQ(clientAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_PSK");
    EXPECT_STREQ(serverAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_PSK");
}

TEST_F(AuthListenerECDHETest, ECDHE_NULL_PSK_SuccessChosenByClient)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_NULL ALLJOYN_ECDHE_PSK"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_PSK"));
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
    EXPECT_STREQ(clientAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_PSK");
    EXPECT_STREQ(serverAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_PSK");
}

TEST_F(AuthListenerECDHETest, ECDHE_NULL_PSK_ECDSA_SuccessChosenByServer)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_NULL ALLJOYN_ECDHE_PSK ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
    EXPECT_STREQ(clientAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_ECDSA");
    EXPECT_STREQ(serverAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_ECDSA");
}

TEST_F(AuthListenerECDHETest, ECDHE_NULL_PSK_ECDSA_SuccessChosenByClient)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_NULL ALLJOYN_ECDHE_PSK ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
    EXPECT_STREQ(clientAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_ECDSA");
    EXPECT_STREQ(serverAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_ECDSA");
}

TEST_F(AuthListenerECDHETest, ECDHE_NULL_PSK_ECDSA_AcceptableDowngradeByServer)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_NULL ALLJOYN_ECDHE_PSK ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_PSK"));
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
    EXPECT_STREQ(clientAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_PSK");
    EXPECT_STREQ(serverAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_PSK");
}

TEST_F(AuthListenerECDHETest, ECDHE_NULL_PSK_ECDSA_Prioritized_To_ECDSA)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_NULL ALLJOYN_ECDHE_PSK ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_NULL ALLJOYN_ECDHE_PSK ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
    EXPECT_STREQ(clientAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_ECDSA");
    EXPECT_STREQ(serverAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_ECDSA");
}

TEST_F(AuthListenerECDHETest, ECDHE_PSK_ECDSA_Prioritized_To_ECDSA)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_PSK ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_PSK ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
    EXPECT_STREQ(clientAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_ECDSA");
    EXPECT_STREQ(serverAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_ECDSA");
}

TEST_F(AuthListenerECDHETest, ECDHE_NULL_PSK_Prioritized_To_PSK)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_NULL ALLJOYN_ECDHE_PSK"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_NULL ALLJOYN_ECDHE_PSK"));
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
    EXPECT_STREQ(clientAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_PSK");
    EXPECT_STREQ(serverAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_PSK");
}

TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_PSK_NULL_Prioritized_To_ECDSA)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA ALLJOYN_ECDHE_PSK ALLJOYN_ECDHE_NULL"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA ALLJOYN_ECDHE_PSK ALLJOYN_ECDHE_NULL"));
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
    EXPECT_STREQ(clientAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_ECDSA");
    EXPECT_STREQ(serverAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_ECDSA");
}

/**
 * In this test, the ECDHE_ECDSA key exchange fails.  The key exchange
 * downgrades to ECDHE_NULL and it should succeed.
 */
TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_Downgrade_To_ECDHE_NULL_FailOnClient)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA ALLJOYN_ECDHE_NULL"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA ALLJOYN_ECDHE_NULL"));
    clientAuthListener.failVerifyCertChain = true;
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
    EXPECT_STREQ(clientAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_NULL");
    EXPECT_STREQ(serverAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_NULL");
}

/**
 * In this test, the ECDHE_ECDSA key exchange fails.  The key exchange
 * downgrades to ECDHE_NULL and it should succeed.
 */
TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_Downgrade_To_ECDHE_NULL_FailOnServer)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA ALLJOYN_ECDHE_NULL"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA ALLJOYN_ECDHE_NULL"));
    serverAuthListener.failVerifyCertChain = true;
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
    EXPECT_STREQ(clientAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_NULL");
    EXPECT_STREQ(serverAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_NULL");
}

/**
 * In this test, the ECDHE_PSK key exchange fails.  The key exchange
 * downgrades to ECDHE_NULL and it should succeed.
 */
TEST_F(AuthListenerECDHETest, ECDHE_PSK_Downgrade_To_ECDHE_NULL)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_PSK ALLJOYN_ECDHE_NULL"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_PSK ALLJOYN_ECDHE_NULL"));
    serverAuthListener.psk = "03781075975973295739873982aabbcc";
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
    EXPECT_STREQ(clientAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_NULL");
    EXPECT_STREQ(serverAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_NULL");
}

/**
 * In this test, the ECDHE_ECDSA key exchange fails.  The key exchange
 * downgrades to ECDHE_PSK and it should succeed.
 */
TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_Downgrade_To_ECDHE_PSK)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA ALLJOYN_ECDHE_PSK"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA ALLJOYN_ECDHE_PSK"));
    serverAuthListener.failVerifyCertChain = true;
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
    EXPECT_STREQ(clientAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_PSK");
    EXPECT_STREQ(serverAuthListener.chosenMechanism.c_str(), "ALLJOYN_ECDHE_PSK");
}

TEST_F(AuthListenerECDHETest, ECDHE_ECDSA_TestExpiredSessionKey)
{
    EXPECT_EQ(ER_OK, EnableSecurity(true, "ALLJOYN_ECDHE_ECDSA"));
    EXPECT_EQ(ER_OK, EnableSecurity(false, "ALLJOYN_ECDHE_ECDSA"));
    clientAuthListener.sendExpiry = true;
    clientAuthListener.expirationSeconds = 10000u;
    serverAuthListener.sendExpiry = true;
    serverAuthListener.expirationSeconds = 1u;
    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);

    /* Despite saying the credential expires in 1 second, it seems to be the case that the minimum expiration
     * is 30 seconds. Sleep for 35 just to be sure.
     */
    printf("*** Sleep 35 secs since the minimum key expiration time is 30 seconds\n");
    qcc::Sleep(35000); /* Parameter for Sleep is ms. */

    /* Use a different bus attachment but use the same client key store. We need a different bus attachment
     * because the default one considers the server peer already secure.
     */
    EXPECT_EQ(ER_OK, secondClientBus.EnablePeerSecurity("ALLJOYN_ECDHE_ECDSA", &clientAuthListener, NULL, false));

    EXPECT_EQ(ER_OK, ExerciseOn(true)); /* `true' parameter will use secondClientBus. */
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
}

class PeerThread : public Thread {
  public:
    PeerThread(String name, BusAttachment& srcBus, BusAttachment& targetBus, const char* objectPath) : Thread(name), srcBus(srcBus), targetBus(targetBus), objectPath(objectPath)
    {
    }
    ~PeerThread()
    {
    }
    const QStatus GetResult() const
    {
        return result;
    }
  protected:
    ThreadReturn STDCALL Run(void* arg) {
        QCC_UNUSED(arg);
        ProxyBusObject proxy(srcBus, targetBus.GetUniqueName().c_str(), objectPath, 0, false);
        result = proxy.SecureConnection();
        return static_cast<ThreadReturn>(0);
    }
  private:
    BusAttachment& srcBus;
    BusAttachment& targetBus;
    const char* objectPath;
    QStatus result;
};

/**
 * Test the concurrent key exchange initiation between sets of peers.
 */
TEST_F(AuthListenerECDHETest, ConcurrentKeyExchange_4Threads_ECDSA)
{
    const char* mechanism = "ALLJOYN_ECDHE_ECDSA";
    EXPECT_EQ(ER_OK, EnableSecurity(true, mechanism));
    EXPECT_EQ(ER_OK, EnableSecurity(false, mechanism));
    /* setup the second bus not sharing the same key store as client bus */
    InMemoryKeyStoreListener secondClientKeyStoreListener;
    ECDHEKeyXListener secondClientAuthListener(false);
    EXPECT_EQ(ER_OK, secondClientBus.UnregisterKeyStoreListener());
    EXPECT_EQ(ER_OK, secondClientBus.RegisterKeyStoreListener(secondClientKeyStoreListener));
    EXPECT_EQ(ER_OK, secondClientBus.EnablePeerSecurity(mechanism, &secondClientAuthListener, NULL, false));

    String name = "thread1: client bus " + clientBus.GetUniqueName() + " to serverBus " + serverBus.GetUniqueName();
    PeerThread thread1(name, clientBus, serverBus, GetPath());
    name = "thread2: server bus " + serverBus.GetUniqueName() + " to clientBus " + clientBus.GetUniqueName();
    PeerThread thread2(name, serverBus, clientBus, GetPath());
    name = "thread3: second bus " + secondClientBus.GetUniqueName() + " to serverBus " + serverBus.GetUniqueName();
    PeerThread thread3(name, secondClientBus, serverBus, GetPath());
    name = "thread4: server bus " + serverBus.GetUniqueName() + " to second Bus " + secondClientBus.GetUniqueName();
    PeerThread thread4(name, serverBus, secondClientBus, GetPath());

    thread1.Start();
    thread2.Start();
    thread3.Start();
    thread4.Start();
    thread1.Join();
    thread2.Join();
    thread3.Join();
    thread4.Join();
    EXPECT_EQ(ER_OK, thread1.GetResult());
    EXPECT_EQ(ER_OK, thread2.GetResult());
    EXPECT_EQ(ER_OK, thread3.GetResult());
    EXPECT_EQ(ER_OK, thread4.GetResult());

    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_EQ(ER_OK, ExerciseOn(true)); /* `true' parameter will use secondClientBus. */
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
    EXPECT_TRUE(secondClientAuthListener.authComplete);
    EXPECT_STREQ(clientAuthListener.chosenMechanism.c_str(), mechanism);
    EXPECT_STREQ(serverAuthListener.chosenMechanism.c_str(), mechanism);
    EXPECT_STREQ(secondClientAuthListener.chosenMechanism.c_str(), mechanism);
}

TEST_F(AuthListenerECDHETest, ConcurrentKeyExchange_2Threads_NULL)
{
    const char* mechanism = "ALLJOYN_ECDHE_NULL";
    EXPECT_EQ(ER_OK, EnableSecurity(true, mechanism));
    EXPECT_EQ(ER_OK, EnableSecurity(false, mechanism));

    String name = "thread1: client bus " + clientBus.GetUniqueName() + " to serverBus " + serverBus.GetUniqueName();
    PeerThread thread1(name, clientBus, serverBus, GetPath());
    name = "thread2: server bus " + serverBus.GetUniqueName() + " to clientBus " + clientBus.GetUniqueName();
    PeerThread thread2(name, serverBus, clientBus, GetPath());

    thread1.Start();
    thread2.Start();
    thread1.Join();
    thread2.Join();
    EXPECT_EQ(ER_OK, thread1.GetResult());
    EXPECT_EQ(ER_OK, thread2.GetResult());

    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
    EXPECT_STREQ(clientAuthListener.chosenMechanism.c_str(), mechanism);
    EXPECT_STREQ(serverAuthListener.chosenMechanism.c_str(), mechanism);
}

TEST_F(AuthListenerECDHETest, ConcurrentKeyExchange_2Threads_PSK)
{
    const char* mechanism = "ALLJOYN_ECDHE_PSK";
    EXPECT_EQ(ER_OK, EnableSecurity(true, mechanism));
    EXPECT_EQ(ER_OK, EnableSecurity(false, mechanism));

    String name = "thread1: client bus " + clientBus.GetUniqueName() + " to serverBus " + serverBus.GetUniqueName();
    PeerThread thread1(name, clientBus, serverBus, GetPath());
    name = "thread2: server bus " + serverBus.GetUniqueName() + " to clientBus " + clientBus.GetUniqueName();
    PeerThread thread2(name, serverBus, clientBus, GetPath());

    thread1.Start();
    thread2.Start();
    thread1.Join();
    thread2.Join();
    EXPECT_EQ(ER_OK, thread1.GetResult());
    EXPECT_EQ(ER_OK, thread2.GetResult());

    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientAuthListener.authComplete);
    EXPECT_TRUE(serverAuthListener.authComplete);
    EXPECT_STREQ(clientAuthListener.chosenMechanism.c_str(), mechanism);
    EXPECT_STREQ(serverAuthListener.chosenMechanism.c_str(), mechanism);
}

TEST_F(AuthListenerECDHETest, ConcurrentKeyExchange_2Threads_SRP)
{
    const char* mechanism = "ALLJOYN_SRP_KEYX";
    SRPKeyXListener serverListener;
    EXPECT_EQ(ER_OK, serverBus.EnablePeerSecurity(mechanism, &serverListener, NULL, false));
    SRPKeyXListener clientListener;
    EXPECT_EQ(ER_OK, clientBus.EnablePeerSecurity(mechanism, &clientListener, NULL, false));

    String name = "thread1: client bus " + clientBus.GetUniqueName() + " to serverBus " + serverBus.GetUniqueName();
    PeerThread thread1(name, clientBus, serverBus, GetPath());
    name = "thread2: server bus " + serverBus.GetUniqueName() + " to clientBus " + clientBus.GetUniqueName();
    PeerThread thread2(name, serverBus, clientBus, GetPath());

    thread1.Start();
    thread2.Start();
    thread1.Join();
    thread2.Join();
    EXPECT_EQ(ER_OK, thread1.GetResult());
    EXPECT_EQ(ER_OK, thread2.GetResult());

    EXPECT_EQ(ER_OK, ExerciseOn());
    EXPECT_TRUE(clientListener.authComplete);
    EXPECT_TRUE(serverListener.authComplete);
    EXPECT_STREQ(clientListener.chosenMechanism.c_str(), mechanism);
    EXPECT_STREQ(serverListener.chosenMechanism.c_str(), mechanism);
}
