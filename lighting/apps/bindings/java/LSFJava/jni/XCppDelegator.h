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

#ifndef LSF_JNI_XCPPDELEGATOR_H_
#define LSF_JNI_XCPPDELEGATOR_H_

#include <jni.h>

#include <ControllerClientDefs.h>

#include "JEnum.h"
#include "NDefs.h"
#include "NUtil.h"

namespace lsf {

class XCppDelegator {
private:
    XCppDelegator();

public:
    // Calls that return ControllerClientStatus
    template <typename T> static jobject Call_ControllerClientStatus(JNIEnv *env, jobject thiz, ControllerClientStatus (T::*cMethod)(void));
    template <typename T> static jobject Call_ControllerClientStatus_String(JNIEnv *env, jobject thiz, jstring jString, ControllerClientStatus (T::*cMethod)(const std::string&));
    template <typename T> static jobject Call_ControllerClientStatus_String_String(JNIEnv *env, jobject thiz, jstring jString1, jstring jString2, ControllerClientStatus (T::*cMethod)(const std::string&, const std::string&));
    template <typename T> static jobject Call_ControllerClientStatus_String_String_String(JNIEnv *env, jobject thiz, jstring jString1, jstring jString2, jstring jString3, ControllerClientStatus (T::*cMethod)(const std::string&, const std::string&, const std::string&));
    template <typename T> static jobject Call_ControllerClientStatus_String_StringList(JNIEnv *env, jobject thiz, jstring jString, jobjectArray jStringList, ControllerClientStatus (T::*cMethod)(const std::string&, const std::list<std::string>&));

    template <typename T> static jobject Call_ControllerClientStatus_String_Boolean(JNIEnv *env, jobject thiz, jstring jString, jboolean jBoolean, ControllerClientStatus (T::*cMethod)(const std::string&, const bool&));
    template <typename T> static jobject Call_ControllerClientStatus_String_UInt32(JNIEnv *env, jobject thiz, jstring jString, jlong jLong, ControllerClientStatus (T::*cMethod)(const std::string&, const uint32_t&));
    template <typename T> static jobject Call_ControllerClientStatus_String_UInt32_UInt32(JNIEnv *env, jobject thiz, jstring jString, jlong jLong1, jlong jLong2, ControllerClientStatus (T::*cMethod)(const std::string&, const uint32_t&, const uint32_t&));
    template <typename T> static jobject Call_ControllerClientStatus_String_String_UInt32(JNIEnv *env, jobject thiz, jstring jString1, jstring jString2, jlong jLong, ControllerClientStatus (T::*cMethod)(const std::string&, const std::string&, const uint32_t&));
    template <typename T> static jobject Call_ControllerClientStatus_String_String_UInt32_UInt32_UInt32_String(JNIEnv *env, jobject thiz, jstring jString1, jstring jString2, jlong jLong1, jlong jLong2, jlong jLong3, jstring jString3, ControllerClientStatus (T::*cMethod)(const std::string&, const std::string&, const uint32_t&, const uint32_t&, const uint32_t&, const std::string&));

    template <typename T1, typename T2, typename T3> static jobject Call_ControllerClientStatus_String_Object(JNIEnv *env, jobject thiz, jstring jString, jobject jObject, ControllerClientStatus (T1::*cMethod)(const std::string&, const T3&));
    template <typename T1, typename T2, typename T3> static jobject Call_ControllerClientStatus_String_Object_UInt32(JNIEnv *env, jobject thiz, jstring jString, jobject jObject, jlong jLong, ControllerClientStatus (T1::*cMethod)(const std::string&, const T3&, const uint32_t&));
    template <typename T1, typename T2, typename T3> static jobject Call_ControllerClientStatus_String_Object_UInt32_UInt32_UInt32_Object(JNIEnv *env, jobject thiz, jstring jString, jobject jObject1, jlong jLong1, jlong jLong2, jlong jLong3, jobject jObject2, ControllerClientStatus (T1::*cMethod)(const std::string&, const T3&, const uint32_t&, const uint32_t&, const uint32_t&, const T3&));

    template <typename T1, typename T2, typename T3> static jobject Call_ControllerClientStatus_Object(JNIEnv *env, jobject thiz, jobject jObject, ControllerClientStatus (T1::*cMethod)(const T3&));
    template <typename T1, typename T2, typename T3> static jobject Call_ControllerClientStatus_Object_String_String(JNIEnv *env, jobject thiz, jobject jObject, jstring jString1, jstring jString2, ControllerClientStatus (T1::*cMethod)(const T3&, const std::string&, const std::string&));

    template <typename T1, typename T2, typename T3> static jobject Call_ControllerClientStatus_TrackingID_Object_String_String(JNIEnv *env, jobject thiz, jobject jTrackingID, jobject jObject, jstring jString1, jstring jString2, ControllerClientStatus (T1::*cMethod)(uint32_t&, const T3&, const std::string&, const std::string&));

    // Calls that return void
    template <typename T> static void Call_Void(JNIEnv *env, jobject thiz, void (T::*cMethod)(void));
    template <typename T> static void Call_Void_String(JNIEnv *env, jobject thiz, jstring jString, void (T::*cMethod)(const std::string&));
};

} /* namespace lsf */

// The .cpp file is #include'd in this .h file because some templated
// methods must be defined here. The following #define prevents the
// non-templated code from being visible here.
#define LSF_JNI_XCPPDELEGATOR_H_INCLUDE_TEMPLATE_METHODS
#include "XCppDelegator.cpp"
#undef LSF_JNI_XCPPDELEGATOR_H_INCLUDE_TEMPLATE_METHODS

#endif /* LSF_JNI_XCPPDELEGATOR_H_ */
