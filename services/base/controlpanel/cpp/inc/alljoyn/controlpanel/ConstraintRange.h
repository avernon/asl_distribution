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

#ifndef CONSTRAINTRANGE_H_
#define CONSTRAINTRANGE_H_

#include <alljoyn/controlpanel/Widget.h>

namespace ajn {
namespace services {

/**
 * ConstraintRangeValue - a union combining all possible values
 * that can make up a constraint Range
 */
typedef union {
    /**
     * Value of type uint16_t
     */
    uint16_t uint16Value;
    /**
     * Value of type int16_t
     */
    int16_t int16Value;
    /**
     * Value of type uint32_t
     */
    uint32_t uint32Value;
    /**
     * Value of type int32_t
     */
    int32_t int32Value;
    /**
     * Value of type uint64_t
     */
    uint64_t uint64Value;
    /**
     * Value of type int64_t
     */
    int64_t int64Value;
    /**
     * Value of type double
     */
    double doubleValue;
} ConstraintRangeVal;

/**
 * Constraint Range class to define a range of
 * Values and constrain a property to those values
 * The Constraint is applied on the controller side.
 * No validations are done in the Controlee
 */
class ConstraintRange {
  public:

    /**
     * Constructor for ConstraintRange
     */
    ConstraintRange();

    /**
     * Destructor for ConstraintRange
     */
    virtual ~ConstraintRange();

    /**
     * get the IncrementValue of the Constraint Range
     * @return IncrementValue
     */
    const ConstraintRangeVal& getIncrementValue() const;

    /**
     * Get the MaxValue of the Constraint Range
     * @return MaxValue
     */
    const ConstraintRangeVal& getMaxValue() const;

    /**
     * Get the MinValue of the Constraint Range
     * @return MinValue
     */
    const ConstraintRangeVal& getMinValue() const;

    /**
     * Set the Min Value for the Constraint
     * @param minValue
     * @return status - success/failure
     */
    QStatus setConstraintMin(uint16_t minValue);

    /**
     * Set the Min Value for the Constraint
     * @param minValue
     * @return status - success/failure
     */
    QStatus setConstraintMin(int16_t minValue);

    /**
     * Set the Min Value for the Constraint
     * @param minValue
     * @return status - success/failure
     */
    QStatus setConstraintMin(uint32_t minValue);

    /**
     * Set the Min Value for the Constraint
     * @param minValue
     * @return status - success/failure
     */
    QStatus setConstraintMin(int32_t minValue);

    /**
     * Set the Min Value for the Constraint
     * @param minValue
     * @return status - success/failure
     */
    QStatus setConstraintMin(uint64_t minValue);

    /**
     * Set the Min Value for the Constraint
     * @param minValue
     * @return status - success/failure
     */
    QStatus setConstraintMin(int64_t minValue);

    /**
     * Set the Min Value for the Constraint
     * @param minValue
     * @return status - success/failure
     */
    QStatus setConstraintMin(double minValue);

    /**
     * Set the Max Value for the Constraint
     * @param maxValue
     * @return status - success/failure
     */
    QStatus setConstraintMax(uint16_t maxValue);

    /**
     * Set the Max Value for the Constraint
     * @param maxValue
     * @return status - success/failure
     */
    QStatus setConstraintMax(int16_t maxValue);

    /**
     * Set the Max Value for the Constraint
     * @param maxValue
     * @return status - success/failure
     */
    QStatus setConstraintMax(uint32_t maxValue);

    /**
     * Set the Max Value for the Constraint
     * @param maxValue
     * @return status - success/failure
     */
    QStatus setConstraintMax(int32_t maxValue);

    /**
     * Set the Max Value for the Constraint
     * @param maxValue
     * @return status - success/failure
     */
    QStatus setConstraintMax(uint64_t maxValue);

    /**
     * Set the Max Value for the Constraint
     * @param maxValue
     * @return status - success/failure
     */
    QStatus setConstraintMax(int64_t maxValue);

    /**
     * Set the Max Value for the Constraint
     * @param maxValue
     * @return status - success/failure
     */
    QStatus setConstraintMax(double maxValue);

    /**
     * Set the Increment Value for the Constraint
     * @param incrementValue
     * @return status - success/failure
     */
    QStatus setConstraintIncrement(uint16_t incrementValue);

    /**
     * Set the Increment Value for the Constraint
     * @param incrementValue
     * @return status - success/failure
     */
    QStatus setConstraintIncrement(int16_t incrementValue);

    /**
     * Set the Increment Value for the Constraint
     * @param incrementValue
     * @return status - success/failure
     */
    QStatus setConstraintIncrement(uint32_t incrementValue);

    /**
     * Set the Increment Value for the Constraint
     * @param incrementValue
     * @return status - success/failure
     */
    QStatus setConstraintIncrement(int32_t incrementValue);

    /**
     * Set the Increment Value for the Constraint
     * @param incrementValue
     * @return status - success/failure
     */
    QStatus setConstraintIncrement(uint64_t incrementValue);

    /**
     * Set the Increment Value for the Constraint
     * @param incrementValue
     * @return status - success/failure
     */
    QStatus setConstraintIncrement(int64_t incrementValue);

    /**
     * Set the Increment Value for the Constraint
     * @param incrementValue
     * @return status - success/failure
     */
    QStatus setConstraintIncrement(double incrementValue);

    /**
     * Fill the MsgArg passed in with the Constraint
     * @param val - msgArg to fill
     * @param languageIndx - the languageIndx for the Display value
     * @param propertyType - the property Type expected
     * @return status - success/failure
     */
    QStatus fillConstraintArg(MsgArg& val, uint16_t languageIndx, PropertyType propertyType);

    /**
     * Read the MsgArg passed in and fill the Constraint
     * @param val - MsgArg passed in
     * @return status - success/failure
     */
    QStatus readConstraintArg(MsgArg* val);

  private:

    /**
     * Validate that the constraint value matches the correct propertyType
     * @param propertyType - propertyType to validate for
     * @return pass/fail
     */
    bool validateConstraintValue(PropertyType propertyType);

    /**
     * The MinValue of the Constraint
     */
    ConstraintRangeVal m_MinValue;

    /**
     * The MaxValue of the Constraint
     */
    ConstraintRangeVal m_MaxValue;

    /**
     * The IncrementValue of the Constraint
     */
    ConstraintRangeVal m_IncrementValue;

    /**
     * The PropertyType of the Constraint
     */
    PropertyType m_PropertyType;
};

} /* namespace services */
} /* namespace ajn */
#endif /* CONSTRAINTRANGE_H_ */
