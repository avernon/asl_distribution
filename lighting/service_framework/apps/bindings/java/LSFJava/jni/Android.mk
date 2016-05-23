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

#$(info ECLIPSE_WORKSPACE_PATH = $(ECLIPSE_WORKSPACE_PATH))

MY_ALLJOYN_HOME        := $(shell $(LOCAL_PATH)/../project_var ALLJOYN_HOME $(ECLIPSE_WORKSPACE_PATH))
MY_ALLJOYN_INC         := $(MY_ALLJOYN_HOME)/cpp/inc
MY_ALLJOYN_LIB         := $(MY_ALLJOYN_HOME)/java/lib
#$(info ALLJOYN_HOME   = $(MY_ALLJOYN_HOME))
#$(info ALLJOYN_INC    = $(MY_ALLJOYN_INC))
#$(info ALLJOYN_LIB    = $(MY_ALLJOYN_LIB))

MY_ABOUT_HOME          := $(MY_ALLJOYN_HOME)
MY_ABOUT_INC           := $(MY_ABOUT_HOME)/about/inc
MY_ABOUT_LIB           := $(MY_ABOUT_HOME)/about/lib
#$(info ABOUT_HOME   = $(MY_ABOUT_HOME))
#$(info ABOUT_INC    = $(MY_ABOUT_INC))
#$(info ABOUT_LIB    = $(MY_ABOUT_LIB))

MY_LSF_HOME            := ../../../../../service_framework
MY_LSF_COMMON_HOME     := $(MY_LSF_HOME)/common
MY_LSF_COMMON_INC      := $(MY_LSF_COMMON_HOME)/inc
MY_LSF_STD_COMMON_HOME := $(MY_LSF_HOME)/standard_core_library/common
MY_LSF_STD_COMMON_INC  := $(MY_LSF_STD_COMMON_HOME)/inc
MY_LSF_STD_COMMON_SRC  := ../$(MY_LSF_STD_COMMON_HOME)/src
MY_LSF_STD_CLIENT_HOME := $(MY_LSF_HOME)/standard_core_library/lighting_controller_client
MY_LSF_STD_CLIENT_INC  := $(MY_LSF_STD_CLIENT_HOME)/inc
MY_LSF_STD_CLIENT_SRC  := ../$(MY_LSF_STD_CLIENT_HOME)/src
#$(info LSF_HOME        = $(MY_LSF_HOME))
#$(info LSF_STD_CLIENT_HOME = $(MY_LSF_STD_CLIENT_HOME))
#$(info LSF_STD_CLIENT_INC  = $(MY_LSF_STD_CLIENT_INC))
#$(info LSF_STD_CLIENT_SRC  = $(MY_LSF_STD_CLIENT_SRC))



# -----------------------------------------------------------------------------
#include $(CLEAR_VARS)

#LOCAL_MODULE            := alljoyn_lsf
#LOCAL_SRC_FILES         := $(MY_LSF_HOME)/build/android/arm/debug/dist/lsf/lib/liballjoyn_lsf.so

#include $(PREBUILT_SHARED_LIBRARY)


# -----------------------------------------------------------------------------
include $(CLEAR_VARS)

LOCAL_MODULE            := alljoyn_java
LOCAL_SRC_FILES         := $(MY_ALLJOYN_LIB)/liballjoyn_java.so

include $(PREBUILT_SHARED_LIBRARY)


# -----------------------------------------------------------------------------
include $(CLEAR_VARS)

LOCAL_MODULE            := alljoyn_about
LOCAL_SRC_FILES         := $(MY_ABOUT_LIB)/liballjoyn_about.a

include $(PREBUILT_STATIC_LIBRARY)


# ----------------------------------------------------------------------------
include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(MY_LSF_COMMON_INC) \
                    $(MY_LSF_STD_COMMON_INC) \
                    $(MY_LSF_STD_CLIENT_INC) \
                    $(MY_ALLJOYN_INC) \
                    $(MY_ALLJOYN_INC)/alljoyn \
                    $(MY_ABOUT_INC)
                    
LOCAL_SHARED_LIBRARIES := alljoyn_java
LOCAL_STATIC_LIBRARIES := alljoyn_about

LOCAL_CFLAGS     := -DQCC_OS_GROUP_POSIX -DQCC_OS_ANDROID -DQCC_CPU_ARM -fpic
LOCAL_LDLIBS	 := -llog

LOCAL_MODULE     := alljoyn_lsf_java
LOCAL_SRC_FILES  := $(MY_LSF_STD_CLIENT_SRC)/ControllerClient.cc \
					$(MY_LSF_STD_CLIENT_SRC)/ControllerClientDefs.cc \
					$(MY_LSF_STD_CLIENT_SRC)/ControllerServiceManager.cc \
					$(MY_LSF_STD_CLIENT_SRC)/LampGroupManager.cc \
					$(MY_LSF_STD_CLIENT_SRC)/LampManager.cc \
					$(MY_LSF_STD_CLIENT_SRC)/Manager.cc \
					$(MY_LSF_STD_CLIENT_SRC)/MasterSceneManager.cc \
					$(MY_LSF_STD_CLIENT_SRC)/PresetManager.cc \
					$(MY_LSF_STD_CLIENT_SRC)/SceneManager.cc \
                    $(MY_LSF_STD_COMMON_SRC)/LSFKeyListener.cc \
                    $(MY_LSF_STD_COMMON_SRC)/LSFResponseCodes.cc \
					$(MY_LSF_STD_COMMON_SRC)/LSFSemaphore.cc \
                    $(MY_LSF_STD_COMMON_SRC)/LSFTypes.cc \
                    $(MY_LSF_STD_COMMON_SRC)/Mutex.cc \
                    $(MY_LSF_STD_COMMON_SRC)/Thread.cc \
					JByteArray.cpp \
					JControllerClient.cpp \
					JControllerClientCallback.cpp \
					JEnum.cpp \
					JEnumArray.cpp \
					JIntArray.cpp \
					JLampDetails.cpp \
					JLampGroup.cpp \
					JLampGroupManager.cpp \
					JLampGroupManagerCallback.cpp \
					JLampManager.cpp \
					JLampManagerCallback.cpp \
					JLampParameters.cpp \
					JLampState.cpp \
					JPrimitiveArray.cpp \
					JStringArray.cpp \
					NUtil.cpp \
					org_allseen_lsf_ControllerClient.cpp \
					org_allseen_lsf_ControllerClientCallback.cpp \
					org_allseen_lsf_ControllerServiceManager.cpp \
					org_allseen_lsf_ControllerServiceManagerCallback.cpp \
					org_allseen_lsf_LampDetails.cpp \
					org_allseen_lsf_LampGroup.cpp \
					org_allseen_lsf_LampGroupManager.cpp \
					org_allseen_lsf_LampGroupManagerCallback.cpp \
					org_allseen_lsf_LampManager.cpp \
					org_allseen_lsf_LampManagerCallback.cpp \
					org_allseen_lsf_LampParameters.cpp \
					org_allseen_lsf_LampState.cpp \
					org_allseen_lsf_MasterScene.cpp \
					org_allseen_lsf_MasterSceneManager.cpp \
					org_allseen_lsf_MasterSceneManagerCallback.cpp \
					org_allseen_lsf_PresetManager.cpp \
					org_allseen_lsf_PresetManagerCallback.cpp \
					org_allseen_lsf_PresetPulseEffect.cpp \
					org_allseen_lsf_PresetTransitionEffect.cpp \
					org_allseen_lsf_Scene.cpp \
					org_allseen_lsf_SceneManager.cpp \
					org_allseen_lsf_SceneManagerCallback.cpp \
					org_allseen_lsf_StatePulseEffect.cpp \
					org_allseen_lsf_StateTransitionEffect.cpp \
					XControllerServiceManager.cpp \
					XControllerServiceManagerCallback.cpp \
					XCppDelegator.cpp \
					XJavaDelegator.cpp \
					XLampMemberList.cpp \
					XLongArray.cpp \
					XObject.cpp \
					XMasterScene.cpp \
					XMasterSceneManager.cpp \
					XMasterSceneManagerCallback.cpp \
					XPresetManager.cpp \
					XPresetManagerCallback.cpp \
					XPresetPulseEffect.cpp \
					XPresetTransitionEffect.cpp \
					XPulseEffect.cpp \
					XScene.cpp \
					XSceneManager.cpp \
					XSceneManagerCallback.cpp \
					XStatePulseEffect.cpp \
					XStateTransitionEffect.cpp \
					XTransitionEffect.cpp

include $(BUILD_SHARED_LIBRARY)
