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

AJ.interfaceDefinition["org.alljoyn.marshal_test"] =
{
    test:{ type:AJ.METHOD, args:["av"], returns:["s"] },
    test2:{ type:AJ.METHOD, args:["av"], returns:["s"]},
	test3:{ type:AJ.METHOD, args:["(ii(ss))"], returns:["s"]},
	test4:{ type:AJ.METHOD, args:["ai"], returns:["s"]},
	test5:{ type:AJ.METHOD, args:["a{is}"], returns:["s"]},
	test6:{ type:AJ.METHOD, args:["a{is}"], returns:["s"]},
	test7:{ type:AJ.METHOD, args:["ay"], returns:["s"]},
	test8:{ type:AJ.SIGNAL}
};

AJ.objectDefinition['/marshal_test'] = {
    interfaces:['org.alljoyn.marshal_test']
};

AJ.onAttach = function()
{
    AJ.addMatch('org.alljoyn.marshal_test', 'test8');
    print("AJ.onAttach");
}

AJ.onDetach = function()
{
    print("AJ.onDetach");
}

AJ.onSignal = function()
{
	if (this.member == 'test8') {
		print("Signal Received " + arguments[0]);
	}
}

AJ.onMethodCall = function()
{
    if (this.member == 'test') {
        print(JSON.stringify(arguments[0]));
        this.reply("Test 1 Passed");
    } else if (this.member == 'test2') {
        print(JSON.stringify(arguments[0]));
        this.reply("Test 2 Passed");
	} else if (this.member == 'test3') {
		print(JSON.stringify(arguments[0]));
		this.reply("Test 3 Passed");
	} else if(this.member == 'test4') {
		print(JSON.stringify(arguments[0]));
		this.reply("Test 4 Passed");
	} else if(this.member == 'test5') {
		print(JSON.stringify(arguments[0]));
		this.reply("Test 5 Passed");
	} else if(this.member == 'test6') {
		print(JSON.stringify(arguments[0]));
		this.reply("Test 6 Passed");
	}else if(this.member == 'test7') {
		print(Duktape.enc("jx", arguments[0]));
		this.reply("Test 7 Passed");

    } else {
        throw('rejected');
    }
}

