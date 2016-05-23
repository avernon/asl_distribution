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

#include <LSFResponseCodes.h>
#include <LSFTypes.h>

namespace lsf {

const char* LSFResponseCodeText(LSFResponseCode responseCode)
{
    switch (responseCode) {
        LSF_CASE(LSF_OK);
        LSF_CASE(LSF_ERR_NULL);
        LSF_CASE(LSF_ERR_UNEXPECTED);
        LSF_CASE(LSF_ERR_INVALID);
        LSF_CASE(LSF_ERR_UNKNOWN);
        LSF_CASE(LSF_ERR_FAILURE);
        LSF_CASE(LSF_ERR_BUSY);
        LSF_CASE(LSF_ERR_REJECTED);
        LSF_CASE(LSF_ERR_RANGE);
        LSF_CASE(LSF_ERR_INVALID_FIELD);
        LSF_CASE(LSF_ERR_MESSAGE);
        LSF_CASE(LSF_ERR_INVALID_ARGS);
        LSF_CASE(LSF_ERR_EMPTY_NAME);
        LSF_CASE(LSF_ERR_RESOURCES);
        LSF_CASE(LSF_ERR_REPLY_WITH_INVALID_ARGS);
        LSF_CASE(LSF_ERR_PARTIAL);
        LSF_CASE(LSF_ERR_NOT_FOUND);
        LSF_CASE(LSF_ERR_NO_SLOT);
        LSF_CASE(LSF_ERR_DEPENDENCY);
        LSF_CASE(LSF_RESPONSE_CODE_LAST);

    default:
        return "<unknown>";
    }
}

}
