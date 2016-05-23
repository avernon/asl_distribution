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

package org.alljoyn.services.common;

import org.alljoyn.bus.annotation.Position;

/**
 * Descriptions of the BusObjects that make up the service.
 * Pairing a BusObject with the BusInterfaces that it implements.
 * @deprecated see org.alljoyn.bus.AboutObjectDescription
 */
@Deprecated
public class BusObjectDescription {

    /**
     * The object path of the BusObject 
     * @deprecated see org.alljoyn.bus.AboutObjectDescription
     */
    @Deprecated
    @Position(0) public String path;
    /**
     * An array of strings where each element of the array names an AllJoyn
     * interface that is implemented by the given BusObject.
     * @deprecated see org.alljoyn.bus.AboutObjectDescription
     */
    @Deprecated
    @Position(1) public String[] interfaces;

    /**
     * Return the BusObject path
     * @deprecated see org.alljoyn.bus.AboutObjectDescription
     * @return the BusObject path
     */
    @Deprecated
    public String getPath()
    {
        return path;
    }

    /**
     * Set the BusObject path
     * @deprecated see org.alljoyn.bus.AboutObjectDescription
     * @param path the BusObject path
     */
    @Deprecated
    public void setPath(String path)
    {
        this.path = path;
    }

    /**
     * @deprecated see org.alljoyn.bus.AboutObjectDescription
     * @return Returns the interfaces that are implemented by this BusObject
     */
    @Deprecated
    public String[] getInterfaces()
    {
        return interfaces;
    }

    /**
     * Set the interfaces that are implemented by this BusObject
     * @deprecated see org.alljoyn.bus.AboutObjectDescription
     * @param interfaces the interfaces that are implemented by this BusObject
     */
    @Deprecated
    public void setInterfaces(String[] interfaces)
    {
        this.interfaces = interfaces;
    }

    @Override
    @Deprecated
    public String toString() {

        StringBuilder s = new StringBuilder("");
        s = s.append("path: ").append(path).append(".\n");
        s.append("interfaces: ");
        for (int i = 0; i < interfaces.length; i++){
            s.append(interfaces[i]);
            if(i != interfaces.length-1)
                s.append(",");
            else
                s.append(".\n");
        }

        return s.toString();
    }
}