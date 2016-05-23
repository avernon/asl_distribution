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

PKG_NAME:=ajtcl-services
PKG_VERSION:=15.09.00dev
PKG_RELEASE:=1
PKG_MD5SUM:=
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)-src
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-src.tar.gz
PKG_SOURCE_URL:=https://build.allseenalliance.org/ci/job/master-source-extraction/lastSuccessfulBuild/artifact/depot/


# SCons supports parallel builds but does not support make's jobserver
PKG_BUILD_PARALLEL:=$(if $(CONFIG_PKG_BUILD_USE_JOBSERVER),0,1)

PKG_CONFIG_DEPENDS:= \
	CONFIG_DEBUG

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)/Default
  SECTION:=net
  CATEGORY:=Network
  DEPENDS:=ajtcl
  URL:=http://www.allseenalliance.org
  MAINTAINER:=AllSeen Alliance <allseen-core@lists.allseenalliance.org>
endef

define Package/$(PKG_NAME)
$(call Package/$(PKG_NAME)/Default)
  TITLE:=AllJoyn Thin Client - Base Services
endef

define Package/$(PKG_NAME)/description
AllJoyn Thin Client Base Services is the standard AllJoyn services libraries for
the AllJoyn Thin Client C library for developing ad hoc peer-to-peer
applications that use the AllJoyn protocol.
endef

define Package/$(PKG_NAME)-samples
$(call Package/$(PKG_NAME)/Default)
  TITLE:=AllJoyn Thin Client - Base Services - samples
  DEPENDS:=$(PKG_NAME)
endef

define Package/$(PKG_NAME)-samples/description
Alljoyn Thin Client Base Services samples.  (This is primarily for testing.  Do not
include in production builds.)
endef

ifeq ($(CONFIG_DEBUG),y)
  ALLJOYN_BUILD_VARIANT:=debug
else
  ALLJOYN_BUILD_VARIANT:=release
endif

define Build/Configure/Default
# Override default to do nothing
endef

TARGET_CFLAGS+=-I$(STAGING_DIR)/usr/include/ajtcl

define Build/Compile
	CROSS_CFLAGS="$(TARGET_CFLAGS) $(EXTRA_CFLAGS) $(TARGET_CPPFLAGS)" \
	CROSS_LINKFLAGS="$(TARGET_LINKFLAGS) $(TARGET_LDFLAGS)" \
	CROSS_PATH=$(TARGET_PATH) \
	CROSS_PREFIX=$(TARGET_CC:gcc=) \
	scons -C $(PKG_BUILD_DIR) \
		$(PKG_JOBS) \
		WS=off \
		TARG=linux \
		"VARIANT=$(ALLJOYN_BUILD_VARIANT)"
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) -R $(PKG_BUILD_DIR)/dist/include/ajtcl $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/dist/lib/libajtcl_services.* $(1)/usr/lib/
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/dist/lib/libajtcl_services.so $(1)/usr/lib/
endef

define Package/$(PKG_NAME)-samples/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(CP) $(PKG_BUILD_DIR)/dist/bin/* $(1)/usr/bin/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
$(eval $(call BuildPackage,$(PKG_NAME)-samples))
