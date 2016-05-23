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

#import "LSFSampleMasterSceneManagerCallback.h"
#import "LSFDispatchQueue.h"
#import "LSFAllJoynManager.h"
#import "LSFMasterSceneModelContainer.h"
#import "LSFMasterSceneDataModel.h"
#import "LSFTabManager.h"
#import "LSFEnums.h"

@interface LSFSampleMasterSceneManagerCallback()

@property (nonatomic, strong) dispatch_queue_t queue;

-(void)postProcessMasterSceneID: (NSString *)masterSceneID;
-(void)postUpdateMasterSceneID: (NSString *)masterSceneID;
-(void)postUpdateMasterScene: (NSString *)masterSceneID withName: (NSString *)masterSceneName;
-(void)postDeleteMasterScenes: (NSArray *)masterSceneIDs;
-(void)postUpdateMasterScene: (NSString *)masterSceneID withMasterScene: (LSFMasterScene *)masterScene;
-(void)updateMasterSceneWithID: (NSString *)masterSceneID andCallbackOperation: (MasterSceneCallbackOperation)callbackOp;

@end

@implementation LSFSampleMasterSceneManagerCallback

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
 * Implementation of LSFMasterSceneManagerCallbackDelegate
 */
-(void)getAllMasterSceneIDsReplyWithCode: (LSFResponseCode)rc andMasterSceneIDs: (NSArray *)masterSceneIDs
{
    //NSLog(@"LSFSampleMasterSceneManagerCallback - getAllMasterSceneIDsReplyCB() executing. Response Code = %i", rc);

    if (rc != LSF_OK)
    {
        //TODO - do something
    }

    dispatch_async(self.queue, ^{
        for (NSString *masterSceneID in masterSceneIDs)
        {
            [self postProcessMasterSceneID: masterSceneID];
        }
    });
}

-(void)getMasterSceneNameReplyWithCode: (LSFResponseCode)rc masterSceneID: (NSString *)masterSceneID language: (NSString *)language andName: (NSString *)masterSceneName
{
    //NSLog(@"LSFSampleMasterSceneManagerCallback - getMasterSceneNameReplyCB() executing. Response Code = %i. Master Scene Name = %@", rc, masterSceneName);

    if (rc != LSF_OK)
    {
        //TODO - do something
    }

    dispatch_async(self.queue, ^{
        [self postUpdateMasterScene: masterSceneID withName: masterSceneName];
    });
}

-(void)setMasterSceneNameReplyWithCode: (LSFResponseCode)rc masterSceneID: (NSString *)masterSceneID andLanguage: (NSString *)language
{
    //NSLog(@"LSFSampleMasterSceneManagerCallback - setMasterSceneNameReplyCB() executing. Response Code = %i", rc);

    if (rc != LSF_OK)
    {
        //TODO - do something
    }

    dispatch_async(self.queue, ^{
        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
        [ajManager.lsfMasterSceneManager getMasterSceneNameWithID: masterSceneID];
    });
}

-(void)masterScenesNameChanged: (NSArray *)masterSceneIDs
{
    //NSLog(@"LSFSampleMasterSceneManagerCallback - masterScenesNameChangedReplyCB() executing");

    dispatch_async(self.queue, ^{
        BOOL containsNewSceneIDs = NO;
        LSFMasterSceneModelContainer *container = [LSFMasterSceneModelContainer getMasterSceneModelContainer];
        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];

        for (NSString *masterSceneID in masterSceneIDs)
        {
            LSFMasterSceneDataModel *model = [container.masterScenesContainer objectForKey: masterSceneID];

            if (model != nil)
            {
                [ajManager.lsfMasterSceneManager getMasterSceneNameWithID: masterSceneID];
            }
            else
            {
                containsNewSceneIDs = YES;
            }
        }

        if (containsNewSceneIDs)
        {
            [ajManager.lsfMasterSceneManager getAllMasterSceneIDs];
        }
    });
}

-(void)createMasterSceneReplyWithCode: (LSFResponseCode)rc andMasterSceneID: (NSString *)masterSceneID
{
    //NSLog(@"LSFSampleMasterSceneManagerCallback - createMasterSceneReplyCB() executing. Response Code = %i", rc);

    if (rc != LSF_OK)
    {
        //TODO - do something
    }

    dispatch_async(self.queue, ^{
        [self postProcessMasterSceneID: masterSceneID];
    });
}

-(void)masterScenesCreated: (NSArray *)masterSceneIDs
{
    //NSLog(@"LSFSampleMasterSceneManagerCallback - masterScenesCreatedReplyCB() executing");

    dispatch_async(self.queue, ^{
        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
        [ajManager.lsfMasterSceneManager getAllMasterSceneIDs];
    });
}

-(void)getMasterSceneReplyWithCode: (LSFResponseCode)rc masterSceneID: (NSString *)masterSceneID andMasterScene: (LSFMasterScene *)masterScene
{
    //NSLog(@"LSFSampleMasterSceneManagerCallback - getMasterSceneReplyCB() executing. Response Code = %i", rc);

    if (rc != LSF_OK)
    {
        //TODO - do something
    }

    dispatch_async(self.queue, ^{
        [self postUpdateMasterScene: masterSceneID withMasterScene: masterScene];
    });
}

-(void)deleteMasterSceneReplyWithCode: (LSFResponseCode)rc andMasterSceneID: (NSString *)masterSceneID
{
    //NSLog(@"LSFSampleMasterSceneManagerCallback - deleteMasterSceneReplyCB() executing. Response Code = %i", rc);

    if (rc != LSF_OK)
    {
        //TODO - do something
    }
}

-(void)masterScenesDeleted: (NSArray *)masterSceneIDs
{
    //NSLog(@"LSFSampleMasterSceneManagerCallback - masterScenesDeletedReplyCB() executing");

    dispatch_async(self.queue, ^{
        [self postDeleteMasterScenes: masterSceneIDs];
    });
}

-(void)updateMasterSceneReplyWithCode: (LSFResponseCode)rc andMasterSceneID: (NSString *)masterSceneID
{
    //NSLog(@"LSFSampleMasterSceneManagerCallback - updateMasterSceneReplyCB() executing. Response Code = %i", rc);

    if (rc != LSF_OK)
    {
        //TODO - do something
    }
}

-(void)masterScenesUpdated: (NSArray *)masterSceneIDs
{
    //NSLog(@"LSFSampleMasterSceneManagerCallback - masterScenesUpdatedReplyCB() executing");

    dispatch_async(self.queue, ^{
        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];

        for (NSString *masterSceneID in masterSceneIDs)
        {
            [ajManager.lsfMasterSceneManager getMasterSceneWithID: masterSceneID];
        }
    });
}

-(void)applyMasterSceneReplyWithCode: (LSFResponseCode)rc andMasterSceneID: (NSString *)masterSceneID
{
    //NSLog(@"LSFSampleMasterSceneManagerCallback - applyMasterSceneReplyCB() executing. Response Code = %i", rc);

    if (rc != LSF_OK)
    {
        //TODO - do something
    }
}

-(void)masterScenesApplied: (NSArray *)masterSceneIDs
{
    //NSLog(@"LSFSampleSceneManagerCallback - masterScenesAppliedReplyCB() executing");
}

/*
 * Private Functions
 */
-(void)postProcessMasterSceneID: (NSString *)masterSceneID
{
    //NSLog(@"postProcessMasterSceneID(): %@", masterSceneID);

    LSFMasterSceneModelContainer *container = [LSFMasterSceneModelContainer getMasterSceneModelContainer];
    LSFMasterSceneDataModel *masterSceneModel = [container.masterScenesContainer valueForKey: masterSceneID];

    if (masterSceneModel == nil)
    {
        //NSLog(@"Master Scene ID not found creating master scene model");
        [self postUpdateMasterSceneID: masterSceneID];

        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
        [ajManager.lsfMasterSceneManager getMasterSceneNameWithID: masterSceneID];
        [ajManager.lsfMasterSceneManager getMasterSceneWithID: masterSceneID];
    }
}

-(void)postUpdateMasterSceneID: (NSString *)masterSceneID
{
    //NSLog(@"postUpdateMasterSceneID(): %@", masterSceneID);

    LSFMasterSceneModelContainer *container = [LSFMasterSceneModelContainer getMasterSceneModelContainer];
    LSFMasterSceneDataModel *masterSceneModel = [container.masterScenesContainer valueForKey: masterSceneID];

    if (masterSceneModel == nil)
    {
        //NSLog(@"SceneModel not found. Creating scene model for %@", masterSceneID);

        masterSceneModel = [[LSFMasterSceneDataModel alloc] initWithID: masterSceneID];
        [container.masterScenesContainer setValue: masterSceneModel forKey: masterSceneID];

        dispatch_async(self.queue, ^{
            LSFTabManager *tabManager = [LSFTabManager getTabManager];
            [tabManager updateScenesTab];
        });
    }

    [self updateMasterSceneWithID: masterSceneID andCallbackOperation: MasterSceneCreated];
}

-(void)postUpdateMasterScene: (NSString *)masterSceneID withName: (NSString *)masterSceneName
{
    //NSLog(@"postUpdateMasterSceneName(): %@ and name: %@", masterSceneID, masterSceneName);

    LSFMasterSceneModelContainer *container = [LSFMasterSceneModelContainer getMasterSceneModelContainer];
    LSFMasterSceneDataModel *masterSceneModel = [container.masterScenesContainer valueForKey: masterSceneID];

    if (masterSceneModel != nil)
    {
        masterSceneModel.name = masterSceneName;
    }

    [self updateMasterSceneWithID: masterSceneID andCallbackOperation: MasterSceneNameUpdated];
}

-(void)postUpdateMasterScene: (NSString *)masterSceneID withMasterScene: (LSFMasterScene *)masterScene
{
    //NSLog(@"postUpdateMasterScene(): %@", masterSceneID);

    LSFMasterSceneModelContainer *container = [LSFMasterSceneModelContainer getMasterSceneModelContainer];
    LSFMasterSceneDataModel *masterSceneModel = [container.masterScenesContainer valueForKey: masterSceneID];

    if (masterSceneModel != nil)
    {
        masterSceneModel.masterScene = masterScene;
    }

    [self updateMasterSceneWithID: masterSceneID andCallbackOperation: MasterSceneUpdated];
}

-(void)postDeleteMasterScenes: (NSArray *)masterSceneIDs
{
    //NSLog(@"postDeleteMasterScenes()");

    NSMutableArray *masterSceneNames = [[NSMutableArray alloc] init];
    NSMutableDictionary *masterScenes = ((LSFMasterSceneModelContainer *)[LSFMasterSceneModelContainer getMasterSceneModelContainer]).masterScenesContainer;

    for (int i = 0; i < masterSceneIDs.count; i++)
    {
        NSString *masterSceneID = [masterSceneIDs objectAtIndex: i];
        LSFMasterSceneDataModel *model = [masterScenes valueForKey: masterSceneID];

        [masterSceneNames insertObject: model.name atIndex: i];
        [masterScenes removeObjectForKey: masterSceneID];

        dispatch_async(self.queue, ^{
            LSFTabManager *tabManager = [LSFTabManager getTabManager];
            [tabManager updateScenesTab];
        });
    }

    dispatch_async(dispatch_get_main_queue(), ^{
        NSNumber *masterSceneOp = [[NSNumber alloc] initWithInt: MasterSceneDeleted];
        NSDictionary *userInfoDict = [[NSDictionary alloc] initWithObjects: [[NSArray alloc] initWithObjects: masterSceneOp, masterSceneIDs, [NSArray arrayWithArray: masterSceneNames], nil] forKeys: [[NSArray alloc] initWithObjects: @"operation", @"masterSceneIDs", @"masterSceneNames", nil]];
        [[NSNotificationCenter defaultCenter] postNotificationName: @"MasterSceneNotification" object: self userInfo: userInfoDict];
    });
}

-(void)updateMasterSceneWithID: (NSString *)masterSceneID andCallbackOperation: (MasterSceneCallbackOperation)callbackOp
{
    dispatch_async(dispatch_get_main_queue(), ^{
        NSNumber *masterSceneOp = [[NSNumber alloc] initWithInt: callbackOp];
        NSDictionary *userInfoDict = [[NSDictionary alloc] initWithObjects: [[NSArray alloc] initWithObjects: masterSceneOp, masterSceneID, nil] forKeys: [[NSArray alloc] initWithObjects: @"operation", @"masterSceneID", nil]];
        [[NSNotificationCenter defaultCenter] postNotificationName: @"MasterSceneNotification" object: self userInfo: userInfoDict];
    });
}

@end
