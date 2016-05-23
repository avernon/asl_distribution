# Copyright (c) 2014, AllSeen Alliance. All rights reserved.
#
#    Contributed by Qualcomm Connected Experiences, Inc.,
#    with authorization from the AllSeen Alliance, Inc.
#    
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#    
#        http://www.apache.org/licenses/LICENSE-2.0
#    
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#    
#    Pursuant to Section 1 of the License, the work of authorship constituting
#    a Work and any Contribution incorporated in the Work shall mean only that
#    Contributor's code submissions authored by that Contributor.  Any rights
#    granted under the License are conditioned upon acceptance of these
#    clarifications.

LOCAL_PATH := $(call my-dir)

MY_LSF_JAVA_HOME  := $(shell $(LOCAL_PATH)/../project_var LSF_JAVA_HOME $(ECLIPSE_WORKSPACE_PATH))
MY_LSF_JAVA_INC   := $(MY_LSF_JAVA_HOME)/jni
MY_LSF_JAVA_LIB   := $(MY_LSF_JAVA_HOME)/obj/local/$(APP_ABI)
$(info LSF_JAVA_HOME   = $(MY_LSF_JAVA_HOME))

MY_LSF_HOME            := $(shell $(LOCAL_PATH)/../project_var LSF_HOME $(ECLIPSE_WORKSPACE_PATH))
MY_LSF_COMMON_HOME     := $(MY_LSF_HOME)/common
MY_LSF_COMMON_INC      := $(MY_LSF_COMMON_HOME)/inc
MY_LSF_STD_COMMON_HOME := $(MY_LSF_HOME)/standard_core_library/common
MY_LSF_STD_COMMON_INC  := $(MY_LSF_STD_COMMON_HOME)/inc
MY_LSF_STD_COMMON_SRC  := ../$(MY_LSF_STD_COMMON_HOME)/src
MY_LSF_STD_CLIENT_HOME := $(MY_LSF_HOME)/standard_core_library/lighting_controller_client
MY_LSF_STD_CLIENT_INC  := $(MY_LSF_STD_CLIENT_HOME)/inc
MY_LSF_STD_CLIENT_SRC  := ../$(MY_LSF_STD_CLIENT_HOME)/src

MY_ALLJOYN_HOME    := $(shell $(MY_LSF_JAVA_HOME)/project_var ALLJOYN_HOME $(ECLIPSE_WORKSPACE_PATH))
MY_ALLJOYN_INC     := $(MY_ALLJOYN_HOME)/cpp/inc
MY_ALLJOYN_LIB     := $(MY_ALLJOYN_HOME)/java/lib

MY_ABOUT_HOME          := $(MY_ALLJOYN_HOME)
MY_ABOUT_INC           := $(MY_ABOUT_HOME)/about/inc
MY_ABOUT_LIB           := $(MY_ABOUT_HOME)/about/lib

LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog


# -----------------------------------------------------------------------------
include $(CLEAR_VARS)

LOCAL_MODULE            := alljoyn_java
LOCAL_SRC_FILES         := $(MY_ALLJOYN_LIB)/liballjoyn_java.so

include $(PREBUILT_SHARED_LIBRARY)


# -----------------------------------------------------------------------------
include $(CLEAR_VARS)

LOCAL_MODULE            := alljoyn_lsf_java
LOCAL_SRC_FILES         := $(MY_LSF_JAVA_LIB)/liballjoyn_lsf_java.so

ifneq ($(MAKECMDGOALS),clean)
include $(PREBUILT_SHARED_LIBRARY)
endif


# -----------------------------------------------------------------------------
include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(MY_ALLJOYN_INC) \
                    $(MY_ABOUT_INC) \
                    $(MY_LSF_COMMON_INC) \
                    $(MY_LSF_STD_COMMON_INC) \
                    $(MY_LSF_STD_CLIENT_INC) \
                    $(MY_LSF_JAVA_INC)

LOCAL_SHARED_LIBRARIES := alljoyn_java alljoyn_lsf_java

LOCAL_CFLAGS     := -DQCC_OS_GROUP_POSIX -DQCC_OS_ANDROID -DQCC_CPU_ARM -fpic
LOCAL_LDLIBS     := -llog

LOCAL_MODULE     := alljoyn_lsf_java_test
LOCAL_SRC_FILES  := org_allseen_lsf_test_ControllerClientCallbackTest.cpp \
                    org_allseen_lsf_test_LampGroupManagerCallbackTest.cpp \
                    org_allseen_lsf_test_LampManagerCallbackTest.cpp \
                    org_allseen_lsf_test_PresetManagerCallbackTest.cpp \
                    org_allseen_lsf_test_ResponseCodeTest.cpp \
                    org_allseen_lsf_test_StatusCodeTest.cpp \
                    org_allseen_lsf_test_TransitionEffectManagerCallbackTest.cpp\
                    org_allseen_lsf_test_PulseEffectManagerCallbackTest.cpp\
                    org_allseen_lsf_test_SceneElementManagerCallbackTest.cpp\
                    org_allseen_lsf_test_SceneManagerCallbackTest.cpp\
                    org_allseen_lsf_test_MasterSceneManagerCallbackTest.cpp\
                    XCppTestDelegator.cpp

include $(BUILD_SHARED_LIBRARY)


