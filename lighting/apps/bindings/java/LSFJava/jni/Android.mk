# Copyright (c) 2014-2015, AllSeen Alliance. All rights reserved.
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
MY_ALLJOYN_OBJ         := obj/local/armeabi/objs-debug/alljoyn
#$(info ALLJOYN_HOME   = $(MY_ALLJOYN_HOME))
#$(info ALLJOYN_INC    = $(MY_ALLJOYN_INC))
#$(info ALLJOYN_LIB    = $(MY_ALLJOYN_LIB))

MY_CONFIG_HOME         := $(shell $(LOCAL_PATH)/../project_var CONFIG_CPP_HOME $(ECLIPSE_WORKSPACE_PATH))
ifeq ($(strip $(MY_CONFIG_HOME)),)
MY_CONFIG_HOME         := $(shell $(LOCAL_PATH)/../project_var CONFIG_HOME $(ECLIPSE_WORKSPACE_PATH))
endif
MY_CONFIG_INC          := $(MY_CONFIG_HOME)/config/inc
MY_CONFIG_LIB          := $(MY_CONFIG_HOME)/config/lib
#$(info CONFIG_INC       = $(MY_CONFIG_INC))

MY_NOTIFICATION_HOME   := $(shell $(LOCAL_PATH)/../project_var NOTIFICATION_CPP_HOME $(ECLIPSE_WORKSPACE_PATH))
ifeq ($(strip $(MY_NOTIFICATION_HOME)),)
MY_NOTIFICATION_HOME   := $(shell $(LOCAL_PATH)/../project_var NOTIFICATION_HOME $(ECLIPSE_WORKSPACE_PATH))
endif
MY_NOTIFICATION_INC    := $(MY_NOTIFICATION_HOME)/notification/inc
MY_NOTIFICATION_LIB    := $(MY_NOTIFICATION_HOME)/notification/lib
#$(info NOTIFICATION_INC = $(MY_NOTIFICATION_INC))

MY_SERVICES_COMMON_HOME := $(MY_CONFIG_HOME)
MY_SERVICES_COMMON_INC  := $(MY_SERVICES_COMMON_HOME)/services_common/inc
MY_SERVICES_COMMON_LIB  := $(MY_SERVICES_COMMON_HOME)/services_common/lib
#$(info SERVICES_COMMON_INC = $(MY_SERVICES_COMMON_INC))

MY_ABOUT_HOME          := $(MY_CONFIG_HOME)
MY_ABOUT_INC           := $(MY_ABOUT_HOME)/cpp/inc
MY_ABOUT_LIB           := $(MY_ABOUT_HOME)/cpp/lib
#$(info ABOUT_HOME   = $(MY_ABOUT_HOME))
#$(info ABOUT_INC    = $(MY_ABOUT_INC))
#$(info ABOUT_LIB    = $(MY_ABOUT_LIB))

MY_LSF_HOME            := $(shell $(LOCAL_PATH)/../project_var LSF_HOME $(ECLIPSE_WORKSPACE_PATH))
MY_LSF_COMMON_HOME     := $(MY_LSF_HOME)/common
MY_LSF_COMMON_INC      := $(MY_LSF_COMMON_HOME)/inc
MY_LSF_STD_COMMON_HOME := $(MY_LSF_HOME)/standard_core_library/common
MY_LSF_STD_COMMON_INC  := $(MY_LSF_STD_COMMON_HOME)/inc
MY_LSF_STD_COMMON_SRC  := $(MY_LSF_STD_COMMON_HOME)/src
MY_LSF_STD_CLIENT_HOME := $(MY_LSF_HOME)/standard_core_library/lighting_controller_client
MY_LSF_STD_CLIENT_INC  := $(MY_LSF_STD_CLIENT_HOME)/inc
MY_LSF_STD_CLIENT_SRC  := $(MY_LSF_STD_CLIENT_HOME)/src
MY_LSF_STD_SERVICE_HOME := $(MY_LSF_HOME)/standard_core_library/lighting_controller_service
MY_LSF_STD_SERVICE_INC  := $(MY_LSF_STD_SERVICE_HOME)/inc
MY_LSF_STD_SERVICE_SRC  := $(MY_LSF_STD_SERVICE_HOME)/src
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


# -----------------------------------------------------------------------------
include $(CLEAR_VARS)

LOCAL_MODULE            := alljoyn_config
LOCAL_SRC_FILES         := $(MY_CONFIG_LIB)/liballjoyn_config.a

include $(PREBUILT_STATIC_LIBRARY)


# -----------------------------------------------------------------------------
include $(CLEAR_VARS)

LOCAL_MODULE            := alljoyn_notification
LOCAL_SRC_FILES         := $(MY_NOTIFICATION_LIB)/liballjoyn_notification.a

include $(PREBUILT_STATIC_LIBRARY)


# -----------------------------------------------------------------------------
include $(CLEAR_VARS)

LOCAL_MODULE            := alljoyn_services_common
LOCAL_SRC_FILES         := $(MY_SERVICES_COMMON_LIB)/liballjoyn_services_common.a

include $(PREBUILT_STATIC_LIBRARY)


# -----------------------------------------------------------------------------
$(shell mkdir -p $(MY_ALLJOYN_OBJ))

# For the controller client
$(shell ar x $(MY_ABOUT_LIB)/liballjoyn.a AboutObjectDescription.o)
$(shell ar x $(MY_ABOUT_LIB)/liballjoyn.a AboutData.o)
$(shell mv AboutObjectDescription.o $(MY_ALLJOYN_OBJ))
$(shell mv AboutData.o $(MY_ALLJOYN_OBJ))
MY_CLIENT_C_INCLUDES  := $(MY_LSF_STD_CLIENT_INC)
MY_CLIENT_LDLIBS      := $(MY_ALLJOYN_OBJ)/AboutObjectDescription.o \
                         $(MY_ALLJOYN_OBJ)/AboutData.o
MY_CLIENT_SRC_FILES   := $(MY_LSF_STD_CLIENT_SRC)/ControllerClient.cc \
                         $(MY_LSF_STD_CLIENT_SRC)/ControllerClientDefs.cc \
                         $(MY_LSF_STD_CLIENT_SRC)/ControllerServiceManager.cc \
                         $(MY_LSF_STD_CLIENT_SRC)/LampGroupManager.cc \
                         $(MY_LSF_STD_CLIENT_SRC)/LampManager.cc \
                         $(MY_LSF_STD_CLIENT_SRC)/Manager.cc \
                         $(MY_LSF_STD_CLIENT_SRC)/MasterSceneManager.cc \
                         $(MY_LSF_STD_CLIENT_SRC)/PresetManager.cc \
                         $(MY_LSF_STD_CLIENT_SRC)/SceneManager.cc \
                         $(MY_LSF_STD_CLIENT_SRC)/TransitionEffectManager.cc \
                         $(MY_LSF_STD_CLIENT_SRC)/PulseEffectManager.cc \
                         $(MY_LSF_STD_CLIENT_SRC)/SceneElementManager.cc \
                         $(MY_LSF_STD_COMMON_SRC)/LSFKeyListener.cc \
                         $(MY_LSF_STD_COMMON_SRC)/LSFResponseCodes.cc \
                         $(MY_LSF_STD_COMMON_SRC)/LSFSemaphore.cc \
                         $(MY_LSF_STD_COMMON_SRC)/LSFTypes.cc \
                         $(MY_LSF_STD_COMMON_SRC)/Mutex.cc \
                         $(MY_LSF_STD_COMMON_SRC)/Rank.cc \
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
                         org_allseen_lsf_LampGroup.cpp \
                         org_allseen_lsf_LampGroupManager.cpp \
                         org_allseen_lsf_LampGroupManagerCallback.cpp \
                         org_allseen_lsf_LampManager.cpp \
                         org_allseen_lsf_LampManagerCallback.cpp \
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
                         org_allseen_lsf_TransitionEffectV2.cpp \
                         org_allseen_lsf_TransitionEffectManager.cpp \
                         org_allseen_lsf_TransitionEffectManagerCallback.cpp \
                         org_allseen_lsf_PulseEffectV2.cpp \
                         org_allseen_lsf_PulseEffectManager.cpp \
                         org_allseen_lsf_PulseEffectManagerCallback.cpp \
                         org_allseen_lsf_SceneElement.cpp \
                         org_allseen_lsf_SceneElementManager.cpp \
                         org_allseen_lsf_SceneElementManagerCallback.cpp \
                         org_allseen_lsf_SceneWithSceneElements.cpp \
                         org_allseen_lsf_sdk_LampDetails.cpp \
                         org_allseen_lsf_sdk_LampParameters.cpp \
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
                         XPulseEffectV2.cpp \
                         XPulseEffectManager.cpp \
                         XPulseEffectManagerCallback.cpp \
                         XSceneElement.cpp \
                         XSceneElementManager.cpp \
                         XSceneElementManagerCallback.cpp \
                         XSceneWithSceneElements.cpp \
                         XScene.cpp \
                         XSceneManager.cpp \
                         XSceneManagerCallback.cpp \
                         XStatePulseEffect.cpp \
                         XStateTransitionEffect.cpp \
                         XTrackingID.cpp \
                         XTransitionEffect.cpp \
                         XTransitionEffectV2.cpp \
                         XTransitionEffectManager.cpp \
                         XTransitionEffectManagerCallback.cpp

# For the controller service
$(shell ar x $(MY_ABOUT_LIB)/liballjoyn.a AboutIcon.o AboutIconObj.o AboutProxy.o)
$(shell mv AboutIcon.o AboutIconObj.o AboutProxy.o $(MY_ALLJOYN_OBJ))
MY_SERVICE_C_INCLUDES := $(MY_LSF_STD_SERVICE_INC) \
                         $(MY_ABOUT_INC) \
                         $(MY_CONFIG_INC) \
                         $(MY_NOTIFICATION_INC) \
                         $(MY_SERVICES_COMMON_INC)
MY_SERVICE_LDLIBS     := $(MY_ALLJOYN_OBJ)/AboutIcon.o \
                         $(MY_ALLJOYN_OBJ)/AboutIconObj.o \
                         $(MY_ALLJOYN_OBJ)/AboutProxy.o
MY_SERVICE_SRC_FILES  := $(MY_LSF_STD_SERVICE_SRC)/ControllerService.cc \
                         $(MY_LSF_STD_SERVICE_SRC)/ControllerServiceRank.cc \
                         $(MY_LSF_STD_SERVICE_SRC)/DeviceIcon.cc \
                         $(MY_LSF_STD_SERVICE_SRC)/FileParser.cc \
                         $(MY_LSF_STD_SERVICE_SRC)/LSFAboutDataStore.cc \
                         $(MY_LSF_STD_SERVICE_SRC)/LampClients.cc \
                         $(MY_LSF_STD_SERVICE_SRC)/LampGroupManager.cc \
                         $(MY_LSF_STD_SERVICE_SRC)/LampManager.cc \
                         $(MY_LSF_STD_SERVICE_SRC)/LeaderElectionObject.cc \
                         $(MY_LSF_STD_SERVICE_SRC)/Main.cc \
                         $(MY_LSF_STD_SERVICE_SRC)/Manager.cc \
                         $(MY_LSF_STD_SERVICE_SRC)/MasterSceneManager.cc \
                         $(MY_LSF_STD_SERVICE_SRC)/PersistenceThread.cc \
                         $(MY_LSF_STD_SERVICE_SRC)/PresetManager.cc \
                         $(MY_LSF_STD_SERVICE_SRC)/PulseEffectManager.cc \
                         $(MY_LSF_STD_SERVICE_SRC)/SceneElementManager.cc \
                         $(MY_LSF_STD_SERVICE_SRC)/SceneManager.cc \
                         $(MY_LSF_STD_SERVICE_SRC)/ServiceDescription.cc \
                         $(MY_LSF_STD_SERVICE_SRC)/TransitionEffectManager.cc \
                         $(MY_LSF_STD_COMMON_SRC)/AJInitializer.cc \
                         $(MY_LSF_STD_COMMON_SRC)/Alarm.cc \
                         org_allseen_lsf_sdk_AboutData.cpp \
                         org_allseen_lsf_ControllerService.cpp \
                         XControllerService.cpp \
                         XControllerServiceManagerInit.cpp \
                         XOEMCSConfig.cpp


# ----------------------------------------------------------------------------
include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(MY_LSF_COMMON_INC) \
                    $(MY_LSF_STD_COMMON_INC) \
                    $(MY_ALLJOYN_INC) \
                    $(MY_ALLJOYN_INC)/alljoyn \
                    $(MY_CLIENT_C_INCLUDES) \
                    $(MY_SERVICE_C_INCLUDES)
                    
LOCAL_SHARED_LIBRARIES := alljoyn_java
LOCAL_STATIC_LIBRARIES := alljoyn_config alljoyn_notification alljoyn_about alljoyn_services_common

LOCAL_CFLAGS     := -DQCC_OS_GROUP_POSIX -DQCC_OS_ANDROID -DQCC_CPU_ARM -DLSF_BINDINGS -fpic
LOCAL_LDLIBS     := $(MY_CLIENT_LDLIBS) $(MY_SERVICE_LDLIBS) -llog

LOCAL_MODULE     := alljoyn_lsf_java
LOCAL_SRC_FILES  := $(MY_CLIENT_SRC_FILES) $(MY_SERVICE_SRC_FILES)

include $(BUILD_SHARED_LIBRARY)
