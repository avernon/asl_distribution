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

AJ.interfaceDefinition['org.alljoyn.test.signatures'] =
{
    bool:{ type:AJ.METHOD, args:["b"], returns:["b"] },
    ints: { type:AJ.METHOD, args:["ynqiux"], returns:["ynqiux"] },
    floating: { type:AJ.METHOD, args:["d"], returns:["d"] },
    string: { type:AJ.METHOD, args:["s"], returns:["s"] },
    array1: { type:AJ.METHOD, args:["ab"], returns:["ab"] },
    array2: { type:AJ.METHOD, args:["ad"], returns:["ad"] },
    array3: { type:AJ.METHOD, args:["as"], returns:["as"] },
    struct1: { type:AJ.METHOD, args:["(ss)"], returns:["(ss)"] }
};

AJ.objectDefinition['/org/alljoyn/test/signatures'] =
{
    interfaces:['org.alljoyn.test.signatures']
};

AJ.onAttach = function()
{
    print('Attached');
}

AJ.onDetach = function()
{
    print('Detached');
}

AJ.onMethodCall = function()
{
    if (this.member == 'bool') {
        print('Got bool: ' + JSON.stringify(arguments));
        this.reply(true);
    } else if (this.member == 'ints') {
        print('Got ints: ' + JSON.stringify(arguments));
        this.reply(arguments[0], arguments[1], arguments[2], arguments[3], arguments[4], arguments[5])
    } else if (this.member == 'floating') {
        print('Got floating: ' + JSON.stringify(arguments));
        this.reply(arguments[0]);
    } else if (this.member == 'string') {
        print('Got string: ' + JSON.stringify(arguments));
        this.reply(arguments[0]);
    } else if (this.member == 'array1') {
        print('Got array1: ' + JSON.stringify(arguments));
        var arr = [];
        for (var i = 0; i < arguments[0].length;i++) {
            arr[i] = arguments[0][i];
        }
        this.reply(arr);
    } else if (this.member == 'array2') {
        print('Got array2: ' + JSON.stringify(arguments));
        var arr = [];
        for (var i = 0; i < arguments[0].length;i++) {
            arr[i] = arguments[0][i];
        }
        this.reply(arr);
    } else if (this.member == 'array3') {
        print('Got array3: ' + JSON.stringify(arguments));
        var arr = [];
        // arguments is an object and its zeroth index is the actual array
        for (var i = 0; i < arguments[0].length;i++) {
            arr[i] = arguments[0][i];
        }
        this.reply(arr);
    } else if (this.member == 'struct1') {
        print('Got struct1: ' + JSON.stringify(arguments));
        var arr = [];
        // arguments is an object and its zeroth index is the actual struct (also an array)
        for (var i = 0; i < arguments[0].length;i++) {
            arr[i] = arguments[0][i];
        }
        this.reply(arr);
    }
}
