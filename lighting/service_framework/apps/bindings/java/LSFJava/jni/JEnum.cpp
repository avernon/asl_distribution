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

#include <qcc/Debug.h>

#include <LampValues.h>             // lighting/service_framework
#include <ControllerClientDefs.h>   // lighting/service_framework
#include <LSFResponseCodes.h>       // lighting/service_framework

#include "NUtil.h"
#include "JEnum.h"

#define QCC_MODULE "AJN-LSF-JNI"

namespace lsf {

// If the enums in LampValues.h, ControllerClientDefs.h, or LSFResponseCodes.h
// change, then you should get compilation errors in the typedef statements
// below. In that case, to fix the errors you should update the corresponding
// Java enum class, and then update the expected last value here.
#define HAS_LAST_VALUE_CHANGED_IN_LAMP_MAKE                             (MAKE_LASTVALUE                  ==  3)
#define HAS_LAST_VALUE_CHANGED_IN_LAMP_MODEL                            (MODEL_LASTVALUE                 ==  2)
#define HAS_LAST_VALUE_CHANGED_IN_DEVICE_TYPE                           (TYPE_LASTVALUE                  ==  5)
#define HAS_LAST_VALUE_CHANGED_IN_LAMP_TYPE                             (LAMPTYPE_LASTVALUE              == 92)
#define HAS_LAST_VALUE_CHANGED_IN_BASE_TYPE                             (BASETYPE_LASTVALUE              == 11)
#define HAS_LAST_VALUE_CHANGED_IN_ERROR_CODE                            (ERROR_LAST_VALUE                ==  7)
#define HAS_LAST_VALUE_CHANGED_IN_CONTROLLER_CLIENT_STATUS              (CONTROLLER_CLIENT_LAST_VALUE    ==  4)
#define HAS_LAST_VALUE_CHANGED_IN_RESPONSE_CODE                         (LSF_RESPONSE_CODE_LAST          == 19)

// You should get compilation failures here if the enums in LampValues.h,
// ControllerClientDefs.h, or LSFResponseCodes.h change (see comment above on
// how to fix).
typedef char Need_to_update_enum_values_in_LampMake_java                [HAS_LAST_VALUE_CHANGED_IN_LAMP_MAKE                ? 1 : -1];
typedef char Need_to_update_enum_values_in_LampModel_java               [HAS_LAST_VALUE_CHANGED_IN_LAMP_MODEL               ? 1 : -1];
typedef char Need_to_update_enum_values_in_DeviceType_java              [HAS_LAST_VALUE_CHANGED_IN_DEVICE_TYPE              ? 1 : -1];
typedef char Need_to_update_enum_values_in_LampType_java                [HAS_LAST_VALUE_CHANGED_IN_LAMP_TYPE                ? 1 : -1];
typedef char Need_to_update_enum_values_in_BaseType_java                [HAS_LAST_VALUE_CHANGED_IN_BASE_TYPE                ? 1 : -1];
typedef char Need_to_update_enum_values_in_ErrorCode_java               [HAS_LAST_VALUE_CHANGED_IN_ERROR_CODE               ? 1 : -1];
typedef char Need_to_update_enum_values_in_ControllerClientStatus_java  [HAS_LAST_VALUE_CHANGED_IN_CONTROLLER_CLIENT_STATUS ? 1 : -1];
typedef char Need_to_update_enum_values_in_ResponseCode_java            [HAS_LAST_VALUE_CHANGED_IN_RESPONSE_CODE            ? 1 : -1];

JEnum* JEnum::jLampMakeEnum = new JEnum("org/allseen/lsf/LampMake");
JEnum* JEnum::jLampModelEnum = new JEnum("org/allseen/lsf/LampModel");
JEnum* JEnum::jDeviceTypeEnum = new JEnum("org/allseen/lsf/DeviceType");
JEnum* JEnum::jLampTypeEnum = new JEnum("org/allseen/lsf/LampType");
JEnum* JEnum::jBaseTypeEnum = new JEnum("org/allseen/lsf/BaseType");

JEnum* JEnum::jErrorCodeEnum = new JEnum("org/allseen/lsf/ErrorCode");
JEnum* JEnum::jControllerClientStatusEnum = new JEnum("org/allseen/lsf/ControllerClientStatus");
JEnum* JEnum::jResponseCodeEnum = new JEnum("org/allseen/lsf/ResponseCode");

JEnum* JEnum::jStatusCodeEnum = new JEnum("org/alljoyn/bus/Status", "create", "getErrorCode");

JEnum::JEnum(char const *className)
{
    init(className, "fromValue", "getValue");
}

JEnum::JEnum(char const *className, char const *objMethodName, char const *intMethodName)
{
    init(className, objMethodName, intMethodName);
}

JEnum::~JEnum()
{
    JScopedEnv env;

    if (clsEnum) {
        env->DeleteGlobalRef(clsEnum);
    }
}

char const *JEnum::getClassName()
{
    return clsName;
}

jclass JEnum::getClass()
{
    return clsEnum;
}

jobject JEnum::getObject(int value)
{
    JScopedEnv env;

    if (!clsEnum) {
        create();
    }

    return (clsEnum && midFromValue) ? env->CallStaticObjectMethod(clsEnum, midFromValue, value) : NULL;
}

jint JEnum::getValue(jobject jobj)
{
    JScopedEnv env;

    if (!clsEnum) {
        create();
    }

    return (clsEnum && midGetValue) ? env->CallIntMethod(jobj, midGetValue) : (jint)-1;
}

void JEnum::init(char const *className, char const *objMethodName, char const *intMethodName)
{
    clsName = className;
    objMetName = objMethodName;
    intMetName = intMethodName;
    clsEnum = NULL;
    midFromValue = NULL;
    midGetValue = NULL;
}

void JEnum::create()
{
    JScopedEnv env;

    jclass clazz = env->FindClass(clsName);
    if (env->ExceptionCheck() || !clazz) {
        QCC_LogError(ER_FAIL, ("FindClass() failed"));
        return;
    }

    clsEnum = (jclass)env->NewGlobalRef(clazz);
    if (env->ExceptionCheck() || !clsEnum) {
        QCC_LogError(ER_FAIL, ("NewGlobalRef() failed"));
        return;
    }

    char sig[128];
    snprintf(sig, sizeof(sig), "(I)L%s;", clsName);

    midFromValue = env->GetStaticMethodID(clsEnum, objMetName, sig);
    if (env->ExceptionCheck() || !midFromValue) {
        QCC_LogError(ER_FAIL, ("GetStaticMethodID() failed"));
        return;
    }

    midGetValue = env->GetMethodID(clsEnum, intMetName, "()I");
    if (env->ExceptionCheck() || !midGetValue) {
        QCC_LogError(ER_FAIL, ("GetMethodID() failed"));
        return;
    }
}

} /* namespace lsf */
