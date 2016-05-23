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

import org.alljoyn.gatewaycontroller.sdk.Acl;
import org.alljoyn.gatewaycontroller.sdk.Acl.AclStatus;

/**
 * {@link Acl} to be visualized by the
 * {@link ConnectorAppAclsAdapter}
 */
public class VisualAcl implements VisualItem {

    /**
     * {@link Acl}
     */
    private Acl acl;

    /**
     * The acl status
     */
    private boolean isActive;

    /**
     * Constructor
     * 
     * @param acl
     */
    public VisualAcl(Acl acl) {

        this.acl = acl;
        updateActivityStatus();
    }

    /**
     * @return {@link Acl}
     */
    public Acl getAcl() {
        return acl;
    }

    /**
     * @return Current isActive status of the {@link VisualAcl}
     */
    public boolean isActive() {
        return isActive;
    }

    /**
     * Updates current {@link VisualAcl} status with the given {@link AclStatus}
     * 
     * @param aclStatus
     */
    public void updateActivityStatus() {

        switch (acl.getStatus()) {

            case GW_AS_ACTIVE: {
    
                isActive = true;
                break;
            }
            case GW_AS_INACTIVE: {
    
                isActive = false;
                break;
            }
        }
    }
}
