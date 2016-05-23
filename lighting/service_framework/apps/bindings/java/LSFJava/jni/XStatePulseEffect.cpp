/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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
 *
 ******************************************************************************/

#include "NUtil.h"
#include "XObject.h"
#include "XStatePulseEffect.h"

namespace lsf {

//TODO-FIX Refactor to common location?
static LSFStringList emptyStringList;
static LampState emptyState;
static uint32_t emptyValue = 0;

XStatePulseEffect::XStatePulseEffect(jobject jobj) : PulseLampsLampGroupsWithState(emptyStringList, emptyStringList, emptyState, emptyState, emptyValue, emptyValue, emptyValue)
{
    // Currently nothing to do
}

XStatePulseEffect::~XStatePulseEffect()
{
    // Currently nothing to do
}

XStatePulseEffect&
XStatePulseEffect::operator=(const PulseLampsLampGroupsWithState& other)
{
    PulseLampsLampGroupsWithState::operator=(other);
    return *this;
}

jobjectArray
XStatePulseEffect::NewArray(std::list<PulseLampsLampGroupsWithState>& cEffectList)
{
    return XObject::NewArray<PulseLampsLampGroupsWithState, XStatePulseEffect>(XClass::xStatePulseEffect, cEffectList);
}

void
XStatePulseEffect::CopyArray(jobjectArray jObjectArray, std::list<PulseLampsLampGroupsWithState>& cEffectList)
{
    XObject::CopyArray<PulseLampsLampGroupsWithState, XStatePulseEffect>(XClass::xStatePulseEffect, jObjectArray, cEffectList);
}

} /* namespace lsf */

