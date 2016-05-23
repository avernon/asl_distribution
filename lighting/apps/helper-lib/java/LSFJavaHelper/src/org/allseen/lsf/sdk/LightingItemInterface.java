/* Copyright (c) AllSeen Alliance. All rights reserved.
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
 */
package org.allseen.lsf.sdk;

/**
 * Base interface that is implemented by all Lighting items and provides getters
 * for the item ID, name, as wells as child and parent Lighting items.
 */
public interface LightingItemInterface {
    /**
     * Returns the ID of the Lighting item.
     *
     * @return ID of the Lighting item
     */
    public String getId();

    /**
     * Returns the name of the Lighting item.
     *
     * @return Name of the Lighting item
     */
    public String getName();

    /**
     * Returns the Lighting items parent components.
     *
     * @return Array of Lighting item parent components
     */
    public LightingItem[] getDependents();

    /**
     * Returns the Lighting items child components.
     *
     * @return Array of Lighting item child components
     */
    public LightingItem[] getComponents();
}
