/*
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
 */
package org.allseen.lsf.sdk.model;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class ControllerDataModel extends LightingItemDataModel {
    public static final char TAG_PREFIX_CONTROLLER = 'C';

    public static String defaultName = "<Controller not found>";

    public long version;
    public boolean connected;

    public ControllerDataModel() {
        this((String)null);
    }

    public ControllerDataModel(String controllerID) {
        this(controllerID, null);
    }

    public ControllerDataModel(String controllerID, String controllerName) {
        super(controllerID, TAG_PREFIX_CONTROLLER, controllerName != null ? controllerName : defaultName);

        version = 0;
        connected = false;
    }

    public ControllerDataModel(ControllerDataModel other) {
        super(other);

        version = other.version;
        connected = other.connected;
    }
}
