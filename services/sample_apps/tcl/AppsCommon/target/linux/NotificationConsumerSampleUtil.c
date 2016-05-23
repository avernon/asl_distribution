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

#include <aj_target.h>
#include <aj_status.h>
#include <stdlib.h>
#include <alljoyn/notification/NotificationConsumer.h>
#include <NotificationConsumerSampleUtil.h>

#define BUF_SIZE 500

static uint8_t GetCmdLine(char* buf, size_t num)
{
    while (AJ_GetCmdLine(buf, num) == NULL) {
    }
    return (strlen(buf) > 0);
}

/**
 * A function that allows us to enter QA InputMode
 */
void Consumer_SetupEnv(uint8_t* inputMode, uint8_t* superAgentMode)
{
    char* value = getenv("INPUT_MODE");
    char buf[BUF_SIZE];
    uint8_t defaultSuperAgentMode = *superAgentMode;

    if (value) {
        *inputMode = (uint8_t)atoi(value);
    }
    if (*inputMode) {
        AJ_StartReadFromStdIn();
        AJ_Printf("Please enter 0=OFF or 1=ON to disable/enable SuperAgentMode. Default is %u\n", defaultSuperAgentMode);
        if (GetCmdLine(buf, BUF_SIZE)) {
            *superAgentMode = (uint8_t)atoi(buf);
            if (1 < *superAgentMode) {
                *superAgentMode = defaultSuperAgentMode;
            }
        }
        AJ_StopReadFromStdIn();
    }
}

void Consumer_GetActionFromUser(uint8_t* action)
{
    char buf[BUF_SIZE];
    uint8_t defaultAction = *action;
    AJ_StartReadFromStdIn();
    AJ_Printf("Please enter an action to perform on the recently received notification\n\t0=Nothing,\n\t1=Dismiss.\n");
    AJ_Printf("Empty string or invalid input will default to %u\n", defaultAction);
    if (GetCmdLine(buf, BUF_SIZE)) {
        *action = (uint8_t)atoi(buf);
        char stringType[10];
        sprintf(stringType, "%u", *action);
        if (!(strcmp(buf, stringType) == 0)) {             //they do not match, it is not int
            AJ_Printf("Action is not an integer value. Defaulting to %u\n", defaultAction);
            *action = defaultAction;
        }
    }
    AJ_StopReadFromStdIn();
}
