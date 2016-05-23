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
 ******************************************************************************/

#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

#include <ostream>
#include <sstream>
#include <string>
#include <qcc/String.h>

namespace mdf {

class StringUtils {

  public:

    template <typename T>
    static T StringToNumber(const qcc::String& Text)
    {
        std::istringstream ss(Text.c_str());
        T result;
        return ss >> result ? result : 0;
    }

    template <typename T>
    static qcc::String NumberToString(T Number)
    {
        std::ostringstream ss;
        ss << Number;
        return qcc::String(ss.str().c_str());
    }

};

} //end mdf

#endif /* STRINGUTILS_H_ */
