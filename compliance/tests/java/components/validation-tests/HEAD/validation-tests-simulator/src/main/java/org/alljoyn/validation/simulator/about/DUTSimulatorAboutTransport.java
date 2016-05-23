/*******************************************************************************
 *  Copyright AllSeen Alliance. All rights reserved.
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
package org.alljoyn.validation.simulator.about;

import java.util.List;
import java.util.Map;

import org.alljoyn.about.AboutService;
import org.alljoyn.about.transport.AboutTransport;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.ErrorReplyBusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.services.common.BusObjectDescription;
import org.alljoyn.validation.simulator.DUTSimulator;

public class DUTSimulatorAboutTransport implements AboutTransport
{
    private DUTSimulator dutSimulator;

    public DUTSimulatorAboutTransport(DUTSimulator dutSimulator)
    {
        this.dutSimulator = dutSimulator;
    }

    @Override
    @BusProperty(signature = "q")
    public short getVersion() throws BusException
    {
        return AboutService.PROTOCOL_VERSION;
    }

    @Override
    @BusMethod(signature = "s", replySignature = "a{sv}")
    public Map<String, Variant> GetAboutData(String languageTag) throws BusException
    {
        Map<String, Variant> aboutMap = dutSimulator.getAbout(languageTag);
        if (aboutMap == null)
        {
            throw new ErrorReplyBusException("org.alljoyn.Error.LanguageNotSupported", "The language specified is not supported");
        }
        return aboutMap;
    }

    @Override
    @BusMethod(replySignature = "a(oas)")
    public BusObjectDescription[] GetObjectDescription() throws BusException
    {
        List<BusObjectDescription> supportedInterfaces = dutSimulator.getSupportedInterfaces();
        return supportedInterfaces.toArray(new BusObjectDescription[supportedInterfaces.size()]);
    }

    @Override
    @BusSignal(signature = "qqa(oas)a{sv}")
    public void Announce(short version, short port, BusObjectDescription[] objectDescriptions, Map<String, Variant> serviceMetadata)
    {
    }
}