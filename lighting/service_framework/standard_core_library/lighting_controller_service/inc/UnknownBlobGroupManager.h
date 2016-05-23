# Contributed by Qualcomm Connected Experiences, Inc.,
# with authorization from the AllSeen Alliance, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Pursuant to Section 1 of the License, the work of authorship constituting
# a Work and any Contribution incorporated in the Work shall mean only that
# Contributor's code submissions authored by that Contributor.  Any rights
# granted under the License are conditioned upon acceptance of these
# clarifications.
#ifndef _UNKNOWN_BLOB_MANAGER_H_
#define _UNKNOWN_BLOB_MANAGER_H_
/**
 * \ingroup ControllerService
 */
/**
 * @file
 * This file provides definitions for unknown blob manager
 */
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

#include <Manager.h>

#include <Mutex.h>
#include <LSFTypes.h>

#include <string>
#include <map>

namespace lsf {

/**
 * class manages a Unknown Blob. \n
 */
class UnknownBlobManager : public Manager {
  public:
    /**
     * class constructor. \n
     * @param controllerSvc - reference to controller service instance
     */
    UnknownBlobManager(ControllerService& controllerSvc, const std::string& unknownBlobFile, uint32_t blobTypeNum);
    /**
     * Reset
     */
    LSFResponseCode Reset(void);
    /**
     * Get the data string
     */
    bool GetString(std::string& output, uint32_t& checksum, uint64_t& timestamp);
    /**
     * Write to cache persistent data
     */
    void ReadWriteFile(void);
    /**
     * Handle received blob. \n
     * Getting the blob string and writing it to the file. \n
     */
    void HandleReceivedBlob(const std::string& blob, uint32_t checksum, uint64_t timestamp);

    /**
     * Read saved persistent data to cache
     */
    void ReadSavedData(void);

  private:
    /**
     * Blob Data
     */
    std::string blobData;
    /**
     * Blob Type Identifier
     */
    uint32_t blobType;
};

/**
 * class manages the Unknown Blobs. \n
 */
class UnknownBlobGroupManager {
  public:
    /**
     * class constructor. \n
     * @param controllerSvc - reference to controller service instance
     */
    UnknownBlobGroupManager(ControllerService& controllerSvc);
    /**
     * class destructor. \n
     */
    ~UnknownBlobGroupManager();
    /**
     * Reset
     */
    LSFResponseCode Reset(uint32_t& numBlobs, uint32_t& failures);
    /**
     * Read saved persistent data to cache
     */
    void ReadSavedData(void);
    /**
     * Write to cache persistent data
     */
    void ReadWriteFile(void);
    /**
     * Handle received blob. \n
     * Getting the blob string and writing it to the file. \n
     */
    void HandleReceivedBlob(uint32_t blobType, const std::string& blob, uint32_t checksum, uint64_t timestamp);
    /**
     * Get blob information about checksum and time stamp.
     */
    void GetBlobInfo(uint32_t blobType, uint32_t& checksum, uint64_t& timestamp);

    /**
     * Trigger update for persistent data
     */
    void TriggerUpdate(uint32_t blobType);

    /**
     * Schedule File Read
     */
    void ScheduleFileRead(uint32_t blobType, ajn::Message& message);

    /**
     * Get a list of blobTypes corresponding to the unknown blobs
     */
    void GetUnknownBlobTypeList(std::list<uint32_t>& blobTypeList);

  private:

    typedef std::map<uint32_t, UnknownBlobManager*> UnknownBlobsMap;

    Mutex unknownBlobsLock;
    /**
     * Map of all the unknown blobs
     */
    UnknownBlobsMap unknownBlobsMap;
    /**
     * Reference to the Controller Service
     */
    ControllerService& controllerService;
};

}


#endif
