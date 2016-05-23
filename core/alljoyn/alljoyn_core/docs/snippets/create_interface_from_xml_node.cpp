/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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
 ******************************************************************************/
/*
 * The following code was developed with the documentation. Please don't modify
 * this code unless fixing errors in the code or documentation.
 */
/*
 * This sample demonstrates how to create and add an alljoyn interface.
 */

#include <cstdio>

#include <alljoyn/BusAttachment.h>
#include <alljoyn/Init.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/Status.h>

/// [xml_node_adding_namespace]
namespace com {
namespace example {
static const char* name = "com.example.interface";
static const char* node = "<node name='/example/xml/interface'>"
                          "  <interface name='com.example.interface'>"
                          "    <method name='Echo'>"
                          "      <arg name='input_arg' type='s' direction='in' />"
                          "      <arg name='return_arg' type='s' direction='out' />"
                          "    </method>"
                          "    <signal name='Chirp'>"
                          "      <arg name='sound' type='s' />"
                          "    </signal>"
                          "    <property name='Volume' type='i' access='readwrite'/>"
                          "  </interface>"
                          "</node>";
}
}
/// [xml_node_adding_namespace]

using namespace ajn;

int CDECL_CALL main()
{
    if (AllJoynInit() != ER_OK) {
        return 1;
    }
#ifdef ROUTER
    if (AllJoynRouterInit() != ER_OK) {
        AllJoynShutdown();
        return 1;
    }
#endif
    {
        BusAttachment busAttachment("AddInterfaceFromXml");

        /// [xml_node_adding_to_busattachment]
        QStatus status = busAttachment.CreateInterfacesFromXml(::com::example::node);
        if (status != ER_OK) {
            // error handling code goes here
            printf("Failed to create %s\n interface from an xml node", ::com::example::name);
        } else {
            printf("%s has been created from xml node\n", ::com::example::name);
        }
        /// [xml_node_adding_to_busattachment]

        const InterfaceDescription* interfaceFromBus = busAttachment.GetInterface(::com::example::name);
        if (interfaceFromBus == NULL) {
            printf("Failed to Get %s\n", ::com::example::name);
        } else {
            printf("Read the %s interface back from the busAttachment.\n%s\n", ::com::example::name, interfaceFromBus->Introspect().c_str());
        }
    }
#ifdef ROUTER
    AllJoynRouterShutdown();
#endif
    AllJoynShutdown();
    return 0;
}
