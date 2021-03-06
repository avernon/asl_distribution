/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#include <alljoyn/gateway/GatewayConnectorAppManifest.h>
#include <alljoyn/gateway/GatewayMgmt.h>
#include <fstream>
#include "GatewayConstants.h"
#include <libxml/xmlschemas.h>

namespace ajn {
namespace gw {
using namespace gwConsts;

GatewayConnectorAppManifest::GatewayConnectorAppManifest() : m_ManifestData(""), m_PackageName(""), m_FriendlyName(""),
    m_ExecutableName(""), m_Version(""), m_MinAjSdkVersion("")
{
}

GatewayConnectorAppManifest::~GatewayConnectorAppManifest()
{
}

const qcc::String& GatewayConnectorAppManifest::getFriendlyName() const
{
    return m_FriendlyName;
}

const qcc::String& GatewayConnectorAppManifest::getMinAjSdkVersion() const
{
    return m_MinAjSdkVersion;
}

const qcc::String& GatewayConnectorAppManifest::getPackageName() const
{
    return m_PackageName;
}

const qcc::String& GatewayConnectorAppManifest::getVersion() const
{
    return m_Version;
}

const qcc::String& GatewayConnectorAppManifest::getManifestData() const
{
    return m_ManifestData;
}

const GatewayConnectorAppManifest::Capabilities& GatewayConnectorAppManifest::getExposedServices() const
{
    return m_ExposedServices;
}

const GatewayConnectorAppManifest::Capabilities& GatewayConnectorAppManifest::getRemotedServices() const
{
    return m_RemotedServices;
}

const std::vector<qcc::String>& GatewayConnectorAppManifest::getEnvironmentVariables() const
{
    return m_EnvironmentVariables;
}

const qcc::String& GatewayConnectorAppManifest::getExecutableName() const
{
    return m_ExecutableName;
}

const std::vector<qcc::String>& GatewayConnectorAppManifest::getAppArguments() const
{
    return m_AppArguments;
}

QStatus GatewayConnectorAppManifest::parseManifestFile(qcc::String const& manifestFileName)
{
    std::ifstream ifs(manifestFileName.c_str());
    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));

    if (content.empty()) {
        QCC_DbgHLPrintf(("Could not read ManifestFile"));
        return ER_READ_ERROR;
    }

    m_ManifestData.assign(content.c_str());

    xmlDocPtr doc = xmlParseMemory(content.c_str(), content.size());
    if (doc == NULL) {
        QCC_DbgHLPrintf(("Could not parse XML from memory"));
        return ER_XML_MALFORMED;
    }

    xmlSchemaParserCtxtPtr parserCtxt = xmlSchemaNewParserCtxt(GATEWAY_XML_XSD.c_str());
    if (parserCtxt == NULL) {
        QCC_DbgHLPrintf(("Could not create xmlSchemaParserCtxtPtr"));
        xmlFreeDoc(doc);
        return ER_FAIL;
    }

    xmlSchemaPtr schema = xmlSchemaParse(parserCtxt);
    if (schema == NULL) {
        QCC_DbgHLPrintf(("Could not create xmlSchemaPtr"));
        xmlFreeDoc(doc);
        xmlSchemaFreeParserCtxt(parserCtxt);
        return ER_FAIL;
    }

    xmlSchemaValidCtxtPtr validCtxt = xmlSchemaNewValidCtxt(schema);
    if (!validCtxt) {
        QCC_DbgHLPrintf(("Could not create xmlSchemaValidCtxtPtr"));
        xmlFreeDoc(doc);
        xmlSchemaFreeParserCtxt(parserCtxt);
        xmlSchemaFree(schema);
        return ER_FAIL;
    }

    int result = xmlSchemaValidateDoc(validCtxt, doc);
    if (result != 0) {
        QCC_DbgHLPrintf(("Schema Validation failed. result is %i", result));
        xmlFreeDoc(doc);
        xmlSchemaFreeParserCtxt(parserCtxt);
        xmlSchemaFree(schema);
        xmlSchemaFreeValidCtxt(validCtxt);
        return ER_BUS_BAD_XML;
    }

    xmlNode* root_element = xmlDocGetRootElement(doc);
    for  (xmlNode* currentKey = root_element->children; currentKey != NULL; currentKey = currentKey->next) {

        if (currentKey->type != XML_ELEMENT_NODE || currentKey->children == NULL) {
            continue;
        }

        const xmlChar* keyName = currentKey->name;
        const xmlChar* value = currentKey->children->content;

        if (xmlStrEqual(keyName, (const xmlChar*)"friendlyName")) {
            m_FriendlyName.assign((const char*)value);
        } else if (xmlStrEqual(keyName, (const xmlChar*)"packageName")) {
            m_PackageName.assign((const char*)value);
        } else if (xmlStrEqual(keyName, (const xmlChar*)"version")) {
            m_Version.assign((const char*)value);
        } else if (xmlStrEqual(keyName, (const xmlChar*)"minAjSdkVersion")) {
            m_MinAjSdkVersion.assign((const char*)value);
        } else if (xmlStrEqual(keyName, (const xmlChar*)"exposedServices")) {
            parseObjects(currentKey, m_ExposedServices);
        } else if (xmlStrEqual(keyName, (const xmlChar*)"remotedServices")) {
            parseObjects(currentKey, m_RemotedServices);
        } else if (xmlStrEqual(keyName, (const xmlChar*)"executionInfo")) {
            parseExecutionInfo(currentKey);
        }
    }

    xmlFreeDoc(doc);
    xmlSchemaFreeParserCtxt(parserCtxt);
    xmlSchemaFree(schema);
    xmlSchemaFreeValidCtxt(validCtxt);
    return ER_OK;
}

void GatewayConnectorAppManifest::parseObjects(xmlNode* currentKey, Capabilities& capabilities)
{
    for (xmlNode* objectKey = currentKey->children; objectKey != NULL; objectKey = objectKey->next) {

        if (objectKey->type != XML_ELEMENT_NODE || objectKey->children == NULL) {
            continue;
        }

        qcc::String objectPath = "";
        xmlChar*xmlObjectFriendly = xmlGetProp(objectKey, (const xmlChar*)"name");
        qcc::String objectFriendly = (const char*)xmlObjectFriendly;
        xmlFree(xmlObjectFriendly);
        bool isPrefix = false;
        std::vector<GatewayConnectorAppCapability::InterfaceDesc> interfaces;

        for  (xmlNode* objectPathKey = objectKey->children; objectPathKey != NULL; objectPathKey = objectPathKey->next) {

            if (objectPathKey->type != XML_ELEMENT_NODE || objectPathKey->children == NULL) {
                continue;
            }

            const xmlChar* objectPathKeyName = objectPathKey->name;

            if (xmlStrEqual(objectPathKeyName, (const xmlChar*)"path")) {
                objectPath.assign((const char*)objectPathKey->children->content);
                continue;
            }

            if (xmlStrEqual(objectPathKeyName, (const xmlChar*)"isPrefix")) {
                if (strcmp((const char*)objectPathKey->children->content, "true") == 0) {
                    isPrefix = true;
                }
                continue;
            }

            if (!xmlStrEqual(objectPathKeyName, (const xmlChar*)"interfaces")) {
                continue;
            }

            for  (xmlNode* interfaceKey = objectPathKey->children; interfaceKey != NULL; interfaceKey = interfaceKey->next) {

                if (interfaceKey->type != XML_ELEMENT_NODE || interfaceKey->children == NULL) {
                    continue;
                }

                bool isSecured = false;

                xmlChar*xmlInterfaceFriendly = xmlGetProp(interfaceKey, (const xmlChar*)"name");
                qcc::String interfaceFriendly = (const char*)xmlInterfaceFriendly;
                xmlFree(xmlInterfaceFriendly);
                qcc::String interfaceName = (const char*)interfaceKey->children->content;
                xmlChar*xmlSecured = xmlGetProp(interfaceKey, (const xmlChar*)"secured");
                qcc::String secured = (const char*)xmlSecured;
                xmlFree(xmlSecured);

                if (secured.compare("true") == 0) {
                    isSecured = true;
                }

                GatewayConnectorAppCapability::InterfaceDesc interface;
                interface.interfaceName = interfaceName;
                interface.interfaceFriendlyName = interfaceFriendly;
                interface.isSecured = isSecured;
                interfaces.push_back(interface);
            }
        }

        GatewayConnectorAppCapability capability(objectPath, objectFriendly, isPrefix, interfaces);
        capabilities.push_back(capability);
    }
}

void GatewayConnectorAppManifest::parseExecutionInfo(xmlNode* currentKey)
{
    for  (xmlNode* execInfoKey = currentKey->children; execInfoKey != NULL; execInfoKey = execInfoKey->next) {

        if (execInfoKey->type != XML_ELEMENT_NODE || execInfoKey->children == NULL) {
            continue;
        }

        const xmlChar* execInfoKeyName = execInfoKey->name;

        if (xmlStrEqual(execInfoKeyName, (const xmlChar*)"executable")) {
            m_ExecutableName.assign((const char*)execInfoKey->children->content);
            continue;
        } else if (xmlStrEqual(execInfoKeyName, (const xmlChar*)"env_variables")) {
            for  (xmlNode* envVariableKey = execInfoKey->children; envVariableKey != NULL; envVariableKey = envVariableKey->next) {
                if (envVariableKey->type != XML_ELEMENT_NODE || envVariableKey->children == NULL) {
                    continue;
                }
                xmlChar*xmlVariableName = xmlGetProp(envVariableKey, (const xmlChar*)"name");
                qcc::String variableName = (const char*)xmlVariableName;
                xmlFree(xmlVariableName);
                qcc::String variableValue = (const char*)envVariableKey->children->content;
                m_EnvironmentVariables.push_back(variableName + "=" + variableValue);
            }
        } else if (xmlStrEqual(execInfoKeyName, (const xmlChar*)"arguments")) {
            for  (xmlNode* argumentKey = execInfoKey->children; argumentKey != NULL; argumentKey = argumentKey->next) {
                if (argumentKey->type != XML_ELEMENT_NODE || argumentKey->children == NULL) {
                    continue;
                }
                qcc::String argValue = (const char*)argumentKey->children->content;
                m_AppArguments.push_back(argValue);
            }
        }
    }
}

} /* namespace gw */
} /* namespace ajn */
