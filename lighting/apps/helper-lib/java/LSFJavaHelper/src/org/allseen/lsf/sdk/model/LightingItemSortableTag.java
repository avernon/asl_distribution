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

import java.util.Locale;

/*
 * This class is designed to be immutable so that it is safer to use
 * as an external marker for the current sorted state of a containing
 * object. Should the containing object later need to update its
 * sorting state, it will have to create a new instance of this class.
 * Any external marker would therefore be left in the old state, and a
 * comparison would reveal that resorting is necessary.
 */
/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class LightingItemSortableTag implements Comparable<LightingItemSortableTag> {

    public final String sortableName;
    public final String tieBreaker;

    public LightingItemSortableTag(String id, char prefix, String name) {
        super();

        this.sortableName = prefix + name.toLowerCase(Locale.ENGLISH);
        this.tieBreaker = id;
    }

    public LightingItemSortableTag(LightingItemSortableTag other) {
        super();

        this.sortableName = other.sortableName;
        this.tieBreaker = other.tieBreaker;
    }

    @Override
    public int compareTo(LightingItemSortableTag other) {
        int comparison = sortableName.compareTo(other.sortableName);

        return comparison != 0 ? comparison : tieBreaker.compareTo(other.tieBreaker);
    }

    @Override
    public String toString() {
        return "{" + sortableName + ", " + tieBreaker + "}";
    }
}
