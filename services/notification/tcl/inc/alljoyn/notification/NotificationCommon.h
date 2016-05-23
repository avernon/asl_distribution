/******************************************************************************
 * Copyright (c) 2013 - 2014, AllSeen Alliance. All rights reserved.
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

#ifndef _NOTIFICATIONCOMMON_H_
#define _NOTIFICATIONCOMMON_H_

#include <alljoyn.h>

/** @defgroup NotificationCommon Notification Common
 * details Functions and variables that assist in writing Notification Producers
 *  @{
 */

/**
 * Definitions of notification attribute keys.
 */
#define AJNS_RICH_CONTENT_ICON_URL_ATTRIBUTE_KEY             0    /**< Content icon url */
#define AJNS_RICH_CONTENT_AUDIO_URL_ATTRIBUTE_KEY            1    /**< Content audio url */
#define AJNS_RICH_CONTENT_ICON_OBJECT_PATH_ATTRIBUTE_KEY     2    /**< Content icon object path */
#define AJNS_RICH_CONTENT_AUDIO_OBJECT_PATH_ATTRIBUTE_KEY    3    /**< Content audio object path */
#define AJNS_CONTROLPANELSERVICE_OBJECT_PATH_ATTRIBUTE_KEY   4    /**< Control panel service object path */
#define AJNS_ORIGINAL_SENDER_NAME_ATTRIBUTE_KEY              5    /**< Original sender name */

/**
 * Number of message types.
 */
#define AJNS_NUM_MESSAGE_TYPES 3                                  /**< Number of message types */

/**
 * Generic structure for key value pairs.
 */
typedef struct _AJNS_DictionaryEntry {
    const char* key;                           /**< key of dictionary */
    const char* value;                         /**< value of dictionary */
} AJNS_DictionaryEntry;

/*!
   \brief struct that holds the notification content
 */
typedef struct _AJNS_NotificationContent {
    int8_t numCustomAttributes;                 /**< numCustomAttributes number of custom Attributs */
    AJNS_DictionaryEntry* customAttributes;     /**< customAttributes Custom attributs */
    int8_t numTexts;                            /**< numTexts number of versions of the notification text */
    AJNS_DictionaryEntry* texts;                /**< texts The text of the notification, one entry per language */
    int8_t numAudioUrls;                        /**< numAudioUrls The number of audio URLs sent */
    AJNS_DictionaryEntry* richAudioUrls;        /**< richAudioUrls The audio URLs, one per language */
    const char* richIconUrl;                    /**< richIconUrl A URL for an icon to be displayed along with the notification */
    const char* richIconObjectPath;             /**< richIconObjectPath The AllJoyn object path of an accompanying icons object */
    const char* richAudioObjectPath;            /**< richAudioObjectPath The AllJoyn object path of an accompanying audio object */
    const char* controlPanelServiceObjectPath;  /**< controlPanelServiceObjectPath The AllJoyn object path of an accompanying Control Panel Service object */
    const char* originalSenderName;             /**< originalSenderName The AllJoyn bus unique name of the originating producer application */
} AJNS_NotificationContent;

/*!
   \brief struct that holds the notification (header fields + content)
 */
typedef struct _AJNS_Notification {
    uint16_t version;                           /**< version of notification */
    uint16_t messageType;                       /**< messageType One of \ref AJNS_NOTIFICATION_MESSAGE_TYPE_INFO, \ref AJNS_NOTIFICATION_MESSAGE_TYPE_WARNING, or \ref AJNS_NOTIFICATION_MESSAGE_TYPE_EMERGENCY */
    int32_t notificationId;                     /**< notification message id */
    const char* originalSenderName;             /**< originalSenderName The AllJoyn bus unique name of the originating producer application */
    const char* deviceId;                       /**< device id of originating producer application */
    const char* deviceName;                     /**< device name of originating producer application */
    const char* appId;                          /**< application id of originating producer application */
    const char* appName;                        /**< application name of originating producer application */
    AJNS_NotificationContent* content;          /**< content of notification */
} AJNS_Notification;

/**
 * Notification interface name
 */
extern const char AJNS_NotificationInterfaceName[];
/**
 * Notification interface signal
 */
extern const char AJNS_NotificationSignalName[];
/**
 * Notification interface property version
 */
extern const char AJNS_NotificationPropertyVersion[];
/**
 * Notification interface version property value
 */
extern const uint16_t AJNS_NotificationVersion;

/**
 * Notification interface name followed by the method signatures.
 *
 * See also ".\inc\aj_introspect.h"
 */
extern const char* AJNS_NotificationInterface[];

/**
 * A NULL terminated collection of all interfaces.
 */
extern const AJ_InterfaceDescription AJNS_NotificationInterfaces[];

/*!
   \brief Minimal time in seconds for the notification signal to live
 */
extern const uint16_t AJNS_NOTIFICATION_TTL_MIN;

/*!
   \brief Maximal time in seconds for the notification signal to live
 */
extern const uint16_t AJNS_NOTIFICATION_TTL_MAX;

/**
 * Notification Dismisser object for the Dismiss signal emitter
 */
/**
 * Notification Dismisser interface name followed by the method signatures.
 *
 * See also ".\inc\aj_introspect.h"
 */
extern const char* const AJNS_NotificationDismisserInterface[];
/**
 * Notification Dismisser interface version property value
 */
extern const uint16_t AJNS_NotificationDismisserVersion;
/**
 * Notification Dismisser interface signal emitter
 */
AJ_Status AJNS_SendDismissSignal(AJ_BusAttachment* busAttachment, int32_t msgId, const char* appId);
/**
 * A NULL terminated collection of all NotificationDismisser interfaces.
 */
extern const AJ_InterfaceDescription AJNS_NotificationDismisserInterfaces[];
/**
 * Notification Dismisser signal emitter object path
 */
extern char AJNS_NotificationDismisserObjectPath[];

/**
 * Number of notification common objects
 */
#define NUM_NOTIFICATION_COMMON_OBJECTS 1

/**
 * Notification common app objects
 */
#define NOTIFICATION_COMMON_APPOBJECTS \
    { AJNS_NotificationDismisserObjectPath,   AJNS_NotificationDismisserInterfaces, AJ_OBJ_FLAG_ANNOUNCED },

/**
 * Notification dismisser object index
 */
#define NOTIFICATION_DISMISSER_OBJECT_INDEX 0 + NUM_PRE_NOTIFICATION_COMMON_OBJECTS
/**
 * Notification dismisser get property
 */
#define NOTIFICATION_DISMISSER_GET_PROPERTY             AJ_APP_PROPERTY_ID(NOTIFICATION_DISMISSER_OBJECT_INDEX, 0, AJ_PROP_GET)
/**
 * Notification dismisser set property
 */
#define NOTIFICATION_DISMISSER_SET_PROPERTY             AJ_APP_PROPERTY_ID(NOTIFICATION_DISMISSER_OBJECT_INDEX, 0, AJ_PROP_SET)
/**
 * Notification dismisser emitter
 */
#define NOTIFICATION_DISMISSER_DISMISS_EMITTER          AJ_APP_MESSAGE_ID(NOTIFICATION_DISMISSER_OBJECT_INDEX, 1, 0)
/**
 * Notification dismisser version property
 */
#define GET_NOTIFICATION_DISMISSER_VERSION_PROPERTY     AJ_APP_PROPERTY_ID(NOTIFICATION_DISMISSER_OBJECT_INDEX, 1, 1)

/**
 * Notification Producer interface name followed by the method signatures.
 *
 * See also ".\inc\aj_introspect.h"
 */
extern const char* const AJNS_NotificationProducerInterface[];
/**
 * Notification Producer interface version property value
 */
extern const uint16_t AJNS_NotificationProducerVersion;
/**
 * A NULL terminated collection of all NotificationProducer interfaces.
 */
extern const AJ_InterfaceDescription AJNS_NotificationProducerInterfaces[];
/**
 * The Notification service Producer object path
 */
extern const char AJNS_NotificationProducerObjectPath[];
/**
 * The Notification service Producer port
 */
extern const uint16_t AJNS_NotificationProducerPort;
/** @} */ // End of group 'NotificationCommon'
#endif /* _NOTIFICATIONCOMMON_H_ */
