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
 
var cp = AJ.controlPanel(); 
var c1 = cp.containerWidget(cp.VERTICAL, cp.HORIZONTAL); 

var freq = c1.propertyWidget(cp.SLIDER, 10000, "Frequency:");
var duty = c1.propertyWidget(cp.SLIDER, 50, "Duty Cycle:");

freq.range = {min:100, max:100000, increment:100, units:"Hz"};
duty.range = {min:1, max:100, increment:5, units:"%"};

var led = IO.digitalOut(IO.pin[16]);

var bright = led.pwm(duty.value / 100, freq.value);

freq.onValueChanged = function(val) { led.pwm(duty.value / 100, val);}
duty.onValueChanged = function(val) { led.pwm(val / 100, freq.value); }

AJ.onAttach = function() { cp.load();} 
 