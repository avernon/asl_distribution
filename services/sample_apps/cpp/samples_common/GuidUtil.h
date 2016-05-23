/******************************************************************************
 * Copyright (c) 2013, AllSeen Alliance. All rights reserved.
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

#ifndef GUID_UTIL_H_
#define GUID_UTIL_H_


#include <qcc/Debug.h>
#include <qcc/String.h>

static const unsigned int GUID_STRING_MAX_LENGTH = 32;
static const unsigned int GUID_HYPHEN_MAX_LENGTH = 4;
static const unsigned int END_OF_STRING_LENGTH = 1;

namespace ajn {
namespace services {

/**
 * implements GUID utilities
 * Generation, saving, exposing - 128 bit unique number
 */
class GuidUtil  {
  public:
    /**
     * GetInstance
     * @return singleton of GuidUtil pointer
     */
    static GuidUtil* GetInstance();
    /**
     * GetDeviceIdString
     * @param deviceId
     */
    void GetDeviceIdString(qcc::String* deviceId);

    /**
     * GenerateGUID
     * @param guid
     */
    void GenerateGUID(qcc::String* guid);

  private:
    /**
     * Constructor for GuidUtil
     */
    GuidUtil();
    /**
     * Destructor for GuidUtil
     */
    virtual ~GuidUtil();
    /**
     * NormalizeString
     * @param strGUID
     */
    void NormalizeString(char* strGUID);

    /**
     * GetDeviceIdFileName
     * @param strGUID
     * @return device id file name
     */
    const char* GetDeviceIdFileName();

    /**
     * ReadGuidOfDeviceID
     * @param strGUID
     */
    bool ReadGuidOfDeviceID(char* strGUID);

    /**
     * WriteGUIDToFile
     * @param strGUID
     */
    void WriteGUIDToFile(char* strGUID);

    /**
     * GenerateGUIDUtil
     * @param strGUID
     */
    void GenerateGUIDUtil(char* strGUID);
    /**
     * a pointer to singleton GuidUtil
     */
    static GuidUtil* pGuidUtil;

};
} //namespace services
} //namespace ajn

#endif /* GUID_UTIL_H_ */
