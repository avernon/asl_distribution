/******************************************************************************
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

#include <jni.h>

#include <qcc/Debug.h>

#include <alljoyn/AboutData.h>

#include "NDefs.h"
#include "NUtil.h"

#include "org_allseen_lsf_sdk_AboutData.h"

#define QCC_MODULE LSF_QCC_MODULE

using namespace ajn;

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_sdk_AboutData_getString(JNIEnv *env, jobject thiz, jlong jNativeAboutDataHandle, jstring jKey, jstring jLanguage)
{
    JString xKey(jKey);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    JString xLanguage(jLanguage);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    MsgArg *cVariant = NULL;
    QStatus status = ((AboutData *)jNativeAboutDataHandle)->GetField(xKey.c_str(), cVariant, xLanguage.c_str());
    if (status != ER_OK || cVariant == NULL) {
        QCC_LogError(status, ("GetField() failed"));
        return NULL;
    }

    char *cValue = NULL;
    status = cVariant->Get("s", &cValue);
    if (status != ER_OK || cValue == NULL) {
        QCC_LogError(status, ("GetField() failed"));
        return NULL;
    }

    jstring jValue = env->NewStringUTF(cValue);
    if (env->ExceptionCheck() || !jValue) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jValue;
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_sdk_AboutData_put(JNIEnv *env, jobject thiz, jlong jNativeAboutDataHandle, jstring jKey, jobject jVariant, jstring jLanguage)
{
    JString xKey(jKey);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return;
    }

    jmethodID jMarshal = env->GetStaticMethodID(XClass::xMsgArg->classRef, "marshal", "(JLjava/lang/String;Ljava/lang/Object;)V");
    if (env->ExceptionCheck() || !jMarshal) {
        QCC_LogError(ER_FAIL, ("GetStaticMethodID() failed"));
        return;
    }

    jstring jSignature = env->NewStringUTF("v");
    if (env->ExceptionCheck() || !jSignature) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return;
    }

    MsgArg cVariant;
    env->CallStaticVoidMethod(XClass::xMsgArg->classRef, jMarshal, (jlong)&cVariant, jSignature, jVariant);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("CallStaticVoidMethod() failed"));
        return;
    }

//    QCC_LogError(ER_FAIL, ("cVariant sig: %s", cVariant.Signature().c_str()));

    MsgArg* cValue = NULL;
    cVariant.Get("v", &cValue);
    if (cValue == NULL) {
        QCC_LogError(ER_FAIL, ("Get variant failed"));
        return;
    }

//    QCC_LogError(ER_FAIL, ("cValue sig: %s", cValue->Signature().c_str()));

    JString xLanguage(jLanguage);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return;
    }

//    QCC_LogError(ER_FAIL, ("Calling SetField: %s, %s, %s", xKey.c_str(), cValue->ToString().c_str(), xLanguage.c_str()));
    ((AboutData *)jNativeAboutDataHandle)->SetField(xKey.c_str(), *cValue, xLanguage.c_str());
}

#ifdef __cplusplus
}
#endif


