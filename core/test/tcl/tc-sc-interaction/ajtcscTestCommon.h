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

#include <gtest/gtest.h>

#include <queue>
#include <functional>
#include <mutex>
#include <future>

extern "C" {
#include <ajtcl/alljoyn.h>
#include <ajtcl/aj_crypto.h>
#include <ajtcl/aj_authentication.h>
#include <ajtcl/aj_authorisation.h>
#include <ajtcl/aj_cert.h>
#include <ajtcl/aj_creds.h>
#include <ajtcl/aj_security.h>
#include <ajtcl/aj_link_timeout.h>
#include <ajtcl/aj_peer.h>

/* Undefine a TC deprecated flag that causes conflicts with SC headers */
#ifdef ALLJOYN_FLAG_SESSIONLESS
#undef ALLJOYN_FLAG_SESSIONLESS
#endif

/* Undefine all SC conflicting macros defined by Thin Library */

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#ifdef KEYLEN
#undef KEYLEN
#endif

#ifdef OUTLEN
#undef OUTLEN
#endif

#ifdef SEEDLEN
#undef SEEDLEN
#endif

#ifdef SIGNAL
#undef SIGNAL
#endif

#ifdef PROPERTY
#undef PROPERTY
#endif
}

#include <qcc/Util.h>
#include <qcc/StringUtil.h>
#include <qcc/Thread.h>

#include <alljoyn/AllJoynStd.h>
#include <alljoyn/DBusStd.h>

#include <alljoyn/Message.h>
#include <alljoyn/TransportMask.h>

#include <alljoyn/BusAttachment.h>
#include <alljoyn/Init.h>

#include <alljoyn/BusObject.h>
#include <alljoyn/ProxyBusObject.h>
#include <alljoyn/InterfaceDescription.h>

#include <alljoyn/AboutData.h>
#include <alljoyn/AboutObjectDescription.h>
#include <alljoyn/AboutProxy.h>
#include <alljoyn/AboutListener.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

// The parameter passed to AJ_FindBusAndConnect API (value in milliseconds)
const uint16_t TC_LEAFNODE_CONNECT_TIMEOUT = 1500;

// The parameter passed to AJ_UnmarshalMsg API (value in milliseconds)
const uint16_t TC_UNMARSHAL_TIMEOUT = 100;

// The duration for which the test waits for an event before declaring a failure
const uint16_t WAIT_TIME  = 3000;
const uint16_t WAIT_MSECS = 5;

static AJ_Status DefaultAuthListener(uint32_t mechanism, uint32_t command, AJ_Credential* cred)
{
    AJ_Status status = AJ_ERR_INVALID;

    AJ_AlwaysPrintf(("DefaultAuthListener mechanism %x command %x\n", mechanism, command));

    switch (mechanism) {
    case AUTH_SUITE_ECDHE_NULL:
        cred->expiration = 0;
        status = AJ_OK;
        break;

    default:
        break;
    }
    return status;
}

static void DefaultAuthCallback(const void* context, AJ_Status status)
{
    std::promise<AJ_Status>* p = (std::promise<AJ_Status>*) context;
    p->set_value(status);
}

class TCProperties {
  public:
    TCProperties() { }
    void SetElement(qcc::String name, int32_t value);
    QStatus GetElement(qcc::String name, int32_t& value);
    void Clear();
    size_t GetNumElements();
    void HandleReply(AJ_Message* msg);

  private:
    std::map<qcc::String, int32_t> props;
};

class TCBusAttachment : public qcc::Thread {
    typedef std::function<void (void)> Function;
    typedef std::map<int, Function> MsgHandlerMap;

  public:

    TCBusAttachment(const char* name, AJ_AuthListenerFunc listener = DefaultAuthListener, AJ_PeerAuthenticateCallback callback = DefaultAuthCallback) : qcc::Thread(name), running(true), authlistener(listener), authcallback(callback) { }
    ~TCBusAttachment();
    void Connect(const char* router = NULL);
    qcc::ThreadReturn STDCALL Run(void* arg);
    QStatus Stop();
    void Enqueue(Function f);
    void SendMessage();
    virtual void RecvMessage(AJ_Message* msg);
    void HandleMessage(AJ_Message* msg);
    qcc::String GetUniqueName();
    QStatus EnablePeerSecurity(const char* mechanisms);
    void SetApplicationState(uint16_t state);
    void SetPermissionManifest(AJ_Manifest* manifest);
    QStatus BindSessionPort(uint16_t port);
    QStatus JoinSession(const char* host, uint16_t port, uint32_t& id);
    QStatus AuthenticatePeer(const char* host);
    QStatus MethodCall(const char* peer, uint32_t id, const char* str = NULL);
    QStatus Signal(const char* peer, uint32_t id, const char* str = NULL);
    QStatus GetProperty(const char* peer, uint32_t mid, uint32_t pid, int32_t& val);
    QStatus SetProperty(const char* peer, uint32_t mid, uint32_t pid, int32_t val);
    QStatus GetAllProperties(const char* peer, uint32_t mid, const char* ifn, TCProperties& val, bool secure = true);

    QStatus GetGuid(qcc::GUID128& guid);

    const char* GetErrorName() {
        return response.c_str();
    }
    const char* GetResponse() {
        return response.c_str();
    }

    std::queue<Function> funcs;
    qcc::Mutex funcs_lock;

    MsgHandlerMap message_handlers;

    bool running;
    AJ_AuthListenerFunc authlistener;
    AJ_PeerAuthenticateCallback authcallback;
    AJ_BusAttachment bus;
    bool bound;
    uint32_t session;
    uint16_t sessionPort;
    QStatus SCStatus;
    qcc::String response;
    uint32_t propid;
    int32_t propval;
    TCProperties properties;
};
