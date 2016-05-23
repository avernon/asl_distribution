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

#define UNICODE_HI_IN_HEBREW "\xd7\xa9\xd7\x9c\xd7\x95\xd7\x9d\x00"
#define UNICODE_HI_IN_CHINESE "\xe5\x97\xa8"

void addDismissSignal(ExecuteActionContext* context, int32_t dismissSignal);

uint8_t getEnabledFunc();
uint8_t getWriteableFunc();
const char* getTestString(uint16_t language);
const char* getUrlString();

void* getDateProperty();
void setDateProperty(DatePropertyValue* datePropertyValue);

void* getTimeProperty();
void setTimeProperty(TimePropertyValue* timePropertyValue);

void* getuint16Var();
void setuint16Var(uint16_t newuint16Var);

void* getint16Var();
void setint16Var(int16_t newint16Var);

void* getuint32Var();
void setuint32Var(uint32_t newuint32Var);

void* getint32Var();
void setint32Var(int32_t newint32Var);

void* getuint64Var();
void setuint64Var(uint64_t newuint64Var);

void* getint64Var();
void setint64Var(int64_t newint64Var);

void* getdoubleVar();
void setdoubleVar(double newdoubleVar);

void* getStringVar();
void setStringVar(const char* newStringVar);

/* For Consistency with C++ code */
#define getboolVar getuint32Var
#define setboolVar setuint32Var

void startOven();
void stopOven();

void* getTemperature();
void setTemperature(uint16_t temperature);

void* getProgram();
void setProgram(uint16_t program);
const char* getProgramString(uint16_t language);
#endif /* CONTROLPANELPROVIDED_H_ */

