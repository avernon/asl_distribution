/**
 * @file
 */
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
#define AJ_MODULE TEST_BASE64

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ajtcl/aj_debug.h>
#include <ajtcl/alljoyn.h>
#include <ajtcl/aj_util.h>

uint8_t dbgTEST_BASE64 = 0;

static int test(const char* input, const char* output)
{
    AJ_Status status;
    int inputlen;
    int outputlen;
    char encode[1024];
    char decode[1024];

    inputlen = strlen(input);
    outputlen = strlen(output);

    status = AJ_RawToB64((uint8_t*) input, inputlen, encode, sizeof (encode));
    if (AJ_OK != status) {
        AJ_AlwaysPrintf(("FAILED STATUS\n"));
        return 1;
    }
    if (0 != strncmp(output, encode, outputlen)) {
        AJ_AlwaysPrintf(("FAILED ENCODE\n"));
        return 1;
    }

    status = AJ_B64ToRaw(output, outputlen, (uint8_t*) decode, sizeof (decode));
    if (AJ_OK != status) {
        AJ_AlwaysPrintf(("FAILED STATUS\n"));
        return 1;
    }
    if (0 != strncmp(input, decode, inputlen)) {
        AJ_AlwaysPrintf(("FAILED DECODE\n"));
        return 1;
    }

    return 0;
}

int AJ_Main(void)
{
    /*
     * put your test cases here.
     */

    if (test("This is a test.", "VGhpcyBpcyBhIHRlc3Qu")) {
        AJ_AlwaysPrintf(("FAILED\n"));
    } else {
        AJ_AlwaysPrintf(("PASSED\n"));
    }

    return 0;
}

#ifdef AJ_MAIN
int main(void)
{
    return AJ_Main();
}
#endif
