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

#include "JLampParameters.h"

#include "NUtil.h"

#include "org_allseen_lsf_LampParameters.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace lsf;

JNIEXPORT
jint JNICALL Java_org_allseen_lsf_LampParameters_getEnergyUsageMilliwatts(JNIEnv *env, jobject thiz)
{
    JLampParameters* xLampParams = GetHandle<JLampParameters*>(thiz);
    if (env->ExceptionCheck() || !xLampParams) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return 0;
    }

    return (jint)xLampParams->energyUsageMilliwatts;
}

JNIEXPORT
jint JNICALL Java_org_allseen_lsf_LampParameters_getLumens(JNIEnv *env, jobject thiz)
{
    JLampParameters* xLampParams = GetHandle<JLampParameters*>(thiz);
    if (env->ExceptionCheck() || !xLampParams) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return 0;
    }

    return (jint)xLampParams->lumens;
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_LampParameters_createNativeObject(JNIEnv *env, jobject thiz)
{
    CreateHandle<JLampParameters>(thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_LampParameters_destroyNativeObject(JNIEnv *env, jobject thiz)
{
    DestroyHandle<JLampParameters>(thiz);
}
