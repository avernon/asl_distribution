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
 *
 ******************************************************************************/
#ifndef _LSF_ALLJOYN_JAVA_TYPES_H
#define _LSF_ALLJOYN_JAVA_TYPES_H

#include <LSFTypes.h>   // lighting/service_framework

namespace lsf {
//typedef LSFString LampID;
typedef LSFString LampGroupID;
//typedef LSFString SavedStateID;
//typedef LSFString SceneID;

//typedef LSFStringList LampIDList;
typedef LSFStringList LampGroupIDList;
//typedef LSFStringList SavedStateIDList;
//typedef LSFStringList SceneIDList;
//typedef LSFStringList LanguageCodeList;

//typedef LSFString LampName;
typedef LSFString LampGroupName;
//typedef LSFString ManufacturerName;
//typedef LSFString StateFieldName;

//typedef LSFString DeviceID;
//typedef LSFString ServiceName;
//typedef LSFString LanguageCode;

typedef std::list<uint32_t> UInt32List;
typedef std::list<uint32_t> EnumList;
}

#endif /* _LSF_ALLJOYN_JAVA_TYPES_H */
