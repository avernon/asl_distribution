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

package org.alljoyn.ioe.controlpanelservice.ui;

import java.util.List;

import org.alljoyn.bus.Variant;
import org.alljoyn.ioe.controlpanelservice.ControlPanelException;
import org.alljoyn.ioe.controlpanelservice.communication.IntrospectionNode;

/**
 * The widget is used to replace a {@link UIElement} that had a failure in its creation <br>
 * Use the {@link ErrorWidget#getLabel()} method to receive a proposed label for this widget. <br>
 * Use the {@link ErrorWidget#getError()} method to receive an error description that triggered creation of this widget 
 */
public class ErrorWidget extends UIElement {

	/**
	 * The error message that explains the reason of this widget creation
	 */
	private String errorMsg;
	
	/**
	 * The default label for the widget
	 */
	private final String LABEL = "NOT AVAILABLE";
	
	/**
	 * Constructor
	 * @param elementType
	 * @param ifName
	 * @param objectPath
	 * @param controlPanel
	 * @param children
	 * @throws ControlPanelException
	 */
	public ErrorWidget(UIElementType elementType, String ifName,
			String objectPath, DeviceControlPanel controlPanel,
			List<IntrospectionNode> children) throws ControlPanelException {
		super(elementType, ifName, objectPath, controlPanel, children);
	}

	/**
	 * The default label for the widget
	 * @return The label content
	 */
	public String getLabel() {
		return LABEL;
	}//getLabel
	
	/**
	 * The error message that explains the reason of this widget creation
	 * @return The error message
	 */
	public String getError() {
		return errorMsg;
	}//getError
	
	/**
	 * The method tries to retrieve the original {@link UIElementType} that failed during the creation process 
	 * @return {@link UIElementType} of the original {@link UIElement} or NULL if it couldn't be retrieved
	 */
	public UIElementType getOriginalUIElement() {
		if ( ifName == null ) {
			return null;
		}
		
		if ( !WidgetFactory.isInitialized() ) {
			return null;
		}
		
		WidgetFactory widgetFact = WidgetFactory.getWidgetFactory(ifName);
		if ( widgetFact == null ) {
			return null;
		}
		
		return widgetFact.getElementType();
	}//getUIElement
	
	
	/**
	 * @see org.alljoyn.ioe.controlpanelservice.ui.UIElement#refreshProperties()
	 */
	@Override
	public void refreshProperties() throws ControlPanelException {
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.ui.UIElement#getVersion()
	 */
	@Override
	public short getVersion() {
		return 0;
	}

	/**
	 * The error message that explains the reason of this widget creation 
	 * @param errorMsg
	 */
	void setError(String errorMsg) {
		this.errorMsg = errorMsg;
	}
	
	/**
	 * @see org.alljoyn.ioe.controlpanelservice.ui.UIElement#setRemoteController()
	 */
	@Override
	protected void setRemoteController() throws ControlPanelException {
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.ui.UIElement#registerSignalHandler()
	 */
	@Override
	protected void registerSignalHandler() throws ControlPanelException {
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.ui.UIElement#setProperty(java.lang.String, org.alljoyn.bus.Variant)
	 */
	@Override
	protected void setProperty(String propName, Variant propValue) throws ControlPanelException {
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.ui.UIElement#createChildWidgets()
	 */
	@Override
	protected void createChildWidgets() throws ControlPanelException {
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.ui.UIElement#versionCheck()
	 */
	@Override
	protected void versionCheck() throws ControlPanelException {
	}

	
	
}
