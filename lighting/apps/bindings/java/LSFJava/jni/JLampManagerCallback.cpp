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

#include "JEnum.h"
#include "JEnumArray.h"
#include "JLampDetails.h"
#include "JLampManagerCallback.h"
#include "JLampParameters.h"
#include "JLampState.h"
#include "JStringArray.h"
#include "XJavaDelegator.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace ajn;

namespace lsf {

JLampManagerCallback::JLampManagerCallback(jobject jobj)
{
    JNIEnv* env = GetEnv();

    /*
     * Be careful when using a weak global reference.  They can only be
     * passed to NewLocalRef, NewGlobalRef and DeleteWeakGlobalRef.
     */
    QCC_DbgPrintf(("Taking weak global reference to Java object %p", jobj));
    jdelegate = env->NewWeakGlobalRef(jobj);
    if (env->ExceptionCheck() || !jdelegate) {
        QCC_LogError(ER_FAIL, ("NewWeakGlobalRef() failed"));
        return;
    }
}

JLampManagerCallback::~JLampManagerCallback()
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    env->DeleteWeakGlobalRef(jdelegate);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("DeleteWeakGlobalRef() failed"));
        return;
    }
}

void JLampManagerCallback::GetAllLampIDsReplyCB(const LSFResponseCode& responseCode, const LSFStringList& lampIDs)
{
    XJavaDelegator::Call_Void_ResponseCode_StringList(jdelegate, __func__, responseCode, lampIDs);
}

void JLampManagerCallback::GetLampNameReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFString& language, const LSFString& lampName)
{
    XJavaDelegator::Call_Void_ResponseCode_String_String_String(jdelegate, __func__, responseCode, lampID, language, lampName);
}

void JLampManagerCallback::GetLampManufacturerReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFString& language, const LSFString& manufacturer)
{
    XJavaDelegator::Call_Void_ResponseCode_String_String_String(jdelegate, __func__, responseCode, lampID, language, manufacturer);
}

void JLampManagerCallback::SetLampNameReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFString& language)
{
    XJavaDelegator::Call_Void_ResponseCode_String_String(jdelegate, __func__, responseCode, lampID, language);
}

void JLampManagerCallback::LampNameChangedCB(const LSFString& lampID, const LSFString& lampName)
{
    XJavaDelegator::Call_Void_String_String(jdelegate, __func__, lampID, lampName);
}

void JLampManagerCallback::LampsFoundCB(const LSFStringList& lampIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, lampIDs);
}

void JLampManagerCallback::LampsLostCB(const LSFStringList& lampIDs)
{
    XJavaDelegator::Call_Void_StringList(jdelegate, __func__, lampIDs);
}

void JLampManagerCallback::GetLampDetailsReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampDetails& lampDetails)
{
    XJavaDelegator::Call_Void_ResponseCode_String_Object<LampDetails, JLampDetails>(jdelegate, __func__, XClass::xLampDetails, responseCode, lampID, lampDetails);
}

void JLampManagerCallback::GetLampParametersReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampParameters& lampParameters)
{
    XJavaDelegator::Call_Void_ResponseCode_String_Object<LampParameters, JLampParameters>(jdelegate, __func__, XClass::xLampParameters, responseCode, lampID, lampParameters);
}

void JLampManagerCallback::GetLampParametersEnergyUsageMilliwattsFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& energyUsageMilliwatts)
{
    XJavaDelegator::Call_Void_ResponseCode_String_UInt32(jdelegate, __func__, responseCode, lampID, energyUsageMilliwatts);
}

void JLampManagerCallback::GetLampParametersLumensFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& brightnessLumens)
{
    XJavaDelegator::Call_Void_ResponseCode_String_UInt32(jdelegate, __func__, responseCode, lampID, brightnessLumens);
}

void JLampManagerCallback::GetLampStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampState& lampState)
{
    XJavaDelegator::Call_Void_ResponseCode_String_Object<LampState, JLampState>(jdelegate, __func__, XClass::xLampState, responseCode, lampID, lampState);
}

void JLampManagerCallback::GetLampStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const bool& onOff)
{
    XJavaDelegator::Call_Void_ResponseCode_String_Boolean(jdelegate, __func__, responseCode, lampID, onOff);
}

void JLampManagerCallback::GetLampStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& hue)
{
    XJavaDelegator::Call_Void_ResponseCode_String_UInt32(jdelegate, __func__, responseCode, lampID, hue);
}

void JLampManagerCallback::GetLampStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& saturation)
{
    XJavaDelegator::Call_Void_ResponseCode_String_UInt32(jdelegate, __func__, responseCode, lampID, saturation);
}

void JLampManagerCallback::GetLampStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& brightness)
{
    XJavaDelegator::Call_Void_ResponseCode_String_UInt32(jdelegate, __func__, responseCode, lampID, brightness);
}

void JLampManagerCallback::GetLampStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& colorTemp)
{
    XJavaDelegator::Call_Void_ResponseCode_String_UInt32(jdelegate, __func__, responseCode, lampID, colorTemp);
}

void JLampManagerCallback::ResetLampStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampID);
}

void JLampManagerCallback::LampStateChangedCB(const LSFString& lampID, const LampState& lampState)
{
    XJavaDelegator::Call_Void_String_Object<LampState, JLampState>(jdelegate, __func__, XClass::xLampState, lampID, lampState);
}

void JLampManagerCallback::TransitionLampStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampID);
}

void JLampManagerCallback::PulseLampWithStateReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampID);
}

void JLampManagerCallback::PulseLampWithPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampID);
}

void JLampManagerCallback::TransitionLampStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampID);
}

void JLampManagerCallback::TransitionLampStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampID);
}

void JLampManagerCallback::TransitionLampStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampID);
}

void JLampManagerCallback::TransitionLampStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampID);
}

void JLampManagerCallback::TransitionLampStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampID);
}

void JLampManagerCallback::GetLampFaultsReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampFaultCodeList& faultCodes)
{
    XJavaDelegator::Call_Void_ResponseCode_String_UInt32List(jdelegate, __func__, responseCode, lampID, faultCodes);
}

void JLampManagerCallback::GetLampServiceVersionReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const uint32_t& lampServiceVersion)
{
    XJavaDelegator::Call_Void_ResponseCode_String_UInt32(jdelegate, __func__, responseCode, lampID, lampServiceVersion);
}

void JLampManagerCallback::ClearLampFaultReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LampFaultCode& faultCode)
{
    XJavaDelegator::Call_Void_ResponseCode_String_UInt32(jdelegate, __func__, responseCode, lampID, faultCode);
}

void JLampManagerCallback::ResetLampStateOnOffFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampID);
}

void JLampManagerCallback::ResetLampStateHueFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampID);
}

void JLampManagerCallback::ResetLampStateSaturationFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampID);
}

void JLampManagerCallback::ResetLampStateBrightnessFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampID);
}

void JLampManagerCallback::ResetLampStateColorTempFieldReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampID);
}

void JLampManagerCallback::TransitionLampStateToPresetReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID)
{
    XJavaDelegator::Call_Void_ResponseCode_String(jdelegate, __func__, responseCode, lampID);
}

void JLampManagerCallback::GetLampSupportedLanguagesReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFStringList& supportedLanguages)
{
    XJavaDelegator::Call_Void_ResponseCode_String_StringList(jdelegate, __func__, responseCode, lampID, supportedLanguages);
}

void JLampManagerCallback::SetLampEffectReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFString& effectID)
{
    XJavaDelegator::Call_Void_ResponseCode_String_String(jdelegate, __func__, responseCode, lampID, effectID);
}

void JLampManagerCallback::GetConsolidatedLampDataSetReplyCB(const LSFResponseCode& responseCode, const LSFString& lampID, const LSFString& language, const LSFString& lampName, const LampDetails& lampDetails, const LampState& lampState, const LampParameters& lampParameters)
{
    XJavaDelegator::Call_Void_ResponseCode_String_String_String_Object_Object_Object<LampDetails, JLampDetails, LampState, JLampState, LampParameters, JLampParameters>(jdelegate, __func__, XClass::xLampDetails, XClass::xLampState, XClass::xLampParameters, responseCode, lampID, language, lampName, lampDetails, lampState, lampParameters);
}

} /* namespace lsf */
