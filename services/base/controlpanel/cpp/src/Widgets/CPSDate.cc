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

#include <alljoyn/controlpanel/CPSDate.h>

namespace ajn {
namespace services {

CPSDate::CPSDate(uint16_t day, uint16_t month, uint16_t year) :
    m_Day(day), m_Month(month), m_Year(year)
{
}

CPSDate::~CPSDate()
{
}

uint16_t CPSDate::getDay() const
{
    return m_Day;
}

void CPSDate::setDay(uint16_t day)
{
    m_Day = day;
}

uint16_t CPSDate::getMonth() const
{
    return m_Month;
}

void CPSDate::setMonth(uint16_t month)
{
    m_Month = month;
}

uint16_t CPSDate::getYear() const
{
    return m_Year;
}

void CPSDate::setYear(uint16_t year)
{
    m_Year = year;
}

} /* namespace services */
} /* namespace ajn */
