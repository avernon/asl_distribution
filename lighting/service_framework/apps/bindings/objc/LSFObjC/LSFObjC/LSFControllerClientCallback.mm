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

#import "LSFControllerClientCallback.h"

LSFControllerClientCallback::LSFControllerClientCallback(id<LSFControllerClientCallbackDelegate> delegate) : _ccDelegate(delegate)
{
    //Empty constructor
}

LSFControllerClientCallback::~LSFControllerClientCallback()
{
    _ccDelegate = nil;
}

void LSFControllerClientCallback::ConnectedToControllerServiceCB(const LSFString& controllerServiceDeviceID, const LSFString& controllerServiceName)
{
    [_ccDelegate connectedToControllerServiceWithID: [NSString stringWithUTF8String: controllerServiceDeviceID.c_str()] andName:[NSString stringWithUTF8String: controllerServiceName.c_str()]];
}

void LSFControllerClientCallback::ConnectToControllerServiceFailedCB(const LSFString& controllerServiceDeviceID, const LSFString& controllerServiceName)
{
    [_ccDelegate connectToControllerServiceFailedForID: [NSString stringWithUTF8String: controllerServiceDeviceID.c_str()] andName: [NSString stringWithUTF8String: controllerServiceName.c_str()]];
}

void LSFControllerClientCallback::DisconnectedFromControllerServiceCB(const LSFString& controllerServiceDeviceID, const LSFString& controllerServiceName)
{
    [_ccDelegate disconnectedFromControllerServiceWithID: [NSString stringWithUTF8String: controllerServiceDeviceID.c_str()] andName: [NSString stringWithUTF8String: controllerServiceName.c_str()]];
}

void LSFControllerClientCallback::ControllerClientErrorCB(const ErrorCodeList& errorCodeList)
{
    NSMutableArray *errorCodesArray = [[NSMutableArray alloc] init];
    
    for (std::list<ErrorCode>::const_iterator iter = errorCodeList.begin(); iter != errorCodeList.end(); ++iter)
    {
        [errorCodesArray addObject: [NSNumber numberWithInt: (*iter)]];
    }
    
    [_ccDelegate controllerClientError: errorCodesArray];
}