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

#include <alljoyn/gateway/GatewayAppIdentifier.h>
#include <alljoyn/Status.h>
#include <map>

#ifndef GATEWAYMETADATAMANAGER_H_
#define GATEWAYMETADATAMANAGER_H_

namespace ajn {
namespace gw {

/**
 * Class that manages the Metadata
 */
class GatewayMetadataManager {

  public:

    /**
     * Constructor for MetadataManager
     */
    GatewayMetadataManager();

    /**
     * Destructor for MetadataManager
     */
    virtual ~GatewayMetadataManager();

    /**
     * Initialize the MetadataManager
     * @return status - success/failure
     */
    QStatus init();

    /**
     * Cleanup the MetadataManager
     * @return status - success/failure
     */
    QStatus cleanup();

    /**
     * Update the metadata
     * @param metadata - metadata to update
     * @return status - success/failure
     */
    QStatus updateMetadata(std::map<qcc::String, qcc::String> const& metadata);

    /**
     * add MetadataValues to metadata map based on key passed in
     * @param key - the key to add metadata for
     * @param metadata - the map to add the Metadata to
     */
    void addMetadataValues(GatewayAppIdentifier const& key, std::map<qcc::String, qcc::String>* metadata);

    /**
     * Increase the Reference Count for a Remote App
     * @param key - key to add Reference Count
     */
    void incRemoteAppRefCount(GatewayAppIdentifier const& key);

  private:

    /**
     * Class that stores MetadataValues.
     * AppName, DeviceName, and RefCount which is used during cleanup
     */
    class MetadataValues {

      public:

        qcc::String appNameKey;
        qcc::String deviceNameKey;
        qcc::String appName;
        qcc::String deviceName;
        int refCount;

        MetadataValues(qcc::String const& appKey, qcc::String const& deviceKey,
                       qcc::String const& app, qcc::String const& device) :
            appNameKey(appKey), deviceNameKey(deviceKey), appName(app), deviceName(device), refCount(0) { }
    };

    /**
     * Metadata being managed
     */
    std::map<GatewayAppIdentifier, MetadataValues> m_Metadata;

    /**
     * Write Metadata to file
     * @return status - success/failure
     */
    QStatus writeToFile();

};

} /* namespace gw */
} /* namespace ajn */

#endif /* GATEWAYMETADATAMANAGER_H_ */
