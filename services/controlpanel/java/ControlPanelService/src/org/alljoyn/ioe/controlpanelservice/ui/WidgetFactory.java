/******************************************************************************
 * Copyright (c) 2013, AllSeen Alliance. All rights reserved.
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

package org.alljoyn.ioe.controlpanelservice.ui;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.alljoyn.ioe.controlpanelservice.ControlPanelException;
import org.alljoyn.ioe.controlpanelservice.communication.IntrospectionNode;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.ActionControl;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.ActionControlSecured;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.AlertDialog;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.AlertDialogSecured;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.Container;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.ContainerSecured;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.Label;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.ListPropertyControl;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.ListPropertyControlSecured;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.PropertyControl;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.PropertyControlSecured;

import android.util.Log;

/**
 * The factory class for the UI widgets
 */
public class WidgetFactory {
	private static final String TAG = "cpan" + WidgetFactory.class.getSimpleName();
	
	/**
	 * Whether the factory was initialized successfully
	 */
	private static boolean isInitialized = false;	
	
	/**
	 * The interface lookup
	 */
	private static Map<String, WidgetFactory> ifaceLookup = new HashMap<String, WidgetFactory>();

	static {
		init();
	}
	
	private String iface;
	
	/**
	 * The class reflection of the AJ interface
	 */
	private Class<?> ifaceClass;
	
	/**
	 * The constructor reflection of the widget class
	 */
	private Constructor<?> constructor;
	
	/**
	 * The element type
	 */
	private UIElementType elementType;
	
	/**
	 * Whether the created widget is a top level object
	 */
	private boolean isTopLevelObj;
	
	private static void init () {
		try {
			ifaceLookup.put(ActionControl.IFNAME, new WidgetFactory(ActionControl.IFNAME, ActionControl.class, getConstructorReflection(ActionWidget.class), UIElementType.ACTION_WIDGET, false));
			ifaceLookup.put(ActionControlSecured.IFNAME, new WidgetFactory(ActionControlSecured.IFNAME, ActionControlSecured.class, getConstructorReflection(ActionWidget.class), UIElementType.ACTION_WIDGET, false));
			
			ifaceLookup.put(Container.IFNAME, new WidgetFactory(Container.IFNAME, Container.class, getConstructorReflection(ContainerWidget.class), UIElementType.CONTAINER, true));
			ifaceLookup.put(ContainerSecured.IFNAME, new WidgetFactory(ContainerSecured.IFNAME, ContainerSecured.class, getConstructorReflection(ContainerWidget.class), UIElementType.CONTAINER, true));
			
			ifaceLookup.put(AlertDialog.IFNAME, new WidgetFactory(AlertDialog.IFNAME, AlertDialog.class, getConstructorReflection(AlertDialogWidget.class), UIElementType.ALERT_DIALOG, true));  
			ifaceLookup.put(AlertDialogSecured.IFNAME, new WidgetFactory(AlertDialogSecured.IFNAME, AlertDialogSecured.class, getConstructorReflection(AlertDialogWidget.class), UIElementType.ALERT_DIALOG, true));
			
			ifaceLookup.put(PropertyControl.IFNAME, new WidgetFactory(PropertyControl.IFNAME, PropertyControl.class, getConstructorReflection(PropertyWidget.class), UIElementType.PROPERTY_WIDGET, false));
			ifaceLookup.put(PropertyControlSecured.IFNAME, new WidgetFactory(PropertyControlSecured.IFNAME, PropertyControlSecured.class, getConstructorReflection(PropertyWidget.class), UIElementType.PROPERTY_WIDGET, false));
			
			ifaceLookup.put(Label.IFNAME, new WidgetFactory(Label.IFNAME, Label.class, getConstructorReflection(LabelWidget.class), UIElementType.LABEL_WIDGET, false));
			
			ifaceLookup.put(ListPropertyControl.IFNAME, new WidgetFactory(ListPropertyControl.IFNAME, ListPropertyControl.class, getConstructorReflection(ListPropertyWidget.class), UIElementType.LIST_PROPERTY_WIDGET, false));
			ifaceLookup.put(ListPropertyControlSecured.IFNAME, new WidgetFactory(ListPropertyControlSecured.IFNAME, ListPropertyControlSecured.class, getConstructorReflection(ListPropertyWidget.class), UIElementType.LIST_PROPERTY_WIDGET, false));
			
			isInitialized = true;
		}
		catch(Exception e) {
			Log.e(TAG, "Failed to initialize widget factory, Error: '" + e.getMessage() + "'");
			isInitialized = false;
		}
	}//init
	
	/**
	 * @return Whether the {@link WidgetFactory} is successfully initialized
	 */
	public static boolean isInitialized() {
		return isInitialized;
	}
	
	/**
	 * @param ifName The interface name to look for the appropriate factory 
	 * @return Return {@link WidgetFactory} if the ifName is a known interface and WidgetFactory was initialized successfully,
	 * otherwise returns NULL
	 */
	public static WidgetFactory getWidgetFactory(String ifName) {
		if ( !isInitialized ) {
			return null;
		}
		
		Log.d(TAG, "getWidgetFactory() is looking for the interface '" + ifName + "'");
		return ifaceLookup.get(ifName);		
	}//getWidgetFactory
	
	/**
	 * Constructor
	 * @param iface The name of the AJ interface
	 * @param ifaceClass The class reflection object of the AJ interface
	 * @param constructor The constructor reflection of the widget class
	 * @param elementType The element type
	 * @param isTopLevelObj Whether the built element is a top level object
	 */
	private WidgetFactory(String iface, Class<?> ifaceClass, Constructor<?> constructor, UIElementType elementType, boolean isTopLevelObj) {
		this.iface 			= iface;
		this.ifaceClass     = ifaceClass;
		this.constructor	= constructor;
		this.elementType 	= elementType;
		this.isTopLevelObj  = isTopLevelObj;
	}

	/**
	 * @param widgClass
	 * @return Returns constructor object of the received class
	 * @throws NoSuchMethodException 
	 */
	private static Constructor<?> getConstructorReflection(Class<?> widgClass) throws NoSuchMethodException {
		return widgClass.getConstructor(
				String.class,
				String.class,
				DeviceControlPanel.class,
				List.class
		);		
	}//getConstructorReflection

	public String getIface() {
		return iface;
	}
	
	public Class<?> getIfaceClass() {
		return ifaceClass;
	}

	public UIElementType getElementType() {
		return elementType;
	}

	public boolean isTopLevelObj() {
		return isTopLevelObj;
	}
	
	/**
	 * Create the  {@link UIElement}
	 * @param objectPath
	 * @param controlPanel
	 * @param children
	 * @return Return  the {@link UIElement} if create succeeded or NULL if failed to create the object
	 * @throws ControlPanelException
	 */
	public UIElement create(String objectPath, DeviceControlPanel controlPanel, List<IntrospectionNode> children) throws ControlPanelException {
		Log.i(TAG, "Create element: '" + elementType + "' objPath: '" + objectPath + "'");
		UIElement retValue;
		try {
			retValue = (UIElement) constructor.newInstance(iface, objectPath, controlPanel, children);
		}
		catch (InvocationTargetException ite) {
			String invokeError = ite.getTargetException().getMessage();
			Log.e(TAG, "Error happened when invoking the constructor of  '" + elementType + "', Error: '" + invokeError + "'");
			throw new ControlPanelException(invokeError);
		}
		catch (Exception e) {
			Log.e(TAG, "Unexpected error happened, failed to create the UIElement: '" + elementType + "'");
			throw new ControlPanelException(e);
		}
		return retValue;
	}//create
}
