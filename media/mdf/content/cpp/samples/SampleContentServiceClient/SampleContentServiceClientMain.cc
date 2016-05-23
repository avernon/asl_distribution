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


#include <signal.h>
#include "LogModule.h"

#include "SampleContentServiceClient.h"

static mdf::SampleContentServiceClient* sampleContentServiceClient = 0;


void cleanup()
{
    delete sampleContentServiceClient;
}

void signal_callback_handler(int32_t signum)
{
    cleanup();
    exit(signum);
}

int main(int argc, char* argv[])
{
    QCC_SetDebugLevel(mdf::CONTENT_SERVICE_LOG_NAME, mdf::ALL_LOG_LEVELS);
    QCC_DbgHLPrintf(("Starting the sample content service client"));
    // Allow CTRL+C to end application
    signal(SIGINT, signal_callback_handler);

    sampleContentServiceClient = new mdf::SampleContentServiceClient();
    QStatus status = sampleContentServiceClient->Init();
    if (status != ER_OK) {
        cleanup();
        return status;
    }

    QCC_DbgHLPrintf(("Completed sample content service client."));
    sampleContentServiceClient->RunExamples();

    int i = 0;
    while (i < 520) {
        sleep(1);
        i++;
    }
    cleanup();

    return 0;
}
