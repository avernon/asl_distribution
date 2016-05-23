/*******************************************************************************
 *  Copyright AllSeen Alliance. All rights reserved.
 *
 *     Contributed by Qualcomm Connected Experiences, Inc.,
 *     with authorization from the AllSeen Alliance, Inc.
 *     
 *     Licensed under the Apache License, Version 2.0 (the "License");
 *     you may not use this file except in compliance with the License.
 *     You may obtain a copy of the License at
 *     
 *         http://www.apache.org/licenses/LICENSE-2.0
 *     
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 *     
 *     Pursuant to Section 1 of the License, the work of authorship constituting
 *     a Work and any Contribution incorporated in the Work shall mean only that
 *     Contributor's code submissions authored by that Contributor.  Any rights
 *     granted under the License are conditioned upon acceptance of these
 *     clarifications.
 *******************************************************************************/
package org.alljoyn.validation.testing.utils.audio;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;

import java.util.concurrent.TimeUnit;

import org.alljoyn.validation.testing.utils.MyRobolectricTestRunner;
import org.alljoyn.validation.testing.utils.audio.handlers.AudioSinkSignalHandler;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.annotation.Config;

@RunWith(MyRobolectricTestRunner.class)
@Config(manifest = Config.NONE)
public class AudioSinkSignalHandlerTest
{
    private AudioSinkSignalHandler audioSinkSignalHandler;

    @Before
    public void setup()
    {
        audioSinkSignalHandler = new AudioSinkSignalHandler();
    }

    @Test
    public void handlePlayStateChangedSignalTest() throws InterruptedException
    {
        assertNull(audioSinkSignalHandler.waitForNextPlayStateChangedSignal(1, TimeUnit.MILLISECONDS));
        audioSinkSignalHandler.handlePlayStateChangedSignal((byte) 0, (byte) 1);
        AudioSinkPlayStateChangedSignal audioSinkPlayStateChangedSignal = audioSinkSignalHandler.waitForNextPlayStateChangedSignal(1, TimeUnit.SECONDS);
        assertEquals((byte) 0, audioSinkPlayStateChangedSignal.getOldState());
        assertEquals((byte) 1, audioSinkPlayStateChangedSignal.getNewState());
    }

    @Test
    public void handleFifoPositionChangedSignalTest() throws InterruptedException
    {
        assertNull(audioSinkSignalHandler.waitForNextFifoPositionChangedSignal(1, TimeUnit.MILLISECONDS));
        audioSinkSignalHandler.handleFifoPositionChangedSignal();
        assertNotNull(audioSinkSignalHandler.waitForNextFifoPositionChangedSignal(1, TimeUnit.SECONDS));
    }

    @Test
    public void clearFifoPositionChangedSignalQueueTest() throws InterruptedException
    {
        audioSinkSignalHandler.handleFifoPositionChangedSignal();
        audioSinkSignalHandler.clearFifoPositionChangedSignalQueue();
        assertNull(audioSinkSignalHandler.waitForNextFifoPositionChangedSignal(1, TimeUnit.MILLISECONDS));
    }
}