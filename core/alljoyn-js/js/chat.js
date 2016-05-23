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

/*
 * Put name extension here. This should be the same as the command
 * line arguments fed to the SCL chat sample (./chat -s <your name>)
 */
var nameExt = "name";

AJ.interfaceDefinition["org.alljoyn.bus.samples.chat"] = { Chat:{ type:AJ.SIGNAL, args:["s"] }, };

AJ.objectDefinition['/chatService'] = { interfaces:['org.alljoyn.bus.samples.chat'] };

var cp = AJ.controlPanel();
var cw = cp.containerWidget(cp.VERTICAL, cp.HORIZONTAL);
var edit_text = cw.propertyWidget(cp.EDIT_TEXT, "", "Chat:");
var text_label = cw.propertyWidget(cp.TEXT_VIEW, "Message:");
/*
 * Need to hold a reference to the service otherwise once found()
 * returns you will lose the service object and no longer receive
 * any signals/method calls from that service.
 */
var service;

edit_text.onValueChanged = function (val) {
   var chat_sig = service.signal('/chatService', {Chat:'org.alljoyn.bus.samples.chat'});
   chat_sig.send(val);
}

function found(svc)
{
    print('Found service');
    service = svc;
}

var nameObject = {
    interfaces:['org.alljoyn.bus.samples.chat'],
    path:'/chatService',
    port:27
}

AJ.onSignal = function()
{
    /*
     * Print out the chat message received
     */
    if (this.member == 'Chat') {
        print(arguments[0]);
        text_label.value = arguments[0];
    }
}

AJ.onAttach = function()
{
    cp.load();
    AJ.addMatch('org.alljoyn.bus.samples.chat', 'Chat');
    /*
     * Legacy API used to find a service by name, rather than using About
     */
    AJ.findServiceByName("org.alljoyn.bus.samples.chat." + nameExt, nameObject, found); 
}

AJ.onDetach = function()
{ 
    print("AJ.onDetach");
}
