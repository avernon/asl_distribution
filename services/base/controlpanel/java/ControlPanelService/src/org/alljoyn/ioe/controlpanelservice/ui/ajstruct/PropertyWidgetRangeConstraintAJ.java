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

package org.alljoyn.ioe.controlpanelservice.ui.ajstruct;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.bus.annotation.Position;
import org.alljoyn.ioe.controlpanelservice.ui.PropertyWidget.RangeConstraint;
import org.alljoyn.ioe.controlpanelservice.ui.PropertyWidget.ValueType;

import android.util.Log;

/**
 * Property widget range constraint 
 */
public class PropertyWidgetRangeConstraintAJ {

	/**
	 * Minimum range value
	 */
	@Position(0)
	public Variant min;
	
	/**
	 * Maximum range value
	 */
	@Position(1)
	public Variant max;
	
	/**
	 * The value to increment/decerement
	 */
	@Position(2)
	public Variant increment;
	
	/**
	 * @param valueType The value type of this property 
	 * @param <T>
	 * @return Property widget range constraint or NULL if failed to unmarshal
	 */
	public RangeConstraint<?> getPropertyWidgetRangeConstraint(ValueType valueType) {
		Log.v("cpan" + PropertyWidgetRangeConstraintAJ.class.getSimpleName(), "Unmarshalling PropertyWidget range constraint");
		try {
			switch (valueType) {
				case BYTE: {
					 Byte minCast 		    = min.getObject(byte.class);
					 Byte maxCast 			= max.getObject(byte.class);
					 Byte incrementCast		= increment.getObject(byte.class);
					 return new RangeConstraint<Byte>(minCast, maxCast, incrementCast);
				}
				case DOUBLE: {
					 Double minCast 		= min.getObject(double.class);
					 Double maxCast			= max.getObject(double.class);
					 Double incrementCast	= increment.getObject(double.class);
					 return new RangeConstraint<Double>(minCast, maxCast, incrementCast);
				}
				case INT: {
					 Integer minCast 		= min.getObject(int.class);
					 Integer maxCast 		= max.getObject(int.class);
					 Integer incrementCast	= increment.getObject(int.class);
					 return new RangeConstraint<Integer>(minCast, maxCast, incrementCast);
				}
				case LONG: {
					 Long minCast 	 	    = min.getObject(long.class);
					 Long maxCast 		    = max.getObject(long.class);
					 Long incrementCast     = increment.getObject(long.class);
					 return new RangeConstraint<Long>(minCast, maxCast, incrementCast);
				}
				case SHORT: {
					 Short minCast 	 	    = min.getObject(short.class);
					 Short maxCast 		    = max.getObject(short.class);
					 Short incrementVal 	= increment.getObject(short.class);
					 return new RangeConstraint<Short>(minCast, maxCast, incrementVal);
				}
				default : {
					break;
				}
			}//SWITCH
		}//TRY
		catch (BusException be) {
			 Log.e("cpan" + PropertyWidgetRangeConstraintAJ.class.getSimpleName(), "Failed to unmarshal Range constraint: Error: '" + be.getMessage() + "'" );
			return null;
		}
		Log.e("cpan" + PropertyWidgetRangeConstraintAJ.class.getSimpleName(), "Failed to unmarshal Range constraint" );
		return null;
	}//getPropertyWidgetRangeConstraint
}
