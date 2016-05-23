/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

#include "IniParser.h"
#include <fstream>

IniParser::IniParser()
{
}

IniParser::~IniParser()
{
}

std::string IniParser::trim(const std::string& str,
                            const std::string& whitespace)
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos) {
        return "";  // no content

    }
    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

bool IniParser::ParseFile(std::string const& fileName, std::map<std::string, std::string>& data)
{
    std::ifstream iniFile(fileName.c_str(), std::ifstream::in);
    if (!iniFile.is_open()) {
        return false;
    }

    std::string line;
    int lineNum = 0;
    while (std::getline(iniFile, line)) {

        lineNum++;
        line = trim(line); // remove leading and trailing whitespaces

        if (!line.length()) {
            continue;      // empty line skip

        }
        if (line[0] == '#') {
            continue;      // commented line skip

        }
        std::size_t found = line.find('=');
        if (found == std::string::npos) {
            std::cout << "Problem reading line: " << lineNum << std::endl;
            continue;
        }

        std::string name = line.substr(0, found);
        name = trim(name); // remove leading and trailing whitespaces

        std::string value = line.substr(found + 1);
        value = trim(value);

        data[name] = value;
    }

    iniFile.close();
    return true;
}

bool IniParser::UpdateFile(std::string const& fileName, std::map<std::string, std::string> const& data)
{
    std::ifstream iniFile(fileName.c_str(), std::ifstream::in);
    if (!iniFile.is_open()) {
        return false;
    }

    std::string origline;
    std::string content = "";
    int lineNum = 0;
    while (std::getline(iniFile, origline)) {

        lineNum++;
        std::string line = trim(origline); // remove leading and trailing whitespaces

        if (!line.length()) {
            content.append(origline + "\n");
            continue;      // empty line skip
        }

        if (line[0] == '#') {
            content.append(origline + "\n");
            continue;      // commented line skip
        }

        std::size_t found = line.find('=');
        if (found == std::string::npos) {
            std::cout << "Problem reading line: " << lineNum << std::endl;
            content.append(origline + "\n");
            continue;
        }

        std::string name = line.substr(0, found);
        name = trim(name); // remove leading and trailing whitespaces

        std::map<std::string, std::string>::const_iterator iter = data.find(name);
        if (iter == data.end()) {
            content.append(origline + "\n");
            continue;
        }

        std::string newline = name + " = " + iter->second;
        content.append(newline + "\n");
    }

    iniFile.close();

    std::ofstream iniFileWrite(fileName.c_str(), std::ofstream::out | std::ofstream::trunc);
    iniFileWrite.write(content.c_str(), content.length());
    iniFileWrite.close();

    return true;
}
