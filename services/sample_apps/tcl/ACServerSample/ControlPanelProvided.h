/******************************************************************************
 * Copyright (c) 2013 - 2014, AllSeen Alliance. All rights reserved.
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

#include "alljoyn.h"
#include "alljoyn/controlpanel/Common/DateTimeUtil.h"
#include "ControlPanelGenerated.h"

//#define UNICODE_HI_IN_HEBREW "\xd7\xa9\xd7\x9c\xd7\x95\xd7\x9d\x00"
//#define UNICODE_HI_IN_CHINESE "\xe5\x97\xa8"
//
//void addDismissSignal(ExecuteActionContext* context, int32_t dismissSignal);
//
//uint8_t getEnabledFunc();
//uint8_t getWriteableFunc();
//const char* getTestString(uint16_t language);
//const char* getUrlString();
//
//void* getDateProperty(PropertyWidget* thisWidget);
//void setDateProperty(DatePropertyValue* datePropertyValue);
//
//void* getTimeProperty(PropertyWidget* thisWidget);
//void setTimeProperty(TimePropertyValue* timePropertyValue);
//
//void* getuint16Var(PropertyWidget* thisWidget);
//void setuint16Var(uint16_t newuint16Var);
//
//void* getint16Var(PropertyWidget* thisWidget);
//void setint16Var(int16_t newint16Var);
//
//void* getuint32Var(PropertyWidget* thisWidget);
//void setuint32Var(uint32_t newuint32Var);
//
//void* getint32Var(PropertyWidget* thisWidget);
//void setint32Var(int32_t newint32Var);
//
//void* getuint64Var(PropertyWidget* thisWidget);
//void setuint64Var(uint64_t newuint64Var);
//
//void* getint64Var(PropertyWidget* thisWidget);
//void setint64Var(int64_t newint64Var);
//
//void* getdoubleVar(PropertyWidget* thisWidget);
//void setdoubleVar(double newdoubleVar);
//
//void* getStringVar(PropertyWidget* thisWidget);
//void setStringVar(const char* newStringVar);

//////////////////////////////////////////////////////

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

//void simulateTemperatureChange();
uint8_t checkForUpdatesToSend();

#endif /* CONTROLPANELPROVIDED_H_ */

