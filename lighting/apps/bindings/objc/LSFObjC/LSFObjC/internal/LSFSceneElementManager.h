/******************************************************************************
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

#import <Foundation/Foundation.h>
#import "LSFObject.h"
#import "LSFControllerClient.h"
#import "LSFSceneElementManagerCallbackDelegate.h"
#import "LSFSceneElement.h"

@interface LSFSceneElementManager : LSFObject

-(id)initWithControllerClient: (LSFControllerClient *)controllerClient andSceneElementManagerCallbackDelegate: (id<LSFSceneElementManagerCallbackDelegate>)semDelegate;
-(ControllerClientStatus)getAllSceneElementIDs;
-(ControllerClientStatus)getSceneElementNameWithID: (NSString *)sceneElementID;
-(ControllerClientStatus)getSceneElementNameWithID: (NSString *)sceneElementID andLanguage: (NSString *)language;
-(ControllerClientStatus)setSceneElementNameWithID: (NSString *)sceneElementID andSceneElementName: (NSString *)sceneElementName;
-(ControllerClientStatus)setSceneElementNameWithID: (NSString *)sceneElementID sceneElementName: (NSString *)sceneElementName andLanguage: (NSString *)language;
-(ControllerClientStatus)createSceneElementWithTracking: (uint32_t *)trackingID sceneElement: (LSFSceneElement *)sceneElement andSceneElementName: (NSString *)sceneElementName;
-(ControllerClientStatus)createSceneElementWithTracking: (uint32_t *)trackingID sceneElement: (LSFSceneElement *)sceneElement sceneElementName: (NSString *)sceneElementName andLanguage: (NSString *)language;
-(ControllerClientStatus)updateSceneElementWithID: (NSString *)sceneElementID withSceneElement: (LSFSceneElement *)sceneElement;
-(ControllerClientStatus)deleteSceneElementWithID: (NSString *)sceneElementID;
-(ControllerClientStatus)getSceneElementWithID: (NSString *)sceneElementID;
-(ControllerClientStatus)applySceneElementWithID: (NSString *)sceneElementID;
-(ControllerClientStatus)getSceneElementDataWithID: (NSString *)sceneElementID;
-(ControllerClientStatus)getSceneElementDataWithID: (NSString *)sceneElementID andLanguage: (NSString *)language;

@end
