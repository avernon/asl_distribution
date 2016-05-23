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
 *
 ******************************************************************************/

#include <qcc/Debug.h>

#include "JControllerClient.h"
#include "JLampManager.h"
#include "JLampManagerCallback.h"
#include "JLampState.h"
#include "NUtil.h"
#include "XCppDelegator.h"

#include "org_allseen_lsf_LampManager.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;
using namespace lsf;

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_getAllLampIDs(JNIEnv *env, jobject thiz)
{
    return XCppDelegator::Call_ControllerClientStatus<JLampManager>(env, thiz, &JLampManager::GetAllLampIDs);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_getLampManufacturer(JNIEnv *env, jobject thiz, jstring jLampID, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String<JLampManager>(env, thiz, jLampID, jLanguage, &JLampManager::GetLampManufacturer);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_getLampName(JNIEnv *env, jobject thiz, jstring jLampID, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String<JLampManager>(env, thiz, jLampID, jLanguage, &JLampManager::GetLampName);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_setLampName(JNIEnv *env, jobject thiz, jstring jLampID, jstring jLampName, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String_String<JLampManager>(env, thiz, jLampID, jLampName, jLanguage, &JLampManager::SetLampName);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_getLampDetails(JNIEnv *env, jobject thiz, jstring jLampID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<JLampManager>(env, thiz, jLampID, &JLampManager::GetLampDetails);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_getLampParameters(JNIEnv *env, jobject thiz, jstring jLampID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<JLampManager>(env, thiz, jLampID, &JLampManager::GetLampParameters);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_getLampParametersEnergyUsageMilliwattsField(JNIEnv *env, jobject thiz, jstring jLampID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<JLampManager>(env, thiz, jLampID, &JLampManager::GetLampParametersEnergyUsageMilliwattsField);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_getLampParametersLumensField(JNIEnv *env, jobject thiz, jstring jLampID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<JLampManager>(env, thiz, jLampID, &JLampManager::GetLampParametersLumensField);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_getLampState(JNIEnv *env, jobject thiz, jstring jLampID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<JLampManager>(env, thiz, jLampID, &JLampManager::GetLampState);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_getLampStateOnOffField(JNIEnv *env, jobject thiz, jstring jLampID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<JLampManager>(env, thiz, jLampID, &JLampManager::GetLampStateOnOffField);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_getLampStateHueField(JNIEnv *env, jobject thiz, jstring jLampID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<JLampManager>(env, thiz, jLampID, &JLampManager::GetLampStateHueField);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_getLampStateSaturationField(JNIEnv *env, jobject thiz, jstring jLampID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<JLampManager>(env, thiz, jLampID, &JLampManager::GetLampStateSaturationField);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_getLampStateBrightnessField(JNIEnv *env, jobject thiz, jstring jLampID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<JLampManager>(env, thiz, jLampID, &JLampManager::GetLampStateBrightnessField);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_getLampStateColorTempField(JNIEnv *env, jobject thiz, jstring jLampID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<JLampManager>(env, thiz, jLampID, &JLampManager::GetLampStateColorTempField);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_resetLampState(JNIEnv *env, jobject thiz, jstring jLampID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<JLampManager>(env, thiz, jLampID, &JLampManager::ResetLampState);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_resetLampStateOnOffField(JNIEnv *env, jobject thiz, jstring jLampID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<JLampManager>(env, thiz, jLampID, &JLampManager::ResetLampStateOnOffField);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_resetLampStateHueField(JNIEnv *env, jobject thiz, jstring jLampID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<JLampManager>(env, thiz, jLampID, &JLampManager::ResetLampStateHueField);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_resetLampStateSaturationField(JNIEnv *env, jobject thiz, jstring jLampID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<JLampManager>(env, thiz, jLampID, &JLampManager::ResetLampStateSaturationField);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_resetLampStateBrightnessField(JNIEnv *env, jobject thiz, jstring jLampID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<JLampManager>(env, thiz, jLampID, &JLampManager::ResetLampStateBrightnessField);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_resetLampStateColorTempField(JNIEnv *env, jobject thiz, jstring jLampID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<JLampManager>(env, thiz, jLampID, &JLampManager::ResetLampStateColorTempField);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_transitionLampState(JNIEnv *env, jobject thiz, jstring jLampID, jobject jLampState, jlong jTransitionPeriod)
{
    return XCppDelegator::Call_ControllerClientStatus_String_Object_UInt32<JLampManager, JLampState, LampState>(env, thiz, jLampID, jLampState, jTransitionPeriod, &JLampManager::TransitionLampState);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_pulseLampWithState(JNIEnv *env, jobject thiz, jstring jLampID, jobject jToLampState, jlong jPeriod, jlong jDuration, jlong jNumPulses, jobject jFromLampState)
{
    return XCppDelegator::Call_ControllerClientStatus_String_Object_UInt32_UInt32_UInt32_Object<JLampManager, JLampState, LampState>(env, thiz, jLampID, jToLampState, jPeriod, jDuration, jNumPulses, jFromLampState, &JLampManager::PulseLampWithState);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_pulseLampWithPreset(JNIEnv *env, jobject thiz, jstring jLampID, jstring jToPresetID, jlong jPeriod, jlong jDuration, jlong jNumPulses, jstring jFromPresetID)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String_UInt32_UInt32_UInt32_String(env, thiz, jLampID, jToPresetID, jPeriod, jDuration, jNumPulses, jFromPresetID, &JLampManager::PulseLampWithPreset);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_transitionLampStateOnOffField(JNIEnv *env, jobject thiz, jstring jLampID, jboolean jOnOff)
{
    return XCppDelegator::Call_ControllerClientStatus_String_Boolean<JLampManager>(env, thiz, jLampID, jOnOff, &JLampManager::TransitionLampStateOnOffField);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_transitionLampStateHueField(JNIEnv *env, jobject thiz, jstring jLampID, jlong jHue, jlong jTransitionPeriod )
{
    return XCppDelegator::Call_ControllerClientStatus_String_UInt32_UInt32<JLampManager>(env, thiz, jLampID, jHue, jTransitionPeriod, &JLampManager::TransitionLampStateHueField);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_transitionLampStateSaturationField(JNIEnv *env, jobject thiz, jstring jLampID, jlong jSaturation, jlong jTransitionPeriod)
{
    return XCppDelegator::Call_ControllerClientStatus_String_UInt32_UInt32<JLampManager>(env, thiz, jLampID, jSaturation, jTransitionPeriod, &JLampManager::TransitionLampStateSaturationField);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_transitionLampStateBrightnessField(JNIEnv *env, jobject thiz, jstring jLampID, jlong jBrightness, jlong jTransitionPeriod)
{
    return XCppDelegator::Call_ControllerClientStatus_String_UInt32_UInt32<JLampManager>(env, thiz, jLampID, jBrightness, jTransitionPeriod, &JLampManager::TransitionLampStateBrightnessField);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_transitionLampStateColorTempField(JNIEnv *env, jobject thiz, jstring jLampID, jlong jColorTemp, jlong jTransitionPeriod)
{
    return XCppDelegator::Call_ControllerClientStatus_String_UInt32_UInt32<JLampManager>(env, thiz, jLampID, jColorTemp, jTransitionPeriod, &JLampManager::TransitionLampStateColorTempField);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_transitionLampStateToPreset(JNIEnv *env, jobject thiz, jstring jLampID, jstring jPresetID, jlong jTransitionPeriod)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String_UInt32<JLampManager>(env, thiz, jLampID, jPresetID, jTransitionPeriod, &JLampManager::TransitionLampStateToPreset);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_getLampFaults(JNIEnv *env, jobject thiz, jstring jLampID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<JLampManager>(env, thiz, jLampID, &JLampManager::GetLampFaults);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_getLampServiceVersion(JNIEnv *env, jobject thiz, jstring jLampID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<JLampManager>(env, thiz, jLampID, &JLampManager::GetLampServiceVersion);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_clearLampFault(JNIEnv *env, jobject thiz, jstring jLampID, jlong jFaultCode)
{
    return XCppDelegator::Call_ControllerClientStatus_String_UInt32<JLampManager>(env, thiz, jLampID, jFaultCode, &JLampManager::ClearLampFault);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_getLampSupportedLanguages(JNIEnv *env, jobject thiz, jstring jLampID)
{
    return XCppDelegator::Call_ControllerClientStatus_String<JLampManager>(env, thiz, jLampID, &JLampManager::GetLampSupportedLanguages);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_getLampDataSet(JNIEnv *env, jobject thiz, jstring jLampID, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String<JLampManager>(env, thiz, jLampID, jLanguage, &JLampManager::GetLampDataSet);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_getConsolidatedLampDataSet(JNIEnv *env, jobject thiz, jstring jLampID, jstring jLanguage)
{
    return XCppDelegator::Call_ControllerClientStatus_String_String<JLampManager>(env, thiz, jLampID, jLanguage, &JLampManager::GetConsolidatedLampDataSet);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_getLampVersion(JNIEnv *env, jobject thiz, jstring jLampID)
{
    // TODO-FIX uncomment once GetLampVersion has implementation in ControllerClient
//    return XCppDelegator::Call_ControllerClientStatus_String<JLampManager>(env, thiz, jLampID, &JLampManager::GetLampVersion);
    return NULL;
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampManager_setLampEffect(JNIEnv *env, jobject thiz, jstring jLampID, jstring jEffectID)
{
    // TODO-FIX uncomment once SetLampEffect has implementation in ControllerClient
//    return XCppDelegator::Call_ControllerClientStatus_String_String<JLampManager>(env, thiz, jLampID, jEffectID, &JLampManager::SetLampEffect);
    return NULL;
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_LampManager_createNativeObject(JNIEnv *env, jobject thiz, jobject controller, jobject callback)
{
    JControllerClient *jcc = GetHandle<JControllerClient*>(controller);
    if (!jcc) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    JLampManagerCallback *jlmcb = GetHandle<JLampManagerCallback*>(callback);
    if (!jlmcb) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    JLampManager* jlm = new JLampManager(thiz, *jcc, *jlmcb);
    if (!jlm) {
        QCC_LogError(ER_FAIL, ("JLampManager() failed"));
        return;
    }

    CreateHandle<JLampManager>(thiz, jlm);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_LampManager_destroyNativeObject(JNIEnv *env, jobject thiz)
{
    DestroyHandle<JLampManager>(thiz);
}
