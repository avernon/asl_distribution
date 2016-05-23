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
var testname = "Test bbclient launch"

var target = UIATarget.localTarget();
var app = target.frontMostApp();
var window = app.mainWindow();
var wkName = "gov.t";
var inputTxt = window.textFields()[0];
var startBtn = window.buttons()[0];

var discovered = "Discovered advertised name";
var joined = "Successfully joined session";
var received = "Received ping string [Ping String 1]";

UIALogger.logStart(testname);

inputTxt.setValue(wkName);
target.delay(1);
startBtn.tap();

// TCP and udp discovery + join may take 60 seconds
target.delay(60);

var outputTxt = window.textViews()[0].value();

//Make sure discovery, joinSession and ping successful

if (outputTxt.indexOf(discovered) == -1)
{
   UIALogger.logFail("Discovery fail!");
}
else if (outputTxt.indexOf(joined) == -1)
{
   UIALogger.logFail("JoinSession fail!");
}
else if (outputTxt.indexOf(received) == -1)
{
   UIALogger.logFail("Received ping string fail!");
}
else
{   
   UIALogger.logPass("Client completed OK");
}
