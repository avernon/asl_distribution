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

PKG_NAME:=ajtcl
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

define Package/ajtcl/Default
  SECTION:=net
  CATEGORY:=Network
  DEPENDS:=+libpthread +librt
  URL:=http://www.allseenalliance.org
  MAINTAINER:=AllSeen Alliance <allseen-core@lists.allseenalliance.org>
  TITLE:=AllJoyn Thin Client Library
endef

define Package/ajtcl
$(call Package/ajtcl/Default)
endef

define Package/ajtcl/description
AllJoyn Thin Client Library is a basic, low-level C library for developing
ad hoc peer-to-peer applications that use the AllJoyn protocol.  This version
uses built-in cryptographic hash functions.
endef

define Package/ajtcl-samples
$(call Package/ajtcl/Default)
  TITLE+= - samples
  DEPENDS:=ajtcl
endef

define Package/ajtcl-samples/description
Alljoyn Thin Client Library samples.  (This is primarily for testing.  Do not
include in production builds.)
endef

define Package/ajtcl-tests
$(call Package/ajtcl/Default)
  TITLE+= - tests
  DEPENDS:=ajtcl
endef

define Package/ajtcl-tests/description
Alljoyn Thin Client Library tests.  (This is primarily for testing.  Do not
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

define Build/Compile
	CROSS_CFLAGS="$(TARGET_CFLAGS) $(EXTRA_CFLAGS) $(TARGET_CPPFLAGS)" \
	CROSS_LINKFLAGS="$(TARGET_LINKFLAGS) $(TARGET_LDFLAGS)" \
	CROSS_PATH=$(TARGET_PATH) \
	CROSS_PREFIX=$(TARGET_CC:gcc=) \
	scons -C $(PKG_BUILD_DIR) \
		$(PKG_JOBS) \
		WS=off \
		TARG=linux \
		"VARIANT=$(ALLJOYN_BUILD_VARIANT)" \
		"AJ_CRYPTO=builtin"
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) -R $(PKG_BUILD_DIR)/dist/include/ajtcl $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/dist/lib/libajtcl.* $(1)/usr/lib/
endef

define Package/ajtcl/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/dist/lib/libajtcl.so $(1)/usr/lib/
endef

define Package/ajtcl-openssl/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/dist/lib/libajtcl.so $(1)/usr/lib/
endef

define Package/ajtcl-samples/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dist/bin/* $(1)/usr/bin/
endef

define Package/ajtcl-tests/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dist/test/* $(1)/usr/bin/
endef

$(eval $(call BuildPackage,ajtcl))
$(eval $(call BuildPackage,ajtcl-samples))
$(eval $(call BuildPackage,ajtcl-tests))
