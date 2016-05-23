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

AJ.interfaceDefinition["org.alljoyn.alljoyn_test.values"] =
{
    int_val:{ type:AJ.PROPERTY, signature:"i" },
    str_val:{ type:AJ.PROPERTY, signature:"s" },
    ro_val:{ type:AJ.PROPERTY, signature:"s", access:"R" }
};

function startGetSet(svc, n)
{
    var int_val = svc.getProp('int_val');
    var str_val = svc.getProp('str_val');
    var ro_val = svc.getProp('ro_val');
    print('int: ' + int_val + ' str: ' + str_val + ' ro: ' + ro_val);
    svc.getAllProps('org.alljoyn.alljoyn_test.values').onReply = function() {
        print(JSON.stringify(arguments));
        svc.setProp('int_val', n).onReply = function() { setTimeout(function() { startGetSet(svc, n + 1); }, 100)}
    }
}

AJ.onAttach = function()
{
    print("AJ.onAttach");
    AJ.findService('org.alljoyn.alljoyn_test.values', function(svc) { startGetSet(svc, 0); });
}

AJ.onDetach = function()
{
    print("AJ.onDetach");
}

print("getset client test program initialized\n");
