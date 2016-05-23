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

package org.alljoyn.ioe.controlpanelservice.ui.ajstruct;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.bus.annotation.Position;
import org.alljoyn.ioe.controlpanelservice.ui.PropertyWidget.ConstrainToValues;
import org.alljoyn.ioe.controlpanelservice.ui.PropertyWidget.ValueType;

import android.util.Log;

public class PropertyWidgetConstrainToValuesAJ {
	
	@Position(0)
	public Variant value;
	
	@Position(1)
	public String label;
	
	/**
	 * Returns single object of PropertyWidget list of values
	 * @param valueType The property type of value
	 * @return
	 */
	public ConstrainToValues<?> getPropertyWidgetConstrainToValues(ValueType valueType) {
		Log.v("cpan" + PropertyWidgetConstrainToValuesAJ.class.getSimpleName(), "Unmarshalling PropertyWidget LOV constraint, label: '" + label + "'");
		try {
			switch (valueType) {
				case BOOLEAN: {
					Boolean valueCast = value.getObject(boolean.class);
					return new ConstrainToValues<Boolean>(valueCast, label);
				}
				case BYTE: {
					Byte valueCast    = value.getObject(byte.class);
					return new ConstrainToValues<Byte>(valueCast, label);
				}
				case DOUBLE: {
					Double valueCast  = value.getObject(double.class);
					return new ConstrainToValues<Double>(valueCast, label);					
				}
				case INT: {
					Integer valueCast = value.getObject(int.class);
					return new ConstrainToValues<Integer>(valueCast, label);					
				}
				case LONG: {
					Long valueCast    = value.getObject(long.class);
					return new ConstrainToValues<Long>(valueCast, label);					
				}
				case SHORT: {
					Short valueCast   = value.getObject(short.class);
					return new ConstrainToValues<Short>(valueCast, label);					
				}
				case STRING: {
					String valueCast  = value.getObject(String.class);
					return new ConstrainToValues<String>(valueCast, label);					
				}
				default: {
					break;
				}
			}//SWITCH
		}//TRY
		catch (BusException be) {
			 Log.e("cpan" + PropertyWidgetConstrainToValuesAJ.class.getSimpleName(), "Failed to unmarshal PropertyWidget LOV - Error: '" + be.getMessage() + "'" );
			return null;
		}
		Log.e("cpan" + PropertyWidgetConstrainToValuesAJ.class.getSimpleName(), "Failed to unmarshal PropertyWidget LOV" );
		return null;
	}//getPropertyWidgetRangeConstraint
	
}
