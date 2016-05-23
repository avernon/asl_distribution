/******************************************************************************
 *
 *
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
#include <gtest/gtest.h>

#include <alljoyn/Init.h>

#include <qcc/Debug.h>

#include <string.h>

static void DebugOut(DbgMsgType type, const char* module, const char* msg, void* context)
{
    // Do nothing to suppress AJ errors and debug prints.
}

static bool IsDebugOn(char** env)
{
    while (env && *env) {
        if (strncmp(*env, "ER_DEBUG_", 9) == 0) {
            return true;
        }
        ++env;
    }
    return false;
}


/** Main entry point */
int main(int argc, char** argv, char** envArg)
{
    if (AllJoynInit() != ER_OK) {
        return 1;
    }
#ifdef ROUTER
    if (AllJoynRouterInit() != ER_OK) {
        AllJoynShutdown();
        return 1;
    }
#endif

    int status = 0;
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    if (!IsDebugOn(envArg)) {
        QCC_RegisterOutputCallback(DebugOut, NULL);
    }

    printf("\n Running alljoyn_core unit test\n");
    testing::InitGoogleTest(&argc, argv);
    status = RUN_ALL_TESTS();

    printf("%s exiting with status %d \n", argv[0], status);

#ifdef ROUTER
    AllJoynRouterShutdown();
#endif
    AllJoynShutdown();
    return (int) status;
}
