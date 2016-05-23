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

#ifndef TESTFUNCTION_H_
#define TESTFUNCTION_H_

#include <algorithm>
#include <map>
#include <vector>
#include <qcc/String.h>

/**
 * TestFunction class used to represent on of the possible API calls
 * in the TestService application
 */
class TestFunction {
  public:

    /**
     * Constructor
     */
    TestFunction();

    /**
     * Destructor
     */
    virtual ~TestFunction();

    /**
     * Validate that required params were added
     * @param params
     * @return true/false
     */
    bool checkRequiredParams(std::map<qcc::String, qcc::String>& params);

    /**
     * Check the optional parameters
     * @param params
     */
    void checkOptionalParams(std::map<qcc::String, qcc::String>& params);

    /**
     * The name of the function
     */
    qcc::String functionName;

    /**
     * The usage string
     */
    qcc::String usage;

    /**
     * The required Parameters
     */
    std::vector<qcc::String> requiredParams;

    /**
     * The optional Parameters
     */
    std::vector<qcc::String> optionalParams;

    /**
     * Preconditions - steps that need to be taken before this API call
     */
    std::vector<qcc::String> requiredSteps;

    /**
     * functionPointer to function that will execute the API call
     * @param params
     * @return
     */
    bool (*activateTest)(std::map<qcc::String, qcc::String>& params);
};

#endif /* TESTFUNCTION_H_ */
