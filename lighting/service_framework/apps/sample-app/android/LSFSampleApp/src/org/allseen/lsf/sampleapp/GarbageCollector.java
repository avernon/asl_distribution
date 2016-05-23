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

import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;

import android.os.SystemClock;
import android.support.v4.app.Fragment;
import android.util.Log;

public class GarbageCollector implements Runnable {

    private final SampleAppActivity activity;
    private final int cycle;
    private final long timeout;

    public GarbageCollector(SampleAppActivity activity, int cycle, long timeout) {
        super();

        this.activity = activity;
        this.cycle = cycle;
        this.timeout = timeout;
    }

    public void start() {
        activity.handler.post(this);
    }

    public boolean isLampExpired(String lampID) {
        return isExpired(activity.lampModels.get(lampID));
    }

    public boolean isExpired(ItemDataModel itemModel) {
        return (itemModel == null) || ((itemModel.timestamp + timeout) < SystemClock.elapsedRealtime());
    }

    @Override
    public void run() {
        if (AllJoynManager.controllerConnected) {
            if (SampleAppActivity.POLLING_DISTRIBUTED) {
                runIncrementalScan();
            } else {
                runFullScan();
            }
        } else {
            activity.handler.postDelayed(this, cycle);
        }
    }

    public void runIncrementalScan() {
        int count = activity.lampIDs.size();
        int delay = Math.max(count > 0 ? Math.round((float)cycle / count) : cycle, SampleAppActivity.POLLING_DELAY_MIN);
        String lampID = activity.lampIDs.poll();

        Log.d(SampleAppActivity.TAG, "runIncrementalScan(): " + lampID + ", " + delay);

        if (lampID != null) {
            LampDataModel lampModel = activity.lampModels.get(lampID);

            if (!isExpired(lampModel)) {
                activity.lampIDs.offer(lampID);
            } else {
                activity.lampModels.remove(lampID);
                onLampExpired(lampModel);
            }
        }

        activity.handler.postDelayed(this, delay);
    }

    public void runFullScan() {
        Iterator<Entry<String, LampDataModel>> lampModelsIterator = activity.lampModels.entrySet().iterator();
        int delay = cycle;

        Log.d(SampleAppActivity.TAG, "runFullScan(): " + delay);

        while (lampModelsIterator.hasNext()) {
            Map.Entry<String, LampDataModel> entry = lampModelsIterator.next();
            LampDataModel lampModel = entry.getValue();

            if (isExpired(lampModel)) {
                lampModelsIterator.remove();

                onLampExpired(lampModel);
            }
        }

        activity.handler.postDelayed(this, cycle);
    }

    public void onLampExpired(LampDataModel lampModel) {
        Log.d(SampleAppActivity.TAG, "Pruned lamp " + lampModel.id);

        Fragment pageFragment = activity.getSupportFragmentManager().findFragmentByTag(LampsPageFragment.TAG);

        if (pageFragment != null) {
            LampsTableFragment tableFragment = (LampsTableFragment) pageFragment.getChildFragmentManager().findFragmentByTag(PageFrameParentFragment.CHILD_TAG_TABLE);
            LampInfoFragment infoFragment = (LampInfoFragment) pageFragment.getChildFragmentManager().findFragmentByTag(PageFrameParentFragment.CHILD_TAG_INFO);

            if (tableFragment != null) {
                tableFragment.removeElement(lampModel.id);

                if (activity.lampModels.size() == 0) {
                    tableFragment.updateLoading();
                }
            }

            if ((infoFragment != null) && (infoFragment.key.equals(lampModel.id))) {
                activity.createLostConnectionErrorDialog(lampModel.getName());
            }
        }
    }
}
