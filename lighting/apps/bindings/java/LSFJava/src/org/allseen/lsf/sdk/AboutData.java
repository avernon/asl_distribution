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
package org.allseen.lsf.sdk;

import org.alljoyn.bus.Variant;

public class AboutData {
    /*
     *  Handle to the native objects backing this Java object
     */
    protected long nativeAboutDataHandle;

    public AboutData(long nativeAboutDataHandle) {
        this.nativeAboutDataHandle = nativeAboutDataHandle;
    }

    public void put(String key, String value) {
        put(key, value, "");
    }

    public void put(String key, String value, String language) {
        put(key, new Variant(new String(value)), language);
    }

    public void put(String key, byte[] value) {
        put(key, value, "");
    }

    public void put(String key, byte[] value, String language) {
        put(key, new Variant(value), language);
    }

    public void put(String key, String[] value) {
        put(key, value, "");
    }

    public void put(String key, String[] value, String language) {
        put(key, new Variant(value), language);
    }

    protected void put(String key, Variant value) {
        put(key, value, "");
    }

    protected void put(String key, Variant value, String language) {
        put(nativeAboutDataHandle, key, value, language);
    }

    protected native void put(long nativeAboutDataHandle, String key, Variant value, String language);
}
