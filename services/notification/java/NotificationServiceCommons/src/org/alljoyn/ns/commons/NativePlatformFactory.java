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

package org.alljoyn.ns.commons;

/**
 * The factory class for the classes extending {@link NativePlatformAbstrImpl} <br>
 * According to the platform that the service is running on, the appropriate platform dependent class is 
 * instantiated and returned 
 */
public class NativePlatformFactory {
	/**
	 * Supported OS platforms 
	 */
	private static enum OSPlatform {
		WINDOWS ("Windows",""),
		ANDROID ("Android","org.alljoyn.ns.nativeplatform.NativePlatformAndroid"),
		LINUX   ("Linux", "");
		
		/**
		 * Name of the platform to look for in System properties
		 */
		public final String NAME;
		
		/**
		 * Class name to load the native platform implementation class dynamically
		 */
		public final String CLASS_NAME;
		
		/**
		 * Constructor
		 * @param name
		 * @param className
		 */
		private OSPlatform(String name, String className) {
			NAME        = name;
			CLASS_NAME 	= className;
		}
	}//enum :: Platform
	
	//=====================================================//
	
	/**
	 * Reference to native platform object
	 */
	private static volatile NativePlatform nativePlatform = null;
	
	/**
	 * Sytem.os.name
	 */
	private static String osPlatform;
	
	/**
	 * System.java.vm.vendor
	 */
	private static String vmVendor;
	
	/**
	 * Constructor
	 * We want to prevent possibility to create objects of this class
	 */
	private NativePlatformFactory(){}
	
	/**
	 * Returns reference to the native platform object
	 * @return reference to the NativePlatform object
	 * @throws NativePlatformFactoryException throws exception if failed to recognize the platform or
	 * to instantiate the native platform object
	 */
	public static NativePlatform getPlatformObject() throws NativePlatformFactoryException {
		if ( nativePlatform != null ) {
			return nativePlatform;
		}

		OSPlatform osPlatformType = identifyPlatform();
		if ( osPlatformType == null || osPlatformType.CLASS_NAME.isEmpty() ) {
			 throw new NativePlatformFactoryException("Failed to find NativePlatform class for os: '" + osPlatformType + "', vmVendor: '" + vmVendor + "'"); 
		}
			
		synchronized (NativePlatformFactory.class) {
			if ( nativePlatform == null ) {
				nativePlatform = getClassInstance(osPlatformType.CLASS_NAME);
			}//if :: nativePlatform == null
		}//synchronized
		
		return nativePlatform;
	}//getPlatformObject
	
	/**
	 * Uses reflection to load class dynamically and create its instance
	 * @param className
	 */
	private static NativePlatform getClassInstance(String className) throws NativePlatformFactoryException {
		NativePlatform nativePlatformObj;
		try {
			@SuppressWarnings("unchecked")
			Class<NativePlatform> nativePlatformClass = (Class<NativePlatform>) Class.forName(className);
			nativePlatformObj = nativePlatformClass.newInstance();
		} catch (ClassNotFoundException e) {
			throw new NativePlatformFactoryException("Failed to load class: '" + className + "'",e);
		}
		catch(IllegalAccessException  ilae) {
			throw new NativePlatformFactoryException(ilae);
		}
		catch (InstantiationException ie) {
			throw new NativePlatformFactoryException(ie);
		}
		return nativePlatformObj;
	}//getClassInstance
	
	/**
	 * Identifies the platform this code is executed on
	 * @return if platform isn't recognized, return NULL
	 */
	private static OSPlatform identifyPlatform() {
		osPlatform = System.getProperty("os.name", "");
		vmVendor   = System.getProperty("java.vm.vendor", "");
		
		if ( osPlatform.isEmpty() ) {
			return null;
		}
		if ( osPlatform.indexOf(OSPlatform.WINDOWS.NAME) > -1 ) {
			return OSPlatform.WINDOWS;
		}//if :: windows
		if ( osPlatform.indexOf(OSPlatform.LINUX.NAME) > -1 ) {
			//Check Android
			if ( !vmVendor.isEmpty() && vmVendor.indexOf(OSPlatform.ANDROID.NAME) > -1 ) {
				return OSPlatform.ANDROID;
			}
			return OSPlatform.LINUX;
		}//if :: linux
		
		return null;
	}//identifyPlatform
	
}//NativePlatformFactory
