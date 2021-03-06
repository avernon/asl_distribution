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
/**
 * @file
 *
 * This file implements methods from the ERConfig class.
 */

/******************************************************************************
 *
 *
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
#include <map>
#include <stdio.h>

#include <qcc/Debug.h>
#include <qcc/Config.h>
#include <qcc/Environ.h>
#include <qcc/FileStream.h>
#include <qcc/String.h>
#include <qcc/StringUtil.h>

#include <Status.h>

#define QCC_MODULE "CONFIG"

using namespace std;
using namespace qcc;

Config::Config(void)
{
    /** Config file name */

    String iniFileResolved = "ER_INI.dat";

    Environ* env = Environ::GetAppEnviron();

    String dir = env->Find("splicehomedir");
    if (dir.empty()) {
        dir = env->Find("SPLICEHOMEDIR");
    }

#if !defined(NDEBUG)
    // Allow testing using a config file in the current directory.
    // Env var value is insignificant, just existence.
    if (env->Find("SPLICECONFIGINCURRENTDIR").empty() && !dir.empty()) {
        iniFileResolved = dir + "/" + iniFileResolved;
    }
#endif

    FileSource iniSource(iniFileResolved);

    if (!iniSource.IsValid()) {
        QCC_LogError(ER_FAIL, ("Unable to open config file %s", iniFileResolved.c_str()));
        // use defaults...
        // ...
    } else {
        String line;
        while (ER_OK == iniSource.GetLine(line)) {
            size_t pos = line.find_first_of(';');
            if (String::npos != pos) {
                line = line.substr(0, pos);
            }
            pos = line.find_first_of('=');
            if (String::npos != pos && (line.length() >= pos + 2)) {
                String key = Trim(line.substr(0, pos));
                String val = Trim(line.substr(pos + 1, String::npos));
                nameValuePairs[key] = val;
            }
            line.clear();
        }
    }
}
