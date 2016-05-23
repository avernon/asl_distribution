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

/* 
 * Configure light sensor ADC
 */
var pin = IO.digitalOut(IO.pin[10], 1)
var lightSensor = IO.analogIn(IO.pin[11]);

function lightCheck()
{
    var level = lightSensor.value;
    print("Light level=", level);
    if (level > 10000 && this.bright != true) {
        this.bright = true;
        this.dark = false;
        AJ.notification(AJ.notification.Info, "Light is too bright " + level).send(100);
    } else if (level < 1000 && this.dark != true) {
        this.bright = false;
        this.dark = true;
        AJ.notification(AJ.notification.Emergency, "Help mommy it's dark").send(100);
    }
}

setInterval(lightCheck, 1000);
