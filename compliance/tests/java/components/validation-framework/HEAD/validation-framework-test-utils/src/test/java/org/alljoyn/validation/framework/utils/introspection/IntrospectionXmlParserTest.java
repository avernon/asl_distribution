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
package org.alljoyn.validation.framework.utils.introspection;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;
import static org.mockito.Mockito.when;

import java.net.URL;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.alljoyn.validation.framework.utils.introspection.IntrospectionXmlParser;
import org.alljoyn.validation.framework.utils.introspection.bean.IntrospectionInterface;
import org.alljoyn.validation.framework.utils.introspection.bean.IntrospectionNode;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;
import org.mockito.runners.MockitoJUnitRunner;
import org.xml.sax.XMLReader;

@RunWith(MockitoJUnitRunner.class)
public class IntrospectionXmlParserTest
{
    @Mock
    private SAXParserFactory saxParserFactory;
    @Mock
    private SAXParser saxParser;
    @Mock
    private XMLReader xmlReader;

    private URL url;

    @Before
    public void setUp() throws Exception
    {
        url = ClassLoader.getSystemResource("test.xml");
        when(saxParserFactory.newSAXParser()).thenReturn(saxParser);
        when(saxParser.getXMLReader()).thenReturn(xmlReader);
    }

    @Test
    public void parserIntrospectionNodeXml() throws Exception
    {
        IntrospectionXmlParser testMetadataXmlParser = new IntrospectionXmlParser();

        URL url = ClassLoader.getSystemResource("testIntrospectionNode.xml");
        IntrospectionNode introspectionNode = testMetadataXmlParser.parseXML(url.openStream());

        assertNotNull(introspectionNode);

        assertEquals("/org/freedesktop/sample_object", introspectionNode.getName());
        assertEquals(2, introspectionNode.getSubNodes().size());
        assertEquals(1, introspectionNode.getInterfaces().size());

        IntrospectionInterface iface = introspectionNode.getInterfaces().get(0);
        assertEquals("org.freedesktop.SampleInterface", iface.getName());
        assertEquals(1, iface.getSignals().size());
        assertEquals(3, iface.getMethods().size());
        assertEquals(1, iface.getProperties().size());
    }

    @Test
    public void parserTestXml() throws Exception
    {
        IntrospectionXmlParser testMetadataXmlParser = new IntrospectionXmlParser();
        IntrospectionNode introspectionNode = testMetadataXmlParser.parseXML(url.openStream());

        assertNotNull(introspectionNode);

        assertNull(introspectionNode.getName());
        assertEquals(2, introspectionNode.getSubNodes().size());
        assertEquals(4, introspectionNode.getInterfaces().size());

        IntrospectionInterface iface = introspectionNode.getInterfaces().get(0);
        assertEquals("org.alljoyn.Control.TV.LG", iface.getName());
        assertEquals(1, iface.getSignals().size());
        assertEquals(5, iface.getMethods().size());
        assertEquals(5, iface.getProperties().size());
    }
}
