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

#include <alljoyn/controlpanel/CPSTime.h>

namespace ajn {
namespace services {

CPSTime::CPSTime(uint16_t hour, uint16_t minute, uint16_t second) :
    m_Hour(hour), m_Minute(minute), m_Second(second)
{
}

CPSTime::~CPSTime()
{
}

uint16_t CPSTime::getHour() const
{
    return m_Hour;
}

void CPSTime::setHour(uint16_t hour)
{
    m_Hour = hour;
}

uint16_t CPSTime::getMinute() const
{
    return m_Minute;
}

void CPSTime::setMinute(uint16_t minute)
{
    m_Minute = minute;
}

uint16_t CPSTime::getSecond() const
{
    return m_Second;
}

void CPSTime::setSecond(uint16_t second)
{
    m_Second = second;
}

} /* namespace services */
} /* namespace ajn */
