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

package org.alljoyn.ioe.controlpanelservice.communication;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.RejectedExecutionException;
import java.util.concurrent.RejectedExecutionHandler;
import java.util.concurrent.SynchronousQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

import android.util.Log;

/**
 *  The thread pool manager is used to handle different tasks. <br>
 *  The tasks can be executed instantly by invoking the {@link TaskManager#execute(Runnable)} method, or 
 *  they may be enqueued and executed later, by calling the {@link TaskManager#enqueue(Runnable)} method
 */
public class TaskManager implements RejectedExecutionHandler {
	private static final String TAG = "cpan" + TaskManager.class.getSimpleName();
	
	/**
	 * Self reference for singleton
	 */
	private static final TaskManager SELF = new TaskManager();
	
	/**
	 * Gets TRUE if the object is valid, which means it has been initialized 
	 */
	private volatile boolean isValid;
	
	/**
	 * The thread TTL time
	 */
	private static final long THREAD_TTL        = 3;
	
	/**
	 * The thread TTL time unit
	 */
	private static final TimeUnit TTL_TIME_UNIT =  TimeUnit.SECONDS;
	
	/**
	 * Amount of the core threads 
	 */
	private static final int THREAD_CORE_NUM    = 4;
	
	/**
	 * The maximum number of threads that may be spawn
	 */
	private static final int THREAD_MAX_NUM     = 10;
	
	/**
	 * Thread pool object
	 */
	private ThreadPoolExecutor threadPool;

	/**
	 * The queue of tasks to be handled sequentially 
	 */
	private ExecutorService taskQueue;
	
	/**
	 * Constructor 
	 */
	private TaskManager() {}

	/**
	 * @return {@link TaskManager} instance
	 */
	public static TaskManager getInstance() {
		return SELF;
	}
	
	
	/**
	 * Initializes the thread pool
	 * @param nativePlatform The reference to the platform dependent object
	 */
	public void initPool() {
		
		Log.d(TAG, "Initializing TaskManager");
		initThreadPool();
		initTaskQueue();
		isValid = true;
	}
	
	/**
	 * @param task Executes the given {@link Runnable} task if there is a free thread worker
	 * @throws IllegalStateException if the object has not been initialized
	 */
	public void execute(Runnable task) {
		
		checkValid();
		Log.d(TAG,"Executing task, Current Thread pool size: '" +
												    threadPool.getPoolSize() + "', 'Number of currently working threads: '" +
												    threadPool.getActiveCount() + "'");
		threadPool.execute(task);
	}
	
	/**
	 * Enqueue the given {@link Runnable} task to be executed later
	 * @param task to executed
	 * @throws IllegalStateException if the object has not been initialized
	 */
	public void enqueue(Runnable task){
		
		checkValid();
		Log.d(TAG, "Enqueueing task to be executed");
		taskQueue.execute(task);
	}
	
	/**
	 * @return TRUE if the {@link TaskManager} has been initialized and it is running
	 */
	public boolean isRunning() {
		return isValid;
	}
	
	/**
	 * Tries to stop the thread pool and all its threads
	 * @throws IllegalStateException if the object has not been initialized  
	 */
	public void shutdown() {
		
		Log.d(TAG, "Shutting down TaskManager");
		isValid = false;
		if ( threadPool != null && !threadPool.isShutdown() ) {
			threadPool.shutdown();
			threadPool = null;
		}
		
		if ( taskQueue != null && !taskQueue.isShutdown() ) {
			taskQueue.shutdown();
			taskQueue = null;
		}
	}
	
	/**
	 * The callback is called, when there are no free threads to execute the given task  
	 */
	@Override
	public void rejectedExecution(Runnable r, ThreadPoolExecutor executor) {
		throw new RejectedExecutionException("Failed to execute the given task, all the worker threads are busy");
	}

	
	//=================================================//
	
	/**
	 * Checks the object validity
	 * @throws IllegalStateException if the object hasn't been initialized
	 */
	private void checkValid() {
		
		if ( !isValid ){
			throw new IllegalStateException("The WorkPoolManager has not been initialized. "
					+ "The initPool mathod should have been invoked");
		}
	}
	
	/**
	 * Initialize the threadpool
	 */
	private void initThreadPool() {
		
		threadPool = new ThreadPoolExecutor(
				THREAD_CORE_NUM,
				THREAD_MAX_NUM,
				THREAD_TTL,
				TTL_TIME_UNIT,
				new SynchronousQueue<Runnable>(true) // The fair order FIFO
		);
		
		threadPool.setRejectedExecutionHandler(this);
	}
	
	/**
	 * Initialize the task queue
	 */
	private void initTaskQueue() {
		taskQueue = Executors.newSingleThreadExecutor();
	}
	
}
