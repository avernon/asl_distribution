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
import java.util.List;

import javax.xml.parsers.ParserConfigurationException;

import org.alljoyn.bus.BusException;
import org.alljoyn.validation.framework.utils.introspection.bean.InterfaceDetail;
import org.alljoyn.validation.framework.utils.introspection.bean.NodeDetail;
import org.xml.sax.SAXException;

public interface BusIntrospector
{
    <T> T getInterface(String path, Class<T> interfaceClass);

    NodeDetail introspect(String path) throws BusException, IOException, ParserConfigurationException, SAXException;

    List<NodeDetail> introspectEntireTree(String path) throws BusException, IOException, ParserConfigurationException, SAXException;

    List<InterfaceDetail> getStandardizedInterfacesExposedOnBus() throws BusException, IOException, ParserConfigurationException, SAXException;

    List<InterfaceDetail> getInterfacesExposedOnBusBasedOnName(String interfaceName) throws BusException, IOException, ParserConfigurationException, SAXException;

    List<InterfaceDetail> getInterfacesExposedOnBusUnderSpecifiedPathBasedOnName(String path, String interfaceName) throws BusException, IOException, ParserConfigurationException,
            SAXException;

    boolean isInterfacePresent(String path, String interfaceName) throws BusException, IOException, ParserConfigurationException, SAXException;

    boolean isAncestorInterfacePresent(String path, String ancestorInterfaceName) throws BusException, IOException, ParserConfigurationException, SAXException;
}