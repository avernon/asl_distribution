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

// This .cpp file is #include'd in the .h file because some templated
// methods must be defined there. The following #ifdef allows the
// templated code to be visible there.
#ifdef LSF_JNI_XCPPDELEGATOR_H_INCLUDE_TEMPLATE_METHODS

#include <qcc/Debug.h>

#define QCC_MODULE LSF_QCC_MODULE

namespace lsf {

template <typename T>
jobject XCppDelegator::Call_ControllerClientStatus(JNIEnv *env, jobject thiz, ControllerClientStatus (T::*cMethod)(void))
{
    T *xDelegate = GetHandle<T*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    return JEnum::jControllerClientStatusEnum->getObject((int)((xDelegate->*cMethod)()));
}

template <typename T>
jobject XCppDelegator::Call_ControllerClientStatus_String(JNIEnv *env, jobject thiz, jstring jString, ControllerClientStatus (T::*cMethod)(const std::string&))
{
    T *xDelegate = GetHandle<T*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    JString xString(jString);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xString.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    std::string cString = xString.c_str();

    return JEnum::jControllerClientStatusEnum->getObject((int)((xDelegate->*cMethod)(cString)));
}

template <typename T>
jobject XCppDelegator::Call_ControllerClientStatus_String_String(JNIEnv *env, jobject thiz, jstring jString1, jstring jString2, ControllerClientStatus (T::*cMethod)(const std::string&, const std::string&))
{
    T *xDelegate = GetHandle<T*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    JString xString1(jString1);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xString1.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    JString xString2(jString2);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xString2.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    std::string cString1 = xString1.c_str();
    std::string cString2 = xString2.c_str();

    return JEnum::jControllerClientStatusEnum->getObject((int)((xDelegate->*cMethod)(cString1, cString2)));
}

template <typename T>
jobject XCppDelegator::Call_ControllerClientStatus_String_String_String(JNIEnv *env, jobject thiz, jstring jString1, jstring jString2, jstring jString3, ControllerClientStatus (T::*cMethod)(const std::string&, const std::string&, const std::string&))
{
    T *xDelegate = GetHandle<T*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    JString xString1(jString1);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xString1.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    JString xString2(jString2);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xString2.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    JString xString3(jString3);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xString3.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    std::string cString1 = xString1.c_str();
    std::string cString2 = xString2.c_str();
    std::string cString3 = xString3.c_str();

    return JEnum::jControllerClientStatusEnum->getObject((int)((xDelegate->*cMethod)(cString1, cString2, cString3)));
}

template <typename T>
jobject XCppDelegator::Call_ControllerClientStatus_String_Boolean(JNIEnv *env, jobject thiz, jstring jString, jboolean jBoolean, ControllerClientStatus (T::*cMethod)(const std::string&, const bool&))
{
    T *xDelegate = GetHandle<T*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    JString xString(jString);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xString.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    std::string cString = xString.c_str();

    return JEnum::jControllerClientStatusEnum->getObject((int)((xDelegate->*cMethod)(cString, (bool)jBoolean)));
}

template <typename T>
jobject XCppDelegator::Call_ControllerClientStatus_String_UInt32(JNIEnv *env, jobject thiz, jstring jString, jlong jLong, ControllerClientStatus (T::*cMethod)(const std::string&, const uint32_t&))
{
    T *xDelegate = GetHandle<T*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    JString xString(jString);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xString.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    std::string cString = xString.c_str();

    return JEnum::jControllerClientStatusEnum->getObject((int)((xDelegate->*cMethod)(cString, (uint32_t)jLong)));
}

template <typename T>
jobject XCppDelegator::Call_ControllerClientStatus_String_UInt32_UInt32(JNIEnv *env, jobject thiz, jstring jString, jlong jLong1, jlong jLong2, ControllerClientStatus (T::*cMethod)(const std::string&, const uint32_t&, const uint32_t&))
{
    T *xDelegate = GetHandle<T*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    JString xString(jString);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xString.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    std::string cString = xString.c_str();

    return JEnum::jControllerClientStatusEnum->getObject((int)((xDelegate->*cMethod)(cString, (uint32_t)jLong1, (uint32_t)jLong2)));
}

template <typename T>
jobject XCppDelegator::Call_ControllerClientStatus_String_String_UInt32(JNIEnv *env, jobject thiz, jstring jString1, jstring jString2, jlong jLong, ControllerClientStatus (T::*cMethod)(const std::string&, const std::string&, const uint32_t&))
{
    T *xDelegate = GetHandle<T*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    JString xString1(jString1);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xString1.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    JString xString2(jString2);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xString2.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    std::string cString1 = xString1.c_str();
    std::string cString2 = xString2.c_str();

    return JEnum::jControllerClientStatusEnum->getObject((int)((xDelegate->*cMethod)(cString1, cString2, (uint32_t)jLong)));
}

template <typename T>
jobject XCppDelegator::Call_ControllerClientStatus_String_String_UInt32_UInt32_UInt32_String(JNIEnv *env, jobject thiz, jstring jString1, jstring jString2, jlong jLong1, jlong jLong2, jlong jLong3, jstring jString3, ControllerClientStatus (T::*cMethod)(const std::string&, const std::string&, const uint32_t&, const uint32_t&, const uint32_t&, const std::string&))
{
    T *xDelegate = GetHandle<T*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    JString xString1(jString1);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xString1.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    JString xString2(jString2);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xString2.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    JString xString3(jString3);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xString3.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    std::string cString1 = xString1.c_str();
    std::string cString2 = xString2.c_str();
    std::string cString3 = xString3.c_str();

    return JEnum::jControllerClientStatusEnum->getObject((int)((xDelegate->*cMethod)(cString1, cString2, (uint32_t)jLong1, (uint32_t)jLong2, (uint32_t)jLong3, cString3)));
}

template <typename T1, typename T2, typename T3>
jobject XCppDelegator::Call_ControllerClientStatus_String_Object(JNIEnv *env, jobject thiz, jstring jString, jobject jObject, ControllerClientStatus (T1::*cMethod)(const std::string&, const T3&))
{
    T1 *xDelegate = GetHandle<T1*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    JString xString(jString);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xString.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    T2 *xObject = GetHandle<T2*>(jObject);
    if (env->ExceptionCheck() || !xObject) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    T3 cObject = (T3&)(*xObject);
    std::string cString = xString.c_str();

    return JEnum::jControllerClientStatusEnum->getObject((int)((xDelegate->*cMethod)(cString, cObject)));
}

template <typename T1, typename T2, typename T3>
jobject XCppDelegator::Call_ControllerClientStatus_String_Object_UInt32(JNIEnv *env, jobject thiz, jstring jString, jobject jObject, jlong jLong, ControllerClientStatus (T1::*cMethod)(const std::string&, const T3&, const uint32_t&))
{
    T1 *xDelegate = GetHandle<T1*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    JString xString(jString);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xString.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    T2 *xObject = GetHandle<T2*>(jObject);
    if (env->ExceptionCheck() || !xObject) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    T3 cObject = (T3&)(*xObject);
    std::string cString = xString.c_str();

    return JEnum::jControllerClientStatusEnum->getObject((int)((xDelegate->*cMethod)(cString, cObject, (uint32_t)jLong)));
}

template <typename T1, typename T2, typename T3>
jobject XCppDelegator::Call_ControllerClientStatus_String_Object_UInt32_UInt32_UInt32_Object(JNIEnv *env, jobject thiz, jstring jString, jobject jObject1, jlong jLong1, jlong jLong2, jlong jLong3, jobject jObject2, ControllerClientStatus (T1::*cMethod)(const std::string&, const T3&, const uint32_t&, const uint32_t&, const uint32_t&, const T3&))
{
    T1 *xDelegate = GetHandle<T1*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    JString xString(jString);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xString.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    T2 *xObject1 = GetHandle<T2*>(jObject1);
    if (env->ExceptionCheck() || !xObject1) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    T2 *xObject2 = GetHandle<T2*>(jObject2);
    if (env->ExceptionCheck() || !xObject2) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    std::string cString = xString.c_str();
    T3 cObject1 = (T3&)(*xObject1);
    T3 cObject2 = (T3&)(*xObject2);

    return JEnum::jControllerClientStatusEnum->getObject((int)((xDelegate->*cMethod)(cString, cObject1, (uint32_t)jLong1, (uint32_t)jLong2, (uint32_t)jLong3, cObject2)));
}

template <typename T1, typename T2, typename T3>
jobject XCppDelegator::Call_ControllerClientStatus_Object(JNIEnv *env, jobject thiz, jobject jObject, ControllerClientStatus (T1::*cMethod)(const T3&))
{
    T1 *xDelegate = GetHandle<T1*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    T2 *xObject = GetHandle<T2*>(jObject);
    if (env->ExceptionCheck() || !xObject) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    T3 cObject = (T3&)(*xObject);

    return JEnum::jControllerClientStatusEnum->getObject((int)((xDelegate->*cMethod)(cObject)));
}

template <typename T1, typename T2, typename T3>
jobject XCppDelegator::Call_ControllerClientStatus_Object_String_String(JNIEnv *env, jobject thiz, jobject jObject, jstring jString1, jstring jString2, ControllerClientStatus (T1::*cMethod)(const T3&, const std::string&, const std::string&))
{
    T1 *xDelegate = GetHandle<T1*>(thiz);
    if (env->ExceptionCheck() || !xDelegate) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    T2 *xObject = GetHandle<T2*>(jObject);
    if (env->ExceptionCheck() || !xObject) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    JString xString1(jString1);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xString1.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    JString xString2(jString2);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("JString failed"));
        return NULL;
    }

    if (!xString2.c_str()) {
        QCC_LogError(ER_FAIL, ("JString invalid"));
        return NULL;
    }

    T3 cObject = (T3&)(*xObject);
    std::string cString1 = xString1.c_str();
    std::string cString2 = xString2.c_str();

    return JEnum::jControllerClientStatusEnum->getObject((int)((xDelegate->*cMethod)(cObject, cString1, cString2)));
}

} // namespace lsf

#undef QCC_MODULE

#endif /* LSF_JNI_XCPPDELEGATOR_H_INCLUDE_TEMPLATE_METHODS */

