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

/*
 * This demonstrates AllJoyn.js' capability to reset your
 * devices access point information (SSID, Passphrase) using
 * offboarding. The blinking LED is your devices function
 * and the reset push button is a "network reset" button.
 *
 * Say you get this "blinking" device in your home and you
 * have onboarded it to your home router and it is blinking
 * away as it should. You then change your routers password
 * or SSID and you need to reconfigure the "blinking" device
 * to the new credentials. Since the device is head-less you
 * must have a way to reset these credentials. To do this
 * you call AJ.offboard() which will clear any old SSID
 * credentials and cause the device to go back into Soft AP
 * mode and wait to be onboarded again. Linking this
 * functionality to a button is the most realistic use case
 * since most devices like this always have a reset button.
 */

var AJ = require('AllJoyn');
var IO = require('IO');

var reset_pb = IO.digitalIn(IO.pin[22], IO.pullDown);
var blink = IO.digitalOut(IO.pin[7]);

/* This devices only function, blink */
function blink() {
    blink.toggle();
}

/* Function to reset the device */
function reset() {
    AJ.offboard();
}

reset_pb.trigger(IO.FallingEdge, reset);

setInterval(blink, 1000);
