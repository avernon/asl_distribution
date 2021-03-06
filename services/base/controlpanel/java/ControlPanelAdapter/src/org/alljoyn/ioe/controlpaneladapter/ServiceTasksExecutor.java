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

package org.alljoyn.ioe.controlpaneladapter;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.RejectedExecutionException;

import android.util.Log;

/**
 * Executes {@link Callable} tasks.
 * The class is initialized with a given number of threads or with {@link ServiceTasksExecutor#NUM_THREADS_DEFAULT}
 */
public class ServiceTasksExecutor {
    private final static String TAG = "cpapp" + ServiceTasksExecutor.class.getSimpleName();

    /**
     * Default number of threads
     */
    private static final int NUM_THREADS_DEFAULT = 2;

    /**
     * Executor service
     */
    private final ExecutorService executor;

    /**
     * Create the {@link ServiceTasksExecutor} with {@link ServiceTasksExecutor#NUM_THREADS_DEFAULT}
     * @return {@link ServiceTasksExecutor}
     */
    public static ServiceTasksExecutor createExecutor(){

        return createExecutor(NUM_THREADS_DEFAULT);
    }

    /**
     * Create the {@link ServiceTasksExecutor} with the given number of threads.
     * @param numThreads Create the executor with the given number of threads
     * @return {@link ServiceTasksExecutor}
     */
    public static ServiceTasksExecutor createExecutor(int numThreads){

        return new ServiceTasksExecutor(numThreads);
    }

    /**
     * Constructor
     */
    private ServiceTasksExecutor(int numThreads) {

        Log.d(TAG, "Creating ServiceTaskExecutor with numThreads: '" + numThreads + "'");
        executor = Executors.newFixedThreadPool(numThreads);
    }

    /**
     * Do the best effort to shutdown the executor.
     * @see ExecutorService#shutdownNow()
     */
    public void shutdown() {

        Log.d(TAG, "Shutting down the ServiceTaskExecutor");
        executor.shutdownNow();
    }

    /**
     * Submit the given task for execution
     * @param task The {@link Callable} task to execute
     * @return {@link Future} of the submitted object
     * @throws IllegalArgumentException if the given task in NULL
     * @throws RejectedExecutionException
     * @see ExecutorService#submit(Callable)
     */
    public Future<Object> submit(Callable<Object> task) {

        if ( task == null ) {

            throw new IllegalArgumentException("task is indefined");
        }

        return executor.submit(task);
    }
}

