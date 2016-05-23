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
package org.alljoyn.validation.testing.utils.bus;

import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.SessionOpts;
import org.alljoyn.bus.Status;
import org.alljoyn.bus.alljoyn.DaemonInit;
import org.alljoyn.validation.testing.utils.AllJoynLibraryLoader;
import org.alljoyn.validation.testing.utils.log.Logger;
import org.alljoyn.validation.testing.utils.log.LoggerFactory;

import android.content.Context;

public class BusAttachmentMgr
{
    private BusAttachment busAttachment;
    private static final String TAG = BusAttachmentMgr.class.getSimpleName();
    private static final Logger logger = LoggerFactory.getLogger(TAG);
    private String daemonName;
    private String advertisedName;
    private static boolean initialized = false;

    public static synchronized void init(Context context)
    {
        if (!initialized)
        {
            AllJoynLibraryLoader.loadLibrary();

            DaemonInit.PrepareDaemon(context);
            initialized = true;
        }
    }

    public void create(String busApplicationName, BusAttachment.RemoteMessage policy) throws BusException
    {
        logger.debug("Creating BusAttachment");
        busAttachment = createBusAttachment(busApplicationName, policy);
    }

    public void connect() throws BusException
    {
        logger.debug("Connecting BusAttachment");
        Status status = busAttachment.connect();

        if (status != Status.OK)
        {
            String message = "Unable to connect busAttachment: " + status;
            logger.error(message);
            throw new BusException(message);
        }
    }

    public void advertise() throws BusException
    {
        daemonName = "org.alljoyn.BusNode_" + busAttachment.getGlobalGUIDString();
        Status status = busAttachment.requestName(daemonName, BusAttachment.ALLJOYN_REQUESTNAME_FLAG_DO_NOT_QUEUE);

        if (status != Status.OK)
        {
            String message = "Failed to requestName '" + daemonName + "': " + status;
            daemonName = null;
            logger.error(message);
            throw new BusException(message);
        }

        advertisedName = "quiet@" + daemonName;
        status = busAttachment.advertiseName(advertisedName, SessionOpts.TRANSPORT_WLAN);

        if (status != Status.OK)
        {
            advertisedName = null;
            String message = "Failed to advertiseName: " + daemonName;
            logger.error(message);
            throw new BusException(message);
        }
    }

    public void release()
    {
        if (advertisedName != null)
        {
            Status status = busAttachment.cancelAdvertiseName(advertisedName, SessionOpts.TRANSPORT_WLAN);
            if (status != Status.OK)
            {
                logger.warn(String.format("cancelAdvertiseName returned: %s", status));
            }
            advertisedName = null;
        }

        if (daemonName != null)
        {
            Status status = busAttachment.releaseName(daemonName);
            if (status != Status.OK)
            {
                logger.warn(String.format("releaseName returned: %s", status));
            }
            daemonName = null;
        }

        if (busAttachment != null)
        {
            logger.debug("Disconnecting busAttachment");
            busAttachment.clearKeyStore();
            busAttachment.disconnect();
            busAttachment.release();
            busAttachment = null;
        }
    }

    protected BusAttachment createBusAttachment(String applicationName, BusAttachment.RemoteMessage policy)
    {
        return new BusAttachment(applicationName, policy);
    }

    public BusAttachment getBusAttachment()
    {
        return busAttachment;
    }

    public void registerSignalHandler(Object signalHandler) throws BusException
    {
        Status status = busAttachment.registerSignalHandlers(signalHandler);

        if (status != Status.OK)
        {
            String message = String.format("Signal handler %s registration failed with status %s", signalHandler.getClass().getName(), status);
            logger.error(message);
            throw new BusException(message);
        }
    }

    public void registerBusObject(BusObject busObject, String objectPath) throws BusException
    {
        Status status = busAttachment.registerBusObject(busObject, objectPath);

        if (status != Status.OK)
        {
            String message = String.format("Failed to register object: %s", status);
            logger.error(message);
            throw new BusException(message);
        }
    }

    public String getBusUniqueName()
    {
        return busAttachment.getUniqueName();
    }
}