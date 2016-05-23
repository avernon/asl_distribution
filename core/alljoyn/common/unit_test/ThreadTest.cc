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
#include <gtest/gtest.h>

#include <qcc/Thread.h>

using namespace std;
using namespace qcc;

#if defined(QCC_OS_GROUP_POSIX)
static void* ExternalThread(void*) {
#elif defined(QCC_OS_GROUP_WINDOWS)
static unsigned __stdcall ExternalThread(void*) {
#endif
    Thread* thread = Thread::GetThread();
    QCC_UNUSED(thread);
    return NULL;
}

/*
 * Test this with valgrind to see that no memory leaks occur with
 * external thread objects.
 */
TEST(ThreadTest, CleanExternalThread) {
#if defined(QCC_OS_GROUP_POSIX)
    pthread_t tid;
    ASSERT_EQ(0, pthread_create(&tid, NULL, ExternalThread, NULL));
    ASSERT_EQ(0, pthread_join(tid, NULL));
#elif defined(QCC_OS_GROUP_WINDOWS)
    uintptr_t handle = _beginthreadex(NULL, 0, ExternalThread, NULL, 0, NULL);
    ASSERT_NE(0, handle);
    ASSERT_EQ(WAIT_OBJECT_0, WaitForSingleObject(reinterpret_cast<HANDLE>(handle), INFINITE));
    ASSERT_NE(0, CloseHandle(reinterpret_cast<HANDLE>(handle)));
#endif
}
