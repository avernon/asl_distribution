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

#include <qcc/platform.h>
#include <stdio.h>
#include <alljoyn/controlpanel/CPSDate.h>
#include <alljoyn/controlpanel/CPSTime.h>

void disableFan();
void enableFan();
void disableTempSelect();
void enableTempSelect();

const char* getNotificationString();
uint16_t isThereANotificationToSend();

uint16_t getCurrentTargetTemp();
void checkTargetTempReached();

void setTemperatureFieldUpdate();
void setStatusFieldUpdate();
void setTempSelectorFieldUpdate();
void setFanSpeedSelectorFieldUpdate();

char const* getCurrentTemperatureString();
void setCurrentTemperatureString(char const* newTemp);
char const* getCurrentHumidityString();
void setCurrentHumidityString(char const* newHumidity);

uint16_t getTargetTemperature();
void setTargetTemperature(uint16_t newTemp);

uint16_t getCurrentMode();
void setCurrentMode(uint16_t newMode);

uint16_t getFanSpeed();
void setFanSpeed(uint16_t newSpeed);

const char* getStatusString();
void setStatusString(const char* newStatusString);

uint8_t checkForUpdatesToSend();

void OnTurnFanOnButton(bool chooseYes);
void OnTurnFanOffButton(bool chooseYes);

bool getOfferToTurnOffTheFan();
void setOfferToTurnOffTheFan(bool turnOffTheFan);

bool getOfferToTurnOnTheFan();
void setOfferToTurnOnTheFan(bool turnOnTheFan);

uint8_t checkForEventsToSend();
void resetEventsToSend();
uint8_t getEventsToSend();

#endif /* CONTROLPANELPROVIDED_H_ */
