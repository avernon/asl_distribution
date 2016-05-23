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

#include <iostream>
#include "TestFunction.h"

using namespace qcc;

TestFunction::TestFunction() : activateTest(0)
{
}

TestFunction::~TestFunction()
{
}

bool TestFunction::checkRequiredParams(std::map<qcc::String, qcc::String>& params)
{
    if (requiredParams.size() == 0) {
        return true;
    }

    for (std::vector<qcc::String>::const_iterator reqParams_it = requiredParams.begin(); reqParams_it != requiredParams.end(); ++reqParams_it) {
        if (params.find(*reqParams_it) == params.end()) {
            std::cout << "Missing required parameter " << reqParams_it->c_str() << std::endl;
            std::cout << usage.c_str() << std::endl;
            return false;
        }
    }
    return true;
}

void TestFunction::checkOptionalParams(std::map<qcc::String, qcc::String>& params)
{
    for (std::map<qcc::String, qcc::String>::const_iterator params_it = params.begin(); params_it != params.end(); ++params_it) {
        if (find(optionalParams.begin(), optionalParams.end(), params_it->first) == optionalParams.end()) {
            if (find(requiredParams.begin(), requiredParams.end(), params_it->first) == requiredParams.end()) {
                // Element is NOT in either vector so let the user know
                std::cout << "Parameter " << params_it->first.c_str() << " is not a valid parameter for " <<
                functionName.c_str() << ". Ignoring value" << std::endl;
            }
        }
    }
}

