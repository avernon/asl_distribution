/*
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

import java.util.HashSet;
import java.util.Set;

public class SceneElementDataModelV2 extends LightingItemDataModel {
    public static final char TAG_PREFIX_SCENE_ELEMENT = 'S';

    public static String defaultName = "<Loading scene element info...>";

    protected boolean lampsInitialized;
    protected boolean groupsInitialized;
    protected boolean effectIdInitialized;

    private Set<String> lamps;
    private Set<String> groups;
    private String effectId;

    public SceneElementDataModelV2() {
        this((String)null);
    }

    public SceneElementDataModelV2(String sceneElementID) {
        this(sceneElementID, null);
    }

    public SceneElementDataModelV2(String sceneElementID, String sceneElementName) {
        super(sceneElementID, TAG_PREFIX_SCENE_ELEMENT, sceneElementName != null ? sceneElementName : defaultName);

        lamps = new HashSet<String>();
        groups = new HashSet<String>();
        effectId = null;

        lampsInitialized = false;
        groupsInitialized = false;
        effectIdInitialized = false;
    }

    public SceneElementDataModelV2(SceneElementDataModelV2 other) {
        super(other);

        lamps = new HashSet<String>(other.getLamps());
        groups = new HashSet<String>(other.getGroups());
        effectId = other.getEffectId();

        lampsInitialized = other.lampsInitialized;
        groupsInitialized = other.groupsInitialized;
        effectIdInitialized = other.effectIdInitialized;
    }

    public Set<String> getLamps() {
        return lamps;
    }

    public void setLamps(Set<String> lamps) {
        this.lamps = lamps;
        lampsInitialized = true;
    }

    public Set<String> getGroups() {
        return groups;
    }

    public void setGroups(Set<String> groups) {
        this.groups = groups;
        groupsInitialized = true;
    }

    public String getEffectId() {
        return effectId;
    }

    public void setEffectId(String effectId) {
        this.effectId = effectId;
        effectIdInitialized = true;
    }

    // Only checks immediate child lamps.
    public boolean containsLamp(String lampID) {
        return lamps.contains(lampID);
    }

    // Only checks immediate child groups.
    public boolean containsGroup(String groupID) {
        return groups.contains(groupID);
    }

    public boolean containsEffect(String effectID) {
        return effectID.equals(this.effectId);
    }

    @Override
    public boolean isInitialized() {
        return super.isInitialized() && lampsInitialized && groupsInitialized && effectIdInitialized;
    }
}
