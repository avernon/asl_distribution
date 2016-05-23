/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

package org.alljoyn.gatewaycontroller.adapters;

import org.alljoyn.gatewaycontroller.sdk.RuleObjectDescription.RuleInterface;
import org.alljoyn.gatewaycontroller.sdk.RuleObjectDescription.RuleObjectPath;
import org.alljoyn.gatewaycontroller.sdk.ConnectorCapabilities;

/**
 * {@link ConnectorCapabilities} to be visualized by the {@link ConnectorCapabilitiesAdapter}
 */
public class VisualRuleItem implements VisualItem {

    public static enum ItemType {

        OBJECT_PATH, INTERFACE
    }

    /**
     * The visual item of the {@link ItemType}
     */
    private Object visualItem;

    /**
     * The type of the visual item
     */
    private ItemType type;

    /**
     * Constructor
     * 
     * @param visualItem
     *            must be either {@link RuleObjectPath} or
     *            {@link RuleInterface}
     * @param type
     * @throws IllegalArgumentException
     */
    public VisualRuleItem(Object visualItem, ItemType type) {

        if (!(visualItem instanceof RuleObjectPath) && !(visualItem instanceof RuleInterface)) {

            throw new IllegalArgumentException("Wrong visualItem type");
        }

        if (type == null) {

            throw new IllegalArgumentException("Undefined type");
        }

        this.visualItem = visualItem;
        this.type = type;
    }

    /**
     * @return visualItem
     */
    public Object getVisualItem() {
        return visualItem;
    }

    /**
     * @return VisualItem type
     */
    public ItemType getType() {
        return type;
    }
}
