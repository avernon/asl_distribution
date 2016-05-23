/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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

package org.alljoyn.bus;


public class AboutObj {

    /**
     * Create native resources held by objects of this class.
     *
     * @param bus the BusAttachment this About BusObject will be registered with
     */
    public AboutObj(BusAttachment bus) {
        create(bus, false);
    }

    /**
     * Create native resources held by objects of this class.
     *
     * @param bus the BusAttachment this About BusObject will be registered with
     * @param isAboutObjectAnnounced if 'true' the org.alljoyn.About interface
     *        will be announced as part of the Announce signal
     */
    public AboutObj(BusAttachment bus, boolean isAboutObjectAnnounced) {
        create(bus, isAboutObjectAnnounced);
    }

    /**
     * Destroy native resources held by objects of this class.
     */
    protected void finalize() throws Throwable {
        try {
            destroy();
        } finally {
            super.finalize();
        }
    }

    /**
     * Create any native resources held by objects of this class.  Specifically,
     * we allocate a C++ counterpart of this listener object.
     */
    private native void create(BusAttachment bus, boolean isAnnounced);

    /**
     * Release any native resources held by objects of this class.
     * Specifically, we may delete a C++ counterpart of this object.
     */
    private native void destroy();

    public native Status announce(short sessionPort, AboutDataListener aboutData);

    /**
     * Cancel the last announce signal sent. If no signals have been sent this
     * method call will return.
     *
     * @return Status.OK on success
     */
    public native Status unannounce();

    /**
     * The opaque pointer to the underlying C++ object which is actually tied
     * to the AllJoyn code.
     */
    private long handle = 0;
}
