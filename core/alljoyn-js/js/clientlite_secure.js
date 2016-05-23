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

AJ.interfaceDefinition["org.alljoyn.alljoyn_test"] =
{
    my_ping:{ type:AJ.METHOD, args:[{inStr:"s"}], returns:[{outStr:"s"}] }
};

AJ.interfaceDefinition["org.alljoyn.alljoyn_test.values"] =
{
    int_val:{ type:AJ.PROPERTY, signature:"i" },
    str_val:{ type:AJ.PROPERTY, signature:"s" },
    ro_val:{ type:AJ.PROPERTY, signature:"s", access:"R" }
};

var service;

function callPing(svc, n)
{
    var my_method = svc.method('my_ping').call("ping message " + n).onReply = function(arg) {
        print("Ping replied with ", arg);
        /*
         * Send another ping one second after we get a reply from the setProp call
         */
        svc.setProp('int_val', n).onReply = function(){ setTimeout(function(){ callPing(svc, n + 1); }, 500);}
    }

}

function onSecuredComplete(svc, success)
{
    if (success) {
        callPing(svc, 0);
    } else {
        alert("authentication failed");
    }
}

AJ.onAttach = function()
{
    print("AJ.onAttach");
    AJ.findService('org.alljoyn.alljoyn_test', function(svc) {
        svc.enableSecurity(onSecuredComplete);
    });
}


AJ.onDetach = function()
{
    print("AJ.onDetach");
}

print("clientlite test program initialized\n");
