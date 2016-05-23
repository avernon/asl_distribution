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

#include <alljoyn/MsgArg.h>

#include "JEnum.h"
#include "JLampGroup.h"
#include "XLampMemberList.h"
#include "XObject.h"

#include "org_allseen_lsf_LampGroup.h"

#define QCC_MODULE "AJN-LSF-JNI"

using namespace lsf;

JNIEXPORT
void JNICALL Java_org_allseen_lsf_LampGroup_setLamps(JNIEnv *env, jobject thiz, jobjectArray jLampIDs)
{
    XLampMemberList::SetLamps<JLampGroup>(env, thiz, jLampIDs);
}

JNIEXPORT
jobjectArray JNICALL Java_org_allseen_lsf_LampGroup_getLamps(JNIEnv *env, jobject thiz)
{
    return XLampMemberList::GetLamps<JLampGroup>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_LampGroup_setLampGroups(JNIEnv *env, jobject thiz, jobjectArray jLampGroupIDs)
{
    XLampMemberList::SetLampGroups<JLampGroup>(env, thiz, jLampGroupIDs);
}

JNIEXPORT
jobjectArray JNICALL Java_org_allseen_lsf_LampGroup_getLampGroups(JNIEnv *env, jobject thiz)
{
    return XLampMemberList::GetLampGroups<JLampGroup>(env, thiz);
}

JNIEXPORT
jobject JNICALL Java_org_allseen_lsf_LampGroup_isDependentLampGroup(JNIEnv *env, jobject thiz, jstring jLampGroupID)
{
    JLampGroup* xLampGroup = GetHandle<JLampGroup*>(thiz);
    if (env->ExceptionCheck() || !xLampGroup) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    JString xLampGroupID(jLampGroupID);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xLampGroupID.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    LSFString cLampGroupID = xLampGroupID.c_str();

    jobject jResponseCode = JEnum::jResponseCodeEnum->getObject((int)(xLampGroup->IsDependentLampGroup(cLampGroupID)));
    if (env->ExceptionCheck() || !jResponseCode) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    return jResponseCode;
}

JNIEXPORT
jstring JNICALL Java_org_allseen_lsf_LampGroup_toString(JNIEnv *env, jobject thiz)
{
    return XObject::ToString<JLampGroup>(env, thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_LampGroup_createNativeObject(JNIEnv *env, jobject thiz)
{
    CreateHandle<JLampGroup>(thiz);
}

JNIEXPORT
void JNICALL Java_org_allseen_lsf_LampGroup_destroyNativeObject(JNIEnv *env, jobject thiz)
{
    DestroyHandle<JLampGroup>(thiz);
}
