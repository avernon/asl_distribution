/*******************************************************************************
*  Copyright (c) AllSeen Alliance. All rights reserved.
*
*     Contributed by Qualcomm Connected Experiences, Inc.,
*     with authorization from the AllSeen Alliance, Inc.
*     
*     Licensed under the Apache License, Version 2.0 (the "License");
*     you may not use this file except in compliance with the License.
*     You may obtain a copy of the License at
*     
*         http://www.apache.org/licenses/LICENSE-2.0
*     
*     Unless required by applicable law or agreed to in writing, software
*     distributed under the License is distributed on an "AS IS" BASIS,
*     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*     See the License for the specific language governing permissions and
*     limitations under the License.
*     
*     Pursuant to Section 1 of the License, the work of authorship constituting
*     a Work and any Contribution incorporated in the Work shall mean only that
*     Contributor's code submissions authored by that Contributor.  Any rights
*     granted under the License are conditioned upon acceptance of these
*     clarifications.
*******************************************************************************/
package org.alljoyn.validation.testing.suites.controller.alljoyn;

import java.util.Map;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.Variant;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.bus.annotation.BusProperty;

public class ControllerServicePulseEffectBusObject implements BusObject, ControllerServicePulseEffectBusInterface
{
    @BusProperty(signature="u")
    public int getVersion() throws BusException
    {
        return 0;
    }

    @BusMethod(replySignature = "uas")
    public GetAllPulseEffectIDsValues GetAllPulseEffectIDs() throws BusException
    {
        return null;
    }

    @BusMethod(signature = "ss", replySignature = "usss")
    public GetPulseEffectNameValues GetPulseEffectName(String pulseEffectID, String language) throws BusException
    {
        return null;
    }

    @BusMethod(signature = "sss", replySignature = "uss")
    public SetPulseEffectNameValues SetPulseEffectName(String pulseEffectID, String pulseEffectName, String language) throws BusException
    {
        return null;
    }

    @BusMethod(signature = "a{sv}uuua{sv}ssss", replySignature = "us")
    public PulseEffectValues CreatePulseEffect(Map<String, Variant> toLampState, int pulsePeriod, int pulseDuration, int numPulses, Map<String, Variant> fromLampState, String toPresetID, String fromPresetID, String pulseEffectName, String language) throws BusException
    {
        return null;
    }

    @BusMethod(signature = "sa{sv}uuua{sv}ss", replySignature = "us")
    public PulseEffectValues UpdatePulseEffect(String pulseEffectID, Map<String, Variant> toLampState, int pulsePeriod, int pulseDuration, int numPulses, Map<String, Variant> fromLampState, String toPresetID, String fromPresetID)throws BusException
    {
        return null;
    }

    @BusMethod(signature = "s", replySignature = "us")
    public PulseEffectValues DeletePulseEffect(String pulseEffectID) throws BusException
    {
        return null;
    }

    @BusMethod(signature = "s", replySignature = "usa{sv}su")
    public GetPulseEffectValues GetPulseEffect(String pulseEffectID) throws BusException
    {
        return null;
    }

    @BusMethod(signature = "sas", replySignature = "usas")
    public ApplyPulseEffectOnLampsValues ApplyPulseEffectOnLamps(String pulseEffectID, String[] lampIDs) throws BusException
    {
        return null;
    }

    @BusMethod(signature = "sas", replySignature = "usas")
    public ApplyPulseEffectOnLampGroupsValues ApplyPulseEffectOnLampGroups(String pulseEffectID, String[] lampGroupIDs) throws BusException
    {
        return null;
    }

    @BusSignal()
    public void PulseEffectsNameChanged(String[] pulseEffectIDs) throws BusException
    {
    }

    @BusSignal()
    public void PulseEffectsCreated(String[] pulseEffectIDs) throws BusException
    {
    }

    @BusSignal()
    public void PulseEffectsUpdated(String[] pulseEffectIDs) throws BusException
    {
    }

    @BusSignal()
    public void PulseEffectsDeleted(String[] pulseEffectIDs) throws BusException
    {
    }
}
