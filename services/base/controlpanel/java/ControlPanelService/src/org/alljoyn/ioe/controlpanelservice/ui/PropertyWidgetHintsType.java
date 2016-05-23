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

/**
 * Possible types of property UI hints
 */
public enum PropertyWidgetHintsType {
	SWITCH((short)1),
	CHECKBOX((short)2),
	SPINNER((short)3),
	RADIO_BUTTON((short)4),
	SLIDER((short)5),
	TIME_PICKER((short)6),
	DATE_PICKER((short)7),
	NUMBER_PICKER((short)8),
	NUMERIC_KEYPAD((short)9),
	ROTARY_KNOB((short)10),
	TEXT_VIEW((short)11),
	NUMERIC_VIEW((short)12),
	EDIT_TEXT((short)13),
	;
	
    /** 
     * The key number
     */  
    public final short ID; 
        
    /** 
     * Constructor
     * @param id
     */
    private PropertyWidgetHintsType(short id) {
        ID = id; 
    }   
        
    /** 
     * Search for the enum by the given id
     * If not found returns NULL
     * @param id  
     * @return Enum type by the given id
     */
    public static PropertyWidgetHintsType getEnumById(short id) {
    	PropertyWidgetHintsType retType = null;
        for (PropertyWidgetHintsType type : PropertyWidgetHintsType.values()) {
            if ( id == type.ID ) { 
                retType = type;
                break;
            }   
        }   
        return retType;
    }//getEnumById
}
