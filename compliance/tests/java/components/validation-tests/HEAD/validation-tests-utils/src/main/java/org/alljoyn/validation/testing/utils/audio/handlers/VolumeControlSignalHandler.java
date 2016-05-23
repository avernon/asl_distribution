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
import org.alljoyn.validation.testing.utils.audio.AudioTransports.Volume;
import org.alljoyn.validation.testing.utils.audio.AudioTransports.VolumeRange;
import org.alljoyn.validation.testing.utils.log.Logger;
import org.alljoyn.validation.testing.utils.log.LoggerFactory;

public class VolumeControlSignalHandler implements Volume, BusObject
{
    private static final String TAG = "VolControlSignalHandler";
    private static final Logger logger = LoggerFactory.getLogger(TAG);
    private LinkedBlockingDeque<Boolean> muteChangedSignalQueue = new LinkedBlockingDeque<Boolean>();
    private LinkedBlockingDeque<Boolean> enabledChangedSignalQueue = new LinkedBlockingDeque<Boolean>();
    private LinkedBlockingDeque<Short> volumeChangedSignalQueue = new LinkedBlockingDeque<Short>();

    @Override
    @BusSignalHandler(iface = "org.alljoyn.Control.Volume", signal = "MuteChanged")
    public void MuteChanged(boolean newMute) throws BusException
    {
        logger.debug("MuteChanged signal received: " + newMute);
        muteChangedSignalQueue.add(newMute);
    }

    @Override
    @BusSignalHandler(iface = "org.alljoyn.Control.Volume", signal = "VolumeChanged")
    public void VolumeChanged(short newVolume) throws BusException
    {
        logger.debug("VolumeChanged signal received: " + newVolume);
        volumeChangedSignalQueue.add(newVolume);
    }

    @Override
    @BusSignalHandler(iface = "org.alljoyn.Control.Volume", signal = "EnabledChanged")
    public void EnabledChanged(boolean newEnabled) throws BusException
    {
        logger.debug("EnabledChanged signal received: " + newEnabled);
        muteChangedSignalQueue.add(newEnabled);
    }

    public Boolean waitForNextEnabledChangedSignal(long timeout, TimeUnit unit) throws InterruptedException
    {
        logger.debug("Waiting for EnabledChanged signal");

        return enabledChangedSignalQueue.poll(timeout, unit);
    }

    public Boolean waitForNextMuteChangedSignal(long timeout, TimeUnit unit) throws InterruptedException
    {
        logger.debug("Waiting for MuteChanged signal");

        return muteChangedSignalQueue.poll(timeout, unit);
    }

    public Short waitForNextVolumeChangedSignal(long timeout, TimeUnit unit) throws InterruptedException
    {
        logger.debug("Waiting for VolumeChanged signal");

        return volumeChangedSignalQueue.poll(timeout, unit);
    }

    @Override
    public short getVersion() throws BusException
    {
        return 0;
    }

    @Override
    public boolean getMute() throws BusException
    {
        return false;
    }

    @Override
    public void setMute(boolean isMuted) throws BusException
    {
    }

    @Override
    public short getVolume() throws BusException
    {
        return 0;
    }

    @Override
    public void setVolume(short level) throws BusException
    {
    }

    @Override
    public VolumeRange getVolumeRange() throws BusException
    {
        return null;
    }

    @Override
    public boolean getEnabled() throws BusException
    {
        return false;
    }

    @Override
    public void setEnabled(boolean isMuted) throws BusException
    {
    }

    @Override
    public void AdjustVolume(short delta) throws BusException
    {
    }

    @Override
    public void AdjustVolumePercent(double change) throws BusException
    {
    }
}

