/******************************************************************************
 * Copyright (c) 2013, AllSeen Alliance. All rights reserved.
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

static bool boolVar = false;

static uint16_t uint16Var = 0;
static int16_t int16Var = 0;

static uint32_t uint32Var = 0;
static int32_t int32Var = 0;

static uint64_t uint64Var = 0;
static int64_t int64Var = 0;

static double doubleVar = 0;

static qcc::String StringVar = "Initial String";

static qcc::String sampleString = "This is a test";
static qcc::String sampleUrlString = ""; //put your url here

static ajn::services::CPSDate dateVar(13, 6, 2006);
static ajn::services::CPSTime timeVar(18, 30, 25);

bool getboolVar()
{
    return boolVar;
}

void setboolVar(bool value)
{
    boolVar = value;
}

double getdoubleVar()
{
    return doubleVar;
}

void setdoubleVar(double value)
{
    doubleVar = value;
}

const char* getStringVar()
{
    return StringVar.c_str();
}

void setStringVar(const char* value)
{
    StringVar = value;
}

uint16_t getuint16Var()
{
    return uint16Var;
}

void setuint16Var(uint16_t value)
{
    uint16Var = value;
}

int16_t getint16Var()
{
    return int16Var;
}

void setint16Var(int16_t value)
{
    int16Var = value;
}

uint32_t getuint32Var()
{
    return uint32Var;
}

void setuint32Var(uint32_t value)
{
    uint32Var = value;
}

int32_t getint32Var()
{
    return int32Var;
}

void setint32Var(int32_t value)
{
    int32Var = value;
}

uint64_t getuint64Var()
{
    return uint64Var;
}

void setuint64Var(uint64_t value)
{
    uint64Var = value;
}

int64_t getint64Var()
{
    return int64Var;
}

void setint64Var(int64_t value)
{
    int64Var = value;
}

bool getEnabledFunc()
{
    return true;
}

bool getWriteableFunc()
{
    return true;
}

const char* getTestString(uint16_t language)
{
    return sampleString.c_str();
}

const char* getUrlString()
{
    return sampleUrlString.c_str();
}

const ajn::services::CPSDate& getDateProperty()
{
    return dateVar;
}

void setDateProperty(const ajn::services::CPSDate& datePropertyValue)
{
    dateVar.setDay(datePropertyValue.getDay());
    dateVar.setMonth(datePropertyValue.getMonth());
    dateVar.setYear(datePropertyValue.getYear());
}

const ajn::services::CPSTime& getTimeProperty()
{
    return timeVar;
}

void setTimeProperty(const ajn::services::CPSTime& timePropertyValue)
{
    timeVar.setHour(timePropertyValue.getHour());
    timeVar.setMinute(timePropertyValue.getMinute());
    timeVar.setSecond(timePropertyValue.getSecond());
}

/**
 * Functions for Oven.xml
 */
static uint16_t temperatureVar = 0;
static uint16_t programVar = 0;
static qcc::String programString = "Program: ";

void startOven()
{
    printf("********* Starting the Oven *********\n");
}

void stopOven()
{
    printf("********* Stopping the Oven *********\n");
}

uint16_t getTemperature()
{
    return temperatureVar;
}

void setTemperature(uint16_t temperature)
{
    temperatureVar = temperature;
}

uint16_t getProgram()
{
    return programVar;
}

void setProgram(uint16_t program)
{
    programVar = program;
}

const char* getProgramString(uint16_t language)
{
    return programString.c_str();
}

