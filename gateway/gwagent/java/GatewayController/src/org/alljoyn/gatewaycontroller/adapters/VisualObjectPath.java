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
import org.alljoyn.gatewaycontroller.sdk.RuleObjectDescription.RuleObjectPath;

/**
 * Visualization {@link RuleObjectPath}
 */
public final class VisualObjectPath {

    /**
     * Reference to the {@link RuleObjectPath}
     */
    private RuleObjectPath objPath;

    /**
     * Gets TRUE if the object is selected to be part of the {@link AclRules}
     */
    private boolean isConfigured;

    /**
     * Gets TRUE if the isConfigured checkbox is enabled
     */
    private boolean isConfiguredEnabled;

    /**
     * Constructor
     * 
     * @param objPath
     * @param isConfigured
     */
    public VisualObjectPath(RuleObjectPath objPath, boolean isConfigured) {

        this.objPath             = objPath;
        this.isConfigured        = isConfigured;
        this.isConfiguredEnabled = true;
    }

    /**
     * @return TRUE if the configuration checkbox was selected
     */
    public boolean isConfigured() {
        return isConfigured;
    }

    /**
     * Set the state of the configuration checkbox
     * 
     * @param isConfigured
     */
    public void setConfigured(boolean isConfigured) {
        this.isConfigured = isConfigured;
    }

    /**
     * @return TRUE if the object path configure checkbox is enabled
     */
    public boolean isConfiguredEnabled() {
        return isConfiguredEnabled;
    }

    /**
     * @param isConfiguredEnabled
     *            TRUE if the configure checkbox is enabled
     */
    public void setConfiguredEnabled(boolean isConfiguredEnabled) {
        this.isConfiguredEnabled = isConfiguredEnabled;
    }

    /**
     * @return Returns wrapped {@link RuleObjectPath}
     */
    public RuleObjectPath getObjPath() {
        return objPath;
    }

    /**
     * @see java.lang.Object#hashCode()
     */
    @Override
    public int hashCode() {

        final int PRIME = 31;
        int result      = 1;
        result          = PRIME * result + ((objPath == null) ? 0 : objPath.hashCode());
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

        if (!(obj instanceof VisualObjectPath)) {
            return false;
        }

        VisualObjectPath other = (VisualObjectPath) obj;
        if (objPath == null) {

            if (other.objPath != null) {
                return false;
            }
        } else if (!objPath.equals(other.objPath)) {
            return false;
        }

        return true;
    }

}