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

var cp = AJ.controlPanel();

function InitControlPanel(cp) {
    var c1 = cp.containerWidget(cp.VERTICAL);
    var l1 = c1.labelWidget("one");
    var l2 = c1.labelWidget("two");

    var p1 = c1.propertyWidget(cp.RADIO_BUTTON, 2);
    p1.choices = [ "cool", "warm", "hot" ];

    var p2 = c1.propertyWidget(cp.SLIDER, 50);
    p2.range = { min:0, max:100 };

    var a1 = c1.actionWidget("What Now?");
    var d1 = a1.dialogWidget("So do you want to do it?");
    d1.buttons = [
        { label:"ok", onClick: function() { print("ok"); } },
        { label:"cancel", onClick: function() { print("cancel"); } },
        { label:"apply", onClick: function() { print("apply"); } }
    ];

    c1.color={red:255,green:0,blue:128};
}

InitControlPanel(cp);

AJ.onAttach = function() { cp.load(); }

