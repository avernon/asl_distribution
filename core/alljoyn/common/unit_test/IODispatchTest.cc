/******************************************************************************
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

#include <qcc/Condition.h>
#include <qcc/IODispatch.h>

using namespace qcc;

class IODispatchStopStreamTest : public testing::Test {
  public:
    class Listener : public IOReadListener, public IOWriteListener, public IOExitListener {
      public:
        Mutex mutex;
        Condition condition;
        bool exitCalled;
        bool returnFromExit;

        Listener() : exitCalled(false), returnFromExit(false) { }
        virtual ~Listener() { }
        virtual QStatus ReadCallback(Source&, bool) { return ER_OK; }
        virtual QStatus WriteCallback(Sink&, bool) { return ER_OK; }
        virtual void ExitCallback() {
            mutex.Lock();
            exitCalled = true;
            condition.Signal();
            mutex.Unlock();

            mutex.Lock();
            while (!returnFromExit) {
                condition.Wait(mutex);
            }
            mutex.Unlock();
        }
        void WaitForExitCallback() {
            mutex.Lock();
            while (!exitCalled) {
                condition.Wait(mutex);
            }
            mutex.Unlock();
        }
        void ReturnFromExitCallback() {
            mutex.Lock();
            returnFromExit = true;
            condition.Signal();
            mutex.Unlock();
        }
    };

    Stream s;
    Listener l;
    IODispatch io;

    IODispatchStopStreamTest() : io("IODispatchStopStreamTest", 4) { }
};

TEST_F(IODispatchStopStreamTest, WhenStreamIsNotStarted)
{
    EXPECT_EQ(ER_INVALID_STREAM, io.StopStream(&s));
}

TEST_F(IODispatchStopStreamTest, WhenExitCallbackIsRunningOrScheduled)
{
    EXPECT_EQ(ER_OK, io.Start());
    EXPECT_EQ(ER_OK, io.StartStream(&s, &l, &l, &l));
    EXPECT_EQ(ER_OK, io.StopStream(&s));
    l.WaitForExitCallback();

    EXPECT_EQ(ER_FAIL, io.StopStream(&s));
    l.ReturnFromExitCallback();
}

TEST_F(IODispatchStopStreamTest, WhenExitCallbackIsRunningOrScheduled_Stop)
{
    EXPECT_EQ(ER_OK, io.Start());
    EXPECT_EQ(ER_OK, io.StartStream(&s, &l, &l, &l));
    EXPECT_EQ(ER_OK, io.Stop());
    l.WaitForExitCallback();

    EXPECT_EQ(ER_FAIL, io.StopStream(&s));
    l.ReturnFromExitCallback();
}

TEST_F(IODispatchStopStreamTest, WhenStreamIsStarted)
{
    EXPECT_EQ(ER_OK, io.Start());
    EXPECT_EQ(ER_OK, io.StartStream(&s, &l, &l, &l));

    EXPECT_EQ(ER_OK, io.StopStream(&s));
    l.WaitForExitCallback();
    l.ReturnFromExitCallback();
}

TEST_F(IODispatchStopStreamTest, WhenStreamIsStarted_Stop)
{
    EXPECT_EQ(ER_OK, io.Start());
    EXPECT_EQ(ER_OK, io.StartStream(&s, &l, &l, &l));

    EXPECT_EQ(ER_OK, io.Stop()); /* This calls StopStream internally. */
    l.WaitForExitCallback();
    l.ReturnFromExitCallback();
}
