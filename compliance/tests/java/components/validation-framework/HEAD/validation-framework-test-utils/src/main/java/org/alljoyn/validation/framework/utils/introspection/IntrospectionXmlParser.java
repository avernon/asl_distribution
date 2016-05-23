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

import java.io.IOException;
import java.io.InputStream;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.alljoyn.validation.framework.utils.introspection.bean.IntrospectionNode;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;

public class IntrospectionXmlParser
{
    public IntrospectionNode parseXML(InputStream inputStream) throws IOException, ParserConfigurationException, SAXException
    {
        IntrospectionXmlHandler introspectionXmlHandler = new IntrospectionXmlHandler();
        parse(inputStream, introspectionXmlHandler);
        return introspectionXmlHandler.getIntrospectionNode();
    }

    private void parse(InputStream inputStream, IntrospectionXmlHandler testMetadataXmlHandler) throws IOException, SAXException, ParserConfigurationException
    {
        XMLReader xmlReader = null;
        SAXParserFactory saxParserFactory = getSAXParserFactory();
        saxParserFactory.setNamespaceAware(true);

        SAXParser parser = saxParserFactory.newSAXParser();
        xmlReader = parser.getXMLReader();
        xmlReader.setContentHandler(testMetadataXmlHandler);
        xmlReader.parse(new InputSource(inputStream));
    }

    protected SAXParserFactory getSAXParserFactory()
    {
        SAXParserFactory saxParserFactory = SAXParserFactory.newInstance();
        return saxParserFactory;
    }

}
