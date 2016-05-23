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

#ifndef _LSF_HANDLE_H
#define _LSF_HANDLE_H

#import <Foundation/Foundation.h>

/**
 * Type definition for the LSFHandle, which is used to refer to C++ API objects.
 */
typedef void* LSFHandle;

/**
 * The objective-c base class that serves as a wrapper for a C++ API class. The instance
 * of the C++ API object is maintained in the handle property.
 */
@protocol LSFHandle <NSObject>

/**
 * Holds a pointer to a C++ API object.
 */
@property (nonatomic, assign) LSFHandle handle;

@end

#endif /* defined(_LSF_HANDLE_H) */