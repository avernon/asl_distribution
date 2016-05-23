/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

import org.alljoyn.ioe.controlpanelservice.ControlPanelException;
import org.alljoyn.ioe.controlpanelservice.ui.UIElement;

import android.util.Log;

/**
 * The class includes all the required data to register/unregister signals <br>
 * Additionally the class has a logic to dispatch the received signals to be handled on the separate thread from AllJoyn
 */
public class UIWidgetSignalHandler implements InvocationHandler {
	private static final String TAG = "cpan" + UIWidgetSignalHandler.class.getSimpleName();
	
	/**
	  * MetadataChanged signal refreshes the {@link UIElement} object properties which it was sent for.
	  * This is done by executing {@link org.alljoyn.bus.ifaces.Properties#GetAll(String)} method.
	  * To avoid load on the AJ daemon when it receives multiple METADATA_CHANGED signals, we handle them
	  * sequentially on a separate thread by invoking {@link TaskManager#enqueue(Runnable)}.
	  * All the other signals that are just delegated to an appropriate listener will be simultaneously 
	  * handled by a separate thread from the {@link TaskManager} thread pool by invoking {@link TaskManager#execute(Runnable)}
	  */
	private static final String METADATA_CHANGED = "MetadataChanged";
	
	/**
	 * The object path that is used as a signal source.
	 */
	 private String objPath;
	    
	 /**
	  * The real signal handler object
	  */
	 private Object signalReceiver;
	 
	 /**
	  * The proxy object signal handler is created based on the {@link Proxy}
	  * This is the object that actually receives signals from the daemon and its {@link InvocationHandler} dispatches 
	  * the signal to be handled on the separate thread from AllJoyn.
	  * Signal handling logic is executed in the signalReceiver object 
	  */
	 private Object proxySignalReceiver;
	 
	 /**
	  * The reflection of the signal method 
	  */
	 private Method method;
	    
	 /**
	  * The interface of the signal
	  */
	 private String ifName;
	
	/**
	 * Constructor
	 * @param objPath The object path that is used as a signal source.
	 * @param signalReceiver The signal receiver object
	 * @param method The reflection of the signal method 
	 * @param ifName The interface of the signal
	 */
	public UIWidgetSignalHandler(String objPath, Object signalReceiver, Method method, String ifName) {
		this.objPath        = objPath;
		this.signalReceiver = signalReceiver;
		this.method         = method;
		this.ifName         = ifName;
	}

	/**
	 * Registers signal handler
	 * @throws ControlPanelException
	 */
	public void register() throws ControlPanelException {
				
		Class<?>[] ifaceList = signalReceiver.getClass().getInterfaces();
		if ( ifaceList.length == 0 ) {
		    String msg = "Received signalReceiver object doesn't implement any interface";
            Log.e(TAG, msg); 
            throw new ControlPanelException(msg);
		}
		
		proxySignalReceiver = createProxySignalReceiver(ifaceList);
		
        ConnectionManager.getInstance().registerObjectAndSetSignalHandler(
                ifName,
                method.getName(),
                method,
                proxySignalReceiver,
                objPath,
                objPath
       );
	}//register
	
	/**
	 * Unregisters signal handler
	 * @throws ControlPanelException
	 */
	public void unregister() throws ControlPanelException {
		
		Log.v(TAG, "Unregistering signal handler: '" + method.getName() + "', objPath: '" + objPath + "'");
		ConnectionManager.getInstance().unregisterSignalHandler(proxySignalReceiver, method);
		signalReceiver      = null;
		proxySignalReceiver = null;
	}//unregister

	/**
	 * Create {@link Proxy} object based on the given array of interface classes
	 * @return Created object
	 */
	private Object createProxySignalReceiver(Class<?>[] ifaceClassList) {
		return Proxy.newProxyInstance(ifaceClassList[0].getClassLoader(), ifaceClassList, this);
	}

	/**
	 * @see java.lang.reflect.InvocationHandler#invoke(java.lang.Object, java.lang.reflect.Method, java.lang.Object[])
	 */
	@Override
	public Object invoke(Object proxy, final Method method, final Object[] args) throws Throwable {
		
		Runnable task = new Runnable() {
			@Override
			public void run() {
				try {
					method.invoke(signalReceiver, args);
				} catch (Exception e) {
					Log.d(TAG, "Failed to invoke the method: '" + method.getName() + "', Error: '" + e.getMessage() + "'", e);
				}
			}
		};
		
		//Received METADATA_CHANGED signal enqueue it to be executed 
		if ( METADATA_CHANGED.equals(method.getName()) ) {
			
			Log.d(TAG, "Received '" + METADATA_CHANGED + "' signal storing it in the queue for later execution");
			TaskManager.getInstance().enqueue(task) ;
		}
		else {
			
			Log.d(TAG, "Received '" + method.getName() + "' signal passing it for execution");
			TaskManager.getInstance().execute(task);
		}
		
		return null;
	}//invoke
	
}
