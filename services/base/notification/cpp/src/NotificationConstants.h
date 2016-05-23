/******************************************************************************
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
 ******************************************************************************/

#ifndef NOTIFICATIONCONSTANTS_H_
#define NOTIFICATIONCONSTANTS_H_

#include <qcc/String.h>

#if defined(QCC_OS_GROUP_WINDOWS)
/* Disabling warning C 4706. Assignment within conditional expression */
#pragma warning(push)
#pragma warning(disable: 4706)
#endif


/*
 * Common Macros
 */

#define CHECK(x) if ((status = x))  { break; }

namespace ajn {
namespace services {
namespace nsConsts {

static const qcc::String BUS_NAME = "NotificationService";

static const uint16_t TTL_MIN = 30;
static const uint16_t TTL_MAX = 43200;

static const uint16_t UUID_LENGTH = 16;
static const int16_t ANNOUNCMENT_PORT_NUMBER = 900;

static const uint16_t NOTIFICATION_DISMISSER_VERSION = 1;
static const uint16_t NOTIFICATION_PRODUCER_VERSION = 1;

static const qcc::String AJPARAM_BOOL = "b";
static const qcc::String AJPARAM_UINT16 = "q";
static const qcc::String AJPARAM_STR = "s";
static const qcc::String AJPARAM_INT = "i";
static const qcc::String AJPARAM_ARR_BYTE = "ay";
static const qcc::String AJPARAM_DICT_INT_VAR = "{iv}";
static const qcc::String AJPARAM_DICT_INT_UINT16 = "{iq}";
static const qcc::String AJPARAM_DICT_INT_STR = "{is}";
static const qcc::String AJPARAM_DICT_STR_STR = "{ss}";
static const qcc::String AJPARAM_DICT_STR_VAR = "{sv}";
static const qcc::String AJPARAM_ARR_DICT_INT_VAR = "a{iv}";
static const qcc::String AJPARAM_ARR_DICT_STR_VAR = "a{sv}";
static const qcc::String AJPARAM_ARR_DICT_STR_STR = "a{ss}";
static const qcc::String AJPARAM_STRUCT_STR_STR = "(ss)";
static const qcc::String AJPARAM_ARR_STRUCT_STR_STR = "a(ss)";
static const qcc::String AJPARAM_ARR_STRUCT_STR_ARR_STR = "a(sas)";
static const qcc::String AJPARAM_STRUCT_STR_ARR_STR = "(sas)";

static const int32_t AJ_NOTIFY_NUM_PARAMS = 10;
static const int32_t AJ_NUM_METADATA_DEFLT_PARAMS = 0;
static const int32_t RICH_CONTENT_ICON_URL_ATTRIBUTE_KEY = 0;
static const int32_t RICH_CONTENT_AUDIO_URL_ATTRIBUTE_KEY = 1;
static const int32_t RICH_CONTENT_ICON_OBJECT_PATH_ATTRIBUTE_KEY = 2;
static const int32_t RICH_CONTENT_AUDIO_OBJECT_PATH_ATTRIBUTE_KEY = 3;
static const int32_t CPS_OBJECT_PATH_ATTRIBUTE_KEY = 4;
static const int32_t ORIGINAL_SENDER_ATTRIBUTE_KEY = 5;

static const qcc::String AJ_NOTIFICATION_INTERFACE_NAME = "org.alljoyn.Notification";
static const uint16_t AJ_NOTIFICATION_PRODUCER_SERVICE_PORT = 1010;
static const qcc::String AJ_PROPERTY_VERSION = "Version";
static const qcc::String AJ_SIGNAL_METHOD = "notify";
static const qcc::String AJ_CONSUMER_SERVICE_PATH = "/receiver";
static const qcc::String AJ_PRODUCER_SERVICE_PATH_PREFIX = "/";
static const qcc::String AJ_NOTIFY_PARAMS = AJPARAM_UINT16 + AJPARAM_INT + AJPARAM_UINT16 + AJPARAM_STR + AJPARAM_STR + AJPARAM_ARR_BYTE + AJPARAM_STR +
                                            AJPARAM_ARR_DICT_INT_VAR + AJPARAM_ARR_DICT_STR_STR + AJPARAM_ARR_STRUCT_STR_STR;
static const qcc::String AJ_NOTIFY_PARAM_NAMES = "version, notificationId, messageType, deviceId, deviceName, appId, appName, attributes, customAttributes, notificationText";
static const qcc::String AJ_SESSIONLESS_MATCH = "sessionless='t'";

static const qcc::String AJ_NOTIFICATION_PRODUCER_INTERFACE = "org.alljoyn.Notification.Producer";
static const qcc::String AJ_NOTIFICATION_PRODUCER_PATH = "/notificationProducer";
static const qcc::String AJ_DISMISS_METHOD_NAME = "Dismiss";
static const qcc::String AJ_DISMISS_METHOD_PARAMS = "i";
static const qcc::String AJ_DISMISS_METHOD_PARAMS_NAMES = "msgId";

static const qcc::String AJ_NOTIFICATION_DISMISSER_INTERFACE = "org.alljoyn.Notification.Dismisser";
static const qcc::String AJ_DISMISS_SIGNAL_NAME = "Dismiss";
static const qcc::String AJ_DISMISS_SIGNAL_PARAMS = AJPARAM_INT + AJPARAM_ARR_BYTE;
static const qcc::String AJ_DISMISS_PARAM_NAMES = "msgId, appId";
static const int32_t AJ_DISMISSER_NUM_PARAMS = 2;
static const qcc::String AJ_NOTIFICATION_DISMISSER_PATH = "/notificationDismisser";

}         //namespace nsConsts
}     //namespace services
} //namespace ajn


#endif /* NOTIFICATIONCONSTANTS_H_ */

