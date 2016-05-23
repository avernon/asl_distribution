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
package org.alljoyn.validation.testing.suites.eventsactions;

import static org.mockito.Mockito.when;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.ProxyBusObject;
import org.alljoyn.bus.ifaces.AllSeenIntrospectable;
import org.alljoyn.validation.testing.suites.MyRobolectricTestRunner;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.robolectric.annotation.Config;

@RunWith(MyRobolectricTestRunner.class)
@Config(manifest = Config.NONE)
public class EventsActionsTestSuiteTest
{

    @Mock
    private ProxyBusObject mockProxyObj;
    @Mock
    private AllSeenIntrospectable mockInstropectable;

    private String xmlStringEn = "<node name=\"/testNode\"><description>description [en]</description><interface><description>Events [en]</description>"
            + "<property name=\"Version\" type=\"q\" access=\"read\"/><signal name=\"sampleSignal\" sessionless=\"true\"><description>Signal description [en]</description>"
            + "</signal></interface><interface><description>Actions [en]</description><property name=\"Version\" type=\"q\" access=\"read\"/><method name=\"sampleAction\">"
            + "<description>Sample Action description</description></method></interface></node>";
    private String xmlStringEs = "<node name=\"/testNode\"><description>description [es]</description><interface><description>Events [es]</description>"
            + "<property name=\"Version\" type=\"q\" access=\"read\"/><signal name=\"sampleSignal\" sessionless=\"true\"><description>Signal description [es]</description>"
            + "</signal></interface><interface><description>Actions [es]</description><property name=\"Version\" type=\"q\" access=\"read\"/><method name=\"sampleAction\">"
            + "<description>Sample Action description</description></method></interface></node>";
    private String xmlStringEnWithAttribute = "<node name=\"/testNode\"><description language=\"en\">description [en]</description><interface><description language=\"en\">Events [en]</description>"
            + "<property name=\"Version\" type=\"q\" access=\"read\"/><signal name=\"sampleSignal\" sessionless=\"true\"><description language=\"en\">Signal description [en]</description>"
            + "</signal></interface><interface><description language=\"en\">Actions [en]</description><property name=\"Version\" type=\"q\" access=\"read\"/><method name=\"sampleAction\">"
            + "<description language=\"en\">Sample Action description</description></method></interface></node>";
    private String xmlStringEsWithAttribute = "<node name=\"/testNode\"><description language=\"es\">description [es]</description><interface><description language=\"es\">Evests [es]</description>"
            + "<property name=\"Version\" type=\"q\" access=\"read\"/><signal name=\"sampleSignal\" sessionless=\"true\"><description language=\"es\">Signal description [es]</description>"
            + "</signal></interface><interface><description language=\"es\">Actions [es]</description><property name=\"Version\" type=\"q\" access=\"read\"/><method name=\"sampleAction\">"
            + "<description language=\"es\">Sample Action description</description></method></interface></node>";

    @Before
    public void setup() throws Exception
    {
        MockitoAnnotations.initMocks(this);
    }

    @Test
    public void testObjectValidityPerLanguages() throws BusException
    {
        EventsActionsTestSuite testSuite = new EventsActionsTestSuite()
        {
            boolean testChildrenObjectValidity(String parentObjectPath, String parentIntroXML)
            {
                return true;
            };
        };

        String descLangs[] =
        { "en", "es" };

        when(mockProxyObj.getInterface(AllSeenIntrospectable.class)).thenReturn(mockInstropectable);
        when(mockInstropectable.IntrospectWithDescription("en")).thenReturn(xmlStringEn);
        when(mockInstropectable.IntrospectWithDescription("es")).thenReturn(xmlStringEs);
        testSuite.testObjectValidityPerLanguages(mockProxyObj, "", descLangs);

        when(mockInstropectable.IntrospectWithDescription("en")).thenReturn(xmlStringEnWithAttribute);
        when(mockInstropectable.IntrospectWithDescription("es")).thenReturn(xmlStringEsWithAttribute);
        testSuite.testObjectValidityPerLanguages(mockProxyObj, "", descLangs);

    }
}
