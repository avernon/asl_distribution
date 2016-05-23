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

/*
 * This file demonstrates how to use the control panel
 * Every kind of widget is demonstrated here
 */

/*
 * Create the control panel object
 */
var cp = AJ.controlPanel();

/*
 * Create a container to hold all the widgets below
 */
var c1 = cp.containerWidget(cp.VERTICAL, cp.HORIZONTAL);

/*
 * Create an action widget. This is a button that will change depending
 * on the action of other widgets
 */
var click_action = c1.actionWidget("Last action");

/*
 * This is a dialog widget. It will pop up when the action widget is pressed
 * You can add multiple buttons which can have different actions
 */
var dw = click_action.dialogWidget("Back", "Back");
dw.buttons = [
   { label:"ok", onClick: function() {click_action.label = "Last action"; } }
];

var text_label = c1.propertyWidget(cp.TEXT_VIEW, "Last command:");
text_label.value = "N/A";

function changeVal(widget, val) {
   dw.label = widget + ": " + val + " was clicked";
   click_action.label = widget + ": " + val;
   click_action.enable = true;
   text_label.value = widget + ": " + val;
}

/* Switch */
var sw = c1.propertyWidget(cp.SWITCH, true, "Switch:");
sw.onValueChanged = function (val) {
   changeVal("Switch", val);
}

/* 
 * Check box. This is currently not implemented in the service code
 * and will not get rendered by AllJoyn On 
 */
var check_box = c1.propertyWidget(cp.CHECK_BOX, 0, "Check box:");
check_box.onValueChanged = function (val) {
   changeVal("Check box", val);
}

/* Radio button */
var p1 = c1.propertyWidget(cp.RADIO_BUTTON, 0, "Radio:");
p1.choices = ["zero", "one", "two"];
p1.onValueChanged = function (val) {
    changeVal("Radio", val);
};

/* Spinner */
var spinner = c1.propertyWidget(cp.SPINNER, 0, "Spinner:");
spinner.choices = ["zero", "one", "two", "three", "four"];
spinner.onValueChanged = function (val) {
   changeVal("Spinner", val);
}

/* Time picker */
var time = c1.propertyWidget(cp.TIME_PICKER);
time.label = "Time Picker:";
time.onValueChanged = function (val) {
   dw.label = "Time picker: \nHour: " + val.hour + "\nMin: " + val.minute + "\nSec: " + val.second;
   click_action.label = "Time picker: \nHour: " + val.hour + "\nMin: " + val.minute + "\nSec: " + val.second;
   click_action.enable = true;
   text_label.value = "Time: " + val.hour + ":" + val.minute + ":" + val.second;
}

/* Date picker */
var date = c1.propertyWidget(cp.DATE_PICKER);
date.label = "Date Picker:";
date.onValueChanged = function (val) {
   dw.label = "Date picker: \nDay: " + val.day + "\nMonth: " + val.month + "\nYear: " + val.year;
   click_action.label = "Date picker: \nDay: " + val.day + "\nMonth: " + val.month + "\nYear: " + val.year;
   click_action.enable = true;
   text_label.value = "Date: " + val.day + ":" + val.month + ":" + val.year;
}

/* 
 * Number picker. This is currently not implemented in the service code
 * and will not get rendered by AllJoyn On 
 */
var number_picker = c1.propertyWidget(cp.NUMBER_PICKER);
number_picker.label = "Number Picker:";
number_picker.onValueChanged = function (val) {
   changeVal("Number Picker", val);
}

/* Keypad */
var keypad = c1.propertyWidget(cp.KEYPAD, 0, "Keypad");
keypad.onValueChanged = function (val) {
   changeVal("Keypad", val);
}

/* 
 * Knob. This is currently not implemented in the service code
 * and will not get rendered by AllJoyn On 
 */
var knob = c1.propertyWidget(cp.ROTARY_KNOB, 30, "Knob");
knob.range = {min:0, max:100, increment:1};
knob.onValueChanged = function (val) {
   changeVal("Knob", val);
}

/* Edit text */
var edit_text = c1.propertyWidget(cp.EDIT_TEXT, "", "Edit text");
edit_text.onValueChanged = function (val) {
   changeVal("Edit text", val);
}

/* Slider */
var slider = c1.propertyWidget(cp.SLIDER, 0, "Slider");
slider.range = {min:0, max:100, increment:1};
slider.onValueChanged = function (val) {
   changeVal("Slider", val);
}

/*
 * Load the control panel and render all the above widgets
 */
cp.load();
