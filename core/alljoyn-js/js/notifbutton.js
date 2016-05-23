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

var pbA=IO.digitalIn(IO.pin[8], IO.pullDown);
var pbB=IO.digitalIn(IO.pin[9], IO.pullDown);

AJ.onAttach = function()
{
    print('attached');
    pbA.setTrigger(IO.fallingEdge, function(){ AJ.notification(AJ.notification.Warning, "Button A pressed").send(200); })
    pbB.setTrigger(IO.fallingEdge, function(){ AJ.notification(AJ.notification.Emergency, "Button B pressed").send(200); })
}

AJ.onDetach = function()
{
    pbA.setTrigger(IO.disable);
    pbB.setTrigger(IO.disable);
}
