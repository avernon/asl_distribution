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

function sendStruct1(svc)
{
    svc.method('struct1').call(["s1", "s2"]).onReply = function(arg) {
        if (arguments[0][0] == "s1" && arguments[0][1] == "s2") {
            print('STRUCT1 PASSED');
        } else {
            print('STRUCT1 FAILED');
            print('Struct1 (ss) replied: ' + JSON.stringify(arguments));
        }
    }
}

function sendArray3(svc)
{
    svc.method('array3').call(["one", "two", "three", "four", "five"]).onReply = function(arg) {
        if (arguments[0][0] == "one" && arguments[0][1] == "two" && arguments[0][2] == "three" && arguments[0][3] == "four" && arguments[0][4] == "five") {
            print('ARRAY3 PASSED');
        } else {
            print('ARRAY3 FAILED');
            print('Array3 "as" replied: ' + JSON.stringify(arguments));
        }
        sendStruct1(svc);
    }
}

function sendArray2(svc)
{
    svc.method('array2').call([12.34, 45.56,78.91, 1111.98765]).onReply = function(arg) {
        if (arguments[0][0] == 12.34 && arguments[0][1] == 45.56 && arguments[0][2] == 78.91 && arguments[0][3] == 1111.98765) {
            print('ARRAY2 PASSED');
        } else {
            print('ARRAY2 FAILED');
            print('Array2 "ad" replied: ' + JSON.stringify(arguments));
        }
        sendArray3(svc);
    }
}

function sendArray1(svc)
{
    svc.method('array1').call([true, false, true, false]).onReply = function(arg) {
        if (arguments[0][0] == true && arguments[0][1] == false && arguments[0][2] == true && arguments[0][3] == false) {
            print('ARRAY1 PASSED');
        } else {
            print('ARRAY1 FAILED');
            print('Array1 "ab" replied: ' + JSON.stringify(arguments));
        }
        sendArray2(svc);
    }
}

function sendString(svc)
{
    svc.method('string').call("a string").onReply = function(arg) {
        if (arguments[0] == "a string") {
            print('STRING PASSED');
        } else {
            print('STRING FAILED');
            print('String "s": ' + JSON.stringify(arguments));
        }
        sendArray1(svc);
    }
}

function sendFloating(svc)
{
    svc.method('floating').call(123.456).onReply = function(arg) {
        if (arguments[0] == 123.456) {
            print('FLOATING PASSED');
        } else {
            print('FLOATING FAILED');
            print('Floating "d": ' + JSON.stringify(arguments));
        }
        sendString(svc);
    }
}

function sendInts(svc)
{
    svc.method('ints').call(254, -10, 1000, -1000, 10000, -10000).onReply = function(arg) {
        if (arguments[0] == 254 && arguments[1] == -10 && arguments[2] == 1000 && arguments[3] == -1000 && arguments[4] == 10000 && arguments[5] == -10000) {
            print('INTS PASSED');
        } else {
            print('INTS FAILED');
            print('Ints "ynqiux": ' + JSON.stringify(arguments));
        }
        sendFloating(svc);
    }
}

function sendBool(svc)
{
    svc.method('bool').call(true).onReply = function(arg) {
        if (arguments[0] == true) {
            print('BOOLEAN PASSED');
        } else {
            print('BOOLEAN FAILED');
            print('Bool "b": ' + JSON.stringify(arguments));
        }
        sendInts(svc);
    }
}

function startSigTest(svc)
{
    sendBool(svc);
}

AJ.onAttach = function()
{
    print('Attached');
    AJ.findService('org.alljoyn.test.signatures', startSigTest);
}

AJ.onDetach = function()
{
    print('Detached');
}
