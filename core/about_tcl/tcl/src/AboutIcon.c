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

#include <alljoyn/about/AboutIcon.h>

#define CHECK(x) if ((status = (x)) != AJ_OK) { break; }

/*
 * Message identifiers for the method calls this application implements
 */

#define ABOUT_ICON_OBJECT_INDEX                         NUM_PRE_ABOUT_OBJECTS + 1

#define ABOUT_ICON_GET_PROP                             AJ_APP_MESSAGE_ID(ABOUT_ICON_OBJECT_INDEX, 0, AJ_PROP_GET)
#define ABOUT_ICON_SET_PROP                             AJ_APP_MESSAGE_ID(ABOUT_ICON_OBJECT_INDEX, 0, AJ_PROP_SET)

#define ABOUT_ICON_VERSION_PROP                         AJ_APP_PROPERTY_ID(ABOUT_ICON_OBJECT_INDEX, 1, 0)
#define ABOUT_ICON_MIMETYPE_PROP                        AJ_APP_PROPERTY_ID(ABOUT_ICON_OBJECT_INDEX, 1, 1)
#define ABOUT_ICON_SIZE_PROP                            AJ_APP_PROPERTY_ID(ABOUT_ICON_OBJECT_INDEX, 1, 2)

#define ABOUT_ICON_GET_URL                              AJ_APP_MESSAGE_ID(ABOUT_ICON_OBJECT_INDEX, 1, 3)
#define ABOUT_ICON_GET_CONTENT                          AJ_APP_MESSAGE_ID(ABOUT_ICON_OBJECT_INDEX, 1, 4)

/*
 * Following definitions are read by the application.
 */

static const char* const AJ_AboutIconInterface[] = {
    "org.alljoyn.Icon",
    "@Version>q",
    "@MimeType>s",
    "@Size>u",
    "?GetUrl >s",
    "?GetContent >ay",
    NULL
};

const AJ_InterfaceDescription AJ_AboutIconInterfaces[] = {
    AJ_PropertiesIface,
    AJ_AboutIconInterface,
    NULL
};

/**
 * Mime type of the About Device icon
 */
static const char* appAboutIconMimetype;

/**
 * Content of the About Device icon
 */
static const uint8_t* appAboutIconContent;

/**
 * Size of the About Device icon
 */
static size_t appAboutIconContentSize;

/**
 * url of the icon About Device icon
 */
static const char* appAboutIconUrl;

AJ_Status AJ_AboutIcon_Start(const char* aboutIconMimetype, const uint8_t* aboutIconContent, const size_t aboutIconContentSize, const char* aboutIconUrl)
{
    AJ_Status status = AJ_OK;

    appAboutIconMimetype = aboutIconMimetype;
    appAboutIconContent = aboutIconContent;
    appAboutIconContentSize = aboutIconContentSize;
    appAboutIconUrl = aboutIconUrl;

    return status;
}

/*
 * Handles a property GET request so marshals the property value to return
 */
static AJ_Status AJ_AboutIcon_PropGetHandler(AJ_Message* replyMsg, uint32_t propId, void* context)
{
    if (propId == ABOUT_ICON_VERSION_PROP) {
        uint16_t q = 1;
        return AJ_MarshalArgs(replyMsg, "q", q);
    } else if (propId == ABOUT_ICON_MIMETYPE_PROP) {
        return AJ_MarshalArgs(replyMsg, "s", appAboutIconMimetype);
    } else if (propId == ABOUT_ICON_SIZE_PROP) {
        uint32_t u = appAboutIconContentSize;
        return AJ_MarshalArgs(replyMsg, "u", u);
    } else {
        return AJ_ERR_UNEXPECTED;
    }
}

/*
 * Handles a property SET request so unmarshals the property value provided
 */
static AJ_Status AJ_AboutIcon_PropSetHandler(AJ_Message* replyMsg, uint32_t propId, void* context)
{
    return AJ_ERR_UNEXPECTED;
}

static AJ_Status AJ_AboutIcon_GetContent(AJ_Message* msg)
{
    AJ_Status status = AJ_OK;
    AJ_Message reply;
    uint32_t u = (uint32_t) appAboutIconContentSize;

    AJ_Printf("AboutIcon_GetContent()\n");
    do {
        CHECK(AJ_MarshalReplyMsg(msg, &reply));
        CHECK(AJ_DeliverMsgPartial(&reply, u + 4));
        CHECK(AJ_MarshalRaw(&reply, &u, 4));
        int i = 0;
        for (; i < appAboutIconContentSize; i++) {
            CHECK(AJ_MarshalRaw(&reply, &(appAboutIconContent[i]), 1));
        }
        CHECK(AJ_DeliverMsg(&reply));
    } while (0);

    return status;
}

static AJ_Status AJ_AboutIcon_GetUrl(AJ_Message* msg)
{
    AJ_Status status = AJ_OK;
    AJ_Message reply;

    AJ_Printf("AboutIcon_GetUrl()\n");

    do {
        CHECK(AJ_MarshalReplyMsg(msg, &reply));
        CHECK(AJ_MarshalArgs(&reply, "s", appAboutIconUrl));
        CHECK(AJ_DeliverMsg(&reply));
    } while (0);

    return status;
}

AJSVC_ServiceStatus AJ_AboutIcon_MessageProcessor(AJ_BusAttachment* bus, AJ_Message* msg, AJ_Status* msgStatus)
{
    AJSVC_ServiceStatus serviceStatus = AJSVC_SERVICE_STATUS_HANDLED;

    switch (msg->msgId) {

    case ABOUT_ICON_GET_PROP:
        *msgStatus = AJ_BusPropGet(msg, AJ_AboutIcon_PropGetHandler, NULL);
        break;

    case ABOUT_ICON_SET_PROP:
        *msgStatus = AJ_BusPropSet(msg, AJ_AboutIcon_PropSetHandler, NULL);
        break;

    case ABOUT_ICON_GET_CONTENT:
        *msgStatus = AJ_AboutIcon_GetContent(msg);
        break;

    case ABOUT_ICON_GET_URL:
        *msgStatus = AJ_AboutIcon_GetUrl(msg);
        break;

    default:
        serviceStatus = AJSVC_SERVICE_STATUS_NOT_HANDLED;
        break;
    }

    return serviceStatus;
}
