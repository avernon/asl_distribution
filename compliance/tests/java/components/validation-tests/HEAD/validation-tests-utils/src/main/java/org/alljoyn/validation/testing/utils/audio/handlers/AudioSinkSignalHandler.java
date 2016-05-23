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
package org.alljoyn.validation.testing.utils.audio.handlers;

import java.util.concurrent.LinkedBlockingDeque;
import java.util.concurrent.TimeUnit;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.annotation.BusSignalHandler;
import org.alljoyn.validation.testing.utils.audio.AudioSinkPlayStateChangedSignal;
import org.alljoyn.validation.testing.utils.audio.AudioTransports.AudioSink;
import org.alljoyn.validation.testing.utils.audio.AudioTransports.AudioSinkDelay;
import org.alljoyn.validation.testing.utils.log.Logger;
import org.alljoyn.validation.testing.utils.log.LoggerFactory;

public class AudioSinkSignalHandler implements AudioSink, BusObject
{
    private static final String TAG = "AudioSinkSignalHandler";
    private static final Logger logger = LoggerFactory.getLogger(TAG);
    private LinkedBlockingDeque<AudioSinkPlayStateChangedSignal> playStateChangedSignalQueue = new LinkedBlockingDeque<AudioSinkPlayStateChangedSignal>();
    private LinkedBlockingDeque<Integer> fifoPositionChangedSignalQueue = new LinkedBlockingDeque<Integer>();

    @BusSignalHandler(iface = "org.alljoyn.Stream.Port.AudioSink", signal = "PlayStateChanged")
    public void handlePlayStateChangedSignal(byte oldState, byte newState)
    {
        logger.debug(String.format("PlayStateChanged signal received. Old state: %d New state: %d", oldState, newState));
        playStateChangedSignalQueue.add(new AudioSinkPlayStateChangedSignal(oldState, newState));
    }

    @BusSignalHandler(iface = "org.alljoyn.Stream.Port.AudioSink", signal = "FifoPositionChanged")
    public void handleFifoPositionChangedSignal()
    {
        logger.debug("FifoPositionChanged signal received");
        fifoPositionChangedSignalQueue.add(0);
    }

    public AudioSinkPlayStateChangedSignal waitForNextPlayStateChangedSignal(long timeout, TimeUnit unit) throws InterruptedException
    {
        logger.debug("Waiting for PlayStateChanged signal");

        return playStateChangedSignalQueue.poll(timeout, unit);
    }

    public Integer waitForNextFifoPositionChangedSignal(long timeout, TimeUnit unit) throws InterruptedException
    {
        logger.debug("Waiting for FifoPositionChanged signal");

        return fifoPositionChangedSignalQueue.poll(timeout, unit);
    }

    public void clearFifoPositionChangedSignalQueue()
    {
        fifoPositionChangedSignalQueue.clear();
    }

    @Override
    public short getVersion() throws BusException
    {
        return 0;
    }

    @Override
    public int getFifoSize() throws BusException
    {
        return 0;
    }

    @Override
    public int getFifoPosition() throws BusException
    {
        return 0;
    }

    @Override
    public AudioSinkDelay getDelay() throws BusException
    {
        return null;
    }

    @Override
    public void FifoPositionChanged() throws BusException
    {
    }

    @Override
    public void PlayStateChanged(byte oldState, byte newState) throws BusException
    {
    }

    @Override
    public void Play() throws BusException
    {
    }

    @Override
    public void Pause(long timeNanos) throws BusException
    {
    }

    @Override
    public int Flush(long timeNanos) throws BusException
    {
        return 0;
    }
}