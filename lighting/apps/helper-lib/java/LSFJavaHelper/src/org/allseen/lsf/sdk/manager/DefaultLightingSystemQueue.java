/*
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
 */
package org.allseen.lsf.sdk.manager;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.concurrent.DelayQueue;
import java.util.concurrent.Delayed;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;

public class DefaultLightingSystemQueue implements LightingSystemQueue {

    private final DelayQueue<DelayedRunnable> delayQueue;
    private volatile Thread backgroundThread;
    private AtomicLong indexCounter;

    private class DelayedRunnable implements Runnable, Delayed {

        private final Runnable runnable;
        private final long expiration;
        private final long priority;

        public DelayedRunnable(Runnable runnable, int delay) {
            this.runnable = runnable;
            this.expiration = System.currentTimeMillis() + delay;
            this.priority = getNextIndex();
        }

        @Override
        public int compareTo(Delayed that) {
            // Long.compare is not available until 1.7
            return Long.valueOf(this.getDelay(TimeUnit.MILLISECONDS)).compareTo(Long.valueOf(that.getDelay(TimeUnit.MILLISECONDS)));
        }

        @Override
        public long getDelay(TimeUnit unit) {
            return unit.convert(expiration - System.currentTimeMillis(), TimeUnit.MILLISECONDS);
        }

        @Override
        public void run() {
            runnable.run();
        }

        public long getPriority() {
            return priority;
        }
    }

    private class DelayedRunnablePriorityComparator implements Comparator<DelayedRunnable> {
        @Override
        public int compare(DelayedRunnable a, DelayedRunnable b) {
            return Long.valueOf(a.getPriority()).compareTo(b.getPriority());
        }
    }

    public DefaultLightingSystemQueue() {
        delayQueue = new DelayQueue<DelayedRunnable>();
        indexCounter = new AtomicLong(0);
        backgroundThread = new Thread() {
            PriorityQueue<DelayedRunnable> pQueue = new PriorityQueue<DelayedRunnable>(10, new DelayedRunnablePriorityComparator());

            @Override
            public void run() {
                while (backgroundThread != null) {
                    try {
                        DelayedRunnable task = null;

                        // grab all expired tasks (to run)
                        pQueue.add(task = delayQueue.take());
                        while ((task = delayQueue.poll()) != null) {
                            pQueue.add(task);
                        }

                        // run tasks in priority order
                        while ((task = pQueue.poll()) != null) {
                            task.run();
                        }
                    } catch (InterruptedException e){
                        // If stopped, we will drop out of the while loop
                    }
                }
            }};
        backgroundThread.start();
    }

    @Override
    public void post(Runnable runnable) {
        postDelayed(runnable, 0);
    }

    @Override
    public void postDelayed(Runnable runnable, int delay) {
        delayQueue.put(new DelayedRunnable(runnable, delay));
    }

    @Override
    public void stop() {
        Thread tempThread = backgroundThread;

        backgroundThread = null;
        tempThread.interrupt();
    }

    private long getNextIndex() {
        return indexCounter.getAndIncrement();
    }
}
