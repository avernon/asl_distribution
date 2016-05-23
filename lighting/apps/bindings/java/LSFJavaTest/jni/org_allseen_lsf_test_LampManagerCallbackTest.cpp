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

#include <stdio.h>
#include <stddef.h>

#include <qcc/Debug.h>
#include <qcc/Log.h>

#include "JEnum.h"
#include "JEnumArray.h"
#include "JLampDetails.h"
#include "JLampManagerCallback.h"
#include "JLampParameters.h"
#include "JLampState.h"
#include "JStringArray.h"
#include "NTypes.h"
#include "NUtil.h"

#include "JLampState.h"
#include "JLampManagerCallback.h"
#include "XCppTestDelegator.h"

#include "org_allseen_lsf_test_LampManagerCallbackTest.h"
#define QCC_MODULE "AJN-LSF-JNI-TEST"

using namespace ajn;
using namespace lsf;


JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_lampNameChangedCB(JNIEnv *env, jobject thiz, jobject jCallback, jstring jLampID, jstring jLampName)
{
    return XCppTestDelegator::Call_Void_String_String<JLampManagerCallback>(env, jCallback, jLampID, jLampName, &JLampManagerCallback::LampNameChangedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_lampsFoundCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jLampIDs)
{
    return XCppTestDelegator::Call_Void_StringList<JLampManagerCallback>(env, jCallback, jLampIDs, &JLampManagerCallback::LampsFoundCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_lampsLostCB(JNIEnv *env, jobject thiz, jobject jCallback, jobjectArray jLampIDs)
{
    return XCppTestDelegator::Call_Void_StringList<JLampManagerCallback>(env, jCallback, jLampIDs, &JLampManagerCallback::LampsLostCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_getLampParametersEnergyUsageMilliwattsFieldReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID, jlong jEnergyUsageMilliwatts)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_UInt32<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, jEnergyUsageMilliwatts, &JLampManagerCallback::GetLampParametersEnergyUsageMilliwattsFieldReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_getLampParametersLumensFieldReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID, jlong jBrightnessLumens)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_UInt32<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, jBrightnessLumens, &JLampManagerCallback::GetLampParametersLumensFieldReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_getLampStateOnOffFieldReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID, jboolean jOnOff)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_Boolean<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, jOnOff, &JLampManagerCallback::GetLampStateOnOffFieldReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_getLampStateHueFieldReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID, jlong jHue)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_UInt32<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, jHue, &JLampManagerCallback::GetLampStateHueFieldReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_getLampStateSaturationFieldReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID, jlong jSaturation)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_UInt32<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, jSaturation, &JLampManagerCallback::GetLampStateSaturationFieldReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_getLampStateBrightnessFieldReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID, jlong jBrightness)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_UInt32<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, jBrightness, &JLampManagerCallback::GetLampStateBrightnessFieldReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_getLampStateColorTempFieldReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID, jlong jColorTemp)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_UInt32<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, jColorTemp, &JLampManagerCallback::GetLampStateColorTempFieldReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_clearLampFaultReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID, jlong jFaultCode)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_UInt32<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, jFaultCode, &JLampManagerCallback::ClearLampFaultReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_lampStateChangedCB(JNIEnv *env, jobject thiz, jobject jCallback, jstring jLampID, jobject jLampState)
{
    return XCppTestDelegator::Call_Void_String_Object<JLampManagerCallback, JLampState, LampState>(env, jCallback, jLampID, jLampState, &JLampManagerCallback::LampStateChangedCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_getLampFaultsReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID, jlongArray jfaultCodes)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_UInt32List<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, jfaultCodes, &JLampManagerCallback::GetLampFaultsReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_getLampServiceVersionReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID, jlong jLampServiceVersion)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_UInt32<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, jLampServiceVersion, &JLampManagerCallback::GetLampServiceVersionReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_getLampSupportedLanguagesReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID, jobjectArray jSupportedLanguages)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_StringList<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, jSupportedLanguages, &JLampManagerCallback::GetLampSupportedLanguagesReplyCB, __func__);
}


JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_getAllLampIDsReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jobjectArray jLampIDs)
{
    return XCppTestDelegator::Call_Void_ResponseCode_StringList<JLampManagerCallback>(env, jCallback, jResponseCode, jLampIDs, &JLampManagerCallback::GetAllLampIDsReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_getLampNameReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID, jstring jLanguage, jstring jLampName)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_String_String<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, jLanguage, jLampName, &JLampManagerCallback::GetLampNameReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_getLampManufacturerReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID, jstring jLanguage, jstring jManufacturer)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_String_String<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, jLanguage, jManufacturer, &JLampManagerCallback::GetLampManufacturerReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_setLampNameReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID, jstring jLanguage)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_String<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, jLanguage, &JLampManagerCallback::SetLampNameReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_getLampStateReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID, jobject jLampState)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_Object<JLampManagerCallback, JLampState, LampState>(env, jCallback, jResponseCode, jLampID, jLampState, &JLampManagerCallback::GetLampStateReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_getLampDetailsReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID, jobject jLampDetails)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_Object<JLampManagerCallback, JLampDetails, LampDetails>(env, jCallback, jResponseCode, jLampID, jLampDetails, &JLampManagerCallback::GetLampDetailsReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_getLampParametersReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID, jobject jLampParameters)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_Object<JLampManagerCallback, JLampParameters, LampParameters>(env, jCallback, jResponseCode, jLampID, jLampParameters, &JLampManagerCallback::GetLampParametersReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_resetLampStateReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, &JLampManagerCallback::ResetLampStateReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_transitionLampStateReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, &JLampManagerCallback::TransitionLampStateReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_pulseLampWithStateReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, &JLampManagerCallback::PulseLampWithStateReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_pulseLampWithPresetReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, &JLampManagerCallback::PulseLampWithPresetReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_transitionLampStateOnOffFieldReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, &JLampManagerCallback::TransitionLampStateOnOffFieldReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_transitionLampStateHueFieldReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, &JLampManagerCallback::TransitionLampStateHueFieldReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_transitionLampStateSaturationFieldReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, &JLampManagerCallback::TransitionLampStateSaturationFieldReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_transitionLampStateBrightnessFieldReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, &JLampManagerCallback::TransitionLampStateBrightnessFieldReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_transitionLampStateColorTempFieldReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, &JLampManagerCallback::TransitionLampStateColorTempFieldReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_resetLampStateOnOffFieldReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, &JLampManagerCallback::ResetLampStateOnOffFieldReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_resetLampStateHueFieldReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, &JLampManagerCallback::ResetLampStateHueFieldReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_resetLampStateSaturationFieldReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, &JLampManagerCallback::ResetLampStateSaturationFieldReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_resetLampStateBrightnessFieldReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, &JLampManagerCallback::ResetLampStateBrightnessFieldReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_resetLampStateColorTempFieldReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, &JLampManagerCallback::ResetLampStateColorTempFieldReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_transitionLampStateToPresetReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, &JLampManagerCallback::TransitionLampStateToPresetReplyCB, __func__);
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_test_LampManagerCallbackTest_setLampEffectReplyCB(JNIEnv *env, jobject thiz, jobject jCallback, jobject jResponseCode, jstring jLampID, jstring jEffectID)
{
    return XCppTestDelegator::Call_Void_ResponseCode_String_String<JLampManagerCallback>(env, jCallback, jResponseCode, jLampID, jEffectID, &JLampManagerCallback::SetLampEffectReplyCB, __func__);
}


#undef QCC_MODULE



