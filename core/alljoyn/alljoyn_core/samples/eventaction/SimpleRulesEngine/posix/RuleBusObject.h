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

#include <alljoyn/BusAttachment.h>
#include <alljoyn/DBusStd.h>
#include <alljoyn/AllJoynStd.h>
#include <alljoyn/BusObject.h>

#include "../SimpleRuleEngine.h"

#ifndef _RULE_BUS_OBJECT_
#define _RULE_BUS_OBJECT_

class RuleBusObject : public ajn::BusObject {
  public:
    /**
     * Construct a RuleBusObject object
     *
     */
    RuleBusObject(ajn::BusAttachment* busAttachment, const char* path, SimpleRuleEngine* ruleEngine);

  private:
    void addRule(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);

    void deleteAllRules(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);


  private:
    ajn::BusAttachment* mBusAttachment;
    SimpleRuleEngine* mRuleEngine;
};

#endif //_RULE_BUS_OBJECT_
