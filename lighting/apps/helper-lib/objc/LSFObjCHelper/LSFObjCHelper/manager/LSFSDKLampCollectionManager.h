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

#import "LSFSDKLightingItemCollectionManager.h"
#import "LSFSDKLamp.h"
#import "LSFSDKLampDelegate.h"


@interface LSFSDKLampCollectionManager : LSFSDKLightingItemCollectionManager
{
    @protected NSMutableArray *lampIDs;
}

-(id)initWithLightingSystemManager: (LSFSDKLightingSystemManager *)lightingSystemManager;
-(void)addLampDelegate: (id<LSFSDKLampDelegate>)lampDelegate;
-(void)removeLampDelegate: (id<LSFSDKLampDelegate>)lampDelegate;
-(LSFSDKLamp *)addLampWithID: (NSString *)lampID;
-(LSFSDKLamp *)addLampWithID: (NSString *)lampID lamp: (LSFSDKLamp *)lamp;
-(LSFSDKLamp *)getLampWithID: (NSString *)lampID;
-(NSArray *)getLamps;
-(NSArray *)getLampsWithFilter: (id<LSFSDKLightingItemFilter>)filter;
-(NSArray *)getLampsCollectionWithFilter: (id<LSFSDKLightingItemFilter>)filter;
-(NSArray *)removeAllLamps;
-(LSFSDKLamp *)removeLampWithID: (NSString *)lampID;
-(LSFLampModel *)getModelWithID: (NSString *)lampID;

@end
