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

#ifndef _SERVICES_COMMON_H_
#define _SERVICES_COMMON_H_

#include <alljoyn.h>

/**
 * Turn on per-module debug printing by setting this variable to non-zero value
 * (usually in debugger).
 */
#ifndef NDEBUG
#ifdef CONFIG_SERVICE
extern uint8_t dbgAJCFG;
#endif
#ifdef ONBOARDING_SERVICE
extern uint8_t dbgAJOBS;
#endif
#if defined(NOTIFICATION_SERVICE_CONSUMER) || defined(NOTIFICATION_SERVICE_PRODUCER)
extern uint8_t dbgAJNS;
#endif
#ifdef CONTROLPANEL_SERVICE
extern uint8_t dbgAJCPS;
#endif
extern uint8_t dbgAJSVC;
#endif

/**
 * Function prototype for return callback when a method call is completed.
 */
typedef void (*AJSVC_MethodCallCompleted)(AJ_Status status, void* context);

/**
 * Service Status is an enum that signals whether a call was handled
 * or not handled within an AJSVC_MessageProcessor function
 */
typedef enum _AJSVC_ServiceStatus {
    AJSVC_SERVICE_STATUS_HANDLED,       //!< SERVICE_STATUS_HANDLED
    AJSVC_SERVICE_STATUS_NOT_HANDLED,   //!< SERVICE_STATUS_NOT_HANDLED
} AJSVC_ServiceStatus;

/**
 * Function used to process request messages.
 * @param busAttachment
 * @param msg
 * @param msgStatus
 * @return serviceStatus
 */
typedef AJSVC_ServiceStatus (*AJSVC_MessageProcessor)(AJ_BusAttachment* busAttachment, AJ_Message* msg, AJ_Status* msgStatus);

/**
 * UpdateNotAllowed Error Message for services
 */
#define AJSVC_ERROR_UPDATE_NOT_ALLOWED     AJ_ErrUpdateNotAllowed

/**
 * InvalidValue Error Message for services
 */
#define AJSVC_ERROR_INVALID_VALUE          AJ_ErrInvalidValue

/**
 * FeatureNotAvailable Error Message for services
 */
#define AJSVC_ERROR_FEATURE_NOT_AVAILABLE  AJ_ErrFeatureNotAvailable

/**
 * MazSizeExceeded Error Message for services
 */
#define AJSVC_ERROR_MAX_SIZE_EXCEEDED      AJ_ErrMaxSizeExceeded

/**
 * LanguageNotSupported Error Message for services
 */
#define AJSVC_ERROR_LANGUAGE_NOT_SUPPORTED AJ_ErrLanguageNotSuppored


/**
 * returns the language index for the given language name possibly creating an error reply message if erred
 * @param msg
 * @param reply
 * @param language
 * @param langIndex
 * @return success
 */
uint8_t AJSVC_IsLanguageSupported(AJ_Message* msg, AJ_Message* reply, const char* language, int8_t* langIndex);

/*!
   \brief Length of the AppID field
 */
#define UUID_LENGTH 16

/**
 * Marshals the provided appId as an 'ay'.
 * @param msg   the message to marshal the appId into
 * @param appId the application id to marshal
 * @return status
 */
AJ_Status AJSVC_MarshalAppId(AJ_Message* msg, const char* appId);

/**
 * Unmarshals the appId from the provided message.
 * @param msg     the message to unmarshal the appId from
 * @param buf     the buffer where the application id is unmarshalled into
 * @param bufLen  the size of the provided buffer. Should be UUID_LENGTH * 2 + 1.
 * @return status
 */
AJ_Status AJSVC_UnmarshalAppId(AJ_Message* msg, char* buf, size_t bufLen);

// The following is the static registration of all services' bus objects

/*
 * For each service:
 * 1) Define pre objects - the amount of objects registered before the service
 * 2) If service is included:
 *    i)   include service header file(s)
 *    If service is NOT included:
 *    i)   define the default number of appobjects and number of objects
 *    ii)  define the default announce objects
 */
/*
 * Includes for all the services
 */
#define NUM_PRE_CONFIG_OBJECTS                0
#ifdef CONFIG_SERVICE
    #include "alljoyn/config/ConfigService.h"
#else
    #define NUM_CONFIG_OBJECTS 0
    #define CONFIG_APPOBJECTS
#endif

#define NUM_PRE_ONBOARDING_OBJECTS            NUM_PRE_CONFIG_OBJECTS + NUM_CONFIG_OBJECTS
#ifdef ONBOARDING_SERVICE
    #include "alljoyn/onboarding/OnboardingService.h"
#else
    #define NUM_ONBOARDING_OBJECTS 0
    #define ONBOARDING_APPOBJECTS
#endif

#define NUM_PRE_NOTIFICATION_COMMON_OBJECTS   NUM_PRE_ONBOARDING_OBJECTS + NUM_ONBOARDING_OBJECTS
#if defined(NOTIFICATION_SERVICE_PRODUCER) || defined(NOTIFICATION_SERVICE_CONSUMER)
    #include "alljoyn/notification/NotificationCommon.h"
#else
    #define NUM_NOTIFICATION_COMMON_OBJECTS 0
    #define NOTIFICATION_COMMON_APPOBJECTS
#endif

#define NUM_PRE_NOTIFICATION_PRODUCER_OBJECTS NUM_PRE_NOTIFICATION_COMMON_OBJECTS + NUM_NOTIFICATION_COMMON_OBJECTS
#ifdef NOTIFICATION_SERVICE_PRODUCER
    #include "alljoyn/notification/NotificationProducer.h"
#else
    #define NUM_NOTIFICATION_PRODUCER_OBJECTS 0
    #define NOTIFICATION_PRODUCER_APPOBJECTS
#endif

#define NUM_PRE_CONTROLPANEL_OBJECTS          NUM_PRE_NOTIFICATION_PRODUCER_OBJECTS + NUM_NOTIFICATION_PRODUCER_OBJECTS
#ifdef CONTROLPANEL_SERVICE
    #include "alljoyn/controlpanel/ControlPanelService.h"
#else
    #define NUM_CONTROLPANEL_OBJECTS 0
    #define CONTROLPANEL_APPOBJECTS
#endif

#define NUM_PRE_APPLICATION_OBJECTS (NUM_PRE_CONTROLPANEL_OBJECTS + NUM_CONTROLPANEL_OBJECTS)

#define NUM_PRE_NOTIFICATION_CONSUMER_PROXYOBJECTS 0
#ifdef NOTIFICATION_SERVICE_CONSUMER
    #include "alljoyn/notification/NotificationConsumer.h"
#else
    #define NUM_NOTIFICATION_CONSUMER_PROXYOBJECTS 0
    #define NOTIFICATION_CONSUMER_PROXYOBJECTS
#endif

#define NUM_PRE_PROXY_OBJECTS (NUM_PRE_NOTIFICATION_CONSUMER_PROXYOBJECTS + NOTIFICATION_CONSUMER_PROXYOBJECTS)

/*
 * Define pre objects - the amount of objects registered before each service
 */

/*
 * Defines AppObjects and Proxyobjects to be registered
 * each of those are described in the service itself
 * for example NOTIFICATION_PRODUCER_APPOBJECTS is defined in
 * services/notification/tcl/inc/alljoyn/notification/NotificationProducer.h
 */
#define IOE_SERVICES_APPOBJECTS \
    CONFIG_APPOBJECTS \
    ONBOARDING_APPOBJECTS \
    NOTIFICATION_COMMON_APPOBJECTS \
    NOTIFICATION_PRODUCER_APPOBJECTS

#define IOE_SERVICES_PROXYOBJECTS \
    NOTIFICATION_CONSUMER_PROXYOBJECTS

#endif /* _SERVICES_COMMON_H_ */
