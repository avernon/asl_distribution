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

#ifdef LSF_BINDINGS
#include <lsf/controllerservice/Manager.h>
#include <lsf/controllerservice/ControllerService.h>
#else
#include <Manager.h>
#include <ControllerService.h>
#endif

#include <qcc/StringUtil.h>
#include <qcc/Debug.h>

#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>

#ifdef LSF_BINDINGS
#define QCC_MODULE "CONTROLLER_MANAGER"
#else
#define QCC_MODULE "MANAGER"
#endif

namespace lsf {

Manager::Manager(ControllerService& controllerSvc, const std::string& fPath)
    : controllerService(controllerSvc),
    updated(false),
    read(false),
    filePath(fPath),
    checkSum(0),
    updatesCheckSum(0),
    timeStamp(0),
    updatesTimeStamp(0),
    blobUpdateCycle(false),
    initialState(false),
    sendUpdate(false)
{
    QCC_DbgTrace(("%s", __func__));
    readBlobMessages.clear();
    readUpdateBlobMessages.clear();

    updateFilePath = filePath;
    QCC_DbgPrintf(("Original = %s", filePath.c_str()));

    std::string findStr = ".lsf";
    size_t replaceLocation = updateFilePath.find(findStr);
    if (replaceLocation != std::string::npos) {
        updateFilePath.erase(replaceLocation, findStr.length());
        updateFilePath.append("_update.lsf");
        QCC_DbgPrintf(("Modified = %s", updateFilePath.c_str()));
    }
}

static uint32_t GetAdler32Checksum(const uint8_t* data, size_t len) {
    QCC_DbgTrace(("%s: len = %d", __func__, len));
    uint32_t adler = 1;
    uint32_t adlerPrime = 65521;
    uint32_t a = adler & 0xFFFF;
    uint32_t b = adler >> 16;
    while (data && len) {
        a = (a + *data++) % adlerPrime;
        b = (b + a) % adlerPrime;
        len--;
    }
    adler = (b << 16) | a;
    QCC_DbgTrace(("%s: adler=0x%x", __func__, adler));
    return adler;
}

uint32_t Manager::GetChecksum(const std::string& str)
{
    QCC_DbgTrace(("%s", __func__));
    return GetAdler32Checksum((uint8_t*) str.c_str(), str.length());
}

void Manager::WriteFileWithChecksumAndTimestamp(const std::string& str, uint32_t checksum, uint64_t timestamp)
{
    QCC_DbgTrace(("%s", __func__));
    std::ofstream fstream(filePath.c_str(), std::ios_base::out);
    if (!fstream.is_open()) {
        QCC_LogError(ER_FAIL, ("File not found: %s\n", filePath.c_str()));
        return;
    }

    fstream << timestamp << std::endl;
    fstream << checksum << std::endl;
    fstream << str;
    fstream.close();
}

void Manager::WriteUpdatesFileWithChecksumAndTimestamp(const std::string& str, uint32_t checksum, uint64_t timestamp)
{
    QCC_DbgTrace(("%s", __func__));
    std::ofstream fstream(updateFilePath.c_str(), std::ios_base::out);
    if (!fstream.is_open()) {
        QCC_LogError(ER_FAIL, ("File not found: %s\n", updateFilePath.c_str()));
        return;
    }

    fstream << timestamp << std::endl;
    fstream << checksum << std::endl;
    fstream << str;
    fstream.close();
}

bool Manager::ValidateFileAndRead(std::istringstream& filestream)
{
    QCC_DbgTrace(("%s", __func__));
    uint32_t checksum;
    uint64_t timestamp;

    bool b = ValidateFileAndReadInternal(checksum, timestamp, filestream);

    if (b) {
        checkSum = checksum;
        timeStamp = timestamp;
    }

    return b;
}

bool Manager::ValidateUpdateFileAndRead(std::istringstream& filestream)
{
    QCC_DbgTrace(("%s", __func__));
    uint32_t checksum;
    uint64_t timestamp;

    bool b = ValidateUpdateFileAndReadInternal(checksum, timestamp, filestream);

    if (b) {
        updatesCheckSum = checksum;
        updatesTimeStamp = timestamp;
    }

    return b;
}

bool Manager::ValidateFileAndReadInternal(uint32_t& checksum, uint64_t& timestamp, std::istringstream& filestream)
{
    QCC_DbgPrintf(("%s: filePath=%s", __func__, filePath.c_str()));

    if (filePath.empty()) {
        return false;
    }

    std::ifstream stream(filePath.c_str());

    if (!stream.is_open()) {
        QCC_LogError(ER_FAIL, ("File not found: %s\n", filePath.c_str()));
        return false;
    }

    stream >> timestamp;

    uint64_t currenttime = GetTimestampInMs();
    QCC_DbgPrintf(("%s: timestamp=%llu", __func__, timestamp));
    QCC_DbgPrintf(("%s: Updated %llu ticks ago", __func__, (currenttime - timestamp)));

    stream >> checksum;

    QCC_DbgPrintf(("%s: checksum=%u", __func__, checksum));

    // put the rest of the file into the filestream
    std::stringbuf rest;
    stream >> &rest;
    std::string data = rest.str();
    data.erase(std::remove(data.begin(), ++data.begin(), '\n'), ++data.begin());
    filestream.str(data);

    // check the adler checksum
    uint32_t adler = GetChecksum(data);

    stream.close();
    return adler == checksum;
}

bool Manager::ValidateUpdateFileAndReadInternal(uint32_t& checksum, uint64_t& timestamp, std::istringstream& filestream)
{
    QCC_DbgPrintf(("%s: updateFilePath=%s", __func__, updateFilePath.c_str()));

    if (updateFilePath.empty()) {
        return false;
    }

    std::ifstream stream(updateFilePath.c_str());

    if (!stream.is_open()) {
        QCC_LogError(ER_FAIL, ("File not found: %s\n", updateFilePath.c_str()));
        return false;
    }

    stream >> timestamp;

    uint64_t currenttime = GetTimestampInMs();
    QCC_DbgPrintf(("%s: timestamp=%llu", __func__, timestamp));
    QCC_DbgPrintf(("%s: Updated %llu ticks ago", __func__, (currenttime - timestamp)));

    stream >> checksum;

    QCC_DbgPrintf(("%s: checksum=%u", __func__, checksum));

    // put the rest of the file into the filestream
    std::stringbuf rest;
    stream >> &rest;
    std::string data = rest.str();
    data.erase(std::remove(data.begin(), ++data.begin(), '\n'), ++data.begin());
    filestream.str(data);

    // check the adler checksum
    uint32_t adler = GetChecksum(data);

    stream.close();
    return adler == checksum;
}

LSFString Manager::GenerateUniqueID(const LSFString& prefix) const
{
    QCC_DbgTrace(("%s", __func__));
    // generate a GUID string with a given prefix
    qcc::String str = qcc::RandHexString(ID_STR_LEN);
    return prefix + str.c_str();
}

void Manager::ScheduleFileWrite(bool blobUpdate, bool initState)
{
    QCC_DbgTrace(("%s", __func__));
    updated = true;
    blobUpdateCycle = blobUpdate;
    initialState = initState;
    controllerService.ScheduleFileReadWrite(this);
}

void Manager::ScheduleFileRead(Message& message)
{
    QCC_DbgTrace(("%s", __func__));
    readMutex.Lock();
    readBlobMessages.push_back(message);
    read = true;
    controllerService.ScheduleFileReadWrite(this);
    readMutex.Unlock();
}

void Manager::ScheduleUpdateFileRead(Message& message)
{
    QCC_DbgTrace(("%s", __func__));
    readMutex.Lock();
    readUpdateBlobMessages.push_back(message);
    read = true;
    controllerService.ScheduleFileReadWrite(this);
    readMutex.Unlock();
}

void Manager::TriggerUpdate(void)
{
    QCC_DbgTrace(("%s", __func__));
    sendUpdate = true;
    controllerService.ScheduleFileReadWrite(this);
}

void Manager::GetBlobInfoInternal(uint32_t& checksum, uint64_t& timestamp)
{
    QCC_DbgTrace(("%s", __func__));
    checksum = checkSum;
    timestamp = timeStamp;
}

void Manager::GetUpdateBlobInfoInternal(uint32_t& checksum, uint64_t& timestamp)
{
    QCC_DbgTrace(("%s", __func__));
    checksum = updatesCheckSum;
    timestamp = updatesTimeStamp;
}

OPTIONAL_NAMESPACE_CLOSE

}
