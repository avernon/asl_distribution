/*
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Contributed by Qualcomm Connected Experiences, Inc.,
 *    with authorization from the AllSeen Alliance, Inc.
 *    
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *    
 *        http://www.apache.org/licenses/LICENSE-2.0
 *    
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *    
 *    Pursuant to Section 1 of the License, the work of authorship constituting
 *    a Work and any Contribution incorporated in the Work shall mean only that
 *    Contributor's code submissions authored by that Contributor.  Any rights
 *    granted under the License are conditioned upon acceptance of these
 *    clarifications.
 */
#include "FeaturePermissions.h"

#include "PluginData.h"
#include <qcc/Debug.h>

#define QCC_MODULE "ALLJOYN_JS"

std::map<std::string, int32_t> PluginData::permissionLevels;

QStatus PluginData::PermissionLevel(Plugin& plugin, const qcc::String& feature, int32_t& level)
{
    QCC_DbgTrace(("%s(feature=%s)", __FUNCTION__, feature.c_str()));

    QStatus status = ER_OK;
    qcc::String origin;
    std::map<std::string, int32_t>::iterator it;

    level = DEFAULT_DENIED;

    if (feature != ALLJOYN_FEATURE) {
        status = ER_FAIL;
        QCC_LogError(status, ("feature '%s' not supported", feature.c_str()));
        goto exit;
    }

    status = plugin->Origin(origin);
    if (ER_OK != status) {
        goto exit;
    }
    lock.Lock();
    it = permissionLevels.find(origin);
    if (it != permissionLevels.end()) {
        level = it->second;
        QCC_DbgTrace(("Using session level %d", level));
    } else {
        status = PersistentPermissionLevel(plugin, origin, level);
        if (ER_OK == status) {
            QCC_DbgTrace(("Using persistent level %d", level));
            permissionLevels[origin] = level;
        }
    }
    lock.Unlock();

exit:
    return status;
}

QStatus PluginData::SetPermissionLevel(Plugin& plugin, const qcc::String& feature, int32_t level, bool remember)
{
    QCC_DbgTrace(("SetPermissionLevel(feature=%s,level=%d,remember=%d)", feature.c_str(), level, remember));

    QStatus status = ER_OK;
    qcc::String origin;
    qcc::String permission;

    if (feature != ALLJOYN_FEATURE) {
        status = ER_FAIL;
        QCC_LogError(status, ("feature '%s' not supported", feature.c_str()));
        goto exit;
    }

    status = plugin->Origin(origin);
    if (ER_OK != status) {
        goto exit;
    }
    lock.Lock();
    permissionLevels[origin] = level;
    if (remember) {
        status = SetPersistentPermissionLevel(plugin, origin, level);
    }
    lock.Unlock();

exit:
    return status;
}
