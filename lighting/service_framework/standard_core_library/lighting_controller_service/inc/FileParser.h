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
#ifndef LSF_FILE_PARSER_H
#define LSF_FILE_PARSER_H
/**
 * \ingroup ControllerService
 */
/**
 * @file
 * This file provides definitions for file parser
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

#include <string>
#include <iostream>
#include <fstream>
#include <LSFTypes.h>
#include "LSFNamespaceSpecifier.h"

namespace lsf {

OPTIONAL_NAMESPACE_CONTROLLER_SERVICE

extern const std::string resetID;

extern const std::string initialStateID;

void ParseLampState(std::istream& stream, LampState& state);

/**
 * Read a string from the stream.  Spaces will be included between double-quotes
 *
 * @param stream    The stream
 * @return          The next token in the stream
 */
std::string ParseString(std::istream& stream);

template <typename T>
T ParseValue(std::istream& stream)
{
    T t;
    stream >> t;
    return t;
}

std::ostream& WriteValue(std::ostream& stream, const std::string& name);

std::ostream& WriteString(std::ostream& stream, const std::string& name);

OPTIONAL_NAMESPACE_CLOSE

} //lsf

#endif
