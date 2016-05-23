/*
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
 */
/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_allseen_lsf_LampState */

#ifndef _Included_org_allseen_lsf_LampState
#define _Included_org_allseen_lsf_LampState
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_allseen_lsf_LampState
 * Method:    setOnOff
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_allseen_lsf_LampState_setOnOff
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     org_allseen_lsf_LampState
 * Method:    getOnOff
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_allseen_lsf_LampState_getOnOff
  (JNIEnv *, jobject);

/*
 * Class:     org_allseen_lsf_LampState
 * Method:    setHue
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_allseen_lsf_LampState_setHue
  (JNIEnv *, jobject, jlong);

/*
 * Class:     org_allseen_lsf_LampState
 * Method:    getHue
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_allseen_lsf_LampState_getHue
  (JNIEnv *, jobject);

/*
 * Class:     org_allseen_lsf_LampState
 * Method:    setSaturation
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_allseen_lsf_LampState_setSaturation
  (JNIEnv *, jobject, jlong);

/*
 * Class:     org_allseen_lsf_LampState
 * Method:    getSaturation
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_allseen_lsf_LampState_getSaturation
  (JNIEnv *, jobject);

/*
 * Class:     org_allseen_lsf_LampState
 * Method:    setColorTemp
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_allseen_lsf_LampState_setColorTemp
  (JNIEnv *, jobject, jlong);

/*
 * Class:     org_allseen_lsf_LampState
 * Method:    getColorTemp
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_allseen_lsf_LampState_getColorTemp
  (JNIEnv *, jobject);

/*
 * Class:     org_allseen_lsf_LampState
 * Method:    setBrightness
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_allseen_lsf_LampState_setBrightness
  (JNIEnv *, jobject, jlong);

/*
 * Class:     org_allseen_lsf_LampState
 * Method:    getBrightness
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_allseen_lsf_LampState_getBrightness
  (JNIEnv *, jobject);

/*
 * Class:     org_allseen_lsf_LampState
 * Method:    setNull
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_allseen_lsf_LampState_setNull
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     org_allseen_lsf_LampState
 * Method:    isNull
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_allseen_lsf_LampState_isNull
  (JNIEnv *, jobject);

/*
 * Class:     org_allseen_lsf_LampState
 * Method:    createNativeObject
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_allseen_lsf_LampState_createNativeObject
  (JNIEnv *, jobject);

/*
 * Class:     org_allseen_lsf_LampState
 * Method:    destroyNativeObject
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_allseen_lsf_LampState_destroyNativeObject
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif