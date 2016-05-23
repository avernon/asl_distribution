/* Copyright (c) AllSeen Alliance. All rights reserved.
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
package org.allseen.lsf.sdk;

/**
 * Provides an interface for developers to implement and provide the Lighting system a thread
 * to process all Lighting events. The lighting system will post all events and invoke all callbacks
 * on the thread associated with the LightingSystemQueue.
 * <p>
 * <b>Note: Once implemented, the queue must be passed to the LightingDirector via the start method.
 * See {@link LightingDirector#start(String, LightingSystemQueue) start} for more information.</b>
 */
public interface LightingSystemQueue extends org.allseen.lsf.sdk.manager.LightingSystemQueue {

    /**
     * Post the provided runnable to the thread associated with the LightingSystemQueue.
     *
     * @param r Runnable to post to the queue
     */
    @Override
    public void post(Runnable r);

    /**
     * Post the provided runnable to the thread associated with the LightingSystemQueue
     * after the specified delay.
     *
     * @param r Runnable to post to the queue
     * @param delay Specifies the delay to wait before posting the runnable
     */
    @Override
    public void postDelayed(Runnable r, int delay);

    /**
     * Stops the thread associated the LightingSystemQueue.
     */
    @Override
    public void stop();
}
