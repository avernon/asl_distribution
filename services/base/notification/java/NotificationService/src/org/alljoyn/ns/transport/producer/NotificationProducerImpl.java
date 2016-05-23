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

package org.alljoyn.ns.transport.producer;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.Status;
import org.alljoyn.ns.NotificationServiceException;
import org.alljoyn.ns.commons.GenericLogger;
import org.alljoyn.ns.commons.NativePlatform;
import org.alljoyn.ns.transport.TaskManager;
import org.alljoyn.ns.transport.Transport;
import org.alljoyn.ns.transport.interfaces.NotificationProducer;

/**
 * The class implements the {@link NotificationProducer} interface and by this
 * realizes the Notification producer proprietary logic
 */
class NotificationProducerImpl implements NotificationProducer {
    private static final String TAG = "ioe" + NotificationProducerImpl.class.getSimpleName();

    /**
     * The Sender transport
     */
    private SenderTransport senderTransport;

    /**
     * The reference to the platform dependent object
     */
    private NativePlatform nativePlatform;

    /**
     * Constructor
     * 
     * @param senderTransport
     *            The Sender transport
     * @param nativePlatform
     *            The reference to the platform dependent object
     */
    public NotificationProducerImpl(SenderTransport senderTransport, NativePlatform nativePlatform) {
        this.senderTransport = senderTransport;
        this.nativePlatform = nativePlatform;
    }

    /**
     * Initializes the object <br>
     * Register {@link BusObject}, if failed to register the
     * {@link NotificationServiceException} is thrown
     * 
     * @throws NotificationServiceException
     */
    public void init() throws NotificationServiceException {
        Status status = Transport.getInstance().getBusAttachment().registerBusObject(this, OBJ_PATH);

        nativePlatform.getNativeLogger().debug(TAG, "NotificationProducer BusObject: '" + OBJ_PATH + "' was registered on the bus, Status: '" + status + "'");

        if (status != Status.OK) {
            throw new NotificationServiceException("Failed to register BusObject: '" + OBJ_PATH + "', Error: '" + status + "'");
        }
    }// init

    /**
     * @see org.alljoyn.ns.transport.interfaces.NotificationProducer#dismiss(int)
     */
    @Override
    public void dismiss(final int msgId) throws BusException {
        GenericLogger logger = nativePlatform.getNativeLogger();
        logger.debug(TAG, "Received Dismiss for notifId: '" + msgId + "', delegating to be executed");

        Transport.getInstance().getBusAttachment().enableConcurrentCallbacks();

        TaskManager.getInstance().enqueue(new Runnable() {
            @Override
            public void run() {
                senderTransport.dismiss(msgId);
            }
        });

    }// dismiss

    /**
     * @see org.alljoyn.ns.transport.interfaces.NotificationProducer#getVersion()
     */
    @Override
    public short getVersion() throws BusException {
        return VERSION;
    }// getVersion

    /**
     * Cleans the object resources
     */
    public void clean() {

        nativePlatform.getNativeLogger().debug(TAG, "Cleaning the NotificationProducerImpl");

        Transport.getInstance().getBusAttachment().unregisterBusObject(this);

        senderTransport = null;
        nativePlatform = null;
    }// clean
}
