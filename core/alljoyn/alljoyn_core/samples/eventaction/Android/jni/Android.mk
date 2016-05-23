# Contributed by Qualcomm Connected Experiences, Inc.,
# with authorization from the AllSeen Alliance, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Pursuant to Section 1 of the License, the work of authorship constituting
# a Work and any Contribution incorporated in the Work shall mean only that
# Contributor's code submissions authored by that Contributor.  Any rights
# granted under the License are conditioned upon acceptance of these
# clarifications.
LOCAL_PATH := $(call my-dir)

# AllJoyn specifics
ALLJOYN_DIST := ../../../..

include $(CLEAR_VARS)
LOCAL_MODULE := ajrouter
LOCAL_SRC_FILES := $(ALLJOYN_DIST)/lib/libajrouter.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := alljoyn
LOCAL_SRC_FILES := $(ALLJOYN_DIST)/lib/liballjoyn.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := alljoyn_about
LOCAL_SRC_FILES := $(ALLJOYN_DIST)/lib/liballjoyn_about.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := MyAllJoynCode

TARGET_PLATFORM := android-16

LOCAL_C_INCLUDES := \
	$(ALLJOYN_DIST)/cpp/inc \
	$(ALLJOYN_DIST)/cpp/inc/alljoyn \
	$(ALLJOYN_DIST)/about/inc

LOCAL_CFLAGS := -std=c++11 -Wno-psabi -Wno-write-strings -DANDROID_NDK -DTARGET_ANDROID -DLINUX -DQCC_OS_GROUP_POSIX -DQCC_OS_ANDROID -DANDROID

LOCAL_CPP_EXTENSION := .cc 

LOCAL_SRC_FILES := \
	event/AndroidJNIBridge.cc \
	event/PresenceDetection.cc \
	event/MyEventCode.cc

LOCAL_STATIC_LIBRARIES := \
	ajrouter \
	alljoyn \
	alljoyn_about

LOCAL_LDLIBS := \
	-llog \
	$(ALLJOYN_OPENSSL_LIBS)

LOCAL_ARM_MODE := arm

include $(BUILD_SHARED_LIBRARY)
