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
#ifndef _ALLJOYN_ABOUTOBJECTDESCRIPTIONINTERNAL_H
#define _ALLJOYN_ABOUTOBJECTDESCRIPTIONINTERNAL_H

#include <alljoyn/AboutObjectDescription.h>
#include <qcc/Mutex.h>

#include <set>
#include <map>

namespace ajn {
/**
 * Class used to hold internal values for the AboutObjectDescription
 */
class AboutObjectDescription::Internal {
    friend class AboutObjectDescription;
  public:
    AboutObjectDescription::Internal& operator=(const AboutObjectDescription::Internal& other) {
        announceObjectsMap = other.announceObjectsMap;
        return *this;
    }

  private:
    /**
     * Mutex that protects the announceObjectsMap
     *
     * this is marked as mutable so we can grab the lock to prevent the Objects
     * map being modified while its being read.
     */
    mutable qcc::Mutex announceObjectsMapLock;

    /**
     *  map that holds interfaces
     */
    std::map<qcc::String, std::set<qcc::String> > announceObjectsMap;
};
}
#endif //_ALLJOYN_ABOUTOBJECTDESCRIPTIONINTERNAL_H
