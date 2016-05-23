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
package org.allseen.lsf.sdk.manager;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public abstract class LightingItemListenerManager<LISTENER> {
    protected final Set<LISTENER> addedListeners = new HashSet<LISTENER>();
    protected final List<LISTENER> currentListeners = new ArrayList<LISTENER>();
    protected final Set<LISTENER> removedListeners = new HashSet<LISTENER>();

    protected final LightingSystemManager<?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?> manager;

    public LightingItemListenerManager(LightingSystemManager<?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?> manager) {
        super();

        this.manager = manager;
    }

    public void addListener(LISTENER listener) {
        removedListeners.remove(listener);
        addedListeners.add(listener);
    }

    public void removeListener(LISTENER listener) {
        addedListeners.remove(listener);
        removedListeners.add(listener);
    }

    protected void processAddedListeners() {
        currentListeners.addAll(addedListeners);
        addedListeners.clear();
    }

    protected LISTENER getNext(Iterator<LISTENER> iterator) {
        LISTENER nextListener = null;

        while (iterator.hasNext() && nextListener == null) {
            LISTENER tempListener = iterator.next();

            if (removedListeners.remove(tempListener)) {
                iterator.remove();
            } else {
                nextListener = tempListener;
            }
        }

        return nextListener;
    }
}
