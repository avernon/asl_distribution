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

#ifndef CPSTIME_H_
#define CPSTIME_H_

#include <qcc/platform.h>

namespace ajn {
namespace services {

/**
 * A class to allow sending of a Time as a Property
 */
class CPSTime {
  public:

    /**
     * Constructor of a CPSTime.
     * @param hour - hour of date
     * @param minute - minute of date
     * @param second - second of date
     */
    CPSTime(uint16_t hour, uint16_t minute, uint16_t second);

    /**
     * Destructor of CPSTime
     */
    virtual ~CPSTime();

    /**
     * Get the hour value of the date
     * @return hour value
     */
    uint16_t getHour() const;

    /**
     * Set the hour Value of the date
     * @param hour value
     */
    void setHour(uint16_t hour);

    /**
     * Get the Minute value of the date
     * @return minute value
     */
    uint16_t getMinute() const;

    /**
     * Set the Minute value of the date
     * @param minute value
     */
    void setMinute(uint16_t minute);

    /**
     * Get the Second value of the date
     * @return second value
     */
    uint16_t getSecond() const;

    /**
     * Set the Second value of the date
     * @param second value
     */
    void setSecond(uint16_t second);

  private:

    /**
     * Hour value of the Time
     */
    uint16_t m_Hour;

    /**
     * Minute value of the Time
     */
    uint16_t m_Minute;

    /**
     * Second value of the Time
     */
    uint16_t m_Second;
};

} /* namespace services */
} /* namespace ajn */

#endif /* CPSTIME_H_ */
