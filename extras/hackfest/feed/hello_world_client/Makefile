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
include $(TOPDIR)/rules.mk

PKG_NAME:=hello_world_client
PKG_RELEASE:=1
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

HF_PKG_SOURCE_DIR:=../../aj_samples/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  TITLE:=AllJoyn Hello World Client Example
  SECTION:=opt
  CATEGORY:=AJ-Tutorial
  DEPENDS:=+libstdcpp +smsg +alljoyn +alljoyn-about
endef

define Package/$(PKG_NAME)/description
AllJoyn Hello World Client Example. Looks for and connects to an AllJoyn Hello World Service Example.
endef


define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(TAR) c -C $(HF_PKG_SOURCE_DIR) . \
		--exclude='.git*' \
		--exclude='*.os' \
		--exclude='*.o' \
		--exclude='*.so' \
	| tar x -C $(PKG_BUILD_DIR)/
endef

define Build/Configure
endef


define Build/Compile
	TARGET_PATH="$(PATH)" \
	scons -C $(PKG_BUILD_DIR) $(MAKE_FLAGS)
endef


define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/build/$(PKG_NAME) $(1)/usr/bin
endef

$(eval $(call BuildPackage,$(PKG_NAME)))

