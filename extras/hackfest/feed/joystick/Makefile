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

PKG_NAME:=joystick
PKG_RELEASE:=1

HF_PKG_SOURCE_DIR:=../../linino/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  TITLE:=Joystick library
  SECTION:=opt
  CATEGORY:=AJ-Tutorial
  DEPENDS:=+libstdcpp +smsg
endef

define Package/$(PKG_NAME)/description
Joystick shield communication abstraction for Arduino Yun.
endef


define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(TAR) c -C $(HF_PKG_SOURCE_DIR) . \
		--exclude=jstest \
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
	scons -C $(PKG_BUILD_DIR)
endef


define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(INSTALL_DIR) $(1)/usr/include/aj_tutorial
	$(CP) $(PKG_BUILD_DIR)/inc/aj_tutorial/*.h $(1)/usr/include/aj_tutorial
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/libjoystick.so $(1)/usr/lib/

endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libjoystick.so $(1)/usr/lib
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/test/jstest $(1)/usr/bin
endef

$(eval $(call BuildPackage,$(PKG_NAME)))

