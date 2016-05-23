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

AJ.interfaceDefinition['org.alljoyn.alljoyn_test'] =
{
    my_ping:{ type:AJ.METHOD, args:[{inStr:'s'}], returns:[{outStr:'s'}] },
    my_signal:{ type:AJ.SIGNAL, args:["a{ys}"]}
};

AJ.interfaceDefinition['org.alljoyn.alljoyn_test.values'] =
{
    int_val:{ type:AJ.PROPERTY, signature:'i' },
    str_val:{ type:AJ.PROPERTY, signature:'s' },
    ro_val:{ type:AJ.PROPERTY, signature:'s', access:'R' }
};

AJ.objectDefinition['/org/alljoyn/alljoyn_test'] = {
    interfaces:['org.alljoyn.alljoyn_test', 'org.alljoyn.alljoyn_test.values']
};

properties = {
    int_val:123,
    str_val:'hello',
    ro_val:'a read only value'
};

AJ.onAttach = function()
{
    print('Attached');
}

AJ.onPeerConnected = function(peer)
{
    peer.authenticate('/org/alljoyn/alljoyn_test');
    return true;
}

AJ.onPropSet = function(iface, prop, value)
{
    if (iface == 'org.alljoyn.alljoyn_test.values') {
        properties[prop] = value;
        this.reply();
    } else {
        throw('rejected');
    }
}

AJ.onPropGet = function(iface, prop)
{
    if (iface == 'org.alljoyn.alljoyn_test.values') {
        this.reply(properties[prop]);
    } else {
        throw('rejected');
    }
}

AJ.onMethodCall = function(arg)
{
    if (this.member == 'my_ping') {
        print('my_ping ', arg);
        this.reply(arg);
    } else {
        throw('rejected');
    }
}

AJ.onSignal = function() {
    if (this.member == 'my_signal') {
        print('my_signal received');
    }
}

print('svclite test program initialized\n');
