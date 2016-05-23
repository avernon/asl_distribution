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
include $(CLEAR_VARS)
LOCAL_MODULE    := aj-check
include $(BUILD_SHARED_LIBRARY)
$(info AJ> TOOLCHAIN_PREFIX = $(TOOLCHAIN_PREFIX))
$(info AJ> TOOLCHAIN_PREBUILT_ROOT = $(TOOLCHAIN_PREBUILT_ROOT))
$(info AJ> CFLAGS = $(TARGET_CFLAGS) $(TARGET_NO_EXECUTE_CFLAGS))
$(info AJ> CXXFLAGS = $(TARGET_CXXFLAGS) $(TARGET_NO_EXECUTE_CFLAGS))
$(info AJ> LDFLAGS = $(TARGET_LDFLAGS) $(TARGET_NO_EXECUTE_LDFLAGS) $(TARGET_NO_UNDEFINED_LDFLAGS))
$(info AJ> INCLUDES = $(TARGET_C_INCLUDES) $(__ndk_modules.$(APP_STL).EXPORT_C_INCLUDES))
$(info AJ> debug_FLAGS = $(TARGET_$(TARGET_ARCH)_debug_CFLAGS))
$(info AJ> release_FLAGS = $(TARGET_$(TARGET_ARCH)_release_CFLAGS))
$(info AJ> SYSROOT = $(NDK_PLATFORM_$(NDK_APP_PLATFORM)_$(TARGET_ARCH)_SYSROOT))

