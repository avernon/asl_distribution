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
#ifndef _ALLJOYN_BUSENDPOINT_H
#define _ALLJOYN_BUSENDPOINT_H
/**
 * @file
 * This file defines the class for handling the client and server
 * endpoints for the message bus wire protocol
 */

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

#include <qcc/platform.h>

#include <qcc/GUID.h>
#include <qcc/Mutex.h>
#include <qcc/String.h>
#include <qcc/ManagedObj.h>

#include <alljoyn/Message.h>
#include <alljoyn/MessageSink.h>

#include <alljoyn/Status.h>

namespace ajn {

class _BusEndpoint;

typedef qcc::ManagedObj<_BusEndpoint> BusEndpoint;

/**
 * BusEndpoint type.
 */
typedef enum {
    ENDPOINT_TYPE_INVALID, /**< An uninitialized endpoint */
    ENDPOINT_TYPE_NULL,    /**< Endpoint type used by the bundled daemon */
    ENDPOINT_TYPE_LOCAL,   /**< The local endpoint */
    ENDPOINT_TYPE_REMOTE,  /**< A remote endpoint */
    ENDPOINT_TYPE_BUS2BUS, /**< An endpoint connecting two busses */
    ENDPOINT_TYPE_VIRTUAL,  /**< Represents an endpoint on another bus */
    ENDPOINT_TYPE_MQTT /**< An endpoint connecting to an MQTT broker */
} EndpointType;

/**
 * Base class for all types of Bus endpoints
 */
class _BusEndpoint : public MessageSink {
  public:

    /**
     * Default constructor initializes an invalid endpoint
     */
    _BusEndpoint() : endpointType(ENDPOINT_TYPE_INVALID), isValid(false), disconnectStatus(ER_OK) { }

    /**
     * Constructor.
     *
     * @param type    BusEndpoint type.
     */
    _BusEndpoint(EndpointType type) : endpointType(type), isValid(type != ENDPOINT_TYPE_INVALID), disconnectStatus(ER_OK), userId(-1), groupId(-1) { }

    /**
     * Virtual destructor for derivable class.
     */
    virtual ~_BusEndpoint() { }

    /**
     * Check if an endpoint is valid
     */
    bool IsValid() const { return isValid; }

    /**
     * Invalidate a bus endpoint
     */
    void Invalidate();

    /**
     * Push a message into the endpoint
     *
     * @param msg   Message to send.
     *
     * @return ER_OK if successful
     */
    virtual QStatus PushMessage(Message& msg) { return ER_NOT_IMPLEMENTED; }

    /**
     * Register SessionId for endpoint.
     * @param[in] session Id to register.
     */
    virtual void RegisterSessionId(SessionId sessionId) { QCC_UNUSED(sessionId); return; };

    /**
     * Unregister SessionId from endpoint.
     * @param[in] session Id to unregister.
     */
    virtual void UnregisterSessionId(SessionId sessionId) { QCC_UNUSED(sessionId); return; };

    /**
     * Get the endpoint's unique name.
     *
     * @return  Unique name for endpoint.
     */
    virtual const qcc::String& GetUniqueName() const { return qcc::String::Empty; }

    /**
     * Get the unique name of the endpoint's local controller object.
     *
     * @return  Unique name for endpoint's controller.
     */
    qcc::String GetControllerUniqueName() const;

    /**
     * Return the user id of the endpoint.
     *
     * @return  User ID number.
     */
    virtual uint32_t GetUserId() const { return -1; }

    /**
     * Return the group id of the endpoint.
     *
     * @return  Group ID number.
     */
    virtual uint32_t GetGroupId() const { return -1; }

    /**
     * Return the process id of the endpoint.
     *
     * @return  Process ID number.
     */
    virtual uint32_t GetProcessId() const { return -1; }

    /**
     * Indicates if the endpoint supports reporting UNIX style user, group, and process IDs.
     *
     * @return  'true' if UNIX IDs supported, 'false' if not supported.
     */
    virtual bool SupportsUnixIDs() const { return false; }

    /**
     * Get endpoint type.
     *
     * @return EndpointType
     */
    EndpointType GetEndpointType() const { return endpointType; }

    /**
     * Set endpoint type.
     *
     * @param type EndpointType to set
     */
    void SetEndpointType(EndpointType type) { endpointType = type; }

    /**
     * BusEndpoint type.
     */
    typedef enum {
        ENDPOINT_FLOW_INVALID, /**< An unknown type of flow */
        ENDPOINT_FLOW_CHARS,   /**< Characters are flowing over the underlying connection */
        ENDPOINT_FLOW_HELLO,   /**< Characters are done flowing, but Hello exchange in progress */
        ENDPOINT_FLOW_MSGS     /**< Startup phase comlete, messages are flowing over the underlying connection */
    } EndpointFlowType;

    /**
     * Set the kind of data this endpoing is flowing.
     *
     * @param type    EndpointFlowType of the endpoint.
     */
    virtual void SetFlowType(EndpointFlowType type) { endpointFlowType = type; }

    /**
     * Return the kind of data this endpoing is flowing.
     *
     * @return  Type of data flowing over the endpoint and associated connection.
     */
    virtual EndpointFlowType GetFlowType() { return endpointFlowType; }

    /**
     * Return true if this endpoint is allowed to receive messages from remote (bus-to-bus) endpoints.
     *
     * @return  true iff endpoint is allowed to receive messages from remote (bus-to-bus) endpoints.
     */
    virtual bool AllowRemoteMessages() { return false; }

    /**
     * Return true if the endpoint was disconnected due to an error rather than a clean shutdown.
     */
    bool SurpriseDisconnect() const { return disconnectStatus != ER_OK; }

    /**
     * Return the status code underlying a disconnect event.
     */
    QStatus GetDisconnectStatus() const { return disconnectStatus; }

    /**
     * Bus endpoints are only equal if they are the same object
     */
    bool operator ==(const _BusEndpoint& other) const { return this == &other; }

    /**
     * Bus endpoints are only equal if they are the same object
     */
    bool operator !=(const _BusEndpoint& other) const { return this != &other; }

    /*
     * Less than operator to allow endpoints to be put in sorted containers
     */
    bool operator <(const _BusEndpoint& other) const
    {
        return reinterpret_cast<ptrdiff_t>(this) < reinterpret_cast<ptrdiff_t>(&other);
    }

    /**
     * Called to find out if the endpoint is a part of a particular session.
     * @param[in] session Id to check.
     * @return  true if this endpoint is a part of the session, otherwise false.
     */
    virtual bool IsInSession(SessionId sessionId)
    {
        QCC_UNUSED(sessionId);
        return false;
    }

  protected:

    EndpointType endpointType;          /**< Type of endpoint */
    EndpointFlowType endpointFlowType;  /**< Type of flow over the endpoint */
    bool isValid;                       /**< Is endpoint currently valid */
    QStatus disconnectStatus;           /**< Reason for the disconnect */
};


}

#endif
