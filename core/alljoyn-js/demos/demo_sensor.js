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
//Include the IO library for HW access
var IO = require('IO');
//Include the AllJoyn.js library
var AJ = require('AllJoyn');
//Force the device name
AJ.store("DeviceName", "Sensor");
AJ.store("Manufacturer", "QCE");
AJ.store("DateOfManufacture", "2015-08-08");
AJ.store("Description", "Sensor board for AllJoyn.js demos");

//Create interface for remote interaction
AJ.interfaceDefinition['org.example.potentiometer'] =
{
    low:{ type:AJ.SIGNAL, description:'the dial is low' },
    high:{ type:AJ.SIGNAL, description:'the dial is high' }
};

//This interface is used for M2M use cases and isn't exposed by this application
//This is needed to make a BusMethod call on a remote service
//It is common practice to have a complete interface, but since we are just interaction with Properties, we can include just these members
AJ.interfaceDefinition['org.example.speaker'] =
{
    playbackDone: { type:AJ.SIGNAL, description: 'audio is done playing' },
    frequency: { type:AJ.PROPERTY, signature:'u'},
    play: { type:AJ.METHOD, description:'play audio out of the speaker' },
    alwaysPlaying: { type:AJ.PROPERTY, signature:'b'}
};
AJ.interfaceDefinition['org.example.simplelight'] =
{
    redDuty: { type:AJ.PROPERTY, signature:'u'},
    blink: { type:AJ.METHOD, description:'blink the led' }
};

//Add the interface to an object path (needed to interact with interface)
AJ.objectDefinition['/sensors'] = {
    interfaces:['org.example.potentiometer']
};

AJ.onSignal = function() {
    //When we receive the playbackDone signal then call play again
    if (remoteSpeakerService && this.member == 'playbackDone') {
        print("playback is done");
    }
}

//Variable to hold the remote service we find
var remoteSpeakerService;
var remoteSimpleLightService;

var playing = false;
var blinking= false;
//Setup our potentiometer
var potentiometer = IO.analogIn(IO.pin[38]);

//Set our light to be a pwm on GPIO 6,7 & 8
var redLed = IO.digitalOut(IO.pin[6]);
var greenLed = IO.digitalOut(IO.pin[7]);
//var blueLed = IO.digitalOut(IO.pin[8]);
redLed.level = 0;
greenLed.level = 0;
//blueLed.level = 0;

//Create a control panel
var cp = AJ.controlPanel();
//Specify the container that can hold vertical and horizontal containers/widgets
var c1 = cp.containerWidget(cp.VERTICAL, cp.HORIZONTAL);
//Create a button to call the remote play method
var callRemoteMethod = c1.actionWidget('Call Remote Method- Play');

var label = c1.labelWidget('Settings:');
//Create a switch to turn on/off AllJoyn Event sending
var eventToggle = c1.propertyWidget(cp.SWITCH, false, 'Send AllJoyn Events');
//Create a switch to turn on/off AllJoyn Notification sending
var notifToggle = c1.propertyWidget(cp.SWITCH, false, 'Send AllJoyn Notifications');

//Setup the Control panel widget callbacks
callRemoteMethod.onClick = function(val) { 
    var playSpkrMethod = remoteSpeakerService.method('play');
    playSpkrMethod.call();
}

function sendEvent(whatEvent) {
    var sig = AJ.signal('/sensors', whatEvent);
    //This makes it as a true Event so a session is not required
    sig.sessionless = true;
    sig.timeToLive = 60; //30 seconds
    sig.send(); 
    print("Event sent:" + JSON.stringify(whatEvent));
}

function sendNotification(notifMsg) {
    AJ.notification(AJ.notification.Info, notifMsg).send(30); //30 seconds
    print("Notif sent:"+notifMsg);
}

function potentiometerCheck() {
    var reading = potentiometer.value; //reading ranges from 37k to 47k so we normalize it down
    print("Potentiometer reading: "+reading);
    if (!blinking && reading < 38000) { //low
        if (eventToggle.value) { sendEvent({low:'org.example.potentiometer'}); }
        if (notifToggle.value) { sendNotification('Dial all the way down'); }
        if (remoteSimpleLightService) {     
            var blinkMethod = remoteSimpleLightService.method('blink');
            blinkMethod.call();
        }
        blinking = true;
        playing = false;
    } else if (!playing && reading > 47000) {
        if (eventToggle.value) { sendEvent({high:'org.example.potentiometer'}); }
        if (notifToggle.value) { sendNotification('Dial turned up'); }
        if (remoteSpeakerService) {
            var playSpkrMethod = remoteSpeakerService.method('play');
            playSpkrMethod.call();
        }
        //  greenLed.pwm(1, 100000);
        blinking = false;
        playing = true;

    } 
}

//When we have found an AllJoyn Router finalize the Control Panel
AJ.onAttach = function()
{
    greenLed.pwm(0.2, 100000);
    redLed.pwm(0, 100000);
    //Finalize the Control Panel
    cp.load();

    //Find simplelight service and save the object for later use
    AJ.findService('org.example.simplelight', function(svc) {
        print(JSON.stringify(svc));
        greenLed.pwm(0.5, 100000);
        remoteSimpleLightService = svc;
    });

    //Find speaker service, save the object and turn off the alwaysPlaying property
    AJ.findService('org.example.speaker', function(svc) {
        print(JSON.stringify(svc));
        remoteSpeakerService = svc;
        greenLed.pwm(0.8, 100000);
        remoteSpeakerService.setProp('alwaysPlaying', false).onReply = function(arg) {  };
    });

}

AJ.onDetach = function() {
    greenLed.pwm(0, 100000);
    redLed.pwm(0, 100000);
}

//The application logic to handle the different sensor input values
var applicationLogic = function main() {
    potentiometerCheck();
}

// turn on red LED upon startup (will turn green 
redLed.pwm(1, 100000);
setInterval(applicationLogic,500);//Run the application logic every .5 seconds



