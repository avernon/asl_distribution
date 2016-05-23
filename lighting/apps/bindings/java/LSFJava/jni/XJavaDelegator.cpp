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

#include "JEnum.h"
#include "JStringArray.h"
#include "JEnumArray.h"
#include "XLongArray.h"
#include "XJavaDelegator.h"

#define QCC_MODULE "AJN-LSF-JNI"


namespace lsf {

// This .cpp file is #include'd in the .h file because some templated
// methods must be defined there. The following #ifndef prevents the
// non-templated code from being visible there.
#ifndef LSF_JNI_XJAVADELEGATOR_H_INCLUDE_TEMPLATE_METHODS
void XJavaDelegator::Call_Void(const jweak jdelegate, char const *func)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    Call_Void_Variadic(env, jdelegate, func, "()V");
}

void XJavaDelegator::Call_Void_UInt32(const jweak jdelegate, char const *func, const uint32_t &uint32Value)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    Call_Void_Variadic(env, jdelegate, func, "(J)V", (jlong)uint32Value);
}

void XJavaDelegator::Call_Void_VoidPointer(const jweak jdelegate, char const *func, const void *voidPointer)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    Call_Void_Variadic(env, jdelegate, func, "(J)V", (jlong)voidPointer);
}

void XJavaDelegator::Call_Void_ResponseCode(const jweak jdelegate, char const *func, const LSFResponseCode &responseCode)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    jobject jresponseCode = JEnum::jResponseCodeEnum->getObject(responseCode);
    if (env->ExceptionCheck() || !jresponseCode) {
        QCC_LogError(ER_FAIL, ("getObject() failed"));
        return;
    }

    Call_Void_Variadic(env, jdelegate, func, "(Lorg/allseen/lsf/sdk/ResponseCode;)V", jresponseCode);
}

void XJavaDelegator::Call_Void_StringList(const jweak jdelegate, char const *func, const LSFStringList &strList)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    jobjectArray jstrList = JStringArray::NewStringArray(strList);
    if (env->ExceptionCheck() || !jstrList) {
        QCC_LogError(ER_FAIL, ("NewStringArray() failed"));
        return;
    }

    Call_Void_Variadic(env, jdelegate, func, "([Ljava/lang/String;)V", jstrList);
}
#endif //LSF_JNI_XJAVADELEGATOR_H_INCLUDE_TEMPLATE_METHODS

// This .cpp file is #include'd in the .h file because some templated
// methods must be defined there. The following #ifdef allows the
// templated code to be visible there.
#ifdef LSF_JNI_XJAVADELEGATOR_H_INCLUDE_TEMPLATE_METHODS
template <typename CTYPE>
void XJavaDelegator::Call_Void_EnumList(const jweak jdelegate, char const *func, JEnum *xEnum, const std::list<CTYPE> &cEnumList)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    jobjectArray jEnumList = JEnumArray::NewEnumArray<CTYPE>(*xEnum, cEnumList);
    if (env->ExceptionCheck() || !jEnumList) {
        QCC_LogError(ER_FAIL, ("NewEnumArray() failed"));
        return;
    }

    char sig[512];
    snprintf(sig, sizeof(sig), "([L%s;)V", xEnum->getClassName());

    Call_Void_Variadic(env, jdelegate, func, sig, jEnumList);
}
#endif //LSF_JNI_XJAVADELEGATOR_H_INCLUDE_TEMPLATE_METHODS

// This .cpp file is #include'd in the .h file because some templated
// methods must be defined there. The following #ifndef prevents the
// non-templated code from being visible there.
#ifndef LSF_JNI_XJAVADELEGATOR_H_INCLUDE_TEMPLATE_METHODS
void XJavaDelegator::Call_Void_ResponseCode_String(const jweak jdelegate, char const *func, const LSFResponseCode &responseCode, const LSFString &strValue)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    jobject jresponseCode = JEnum::jResponseCodeEnum->getObject(responseCode);
    if (env->ExceptionCheck() || !jresponseCode) {
        QCC_LogError(ER_FAIL, ("getObject() failed"));
        return;
    }

    jstring jstrValue = env->NewStringUTF(strValue.c_str());
    if (env->ExceptionCheck() || !jstrValue) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return;
    }

    Call_Void_Variadic(env, jdelegate, func, "(Lorg/allseen/lsf/sdk/ResponseCode;Ljava/lang/String;)V", jresponseCode, jstrValue);
}

void XJavaDelegator::Call_Void_ResponseCode_StringList(const jweak jdelegate, char const *func, const LSFResponseCode &responseCode, const LSFStringList &strList)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    jobject jresponseCode = JEnum::jResponseCodeEnum->getObject(responseCode);
    if (env->ExceptionCheck() || !jresponseCode) {
        QCC_LogError(ER_FAIL, ("getObject() failed"));
        return;
    }

    jobjectArray jstrList = JStringArray::NewStringArray(strList);
    if (env->ExceptionCheck() || !jstrList) {
        QCC_LogError(ER_FAIL, ("NewStringArray() failed"));
        return;
    }

    Call_Void_Variadic(env, jdelegate, func, "(Lorg/allseen/lsf/sdk/ResponseCode;[Ljava/lang/String;)V", jresponseCode, jstrList);
}
#endif //LSF_JNI_XJAVADELEGATOR_H_INCLUDE_TEMPLATE_METHODS

// This .cpp file is #include'd in the .h file because some templated
// methods must be defined there. The following #ifdef allows the
// templated code to be visible there.
#ifdef LSF_JNI_XJAVADELEGATOR_H_INCLUDE_TEMPLATE_METHODS
template <typename CTYPE, typename XTYPE>
void XJavaDelegator::Call_Void_String_Object(const jweak jdelegate, char const *func, XClass *xClass, const LSFString &strValue, const CTYPE &objValue)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    jstring jstrValue = env->NewStringUTF(strValue.c_str());
    if (env->ExceptionCheck() || !jstrValue) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return;
    }

    jmethodID jconstructor = env->GetMethodID(xClass->classRef, "<init>", "()V");
    if (env->ExceptionCheck() || !jconstructor) {
        QCC_LogError(ER_FAIL, ("GetMethodID() failed"));
        return;
    }

    jobject jobjValue = env->NewObject(xClass->classRef, jconstructor);
    if (env->ExceptionCheck() || !jobjValue) {
        QCC_LogError(ER_FAIL, ("NewObject() failed"));
        return;
    }

    XTYPE *xobjValue = GetHandle<XTYPE *>(jobjValue);
    if (env->ExceptionCheck() || !xobjValue) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    *xobjValue = objValue;

    char sig[512];
    snprintf(sig, sizeof(sig), "(Ljava/lang/String;L%s;)V", xClass->className);

    Call_Void_Variadic(env, jdelegate, func, sig, jstrValue, jobjValue);
}
#endif //LSF_JNI_XJAVADELEGATOR_H_INCLUDE_TEMPLATE_METHODS


// This .cpp file is #include'd in the .h file because some templated
// methods must be defined there. The following #ifndef prevents the
// non-templated code from being visible there.
#ifndef LSF_JNI_XJAVADELEGATOR_H_INCLUDE_TEMPLATE_METHODS
void XJavaDelegator::Call_Void_String_String(const jweak jdelegate, char const *func, const LSFString &strValue1, const LSFString &strValue2)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    jstring jstrValue1 = env->NewStringUTF(strValue1.c_str());
    if (env->ExceptionCheck() || !jstrValue1) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return;
    }

    jstring jstrValue2 = env->NewStringUTF(strValue2.c_str());
    if (env->ExceptionCheck() || !jstrValue2) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return;
    }

    Call_Void_Variadic(env, jdelegate, func, "(Ljava/lang/String;Ljava/lang/String;)V", jstrValue1, jstrValue2);
}

void XJavaDelegator::Call_Void_ResponseCode_String_Boolean(const jweak jdelegate, char const *func, const LSFResponseCode &responseCode, const LSFString &strValue, const bool &boolValue)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    jobject jresponseCode = JEnum::jResponseCodeEnum->getObject(responseCode);
    if (env->ExceptionCheck() || !jresponseCode) {
        QCC_LogError(ER_FAIL, ("getObject() failed"));
        return;
    }

    jstring jstrValue = env->NewStringUTF(strValue.c_str());
    if (env->ExceptionCheck() || !jstrValue) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return;
    }

    jboolean jboolValue = (jboolean)boolValue;

    Call_Void_Variadic(env, jdelegate, func, "(Lorg/allseen/lsf/sdk/ResponseCode;Ljava/lang/String;Z)V", jresponseCode, jstrValue, jboolValue);
}

void XJavaDelegator::Call_Void_ResponseCode_String_UInt32(const jweak jdelegate, char const *func, const LSFResponseCode &responseCode, const LSFString &strValue, const uint32_t &uint32Value)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    jobject jresponseCode = JEnum::jResponseCodeEnum->getObject(responseCode);
    if (env->ExceptionCheck() || !jresponseCode) {
        QCC_LogError(ER_FAIL, ("getObject() failed"));
        return;
    }

    jstring jstrValue = env->NewStringUTF(strValue.c_str());
    if (env->ExceptionCheck() || !jstrValue) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return;
    }

    jlong jlongValue = (jlong)uint32Value;

    Call_Void_Variadic(env, jdelegate, func, "(Lorg/allseen/lsf/sdk/ResponseCode;Ljava/lang/String;J)V", jresponseCode, jstrValue, jlongValue);
}

void XJavaDelegator::Call_Void_ResponseCode_String_Enum(const jweak jdelegate, char const *func, const LSFResponseCode &responseCode, const LSFString &strValue, JEnum *enumObject, const int &enumValue, char const *enumClass)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    jobject jresponseCode = JEnum::jResponseCodeEnum->getObject(responseCode);
    if (env->ExceptionCheck() || !jresponseCode) {
        QCC_LogError(ER_FAIL, ("getObject() failed"));
        return;
    }

    jstring jstrValue = env->NewStringUTF(strValue.c_str());
    if (env->ExceptionCheck() || !jstrValue) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return;
    }

    jobject jenumValue = enumObject->getObject(enumValue);
    if (env->ExceptionCheck() || !jenumValue) {
        QCC_LogError(ER_FAIL, ("getObject() failed"));
        return;
    }

    char sig[512];
    snprintf(sig, sizeof(sig), "(Lorg/allseen/lsf/sdk/ResponseCode;Ljava/lang/String;L%s;)V", enumClass);

    Call_Void_Variadic(env, jdelegate, func, sig, jresponseCode, jstrValue, jenumValue);
}

void XJavaDelegator::Call_Void_ResponseCode_String_String(const jweak jdelegate, char const *func, const LSFResponseCode &responseCode, const LSFString &strValue1, const LSFString &strValue2)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    jobject jresponseCode = JEnum::jResponseCodeEnum->getObject(responseCode);
    if (env->ExceptionCheck() || !jresponseCode) {
        QCC_LogError(ER_FAIL, ("getObject() failed"));
        return;
    }

    jstring jstrValue1 = env->NewStringUTF(strValue1.c_str());
    if (env->ExceptionCheck() || !jstrValue1) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return;
    }

    jstring jstrValue2 = env->NewStringUTF(strValue2.c_str());
    if (env->ExceptionCheck() || !jstrValue2) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return;
    }

    Call_Void_Variadic(env, jdelegate, func, "(Lorg/allseen/lsf/sdk/ResponseCode;Ljava/lang/String;Ljava/lang/String;)V", jresponseCode, jstrValue1, jstrValue2);
}
#endif //LSF_JNI_XJAVADELEGATOR_H_INCLUDE_TEMPLATE_METHODS

// This .cpp file is #include'd in the .h file because some templated
// methods must be defined there. The following #ifdef allows the
// templated code to be visible there.
#ifdef LSF_JNI_XJAVADELEGATOR_H_INCLUDE_TEMPLATE_METHODS
template <typename CTYPE, typename XTYPE>
void XJavaDelegator::Call_Void_ResponseCode_String_Object(const jweak jdelegate, char const *func, XClass *xClass, const LSFResponseCode &responseCode, const LSFString &strValue, const CTYPE &objValue)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    jobject jresponseCode = JEnum::jResponseCodeEnum->getObject(responseCode);
    if (env->ExceptionCheck() || !jresponseCode) {
        QCC_LogError(ER_FAIL, ("getObject() failed"));
        return;
    }

    jstring jstrValue = env->NewStringUTF(strValue.c_str());
    if (env->ExceptionCheck() || !jstrValue) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return;
    }

    jmethodID jconstructor = env->GetMethodID(xClass->classRef, "<init>", "()V");
    if (env->ExceptionCheck() || !jconstructor) {
        QCC_LogError(ER_FAIL, ("GetMethodID() failed"));
        return;
    }

    jobject jobjValue = env->NewObject(xClass->classRef, jconstructor);
    if (env->ExceptionCheck() || !jobjValue) {
        QCC_LogError(ER_FAIL, ("NewObject() failed"));
        return;
    }

    XTYPE *xobjValue = GetHandle<XTYPE *>(jobjValue);
    if (env->ExceptionCheck() || !xobjValue) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    *xobjValue = objValue;

    char sig[512];
    snprintf(sig, sizeof(sig), "(Lorg/allseen/lsf/sdk/ResponseCode;Ljava/lang/String;L%s;)V", xClass->className);

    Call_Void_Variadic(env, jdelegate, func, sig, jresponseCode, jstrValue, jobjValue);
}

template <typename CTYPE1, typename XTYPE1, typename CTYPE2, typename XTYPE2, typename CTYPE3, typename XTYPE3>
void XJavaDelegator::Call_Void_ResponseCode_String_String_String_Object_Object_Object(const jweak jdelegate, char const *func, XClass *xClass1, XClass *xClass2, XClass *xClass3, const LSFResponseCode &responseCode, const LSFString &strValue1, const LSFString &strValue2, const LSFString &strValue3, const CTYPE1 &objValue1, const CTYPE2 &objValue2, const CTYPE3 &objValue3)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    jobject jresponseCode = JEnum::jResponseCodeEnum->getObject(responseCode);
    if (env->ExceptionCheck() || !jresponseCode) {
        QCC_LogError(ER_FAIL, ("getObject() failed"));
        return;
    }

    jstring jstrValue1 = env->NewStringUTF(strValue1.c_str());
    if (env->ExceptionCheck() || !jstrValue1) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return;
    }

    jstring jstrValue2 = env->NewStringUTF(strValue2.c_str());
    if (env->ExceptionCheck() || !jstrValue2) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return;
    }

    jstring jstrValue3 = env->NewStringUTF(strValue3.c_str());
    if (env->ExceptionCheck() || !jstrValue3) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return;
    }

    jmethodID jconstructor1 = env->GetMethodID(xClass1->classRef, "<init>", "()V");
    if (env->ExceptionCheck() || !jconstructor1) {
        QCC_LogError(ER_FAIL, ("GetMethodID() failed"));
        return;
    }

    jobject jobjValue1 = env->NewObject(xClass1->classRef, jconstructor1);
    if (env->ExceptionCheck() || !jobjValue1) {
        QCC_LogError(ER_FAIL, ("NewObject() failed"));
        return;
    }

    XTYPE1 *xobjValue1 = GetHandle<XTYPE1 *>(jobjValue1);
    if (env->ExceptionCheck() || !xobjValue1) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    jmethodID jconstructor2 = env->GetMethodID(xClass2->classRef, "<init>", "()V");
    if (env->ExceptionCheck() || !jconstructor2) {
        QCC_LogError(ER_FAIL, ("GetMethodID() failed"));
        return;
    }

    jobject jobjValue2 = env->NewObject(xClass2->classRef, jconstructor2);
    if (env->ExceptionCheck() || !jobjValue2) {
        QCC_LogError(ER_FAIL, ("NewObject() failed"));
        return;
    }

    XTYPE2 *xobjValue2 = GetHandle<XTYPE2 *>(jobjValue2);
    if (env->ExceptionCheck() || !xobjValue2) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    jmethodID jconstructor3 = env->GetMethodID(xClass3->classRef, "<init>", "()V");
    if (env->ExceptionCheck() || !jconstructor3) {
        QCC_LogError(ER_FAIL, ("GetMethodID() failed"));
        return;
    }

    jobject jobjValue3 = env->NewObject(xClass3->classRef, jconstructor3);
    if (env->ExceptionCheck() || !jobjValue3) {
        QCC_LogError(ER_FAIL, ("NewObject() failed"));
        return;
    }

    XTYPE3 *xobjValue3 = GetHandle<XTYPE3 *>(jobjValue3);
    if (env->ExceptionCheck() || !xobjValue3) {
        QCC_LogError(ER_FAIL, ("GetHandle() failed"));
        return;
    }

    *xobjValue1 = objValue1;
    *xobjValue2 = objValue2;
    *xobjValue3 = objValue3;

    char sig[512];
    snprintf(sig, sizeof(sig), "(Lorg/allseen/lsf/sdk/ResponseCode;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;L%s;L%s;L%s;)V", xClass1->className, xClass2->className, xClass3->className);

    Call_Void_Variadic(env, jdelegate, func, sig, jresponseCode, jstrValue1, jstrValue2, jstrValue3, jobjValue1, jobjValue2, jobjValue3);
}

#endif //LSF_JNI_XJAVADELEGATOR_H_INCLUDE_TEMPLATE_METHODS

// This .cpp file is #include'd in the .h file because some templated
// methods must be defined there. The following #ifndef prevents the
// non-templated code from being visible there.
#ifndef LSF_JNI_XJAVADELEGATOR_H_INCLUDE_TEMPLATE_METHODS
void XJavaDelegator::Call_Void_ResponseCode_String_UInt32List(const jweak jdelegate, char const *func, const LSFResponseCode &responseCode, const LSFString &strValue, const UInt32List& uint32List)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    jobject jresponseCode = JEnum::jResponseCodeEnum->getObject(responseCode);
    if (env->ExceptionCheck() || !jresponseCode) {
        QCC_LogError(ER_FAIL, ("getObject() failed"));
        return;
    }

    jstring jstrValue = env->NewStringUTF(strValue.c_str());
    if (env->ExceptionCheck() || !jstrValue) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return;
    }

    Call_Void_Variadic(env, jdelegate, func, "(Lorg/allseen/lsf/sdk/ResponseCode;Ljava/lang/String;[J)V", jresponseCode, jstrValue, XLongArray::NewLongArray(uint32List));
}

void XJavaDelegator::Call_Void_ResponseCode_String_StringList(const jweak jdelegate, char const *func, const LSFResponseCode &responseCode, const LSFString &strValue, const LSFStringList &strList)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    jobject jresponseCode = JEnum::jResponseCodeEnum->getObject(responseCode);
    if (env->ExceptionCheck() || !jresponseCode) {
        QCC_LogError(ER_FAIL, ("getObject() failed"));
        return;
    }

    jstring jstrValue = env->NewStringUTF(strValue.c_str());
    if (env->ExceptionCheck() || !jstrValue) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return;
    }

    jobjectArray jstrList = JStringArray::NewStringArray(strList);
    if (env->ExceptionCheck() || !jstrList) {
        QCC_LogError(ER_FAIL, ("NewStringArray() failed"));
        return;
    }

    Call_Void_Variadic(env, jdelegate, func, "(Lorg/allseen/lsf/sdk/ResponseCode;Ljava/lang/String;[Ljava/lang/String;)V", jresponseCode, jstrValue, jstrList);
}

void XJavaDelegator::Call_Void_ResponseCode_String_String_String(const jweak jdelegate, char const *func, const LSFResponseCode &responseCode, const LSFString &strValue1, const LSFString &strValue2, const LSFString &strValue3)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    jobject jresponseCode = JEnum::jResponseCodeEnum->getObject(responseCode);
    if (env->ExceptionCheck() || !jresponseCode) {
        QCC_LogError(ER_FAIL, ("getObject() failed"));
        return;
    }

    jstring jstrValue1 = env->NewStringUTF(strValue1.c_str());
    if (env->ExceptionCheck() || !jstrValue1) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return;
    }

    jstring jstrValue2 = env->NewStringUTF(strValue2.c_str());
    if (env->ExceptionCheck() || !jstrValue2) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return;
    }

    jstring jstrValue3 = env->NewStringUTF(strValue3.c_str());
    if (env->ExceptionCheck() || !jstrValue3) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return;
    }

    Call_Void_Variadic(env, jdelegate, func, "(Lorg/allseen/lsf/sdk/ResponseCode;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", jresponseCode, jstrValue1, jstrValue2, jstrValue3);
}

void XJavaDelegator::Call_Void_Variadic(JScopedEnv& env, const jweak jdelegate, const char *func, char const * const sig, ...)
{
    /*
     * The weak reference to the Java delegate cannot be directly used.  We have to get
     * a "hard" reference to it and then use that. If you try to use a weak reference
     * directly you will crash and burn.
     */
    jobject jobj = env->NewLocalRef(jdelegate);
    if (env->ExceptionCheck() || !jobj) {
        QCC_LogError(ER_FAIL, ("NewLocalRef() failed"));
        return;
    }

    jclass clazz = env->GetObjectClass(jobj);
    if (env->ExceptionCheck() || !clazz) {
        QCC_LogError(ER_FAIL, ("GetObjectClass() failed"));
        return;
    }

    std::string jfunc = GetJavaMethodNameFromCPPMethodName(func);
    jmethodID mid = env->GetMethodID(clazz, jfunc.c_str(), sig);
    if (env->ExceptionCheck() || !mid) {
        QCC_LogError(ER_FAIL, ("GetMethodID() failed"));
        return;
    }

    va_list args;
    va_start(args, sig);
    env->CallVoidMethodV(jobj, mid, args);
    va_end(args);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("CallVoidMethod() exception"));
        return;
    }
}

LSFString XJavaDelegator::Call_String_String(const jweak jdelegate, char const *func, const LSFString &strValue, const LSFString &strDefault)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    /*
     * The weak reference to the Java delegate cannot be directly used.  We have to get
     * a "hard" reference to it and then use that. If you try to use a weak reference
     * directly you will crash and burn.
     */
    jobject jobj = env->NewLocalRef(jdelegate);
    if (env->ExceptionCheck() || !jobj) {
        QCC_LogError(ER_FAIL, ("NewLocalRef() failed"));
        return strDefault;
    }

    jclass clazz = env->GetObjectClass(jobj);
    if (env->ExceptionCheck() || !clazz) {
        QCC_LogError(ER_FAIL, ("GetObjectClass() failed"));
        return strDefault;
    }

    std::string jfunc = GetJavaMethodNameFromCPPMethodName(func);
    jmethodID mid = env->GetMethodID(clazz, jfunc.c_str(), "(Ljava/lang/String;)Ljava/lang/String;");
    if (env->ExceptionCheck() || !mid) {
        QCC_LogError(ER_FAIL, ("GetMethodID() failed"));
        return strDefault;
    }

    jstring jstrValue = env->NewStringUTF(strValue.c_str());
    if (env->ExceptionCheck() || !jstrValue) {
        QCC_LogError(ER_FAIL, ("NewStringUTF() failed"));
        return strDefault;
    }

    jstring jstrReturn = (jstring)env->CallObjectMethod(jobj, mid, jstrValue);
    if (env->ExceptionCheck() || !jstrReturn) {
        QCC_LogError(ER_FAIL, ("CallObjectMethod() exception"));
        return strDefault;
    }

    const char *cstrReturn = env->GetStringUTFChars(jstrReturn, NULL);
    LSFString strReturn = cstrReturn;
    env->ReleaseStringUTFChars(jstrReturn, cstrReturn);

    return strReturn;
}

bool XJavaDelegator::Call_Boolean(const jweak jdelegate, char const *func, const bool &boolDefault)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    /*
     * The weak reference to the Java delegate cannot be directly used.  We have to get
     * a "hard" reference to it and then use that. If you try to use a weak reference
     * directly you will crash and burn.
     */
    jobject jobj = env->NewLocalRef(jdelegate);
    if (env->ExceptionCheck() || !jobj) {
        QCC_LogError(ER_FAIL, ("NewLocalRef() failed"));
        return boolDefault;
    }

    jclass clazz = env->GetObjectClass(jobj);
    if (env->ExceptionCheck() || !clazz) {
        QCC_LogError(ER_FAIL, ("GetObjectClass() failed"));
        return boolDefault;
    }

    std::string jfunc = GetJavaMethodNameFromCPPMethodName(func);
    jmethodID mid = env->GetMethodID(clazz, jfunc.c_str(), "()Z");
    if (env->ExceptionCheck() || !mid) {
        QCC_LogError(ER_FAIL, ("GetMethodID() failed"));
        return boolDefault;
    }

    jboolean jboolReturn = env->CallBooleanMethod(jobj, mid);
    if (env->ExceptionCheck()) {
        QCC_LogError(ER_FAIL, ("CallBooleanMethod() exception"));
        return boolDefault;
    }

    return jboolReturn == JNI_TRUE;
}

#endif //LSF_JNI_XJAVADELEGATOR_H_INCLUDE_TEMPLATE_METHODS

// This .cpp file is #include'd in the .h file because some templated
// methods must be defined there. The following #ifdef allows the
// templated code to be visible there.
#ifdef LSF_JNI_XJAVADELEGATOR_H_INCLUDE_TEMPLATE_METHODS
template <typename CTYPE>
CTYPE XJavaDelegator::Call_Enum(const jweak jdelegate, char const *func, JEnum *xEnum, const CTYPE &enumDefault)
{
    // Get the JNIEnv for the current native thread
    JScopedEnv env;

    /*
     * The weak reference to the Java delegate cannot be directly used.  We have to get
     * a "hard" reference to it and then use that. If you try to use a weak reference
     * directly you will crash and burn.
     */
    jobject jobj = env->NewLocalRef(jdelegate);
    if (env->ExceptionCheck() || !jobj) {
        QCC_LogError(ER_FAIL, ("NewLocalRef() failed"));
        return enumDefault;
    }

    jclass clazz = env->GetObjectClass(jobj);
    if (env->ExceptionCheck() || !clazz) {
        QCC_LogError(ER_FAIL, ("GetObjectClass() failed"));
        return enumDefault;
    }

    char sig[512];
    snprintf(sig, sizeof(sig), "()L%s;", xEnum->getClassName());

    std::string jfunc = GetJavaMethodNameFromCPPMethodName(func);
    jmethodID mid = env->GetMethodID(clazz, jfunc.c_str(), sig);
    if (env->ExceptionCheck() || !mid) {
        QCC_LogError(ER_FAIL, ("GetMethodID() failed"));
        return enumDefault;
    }

    jobject jenumReturn = env->CallObjectMethod(jobj, mid);
    if (env->ExceptionCheck() || !jenumReturn) {
        QCC_LogError(ER_FAIL, ("CallObjectMethod() exception"));
        return enumDefault;
    }

    return (CTYPE)xEnum->getValue(jenumReturn);
}

#endif //LSF_JNI_XJAVADELEGATOR_H_INCLUDE_TEMPLATE_METHODS

} //namespace lsf

#undef QCC_MODULE

