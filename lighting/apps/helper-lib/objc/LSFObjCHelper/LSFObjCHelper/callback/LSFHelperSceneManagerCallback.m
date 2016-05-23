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

#import "LSFHelperSceneManagerCallback.h"
#import "LSFSceneModelContainer.h"
#import "LSFSceneDataModel.h"
#import "LSFAllJoynManager.h"
#import "LSFDispatchQueue.h"
#import "LSFEnums.h"
#import "LSFSDKSceneV1.h"

@interface LSFHelperSceneManagerCallback()

@property (nonatomic, strong) dispatch_queue_t queue;

-(void)postProcessSceneID: (NSString *)sceneID;
-(void)postUpdateSceneID: (NSString *)sceneID;
-(void)postUpdateScene: (NSString *)sceneID withName: (NSString *)sceneName;
-(void)postDeleteScenes: (NSArray *)sceneIDs;
-(void)postUpdateScene:(NSString *)sceneID withScene:(LSFScene *)scene;
-(void)updateSceneWithID: (NSString *)sceneID andCallbackOperation: (SceneCallbackOperation)callbackOp;

@end

@implementation LSFHelperSceneManagerCallback

@synthesize queue = _queue;

-(id)init
{
    self = [super init];

    if (self)
    {
        self.queue = ([LSFDispatchQueue getDispatchQueue]).queue;
    }

    return self;
}

/*
 * Implementation of LSFSceneManagerCallbackDelegate
 */
-(void)getAllSceneIDsReplyWithCode: (LSFResponseCode)rc andSceneIDs: (NSArray *)sceneIDs
{
    NSLog(@"LSFHelperSceneManagerCallback - getAllSceneIDsReply() count = %lu", (unsigned long)sceneIDs.count);

    if (rc != LSF_OK)
    {
        NSLog(@"getAllSceneIDsReply() returned error %@", [NSString stringWithUTF8String: LSFResponseCodeText(rc)]);
    }

    dispatch_async(self.queue, ^{
        for (NSString *sceneID in sceneIDs)
        {
            [self postProcessSceneID: sceneID];
        }
    });
}

-(void)getSceneNameReplyWithCode: (LSFResponseCode)rc sceneID: (NSString *)sceneID language: (NSString *)language andName: (NSString *)sceneName
{
    NSLog(@"LSFHelperSceneManagerCallback - getSceneNameReplyWithCode()");

    if (rc != LSF_OK)
    {
        NSLog(@"getSceneNameReplyWithCode() returned error %@", [NSString stringWithUTF8String: LSFResponseCodeText(rc)]);
    }

    dispatch_async(self.queue, ^{
        [self postUpdateScene: sceneID withName: sceneName];
    });
}

-(void)getSceneVersionReplyWithCode: (LSFResponseCode)rc sceneID: (NSString *)sceneID andSceneVersion: (unsigned int)sceneVersion
{
    if (rc != LSF_OK)
    {
        NSLog(@"getSceneVersionReplyWithCode() returned error %@", [NSString stringWithUTF8String: LSFResponseCodeText(rc)]);
    }

    //TODO - implement if needed
}

-(void)setSceneNameReplyWithCode: (LSFResponseCode)rc sceneID: (NSString *)sceneID andLanguage: (NSString *)language
{
    NSLog(@"LSFHelperSceneManagerCallback - setSceneNameReplyWithCode()");

    if (rc != LSF_OK)
    {
        NSLog(@"setSceneNameReplyWithCode() returned error %@", [NSString stringWithUTF8String: LSFResponseCodeText(rc)]);
    }

    dispatch_async(self.queue, ^{
        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
        [ajManager.lsfSceneManager getSceneNameWithID: sceneID];
    });
}

-(void)scenesNameChanged: (NSArray *)sceneIDs
{
    NSLog(@"LSFHelperSceneManagerCallback - scenesNameChanged()");

    dispatch_async(self.queue, ^{
        BOOL containsNewSceneIDs = NO;
        LSFSceneModelContainer *container = [LSFSceneModelContainer getSceneModelContainer];
        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];

        for (NSString *sceneID in sceneIDs)
        {
            LSFSceneDataModel *model = [container.sceneContainer objectForKey: sceneID];

            if (model != nil)
            {
                [ajManager.lsfSceneManager getSceneNameWithID: sceneID];
            }
            else
            {
                containsNewSceneIDs = YES;
            }
        }

        if (containsNewSceneIDs)
        {
            [ajManager.lsfSceneManager getAllSceneIDs];
        }
    });
}

-(void)createSceneReplyWithCode: (LSFResponseCode)rc andSceneID: (NSString *)sceneID
{
    NSLog(@"LSFHelperSceneManagerCallback - createSceneReplyWithCode()");

    if (rc != LSF_OK)
    {
        NSLog(@"createSceneReplyWithCode() returned error %@", [NSString stringWithUTF8String: LSFResponseCodeText(rc)]);
    }

    dispatch_async(self.queue, ^{
        [self postProcessSceneID: sceneID];
    });
}

-(void)createSceneTrackingReplyWithCode: (LSFResponseCode)rc sceneID: (NSString *)sceneID andTrackingID: (unsigned int)trackingID
{
    NSLog(@"LSFHelperSceneManagerCallback - createSceneTrackingReplyWithCode()");

    if (rc != LSF_OK)
    {
        NSLog(@"createSceneTrackingReplyWithCode() returned error %@", [NSString stringWithUTF8String: LSFResponseCodeText(rc)]);
    }

    dispatch_async(self.queue, ^{
        [self postProcessSceneID: sceneID];
    });
}

-(void)createSceneWithSceneElementsReplyWithCode: (LSFResponseCode)rc sceneID: (NSString *)sceneID andTrackingID: (unsigned int)trackingID
{
    //TODO - implement when sceneWithSceneElements is implemented
}

-(void)scenesCreated: (NSArray *)sceneIDs
{
    NSLog(@"LSFHelperSceneManagerCallback - scenesCreated()");

    dispatch_async(self.queue, ^{
        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
        [ajManager.lsfSceneManager getAllSceneIDs];
    });
}

-(void)updateSceneReplyWithCode: (LSFResponseCode)rc andSceneID: (NSString *)sceneID
{
    NSLog(@"LSFHelperSceneManagerCallback - updateSceneReplyWithCode()");

    if (rc != LSF_OK)
    {
        NSLog(@"updateSceneReplyWithCode() returned error %@", [NSString stringWithUTF8String: LSFResponseCodeText(rc)]);
    }
}

-(void)updateSceneWithSceneElementsReplyWithCode: (LSFResponseCode)rc andSceneID: (NSString *)sceneID
{
    //TODO - implement when sceneWithSceneElements is implemented
}

-(void)scenesUpdated: (NSArray *)sceneIDs
{
    NSLog(@"LSFHelperSceneManagerCallback - scenesUpdated()");

    dispatch_async(self.queue, ^{
        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];

        for (NSString *sceneID in sceneIDs)
        {
            [ajManager.lsfSceneManager getSceneWithID: sceneID];
        }
    });
}

-(void)deleteSceneReplyWithCode: (LSFResponseCode)rc andSceneID: (NSString *)sceneID
{
    NSLog(@"LSFHelperSceneManagerCallback - deleteSceneReplyWithCode()");

    if (rc != LSF_OK)
    {
        NSLog(@"deleteSceneReplyWithCode() returned error %@", [NSString stringWithUTF8String: LSFResponseCodeText(rc)]);
    }
}

-(void)scenesDeleted: (NSArray *)sceneIDs
{
    NSLog(@"LSFHelperSceneManagerCallback - scenesDeleted()");

    dispatch_async(self.queue, ^{
        [self postDeleteScenes: sceneIDs];
    });
}

-(void)getSceneReplyWithCode: (LSFResponseCode)rc sceneID: (NSString *)sceneID andScene: (LSFScene *)scene
{
    NSLog(@"LSFHelperSceneManagerCallback - getSceneReplyWithCode()");

    if (rc != LSF_OK)
    {
        NSLog(@"getSceneReplyWithCode() returned error %@", [NSString stringWithUTF8String: LSFResponseCodeText(rc)]);
    }

    dispatch_async(self.queue, ^{
        [self postUpdateScene: sceneID withScene: scene];
    });
}

-(void)getSceneWithSceneElementsReplyWithCode: (LSFResponseCode)rc sceneID: (NSString *)sceneID andSceneWithSceneElements: (LSFSceneWithSceneElements *)sceneWithSceneElements
{
    //TODO - implement when sceneWithSceneElements is implemented
}

-(void)applySceneReplyWithCode: (LSFResponseCode)rc andSceneID: (NSString *)sceneID
{
    NSLog(@"LSFHelperSceneManagerCallback - applySceneReplyWithCode()");

    if (rc != LSF_OK)
    {
        NSLog(@"applySceneReplyWithCode() returned error %@", [NSString stringWithUTF8String: LSFResponseCodeText(rc)]);
    }
}

-(void)scenesApplied: (NSArray *)sceneIDs
{
    NSLog(@"LSFHelperSceneManagerCallback - scenesApplied()");
    // Method does nothing
}

/*
 * Private Functions
 */
-(void)postProcessSceneID: (NSString *)sceneID
{
    NSMutableDictionary *scenes = [[LSFSceneModelContainer getSceneModelContainer] sceneContainer];
    LSFSDKSceneV1 *scene = [scenes valueForKey: sceneID];

    if (scene == nil)
    {
        //NSLog(@"Scene ID not found creating scene model");
        [self postUpdateSceneID: sceneID];

        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
        [ajManager.lsfSceneManager getSceneNameWithID: sceneID];
        [ajManager.lsfSceneManager getSceneWithID: sceneID];
    }
}

-(void)postUpdateSceneID: (NSString *)sceneID
{
    //LSFSceneModelContainer *container = [LSFSceneModelContainer getSceneModelContainer];
    //LSFSceneDataModel *sceneModel = [container.sceneContainer valueForKey: sceneID];

    NSMutableDictionary *scenes = [[LSFSceneModelContainer getSceneModelContainer] sceneContainer];
    LSFSDKSceneV1 *scene = [scenes valueForKey: sceneID];

    if (scene == nil)
    {
        scene = [[LSFSDKSceneV1 alloc] initWithSceneID: sceneID];
        [scenes setValue: scene forKey: sceneID];

        dispatch_async(dispatch_get_main_queue(), ^{
            [[NSNotificationCenter defaultCenter] postNotificationName: @"UpdateScenes" object: self userInfo: nil];
        });
    }

    [self updateSceneWithID: sceneID andCallbackOperation: SceneCreated];
}

-(void)postUpdateScene: (NSString *)sceneID withName: (NSString *)sceneName
{
    NSMutableDictionary *scenes = [[LSFSceneModelContainer getSceneModelContainer] sceneContainer];
    LSFSceneDataModel *sceneModel = [[scenes valueForKey: sceneID] getSceneDataModel];

    if (sceneModel != nil)
    {
        sceneModel.name = sceneName;
        NSLog(@"SceneModel Name = %@", sceneModel.name);
    }

    [self updateSceneWithID: sceneID andCallbackOperation: SceneNameUpdated];
}

-(void)postUpdateScene:(NSString *)sceneID withScene:(LSFScene *)scene
{
    NSMutableDictionary *scenes = [[LSFSceneModelContainer getSceneModelContainer] sceneContainer];
    LSFSceneDataModel *sceneModel = [[scenes valueForKey: sceneID] getSceneDataModel];

    if (sceneModel != nil)
    {
        [sceneModel fromScene: scene];
    }

    [self updateSceneWithID: sceneID andCallbackOperation: SceneUpdated];
}

-(void)postDeleteScenes: (NSArray *)sceneIDs
{
    NSMutableArray *sceneNames = [[NSMutableArray alloc] init];
    NSMutableDictionary *scenes = [[LSFSceneModelContainer getSceneModelContainer] sceneContainer];

    for (int i = 0; i < sceneIDs.count; i++)
    {
        NSString *sceneID = [sceneIDs objectAtIndex: i];
        LSFSceneDataModel *model = [[scenes valueForKey: sceneID] getSceneDataModel];

        [sceneNames insertObject: model.name atIndex: i];
        [scenes removeObjectForKey: sceneID];

        dispatch_async(dispatch_get_main_queue(), ^{
            [[NSNotificationCenter defaultCenter] postNotificationName: @"UpdateScenes" object: self userInfo: nil];
        });
    }

    dispatch_async(dispatch_get_main_queue(), ^{
        NSNumber *sceneOp = [[NSNumber alloc] initWithInt: SceneDeleted];
        NSDictionary *userInfoDict = [[NSDictionary alloc] initWithObjects: [[NSArray alloc] initWithObjects: sceneOp, sceneIDs, [NSArray arrayWithArray: sceneNames], nil] forKeys: [[NSArray alloc] initWithObjects: @"operation", @"sceneIDs", @"sceneNames", nil]];
        [[NSNotificationCenter defaultCenter] postNotificationName: @"SceneNotification" object: self userInfo: userInfoDict];
    });
}

-(void)updateSceneWithID: (NSString *)sceneID andCallbackOperation: (SceneCallbackOperation)callbackOp
{
    dispatch_async(dispatch_get_main_queue(), ^{
        NSNumber *sceneOp = [[NSNumber alloc] initWithInt: callbackOp];
        NSDictionary *userInfoDict = [[NSDictionary alloc] initWithObjects: [[NSArray alloc] initWithObjects: sceneOp, sceneID, nil] forKeys: [[NSArray alloc] initWithObjects: @"operation", @"sceneID", nil]];
        [[NSNotificationCenter defaultCenter] postNotificationName: @"SceneNotification" object: self userInfo: userInfoDict];
    });
}

@end
