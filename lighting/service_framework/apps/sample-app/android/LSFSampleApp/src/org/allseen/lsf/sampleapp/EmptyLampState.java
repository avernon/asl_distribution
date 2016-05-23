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

import org.allseen.lsf.LampState;

public class EmptyLampState extends LampState {
    public static EmptyLampState instance = new EmptyLampState();

    private EmptyLampState() {}

    //TODO-FIX getters should all return null when superclass methods are defined to all return objects
    @Override
    public void setOnOff(boolean onOff)         { /* Do nothing */ }
    @Override
    public boolean getOnOff()                   { return false; }
    @Override
    public void setHue(long hue)                { /* Do nothing */ }
    @Override
    public long getHue()                        { return 0; }
    @Override
    public void setSaturation(long saturation)  { /* Do nothing */ }
    @Override
    public long getSaturation()                 { return 0; }
    @Override
    public void setColorTemp(long colorTemp)    { /* Do nothing */ }
    @Override
    public long getColorTemp()                  { return 0; }
    @Override
    public void setBrightness(long brightness)  { /* Do nothing */ }
    @Override
    public long getBrightness()                 { return 0; }
}
