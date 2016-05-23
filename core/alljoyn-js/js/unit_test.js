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

var args_object = {
    sessionless_sig1: "sessionless_sig1",
    sessionless_sig2: 123456,
    sessionless_sig3: 1234.5678,
    sessionless_sig4: true,
    sessionless_sig5: ['one', 'two', 'three', 'four', 'five', 'six'],
    sessionless_sig6: [1111, 2222, 3333, 4444, 5555, 6666],
    sessionless_sig7: [111.111, 222.222, 333.333, 444.444, 555.555, 666.666],
    sessionless_sig8: [true, false, true, false, true, false]
}

AJ.interfaceDefinition['org.alljoyn.unit_test'] =
{
    sessionless_sig1:{ type:AJ.SIGNAL, args:["s"] },
    sessionless_sig2:{ type:AJ.SIGNAL, args:["u"] },
    sessionless_sig3:{ type:AJ.SIGNAL, args:["d"] },
    sessionless_sig4:{ type:AJ.SIGNAL, args:["b"] },
    sessionless_sig5:{ type:AJ.SIGNAL, args:["as"] },
    sessionless_sig6:{ type:AJ.SIGNAL, args:["au"] },
    sessionless_sig7:{ type:AJ.SIGNAL, args:["ad"] },
    sessionless_sig8:{ type:AJ.SIGNAL, args:["ab"] },
};

AJ.objectDefinition['/org/alljoyn/unit_test1'] =
{
    interfaces:['org.alljoyn.unit_test']
};

AJ.objectDefinition['/org/alljoyn/unit_test2'] =
{
    interfaces:['org.alljoyn.unit_test']
};

AJ.objectDefinition['/org/alljoyn/unit_test3'] =
{
    interfaces:['org.alljoyn.unit_test']
};

AJ.objectDefinition['/org/alljoyn/unit_test4'] =
{
    interfaces:['org.alljoyn.unit_test']
};

AJ.objectDefinition['/org/alljoyn/unit_test5'] =
{
    interfaces:['org.alljoyn.unit_test']
};

AJ.objectDefinition['/org/alljoyn/unit_test6'] =
{
    interfaces:['org.alljoyn.unit_test']
};

AJ.objectDefinition['/org/alljoyn/unit_test7'] =
{
    interfaces:['org.alljoyn.unit_test']
};

AJ.objectDefinition['/org/alljoyn/unit_test8'] =
{
    interfaces:['org.alljoyn.unit_test']
};

var MAX_SIG_ITERATIONS = 1000;
var self_sls_count = 0;
var sls_count = 0;

var sls_pass = true;
var sls_done = false;
var counter_pass = true;
var count_done = false;
var nvram_pass = true;
var nvram_done = false;

AJ.onSignal = function()
{
    if (this.member == 'sessionless_sig1') {
        if (arguments[0] == args_object.sessionless_sig1) {
            self_sls_count++;
        } else {
            alert('ERROR: sessionless_sig1: invalid argument: ' + arguments[0]);
            sls_pass = false;
        }
    } else if (this.member == 'sessionless_sig2') {
        if (arguments[0] == args_object.sessionless_sig2) {
            self_sls_count++;
        } else {
            alert('ERROR: sessionless_sig2: invalid argument: ' + arguments[0]);
            sls_pass = false;
        }
    } else if (this.member == 'sessionless_sig3') {
        if (arguments[0] == args_object.sessionless_sig3) {
            self_sls_count++;
        } else {
            alert('ERROR: sessionless_sig3: invalid argument: ' + arguments[0]);
            sls_pass = false;
        }
    } else if (this.member == 'sessionless_sig4') {
        if (arguments[0] == args_object.sessionless_sig4) {
            self_sls_count++;
        } else {
            alert('ERROR: sessionless_sig1: invalid argument: ' + arguments[0]);
            sls_pass = false;
        }
    } else if (this.member == 'sessionless_sig5') {
        var pass = true;
        for (var i = 0; i < arguments[0].length; i++) {
            if (arguments[0][i] != args_object.sessionless_sig5[i]) {
                alert('ERROR: sessionless_sig5: invalid argument: ' + arguments[0]);
                pass = false;
            }
        }
        if (pass) {
            self_sls_count++;
        } else {
            sls_pass = false;
        }
    } else if (this.member == 'sessionless_sig6') {
        var pass = true;
        for (var i = 0; i < arguments[0].length; i++) {
            if (arguments[0][i] != args_object.sessionless_sig6[i]) {
                alert('ERROR: sessionless_sig6: invalid argument: ' + arguments[0]);
                pass = false;
            }
        }
        if (pass) {
            self_sls_count++;
        } else {
            sls_pass = false;
        }
    } else if (this.member == 'sessionless_sig7') {
        var pass = true;
        for (var i = 0; i < arguments[0].length; i++) {
            if (arguments[0][i] != args_object.sessionless_sig7[i]) {
                alert('ERROR: sessionless_sig7: invalid argument: ' + arguments[0]);
                pass = false;
            }
        }
        if (pass) {
            self_sls_count++;
        } else {
            sls_pass = false;
        }
    } else if (this.member == 'sessionless_sig8') {
        var pass = true;
        for (var i = 0; i < arguments[0].length; i++) {
            if (arguments[0][i] != args_object.sessionless_sig8[i]) {
                alert('ERROR: sessionless_sig8: invalid argument: ' + arguments[0]);
                pass = false;
            }
        }
        if (pass) {
            self_sls_count++;
        } else {
            sls_pass = false;
        }
    } else if (this.member == 'notif') {
        JSON.stringify(arguments);
    }
}

function sendSLS(iter)
{
    if (iter >= MAX_SIG_ITERATIONS) {
        print('PASS: sessionless_sig - count: ' + sls_count);
        sls_done = true;
        return;
    }
    AJ.signal('/org/alljoyn/unit_test1', {sessionless_sig1:'org.alljoyn.unit_test'}).send(args_object.sessionless_sig1);
    AJ.signal('/org/alljoyn/unit_test2', {sessionless_sig2:'org.alljoyn.unit_test'}).send(args_object.sessionless_sig2);
    AJ.signal('/org/alljoyn/unit_test3', {sessionless_sig3:'org.alljoyn.unit_test'}).send(args_object.sessionless_sig3);
    AJ.signal('/org/alljoyn/unit_test4', {sessionless_sig4:'org.alljoyn.unit_test'}).send(args_object.sessionless_sig4);
    AJ.signal('/org/alljoyn/unit_test5', {sessionless_sig5:'org.alljoyn.unit_test'}).send(args_object.sessionless_sig5);
    AJ.signal('/org/alljoyn/unit_test6', {sessionless_sig6:'org.alljoyn.unit_test'}).send(args_object.sessionless_sig6);
    AJ.signal('/org/alljoyn/unit_test7', {sessionless_sig7:'org.alljoyn.unit_test'}).send(args_object.sessionless_sig7);
    AJ.signal('/org/alljoyn/unit_test8', {sessionless_sig8:'org.alljoyn.unit_test'}).send(args_object.sessionless_sig8);
    sls_count++;
    sendSLS(iter + 1);
}

AJ.onAttach = function()
{
    AJ.addMatch('org.alljoyn.unit_test', 'sessionless_sig1');
    AJ.addMatch('org.alljoyn.unit_test', 'sessionless_sig2');
    AJ.addMatch('org.alljoyn.unit_test', 'sessionless_sig3');
    AJ.addMatch('org.alljoyn.unit_test', 'sessionless_sig4');
    AJ.addMatch('org.alljoyn.unit_test', 'sessionless_sig5');
    AJ.addMatch('org.alljoyn.unit_test', 'sessionless_sig6');
    AJ.addMatch('org.alljoyn.unit_test', 'sessionless_sig7');
    AJ.addMatch('org.alljoyn.unit_test', 'sessionless_sig8');
    print("Starting SLS test");
    sendSLS(0);
}

var store_obj = {
    int_val:100,
    str_val:"string",
    obj_val:{
        obj_int:10,
        obj_str:"obj_string"
    }
}

var store_int = 60;
var store_str = "simple_string";
    
print("===== Starting Unit Tests =====");
/*
 * Store/Load tests
 */
AJ.store('int_store', store_int);
AJ.store('str_store', store_str);
AJ.store('obj_store', store_obj);

var out_int = AJ.load('int_store');
if (out_int != store_int) {
    alert('Store/Load test error: integer value did not match');
    nvram_pass = false;
}
var out_str = AJ.load('str_store');
if (out_str != store_str) {
    alert('Store/Load test error: string value did not match');
    nvram_pass = false;
}
var out_obj = AJ.load('obj_store');
if (out_obj.int_val != store_obj.int_val) {
    alert('Store/Load test error: object.int_val value did not match');
    nvram_pass = false;
}
if (out_obj.str_val != store_obj.str_val) {
    alert('Store/Load test error: object.str_val value did not match');
    nvram_pass = false;
}
if (out_obj.obj_val.obj_int != store_obj.obj_val.obj_int) {
    alert('Store/Load test error: object.obj_val.obj_int value did not match');
    nvram_pass = false;
}
if (out_obj.obj_val.obj_str != store_obj.obj_val.obj_str) {
    alert('Store/Load test error: object.obj_val.obj_str value did not match');
    nvram_pass = false;
}

if (nvram_pass == false) {
    alert('ERROR: Store/Load test failed');
}

nvram_done = true;

/*
 * Time tests
 */
var counter = 0;

function checkCounter()
{
    if (counter > 5) {
        print("Error, setInterval was called too many times");
        counter_pass = false;
        count_done = true;
        return;
    }
    clearInterval(interval);
    print('PASS: Counter was correct');
    count_done = true;
}

function incCounter()
{
    counter++;
}
/*
 * Set a counter to increment every 100ms
 * Set a timeout for 500ms
 * if the counter is > 5 then timers don't work correctly.
 */
var interval = setInterval(incCounter, 100);
setTimeout(checkCounter, 500);

var done = setInterval(function() {
    if (count_done && nvram_done && sls_done) {
        if (counter_pass && nvram_pass && sls_pass) {
            print("*** UNIT TEST PASSED ***");
        } else {
            print("*** UNIT TEST FAILED ***");
        }
        clearInterval(done);
    }
}, 1000);

