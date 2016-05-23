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
var testname = "Test bbservice launch"

var target = UIATarget.localTarget();
var app = target.frontMostApp();
var window = app.mainWindow();
var wkName = "gov.s";
var inputTxt = window.textFields()[0];
var startBtn = window.buttons()[0];

var registered = "Bus object registered successfully";
var connected = "Bus connected successfully";
var requested = "Request for service name succeeded";
var binded = "Session to port binding successfully";

UIALogger.logStart(testname);

inputTxt.setValue(wkName);
target.delay(2);
startBtn.tap();

// android tcp or udp client discover + join at most takes 60 seconds 
target.delay(60);

var outputTxt = window.textViews()[0].value();

//Make sure register, connect, request, advertise, bind successful

if (outputTxt.indexOf(registered) == -1)
{
   UIALogger.logFail("Bus object register fail!");
}
else if (outputTxt.indexOf(connected) == -1)
{
   UIALogger.logFail("Bus connect fail!" + outputTxt);
}
else if (outputTxt.indexOf(requested) == -1)
{
   UIALogger.logFail("Request for service name fail!");
}
else if (outputTxt.indexOf(binded) == -1)
{
   UIALogger.logFail("Session to port binding fail!");
}
else
{   
   UIALogger.logPass("Service started OK");
}
