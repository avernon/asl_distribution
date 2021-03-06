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
#include "BusAttachmentInterface.h"

#include "BusAttachmentHost.h"
#include "CallbackNative.h"
#include "FeaturePermissions.h"
#include "HostObject.h"
#include "TypeMapping.h"
#include <qcc/Debug.h>

#define QCC_MODULE "ALLJOYN_JS"

std::map<qcc::String, int32_t> _BusAttachmentInterface::constants;

std::map<qcc::String, int32_t>& _BusAttachmentInterface::Constants()
{
    if (constants.empty()) {
        CONSTANT("DBUS_NAME_FLAG_ALLOW_REPLACEMENT", 0x01);
        CONSTANT("DBUS_NAME_FLAG_REPLACE_EXISTING",  0x02);
        CONSTANT("DBUS_NAME_FLAG_DO_NOT_QUEUE",      0x04);

        CONSTANT("SESSION_PORT_ANY", 0);
    }
    return constants;
}

_BusAttachmentInterface::_BusAttachmentInterface(Plugin& plugin) :
    ScriptableObject(plugin, Constants())
{
    QCC_DbgTrace(("%s", __FUNCTION__));
}

_BusAttachmentInterface::~_BusAttachmentInterface()
{
    QCC_DbgTrace(("%s", __FUNCTION__));
}

bool _BusAttachmentInterface::Construct(const NPVariant* args, uint32_t argCount, NPVariant* result)
{
    QCC_UNUSED(args);
    QCC_UNUSED(argCount);
    QCC_DbgTrace(("%s", __FUNCTION__));

    QStatus status = ER_OK;
    bool typeError = false;
    int32_t level = 0;

    /*
     * Check permission level first.
     */
    status = PluginData::PermissionLevel(plugin, ALLJOYN_FEATURE, level);
    if (ER_OK != status) {
        status = ER_OK;
        level = 0;
    }
    if (level <= 0) {
        typeError = true;
        plugin->RaiseTypeError("permission denied");
        goto exit;
    }

    {
        BusAttachmentHost busAttachmentHost(plugin);
        ToHostObject<BusAttachmentHost>(plugin, busAttachmentHost, *result);
    }

exit:
    if ((ER_OK == status) && !typeError) {
        return true;
    } else {
        if (ER_OK != status) {
            plugin->RaiseBusError(status);
        }
        return false;
    }
}
