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

#ifdef LSF_BINDINGS
#include <lsf/controllerservice/FileParser.h>
#else
#include <FileParser.h>
#endif

#include <LSFTypes.h>
#include <qcc/Debug.h>

#define QCC_MODULE "FILE_PARSER"

namespace lsf {

OPTIONAL_NAMESPACE_CONTROLLER_SERVICE

const std::string resetID = "Reset";

const std::string initialStateID = "InitialState";

void ParseLampState(std::istream& stream, LampState& state)
{
    bool nullState = (bool) ParseValue<uint32_t>(stream);

    if (!nullState) {
        bool onOff = (bool) ParseValue<uint32_t>(stream);
        uint32_t hue = ParseValue<uint32_t>(stream);
        uint32_t saturation = ParseValue<uint32_t>(stream);
        uint32_t colorTemp = ParseValue<uint32_t>(stream);
        uint32_t brightness = ParseValue<uint32_t>(stream);
        state = LampState(onOff, hue, saturation, colorTemp, brightness);
        //QCC_DbgPrintf(("%s: Parsed State = %s", __func__, state.c_str()));
    } else {
        state = LampState();
        QCC_DbgPrintf(("%s: Parsed Null State", __func__));
    }
}

std::string ParseString(std::istream& stream)
{
    std::string name;
    stream >> name;

    if (name[0] == '"') {
        name = name.substr(1, std::string::npos);

        while (name[name.length() - 1] != '"') {
            std::string s;
            stream >> s;
            name += ' ' + s;
        }

        if (name[name.length() - 1] == '"') {
            name = name.substr(0, name.length() - 1);
        }
    }

    return name;
}

std::ostream& WriteValue(std::ostream& stream, const std::string& name)
{
    stream << name;
    return stream;
}

std::ostream& WriteString(std::ostream& stream, const std::string& name)
{
    stream << '"' << name << '"';
    return stream;
}

OPTIONAL_NAMESPACE_CLOSE
}
