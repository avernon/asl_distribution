/*
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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
 */
package org.allseen.lsf.sampleapp;

import android.util.Log;

public class RetryManager implements Runnable {

    private final SampleAppActivity activity;
    private final int interval;

    public RetryManager(SampleAppActivity activity, int interval) {
        super();

        this.activity = activity;
        this.interval = interval;
    }

    public void start() {
        activity.handler.post(this);
    }

    public void post(final Runnable command) {
        activity.handler.post(new Runnable() {
            @Override
            public void run() {
                activity.commands.offer(command);
            }
         });
    }

    @Override
    public void run() {
        if (AllJoynManager.controllerConnected) {
            Runnable command = activity.commands.poll();

            if (command != null) {
                Log.d(SampleAppActivity.TAG, "Retrying next command");
                command.run();
            }
        }

        activity.handler.postDelayed(this, interval);
    }
}
