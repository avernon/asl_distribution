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

var led1=IO.digitalOut(IO.pin[0]);
var led2=IO.digitalOut(IO.pin[1], 0);
var led3=IO.digitalOut(IO.pin[2]);
var led4=IO.digitalOut(IO.pin[3], 0);

var in1=IO.digitalIn(IO.pin[4], IO.pullUp);
var in2=IO.digitalIn(IO.pin[5], IO.pullUp);
var in3=IO.digitalIn(IO.pin[6], IO.pullUp);
var in4=IO.digitalIn(IO.pin[7], IO.pullUp);

var pb1=IO.digitalIn(IO.pin[8], IO.pullUp);
var pb2=IO.digitalIn(IO.pin[9], IO.pullUp);
var pb3=IO.digitalIn(IO.pin[10], IO.pullUp);
var pb4=IO.digitalIn(IO.pin[11], IO.pullUp);

var uart=IO.uart(IO.pin[12], IO.pin[13], 9600);

setInterval(function() {
    if (in1.level == 1) { led1.toggle() }
    if (in2.level == 1) { led2.toggle() }
    if (in3.level == 1) { led3.toggle() }
    if (in4.level == 1) { led4.pwm(Math.round(saw()*100)/100, 1)  }
}, 500);

pb1.setTrigger(IO.fallingEdge | IO.risingEdge, function(){ uart.write(this.pin.info.description + this.level); led1.toggle()});
pb2.setTrigger(IO.fallingEdge, function(){ uart.write(this.pin.info.description + this.level); led2.toggle()});
pb3.setTrigger(IO.risingEdge, function(){ uart.write(this.pin.info.description + this.level); led3.toggle()});
pb4.setTrigger(IO.risingEdge, function(){ uart.write(this.pin.info.description + this.level); led4.toggle()});

function uartOnRxReady(data)
{
    data = uart.read(16);
    uart.write("->" + data + "<-");
}

uart.setTrigger(IO.rxReady, uartOnRxReady);

var saw = sawTooth(1.0, 0.1);
function sawTooth(peak, step) {
    var i = peak-step;
    return function() {
        return Math.abs((i += step)%(2*peak)-peak)
    }
}

