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

package org.alljoyn.gatewaycontroller.sdk;

import org.alljoyn.gatewaycontroller.sdk.Acl.AclResponseCode;

/**
 * The class holds the {@link AclResponseCode} returned by the invocation of the
 * createAcl or updateAcl methods. In addition it holds the {@link AclRules}
 * object with the rules that do not comply with the {@link ConnectorCapabilities}
 */
public class AclWriteResponse {

    /**
     * Acl id
     */
    private final String id;

    /**
     * Response code
     */
    private final AclResponseCode code;

    /**
     * ACL object path
     */
    private final String objectPath;

    /**
     * The rules that don't comply with the {@link ConnectorCapabilities}
     */
    private final AclRules invalidRules;

    /**
     * Constructor
     * 
     * @param id
     *            ACL id
     * @param code
     *            {@link AclResponseCode}
     * @param invalidRules
     *            {@link AclRules}
     * @param objPath
     *            Object path
     */
    AclWriteResponse(String id, AclResponseCode code, AclRules invalidRules, String objPath) {

        this.id             = id;
        this.code           = code;
        this.invalidRules   = invalidRules;
        this.objectPath     = objPath;
    }

    /**
     * @return The id of the ACL that the write operation was referred to
     */
    public String getAclId() {
        return id;
    }

    /**
     * @return {@link AclResponseCode} of the ACL write action
     */
    public AclResponseCode getResponseCode() {
        return code;
    }

    /**
     * @return {@link AclRules} with the rules that don't comply with the {@link ConnectorCapabilities}
     */
    public AclRules getInvalidRules() {
        return invalidRules;
    }

    /**
     * @return {@link Acl} object path
     */
    public String getObjectPath() {
        return objectPath;
    }
}
