/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#include "ControlPanelProvided.h"
#include <qcc/String.h>
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream
#include <stdlib.h>     // atoi

static uint16_t currentMessage = 1;
static uint32_t counterValue = 1;
static qcc::String counterBuffer = "1";

uint16_t getCurrentMessage() {
    return currentMessage;
}

void setCurrentMessage(uint16_t newMessage)
{
    currentMessage = newMessage;
}

void printCurrentMessage() {
	const char* message;
	switch (currentMessage) {
	case 1:
		message = "Message One";
		break;
	case 2:
		message = "Message Two";
		break;
	case 3:
		message = "Message Three";
		break;
	default:
		message = "Invalid message value";
		break;
	}
	std::cout << "\n ### printCurrentMessage:  " << message << "\n" << std::endl;
}

char const* getCounterValueString()
{
    std::stringstream sMessageId;
    sMessageId << counterValue;
    counterBuffer = sMessageId.str().c_str();
    return counterBuffer.c_str();
}

void setCounterValueString(char const* newCounterValue)
{
	counterValue = (uint32_t) atoi(newCounterValue);
}
