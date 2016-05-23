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

#import "LSFSampleSceneManagerCallback.h"
#import "LSFSceneModelContainer.h"
#import "LSFSceneDataModel.h"
#import "LSFAllJoynManager.h"
#import "LSFDispatchQueue.h"
#import "LSFTabManager.h"
#import "LSFEnums.h"

@interface LSFSampleSceneManagerCallback()

@property (nonatomic, strong) dispatch_queue_t queue;

-(void)postProcessSceneID: (NSString *)sceneID;
-(void)postUpdateSceneID: (NSString *)sceneID;
-(void)postUpdateScene: (NSString *)sceneID withName: (NSString *)sceneName;
-(void)postDeleteScenes: (NSArray *)sceneIDs;
-(void)postUpdateScene:(NSString *)sceneID withScene:(LSFScene *)scene;
-(void)updateSceneWithID: (NSString *)sceneID andCallbackOperation: (SceneCallbackOperation)callbackOp;

@end

@implementation LSFSampleSceneManagerCallback

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
    if (rc != LSF_OK)
    {
        //TODO - do something
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
    if (rc != LSF_OK)
    {
        //TODO - do something
    }

    dispatch_async(self.queue, ^{
        [self postUpdateScene: sceneID withName: sceneName];
    });
}

-(void)setSceneNameReplyWithCode: (LSFResponseCode)rc sceneID: (NSString *)sceneID andLanguage: (NSString *)language
{
    if (rc != LSF_OK)
    {
        //TODO - do something
    }

    dispatch_async(self.queue, ^{
        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
        [ajManager.lsfSceneManager getSceneNameWithID: sceneID];
    });
}

-(void)scenesNameChanged: (NSArray *)sceneIDs
{
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
    if (rc != LSF_OK)
    {
        //TODO - do something
    }

    dispatch_async(self.queue, ^{
        [self postProcessSceneID: sceneID];
    });
}

-(void)scenesCreated: (NSArray *)sceneIDs
{
    dispatch_async(self.queue, ^{
        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
        [ajManager.lsfSceneManager getAllSceneIDs];
    });
}

-(void)updateSceneReplyWithCode: (LSFResponseCode)rc andSceneID: (NSString *)sceneID
{
    if (rc != LSF_OK)
    {
        //TODO - do something
    }
}

-(void)scenesUpdated: (NSArray *)sceneIDs
{
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
    if (rc != LSF_OK)
    {
        //TODO - do something
    }
}

-(void)scenesDeleted: (NSArray *)sceneIDs
{
    dispatch_async(self.queue, ^{
        [self postDeleteScenes: sceneIDs];
    });
}

-(void)getSceneReplyWithCode: (LSFResponseCode)rc sceneID: (NSString *)sceneID andScene: (LSFScene *)scene
{
    if (rc != LSF_OK)
    {
        //TODO - do something
    }

    dispatch_async(self.queue, ^{
        [self postUpdateScene: sceneID withScene: scene];
    });
}

-(void)applySceneReplyWithCode: (LSFResponseCode)rc andSceneID: (NSString *)sceneID
{
    if (rc != LSF_OK)
    {
        //TODO - do something
    }
}

-(void)scenesApplied: (NSArray *)sceneIDs
{
    // Method does nothing
}

/*
 * Private Functions
 */
-(void)postProcessSceneID: (NSString *)sceneID
{
    LSFSceneModelContainer *container = [LSFSceneModelContainer getSceneModelContainer];
    LSFSceneDataModel *sceneModel = [container.sceneContainer valueForKey: sceneID];

    if (sceneModel == nil)
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
    LSFSceneModelContainer *container = [LSFSceneModelContainer getSceneModelContainer];
    LSFSceneDataModel *sceneModel = [container.sceneContainer valueForKey: sceneID];

    if (sceneModel == nil)
    {
        sceneModel = [[LSFSceneDataModel alloc] initWithSceneID: sceneID];
        [container.sceneContainer setValue: sceneModel forKey: sceneID];

        dispatch_async(self.queue, ^{
            LSFTabManager *tabManager = [LSFTabManager getTabManager];
            [tabManager updateScenesTab];
        });
    }

    [self updateSceneWithID: sceneID andCallbackOperation: SceneCreated];
}

-(void)postUpdateScene: (NSString *)sceneID withName: (NSString *)sceneName
{
    LSFSceneModelContainer *container = [LSFSceneModelContainer getSceneModelContainer];
    LSFSceneDataModel *sceneModel = [container.sceneContainer valueForKey: sceneID];

    if (sceneModel != nil)
    {
        sceneModel.name = sceneName;
    }

    [self updateSceneWithID: sceneID andCallbackOperation: SceneNameUpdated];
}

-(void)postUpdateScene:(NSString *)sceneID withScene:(LSFScene *)scene
{
    LSFSceneModelContainer *container = [LSFSceneModelContainer getSceneModelContainer];
    LSFSceneDataModel *sceneModel = [container.sceneContainer valueForKey: sceneID];

    if (sceneModel != nil)
    {
        [sceneModel fromScene: scene];
    }

    [self updateSceneWithID: sceneID andCallbackOperation: SceneUpdated];
}

-(void)postDeleteScenes: (NSArray *)sceneIDs
{
    NSMutableArray *sceneNames = [[NSMutableArray alloc] init];
    NSMutableDictionary *scenes = ((LSFSceneModelContainer *)[LSFSceneModelContainer getSceneModelContainer]).sceneContainer;

    for (int i = 0; i < sceneIDs.count; i++)
    {
        NSString *sceneID = [sceneIDs objectAtIndex: i];
        LSFSceneDataModel *model = [scenes valueForKey: sceneID];

        [sceneNames insertObject: model.name atIndex: i];
        [scenes removeObjectForKey: sceneID];

        dispatch_async(self.queue, ^{
            LSFTabManager *tabManager = [LSFTabManager getTabManager];
            [tabManager updateScenesTab];
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
