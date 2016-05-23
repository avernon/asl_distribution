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

import static junit.framework.Assert.assertEquals;

import java.util.concurrent.CountDownLatch;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.annotation.BusSignalHandler;
import org.alljoyn.validation.testing.utils.audio.AudioTransports.Configuration;
import org.alljoyn.validation.testing.utils.audio.AudioTransports.Port;
import org.alljoyn.validation.testing.utils.log.Logger;
import org.alljoyn.validation.testing.utils.log.LoggerFactory;

public class OwnershipLostSignalHandler implements Port, BusObject
{
    private static final String TAG = "OwnershipLostHandler";
    private static final Logger logger = LoggerFactory.getLogger(TAG);
    private CountDownLatch countDownLatch;
    private String expectedNewOwner;

    public OwnershipLostSignalHandler(CountDownLatch countDownLatch)
    {
        this.countDownLatch = countDownLatch;
    }

    @BusSignalHandler(iface = "org.alljoyn.Stream.Port", signal = "OwnershipLost")
    public void handleOwnershipLostSignal(String newOwner)
    {
        logger.debug("New owner: " + newOwner);
        assertEquals("New owner name does not match", expectedNewOwner, newOwner);
        countDownLatch.countDown();
    }

    public void setExpectedNewOwner(String expectedNewOwner)
    {
        this.expectedNewOwner = expectedNewOwner;
    }

    public CountDownLatch getCountDownLatch()
    {
        return countDownLatch;
    }

    @Override
    public short getVersion() throws BusException
    {
        return 1;
    }

    @Override
    public byte getDirection() throws BusException
    {
        return 0;
    }

    @Override
    public Configuration[] getCapabilities() throws BusException
    {
        return null;
    }

    @Override
    public void OwnershipLost(String newOwner) throws BusException
    {
    }

    @Override
    public void Connect(String host, String objectPath, Configuration configuration)
    {
    }
}