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

#include <Rank.h>
#include <qcc/Debug.h>
#include <qcc/String.h>
#include <qcc/StringUtil.h>

#define QCC_MODULE "LSF_RANK"

using namespace qcc;

namespace lsf {

Rank::Rank() :
    higherOrderBits(0UL),
    lowerOrderBits(0UL),
    initialized(false)
{
    QCC_DbgTrace(("%s", __func__));
}

Rank::Rank(uint64_t higherBits, uint64_t lowerBits)
{
    QCC_DbgTrace(("%s", __func__));
    Set(higherBits, lowerBits);
}

Rank::Rank(const Rank& other) :
    higherOrderBits(other.higherOrderBits),
    lowerOrderBits(other.lowerOrderBits),
    initialized(other.initialized)
{
    QCC_DbgTrace(("%s", __func__));
}

Rank::~Rank()
{
    QCC_DbgTrace(("%s", __func__));
}

void Rank::Set(uint64_t higherBits, uint64_t lowerBits)
{
    QCC_DbgTrace(("%s", __func__));
    higherOrderBits = higherBits;
    lowerOrderBits = lowerBits;
    initialized = true;
}

Rank& Rank::operator =(const Rank& other)
{
    QCC_DbgTrace(("%s", __func__));
    higherOrderBits = other.higherOrderBits;
    lowerOrderBits = other.lowerOrderBits;
    initialized = other.initialized;
    return *this;
}

bool Rank::operator ==(const Rank& other) const
{
    QCC_DbgTrace(("%s", __func__));
    if ((higherOrderBits == other.higherOrderBits) && (lowerOrderBits == other.lowerOrderBits)) {
        QCC_DbgPrintf(("%s: Returning true", __func__));
        return true;
    }
    QCC_DbgPrintf(("%s: Returning false", __func__));
    return false;
}

bool Rank::operator !=(const Rank& other) const
{
    QCC_DbgTrace(("%s", __func__));
    if ((higherOrderBits != other.higherOrderBits) || (lowerOrderBits != other.lowerOrderBits)) {
        QCC_DbgPrintf(("%s: Returning true", __func__));
        return true;
    }
    QCC_DbgPrintf(("%s: Returning false", __func__));
    return false;
}

bool Rank::operator <(const Rank& other) const
{
    QCC_DbgTrace(("%s", __func__));
    if (higherOrderBits < other.higherOrderBits) {
        QCC_DbgPrintf(("%s: Returning true", __func__));
        return true;
    } else if ((higherOrderBits == other.higherOrderBits) && (lowerOrderBits < other.lowerOrderBits)) {
        QCC_DbgPrintf(("%s: Returning true", __func__));
        return true;
    }
    QCC_DbgPrintf(("%s: Returning false", __func__));
    return false;
}

bool Rank::operator >(const Rank& other) const
{
    QCC_DbgTrace(("%s", __func__));
    if (higherOrderBits > other.higherOrderBits) {
        QCC_DbgPrintf(("%s: Returning true", __func__));
        return true;
    } else if ((higherOrderBits == other.higherOrderBits) && (lowerOrderBits > other.lowerOrderBits)) {
        QCC_DbgPrintf(("%s: Returning true", __func__));
        return true;
    }
    QCC_DbgPrintf(("%s: Returning false", __func__));
    return false;
}

const char* Rank::c_str(void) const
{
    QCC_DbgPrintf(("%s", __func__));
    static qcc::String ret;
    ret.clear();
    ret = qcc::String("Higher Order Bits = 0x") + U64ToString(higherOrderBits, 16) + qcc::String("(") + U64ToString(higherOrderBits) + qcc::String(")");
    ret += qcc::String(" Lower Order Bits = 0x") + U64ToString(lowerOrderBits, 16) + qcc::String("(") + U64ToString(lowerOrderBits) + qcc::String(")") + qcc::String("\n");
    return ret.c_str();
}

}
