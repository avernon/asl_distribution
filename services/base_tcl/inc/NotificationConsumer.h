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

#ifndef NOTIFICATIONCONSUMER_H_
#define NOTIFICATIONCONSUMER_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/services/ServicesCommon.h>
#include <ajtcl/services/NotificationCommon.h>

/** @defgroup NotificationConsumer Notification Consumer
 * details Functions and variables that assist in writing Notification Producers
 *  @{
 */

/* Allowed limits on message content */
#define NUMALLOWEDCUSTOMATTRIBUTES      10    /**< Number allowed custom attributes */
#define NUMALLOWEDTEXTS                 10    /**< Number allowed test */
#define NUMALLOWEDRICHNOTS              10    /**< Number allowed richnots */

/**
 * Published Notification Signal Receiver Proxy BusObjects and Interfaces.
 */

/**
 * Utility structure for saving a reference to a received notification.
 */
typedef struct _AJNS_Consumer_NotificationReference {
    uint16_t version;                        /**< version of notification */
    int32_t notificationId;                  /**< id of notification */
    char appId[UUID_LENGTH * 2 + 1];         /**< app id */
    char originalSenderName[16];             /**< original sender name */
} AJNS_Consumer_NotificationReference;

/**
 * OnNotify implemented by the application
 * @param notification header and content
 * @return status success/failure
 */
typedef AJ_Status (*AJNS_Consumer_OnNotify)(AJNS_Notification* notification);

/**
 * OnDismiss implemented by the application
 * @param notificationId the notification id of the notification to dismiss
 * @param appId          the application id of the original sender of the notification to dismiss
 * @return status success/failure
 */
typedef AJ_Status (*AJNS_Consumer_OnDismiss)(int32_t notificationId, const char* appId);

/**
 * Start Notification service framework Consumer passing mode and callbacks
 * @param appSuperAgentMode
 * @param appOnNotify
 * @param appOnDismiss
 * @return status
 */
AJ_Status AJNS_Consumer_Start(uint8_t appSuperAgentMode, AJNS_Consumer_OnNotify appOnNotify, const AJNS_Consumer_OnDismiss appOnDismiss);

/**
 * Consumer_SetSignalRules, to add the correct filter for the required interface
 * @param busAttachment
 * @param superAgentMode
 * @param senderBusName
 * @return status
 */
AJ_Status AJNS_Consumer_SetSignalRules(AJ_BusAttachment* busAttachment, uint8_t superAgentMode, const char* senderBusName);

/**
 * Consumer_IsSuperAgentLost, checks whether the lost device/app is the SuperAgent
 * @param msg LOST_ADVERTISED_NAME message to process
 * @return Whether the lost device/app is the SuperAgent
 */
uint8_t AJNS_Consumer_IsSuperAgentLost(AJ_Message* msg);

/**
 * Consumer_NotifySignalHandler - receives message, unmarshals it and calls handleNotify
 * @param msg
 * @return status
 */
AJ_Status AJNS_Consumer_NotifySignalHandler(AJ_Message* msg);

/**
 * Consumer_DismissSignalHandler - receives message, unmarshals it and calls handleDismiss
 * @param msg
 * @return status
 */
AJ_Status AJNS_Consumer_DismissSignalHandler(AJ_Message* msg);

/**
 * Consumer_DismissNotification - send a dismissal request to the producer of the given message, marshals the methodcall and delivers it
 * @param busAttachment
 * @param version               the message version
 * @param notificationId        the notification id
 * @param appId                 the application id of the message sender application
 * @param senderName            the bus unique name of the message sender
 * @param completedCallback     the callback to call when the Dismiss method reply is received
 * @return status
 */
AJ_Status AJNS_Consumer_DismissNotification(AJ_BusAttachment* busAttachment, uint16_t version, int32_t notificationId, const char* appId, const char* senderName, AJSVC_MethodCallCompleted completedCallback);

/**
 * Consumer_PropGetHandler - handle get property call
 * @param replyMsg
 * @param propId
 * @param context
 * @return the Alljoyn status
 */
AJ_Status AJNS_Consumer_PropGetHandler(AJ_Message* replyMsg, uint32_t propId, void* context);

/**
 * Consumer_PropSetHandler - handle set property call
 * @param replyMsg
 * @param propId
 * @param context
 * @return the Alljoyn status
 */
AJ_Status AJNS_Consumer_PropSetHandler(AJ_Message* replyMsg, uint32_t propId, void* context);

/**
 * Function called after service connects
 * @param busAttachment
 * @return the Alljoyn status
 */
AJ_Status AJNS_Consumer_ConnectedHandler(AJ_BusAttachment* busAttachment);

/**
 * Process the message received
 * @param busAttachment
 * @param msg
 * @param msgStatus
 * @return status - was message handled
 */
AJSVC_ServiceStatus AJNS_Consumer_MessageProcessor(AJ_BusAttachment* busAttachment, AJ_Message* msg, AJ_Status* msgStatus);

/**
 * Handle failed session join
 * @param busAttachment
 * @param sessionId
 * @param replySerialNum
 * @return status - was message handled
 */
AJSVC_ServiceStatus AJNS_Consumer_SessionJoinedHandler(AJ_BusAttachment* busAttachment, uint32_t sessionId, uint32_t replySerialNum);

/**
 * Handle successful session join
 * @param busAttachment
 * @param replySerialNum
 * @param replyCode
 * @return status - was message handled
 */
AJSVC_ServiceStatus AJNS_Consumer_SessionRejectedHandler(AJ_BusAttachment* busAttachment, uint32_t replySerialNum, uint32_t replyCode);

/**
 * Handle session loss
 * @param busAttachment
 * @param sessionId
 * @param reason
 * @return status - was message handled
 */
AJSVC_ServiceStatus AJNS_Consumer_SessionLostHandler(AJ_BusAttachment* busAttachment, uint32_t sessionId, uint32_t reason);

/**
 * Function called after service disconnects
 * @param busAttachment
 * @return the Alljoyn status
 */
AJ_Status AJNS_Consumer_DisconnectHandler(AJ_BusAttachment* busAttachment);
/** @} */ // End of group 'NotificationConsumer'
#endif /* NOTIFICATIONCONSUMER_H_ */
