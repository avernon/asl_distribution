/**
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

#include <stdint.h>
#include <stdarg.h>

#include <alljoyn.h>

#include <SPI.h>
#ifdef WIFI_UDP_WORKING
#include <WiFi.h>
#else
#include <Ethernet.h>
#endif

int AJ_Main(void);

void setup() {
    //Initialize serial and wait for port to open:
    Serial.begin(115200);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for Leonardo only
    }

    AJ_Printf("setup");

#ifdef WIFI_UDP_WORKING
    char ssid[] = "eric-wifi";
    int status = WL_IDLE_STATUS;     // the Wifi radio's status

    if (WiFi.status() == WL_NO_SHIELD) {
        Serial.println("WiFi shield not present");
        // don't continue:
        while (true) ;
    }

    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to open SSID: ");
        Serial.println(ssid);
        WiFi.begin(ssid);

        // wait 10 seconds for connection:
        delay(10000);
    }
#else
    byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0xA7, 0xCA };
    // start the Ethernet connection:
    if (Ethernet.begin(mac) == 0) {
        AJ_Printf("Failed to configure Ethernet using DHCP\n");
        // no point in carrying on, so do nothing forevermore:
        for (;;)
            ;
    }
#endif

}


void loop() {
    AJ_Main();
}

