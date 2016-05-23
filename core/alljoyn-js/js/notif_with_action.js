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

var d1 = cp.dialogWidget("What do you want to do?", "Decision");

d1.buttons = [
{ label:"ok", onClick: function() { print("ok"); } },
{ label:"cancel", onClick: function() { print("cancel"); } },
{ label:"apply", onClick: function() { print("apply"); } }
];

var notif = AJ.notification(AJ.notification.Emergency, "I've fallen and I can't get up!");
print("controlPanelPath " + d1.path);
notif.controlPanelPath = d1.path;

AJ.onAttach = function() { cp.load(); setTimeout(function() {notif.send(100)}, 5000) }

