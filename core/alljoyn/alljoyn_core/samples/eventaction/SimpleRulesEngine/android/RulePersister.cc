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

#include "RulePersister.h"

void RulePersister::saveRule(Rule* rule)
{
    JNIEnv* env;
    jint jret = vm->GetEnv((void**)&env, JNI_VERSION_1_2);
    if (JNI_EDETACHED == jret) {
        vm->AttachCurrentThread(&env, NULL);
    }

    jclass jcls = env->GetObjectClass(jobj);
    jmethodID mid = env->GetMethodID(jcls, "saveRule", "(Ljava/lang/String;)V");
    if (mid == 0) {
        LOGTHIS("Failed to get Java saveRule");
    } else {
        jstring jRule = env->NewStringUTF(rule->toString().c_str());
        env->CallVoidMethod(jobj, mid, jRule);
        env->DeleteLocalRef(jRule);
    }
    if (JNI_EDETACHED == jret) {
        vm->DetachCurrentThread();
    }
}

void RulePersister::loadRules()
{
    JNIEnv* env;
    jint jret = vm->GetEnv((void**)&env, JNI_VERSION_1_2);
    if (JNI_EDETACHED == jret) {
        vm->AttachCurrentThread(&env, NULL);
    }

    jclass jcls = env->GetObjectClass(jobj);
    jmethodID mid = env->GetMethodID(jcls, "loadRules", "()V");
    if (mid == 0) {
        LOGTHIS("Failed to get Java loadRules");
    } else {
        env->CallVoidMethod(jobj, mid);
    }
    if (JNI_EDETACHED == jret) {
        vm->DetachCurrentThread();
    }
}

void RulePersister::clearRules()
{
    JNIEnv* env;
    jint jret = vm->GetEnv((void**)&env, JNI_VERSION_1_2);
    if (JNI_EDETACHED == jret) {
        vm->AttachCurrentThread(&env, NULL);
    }

    jclass jcls = env->GetObjectClass(jobj);
    jmethodID mid = env->GetMethodID(jcls, "clearRules", "()V");
    if (mid == 0) {
        LOGTHIS("Failed to get Java clearRules");
    } else {
        env->CallVoidMethod(jobj, mid);
    }
    if (JNI_EDETACHED == jret) {
        vm->DetachCurrentThread();
    }
}
