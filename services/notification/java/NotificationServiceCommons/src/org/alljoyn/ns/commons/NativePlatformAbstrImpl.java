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
 * The abstract parent class for all the classes implementing platform dependent logic 
 */
public abstract class NativePlatformAbstrImpl implements NativePlatform {
	
	/**
	 * Reference to logger
	 */
	protected GenericLogger logger; 
	
	/**
	 * Constructor
	 */
	public NativePlatformAbstrImpl() {
		createLogger();
	}

	/**
	 * Creates and set logger object
	 */
	protected abstract void createLogger();
	
	/**
	 * @see org.alljoyn.ns.commons.NativePlatform#getNativeLogger()
	 */
	@Override
	public GenericLogger getNativeLogger() {
		return logger;
	}

	/**
	 * @see org.alljoyn.ns.commons.NativePlatform#setNativeLogger(org.alljoyn.ns.commons.GenericLogger)
	 */
	@Override
	public void setNativeLogger(GenericLogger logger) {
		this.logger = logger;
	}
}
