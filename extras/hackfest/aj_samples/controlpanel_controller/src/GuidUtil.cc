/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

#include "GuidUtil.h"
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <linux/limits.h>



static const char DEVICE_ID_FILE_NAME[] = "alljoyn-deviceId.txt";

using namespace ajn;
using namespace services;
using namespace qcc;

GuidUtil* GuidUtil::pGuidUtil = NULL;

GuidUtil* GuidUtil::GetInstance()
{
    if (pGuidUtil == NULL) {
        pGuidUtil = new GuidUtil();
    }
    return pGuidUtil;
}

GuidUtil::GuidUtil()
{
}


GuidUtil::~GuidUtil()
{
}

void GuidUtil::NormalizeString(char* strGUID)
{
    //remove the '-' from the string:
    std::string sGUID(strGUID);
    std::string::size_type nposition = std::string::npos;
    while ((nposition = sGUID.find('-')) != std::string::npos) {
        sGUID.erase(nposition, 1);
    }
    strcpy(strGUID, sGUID.c_str());
}

const char* GuidUtil::GetDeviceIdFileName()
{
    static std::string sFileName;
    if (sFileName.length() == 0) {
        //Get the path of the binary
        char buf[PATH_MAX] = { 0 };
        ssize_t ret = readlink("/proc/self/exe", buf, PATH_MAX);
        if (ret < 0) {
            //In that case the file will be created at the current dir
            perror("lstat");
        }
        sFileName += buf;
        unsigned found = sFileName.find_last_of("/");
        if (found !=  std::string::npos) {
            sFileName.erase(found + 1);
        }
        //Add file name
        sFileName += DEVICE_ID_FILE_NAME;
    }
    return sFileName.c_str();
}

bool GuidUtil::ReadGuidOfDeviceID(char* strGUID)
{
    bool success = false;
    std::ifstream ifs(GetDeviceIdFileName(),  std::ifstream::in);
    if (ifs.is_open()) {
        ifs.getline(strGUID, GUID_STRING_MAX_LENGTH + END_OF_STRING_LENGTH);
        success = true;
    }
    ifs.close();
    return success;
}

void GuidUtil::WriteGUIDToFile(char* strGUID)
{
    std::ofstream ofs(GetDeviceIdFileName(), std::ofstream::out);
    ofs << strGUID;
    ofs.close();
}

void GuidUtil::GenerateGUIDUtil(char* strGUID)
{
    std::ifstream ifs("/proc/sys/kernel/random/uuid", std::ifstream::in);
    ifs.getline(strGUID, GUID_STRING_MAX_LENGTH + GUID_HYPHEN_MAX_LENGTH + END_OF_STRING_LENGTH);
    ifs.close();
    NormalizeString(strGUID);
}

void GuidUtil::GenerateGUID(qcc::String* guid)
{
    if (guid == NULL) {
        return;
    }

    char tempstrGUID[GUID_STRING_MAX_LENGTH + GUID_HYPHEN_MAX_LENGTH + END_OF_STRING_LENGTH];
    GenerateGUIDUtil(tempstrGUID);
    guid->assign(tempstrGUID);
}

void GuidUtil::GetDeviceIdString(qcc::String* deviceId)
{
    if (deviceId == NULL) {
        return;
    }

    char tempstrGUID[GUID_STRING_MAX_LENGTH + GUID_HYPHEN_MAX_LENGTH + END_OF_STRING_LENGTH];
    if (!ReadGuidOfDeviceID(tempstrGUID)) {
        GenerateGUIDUtil(tempstrGUID);
        WriteGUIDToFile(tempstrGUID);
    }
    deviceId->assign(tempstrGUID);
}

