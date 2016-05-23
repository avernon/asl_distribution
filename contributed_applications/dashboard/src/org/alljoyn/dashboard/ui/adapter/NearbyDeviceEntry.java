/*
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
*/
package org.alljoyn.dashboard.ui.adapter;

import java.util.ArrayList;

import org.alljoyn.dashboard.logic.Interface.Device;

public class NearbyDeviceEntry {

    private String m_nearbyEntryTitle;//In our case: configured or unconfigured
    private int m_textAppearance;
    private final ArrayList<Device> m_devices;

    //=============================================================
    public NearbyDeviceEntry(String title, int textAppearance, ArrayList<Device> devices) {

        m_nearbyEntryTitle = title;
        m_textAppearance = textAppearance;
        m_devices = devices;
    }
    //=============================================================
    public String getTitle(){
        return m_nearbyEntryTitle;
    }
    //=============================================================
    public ArrayList<Device> getDevices(){
        return m_devices;
    }
    //=============================================================
    public void setTitle(String title){
        m_nearbyEntryTitle = title;
    }
    //=============================================================
    public int getTextAppearance()
    {
        return m_textAppearance;
    }
    public void setTextAppearance(int textAppearance)
    {
        m_textAppearance = textAppearance;
    }
}
