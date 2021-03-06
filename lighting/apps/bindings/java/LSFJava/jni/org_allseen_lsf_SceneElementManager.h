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
 *
 ******************************************************************************/
/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_allseen_lsf_SceneElementManager */

#ifndef _Included_org_allseen_lsf_SceneElementManager
#define _Included_org_allseen_lsf_SceneElementManager
#ifdef __cplusplus
extern "C" {
#endif
#undef org_allseen_lsf_SceneElementManager_MAX_SCENE_ELEMENTS
#define org_allseen_lsf_SceneElementManager_MAX_SCENE_ELEMENTS 100L
/*
 * Class:     org_allseen_lsf_SceneElementManager
 * Method:    getAllSceneElementIDs
 * Signature: ()Lorg/allseen/lsf/sdk/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_SceneElementManager_getAllSceneElementIDs
  (JNIEnv *, jobject);

/*
 * Class:     org_allseen_lsf_SceneElementManager
 * Method:    getSceneElementName
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Lorg/allseen/lsf/sdk/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_SceneElementManager_getSceneElementName
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     org_allseen_lsf_SceneElementManager
 * Method:    setSceneElementName
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Lorg/allseen/lsf/sdk/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_SceneElementManager_setSceneElementName
  (JNIEnv *, jobject, jstring, jstring, jstring);

/*
 * Class:     org_allseen_lsf_SceneElementManager
 * Method:    createSceneElement
 * Signature: (Lorg/allseen/lsf/sdk/TrackingID;Lorg/allseen/lsf/SceneElement;Ljava/lang/String;Ljava/lang/String;)Lorg/allseen/lsf/sdk/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_SceneElementManager_createSceneElement
  (JNIEnv *, jobject, jobject, jobject, jstring, jstring);

/*
 * Class:     org_allseen_lsf_SceneElementManager
 * Method:    updateSceneElement
 * Signature: (Ljava/lang/String;Lorg/allseen/lsf/SceneElement;)Lorg/allseen/lsf/sdk/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_SceneElementManager_updateSceneElement
  (JNIEnv *, jobject, jstring, jobject);

/*
 * Class:     org_allseen_lsf_SceneElementManager
 * Method:    deleteSceneElement
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/sdk/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_SceneElementManager_deleteSceneElement
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_SceneElementManager
 * Method:    getSceneElement
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/sdk/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_SceneElementManager_getSceneElement
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_SceneElementManager
 * Method:    applySceneElement
 * Signature: (Ljava/lang/String;)Lorg/allseen/lsf/sdk/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_SceneElementManager_applySceneElement
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_allseen_lsf_SceneElementManager
 * Method:    getSceneElementDataSet
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Lorg/allseen/lsf/sdk/ControllerClientStatus;
 */
JNIEXPORT jobject JNICALL Java_org_allseen_lsf_SceneElementManager_getSceneElementDataSet
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     org_allseen_lsf_SceneElementManager
 * Method:    createNativeObject
 * Signature: (Lorg/allseen/lsf/ControllerClient;Lorg/allseen/lsf/SceneElementManagerCallback;)V
 */
JNIEXPORT void JNICALL Java_org_allseen_lsf_SceneElementManager_createNativeObject
  (JNIEnv *, jobject, jobject, jobject);

/*
 * Class:     org_allseen_lsf_SceneElementManager
 * Method:    destroyNativeObject
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_allseen_lsf_SceneElementManager_destroyNativeObject
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
