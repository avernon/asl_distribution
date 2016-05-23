/*****************************************************************************
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

#include <ControllerClient.h>
#include <LampManager.h>
#include <LampGroupManager.h>
#include <PresetManager.h>
#include <TransitionEffectManager.h>
#include <SceneElementManager.h>
#include <SceneManager.h>
#include <MasterSceneManager.h>
#include <PulseEffectManager.h>
#include <ControllerServiceManager.h>
#include <AJInitializer.h>

#include <qcc/StringUtil.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/ProxyBusObject.h>
#include <qcc/Debug.h>
#include <inttypes.h>


using namespace qcc;
using namespace lsf;
using namespace ajn;

#define QCC_MODULE "SAMPLE"

volatile bool connectedToControllerService = false;
volatile bool gotReply = false;
volatile bool gotSignal = false;

LSFStringList lampList;
LSFStringList lampGroupList;
LSFStringList presetList;
LSFStringList allSceneElementIDs;
LSFStringList allTransitionEffectIDs;
LSFStringList allPulseEffectIDs;
LSFStringList sceneList;
uint8_t lampIndex = 0;
uint8_t lampGroupIndex = 0;

uint8_t numRepliesToWait = 0;

char* get_line(char* str, size_t num, FILE* fp)
{
    char* p = fgets(str, num, fp);

    // fgets will capture the '\n' character if the string entered is shorter than
    // num. Remove the '\n' from the end of the line and replace it with nul '\0'.
    if (p != NULL) {
        size_t last = strlen(str) - 1;
        if (str[last] == '\n') {
            str[last] = '\0';
        }
    }
    return p;
}

static qcc::String NextTok(qcc::String& inStr)
{
    qcc::String ret;
    size_t off = inStr.find_first_of(' ');
    if (off == qcc::String::npos) {
        ret = inStr;
        inStr.clear();
    } else {
        ret = inStr.substr(0, off);
        inStr = qcc::Trim(inStr.substr(off));
    }
    return qcc::Trim(ret);
}

class ControllerClientCallbackHandler : public ControllerClientCallback {
  public:

    ~ControllerClientCallbackHandler() { }

    void ConnectedToControllerServiceCB(const LSFString& controllerServiceDeviceID, const LSFString& controllerServiceName) {
        LSFString uniqueId = controllerServiceDeviceID;
        LSFString name = controllerServiceName;
        printf("\n%s: controllerServiceDeviceID = %s controllerServiceName = %s\n", __func__, uniqueId.c_str(), name.c_str());
        connectedToControllerService = true;
        gotReply = true;
        gotSignal = true;
    }

    void ConnectToControllerServiceFailedCB(const LSFString& controllerServiceDeviceID, const LSFString& controllerServiceName) {
        LSFString uniqueId = controllerServiceDeviceID;
        LSFString name = controllerServiceName;
        printf("\n%s: controllerServiceDeviceID = %s controllerServiceName = %s\n", __func__, uniqueId.c_str(), name.c_str());
        gotReply = true;
        gotSignal = true;
    }

    void DisconnectedFromControllerServiceCB(const LSFString& controllerServiceDeviceID, const LSFString& controllerServiceName) {
        LSFString uniqueId = controllerServiceDeviceID;
        LSFString name = controllerServiceName;
        printf("\n%s: controllerServiceDeviceID = %s controllerServiceName = %s\n", __func__, uniqueId.c_str(), name.c_str());
        connectedToControllerService = false;
        gotReply = true;
        gotSignal = true;
    }

    void ControllerClientErrorCB(const ErrorCodeList& errorCodeList) {
        printf("\n%s:", __func__);
        ErrorCodeList::const_iterator it = errorCodeList.begin();
        for (; it != errorCodeList.end(); ++it) {
            printf("\n%s", ControllerClientErrorText(*it));
        }
        printf("\n");
    }
};

class ControllerServiceManagerCallbackHandler : public ControllerServiceManagerCallback {

    void GetControllerServiceVersionReplyCB(const uint32_t& version) {
        printf("\n%s: version = %d\n", __func__, version);
        gotReply = true;
    }

    void LightingResetControllerServiceReplyCB(const LSFResponseCode& responseCode) {
        printf("\n%s: responseCode = %s\n", __func__, LSFResponseCodeText(responseCode));
        gotReply = true;
    }

    void ControllerServiceLightingResetCB(void) {
        printf("\n%s\n", __func__);
        gotSignal = true;
    }

    void ControllerServiceNameChangedCB(const LSFString& controllerServiceDeviceID, const LSFString& controllerServiceName) {
        LSFString uniqueId = controllerServiceDeviceID;
        LSFString name = controllerServiceName;
        printf("\n%s: controllerServiceDeviceID = %s controllerServiceName = %s\n", __func__, uniqueId.c_str(), name.c_str());
        gotSignal = true;
    }
};

class LampManagerCallbackHandler : public LampManagerCallback {

    void GetAllLampIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& lampIDs) {
        printf("\n%s(): responseCode = %s", __func__, LSFResponseCodeText(responseCode));
        if (responseCode == LSF_OK) {
            LSFStringList::const_iterator it = lampIDs.begin();
            uint8_t count = 1;
            for (; it != lampIDs.end(); ++it) {
                printf("\n(%d)%s", count, (*it).c_str());
                count++;
            }
            printf("\n");
            lampList.clear();
            lampList = lampIDs;
        }
        gotReply = true;
    }

    void GetLampSupportedLanguagesReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFStringList& supportedLanguages) {
        printf("\n%s(): responseCode = %s", __func__, LSFResponseCodeText(responseCode));
        if (responseCode == LSF_OK) {
            LSFStringList::const_iterator it = supportedLanguages.begin();
            uint8_t count = 1;
            for (; it != supportedLanguages.end(); ++it) {
                printf("\n(%d)%s", count, (*it).c_str());
                count++;
            }
            printf("\n");
        }
        gotReply = true;
    }

    void GetLampManufacturerReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFString& language, const LSFString& manufacturer) {
        LSFString uniqueId = lampID;

        printf("\n%s: responseCode = %s lampID = %s language = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str(), language.c_str());

        if (responseCode == LSF_OK) {
            printf("\nmanufacturer = %s", manufacturer.c_str());
        }
        gotReply = true;
    }

    void GetLampNameReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFString& language, const LSFString& lampName) {
        LSFString uniqueId = lampID;

        printf("\n%s: responseCode = %s lampID = %s language = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str(), language.c_str());

        if (responseCode == LSF_OK) {
            printf("\nlampName = %s", lampName.c_str());
        }
        gotReply = true;
        if (numRepliesToWait) {
            numRepliesToWait--;
        }
    }

    void SetLampNameReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFString& language) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s language = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str(), language.c_str());
        gotReply = true;
        if (responseCode != LSF_OK) {
            gotSignal = true;
        }
    }

    void LampNameChangedCB(const LSFString& lampID, const LSFString& lampName) {
        printf("\n%s: lampID = %s lampName = %s", __func__, lampID.c_str(), lampName.c_str());
        gotSignal = true;
    }

    void GetLampDetailsReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampDetails& lampDetails) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        if (responseCode == LSF_OK) {
            printf("\n%s: lampDetails = %s", __func__, lampDetails.c_str());
        }
        gotReply = true;
        if (numRepliesToWait) {
            numRepliesToWait--;
        }
    }

    void GetLampParametersReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampParameters& lampParameters) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        if (responseCode == LSF_OK) {
            printf("\n%s: parameters = %s", __func__, lampParameters.c_str());
        }
        gotReply = true;
    }

    void GetLampParametersLumensFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& value) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        if (responseCode == LSF_OK) {
            printf(" value = %d", value);
        }
        gotReply = true;
    }

    void GetLampParametersEnergyUsageMilliwattsFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& value) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        if (responseCode == LSF_OK) {
            printf(" value = %d", value);
        }
        gotReply = true;
    }

    void GetLampStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampState& lampState) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        if (responseCode == LSF_OK) {
            printf("\nstate=%s\n", lampState.c_str());
        }
        gotReply = true;
        if (numRepliesToWait) {
            numRepliesToWait--;
        }
    }

    void GetLampStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const bool& onOff) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        if (responseCode == LSF_OK) {
            printf(" onOff = %d", onOff);
        }
        gotReply = true;
    }

    void GetLampStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& hue) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        if (responseCode == LSF_OK) {
            printf(" hue = %d", hue);
        }
        gotReply = true;
    }

    void GetLampStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& saturation) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        if (responseCode == LSF_OK) {
            printf(" saturation = %d", saturation);
        }
        gotReply = true;
    }

    void GetLampStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& brightness) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        if (responseCode == LSF_OK) {
            printf(" brightness = %d", brightness);
        }
        gotReply = true;
    }

    void GetLampStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& colorTemp) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        if (responseCode == LSF_OK) {
            printf(" colorTemp = %d", colorTemp);
        }
        gotReply = true;
    }

    void ResetLampStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void LampStateChangedCB(const LSFString& lampID, const LampState& lampState) {
        printf("\n%s: lampID = %s lampState = %s", __func__, lampID.c_str(), lampState.c_str());
        gotSignal = true;
    }

    void TransitionLampStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (responseCode != LSF_OK) {
            gotSignal = true;
        }
    }

    void PulseLampWithStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
    }

    void PulseLampWithPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
    }

    void TransitionLampStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void TransitionLampStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void TransitionLampStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void TransitionLampStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void TransitionLampStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void GetLampFaultsReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampFaultCodeList& faultCodes) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        if (responseCode == LSF_OK) {
            LampFaultCodeList::const_iterator it = faultCodes.begin();
            for (; it != faultCodes.end(); ++it) {
                printf("\n%d", *it);
            }
            printf("\n");
        }
        gotReply = true;
    }

    void ClearLampFaultReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampFaultCode& faultCode) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s faultCode=0x%x", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str(), faultCode);
        gotReply = true;
    }

    void GetLampServiceVersionReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& lampServiceVersion) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s lampServiceVersion=0x%x", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str(), lampServiceVersion);
        gotReply = true;
    }

    void ResetLampStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void ResetLampStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void ResetLampStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void ResetLampStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void ResetLampStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void TransitionLampStateToPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID) {
        LSFString uniqueId = lampID;
        printf("\n%s: responseCode = %s lampID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void LampsFoundCB(const LSFStringList& lampIDs) {
        printf("\n%s()", __func__);
        LSFStringList::const_iterator it = lampIDs.begin();
        uint8_t count = 1;
        for (; it != lampIDs.end(); ++it) {
            printf("\n(%d)%s", count, (*it).c_str());
            count++;
        }
        printf("\n");
        lampList.clear();
        lampList = lampIDs;
    }

    void LampsLostCB(const LSFStringList& lampIDs) {
        printf("\n%s()", __func__);
        LSFStringList::const_iterator it = lampIDs.begin();
        uint8_t count = 1;
        for (; it != lampIDs.end(); ++it) {
            printf("\n(%d)%s", count, (*it).c_str());
            count++;
        }
        printf("\n");
        lampList.clear();
        lampList = lampIDs;
    }

    void GetConsolidatedLampDataSetReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFString& language, const LSFString& lampName, const LampDetails& lampDetails, const LampState& lampState, const LampParameters& lampParameters) {
        gotReply = true;
    }
};

class LampGroupManagerCallbackHandler : public LampGroupManagerCallback {
    void GetLampGroupReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID, const LampGroup& lampGroup) {
        printf("\n%s(): responseCode = %s, lampGroupID=%s\n", __func__, LSFResponseCodeText(responseCode), lampGroupID.c_str());
        if (responseCode == LSF_OK) {
            printf("\nlampGroup=%s", lampGroup.c_str());
        }
        gotReply = true;
        if (numRepliesToWait) {
            numRepliesToWait--;
        }
    }

    void GetAllLampGroupIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& lampGroupIDs) {
        printf("\n%s(): responseCode = %s", __func__, LSFResponseCodeText(responseCode));
        lampGroupList = lampGroupIDs;
        if (responseCode == LSF_OK) {
            LSFStringList::const_iterator it = lampGroupIDs.begin();
            uint8_t count = 1;
            for (; it != lampGroupIDs.end(); ++it) {
                printf("\n(%d)%s", count, (*it).c_str());
                count++;
            }
            printf("\n");
        }
        gotReply = true;
    }

    void GetLampGroupNameReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID, const LSFString& language, const LSFString& lampGroupName) {
        LSFString uniqueId = lampGroupID;

        printf("\n%s: responseCode = %s lampGroupID = %s language = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str(), language.c_str());

        if (responseCode == LSF_OK) {
            printf("\nlampGroupName = %s", lampGroupName.c_str());
        }
        gotReply = true;
        if (numRepliesToWait) {
            numRepliesToWait--;
        }
    }

    void SetLampGroupNameReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID, const LSFString& language) {
        LSFString uniqueId = lampGroupID;
        printf("\n%s: responseCode = %s lampGroupID = %s language = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str(), language.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void LampGroupsNameChangedCB(const LSFStringList& lampGroupIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = lampGroupIDs.begin();
        for (; it != lampGroupIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void CreateLampGroupReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID) {
        printf("\n%s: responseCode=%s\n", __func__, LSFResponseCodeText(responseCode));
        if (LSF_OK == responseCode) {
            printf("lampGroupID=%s\n", lampGroupID.c_str());
            lampGroupList.push_back(lampGroupID);
        } else {
            gotSignal = true;
        }
        gotReply = true;
    }

    void LampGroupsCreatedCB(const LSFStringList& lampGroupIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = lampGroupIDs.begin();
        for (; it != lampGroupIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void UpdateLampGroupReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID) {
        printf("\n%s(): responseCode = %s, lampGroupID=%s\n", __func__, LSFResponseCodeText(responseCode), lampGroupID.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void LampGroupsUpdatedCB(const LSFStringList& lampGroupIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = lampGroupIDs.begin();
        for (; it != lampGroupIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void DeleteLampGroupReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID) {
        printf("\n%s(): responseCode = %s, lampGroupID=%s\n", __func__, LSFResponseCodeText(responseCode), lampGroupID.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void LampGroupsDeletedCB(const LSFStringList& lampGroupIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = lampGroupIDs.begin();
        for (; it != lampGroupIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void ResetLampGroupStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID) {
        LSFString uniqueId = lampGroupID;
        printf("\n%s: responseCode = %s lampGroupID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void TransitionLampGroupStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID) {
        LSFString uniqueId = lampGroupID;
        printf("\n%s: responseCode = %s lampGroupID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (responseCode != LSF_OK) {
            gotSignal = true;
        }
    }

    void PulseLampGroupWithStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID) {
        LSFString uniqueId = lampGroupID;
        printf("\n%s: responseCode = %s lampGroupID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
    }

    void PulseLampGroupWithPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID) {
        LSFString uniqueId = lampGroupID;
        printf("\n%s: responseCode = %s lampGroupID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
    }

    void TransitionLampGroupStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID) {
        LSFString uniqueId = lampGroupID;
        printf("\n%s: responseCode = %s lampGroupID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void TransitionLampGroupStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID) {
        LSFString uniqueId = lampGroupID;
        printf("\n%s: responseCode = %s lampGroupID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void TransitionLampGroupStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID) {
        LSFString uniqueId = lampGroupID;
        printf("\n%s: responseCode = %s lampGroupID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void TransitionLampGroupStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID) {
        LSFString uniqueId = lampGroupID;
        printf("\n%s: responseCode = %s lampGroupID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void TransitionLampGroupStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID) {
        LSFString uniqueId = lampGroupID;
        printf("\n%s: responseCode = %s lampGroupID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void ResetLampGroupStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID) {
        LSFString uniqueId = lampGroupID;
        printf("\n%s: responseCode = %s lampGroupID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void ResetLampGroupStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID) {
        LSFString uniqueId = lampGroupID;
        printf("\n%s: responseCode = %s lampGroupID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void ResetLampGroupStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID) {
        LSFString uniqueId = lampGroupID;
        printf("\n%s: responseCode = %s lampGroupID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void ResetLampGroupStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID) {
        LSFString uniqueId = lampGroupID;
        printf("\n%s: responseCode = %s lampGroupID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void ResetLampGroupStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID) {
        LSFString uniqueId = lampGroupID;
        printf("\n%s: responseCode = %s lampGroupID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void TransitionLampGroupStateToPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& lampGroupID) {
        LSFString uniqueId = lampGroupID;
        printf("\n%s: responseCode = %s lampGroupID = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }
};

class PresetManagerCallbackHandler : public PresetManagerCallback {

    void GetPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID, const LampState& preset) {
        printf("\n%s(): responseCode = %s, presetID=%s\n", __func__, LSFResponseCodeText(responseCode), presetID.c_str());
        if (responseCode == LSF_OK) {
            printf("\npreset=%s", preset.c_str());
        }
        gotReply = true;
        if (numRepliesToWait) {
            numRepliesToWait--;
        }
    }

    void GetAllPresetIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& presetIDs) {
        printf("\n%s(): responseCode = %s", __func__, LSFResponseCodeText(responseCode));
        if (responseCode == LSF_OK) {
            presetList = presetIDs;
            LSFStringList::const_iterator it = presetIDs.begin();
            uint8_t count = 1;
            for (; it != presetIDs.end(); ++it) {
                printf("\n(%d)%s", count, (*it).c_str());
                count++;
            }
            printf("\n");
        }
        gotReply = true;
    }

    void GetPresetNameReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID, const LSFString& language, const LSFString& presetName) {
        LSFString uniqueId = presetID;

        printf("\n%s: responseCode = %s presetID = %s language = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str(), language.c_str());

        if (responseCode == LSF_OK) {
            printf("\npresetName = %s", presetName.c_str());
        }
        gotReply = true;
        if (numRepliesToWait) {
            numRepliesToWait--;
        }
    }

    void SetPresetNameReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID, const LSFString& language) {
        LSFString uniqueId = presetID;
        printf("\n%s: responseCode = %s presetID = %s language = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str(), language.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void PresetsNameChangedCB(const LSFStringList& presetIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = presetIDs.begin();
        for (; it != presetIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void CreatePresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID) {
        printf("\n%s: responseCode=%s\n", __func__, LSFResponseCodeText(responseCode));
        if (LSF_OK == responseCode) {
            printf("presetID=%s\n", presetID.c_str());
            presetList.push_back(presetID);
        } else {
            gotSignal = true;
        }
        gotReply = true;
    }

    void PresetsCreatedCB(const LSFStringList& presetIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = presetIDs.begin();
        for (; it != presetIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void UpdatePresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID) {
        printf("\n%s(): responseCode = %s, presetID=%s\n", __func__, LSFResponseCodeText(responseCode), presetID.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void PresetsUpdatedCB(const LSFStringList& presetIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = presetIDs.begin();
        for (; it != presetIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void DeletePresetReplyCB(const LSFResponseCode& responseCode, const LSFString& presetID) {
        printf("\n%s(): responseCode = %s, presetID=%s\n", __func__, LSFResponseCodeText(responseCode), presetID.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void PresetsDeletedCB(const LSFStringList& presetIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = presetIDs.begin();
        for (; it != presetIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void GetDefaultLampStateReplyCB(const LSFResponseCode& responseCode, const LampState& defaultState) {
        printf("\n%s: responseCode = %s", __func__, LSFResponseCodeText(responseCode));
        if (responseCode == LSF_OK) {
            printf("\nstate=%s\n", defaultState.c_str());
        }
        gotReply = true;
    }

    void SetDefaultLampStateReplyCB(const LSFResponseCode& responseCode) {
        printf("\n%s: responseCode = %s\n", __func__, LSFResponseCodeText(responseCode));
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void DefaultLampStateChangedCB(void) {
        printf("\n%s", __func__);
        gotSignal = true;
    }
};

class TransitionEffectManagerCallbackHandler : public TransitionEffectManagerCallback {
    void GetAllTransitionEffectIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& transitionEffectIDs) {
        printf("\n%s(): responseCode = %s", __func__, LSFResponseCodeText(responseCode));
        allTransitionEffectIDs = transitionEffectIDs;
        if (responseCode == LSF_OK) {
            LSFStringList::const_iterator it = transitionEffectIDs.begin();
            uint8_t count = 1;
            for (; it != transitionEffectIDs.end(); ++it) {
                printf("\n(%d)%s", count, (*it).c_str());
                count++;
            }
            printf("\n");
        }
        gotReply = true;
    }
    void ApplyTransitionEffectOnLampGroupsReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const LSFStringList& lampGroupIDs) {
        printf("\n%s: responseCode = %s transitionEffectID = %s", __func__, LSFResponseCodeText(responseCode), transitionEffectID.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
        printf("\nlampGroupIDs: ");
        LSFStringList::const_iterator it = lampGroupIDs.begin();
        for (; it != lampGroupIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }


    }
    void GetTransitionEffectNameReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const LSFString& language, const LSFString& transitionEffectName) {
        LSFString uniqueId = transitionEffectID;

        printf("\n%s: responseCode = %s transitionEffectID = %s language = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str(), language.c_str());

        if (responseCode == LSF_OK) {
            printf("\ntransitionEffectName = %s", transitionEffectName.c_str());
        }
        gotReply = true;
        if (numRepliesToWait) {
            numRepliesToWait--;
        }
    }

    void GetTransitionEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const TransitionEffect& transitionEffect) {
        printf("\n%s(): responseCode = %s, transitionEffectID=%s\n", __func__, LSFResponseCodeText(responseCode), transitionEffectID.c_str());
        if (responseCode == LSF_OK) {
            printf("\ntransitionEffect=\n%s", transitionEffect.state.c_str());
            printf("\ntransitionPeriod = %" PRIu32 "\n", transitionEffect.transitionPeriod);
        }
        gotReply = true;
        if (numRepliesToWait) {
            numRepliesToWait--;
        }
    }
    void SetTransitionEffectNameReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const LSFString& language) {
        LSFString uniqueId = transitionEffectID;
        printf("\n%s: responseCode = %s transitionEffectID = %s language = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str(), language.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void ApplyTransitionEffectOnLampsReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const LSFStringList& lampIDs) {
        printf("\n%s(): responseCode = %s, transitionEffectID=%s\n", __func__, LSFResponseCodeText(responseCode), transitionEffectID.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
        /*printf("\n%s: responseCode = %s transitionEffectID = %s", __func__, LSFResponseCodeText(responseCode), transitionEffectID.c_str());
           printf("\nlampIDs: ");
           gotReply = true;
           if (LSF_OK != responseCode) {
            gotSignal = true;
           }
           LSFStringList::const_iterator it = lampIDs.begin();
           for (; it != lampIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
           }
           printf("\n");
           if (numRepliesToWait) {
            numRepliesToWait--;
           }*/

    }
    void CreateTransitionEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID, const uint32_t& trackingID) {
        printf("\n%s: responseCode=%s\n", __func__, LSFResponseCodeText(responseCode));
        if (LSF_OK == responseCode) {
            printf("transitionEffectID=%s\n", transitionEffectID.c_str());
            allTransitionEffectIDs.push_back(transitionEffectID);
        } else {
            gotSignal = true;
        }
        gotReply = true;
    }
    void UpdateTransitionEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID) {
        printf("\n%s(): responseCode = %s, transitionEffectID=%s\n", __func__, LSFResponseCodeText(responseCode), transitionEffectID.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }
    void DeleteTransitionEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& transitionEffectID) {
        printf("\n%s(): responseCode = %s, transitionEffectID=%s\n", __func__, LSFResponseCodeText(responseCode), transitionEffectID.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void TransitionEffectsDeletedCB(const LSFStringList& transitionEffectIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = transitionEffectIDs.begin();
        for (; it != transitionEffectIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void TransitionEffectsNameChangeCB(const LSFStringList& transitionEffectIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = transitionEffectIDs.begin();
        for (; it != transitionEffectIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void TransitionEffectsCreatedCB(const LSFStringList& transitionEffectIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = transitionEffectIDs.begin();
        for (; it != transitionEffectIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;

    }
    void TransitionEffectsUpdatedCB(const LSFStringList& transitionEffectIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = transitionEffectIDs.begin();
        for (; it != transitionEffectIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void TransitionEffectsChangedCB(const LSFStringList& transitionEffectIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = transitionEffectIDs.begin();
        for (; it != transitionEffectIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }
};

class PulseEffectManagerCallbackHandler : public PulseEffectManagerCallback {
    void GetAllPulseEffectIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& pulseEffectIDs) {
        printf("\n%s(): responseCode = %s", __func__, LSFResponseCodeText(responseCode));
        allPulseEffectIDs = pulseEffectIDs;
        if (responseCode == LSF_OK) {
            LSFStringList::const_iterator it = pulseEffectIDs.begin();
            uint8_t count = 1;
            for (; it != pulseEffectIDs.end(); ++it) {
                printf("\n(%d)%s", count, (*it).c_str());
                count++;
            }
            printf("\n");
        }
        gotReply = true;
    }
    void ApplyPulseEffectOnLampGroupsReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const LSFStringList& lampGroupIDs) {
        printf("\n%s: responseCode = %s pulseEffectID = %s", __func__, LSFResponseCodeText(responseCode), pulseEffectID.c_str());
        printf("\nlampGroupIDs: ");
        LSFStringList::const_iterator it = lampGroupIDs.begin();
        for (; it != lampGroupIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotReply = true;
        if (numRepliesToWait) {
            numRepliesToWait--;
        }
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void GetPulseEffectNameReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const LSFString& language, const LSFString& pulseEffectName) {
        LSFString uniqueId = pulseEffectID;

        printf("\n%s: responseCode = %s pulseEffectID = %s language = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str(), language.c_str());

        if (responseCode == LSF_OK) {
            printf("\npulseEffectName = %s", pulseEffectName.c_str());
        }
        gotReply = true;
        if (numRepliesToWait) {
            numRepliesToWait--;
        }
    }

    void GetPulseEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const PulseEffect& pulseEffect) {
        printf("\n%s(): responseCode = %s, pulseEffectID=%s\n", __func__, LSFResponseCodeText(responseCode), pulseEffectID.c_str());
        if (responseCode == LSF_OK) {
            printf("\ntoLampState: %s", pulseEffect.toState.c_str());
            printf("\npulsePeriod = %" PRIu32 "\n", pulseEffect.pulsePeriod);
            printf("\npulseDuration = %" PRIu32 "\n", pulseEffect.pulseDuration);
            printf("\nnumPulses = %" PRIu32 "\n", pulseEffect.numPulses);
            printf("\nfromLampState: %s", pulseEffect.fromState.c_str());

        }
        gotReply = true;
        if (numRepliesToWait) {
            numRepliesToWait--;
        }
    }
    void SetPulseEffectNameReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const LSFString& language) {
        LSFString uniqueId = pulseEffectID;
        printf("\n%s: responseCode = %s pulseEffectID = %s language = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str(), language.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void ApplyPulseEffectOnLampsReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const LSFStringList& lampIDs) {
        printf("\n%s: responseCode = %s pulseEffectID = %s", __func__, LSFResponseCodeText(responseCode), pulseEffectID.c_str());
        printf("\nlampIDs: ");
        LSFStringList::const_iterator it = lampIDs.begin();
        for (; it != lampIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotReply = true;
        if (numRepliesToWait) {
            numRepliesToWait--;
        }
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }
    void CreatePulseEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID, const uint32_t& trackingID) {
        printf("\n%s: responseCode=%s\n", __func__, LSFResponseCodeText(responseCode));
        if (LSF_OK == responseCode) {
            printf("pulseEffectID=%s\n", pulseEffectID.c_str());
            allPulseEffectIDs.push_back(pulseEffectID);
        } else {
            gotSignal = true;
        }
        gotReply = true;
    }
    void UpdatePulseEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID) {
        printf("\n%s(): responseCode = %s, pulseEffectID=%s\n", __func__, LSFResponseCodeText(responseCode), pulseEffectID.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }
    void DeletePulseEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& pulseEffectID) {
        printf("\n%s(): responseCode = %s, pulseEffectID=%s\n", __func__, LSFResponseCodeText(responseCode), pulseEffectID.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void PulseEffectsDeletedCB(const LSFStringList& pulseEffectIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = pulseEffectIDs.begin();
        for (; it != pulseEffectIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void PulseEffectsNameChangeCB(const LSFStringList& pulseEffectIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = pulseEffectIDs.begin();
        for (; it != pulseEffectIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void PulseEffectsCreatedCB(const LSFStringList& pulseEffectIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = pulseEffectIDs.begin();
        for (; it != pulseEffectIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;

    }
    void PulseEffectsUpdatedCB(const LSFStringList& pulseEffectIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = pulseEffectIDs.begin();
        for (; it != pulseEffectIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void PulseEffectsChangedCB(const LSFStringList& pulseEffectIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = pulseEffectIDs.begin();
        for (; it != pulseEffectIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }
};

class SceneElementManagerCallbackHandler : public SceneElementManagerCallback {
    void GetAllSceneElementIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& sceneElementIDs) {
        printf("\n%s(): responseCode = %s", __func__, LSFResponseCodeText(responseCode));
        allSceneElementIDs = sceneElementIDs;
        if (responseCode == LSF_OK) {
            LSFStringList::const_iterator it = sceneElementIDs.begin();
            uint8_t count = 1;
            for (; it != sceneElementIDs.end(); ++it) {
                printf("\n(%d)%s", count, (*it).c_str());
                count++;
            }
            printf("\n");
        }
        gotReply = true;
    }

    void DeleteSceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID) {
        printf("\n%s(): responseCode = %s, sceneElementID=%s\n", __func__, LSFResponseCodeText(responseCode), sceneElementID.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void GetSceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID, const SceneElement& sceneElement) {
        printf("\n%s(): responseCode = %s, sceneElementID=%s\n", __func__, LSFResponseCodeText(responseCode), sceneElementID.c_str());
        if (responseCode == LSF_OK) {
            printf("\nsceneElement=%s", sceneElement.c_str());
        }
        gotReply = true;
        if (numRepliesToWait) {
            numRepliesToWait--;
        }
    }

    void ApplySceneElementReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneElementID) {
        printf("\n%s(): responseCode = %s, sceneElementID=%s\n", __func__, LSFResponseCodeText(responseCode), sceneElementID.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

};

class SceneManagerCallbackHandler : public SceneManagerCallback {
    void GetSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID, const Scene& scene) {
        printf("\n%s(): responseCode = %s, sceneID=%s\n", __func__, LSFResponseCodeText(responseCode), sceneID.c_str());
        if (responseCode == LSF_OK) {
            printf("\nscene=%s", scene.c_str());
        }
        gotReply = true;
        if (numRepliesToWait) {
            numRepliesToWait--;
        }
    }

    void GetSceneWithSceneElementsReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID, const SceneWithSceneElements& sceneWithSceneElements) {
        printf("\n%s(): responseCode = %s, sceneID=%s\n", __func__, LSFResponseCodeText(responseCode), sceneID.c_str());
        if (responseCode == LSF_OK) {
            printf("\nsceneWithSceneElements=%s", sceneWithSceneElements.c_str());
        }
        gotReply = true;
        if (numRepliesToWait) {
            numRepliesToWait--;
        }
    }

    void GetAllSceneIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& sceneIDs) {
        printf("\n%s(): responseCode = %s", __func__, LSFResponseCodeText(responseCode));
        if (responseCode == LSF_OK) {
            sceneList = sceneIDs;
            LSFStringList::const_iterator it = sceneIDs.begin();
            uint8_t count = 1;
            for (; it != sceneIDs.end(); ++it) {
                printf("\n(%d)%s", count, (*it).c_str());
                count++;
            }
            printf("\n");
        }
        gotReply = true;
    }

    void GetSceneNameReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID, const LSFString& language, const LSFString& sceneName) {
        LSFString uniqueId = sceneID;

        printf("\n%s: responseCode = %s sceneID = %s language = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str(), language.c_str());

        if (responseCode == LSF_OK) {
            printf("\nsceneName = %s", sceneName.c_str());
        }
        gotReply = true;
        if (numRepliesToWait) {
            numRepliesToWait--;
        }
    }

    void SetSceneNameReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID, const LSFString& language) {
        LSFString uniqueId = sceneID;
        printf("\n%s: responseCode = %s sceneID = %s language = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str(), language.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void ScenesNameChangedCB(const LSFStringList& sceneIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = sceneIDs.begin();
        for (; it != sceneIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void CreateSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID) {
        printf("\n%s: responseCode=%s\n", __func__, LSFResponseCodeText(responseCode));
        if (LSF_OK == responseCode) {
            printf("sceneID=%s\n", sceneID.c_str());
            sceneList.push_back(sceneID);
        } else {
            gotSignal = true;
        }
        gotReply = true;
    }

    void CreateSceneWithSceneElementsReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID, const uint32_t& trackingID) {
        printf("\n%s: responseCode=%s\n", __func__, LSFResponseCodeText(responseCode));
        if (LSF_OK == responseCode) {
            printf("sceneID=%s\n", sceneID.c_str());
            printf("trackingID=%d\n", trackingID);
            sceneList.push_back(sceneID);
        } else {
            gotSignal = true;
        }
        gotReply = true;
    }

    void UpdateSceneWithSceneElementsReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID) {
        printf("\n%s: responseCode=%s\n", __func__, LSFResponseCodeText(responseCode));
        if (LSF_OK == responseCode) {
            printf("sceneID=%s\n", sceneID.c_str());
            sceneList.push_back(sceneID);
        } else {
            gotSignal = true;
        }
        gotReply = true;
    }

    void ScenesCreatedCB(const LSFStringList& sceneIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = sceneIDs.begin();
        for (; it != sceneIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void UpdateSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID) {
        printf("\n%s(): responseCode = %s, sceneID=%s\n", __func__, LSFResponseCodeText(responseCode), sceneID.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void ScenesUpdatedCB(const LSFStringList& sceneIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = sceneIDs.begin();
        for (; it != sceneIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void DeleteSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID) {
        printf("\n%s(): responseCode = %s, sceneID=%s\n", __func__, LSFResponseCodeText(responseCode), sceneID.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void ScenesDeletedCB(const LSFStringList& sceneIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = sceneIDs.begin();
        for (; it != sceneIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void ApplySceneReplyCB(const LSFResponseCode& responseCode, const LSFString& sceneID) {
        printf("\n%s(): responseCode = %s, sceneID=%s\n", __func__, LSFResponseCodeText(responseCode), sceneID.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void ScenesAppliedCB(const LSFStringList& sceneIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = sceneIDs.begin();
        for (; it != sceneIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }
};

class MasterSceneManagerCallbackHandler : public MasterSceneManagerCallback {
    void GetMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID, const MasterScene& masterScene) {
        printf("\n%s(): responseCode = %s, masterSceneID=%s\n", __func__, LSFResponseCodeText(responseCode), masterSceneID.c_str());
        if (responseCode == LSF_OK) {
            printf("\nmasterScene=%s", masterScene.c_str());
        }
        gotReply = true;
        if (numRepliesToWait) {
            numRepliesToWait--;
        }
    }

    void GetAllMasterSceneIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& masterSceneIDs) {
        printf("\n%s(): responseCode = %s", __func__, LSFResponseCodeText(responseCode));
        if (responseCode == LSF_OK) {
            LSFStringList::const_iterator it = masterSceneIDs.begin();
            uint8_t count = 1;
            for (; it != masterSceneIDs.end(); ++it) {
                printf("\n(%d)%s", count, (*it).c_str());
                count++;
            }
            printf("\n");
        }
        gotReply = true;
    }

    void GetMasterSceneNameReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID, const LSFString& language, const LSFString& masterSceneName) {
        LSFString uniqueId = masterSceneID;

        printf("\n%s: responseCode = %s masterSceneID = %s language = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str(), language.c_str());

        if (responseCode == LSF_OK) {
            printf("\nmasterSceneName = %s", masterSceneName.c_str());
        }
        gotReply = true;
        if (numRepliesToWait) {
            numRepliesToWait--;
        }
    }

    void SetMasterSceneNameReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID, const LSFString& language) {
        LSFString uniqueId = masterSceneID;
        printf("\n%s: responseCode = %s masterSceneID = %s language = %s", __func__, LSFResponseCodeText(responseCode), uniqueId.c_str(), language.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void MasterScenesNameChangedCB(const LSFStringList& masterSceneIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = masterSceneIDs.begin();
        for (; it != masterSceneIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void CreateMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID) {
        printf("\n%s: responseCode=%s\n", __func__, LSFResponseCodeText(responseCode));
        if (LSF_OK == responseCode) {
            printf("masterSceneID=%s\n", masterSceneID.c_str());
        } else {
            gotSignal = true;
        }
        gotReply = true;
    }

    void MasterScenesCreatedCB(const LSFStringList& masterSceneIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = masterSceneIDs.begin();
        for (; it != masterSceneIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void UpdateMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID) {
        printf("\n%s(): responseCode = %s, masterSceneID=%s\n", __func__, LSFResponseCodeText(responseCode), masterSceneID.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void MasterScenesUpdatedCB(const LSFStringList& masterSceneIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = masterSceneIDs.begin();
        for (; it != masterSceneIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void DeleteMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID) {
        printf("\n%s(): responseCode = %s, masterSceneID=%s\n", __func__, LSFResponseCodeText(responseCode), masterSceneID.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void MasterScenesDeletedCB(const LSFStringList& masterSceneIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = masterSceneIDs.begin();
        for (; it != masterSceneIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }

    void ApplyMasterSceneReplyCB(const LSFResponseCode& responseCode, const LSFString& masterSceneID) {
        printf("\n%s(): responseCode = %s, masterSceneID=%s\n", __func__, LSFResponseCodeText(responseCode), masterSceneID.c_str());
        gotReply = true;
        if (LSF_OK != responseCode) {
            gotSignal = true;
        }
    }

    void MasterScenesAppliedCB(const LSFStringList& masterSceneIDs) {
        printf("\n%s", __func__);
        LSFStringList::const_iterator it = masterSceneIDs.begin();
        for (; it != masterSceneIDs.end(); ++it) {
            printf("\n%s", (*it).c_str());
        }
        printf("\n");
        gotSignal = true;
    }
};

void PrintHelp() {
    printf("\nEnter one of the following command numbers to test end-to-end functionality:\n");
    printf("(1):   GetControllerServiceVersion\n");
    printf("(2):   LightingResetControllerService\n");
    printf("(3):   GetAllLampIDs\n");
    printf("(4):   GetLampManufacturer                              lampID\n");
    printf("(5):   GetLampSupportedLanguages                        lampID\n");
    printf("(6):   GetLampName                                      lampID\n");
    printf("(7):   SetLampName                                      lampID\n");
    printf("(8):   GetLampState                                     lampID\n");
    printf("(9):   GetLampStateOnOffField                           lampID\n");
    printf("(10):  GetLampStateHueField                             lampID\n");
    printf("(11):  GetLampStateSaturationField                      lampID\n");
    printf("(12):  GetLampStateBrightnessField                      lampID\n");
    printf("(13):  GetLampStateColorTempField                       lampID\n");
    printf("(14):  ResetLampState                                   lampID\n");
    printf("(15):  ResetLampStateOnOffField                         lampID\n");
    printf("(16):  ResetLampStateHueField                           lampID\n");
    printf("(17):  ResetLampStateSaturationField                    lampID\n");
    printf("(18):  ResetLampStateBrightnessField                    lampID\n");;
    printf("(19):  ResetLampStateColorTempField                     lampID\n");
    printf("(20):  TransitionLampState                              lampID\n");
    printf("(21):  PulseLampWithState                               lampID\n");
    printf("(22):  PulseLampWithPreset                              lampID toPresetID\n");
    printf("(23):  TransitionLampStateOnOffField                    lampID\n");
    printf("(24):  TransitionLampStateHueField                      lampID\n");
    printf("(25):  TransitionLampStateSaturationField               lampID\n");
    printf("(26):  TransitionLampStateBrightnessField               lampID\n");
    printf("(27):  TransitionLampStateColorTempField                lampID\n");
    printf("(28):  TransitionLampStateToPreset                      lampID presetID\n");
    printf("(29):  GetLampFaults                                    lampID\n");
    printf("(30):  ClearLampFault                                   lampID\n");
    printf("(31):  GetLampServiceVersion                            lampID\n");
    printf("(32):  GetLampDetails                                   lampID\n");
    printf("(33):  GetLampParameters                                lampID\n");
    printf("(34):  GetLampParametersEnergyUsageMilliwattsField      lampID\n");
    printf("(35):  GetLampParametersLumensField                     lampID\n");
    printf("(36):  GetAllLampGroupIDs\n");
    printf("(37):  GetLampGroupName                                 lampGoupID\n");;
    printf("(38):  SetLampGroupName                                 lampGoupID name\n");
    printf("(39):  CreateLampGroup\n");
    printf("(40):  UpdateLampGroup                                  lampGoupID\n");
    printf("(41):  DeleteLampGroup                                  lampGoupID\n");
    printf("(42):  GetLampGroup                                     lampGoupID\n");
    printf("(43):  ResetLampGroupState                              lampGoupID\n");
    printf("(44):  ResetLampGroupStateOnOffField                    lampGoupID\n");
    printf("(45):  ResetLampGroupStateHueField                      lampGoupID\n");
    printf("(46):  ResetLampGroupStateSaturationField               lampGoupID\n");
    printf("(47):  ResetLampGroupStateBrightnessField               lampGoupID\n");
    printf("(48):  ResetLampGroupStateColorTempField                lampGoupID\n");
    printf("(49):  TransitionLampGroupState                         lampGoupID\n");
    printf("(50):  PulseLampGroupWithState                          lampGoupID\n");
    printf("(51):  PulseLampGroupWithPreset                         lampGoupID toPresetID\n");
    printf("(52):  TransitionLampGroupStateOnOffField               lampGoupID\n");
    printf("(53):  TransitionLampGroupStateHueField                 lampGoupID\n");
    printf("(54):  TransitionLampGroupStateSaturationField          lampGoupID\n");
    printf("(55):  TransitionLampGroupStateBrightnessField          lampGoupID\n");
    printf("(56):  TransitionLampGroupStateColorTempField           lampGoupID\n");
    printf("(57):  TransitionLampGroupStateToPreset                 lampGoupID toPresetID\n");
    printf("(58):  GetDefaultLampState\n");
    printf("(59):  SetDefaultLampState\n");
    printf("(60):  GetAllPresetIDs\n");
    printf("(61):  GetPresetName                            presetID\n");
    printf("(62):  SetPresetName                            presetID name\n");
    printf("(63):  CreatePreset\n");
    printf("(64):  UpdatePreset                             presetID\n");
    printf("(65):  DeletePreset                             presetID\n");
    printf("(66):  GetPreset                                presetID\n");
    printf("(67):  GetAllSceneIDs\n");
    printf("(68):  GetSceneName                             sceneID\n");
    printf("(69):  SetSceneName                             sceneID name\n");
    printf("(70):  CreateScene\n");
    printf("(71):  UpdateScene                              sceneID\n");
    printf("(72):  DeleteScene                              sceneID\n");
    printf("(73):  GetScene                                 sceneID\n");
    printf("(74):  ApplyScene                               sceneID\n");
    printf("(75):  GetAllMasterSceneIDs\n");
    printf("(76):  GetMasterSceneName                       masterSceneID\n");
    printf("(77):  SetMasterSceneName                       masterSceneID name\n");
    printf("(78):  CreateMasterScene\n");
    printf("(79):  UpdateMasterScene                        masterSceneID\n");
    printf("(80):  DeleteMasterScene                        masterSceneID\n");
    printf("(81):  GetMasterScene                           masterSceneID\n");
    printf("(82):  ApplyMasterScene                         masterSceneID\n");
    printf("(83):  GetLampDataSet                           lampID\n");
    printf("(84):  GetLampGroupDataSet                      lampGroupID\n");
    printf("(85):  GetPresetDataSet                         presetID\n");
    printf("(86):  GetSceneDataSet                          sceneID\n");
    printf("(87):  GetMasterSceneDataSet                    masterSceneID\n");
    printf("(88):  Stop\n");
    printf("(89):  Start\n");
    printf("(90):  CreateTransitionEffect                   name\n");
    printf("(91):  CreateSceneElement                       name effectID lampID\n");
    printf("(92):  GetAllSceneElementIDs\n");
    printf("(93):  GetSceneElement                          sceneElementID\n");
    printf("(94):  ApplySceneElement                        sceneElementID\n");
    printf("(95):  CreateSceneWithSceneElements             [name [sceneElementID ...]]\n");
    printf("(96):  UpdateSceneWithSceneElements             sceneID [sceneElementID ...]\n");
    printf("(97):  GetSceneWithSceneElements                sceneID\n");
    printf("(98):  GetTransitionEffect                      transitionEffectID\n");
    printf("(99):  ApplyTransitionEffectOnLamps             transitionEffectID lampGroupIDs\n");
    printf("(100): ApplyTransitionEffectOnLampGroups        transitionEffectIDs lampGroupIDs\n");
    printf("(101): GetTransitionEffectName                  transitionEffectID\n");
    printf("(102): GetAllTransitionEffectIDs\n");
    printf("(103): SetTransitionEffectName                  transitionEffectID name\n");
    printf("(104): UpdateTransitionEffect                   transitionEffectID\n");
    printf("(105): DeleteTransitionEffect                   transitionEffectID\n");
    printf("(106): GetTransitionEffectDataSet               transitionEffectID\n");
    printf("(107): GetPulseEffect                           pulseEffectID\n");
    printf("(108): ApplyPulseEffectOnLamps                  pulseEffectID lampIDs\n");
    printf("(109): ApplyPulseEffectOnLampGroups             pulseEffectIDs lampGroupIDs\n");
    printf("(110): GetPulseEffectName                       pulseEffectID\n");
    printf("(111): GetAllPulseEffectIDs\n");
    printf("(112): SetPulseEffectName                       pulseEffectID name\n");
    printf("(113): UpdatePulseEffect                        pulseEffectID\n");
    printf("(114): DeletePulseEffect                        pulseEffectID\n");
    printf("(115): GetPulseEffectDataSet                    pulseEffectID\n");
    printf("(116): CreatePulseEffect                        name\n");
}

int main()
{

    AJInitializer ajInit;
    if (ajInit.Initialize() != ER_OK) {
        printf("Failed to initialize AllJoyn\n");
        return -1;
    }

    bool waitForReply = false;
    bool waitForSignal = false;
    bool unrecognizedCommand = false;

    BusAttachment bus("ClientTest", true);
    bus.Start();
    bus.Connect();

    ControllerClientCallbackHandler controllerClientCBHandler;
    ControllerServiceManagerCallbackHandler controllerServiceManagerCBHandler;
    LampManagerCallbackHandler lampManagerCBHandler;
    LampGroupManagerCallbackHandler lampGroupManagerCBHandler;
    PresetManagerCallbackHandler presetManagerCBHandler;
    TransitionEffectManagerCallbackHandler transitionEffectManagerCBHandler;
    SceneElementManagerCallbackHandler sceneElementManagerCBHandler;
    SceneManagerCallbackHandler sceneManagerCBHandler;
    MasterSceneManagerCallbackHandler masterSceneManagerCBHandler;
    PulseEffectManagerCallbackHandler pulseEffectManagerCBHandler;

    ControllerClient client(bus, controllerClientCBHandler);
    ControllerServiceManager controllerServiceManager(client, controllerServiceManagerCBHandler);
    LampManager lampManager(client, lampManagerCBHandler);
    LampGroupManager lampGroupManager(client, lampGroupManagerCBHandler);
    PresetManager presetManager(client, presetManagerCBHandler);
    TransitionEffectManager transitionEffectManager(client, transitionEffectManagerCBHandler);
    SceneElementManager sceneElementManager(client, sceneElementManagerCBHandler);
    SceneManager sceneManager(client, sceneManagerCBHandler);
    MasterSceneManager masterSceneManager(client, masterSceneManagerCBHandler);
    PulseEffectManager pulseEffectManager(client, pulseEffectManagerCBHandler);


    ControllerClientStatus status = client.Start();
    printf("\nController Client Start() returned %s\n", ControllerClientStatusText(status));

    printf("\nController Client Version = %d\n", client.GetVersion());

    printf("\nWaiting for the Controller Client to connect to a Controller Service!\n");

    //Wait for the Controller Client to find and connect to a Controller Service
    while (!connectedToControllerService) ;

    printf("\nController Client setup successful.\n");

    status = CONTROLLER_CLIENT_OK;
    const int bufSize = 1024;
    char buf[bufSize];

    while (true) {
        gotReply = false;
        gotSignal = false;

        waitForReply = false;
        waitForSignal = false;

        sleep(1);
        PrintHelp();

        if (get_line(buf, bufSize, stdin)) {
            String line(buf);
            String cmd = NextTok(line);

            if (cmd == "1") {
                printf("\nInvoking GetControllerServiceVersion()\n");
                status = controllerServiceManager.GetControllerServiceVersion();
                printf("\nReturn Status = %s\n", ControllerClientStatusText(status));
                waitForReply = true;
            } else if (cmd == "2") {
                status = controllerServiceManager.LightingResetControllerService();
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "3") {
                printf("\nInvoking GetAllLampIDs()\n");
                status = lampManager.GetAllLampIDs();
                waitForReply = true;
            } else if (cmd == "4") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetLampManufacturer(%s)\n", uniqueId.c_str());
                status = lampManager.GetLampManufacturer(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "5") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetLampSupportedLanguages(%s)\n", uniqueId.c_str());
                lampManager.GetLampSupportedLanguages(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "6") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetLampName(%s)\n", uniqueId.c_str());
                status = lampManager.GetLampName(uniqueId.c_str(), "en");
                waitForReply = true;
            } else if (cmd == "7") {
                String uniqueId = NextTok(line);
                String name = NextTok(line);
                printf("\nInvoking SetLampName(%s, %s)\n", uniqueId.c_str(), name.c_str());
                lampManager.SetLampName(uniqueId.c_str(), name.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "8") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetLampState(%s)\n", uniqueId.c_str());
                status = lampManager.GetLampState(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "9") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetLampStateOnOffField(%s)\n", uniqueId.c_str());
                lampManager.GetLampStateOnOffField(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "10") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetLampStateHueField(%s)\n", uniqueId.c_str());
                lampManager.GetLampStateHueField(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "11") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetLampStateSaturationField(%s)\n", uniqueId.c_str());
                lampManager.GetLampStateSaturationField(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "12") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetLampStateBrightnessField(%s)\n", uniqueId.c_str());
                lampManager.GetLampStateBrightnessField(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "13") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetLampStateColorTempField(%s)\n", uniqueId.c_str());
                lampManager.GetLampStateColorTempField(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "14") {
                String uniqueId = NextTok(line);
                printf("\nInvoking ResetLampState(%s)\n", uniqueId.c_str());
                lampManager.ResetLampState(uniqueId.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "15") {
                String uniqueId = NextTok(line);
                printf("\nInvoking ResetLampStateOnOffField(%s)\n", uniqueId.c_str());
                lampManager.ResetLampStateOnOffField(uniqueId.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "16") {
                String uniqueId = NextTok(line);
                printf("\nInvoking ResetLampStateHueField(%s)\n", uniqueId.c_str());
                lampManager.ResetLampStateHueField(uniqueId.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "17") {
                String uniqueId = NextTok(line);
                printf("\nInvoking ResetLampStateSaturationField(%s)\n", uniqueId.c_str());
                lampManager.ResetLampStateSaturationField(uniqueId.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "18") {
                String uniqueId = NextTok(line);
                printf("\nInvoking ResetLampStateBrightnessField(%s)\n", uniqueId.c_str());
                lampManager.ResetLampStateBrightnessField(uniqueId.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "19") {
                String uniqueId = NextTok(line);
                printf("\nInvoking ResetLampStateColorTempField(%s)\n", uniqueId.c_str());
                lampManager.ResetLampStateColorTempField(uniqueId.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "20") {
                String uniqueId = NextTok(line);
                LampState state(false, 7, 7, 7, 7);
                printf("\nInvoking TransitionLampState(%s)\n", uniqueId.c_str());
                lampManager.TransitionLampState(uniqueId.c_str(), state, 5);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "21") {
                String uniqueId = NextTok(line);
                LampState toState(false, 5, 5, 5, 5);
                LampState fromState(false, 7, 7, 7, 7);
                printf("\nInvoking PulseLampWithState(%s)\n", uniqueId.c_str());
                lampManager.PulseLampWithState(uniqueId.c_str(), toState, 100, 10, 20, fromState);
                waitForReply = true;
            } else if (cmd == "22") {
                String uniqueId = NextTok(line);
                String toState = NextTok(line);
                printf("\nInvoking PulseLampWithPreset(%s)\n", uniqueId.c_str());
                lampManager.PulseLampWithPreset(uniqueId.c_str(), LSFString(toState.c_str()), 100, 10, 20, LSFString(toState.c_str()));
                waitForReply = true;
            } else if (cmd == "23") {
                String uniqueId = NextTok(line);
                printf("\nInvoking TransitionLampStateOnOffField(%s)\n", uniqueId.c_str());
                lampManager.TransitionLampStateOnOffField(uniqueId.c_str(), true);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "24") {
                String uniqueId = NextTok(line);
                printf("\nInvoking TransitionLampStateHueField(%s)\n", uniqueId.c_str());
                lampManager.TransitionLampStateHueField(uniqueId.c_str(), 10, 100);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "25") {
                String uniqueId = NextTok(line);
                printf("\nInvoking TransitionLampStateSaturationField(%s)\n", uniqueId.c_str());
                lampManager.TransitionLampStateSaturationField(uniqueId.c_str(), 20);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "26") {
                String uniqueId = NextTok(line);
                printf("\nInvoking TransitionLampStateBrightnessField(%s)\n", uniqueId.c_str());
                lampManager.TransitionLampStateBrightnessField(uniqueId.c_str(), 30, 100);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "27") {
                String uniqueId = NextTok(line);
                printf("\nInvoking TransitionLampStateColorTempField(%s)\n", uniqueId.c_str());
                lampManager.TransitionLampStateColorTempField(uniqueId.c_str(), 50);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "28") {
                String uniqueId = NextTok(line);
                String presetID = NextTok(line);
                printf("\nInvoking TransitionLampStateToPreset(%s, %s)\n", uniqueId.c_str(), presetID.c_str());
                lampManager.TransitionLampStateToPreset(uniqueId.c_str(), presetID.c_str(), 25);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "29") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetLampFaults(%s)\n", uniqueId.c_str());
                status = lampManager.GetLampFaults(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "30") {
                String uniqueId = NextTok(line);
                LampFaultCode code = qcc::StringToU32(NextTok(line));
                printf("\nInvoking ClearLampFault(%s, %d)\n", uniqueId.c_str(), code);
                status = lampManager.ClearLampFault(uniqueId.c_str(), code);
                waitForReply = true;
            } else if (cmd == "31") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetLampServiceVersion(%s)\n", uniqueId.c_str());
                status = lampManager.GetLampServiceVersion(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "32") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetLampDetails(%s)\n", uniqueId.c_str());
                status = lampManager.GetLampDetails(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "33") {
                String uniqueId = NextTok(line);
                status = lampManager.GetLampParameters(uniqueId.c_str());
                printf("\nInvoking GetLampParameters(%s)\n", uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "34") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetLampParametersEnergyUsageMilliwattsField(%s)\n", uniqueId.c_str());
                lampManager.GetLampParametersEnergyUsageMilliwattsField(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "35") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetLampParametersLumensField(%s)\n", uniqueId.c_str());
                lampManager.GetLampParametersLumensField(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "36") {
                printf("\nInvoking GetAllLampGroupIDs()\n");
                status = lampGroupManager.GetAllLampGroupIDs();
                waitForReply = true;
            } else if (cmd == "37") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetLampGroupName(%s)\n", uniqueId.c_str());
                status = lampGroupManager.GetLampGroupName(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "38") {
                String uniqueId = NextTok(line);
                String name = NextTok(line);
                printf("\nInvoking SetLampGroupName(%s, %s)\n", uniqueId.c_str(), name.c_str());
                status = lampGroupManager.SetLampGroupName(uniqueId.c_str(), name.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "39") {
                for (uint8_t i = 0; i < 4; i++) {
                    LSFStringList lamps;
                    lamps.clear();
                    LSFStringList lampGroups;
                    lampGroups.clear();
                    if (lampList.empty()) {
                        printf("\nYou need to have 20 Lamp Services running for invoking this call. Also call GetAllLampIDs once before invoking this call.\n");
                        return 0;
                    }
                    lamps.push_back(lampList.front());
                    lampList.pop_front();
                    LampGroup group(lamps, lampGroups);
                    LSFString name = LSFString("01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123");
                    printf("\nInvoking CreateLampGroup(%s)\n", group.c_str());
                    status = lampGroupManager.CreateLampGroup(group, name);
                    waitForReply = true;
                    waitForSignal = true;
                    sleep(1);
                }
                for (uint8_t i = 0; i < 4; i++) {
                    LSFStringList lamps;
                    lamps.clear();
                    LSFStringList lampGroups;
                    lampGroups.clear();
                    if (lampList.empty()) {
                        printf("\nYou need to have 20 Lamp Services running for invoking this call. Also call GetAllLampIDs once before invoking this call.\n");
                        return 0;
                    }
                    lamps.push_back(lampList.front());
                    lampList.pop_front();
                    if (lampGroupList.size()) {
                        lampGroups.push_back(lampGroupList.front());
                        lampGroupList.pop_front();
                    } else {
                        printf("\nError");
                        return 0;
                    }
                    LampGroup group(lamps, lampGroups);
                    printf("\nInvoking CreateLampGroup(%s)\n", group.c_str());
                    LSFString name = LSFString("SampleLampGroup");
                    status = lampGroupManager.CreateLampGroup(group, name);
                    waitForReply = true;
                    waitForSignal = true;
                    sleep(1);
                }
#if 0
                LSFStringList lamps;
                LSFStringList lampGroups;
                lamps.clear();
                lampGroups.clear();
                lamps.push_back(LSFString("9006470d13d65e07f286caf63b89fb03"));
                lamps.push_back(LSFString("89c339ab8ea15eff7239ced786458f0d"));
                lamps.push_back(LSFString("9006470d13d65e07f286caf63b89fb03"));
                LampGroup group(lamps, lampGroups);
                printf("\nInvoking CreateLampGroup(%s)\n", group.c_str());
                LSFString name = LSFString("SampleLampGroup");
                status = lampGroupManager.CreateLampGroup(group, name);
                waitForReply = true;
                waitForSignal = true;
#endif
            } else if (cmd == "40") {
                String uniqueId = NextTok(line);
                LSFStringList lamps;
                LSFStringList lampGroups;
                lamps.push_back(LSFString("9006470d13d65e07f286caf63b89fb03"));
                lampGroups.push_back(LSFString("LAMP_GROUP1FE42B366FB3D943"));
                LampGroup group(lamps, lampGroups);
                printf("\nInvoking UpdateLampGroup(%s, %s)\n", uniqueId.c_str(), group.c_str());
                status = lampGroupManager.UpdateLampGroup(uniqueId.c_str(), group);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "41") {
                String uniqueId = NextTok(line);
                printf("\nInvoking DeleteLampGroup(%s)\n", uniqueId.c_str());
                status = lampGroupManager.DeleteLampGroup(uniqueId.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "42") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetLampGroup(%s)\n", uniqueId.c_str());
                status = lampGroupManager.GetLampGroup(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "43") {
                String uniqueId = NextTok(line);
                printf("\nInvoking ResetLampGroupState(%s)\n", uniqueId.c_str());
                lampGroupManager.ResetLampGroupState(uniqueId.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "44") {
                String uniqueId = NextTok(line);
                printf("\nInvoking ResetLampGroupStateOnOffField(%s)\n", uniqueId.c_str());
                lampGroupManager.ResetLampGroupStateOnOffField(uniqueId.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "45") {
                String uniqueId = NextTok(line);
                printf("\nInvoking ResetLampGroupStateHueField(%s)\n", uniqueId.c_str());
                lampGroupManager.ResetLampGroupStateHueField(uniqueId.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "46") {
                String uniqueId = NextTok(line);
                printf("\nInvoking ResetLampGroupStateSaturationField(%s)\n", uniqueId.c_str());
                lampGroupManager.ResetLampGroupStateSaturationField(uniqueId.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "47") {
                String uniqueId = NextTok(line);
                printf("\nInvoking ResetLampGroupStateBrightnessField(%s)\n", uniqueId.c_str());
                lampGroupManager.ResetLampGroupStateBrightnessField(uniqueId.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "48") {
                String uniqueId = NextTok(line);
                printf("\nInvoking ResetLampGroupStateColorTempField(%s)\n", uniqueId.c_str());
                lampGroupManager.ResetLampGroupStateColorTempField(uniqueId.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "49") {
                String uniqueId = NextTok(line);
                LampState state(false, 7, 7, 7, 7);
                printf("\nInvoking TransitionLampGroupState(%s)\n", uniqueId.c_str());
                lampGroupManager.TransitionLampGroupState(uniqueId.c_str(), state, 5);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "50") {
                String uniqueId = NextTok(line);
                LampState toState(false, 5, 5, 5, 5);
                LampState fromState(false, 7, 7, 7, 7);
                printf("\nInvoking PulseLampGroupWithState(%s)\n", uniqueId.c_str());
                lampGroupManager.PulseLampGroupWithState(uniqueId.c_str(), toState, 100, 10, 20, fromState);
                waitForReply = true;
            } else if (cmd == "51") {
                String uniqueId = NextTok(line);
                String toState = NextTok(line);
                printf("\nInvoking PulseLampGroupWithPreset(%s)\n", uniqueId.c_str());
                lampGroupManager.PulseLampGroupWithPreset(uniqueId.c_str(), LSFString(toState.c_str()), 100, 10, 20, LSFString(toState.c_str()));
                waitForReply = true;
            } else if (cmd == "52") {
                String uniqueId = NextTok(line);
                printf("\nInvoking TransitionLampGroupStateOnOffField(%s)\n", uniqueId.c_str());
                lampGroupManager.TransitionLampGroupStateOnOffField(uniqueId.c_str(), true);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "53") {
                String uniqueId = NextTok(line);
                printf("\nInvoking TransitionLampGroupStateHueField(%s)\n", uniqueId.c_str());
                lampGroupManager.TransitionLampGroupStateHueField(uniqueId.c_str(), 10, 100);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "54") {
                String uniqueId = NextTok(line);
                printf("\nInvoking TransitionLampGroupStateSaturationField(%s)\n", uniqueId.c_str());
                lampGroupManager.TransitionLampGroupStateSaturationField(uniqueId.c_str(), 20);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "55") {
                String uniqueId = NextTok(line);
                printf("\nInvoking TransitionLampGroupStateBrightnessField(%s)\n", uniqueId.c_str());
                lampGroupManager.TransitionLampGroupStateBrightnessField(uniqueId.c_str(), 30, 100);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "56") {
                String uniqueId = NextTok(line);
                printf("\nInvoking TransitionLampGroupStateColorTempField(%s)\n", uniqueId.c_str());
                lampGroupManager.TransitionLampGroupStateColorTempField(uniqueId.c_str(), 50);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "57") {
                String uniqueId = NextTok(line);
                String presetID = NextTok(line);
                printf("\nInvoking TransitionLampGroupStateToPreset(%s, %s)\n", uniqueId.c_str(), presetID.c_str());
                lampGroupManager.TransitionLampGroupStateToPreset(uniqueId.c_str(), presetID.c_str(), 25);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "58") {
                printf("\nInvoking GetDefaultLampState()\n");
                status = presetManager.GetDefaultLampState();
                waitForReply = true;
            } else if (cmd == "59") {
                printf("\nInvoking SetDefaultLampState()\n");
                LampState state(true, 3, 3, 3, 3);
                status = presetManager.SetDefaultLampState(state);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "60") {
                printf("\nInvoking GetAllPresetIDs()\n");
                status = presetManager.GetAllPresetIDs();
                waitForReply = true;
            } else if (cmd == "61") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetPresetName(%s)\n", uniqueId.c_str());
                status = presetManager.GetPresetName(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "62") {
                String uniqueId = NextTok(line);
                String name = NextTok(line);
                printf("\nInvoking SetPresetName(%s, %s)\n", uniqueId.c_str(), name.c_str());
                status = presetManager.SetPresetName(uniqueId.c_str(), name.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "63") {
                LampState state(true, 5, 5, 5, 5);
                printf("\nInvoking CreatePreset(%s)\n", state.c_str());
                LSFString name = LSFString("SamplePreset");
                status = presetManager.CreatePreset(state, name);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "64") {
                String uniqueId = NextTok(line);
                LampState state(true, 6, 6, 6, 6);
                printf("\nInvoking UpdatePreset(%s, %s)\n", uniqueId.c_str(), state.c_str());
                status = presetManager.UpdatePreset(uniqueId.c_str(), state);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "65") {
                String uniqueId = NextTok(line);
                printf("\nInvoking DeletePreset(%s)\n", uniqueId.c_str());
                status = presetManager.DeletePreset(uniqueId.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "66") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetPreset(%s)\n", uniqueId.c_str());
                status = presetManager.GetPreset(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "67") {
                printf("\nInvoking GetAllSceneIDs()\n");
                status = sceneManager.GetAllSceneIDs();
                waitForReply = true;
            } else if (cmd == "68") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetSceneName(%s)\n", uniqueId.c_str());
                status = sceneManager.GetSceneName(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "69") {
                String uniqueId = NextTok(line);
                String name = NextTok(line);
                printf("\nInvoking SetSceneName(%s, %s)\n", uniqueId.c_str(), name.c_str());
                status = sceneManager.SetSceneName(uniqueId.c_str(), name.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "70") {
                LSFStringList lamps1;
                LSFStringList lampGroups1;
                lamps1.clear();
                lampGroups1.clear();
                if (lampList.empty()) {
                    printf("\nYou need to have 20 Lamp Services running for invoking this call. Also call GetAllLampIDs once before invoking this call.\n");
                    return 0;
                }
                lamps1.push_back(lampList.front());
                lampList.pop_front();

                if (lampGroupList.size()) {
                    lampGroups1.push_back(lampGroupList.front());
                    lampGroupList.pop_front();
                } else {
                    printf("\nError");
                    return 0;
                }
                LampState state(true, 3, 3, 3, 3);
                uint32_t transPeriod = 35;
                TransitionLampsLampGroupsToState transitionToStateComponent(lamps1, lampGroups1, state, transPeriod);

                LSFStringList lamps2;
                LSFStringList lampGroups2;
                lamps2.clear();
                lampGroups2.clear();
                if (lampList.empty()) {
                    printf("\nYou need to have 20 Lamp Services running for invoking this call. Also call GetAllLampIDs once before invoking this call.\n");
                    return 0;
                }
                lamps2.push_back(lampList.front());
                lampList.pop_front();
                if (lampGroupList.size()) {
                    lampGroups2.push_back(lampGroupList.front());
                    lampGroupList.pop_front();
                } else {
                    printf("\nError");
                    return 0;
                }
                if (presetList.empty()) {
                    printf("\nYou need to have 2 Presets created for invoking this call\n");
                    return 0;
                }
                TransitionLampsLampGroupsToPreset transitionToPresetComponent(lamps2, lampGroups2, presetList.front(), transPeriod);
                presetList.pop_front();

                uint32_t period = 100;
                uint32_t duration = 20;
                uint32_t numPulses = 25;
                LSFStringList lamps3;
                LSFStringList lampGroups3;
                lamps3.clear();
                lampGroups3.clear();
                if (lampList.empty()) {
                    printf("\nYou need to have 20 Lamp Services running for invoking this call. Also call GetAllLampIDs once before invoking this call.\n");
                    return 0;
                }
                lamps3.push_back(lampList.front());
                lampList.pop_front();
                if (lampGroupList.size()) {
                    lampGroups3.push_back(lampGroupList.front());
                    lampGroupList.pop_front();
                } else {
                    printf("\nError");
                    return 0;
                }
                PulseLampsLampGroupsWithState pulseWithStateComponent(lamps3, lampGroups3, state, period, duration, numPulses);

                LSFStringList lamps4;
                LSFStringList lampGroups4;
                lamps4.clear();
                lampGroups4.clear();
                if (lampList.empty()) {
                    printf("\nYou need to have 20 Lamp Services running for invoking this call. Also call GetAllLampIDs once before invoking this call.\n");
                    return 0;
                }
                lamps4.push_back(lampList.front());
                lampList.pop_front();
                if (lampGroupList.size()) {
                    lampGroups4.push_back(lampGroupList.front());
                    lampGroupList.pop_front();
                } else {
                    printf("\nError");
                    return 0;
                }

                if (presetList.empty()) {
                    printf("\nYou need to have 2 Presets created for invoking this call\n");
                    return 0;
                }
                PulseLampsLampGroupsWithPreset pulseWithPresetComponent(lamps4, lampGroups4, presetList.front(), period, duration, numPulses);
                presetList.pop_front();

                TransitionLampsLampGroupsToStateList transitionToStateList;
                transitionToStateList.push_back(transitionToStateComponent);

                TransitionLampsLampGroupsToPresetList transitionToPresetList;
                transitionToPresetList.push_back(transitionToPresetComponent);

                PulseLampsLampGroupsWithStateList pulseWithStateList;
                pulseWithStateList.push_back(pulseWithStateComponent);

                PulseLampsLampGroupsWithPresetList pulseWithPresetList;
                pulseWithPresetList.push_back(pulseWithPresetComponent);

                Scene scene(transitionToStateList, transitionToPresetList, pulseWithStateList, pulseWithPresetList);

                printf("\nInvoking CreateScene(%s)\n", scene.c_str());
                LSFString name = LSFString("SampleScene");
                status = sceneManager.CreateScene(scene, name);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "71") {
                String uniqueId = NextTok(line);

                LSFStringList lampList;
                lampList.push_back("ABC");
                LSFStringList lampGroupList;
                lampGroupList.push_back("XYZ");
                LampState state(false, 7, 7, 7, 7);
                LampState toState(false, 5, 5, 5, 5);
                LSFString presetID = LSFString("123");
                LSFString toPresetID = LSFString("xyz");
                TransitionLampsLampGroupsToState transitionToStateComponent(lampList, lampGroupList, state);
                TransitionLampsLampGroupsToPreset transitionToPresetComponent(lampList, lampGroupList, presetID);
                uint32_t period = 100;
                uint32_t duration = 20;
                uint32_t numPulses = 25;
                PulseLampsLampGroupsWithState pulseWithStateComponent(lampList, lampGroupList, state, toState, period, duration, numPulses);
                PulseLampsLampGroupsWithPreset pulseWithPresetComponent(lampList, lampGroupList, presetID, toPresetID, period, duration, numPulses);

                TransitionLampsLampGroupsToStateList transitionToStateList;
                transitionToStateList.push_back(transitionToStateComponent);

                TransitionLampsLampGroupsToPresetList transitionToPresetList;
                transitionToPresetList.push_back(transitionToPresetComponent);

                PulseLampsLampGroupsWithStateList pulseWithStateList;
                pulseWithStateList.push_back(pulseWithStateComponent);

                PulseLampsLampGroupsWithPresetList pulseWithPresetList;
                pulseWithPresetList.push_back(pulseWithPresetComponent);

                Scene scene(transitionToStateList, transitionToPresetList, pulseWithStateList, pulseWithPresetList);

                printf("\nInvoking UpdateScene(%s, %s)\n", uniqueId.c_str(), scene.c_str());
                status = sceneManager.UpdateScene(uniqueId.c_str(), scene);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "72") {
                String uniqueId = NextTok(line);
                printf("\nInvoking DeleteScene(%s)\n", uniqueId.c_str());
                status = sceneManager.DeleteScene(uniqueId.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "73") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetScene(%s)\n", uniqueId.c_str());
                status = sceneManager.GetScene(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "74") {
                String uniqueId = NextTok(line);
                printf("\nInvoking ApplyScene(%s)\n", uniqueId.c_str());
                status = sceneManager.ApplyScene(uniqueId.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "75") {
                printf("\nInvoking GetAllMasterSceneIDs()\n");
                status = masterSceneManager.GetAllMasterSceneIDs();
                waitForReply = true;
            } else if (cmd == "76") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetMasterSceneName(%s)\n", uniqueId.c_str());
                status = masterSceneManager.GetMasterSceneName(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "77") {
                String uniqueId = NextTok(line);
                String name = NextTok(line);
                printf("\nInvoking SetMasterSceneName(%s, %s)\n", uniqueId.c_str(), name.c_str());
                status = masterSceneManager.SetMasterSceneName(uniqueId.c_str(), name.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "78") {
                if (sceneList.empty()) {
                    printf("\nYou need to have a Scene Created for invoking this call\n");
                    return 0;
                }
                MasterScene group(sceneList);
                printf("\nInvoking CreateMasterScene(%s)\n", group.c_str());
                LSFString name = LSFString("SampleMasterScene");
                status = masterSceneManager.CreateMasterScene(group, name);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "79") {
                String uniqueId = NextTok(line);
                LSFStringList scenes;
                scenes.push_back("123");
                scenes.push_back("456");
                MasterScene group(scenes);
                printf("\nInvoking UpdateMasterScene(%s, %s)\n", uniqueId.c_str(), group.c_str());
                status = masterSceneManager.UpdateMasterScene(uniqueId.c_str(), group);
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "80") {
                String uniqueId = NextTok(line);
                printf("\nInvoking DeleteMasterScene(%s)\n", uniqueId.c_str());
                status = masterSceneManager.DeleteMasterScene(uniqueId.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "81") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetMasterScene(%s)\n", uniqueId.c_str());
                status = masterSceneManager.GetMasterScene(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "82") {
                String uniqueId = NextTok(line);
                printf("\nInvoking ApplyMasterScene(%s)\n", uniqueId.c_str());
                status = masterSceneManager.ApplyMasterScene(uniqueId.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "83") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetLampDataSet(%s)\n", uniqueId.c_str());
                status = lampManager.GetConsolidatedLampDataSet(uniqueId.c_str());
                waitForReply = true;
            } else if (cmd == "84") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetLampGroupDataSet(%s)\n", uniqueId.c_str());
                status = lampGroupManager.GetLampGroupDataSet(uniqueId.c_str());
                numRepliesToWait = 2;
            } else if (cmd == "85") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetPresetDataSet(%s)\n", uniqueId.c_str());
                status = presetManager.GetPresetDataSet(uniqueId.c_str());
                numRepliesToWait = 2;
            } else if (cmd == "86") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetSceneDataSet(%s)\n", uniqueId.c_str());
                status = sceneManager.GetSceneDataSet(uniqueId.c_str());
                numRepliesToWait = 2;
            } else if (cmd == "87") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetMasterSceneDataSet(%s)\n", uniqueId.c_str());
                status = masterSceneManager.GetMasterSceneDataSet(uniqueId.c_str());
                numRepliesToWait = 2;
            } else if (cmd == "88") {
                printf("\nInvoking Stop()");
                status = client.Stop();
                printf("\nController Client Stop() returned %s\n", ControllerClientStatusText(status));
            } else if (cmd == "89") {
                printf("\nInvoking Start()");
                status = client.Start();
                printf("\nController Client Start() returned %s\n", ControllerClientStatusText(status));
            } else if (cmd == "90") {
                printf("\nInvoking CreateTransitionEffect(%s)", line.c_str());
                uint32_t trackingID = 0;
                LampState state(true, 2147483648u, 2147483648u, 2147483648u, 2147483648u);
                uint32_t transitionPeriod = 5000;
                String name = NextTok(line);

                TransitionEffect transitionEffect(state, transitionPeriod);
                status = transitionEffectManager.CreateTransitionEffect(trackingID, transitionEffect, name.c_str());
                printf("\nCreateTransitionEffect() returned %s\n", ControllerClientStatusText(status));
            } else if (cmd == "91") {
                printf("\nInvoking CreateSceneElement(%s)", line.c_str());
                uint32_t trackingID = 0;
                LSFStringList lamps;
                LSFStringList lampGroups;
                String name = NextTok(line);
                String effectId = NextTok(line);
                String lampId = NextTok(line);

                lamps.clear();
                lamps.push_back(lampId.c_str());

                lampGroups.clear();

                SceneElement sceneElement(lamps, lampGroups, effectId.c_str());
                status = sceneElementManager.CreateSceneElement(trackingID, sceneElement, name.c_str());
                printf("\nCreateSceneElement() returned %s\n", ControllerClientStatusText(status));
            } else if (cmd == "92") {
                printf("\nInvoking GetAllSceneElementIDs()\n");
                status = sceneElementManager.GetAllSceneElementIDs();
                printf("GetAllSceneElementIDs() returned %s\n", ControllerClientStatusText(status));
                waitForReply = true;
            } else if (cmd == "93") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetSceneElement(%s)\n", uniqueId.c_str());
                status = sceneElementManager.GetSceneElement(uniqueId.c_str());
                printf("GetSceneElement() returned %s\n", ControllerClientStatusText(status));
                waitForReply = true;
            } else if (cmd == "94") {
                String uniqueId = NextTok(line);
                printf("\nInvoking ApplySceneElement(%s)\n", uniqueId.c_str());
                status = sceneElementManager.ApplySceneElement(uniqueId.c_str());
                printf("ApplySceneElement() returned %s\n", ControllerClientStatusText(status));
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "95") {
                String sceneElementName = NextTok(line);
                String sceneElementID = NextTok(line);

                if (sceneElementName.empty()) {
                    sceneElementName = String("SampleSceneWithSceneElements");
                }

                LSFStringList sceneElementIDs;
                while (!sceneElementID.empty()) {
                    sceneElementIDs.push_back(sceneElementID.c_str());
                    sceneElementID = NextTok(line);
                }

                if (sceneElementIDs.empty()) {
                    sceneElementIDs = allSceneElementIDs;
                }
                if (sceneElementIDs.empty()) {
                    printf("\nYou need to call GetAllSceneElementIDs before making this call,\n");
                    printf("or specify at least one scene element ID in the command.\n");
                    return 0;
                }
                uint32_t trackingID = -1;
                SceneWithSceneElements sceneWithSceneElements(sceneElementIDs);
                printf("\nInvoking CreateSceneWithSceneElements(%s %s)\n", sceneElementName.c_str(), sceneWithSceneElements.c_str());
                status = sceneManager.CreateSceneWithSceneElements(trackingID, sceneWithSceneElements, LSFString(sceneElementName.c_str()));
                printf("CreateSceneWithSceneElements() tracking ID = %d, status = %s\n", trackingID, ControllerClientStatusText(status));
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "96") {
                String sceneID = NextTok(line);
                String sceneElementID = NextTok(line);

                LSFStringList sceneElementIDs;
                while (!sceneElementID.empty()) {
                    sceneElementIDs.push_back(sceneElementID.c_str());
                    sceneElementID = NextTok(line);
                }
                if (sceneElementIDs.empty()) {
                    sceneElementIDs = allSceneElementIDs;
                }
                if (sceneElementIDs.empty()) {
                    printf("\nYou need to call GetAllSceneElementIDs before making this call,\n");
                    printf("or specify at least one scene element ID in the command.\n");
                    return 0;
                }
                SceneWithSceneElements sceneWithSceneElements(sceneElementIDs);
                printf("\nInvoking UpdateSceneWithSceneElements(%s %s)\n", sceneID.c_str(), sceneWithSceneElements.c_str());
                status = sceneManager.UpdateSceneWithSceneElements(LSFString(sceneID.c_str()), sceneWithSceneElements);
                printf("UpdateSceneWithSceneElements() status = %s\n", ControllerClientStatusText(status));
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "97") {
                String sceneID = NextTok(line);
                printf("\nInvoking GetSceneWithSceneElements(%s)\n", sceneID.c_str());
                status = sceneManager.GetSceneWithSceneElements(sceneID.c_str());
                waitForReply = true;
            } else if (cmd == "98") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetTransitionEffect(%s)\n", uniqueId.c_str());
                status = transitionEffectManager.GetTransitionEffect(uniqueId.c_str());
                printf("GetTransitionEffect() returned %s\n", ControllerClientStatusText(status));
                waitForReply = true;
            } else if (cmd == "99") {
                LSFStringList lamps;
                String transitionEffectID = NextTok(line);
                String lampID = NextTok(line);
                lamps.clear();
                lamps.push_back(lampID.c_str());

                status = transitionEffectManager.ApplyTransitionEffectOnLamps(transitionEffectID.c_str(), lamps);
                printf("\nApplyTransitionEffectOnLamps() returned %s\n", ControllerClientStatusText(status));
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "100") {
                LSFStringList lampGroupIDs;
                String transitionEffectID = NextTok(line);
                String lampGroupID = NextTok(line);
                lampGroupIDs.clear();
                lampGroupIDs.push_back(lampGroupID.c_str());

                status = transitionEffectManager.ApplyTransitionEffectOnLampGroups(transitionEffectID.c_str(), lampGroupIDs);
                printf("\nApplyTransitionEffectOnLampGroups() returned %s\n", ControllerClientStatusText(status));
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "101") {
                ;
                String transitionEffectID = NextTok(line);
                printf("\nInvoking GetTransitionEffectName(%s)\n", transitionEffectID.c_str());
                status = transitionEffectManager.GetTransitionEffectName(transitionEffectID.c_str());
                waitForReply = true;
            } else if (cmd == "102") {
                String transitionEffectID = NextTok(line);
                printf("\nInvoking GetAllTransitionEffectIDs()\n");
                status = transitionEffectManager.GetAllTransitionEffectIDs();
                waitForReply = true;
            } else if (cmd == "103") {
                String uniqueId = NextTok(line);
                String name = NextTok(line);
                printf("\nInvoking SetTransitionEffectName(%s, %s)\n", uniqueId.c_str(), name.c_str());
                status = transitionEffectManager.SetTransitionEffectName(uniqueId.c_str(), name.c_str());
                //waitForReply = true;
                //waitForSignal = true;
            } else if (cmd == "104") {
                String transitionEffectID = NextTok(line);
                printf("\nInvoking UpdateTransitionEffect(%s)\n", transitionEffectID.c_str());
                LampState state(true, 2147483648u, 2147483648u, 2147483648u, 2147483648u);

                uint32_t transitionPeriod = 5000;
                TransitionEffect transitionEffect(state, transitionPeriod);

                status = transitionEffectManager.UpdateTransitionEffect(transitionEffectID.c_str(), transitionEffect);
                printf("\nUpdateTransitionEffect returned %s\n", ControllerClientStatusText(status));
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "105") {
                String transitionEffectID = NextTok(line);
                printf("\nInvoking DeleteTransitionEffect(%s)\n", transitionEffectID.c_str());
                status = transitionEffectManager.DeleteTransitionEffect(transitionEffectID.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "106") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetTransitionEffectDataSet(%s)\n", uniqueId.c_str());
                status = transitionEffectManager.GetTransitionEffectDataSet(uniqueId.c_str());
                numRepliesToWait = 2;
            }  else if (cmd == "107") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetPulseEffect(%s)\n", uniqueId.c_str());
                status = pulseEffectManager.GetPulseEffect(uniqueId.c_str());
                printf("GetPulseEffect() returned %s\n", ControllerClientStatusText(status));
                waitForReply = true;
                //waitForSignal = true;
            } else if (cmd == "108") {
                LSFStringList lamps;
                String pulseEffectID = NextTok(line);
                String lampID = NextTok(line);
                lamps.clear();
                lamps.push_back(lampID.c_str());

                status = pulseEffectManager.ApplyPulseEffectOnLamps(pulseEffectID.c_str(), lamps);
                printf("\nApplyPulseEffectOnLamps() returned %s\n", ControllerClientStatusText(status));
                waitForReply = true;
            } else if (cmd == "109") {
                LSFStringList lampGroupIDs;
                String pulseEffectID = NextTok(line);
                String lampGroupID = NextTok(line);
                lampGroupIDs.clear();
                lampGroupIDs.push_back(lampGroupID.c_str());

                status = pulseEffectManager.ApplyPulseEffectOnLampGroups(pulseEffectID.c_str(), lampGroupIDs);
                printf("\nApplyPulseEffectOnLampGroups() returned %s\n", ControllerClientStatusText(status));
                waitForReply = true;
                //waitForSignal = true;
            } else if (cmd == "110") {
                String pulseEffectID = NextTok(line);
                printf("\nInvoking GetPulseEffectName(%s)\n", pulseEffectID.c_str());
                status = pulseEffectManager.GetPulseEffectName(pulseEffectID.c_str());
                waitForReply = true;
            } else if (cmd == "111") {
                String pulseEffectID = NextTok(line);
                printf("\nInvoking GetAllPulseEffectIDs()\n");
                status = pulseEffectManager.GetAllPulseEffectIDs();
                waitForReply = true;
            } else if (cmd == "112") {
                // printf("(114):  SetPulseEffectName        pulseEffectID pulseEffectName\n");
                String uniqueId = NextTok(line);
                String name = NextTok(line);
                printf("\nInvoking SetPulseEffectName(%s, %s)\n", uniqueId.c_str(), name.c_str());
                status = pulseEffectManager.SetPulseEffectName(uniqueId.c_str(), name.c_str());
                //waitForReply = true;
                //waitForSignal = true;
            } else if (cmd == "113") {
                String pulseEffectID = NextTok(line);
                printf("\nInvoking UpdatePulseEffect(%s)\n", pulseEffectID.c_str());
                LampState toState(true, 2147483648u, 2147483648u, 2147483648u, 2147483648u);
                LampState fromState(true, 0, 0, 0, 0);
                uint32_t pulsePeriod = 5000;
                uint32_t pulseDuration = 1000;
                uint32_t numPulses = 5;
                String name = NextTok(line);
                PulseEffect(toState, pulsePeriod, pulseDuration, numPulses, fromState);
                PulseEffect pulseEffect(toState, pulsePeriod, pulseDuration, numPulses, fromState);
                status = pulseEffectManager.UpdatePulseEffect(pulseEffectID.c_str(), pulseEffect);
                printf("\nUpdatePulseEffect returned %s\n", ControllerClientStatusText(status));
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "114") {
                String pulseEffectID = NextTok(line);
                printf("\nInvoking DeletePulseEffect(%s)\n", pulseEffectID.c_str());
                status = pulseEffectManager.DeletePulseEffect(pulseEffectID.c_str());
                waitForReply = true;
                waitForSignal = true;
            } else if (cmd == "115") {
                String uniqueId = NextTok(line);
                printf("\nInvoking GetPulseEffectDataSet(%s)\n", uniqueId.c_str());
                status = pulseEffectManager.GetPulseEffectDataSet(uniqueId.c_str());
                numRepliesToWait = 2;
            } else if (cmd == "116") {
                printf("\nInvoking CreatePulseEffect(%s)", line.c_str());
                uint32_t trackingID = 0;
                LampState toState(true, 2147483648u, 2147483648u, 2147483648u, 2147483648u);
                LampState fromState(true, 5, 5, 5, 5);
                uint32_t pulsePeriod = 5000;
                uint32_t pulseDuration = 1000;
                uint32_t numPulses = 10;
                String name = NextTok(line);
                PulseEffect(toState, pulsePeriod, pulseDuration, numPulses, fromState);
                PulseEffect pulseEffect(toState, pulsePeriod, pulseDuration, numPulses, fromState);
                status = pulseEffectManager.CreatePulseEffect(trackingID, pulseEffect, name.c_str());
                printf("\nCreatePulseEffect returned %s\n", ControllerClientStatusText(status));
            } else if (cmd == "help") {
                PrintHelp();
            } else if (cmd == "exit") {
                break;
            } else {
                //unrecognizedCommand = true;
            }

            if (unrecognizedCommand) {
                printf("\nInvalid Command\n");
                unrecognizedCommand = false;
            } else {
                if (status == CONTROLLER_CLIENT_OK) {
                    printf("\nSent command successfully\n");
                    if (numRepliesToWait > 0) {
                        while (numRepliesToWait > 0) {
                            printf("\nnumRepliesToWait\n");
                        }
                    } else {
                        if (waitForReply) {
                            while (!gotReply) ;
                        }
                        if (waitForSignal) {
                            while (!gotSignal) ;
                        }
                        sleep(3);
                    }
                } else {
                    printf("\nCommand send failed\n");
                }
            }
        }
    }
    bus.Stop();
    bus.Join();
}
