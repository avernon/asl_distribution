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

#ifndef GATEWAYAPPMANIFEST_H_
#define GATEWAYAPPMANIFEST_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/gateway/GatewayConnectorAppCapability.h>
#include <libxml/tree.h>
#include <map>
#include <vector>

namespace ajn {
namespace gw {

/**
 * Class used to parse a Manifest file for an App and store its data
 */
class GatewayConnectorAppManifest {

  public:

    /**
     * typedef to define a Manifest Permissions Vector.
     */
    typedef std::vector<GatewayConnectorAppCapability> Capabilities;

    /**
     * Constructor for GatewayConnectorAppManifest
     */
    GatewayConnectorAppManifest();

    /**
     * Destructor for GatewayConnectorAppManifest
     */
    virtual ~GatewayConnectorAppManifest();

    /**
     * Parse the ManifestFile and use it to fill this class
     * @param manifestFileName - name of file
     * @return success/failure
     */
    QStatus parseManifestFile(qcc::String const& manifestFileName);

    /**
     * Get the FriendlyName
     * @return friendlyName
     */
    const qcc::String& getFriendlyName() const;

    /**
     * Get the Minimum AJ-Sdk version
     * @return minAjSdkVersion
     */
    const qcc::String& getMinAjSdkVersion() const;

    /**
     * Get the packageName
     * @return packageName
     */
    const qcc::String& getPackageName() const;

    /**
     * Get the Version
     * @return version
     */
    const qcc::String& getVersion() const;

    /**
     * Get the ManifestData
     * @return manifestData
     */
    const qcc::String& getManifestData() const;

    /**
     * Get the ExposedServices
     * @return exposedServices
     */
    const Capabilities& getExposedServices() const;

    /**
     * Get the RemotedServices
     * @return remotedServices
     */
    const Capabilities& getRemotedServices() const;

    /**
     * Get the Environment Variables of the App
     * @return environment variables
     */
    const std::vector<qcc::String>& getEnvironmentVariables() const;

    /**
     * Get the Executable Name of the App
     * @return executable Name
     */
    const qcc::String& getExecutableName() const;

    /**
     * Get the Applications Arguments
     * @return arguments
     */
    const std::vector<qcc::String>& getAppArguments() const;

  private:

    /**
     * ManifestData of the App
     */
    qcc::String m_ManifestData;

    /**
     * PackageNAme of the App
     */
    qcc::String m_PackageName;

    /**
     * FriendlyName of the App
     */
    qcc::String m_FriendlyName;

    /**
     * ExecutableName of the App
     */
    qcc::String m_ExecutableName;

    /**
     * Version of the App
     */
    qcc::String m_Version;

    /**
     * MinAjSdkVersion of the App
     */
    qcc::String m_MinAjSdkVersion;

    /**
     * Environment Variables of the App
     */
    std::vector<qcc::String> m_EnvironmentVariables;

    /**
     * Application's arguments
     */
    std::vector<qcc::String> m_AppArguments;

    /**
     * ExposedServices of the App
     */
    Capabilities m_ExposedServices;

    /**
     * RemotedServices of the App
     */
    Capabilities m_RemotedServices;

    /**
     * parseObjects - internal function to help parse the objects
     * @param currentKey - current key in parser
     * @param permissionsMap - map to fill
     */
    void parseObjects(xmlNode* currentKey, Capabilities& capabilitiesMap);

    /**
     * parseExecutionInfo - internal function to help parse the parseExecutionInfo
     * @param currentKey - current key in parser
     */
    void parseExecutionInfo(xmlNode* currentKey);

};

} /* namespace gw */
} /* namespace ajn */
#endif /* GATEWAYAPPMANIFEST_H_ */
