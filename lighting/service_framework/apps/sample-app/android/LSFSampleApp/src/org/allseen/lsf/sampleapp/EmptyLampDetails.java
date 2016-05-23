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

import org.allseen.lsf.BaseType;
import org.allseen.lsf.DeviceType;
import org.allseen.lsf.LampDetails;
import org.allseen.lsf.LampMake;
import org.allseen.lsf.LampModel;
import org.allseen.lsf.LampType;

public class EmptyLampDetails extends LampDetails {
    public static EmptyLampDetails instance = new EmptyLampDetails();

    private EmptyLampDetails()              { }

    //TODO-FIX these should all return null when superclass methods are defined to all return objects
    @Override
    public LampMake getMake()               { return null; }
    @Override
    public LampModel getModel()             { return null; }
    @Override
    public DeviceType getType()             { return null; }
    @Override
    public LampType getLampType()           { return null; }
    @Override
    public BaseType getLampBaseType()       { return null; }
    @Override
    public int getLampBeamAngle()           { return 0; }
    @Override
    public boolean isDimmable()             { return false; }
    @Override
    public boolean hasColor()               { return false; }
    @Override
    public boolean hasVariableColorTemp()   { return false; }
    @Override
    public boolean hasEffects()             { return false; }
    @Override
    public int getMinVoltage()              { return 0; }
    @Override
    public int getMaxVoltage()              { return 0; }
    @Override
    public int getWattage()                 { return 0; }
    @Override
    public int getIncandescentEquivalent()  { return 0; }
    @Override
    public int getMaxLumens()               { return 0; }
    @Override
    public int getMinTemperature()          { return 0; }
    @Override
    public int getMaxTemperature()          { return 0; }
    @Override
    public int getColorRenderingIndex()     { return 0; }
    @Override
    public String getLampID()               { return null; }
}
