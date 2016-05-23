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
#include <qcc/Log.h>

#include "JEnum.h"
#include "JLampDetails.h"

#include "NUtil.h"

#include "org_allseen_lsf_sdk_LampDetails.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace lsf;

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_sdk_LampDetails_getMake(JNIEnv *env, jobject thiz)
{
    JLampDetails* xLampDetails = GetHandle<JLampDetails*>(thiz);
    if (env->ExceptionCheck() || !xLampDetails) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    LampMake cLampMake = xLampDetails->make;

    return JEnum::jLampMakeEnum->getObject((int)cLampMake);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_sdk_LampDetails_getModel(JNIEnv *env, jobject thiz)
{
    JLampDetails* xLampDetails = GetHandle<JLampDetails*>(thiz);
    if (env->ExceptionCheck() || !xLampDetails) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    LampModel cLampModel = xLampDetails->model;

    return JEnum::jLampModelEnum->getObject((int)cLampModel);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_sdk_LampDetails_getType(JNIEnv *env, jobject thiz)
{
    JLampDetails* xLampDetails = GetHandle<JLampDetails*>(thiz);
    if (env->ExceptionCheck() || !xLampDetails) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    DeviceType cDeviceType = xLampDetails->type;

    return JEnum::jDeviceTypeEnum->getObject((int)cDeviceType);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_sdk_LampDetails_getLampType(JNIEnv *env, jobject thiz)
{
    JLampDetails* xLampDetails = GetHandle<JLampDetails*>(thiz);
    if (env->ExceptionCheck() || !xLampDetails) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    LampType cLampType = xLampDetails->lampType;

    return JEnum::jLampTypeEnum->getObject((int)cLampType);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_sdk_LampDetails_getLampBaseType(JNIEnv *env, jobject thiz)
{
    JLampDetails* xLampDetails = GetHandle<JLampDetails*>(thiz);
    if (env->ExceptionCheck() || !xLampDetails) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    BaseType cBaseType = xLampDetails->lampBaseType;

    return JEnum::jBaseTypeEnum->getObject((int)cBaseType);
}

JNIEXPORT
jint JNICALL Java_org_allseen_lsf_sdk_LampDetails_getLampBeamAngle(JNIEnv *env, jobject thiz)
{
    JLampDetails* xLampDetails = GetHandle<JLampDetails*>(thiz);
    if (env->ExceptionCheck() || !xLampDetails) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return 0;
    }

    return (jint)xLampDetails->lampBeamAngle;
}

JNIEXPORT
jboolean JNICALL Java_org_allseen_lsf_sdk_LampDetails_isDimmable(JNIEnv *env, jobject thiz)
{
    JLampDetails* xLampDetails = GetHandle<JLampDetails*>(thiz);
    if (env->ExceptionCheck() || !xLampDetails) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return 0;
    }

    return (jboolean)xLampDetails->dimmable;
}

JNIEXPORT
jboolean JNICALL Java_org_allseen_lsf_sdk_LampDetails_hasColor(JNIEnv *env, jobject thiz)
{
    JLampDetails* xLampDetails = GetHandle<JLampDetails*>(thiz);
    if (env->ExceptionCheck() || !xLampDetails) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return 0;
    }

    return (jboolean)xLampDetails->color;
}

JNIEXPORT
jboolean JNICALL Java_org_allseen_lsf_sdk_LampDetails_hasVariableColorTemp(JNIEnv *env, jobject thiz)
{
    JLampDetails* xLampDetails = GetHandle<JLampDetails*>(thiz);
    if (env->ExceptionCheck() || !xLampDetails) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return 0;
    }

    return (jboolean)xLampDetails->variableColorTemp;
}

JNIEXPORT
jboolean JNICALL Java_org_allseen_lsf_sdk_LampDetails_hasEffects(JNIEnv *env, jobject thiz)
{
    JLampDetails* xLampDetails = GetHandle<JLampDetails*>(thiz);
    if (env->ExceptionCheck() || !xLampDetails) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return 0;
    }

    return (jboolean)xLampDetails->hasEffects;
}

JNIEXPORT
jint JNICALL Java_org_allseen_lsf_sdk_LampDetails_getMinVoltage(JNIEnv *env, jobject thiz)
{
    JLampDetails* xLampDetails = GetHandle<JLampDetails*>(thiz);
    if (env->ExceptionCheck() || !xLampDetails) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return 0;
    }

    return (jint)xLampDetails->minVoltage;
}

JNIEXPORT
jint JNICALL Java_org_allseen_lsf_sdk_LampDetails_getMaxVoltage(JNIEnv *env, jobject thiz)
{
    JLampDetails* xLampDetails = GetHandle<JLampDetails*>(thiz);
    if (env->ExceptionCheck() || !xLampDetails) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return 0;
    }

    return (jint)xLampDetails->maxVoltage;
}

JNIEXPORT
jint JNICALL Java_org_allseen_lsf_sdk_LampDetails_getWattage(JNIEnv *env, jobject thiz)
{
    JLampDetails* xLampDetails = GetHandle<JLampDetails*>(thiz);
    if (env->ExceptionCheck() || !xLampDetails) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return 0;
    }

    return (jint)xLampDetails->wattage;
}

JNIEXPORT
jint JNICALL Java_org_allseen_lsf_sdk_LampDetails_getIncandescentEquivalent(JNIEnv *env, jobject thiz)
{
    JLampDetails* xLampDetails = GetHandle<JLampDetails*>(thiz);
    if (env->ExceptionCheck() || !xLampDetails) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return 0;
    }

    return (jint)xLampDetails->incandescentEquivalent;
}

JNIEXPORT
jint JNICALL Java_org_allseen_lsf_sdk_LampDetails_getMaxLumens(JNIEnv *env, jobject thiz)
{
    JLampDetails* xLampDetails = GetHandle<JLampDetails*>(thiz);
    if (env->ExceptionCheck() || !xLampDetails) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return 0;
    }

    return (jint)xLampDetails->maxLumens;
}

JNIEXPORT
jint JNICALL Java_org_allseen_lsf_sdk_LampDetails_getMinTemperature(JNIEnv *env, jobject thiz)
{
    JLampDetails* xLampDetails = GetHandle<JLampDetails*>(thiz);
    if (env->ExceptionCheck() || !xLampDetails) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return 0;
    }

    return (jint)xLampDetails->minTemperature;
}

JNIEXPORT
jint JNICALL Java_org_allseen_lsf_sdk_LampDetails_getMaxTemperature(JNIEnv *env, jobject thiz)
{
    JLampDetails* xLampDetails = GetHandle<JLampDetails*>(thiz);
    if (env->ExceptionCheck() || !xLampDetails) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return 0;
    }

    return (jint)xLampDetails->maxTemperature;
}

JNIEXPORT
jint JNICALL Java_org_allseen_lsf_sdk_LampDetails_getColorRenderingIndex(JNIEnv *env, jobject thiz)
{
    JLampDetails* xLampDetails = GetHandle<JLampDetails*>(thiz);
    if (env->ExceptionCheck() || !xLampDetails) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return 0;
    }

    return (jint)xLampDetails->colorRenderingIndex;
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_sdk_LampDetails_getLampID(JNIEnv *env, jobject thiz)
{
    JLampDetails* xLampDetails = GetHandle<JLampDetails*>(thiz);
    if (env->ExceptionCheck() || !xLampDetails) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jstring jLampID = env->NewStringUTF(xLampDetails->lampID.c_str());
    if (env->ExceptionCheck() || !jLampID) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jLampID;
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_sdk_LampDetails_createNativeObject(JNIEnv*env, jobject thiz)
{
    CreateHandle<JLampDetails>(thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_sdk_LampDetails_destroyNativeObject(JNIEnv*env, jobject thiz)
{
    DestroyHandle<JLampDetails>(thiz);
}
