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
var AJ = require('AllJoyn');
var IO = require('IO');

var cp = AJ.controlPanel();

var c1 = cp.containerWidget(cp.VERTICAL, cp.HORIZONTAL);
var rate = c1.propertyWidget(cp.SLIDER, 500, "Flash rate:");
rate.range = { min:20, max:1000, increment:50, units:"milliseconds" };

var led = IO.digitalOut(IO.pin[0]);

var blinky = setInterval(function(){led.toggle();}, rate.value);

rate.onValueChanged = function(val) { resetInterval(blinky, val); }

AJ.onAttach = function() { cp.load(); }
