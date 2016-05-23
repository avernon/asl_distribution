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

import org.alljoyn.bus.annotation.BusSignalHandler;
import org.alljoyn.validation.testing.suites.controller.ControllerServiceSignalListener;

public class ControllerServicePulseEffectSignalHandler
{
    static
    {
        System.loadLibrary("alljoyn_java");
    }

    private ControllerServiceSignalListener signalListener;

    public void setUpdateListener(ControllerServiceSignalListener listener)
    {
        signalListener = listener;
    }

    @BusSignalHandler(iface = "org.allseen.LSF.ControllerService.PulseEffect", signal = "PulseEffectsNameChanged")
    public void PulseEffectsNameChanged(String[] pulseEffectIDs)
    {
        if (signalListener != null)
        {
            signalListener.handlePulseEffectsNameChanged(pulseEffectIDs);
        }
    }

    @BusSignalHandler(iface = "org.allseen.LSF.ControllerService.PulseEffect", signal = "PulseEffectsCreated")
    public void PulseEffectsCreated(String[] pulseEffectIDs)
    {
        if (signalListener != null)
        {
            signalListener.handlePulseEffectsCreated(pulseEffectIDs);
        }
    }

    @BusSignalHandler(iface = "org.allseen.LSF.ControllerService.PulseEffect", signal = "PulseEffectsUpdated")
    public void PulseEffectsUpdated(String[] pulseEffectIDs)
    {
        if (signalListener != null)
        {
            signalListener.handlePulseEffectsUpdated(pulseEffectIDs);
        }
    }

    @BusSignalHandler(iface = "org.allseen.LSF.ControllerService.PulseEffect", signal = "PulseEffectsDeleted")
    public void PulseEffectsDeleted(String[] pulseEffectIDs)
    {
        if (signalListener != null)
        {
            signalListener.handlePulseEffectsDeleted(pulseEffectIDs);
        }
    }
}
