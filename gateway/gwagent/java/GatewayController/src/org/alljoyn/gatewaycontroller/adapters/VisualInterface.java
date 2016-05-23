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

import org.alljoyn.gatewaycontroller.sdk.AclRules;
import org.alljoyn.gatewaycontroller.sdk.RuleObjectDescription.RuleInterface;

/**
 * Visualization of the {@link RuleInterface}
 */
public final class VisualInterface {

    /**
     * Reference to the {@link RuleInterface} object
     */
    private RuleInterface iface;

    /**
     * Gets TRUE if the interface is selected to be part of the
     * {@link AclRules}
     */
    private boolean isConfigured;

    /**
     * Constructor
     * 
     * @param iface
     * @param isConfigured
     */
    public VisualInterface(RuleInterface iface) {

        this.iface = iface;
    }

    /**
     * @return Returns TRUE if the interface is selected
     */
    public boolean isConfigured() {
        return isConfigured;
    }

    /**
     * @param isConfigured
     *            Set the configuration state of the interface
     */
    public void setConfigured(boolean isConfigured) {
        this.isConfigured = isConfigured;
    }

    /**
     * @return Return the wrapped {@link RuleInterface} object
     */
    public RuleInterface getIface() {
        return iface;
    }

    /**
     * @see java.lang.Object#hashCode()
     */
    @Override
    public int hashCode() {

        final int PRIME = 31;
        int result      = 1;
        result          = PRIME * result + ((iface == null) ? 0 : iface.hashCode());
        return result;
    }

    /**
     * @see java.lang.Object#equals(java.lang.Object)
     */
    @Override
    public boolean equals(Object obj) {

        if (this == obj) {
            return true;
        }

        if (obj == null) {
            return false;
        }

        if (!(obj instanceof VisualInterface)) {
            return false;
        }

        VisualInterface other = (VisualInterface) obj;
        if (iface == null) {

            if (other.iface != null) {
                return false;
            }
        } else if (!iface.equals(other.iface)) {
            return false;
        }

        return true;
    }

}