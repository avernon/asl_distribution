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

public class ControllerServiceTransitionEffectSignalHandler
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

    @BusSignalHandler(iface = "org.allseen.LSF.ControllerService.TransitionEffect", signal = "TransitionEffectsNameChanged")
    public void TransitionEffectsNameChanged(String[] transitionEffectIDs)
    {
        if (signalListener != null)
        {
            signalListener.handleTransitionEffectsNameChanged(transitionEffectIDs);
        }
    }

    @BusSignalHandler(iface = "org.allseen.LSF.ControllerService.TransitionEffect", signal = "TransitionEffectsCreated")
    public void TransitionEffectsCreated(String[] transitionEffectIDs)
    {
        if (signalListener != null)
        {
            signalListener.handleTransitionEffectsCreated(transitionEffectIDs);
        }
    }

    @BusSignalHandler(iface = "org.allseen.LSF.ControllerService.TransitionEffect", signal = "TransitionEffectsUpdated")
    public void TransitionEffectsUpdated(String[] transitionEffectIDs)
    {
        if (signalListener != null)
        {
            signalListener.handleTransitionEffectsUpdated(transitionEffectIDs);
        }
    }

    @BusSignalHandler(iface = "org.allseen.LSF.ControllerService.TransitionEffect", signal = "TransitionEffectsDeleted")
    public void TransitionEffectsDeleted(String[] transitionEffectIDs)
    {
        if (signalListener != null)
        {
            signalListener.handleTransitionEffectsDeleted(transitionEffectIDs);
        }
    }
}
