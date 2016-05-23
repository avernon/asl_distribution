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
package org.allseen.lsf.sampleapp;

import android.os.SystemClock;

public class ItemDataModel {

    public String id;
    private final char prefix;
    private String name;
    public long timestamp;
    public LightingItemSortableTag tag;

    public ItemDataModel(String id, char prefix, String name) {
        super();

        this.id = id;
        this.prefix = prefix;
        this.name = name;
        this.timestamp = SystemClock.elapsedRealtime();
        this.tag = new LightingItemSortableTag(this.id, this.prefix, this.name);
    }

    public ItemDataModel(ItemDataModel other) {
        this.id = other.id;
        this.prefix = other.prefix;
        this.name = other.name;
        this.timestamp = other.timestamp;
        this.tag = new LightingItemSortableTag(other.tag);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
        this.tag = new LightingItemSortableTag(this.id, this.prefix, this.name);
    }

    @Override
    public int hashCode() {
        return id.hashCode();
    }

    public boolean equalsID(String itemID) {
        return id.equals(itemID);
    }

    @Override
    public boolean equals(Object other) {
        boolean equivalent = false;

        if ((other != null) && (other instanceof ItemDataModel)) {
            equivalent = (other == this) || (equalsID(((ItemDataModel)other).id));
        }

        return equivalent;
    }
}
