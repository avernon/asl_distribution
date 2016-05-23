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

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <qcc/String.h>
#include <vector>
#include <map>

#include "Rule.h"
#if TARGET_ANDROID
#include "android/RulePersister.h"
#else
#include "posix/RulePersister.h"
#endif

#ifndef LOGTHIS
#if TARGET_ANDROID
#include <jni.h>
#include <android/log.h>
#define LOG_TAG  "JNI_EventActionBrowser"
#define LOGTHIS(...) (__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))
#else
#define LOGTHIS(...) { printf(__VA_ARGS__); printf("\n"); }
#endif
#endif

#ifndef _SIMPLE_RULE_ENGINE_
#define _SIMPLE_RULE_ENGINE_

class SimpleRuleEngine {
  public:
    /**
     * Construct a MyAllJoynCode object
     *
     */
    SimpleRuleEngine(
        #if TARGET_ANDROID
        JavaVM* vm,
        jobject jobj
        #endif
        ) :
        #if TARGET_ANDROID
        vm(vm), jobj(jobj), mRulePersister(vm, jobj)
        #else
        mRulePersister()
        #endif
    { };

    /**
     * Destructor
     */
    ~SimpleRuleEngine() {
        shutdown();
    };

    /**
     * .
     *
     * @param engineName
     * @param bus
     *
     */
    QStatus initialize(const char* engineName, ajn::BusAttachment* bus);

    QStatus addRule(Rule* rule, bool persist);

    QStatus removeRule(Rule* rule);

    QStatus removeAllRules();

    Rule* getRules(size_t& len);

    //Application using this engine is responsible for registering for About handler and passing
    //through the call to this engine
    void Announce(const char* busName, uint16_t version,
                  ajn::SessionPort port, const ajn::MsgArg& objectDescriptionArg,
                  const ajn::MsgArg& aboutDataArg);

    /**
     * Free up and release the objects used
     */
    QStatus shutdown();

  private:
#if TARGET_ANDROID
    JavaVM * vm;
    jobject jobj;
#endif

    RulePersister mRulePersister;

    struct NearbyAppInfo {
        qcc::String friendlyName;
        qcc::String deviceId;
        qcc::String appId;
        short port;
    };
    std::map<qcc::String, NearbyAppInfo*> mNearbyAppMap;

    std::vector<Rule*> mRules;
};

#endif //_SIMPLE_RULE_ENGINE_
