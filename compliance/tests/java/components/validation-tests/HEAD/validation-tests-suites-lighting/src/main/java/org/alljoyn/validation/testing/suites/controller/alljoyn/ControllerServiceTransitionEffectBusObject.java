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

public class ControllerServiceTransitionEffectBusObject implements BusObject, ControllerServiceTransitionEffectBusInterface
{
    @BusProperty(signature="u")
    public int getVersion() throws BusException
    {
        return 0;
    }

    @BusMethod(replySignature = "uas")
    public GetAllTransitionEffectIDsValues GetAllTransitionEffectIDs() throws BusException
    {
        return null;
    }

    @BusMethod(signature = "ss", replySignature = "usss")
    public GetTransitionEffectNameValues GetTransitionEffectName(String transitionEffectID, String language) throws BusException
    {
        return null;
    }

    @BusMethod(signature = "sss", replySignature = "uss")
    public SetTransitionEffectNameValues SetTransitionEffectName(String transitionEffectID, String transitionEffectName, String language) throws BusException
    {
        return null;
    }

    @BusMethod(signature = "a{sv}suss", replySignature = "us")
    public TransitionEffectValues CreateTransitionEffect(Map<String, Variant> lampState, String presetID, int transitionPeriod, String transitionEffectName, String language) throws BusException{
        return null;
    }

    @BusMethod(signature = "sa{sv}su", replySignature = "us")
    public TransitionEffectValues UpdateTransitionEffect(String transitionEffectID, Map<String, Variant> lampState, String presetID, int transitionPeriod) throws BusException
    {
        return null;
    }

    @BusMethod(signature = "s", replySignature = "us")
    public TransitionEffectValues DeleteTransitionEffect(String transitionEffectID) throws BusException
    {
        return null;
    }

    @BusMethod(signature = "s", replySignature = "usa{sv}su")
    public GetTransitionEffectValues GetTransitionEffect(String transitionEffectID) throws BusException
    {
        return null;
    }

    @BusMethod(signature = "sas", replySignature = "usas")
    public ApplyTransitionEffectOnLampsValues ApplyTransitionEffectOnLamps(String transitionEffectID, String[] lampIDs) throws BusException
    {
        return null;
    }

    @BusMethod(signature = "sas", replySignature = "usas")
    public ApplyTransitionEffectOnLampGroupsValues ApplyTransitionEffectOnLampGroups(String transitionEffectID, String[] lampGroupIDs) throws BusException
    {
        return null;
    }

    @BusSignal()
    public void TransitionEffectsNameChanged(String[] transitionEffectIDs) throws BusException
    {
    }

    @BusSignal()
    public void TransitionEffectsCreated(String[] transitionEffectIDs) throws BusException
    {
    }

    @BusSignal()
    public void TransitionEffectsUpdated(String[] transitionEffectIDs) throws BusException
    {
    }

    @BusSignal()
    public void TransitionEffectsDeleted(String[] transitionEffectIDs) throws BusException
    {
    }

}
