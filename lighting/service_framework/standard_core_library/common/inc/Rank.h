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
#ifndef LSF_RANK_H
#define LSF_RANK_H
/**
 * \defgroup Common
 * Common code
 */
/**
 * \ingroup Common
 */
/**
 * @file
 * This file provides definitions for the Rank class
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

namespace lsf {

class Rank {
  public:
    /**
     * class constructor
     */
    Rank();

    /**
     * Parameterized Constructor
     */
    Rank(uint64_t higherBits, uint64_t lowerBits);

    /**
     * Copy Constructor
     */
    Rank(const Rank& other);

    /**
     * class destructor
     */
    ~Rank();

    /**
     * Set the parameters of the rank
     */
    void Set(uint64_t higherBits, uint64_t lowerBits);

    /**
     * Returns the higher order bits of the rank
     */
    uint64_t GetHigherOrderBits(void) { return higherOrderBits; };

    /**
     * Returns the lower order bits of the rank
     */
    uint64_t GetLowerOrderBits(void) { return lowerOrderBits; };

    /**
     * Assignment operator
     */
    Rank& operator =(const Rank& other);

    /**
     * Rank == operator
     */
    bool operator ==(const Rank& other) const;

    /**
     * Rank != operator
     */
    bool operator !=(const Rank& other) const;

    /**
     * Rank < operator
     */
    bool operator <(const Rank& other) const;

    /**
     * Rank > operator
     */
    bool operator >(const Rank& other) const;

    /**
     * Return the details of the Rank as a string
     *
     * @return string
     */
    const char* c_str(void) const;

    /**
     * Returns true if the rank has been initialized
     */
    bool IsInitialized(void) { return initialized; }

    /**
     * Set initialized to true
     */
    void SetInitialized(void) { initialized = true; };

  private:

    /**
     * 64 higher order bits in the 128-bit rank
     */
    uint64_t higherOrderBits;

    /**
     * 64 lower order bits in the 128-bit rank
     */
    uint64_t lowerOrderBits;

    /**
     * Indicates if the rank has been initialized
     */
    bool initialized;
};

}

#endif
