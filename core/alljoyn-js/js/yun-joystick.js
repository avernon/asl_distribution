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
var IO = require('IO');

/* Map AllJoyn-JS IO pins to Arduino Yun nomenclature. */

var D0 = IO.pin[0];
var D1 = IO.pin[1];
var D2 = IO.pin[2];
var D3 = IO.pin[3];
var D4 = IO.pin[4];
var D5 = IO.pin[5];
var D6 = IO.pin[6];
var D7 = IO.pin[7];
var D8 = IO.pin[8];
var D9 = IO.pin[9];
var D10 = IO.pin[10];
var D11 = IO.pin[11];
var D12 = IO.pin[12];
var D13 = IO.pin[13];

var A0 = IO.pin[14];
var A1 = IO.pin[15];
var A2 = IO.pin[16];
var A3 = IO.pin[17];
var A4 = IO.pin[18];
var A5 = IO.pin[19];


/* Joystick pin mapping for Open Jumper Joystick shield */
var xAxis    = IO.analogIn(A1);
var yAxis    = IO.analogIn(A0);
var red      = IO.digitalIn(D3, IO.pullUp);
var green    = IO.digitalIn(D4, IO.pullUp);
var blue     = IO.digitalIn(D5, IO.pullUp);
var yellow   = IO.digitalIn(D6, IO.pullUp);
var joystick = IO.digitalIn(D7, IO.pullUp);
var pin[12]LED = IO.digitalOut(D13);

function readJoystick()
{
    var redStr = "";
    var greenStr = "";
    var blueStr = "";
    var yellowStr = "";
    var jsStr = "";

    var rb = red.level;
    var gb = green.level;
    var bb = blue.level;
    var yb = yellow.level;
    var jsb = joystick.level;

    var xp = xAxis.value;
    var yp = yAxis.value;

    if (rb == 0) {
        redStr = " RED";
    }

    if (gb == 0) {
        greenStr = " GREEN";
    }

    if (bb == 0) {
        blueStr = " BLUE";
    }

    if (yb == 0) {
        yellowStr = " YELLOW";
    }

    if (jsb == 0) {
        jsStr = " JOYSTICK";
    }

    print("x = " + xp + "   y = " + yp + redStr + greenStr + blueStr + yellowStr + jsStr);
}

//red.setTrigger(IO.risingEdge, function(){ print("RED button up"); });
red.setTrigger(IO.fallingEdge, function(){ print("RED button down"); pin[12]LED.toggle(); });

//green.setTrigger(IO.risingEdge, function(){ print("GREEN button up"); });
green.setTrigger(IO.fallingEdge, function(){ print("GREEN button down"); });

//blue.setTrigger(IO.risingEdge, function(){ print("BLUE button up"); });
blue.setTrigger(IO.fallingEdge, function(){ print("BLUE button down"); });

//yellow.setTrigger(IO.risingEdge, function(){ print("YELLOW button up"); });
yellow.setTrigger(IO.fallingEdge, function(){ print("YELLOW button down"); });

//joystick.setTrigger(IO.risingEdge, function(){ print("JOYSTICK button up"); });
joystick.setTrigger(IO.fallingEdge, function(){ print("JOYSTICK button down"); });

setInterval(readJoystick, 1000);
