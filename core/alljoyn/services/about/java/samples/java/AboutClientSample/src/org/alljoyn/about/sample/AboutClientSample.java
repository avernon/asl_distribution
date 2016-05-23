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

package org.alljoyn.about.sample;

import org.alljoyn.about.AboutService;
import org.alljoyn.about.AboutServiceImpl;
import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.Status;

public class AboutClientSample
{
    static
    {
        System.loadLibrary("alljoyn_java");
    }

    static BusAttachment mBus;
    private static AboutService aboutService;
    private static DeviceAnnouncementHandler announcementHandler;

    public static void main(String[] args)
    {
        Status status;
        System.out.println("starting.....");
        Runtime.getRuntime().addShutdownHook(new Thread()
        {
            public void run()
            {
                mBus.release();
            }
        });

        mBus = new BusAttachment("AppName", BusAttachment.RemoteMessage.Receive);
        System.out.println("created bus attachment");

        status = mBus.connect();
        if (status != Status.OK)
        {
            System.out.println(status.name());
            System.exit(0);
            return;
        }
        // uncomment these lines to see additional debug output
        //mBus.setDaemonDebug("ALL", 7);
        //mBus.setLogLevels("ALL=7");
        //mBus.useOSLogging(true);

        try
        {
            aboutService = AboutServiceImpl.getInstance();
            System.out.println("starting about service in client mode");
            aboutService.setLogger(new SampleLogger());
            aboutService.startAboutClient(mBus);
            System.out.println("started about service in client mode");
            announcementHandler = new DeviceAnnouncementHandler(mBus);
            String[] interfaces = new String[] { "org.alljoyn.Icon", "org.alljoyn.About" };
            aboutService.addAnnouncementHandler(announcementHandler, interfaces);
            System.out.println("added announcement handler");

            System.out.println("waiting for announcement");
            Thread.sleep(120000);

            shutdownAboutService();
            System.out.println("Disconnecting busAttachment");
            mBus.disconnect();
            mBus.release();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    private static void shutdownAboutService()
    {
        if (aboutService != null)
        {
            try
            {
                System.out.format("aboutClient running: %s\n", aboutService.isClientRunning());
                System.out.println("Stopping aboutClient");
                String[] interfaces = new String[] { "org.alljoyn.Icon", "org.alljoyn.About" };
                aboutService.removeAnnouncementHandler(announcementHandler, interfaces);
                aboutService.stopAboutClient();
            }
            catch (Exception e)
            {
                System.out.format("Exception calling stopAboutClient() %s\n", e.getMessage());
            }
        }
    }
}
