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

package org.alljoyn.about.test;

import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import org.alljoyn.about.AboutKeys;
import org.alljoyn.services.common.BusObjectDescription;

/**
 * This class represents an AllJoyn device.
 */
public class SoftAPDetails{

    /**
     * The device id.
     */
    String appId;//The device UUID

    /**
     * The device bus name
     */
    String busName;

    /**
     * The device friendly name
     */
    String deviceFriendlyName;

    /**
     * The device port
     */
    short port;

    /**
     * The device supported interfaces
     */
    BusObjectDescription[] interfaces;

    /**
     * Indicates whether the device support the about service
     */
    boolean supportAbout = false;

    /**
     * Indicates whether the device support the icon service
     */
    boolean supportIcon = false;

    /**
     * Represents the the device about fields as we got in the announcement.
     */
    Map<String, Object> aboutMap;

    /**
     * Represents the device about languages - the language in which the device requests the about data.
     */
    String aboutLanguage = "";

    //===================================================================

    /**
     * Create a device according to the following parameters.
     * @param appId The device id
     * @param busName The device bus name
     * @param deviceFriendlyName The device friendly name
     * @param port The device port
     * @param interfaces The device supported interfaces
     * @param aboutMap The device about fields
     * @param password The device password
     */
    public SoftAPDetails(String appId, String busName, String deviceFriendlyName, short port, BusObjectDescription[] interfaces, Map<String, Object> aboutMap) {

        this.appId = appId;
        this.busName = busName;
        this.deviceFriendlyName = deviceFriendlyName;
        this.port = port;
        this.interfaces = interfaces;
        this.aboutMap = aboutMap;
        if(aboutMap != null){
            this.aboutLanguage = (String) aboutMap.get(AboutKeys.ABOUT_DEFAULT_LANGUAGE);
        }
        updateSupportedServices();
    }
    //===================================================================

    /**
     * Initialize the device supported services according to the device bus object description.
     */
    public void updateSupportedServices(){

        if(interfaces != null){
            for(int i = 0; i < interfaces.length; ++i){
                BusObjectDescription temp = interfaces[i];
                String[] supportedInterfaces = temp.getInterfaces();
                for(int j = 0; j < supportedInterfaces.length; ++j){
                    String interface1 = supportedInterfaces[j];
                    if(interface1.equals("org.alljoyn.About"))
                        this.supportAbout = true;
                    else if(interface1.startsWith("org.alljoyn.Icon"))
                        this.supportIcon = true;

                }
            }
        }
    }
    //===================================================================

    /**
     * @return Returns the device announcement
     */
    public String getAnnounce() {
        StringBuilder sb = new StringBuilder();
        //device name
        sb.append("BusName: "+busName+"\n\n");
        //port
        sb.append("Port: "+port+"\n\n");
        //about map
        if(aboutMap == null){
            sb.append("About map:\n");
            sb.append("About map is null\n");
            sb.append("\n");
        }
        else{
            Set<String> set = aboutMap.keySet();
            sb.append("About map:\n");
            Iterator<String> iterator = set.iterator();
            while (iterator.hasNext()){

                String current = iterator.next();
                Object value = aboutMap.get(current);
                sb.append(current+" : "+value.toString()+"\n");
            }
            sb.append("\n");
        }
        //interfaces
        sb.append("Bus Object Description:\n");
        for(int i = 0; i < interfaces.length; i++){
            sb.append(busObjectDescriptionString(interfaces[i]));
            if(i != interfaces.length-1)
                sb.append("\n");
        }
        return sb.toString();
    }
    //===================================================================
    private String busObjectDescriptionString(BusObjectDescription bus) {

        String s = "";
        s += "path: "+bus.getPath()+"\n";
        s += "interfaces: ";
        String[] tmp = bus.getInterfaces();
        for (int i = 0; i < tmp.length; i++){
            s += tmp[i];
            if(i != tmp.length-1)
                s += ",";
            else
                s += "\n";
        }
        return s;
    }
    //===================================================================
}