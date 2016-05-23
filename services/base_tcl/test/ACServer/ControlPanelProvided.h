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

#ifndef CONTROLPANELPROVIDED_H_
#define CONTROLPANELPROVIDED_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/services/Common/DateTimeUtil.h>
#include "ControlPanelGenerated.h"

//////////////////////////////////////////////////////

void disableFan();
void enableFan();
void disableTempSelect();
void enableTempSelect();

const char* getNotificationString();
const char* getNotificationActionObjPath();
uint16_t isThereANotificationToSend();

uint16_t getCurrentTargetTemp();

void checkTargetTempReached();

void setTemperatureFieldUpdate();
void setStatusFieldUpdate();
void setTempSelectorFieldUpdate();
void setFanSpeedSelectorFieldUpdate();

//char const* getCurrentTemperatureString(uint16_t lang);
//char const* getCurrentHumidityString(uint16_t lang);

void* getCurrentTemperatureString(PropertyWidget* thisWidget);
void setCurrentTemperatureString(char const* newTemp);
void* getCurrentHumidityString(PropertyWidget* thisWidget);
void setCurrentHumidityString(char const* newHumidity);

void* getTargetTemperature(PropertyWidget* thisWidget);
void setTargetTemperature(uint16_t newTemp);

void* getCurrentMode(PropertyWidget* thisWidget);
void setCurrentMode(uint16_t newMode);

void* getFanSpeed(PropertyWidget* thisWidget);
void setFanSpeed(uint16_t newSpeed);

void* getStatusString(PropertyWidget* thisWidget);
void setStatusString(const char* newStatusString);

void onTurnFanOn(ExecuteActionContext* context, uint8_t accepted);
void onTurnFanOff(ExecuteActionContext* context, uint8_t accepted);

//void simulateTemperatureChange();
uint8_t checkForUpdatesToSend();
uint8_t checkForEventsToSend();

#endif /* CONTROLPANELPROVIDED_H_ */

