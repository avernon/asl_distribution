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
AJ_SERVICE:=lighting
AJ_SERVICE_NAME:=Lighting

include $(TOPDIR)/rules.mk

PKG_NAME:=alljoyn-$(AJ_SERVICE)
PKG_VERSION:=0.0.1
PKG_RELEASE:=1
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)-src
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-src.tar.gz
PKG_SOURCE_URL:=https://allseenalliance.org/releases/alljoyn/$(PKG_VERSION)/
PKG_MD5SUM:=

# SCons supports parallel builds but does not support make's jobserver
PKG_BUILD_PARALLEL:=$(if $(CONFIG_PKG_BUILD_USE_JOBSERVER),0,1)

include $(INCLUDE_DIR)/package.mk

ifneq ($(CONFIG_CCACHE),)
	TARGET_CC=$(TARGET_CC_NOCACHE)
	TARGET_CXX=$(TARGET_CXX_NOCACHE)
endif

ALLJOYN_BINDINGS:=cpp,

define Package/$(PKG_NAME)
	TITLE:=AllJoyn $(AJ_SERVICE_NAME)
	SECTION:=net
	CATEGORY:=Network
	DEPENDS:=alljoyn \
		+alljoyn-about \
		+alljoyn-config \
		+alljoyn-onboarding \
		+alljoyn-services_common \
		+alljoyn-notification \
		+libstdcpp \
		+libpthread \
		+librt
	URL:=http://www.allseenalliance.org
	MAINTAINER:=AllSeen Alliance <allseen-core@lists.allseenalliance.org>
	MENU:=1
endef

define Package/$(PKG_NAME)/description
AllJoyn $(AJ_SERVICE_NAME)
endef

define Build/Configure/Default
# Override default to do nothing
endef

define Build/Compile
	scons -C $(PKG_BUILD_DIR)/core/service_framework \
		WS=off \
		V=1 \
		CPU=openwrt \
		OS=openwrt \
		BR=off \
		ICE=off \
		"BINDINGS=$$(ALLJOYN_BINDINGS)" \
		"TARGET_CC=$$(TARGET_CC)" \
		"TARGET_CXX=$$(TARGET_CXX)" \
		"TARGET_CFLAGS=$$(TARGET_CFLAGS)" \
		"TARGET_CPPFLAGS=$$(TARGET_CPPFLAGS)" \
		"TARGET_PATH=$$(TARGET_PATH)" \
		"TARGET_LINKFLAGS=$$(TARGET_LDFLAGS)" \
		"TARGET_LINK=$$(TARGET_CC)" \
		"TARGET_AR=$$(TARGET_AR)" \
		"TARGET_RANLIB=$$(TARGET_RANLIB)" \
		"STAGING_DIR=$$(STAGING_DIR)"
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/core/service_framework/build/linux/standard_core_library/lighting_controller_service/bin/lighting_controller_service $(1)/usr/bin
endef

$(eval $(call BuildPackage,$(PKG_NAME)))

