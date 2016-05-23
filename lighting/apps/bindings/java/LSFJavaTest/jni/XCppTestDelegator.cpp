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


#ifdef LSF_JNI_XCPPTESTDELEGATOR_H_INCLUDE_TEMPLATE_METHODS

#include <qcc/Debug.h>

#include "XLongArray.h"

#define QCC_MODULE LSF_QCC_MODULE

namespace lsf {

template <typename T>
jstring XCppTestDelegator::Call_Void(JNIEnv *env, jobject jCallback, void (T::*cMethod)(), char const *cFunc)
{
    T* xCallback = GetHandle<T*>(jCallback);
    if (env->ExceptionCheck() || !xCallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    (xCallback->*cMethod)();
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("Call failed"));
        return NULL;
    }

    jstring jFunc = env->NewStringUTF(GetJavaNativeMethodNameFromFunc(cFunc).c_str());
    if (env->ExceptionCheck() || !jFunc) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jFunc;
}

template <typename T>
jstring XCppTestDelegator::Call_Void_String_String(JNIEnv *env, jobject jCallback, jstring jString1, jstring jString2, void (T::*cMethod)(const std::string&, const std::string&), char const *cFunc)
{
    T* xCallback = GetHandle<T*>(jCallback);
    if (env->ExceptionCheck() || !xCallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    JString xString1(jString1);
    if (env->ExceptionCheck() || !xString1.c_str()) {
        QCC_LogError(ER_FAIL, ("JString() failed"));
        return NULL;
    }

    JString xString2(jString2);
    if (env->ExceptionCheck() || !xString2.c_str()) {
        QCC_LogError(ER_FAIL, ("JString() failed"));
        return NULL;
    }

    (xCallback->*cMethod)(xString1.c_str(), xString2.c_str());
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("Call failed"));
        return NULL;
    }

    jstring jFunc = env->NewStringUTF(GetJavaNativeMethodNameFromFunc(cFunc).c_str());
    if (env->ExceptionCheck() || !jFunc) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jFunc;
}

template <typename T>
jstring XCppTestDelegator::Call_Void_StringList(JNIEnv *env, jobject jCallback, jobjectArray jStringList, void (T::*cMethod)(const std::list<std::string>&), char const *cFunc)
{
    T* xCallback = GetHandle<T*>(jCallback);
    if (env->ExceptionCheck() || !xCallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    std::list<std::string> cStringList;
    JStringArray::CopyStringArray(jStringList, cStringList);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("CopyStringArray() failed"));
        return NULL;
    }

    (xCallback->*cMethod)(cStringList);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("Call failed"));
        return NULL;
    }

    jstring jFunc = env->NewStringUTF(GetJavaNativeMethodNameFromFunc(cFunc).c_str());
    if (env->ExceptionCheck() || !jFunc) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jFunc;
}

template <typename T1, typename T2, typename T3>
jstring XCppTestDelegator::Call_Void_String_Object(JNIEnv *env, jobject jCallback, jstring jString, jobject jObject, void (T1::*cMethod)(const std::string&, const T3&), char const *cFunc)
{
    T1* xCallback = GetHandle<T1*>(jCallback);
    if (env->ExceptionCheck() || !xCallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    JString xString(jString);
    if (env->ExceptionCheck() || !xString.c_str()) {
        QCC_LogError(ER_FAIL, ("JString() failed"));
        return NULL;
    }

    T2* xObject = GetHandle<T2*>(jObject);
    if (env->ExceptionCheck() || !xObject) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    T3 cObject = (T3&)(*xObject);
    std::string cString = xString.c_str();

    (xCallback->*cMethod)(cString, cObject);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("Call failed"));
        return NULL;
    }

    jstring jFunc = env->NewStringUTF(GetJavaNativeMethodNameFromFunc(cFunc).c_str());
    if (env->ExceptionCheck() || !jFunc) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jFunc;
}

template <typename T>
jstring XCppTestDelegator::Call_Void_ResponseCode(JNIEnv *env, jobject jCallback, jobject jResponseCode, void (T::*cMethod)(const LSFResponseCode &), char const *cFunc)
{
    T* xCallback = GetHandle<T*>(jCallback);
    if (env->ExceptionCheck() || !xCallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jint xResponseCode = JEnum::jResponseCodeEnum->getValue(jResponseCode);
    LSFResponseCode cResponseCode = (LSFResponseCode)xResponseCode;
    if (env->ExceptionCheck() || (xResponseCode == (jint)-1)) {
        QCC_LogError(ER_FAIL, ("getValue() failed"));
        return NULL;
    }

    (xCallback->*cMethod)(cResponseCode);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("Call failed"));
        return NULL;
    }

    jstring jFunc = env->NewStringUTF(GetJavaNativeMethodNameFromFunc(cFunc).c_str());
    if (env->ExceptionCheck() || !jFunc) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jFunc;
}

template <typename T>
jstring XCppTestDelegator::Call_Void_ResponseCode_StringList(JNIEnv *env, jobject jCallback, jobject jResponseCode, jobjectArray jStringList, void (T::*cMethod)(const LSFResponseCode &, const std::list<std::string>&), char const *cFunc)
{
    T* xCallback = GetHandle<T*>(jCallback);
    if (env->ExceptionCheck() || !xCallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jint xResponseCode = JEnum::jResponseCodeEnum->getValue(jResponseCode);
    LSFResponseCode cResponseCode = (LSFResponseCode)xResponseCode;
    if (env->ExceptionCheck() || (xResponseCode == (jint)-1)) {
        QCC_LogError(ER_FAIL, ("getValue() failed"));
        return NULL;
    }

    std::list<std::string> cStringList;
    JStringArray::CopyStringArray(jStringList, cStringList);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("CopyStringArray() failed"));
        return NULL;
    }

    (xCallback->*cMethod)(cResponseCode, cStringList);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("Call failed"));
        return NULL;
    }

    jstring jFunc = env->NewStringUTF(GetJavaNativeMethodNameFromFunc(cFunc).c_str());
    if (env->ExceptionCheck() || !jFunc) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jFunc;
}

template <typename T>
jstring XCppTestDelegator::Call_Void_ResponseCode_String(JNIEnv *env, jobject jCallback, jobject jResponseCode, jstring jString, void (T::*cMethod)(const LSFResponseCode &, const std::string&), char const *cFunc)
{
    T* xCallback = GetHandle<T*>(jCallback);
    if (env->ExceptionCheck() || !xCallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jint xResponseCode = JEnum::jResponseCodeEnum->getValue(jResponseCode);
    LSFResponseCode cResponseCode = (LSFResponseCode)xResponseCode;
    if (env->ExceptionCheck() || (xResponseCode == (jint)-1)) {
        QCC_LogError(ER_FAIL, ("getValue() failed"));
        return NULL;
    }

    JString xString(jString);
    if (env->ExceptionCheck() || !xString.c_str()) {
        QCC_LogError(ER_FAIL, ("JString() failed"));
        return NULL;
    }

    (xCallback->*cMethod)(cResponseCode, xString.c_str());
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("Call failed"));
        return NULL;
    }

    jstring jFunc = env->NewStringUTF(GetJavaNativeMethodNameFromFunc(cFunc).c_str());
    if (env->ExceptionCheck() || !jFunc) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jFunc;
}

template <typename T>
jstring XCppTestDelegator::Call_Void_ResponseCode_String_String(JNIEnv *env, jobject jCallback, jobject jResponseCode, jstring jString1, jstring jString2, void (T::*cMethod)(const LSFResponseCode &, const std::string&, const std::string&), char const *cFunc)
{
    T* xCallback = GetHandle<T*>(jCallback);
    if (env->ExceptionCheck() || !xCallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jint xResponseCode = JEnum::jResponseCodeEnum->getValue(jResponseCode);
    LSFResponseCode cResponseCode = (LSFResponseCode)xResponseCode;
    if (env->ExceptionCheck() || (xResponseCode == (jint)-1)) {
        QCC_LogError(ER_FAIL, ("getValue() failed"));
        return NULL;
    }

    JString xString1(jString1);
    if (env->ExceptionCheck() || !xString1.c_str()) {
        QCC_LogError(ER_FAIL, ("JString() failed"));
        return NULL;
    }

    JString xString2(jString2);
    if (env->ExceptionCheck() || !xString2.c_str()) {
        QCC_LogError(ER_FAIL, ("JString() failed"));
        return NULL;
    }

    (xCallback->*cMethod)(cResponseCode, xString1.c_str(), xString2.c_str());
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("Call failed"));
        return NULL;
    }

    jstring jFunc = env->NewStringUTF(GetJavaNativeMethodNameFromFunc(cFunc).c_str());
    if (env->ExceptionCheck() || !jFunc) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jFunc;
}

template <typename T>
jstring XCppTestDelegator::Call_Void_ResponseCode_String_String_String(JNIEnv *env, jobject jCallback, jobject jResponseCode, jstring jString1, jstring jString2, jstring jString3, void (T::*cMethod)(const LSFResponseCode &, const std::string&, const std::string&, const std::string&), char const *cFunc)
{
    T* xCallback = GetHandle<T*>(jCallback);
    if (env->ExceptionCheck() || !xCallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jint xResponseCode = JEnum::jResponseCodeEnum->getValue(jResponseCode);
    LSFResponseCode cResponseCode = (LSFResponseCode)xResponseCode;
    if (env->ExceptionCheck() || (xResponseCode == (jint)-1)) {
        QCC_LogError(ER_FAIL, ("getValue() failed"));
        return NULL;
    }

    JString xString1(jString1);
    if (env->ExceptionCheck() || !xString1.c_str()) {
        QCC_LogError(ER_FAIL, ("JString() failed"));
        return NULL;
    }

    JString xString2(jString2);
    if (env->ExceptionCheck() || !xString2.c_str()) {
        QCC_LogError(ER_FAIL, ("JString() failed"));
        return NULL;
    }

    JString xString3(jString3);
    if (env->ExceptionCheck() || !xString3.c_str()) {
        QCC_LogError(ER_FAIL, ("JString() failed"));
        return NULL;
    }

    (xCallback->*cMethod)(cResponseCode, xString1.c_str(), xString2.c_str(), xString3.c_str());
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("Call failed"));
        return NULL;
    }

    jstring jFunc = env->NewStringUTF(GetJavaNativeMethodNameFromFunc(cFunc).c_str());
    if (env->ExceptionCheck() || !jFunc) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jFunc;
}

template <typename T>
jstring XCppTestDelegator::Call_Void_ResponseCode_String_Boolean(JNIEnv *env, jobject jCallback, jobject jResponseCode, jstring jString, jboolean jBoolean, void (T::*cMethod)(const LSFResponseCode &, const std::string&, const bool&), char const *cFunc)
{
    T* xCallback = GetHandle<T*>(jCallback);
    if (env->ExceptionCheck() || !xCallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jint xResponseCode = JEnum::jResponseCodeEnum->getValue(jResponseCode);
    LSFResponseCode cResponseCode = (LSFResponseCode)xResponseCode;
    if (env->ExceptionCheck() || (xResponseCode == (jint)-1)) {
        QCC_LogError(ER_FAIL, ("getValue() failed"));
        return NULL;
    }

    JString xString(jString);
    if (env->ExceptionCheck() || !xString.c_str()) {
        QCC_LogError(ER_FAIL, ("JString() failed"));
        return NULL;
    }
    (xCallback->*cMethod)(cResponseCode, xString.c_str(), (jBoolean == JNI_TRUE));

    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("Call failed"));
        return NULL;
    }

    jstring jFunc = env->NewStringUTF(GetJavaNativeMethodNameFromFunc(cFunc).c_str());
    if (env->ExceptionCheck() || !jFunc) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jFunc;
}

template <typename T>
jstring XCppTestDelegator::Call_Void_ResponseCode_String_UInt32(JNIEnv *env, jobject jCallback, jobject jResponseCode, jstring jString, jlong jLong, void (T::*cMethod)(const LSFResponseCode &, const std::string&, const uint32_t&), char const *cFunc)
{
    T* xCallback = GetHandle<T*>(jCallback);
    if (env->ExceptionCheck() || !xCallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jint xResponseCode = JEnum::jResponseCodeEnum->getValue(jResponseCode);
    LSFResponseCode cResponseCode = (LSFResponseCode)xResponseCode;
    if (env->ExceptionCheck() || (xResponseCode == (jint)-1)) {
        QCC_LogError(ER_FAIL, ("getValue() failed"));
        return NULL;
    }

    JString xString(jString);
    if (env->ExceptionCheck() || !xString.c_str()) {
        QCC_LogError(ER_FAIL, ("JString() failed"));
        return NULL;
    }

    (xCallback->*cMethod)(cResponseCode, xString.c_str(), (uint32_t)jLong);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("Call failed"));
        return NULL;
    }

    jstring jFunc = env->NewStringUTF(GetJavaNativeMethodNameFromFunc(cFunc).c_str());
    if (env->ExceptionCheck() || !jFunc) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jFunc;
}

template <typename T>
jstring XCppTestDelegator::Call_Void_ResponseCode_String_UInt32List(JNIEnv *env, jobject jCallback, jobject jResponseCode, jstring jString, jlongArray jLongList, void (T::*cMethod)(const LSFResponseCode &, const std::string&, const std::list<uint32_t>&), char const *cFunc)
{
    T* xCallback = GetHandle<T*>(jCallback);
    if (env->ExceptionCheck() || !xCallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jint xResponseCode = JEnum::jResponseCodeEnum->getValue(jResponseCode);
    LSFResponseCode cResponseCode = (LSFResponseCode)xResponseCode;
    if (env->ExceptionCheck() || (xResponseCode == (jint)-1)) {
        QCC_LogError(ER_FAIL, ("getValue() failed"));
        return NULL;
    }

    JString xString(jString);
    if (env->ExceptionCheck() || !xString.c_str()) {
        QCC_LogError(ER_FAIL, ("JString() failed"));
        return NULL;
    }

    std::list<uint32_t> cUIntList;
    XLongArray::CopyLongArray(jLongList, cUIntList);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("CopyStringArray() failed"));
        return NULL;
    }
    (xCallback->*cMethod)(cResponseCode, xString.c_str(), cUIntList);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("Call failed"));
        return NULL;
    }

    jstring jFunc = env->NewStringUTF(GetJavaNativeMethodNameFromFunc(cFunc).c_str());
    if (env->ExceptionCheck() || !jFunc) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }
    return jFunc;

}

template <typename T>
jstring XCppTestDelegator::Call_Void_ResponseCode_String_StringList(JNIEnv *env, jobject jCallback, jobject jResponseCode, jstring jString, jobjectArray jStringList, void (T::*cMethod)(const LSFResponseCode &, const std::string&, const std::list<std::string>&), char const *cFunc)
{

    T* xCallback = GetHandle<T*>(jCallback);
    if (env->ExceptionCheck() || !xCallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jint xResponseCode = JEnum::jResponseCodeEnum->getValue(jResponseCode);
    LSFResponseCode cResponseCode = (LSFResponseCode)xResponseCode;
    if (env->ExceptionCheck() || (xResponseCode == (jint)-1)) {
        QCC_LogError(ER_FAIL, ("getValue() failed"));
        return NULL;
    }

    JString xString(jString);
    if (env->ExceptionCheck() || !xString.c_str()) {
        QCC_LogError(ER_FAIL, ("JString() failed"));
        return NULL;
    }

    std::list<std::string> cStringList;
    JStringArray::CopyStringArray(jStringList, cStringList);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("CopyStringArray() failed"));
        return NULL;
    }

    (xCallback->*cMethod)(cResponseCode, xString.c_str(), cStringList);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("Call failed"));
        return NULL;
    }

    jstring jFunc = env->NewStringUTF(GetJavaNativeMethodNameFromFunc(cFunc).c_str());
    if (env->ExceptionCheck() || !jFunc) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jFunc;
}

template <typename T1, typename T2, typename T3>
jstring XCppTestDelegator::Call_Void_ResponseCode_Object(JNIEnv *env, jobject jCallback, jobject jResponseCode, jobject jObject, void (T1::*cMethod)(const LSFResponseCode &, const T3&), char const *cFunc)
{
    T1* xCallback = GetHandle<T1*>(jCallback);
    if (env->ExceptionCheck() || !xCallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jint xResponseCode = JEnum::jResponseCodeEnum->getValue(jResponseCode);
    LSFResponseCode cResponseCode = (LSFResponseCode)xResponseCode;
    if (env->ExceptionCheck() || (xResponseCode == (jint)-1)) {
        QCC_LogError(ER_FAIL, ("getValue() failed"));
        return NULL;
    }

    T2* xObject = GetHandle<T2*>(jObject);
    if (env->ExceptionCheck() || !xObject) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    T3 cObject = (T3&)(*xObject);

    (xCallback->*cMethod)(cResponseCode, cObject);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("Call failed"));
        return NULL;
    }

    jstring jFunc = env->NewStringUTF(GetJavaNativeMethodNameFromFunc(cFunc).c_str());
    if (env->ExceptionCheck() || !jFunc) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }

    return jFunc;
}

template <typename T1, typename T2, typename T3>
jstring XCppTestDelegator::Call_Void_ResponseCode_String_Object(JNIEnv *env, jobject jCallback, jobject jResponseCode, jstring jString, jobject jObject, void (T1::*cMethod)(const LSFResponseCode &, const std::string&, const T3&), char const *cFunc)
{
    T1* xCallback = GetHandle<T1*>(jCallback);
    if (env->ExceptionCheck() || !xCallback) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    jint xResponseCode = JEnum::jResponseCodeEnum->getValue(jResponseCode);
    LSFResponseCode cResponseCode = (LSFResponseCode)xResponseCode;
    if (env->ExceptionCheck() || (xResponseCode == (jint)-1)) {
        QCC_LogError(ER_FAIL, ("getValue() failed"));
        return NULL;
    }

    JString xString(jString);
    if (env->ExceptionCheck() || !xString.c_str()) {
        QCC_LogError(ER_FAIL, ("JString() failed"));
        return NULL;
    }

    T2* xObject = GetHandle<T2*>(jObject);
    if (env->ExceptionCheck() || !xObject) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return NULL;
    }

    T3 cObject = (T3&)(*xObject);
    std::string cString = xString.c_str();

    (xCallback->*cMethod)(cResponseCode, cString, cObject);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("Call failed"));
        return NULL;
    }

    jstring jFunc = env->NewStringUTF(GetJavaNativeMethodNameFromFunc(cFunc).c_str());
    if (env->ExceptionCheck() || !jFunc) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return NULL;
    }
    return jFunc;
}

} // namespace lsf

#undef QCC_MODULE

#endif /* LSF_JNI_XCPPTESTDELEGATOR_H_INCLUDE_TEMPLATE_METHODS */

