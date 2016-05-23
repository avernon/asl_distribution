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

#import "LSFHelperLampGroupManagerCallback.h"
#import "LSFDispatchQueue.h"
#import "LSFConstants.h"
#import "LSFGroupModelContainer.h"
#import "LSFGroupModel.h"
#import "LSFGroupsFlattener.h"
#import "LSFLampModelContainer.h"
#import "LSFLampModel.h"
#import "LSFAllJoynManager.h"
#import "LSFEnums.h"
#import "LSFColorAverager.h"
#import "LSFSDKGroup.h"
#import "LSFSDKLamp.h"

@interface LSFHelperLampGroupManagerCallback()

@property (nonatomic, strong) dispatch_queue_t queue;
@property (nonatomic, strong) NSString *flattenTriggerGroupID;
@property (nonatomic, strong) LSFColorAverager *averageBrightness;
@property (nonatomic, strong) LSFColorAverager *averageHue;
@property (nonatomic, strong) LSFColorAverager *averageSaturation;
@property (nonatomic, strong) LSFColorAverager *averageColorTemp;

-(void)postProcessLampGroupIDs: (NSArray *)groupIDs;
-(void)postProcessLampGroupID: (NSString *)groupID;
-(void)postUpdateLampGroupName: (NSString *)groupID andName: (NSString *)name;
-(void)postUpdateLampGroup: (NSString *)groupID andLampGroup: (LSFLampGroup *)lampGroup;
-(void)postFlattenLampGroups;
-(void)postUpdateLampGroupState: (LSFGroupModel *)groupModel;
-(void)postUpdateLampGroupMembersLamps: (NSString *)groupID;
-(void)postDeleteGroups: (NSArray *)groupIDs;
-(void)updateGroupWithID: (NSString *)groupID andCallbackOperation: (GroupCallbackOperation)callbackOp;

@end

@implementation LSFHelperLampGroupManagerCallback

@synthesize queue = _queue;
@synthesize flattenTriggerGroupID = _flattenTriggerGroupID;

-(id)init
{
    self = [super init];
    
    if (self)
    {
        self.queue = ([LSFDispatchQueue getDispatchQueue]).queue;
        self.averageBrightness = [[LSFColorAverager alloc] init];
        self.averageHue = [[LSFColorAverager alloc] init];
        self.averageSaturation = [[LSFColorAverager alloc] init];
        self.averageColorTemp = [[LSFColorAverager alloc] init];
    }
    
    return self;
}

-(void)refreshAllLampGroupIDs
{
    LSFGroupModelContainer *container = [LSFGroupModelContainer getGroupModelContainer];
    NSMutableDictionary *groups = container.groupContainer;

    if (groups.count > 0)
    {
        [self getAllLampGroupIDsReplyWithCode: LSF_OK andGroupIDs: [groups allKeys]];
    }
}

/*
 * Implementation of LSFLampGroupManagerCallbackDelegate
 */
-(void)getAllLampGroupIDsReplyWithCode: (LSFResponseCode)rc andGroupIDs: (NSArray*)groupIDs
{
    //NSLog(@"getAllLampGroupIDs() executing");

    if (rc != LSF_OK)
    {
        NSLog(@"LSFSampleLampGroupManagerCallback - getAllLampGroupIDsReply() returned error code %i", rc);
    }

    dispatch_async(self.queue, ^{
        [self postProcessLampGroupIDs: groupIDs];
        [self postProcessLampGroupID: ([LSFConstants getConstants]).ALL_LAMPS_GROUP_ID];

        for (NSString *groupID in groupIDs)
        {
            [self postProcessLampGroupID: groupID];
        }
    });
}

-(void)getLampGroupNameReplyWithCode: (LSFResponseCode)rc groupID: (NSString*)groupID language: (NSString *)language andGroupName: (NSString*)name
{
    if (rc != LSF_OK)
    {
        NSLog(@"LSFSampleLampGroupManagerCallback - getLampGroupNameReply() returned error code %i", rc);
    }

    dispatch_async(self.queue, ^{
        [self postUpdateLampGroupName: groupID andName: name];
    });
}

-(void)getLampGroupVersionReplyWithCode: (LSFResponseCode)rc groupID: (NSString *)groupID andVersion: (unsigned int)version
{
    //TODO - implement, may be unused
}

-(void)setLampGroupNameReplyWithCode: (LSFResponseCode)rc groupID: (NSString*)groupID andLanguage: (NSString *)language
{
    if (rc != LSF_OK)
    {
        NSLog(@"LSFSampleLampGroupManagerCallback - setLampGroupNameReply() returned error code %i", rc);
    }
    
    dispatch_async(self.queue, ^{
        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
        [ajManager.lsfLampGroupManager getLampGroupNameForID: groupID andLanguage: language];
    });
}

-(void)lampGroupsNameChanged: (NSArray *)groupIDs
{
    dispatch_async(self.queue, ^{
        BOOL containsNewIDs = NO;
        NSMutableDictionary *groups = ((LSFGroupModelContainer *)[LSFGroupModelContainer getGroupModelContainer]).groupContainer;
        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
        
        for (NSString *groupID in groupIDs)
        {
            if ([groups valueForKey: groupID] != nil)
            {
                [ajManager.lsfLampGroupManager getLampGroupNameForID: groupID];
            }
            else
            {
                containsNewIDs = YES;
            }
        }
        
        if (containsNewIDs)
        {
            [ajManager.lsfLampGroupManager getAllLampGroupIDs];
        }
    });
}

-(void)createLampGroupReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID
{
    if (rc != LSF_OK)
    {
        NSLog(@"LSFSampleLampGroupManagerCallback - createLampGroupNameReply() returned error code %i", rc);
    }

    dispatch_async(self.queue, ^{
        [self postProcessLampGroupID: groupID];
    });
}

-(void)createLampGroupTrackingReplyWithCode: (LSFResponseCode)rc groupID: (NSString *)groupID andTrackingID: (unsigned int)trackingID
{
    //TODO - implement, may be unused
}

-(void)lampGroupsCreated: (NSArray *)groupIDs
{
    //NSLog(@"Lamp Groups Created Callback");

    dispatch_async(self.queue, ^{
        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
        [ajManager.lsfLampGroupManager getAllLampGroupIDs];
    });
}

-(void)getLampGroupReplyWithCode: (LSFResponseCode)rc groupID: (NSString *)groupID andLampGroup: (LSFLampGroup *)group
{
    if (rc != LSF_OK)
    {
        NSLog(@"LSFSampleLampGroupManagerCallback - getLampGroupReply() returned error code %i", rc);
    }
    else
    {
        dispatch_async(self.queue, ^{
            [self postUpdateLampGroup: groupID andLampGroup: group];
        });
    }
}

-(void)deleteLampGroupReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID
{
    NSLog(@"LSFSampleLampGroupManagerCallback - deleteLampGroupReply()");

    if (rc != LSF_OK)
    {
        NSLog(@"Delete lamp group returned an error code = %u", rc);
    }
}

-(void)lampGroupsDeleted: (NSArray *)groupIDs
{
    dispatch_async(self.queue, ^{
        [self postDeleteGroups: groupIDs];
    });
}

-(void)transitionLampGroupToStateReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID
{
    if (rc != LSF_OK)
    {
        NSLog(@"LSFSampleLampGroupManagerCallback - transitionLampGroupToStateReply() returned error code %i", rc);
    }

    dispatch_async(self.queue, ^{
        [self postUpdateLampGroupMembersLamps: groupID];
    });
}

-(void)pulseLampGroupWithStateReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID
{
    //TODO
}

-(void)pulseLampGroupWithPresetReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID
{
    //TODO
}

-(void)transitionLampGroupStateOnOffFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID
{
    if (rc != LSF_OK)
    {
        NSLog(@"LSFSampleLampGroupManagerCallback - transitionLampGroupStateOnOffFieldReply() returned error code %i", rc);
    }
    
    dispatch_async(self.queue, ^{
        [self postUpdateLampGroupMembersLamps: groupID];
    });
}

-(void)transitionLampGroupStateHueFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID
{
    if (rc != LSF_OK)
    {
        NSLog(@"LSFSampleLampGroupManagerCallback - transitionLampGroupStateHueFieldReply() returned error code %i", rc);
    }

    dispatch_async(self.queue, ^{
        [self postUpdateLampGroupMembersLamps: groupID];
    });
}

-(void)transitionLampGroupStateSaturationFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID
{
    if (rc != LSF_OK)
    {
        NSLog(@"LSFSampleLampGroupManagerCallback - transitionLampGroupStateSaturationFieldReply() returned error code %i", rc);
    }
    
    dispatch_async(self.queue, ^{
        [self postUpdateLampGroupMembersLamps: groupID];
    });
}

-(void)transitionLampGroupStateBrightnessFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID
{
    if (rc != LSF_OK)
    {
        NSLog(@"LSFSampleLampGroupManagerCallback - transitionLampGroupStateBrightnessFieldReply() returned error code %i", rc);
    }
    
    dispatch_async(self.queue, ^{
        [self postUpdateLampGroupMembersLamps: groupID];
    });
}

-(void)transitionLampGroupStateColorTempFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID
{
    if (rc != LSF_OK)
    {
        NSLog(@"LSFSampleLampGroupManagerCallback - transitionLampGroupStateColorTempFieldReply() returned error code %i", rc);
    }
    
    dispatch_async(self.queue, ^{
        [self postUpdateLampGroupMembersLamps: groupID];
    });
}

-(void)resetLampGroupStateReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID
{
    //TODO
}

-(void)resetLampGroupStateOnOffFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID
{
    //TODO
}

-(void)resetLampGroupStateHueFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID
{
    //TODO
}

-(void)resetLampGroupStateSaturationFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID
{
    //TODO
}

-(void)resetLampGroupStateBrightnessFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID
{
    //TODO
}

-(void)resetLampGroupStateColorTempFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID
{
    //TODO
}

-(void)updateLampGroupReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID
{
    //TODO
}

-(void)lampGroupsUpdated: (NSArray *)groupIDs
{
    dispatch_async(self.queue, ^{
        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
        
        for (NSString *groupID in groupIDs)
        {
            [ajManager.lsfLampGroupManager getLampGroupWithID: groupID];
        }
    });
}

-(void)transitionLampGroupStateToPresetReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID
{
    //TODO
}

-(void)setLampGroupEffectReplyWithCode: (LSFResponseCode)rc groupID: (NSString *)groupID andEffectID: (NSString *)effectID
{
    //TODO - implement, may be unused
}

/*
 * Private Functions
 */
-(void)postProcessLampGroupIDs: (NSArray *)groupIDs
{
    if ([groupIDs count] > 0)
    {
        self.flattenTriggerGroupID = [groupIDs objectAtIndex: ([groupIDs count] - 1)];
    }
    else
    {
        self.flattenTriggerGroupID = ([LSFConstants getConstants]).ALL_LAMPS_GROUP_ID;
    }
}

-(void)postProcessLampGroupID: (NSString *)groupID
{
    NSMutableDictionary *groups = [[LSFGroupModelContainer getGroupModelContainer] groupContainer];

    LSFSDKGroup *group = [groups valueForKey: groupID];

    if (group == nil)
    {
        group = [[LSFSDKGroup alloc] initWithGroupID: groupID];
        [groups setValue: group forKey: groupID];

        [self updateGroupWithID: groupID andCallbackOperation: GroupCreated];

        dispatch_async(dispatch_get_main_queue(), ^{
            [[NSNotificationCenter defaultCenter] postNotificationName: @"UpdateGroups" object: self userInfo: nil];
        });

        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
        [ajManager.lsfLampGroupManager getLampGroupNameForID: groupID];
        [ajManager.lsfLampGroupManager getLampGroupWithID: groupID];
    }
    
    if ([groupID isEqualToString: self.flattenTriggerGroupID])
    {
        [self postFlattenLampGroups];
    }
}

-(void)postUpdateLampGroupName: (NSString *)groupID andName: (NSString *)name
{
    NSMutableDictionary *groups = [[LSFGroupModelContainer getGroupModelContainer] groupContainer];
    LSFGroupModel *groupModel = [[groups valueForKey: groupID] getLampGroupDataModel];
    
    if (groupModel != nil)
    {
        groupModel.name = name;
    }
    
    [self updateGroupWithID: groupID andCallbackOperation: GroupNameUpdated];
}

-(void)postUpdateLampGroup: (NSString *)groupID andLampGroup: (LSFLampGroup *)lampGroup
{
    NSMutableDictionary *groups = [[LSFGroupModelContainer getGroupModelContainer] groupContainer];
    LSFGroupModel *groupModel = [[groups valueForKey: groupID] getLampGroupDataModel];
    
    if (groupModel != nil)
    {
        groupModel.members = lampGroup;
    }

    [self postFlattenLampGroups];
}

-(void)postFlattenLampGroups
{
    NSMutableDictionary *groups = [[LSFGroupModelContainer getGroupModelContainer] groupContainer];
    [[[LSFGroupsFlattener alloc] init] flattenGroups: groups];
    
    for (LSFSDKGroup *group in [groups allValues])
    {
        [self postUpdateLampGroupState: [group getLampGroupDataModel]];
    }
}

-(void)postUpdateLampGroupState: (LSFGroupModel *)groupModel
{
    NSMutableDictionary *lamps = [[LSFLampModelContainer getLampModelContainer] lampContainer];

    LSFCapabilityData *capability = [[LSFCapabilityData alloc] init];
    int countOn = 0;
    int countOff = 0;
    int colorTempGroupMin = -1;
    int colorTempGroupMax = -1;

    [self.averageBrightness reset];
    [self.averageHue reset];
    [self.averageSaturation reset];
    [self.averageColorTemp reset];
    
    for (NSString *lampID in groupModel.lamps)
    {
        LSFLampModel *lampModel = [[lamps valueForKey: lampID] getLampDataModel];
        
        if (lampModel != nil)
        {
            [capability includeData: lampModel.capability];

            if (lampModel.state.onOff)
            {
                countOn++;
            }
            else
            {
                countOff++;
            }

            if (lampModel.lampDetails.dimmable)
            {
                [self.averageBrightness add: lampModel.state.brightness];
            }

            if (lampModel.lampDetails.color)
            {
                [self.averageHue add: lampModel.state.hue];
                [self.averageSaturation add: lampModel.state.saturation];
            }

            //Average the color temp and figure out the min/max
            //NSLog(@"Adding %u to the color temp averager", lampModel.state.colorTemp);
            [self.averageColorTemp add: lampModel.state.colorTemp];

            int colorTempLampMin = lampModel.lampDetails.minTemperature;
            int colorTempLampMax = lampModel.lampDetails.maxTemperature;

            if ((colorTempGroupMin == -1) || (colorTempGroupMin > colorTempLampMin))
            {
                colorTempGroupMin = colorTempLampMin;
            }

            if ((colorTempGroupMax == -1) || (colorTempGroupMax < colorTempLampMax))
            {
                colorTempGroupMax = colorTempLampMax;
            }
        }
        else
        {
            NSLog(@"postUpdateLampGroupState - missing lamp");
        }
    }

    groupModel.capability = capability;
    
    groupModel.state.onOff = (countOn > 0);
    groupModel.state.brightness = (uint32_t)[self.averageBrightness getAverage];
    groupModel.state.hue = (uint32_t)[self.averageHue getAverage];
    groupModel.state.saturation = (uint32_t)[self.averageSaturation getAverage];
    groupModel.state.colorTemp = (uint32_t)[self.averageColorTemp getAverage];

    groupModel.uniformity.power = ((countOn == 0) || (countOff == 0));
    groupModel.uniformity.brightness = [self.averageBrightness isUniform];
    groupModel.uniformity.hue = [self.averageHue isUniform];
    groupModel.uniformity.saturation = [self.averageSaturation isUniform];
    groupModel.uniformity.colorTemp = [self.averageColorTemp isUniform];

    groupModel.groupColorTempMin = (colorTempGroupMin != -1 || (colorTempGroupMin >= ([LSFConstants getConstants]).MIN_COLOR_TEMP && colorTempGroupMin <= ([LSFConstants getConstants]).MAX_COLOR_TEMP)) ? colorTempGroupMin : ([LSFConstants getConstants]).MIN_COLOR_TEMP;
    groupModel.groupColorTempMax = (colorTempGroupMax != -1 || (colorTempGroupMax >= ([LSFConstants getConstants]).MIN_COLOR_TEMP && colorTempGroupMax <= ([LSFConstants getConstants]).MAX_COLOR_TEMP)) ? colorTempGroupMax : ([LSFConstants getConstants]).MAX_COLOR_TEMP;

//    NSLog(@"Group Model State - %@", groupModel.name);
//    NSLog(@"OnOff = %@, Uniformity = %@", groupModel.state.onOff ? @"On" : @"Off", groupModel.uniformity.power ? @"True" : @"False");
//    NSLog(@"Brightness = %u, Uniformity = %@", groupModel.state.brightness, groupModel.uniformity.brightness ? @"True" : @"False");
//    NSLog(@"Hue = %u, Uniformity = %@", groupModel.state.hue, groupModel.uniformity.hue ? @"True" : @"False");
//    NSLog(@"Saturation = %u, Uniformity = %@", groupModel.state.saturation, groupModel.uniformity.saturation ? @"True" : @"False");
//    NSLog(@"Color Temp = %u, Uniformity = %@", groupModel.state.colorTemp, groupModel.uniformity.colorTemp ? @"True" : @"False");
//    NSLog(@"Color Temp Group Min = %u", groupModel.groupColorTempMin);
//    NSLog(@"Color Temp Group Max = %u", groupModel.groupColorTempMax);

    [self updateGroupWithID: groupModel.theID andCallbackOperation: GroupStateUpdated];
}

-(void)postUpdateLampGroupMembersLamps: (NSString *)groupID
{
    NSLog(@"postUpdateLampGroupMembersLamps() executing");

    NSMutableDictionary *groups = [[LSFGroupModelContainer getGroupModelContainer] groupContainer];
    LSFGroupModel *groupModel = [[groups valueForKey: groupID] getLampGroupDataModel];
    LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
    
    if (groupModel != nil)
    {
        for (NSString *lampID in groupModel.lamps)
        {
            [ajManager.lsfLampManager getLampStateForID: lampID];
        }
    }
}

-(void)postDeleteGroups: (NSArray *)groupIDs
{
    NSMutableArray *groupNames = [[NSMutableArray alloc] init];
    NSMutableDictionary *groups = [[LSFGroupModelContainer getGroupModelContainer] groupContainer];
    
    for (int i = 0; i < groupIDs.count; i++)
    {
        NSString *groupID = [groupIDs objectAtIndex: i];
        LSFGroupModel *model = [[groups valueForKey: groupID] getLampGroupDataModel];

        [groupNames insertObject: model.name atIndex: i];
        [groups removeObjectForKey: groupID];

        dispatch_async(dispatch_get_main_queue(), ^{
            [[NSNotificationCenter defaultCenter] postNotificationName: @"UpdateGroups" object: self userInfo: nil];
        });
    }

    dispatch_async(dispatch_get_main_queue(), ^{
        NSNumber *groupOp = [[NSNumber alloc] initWithInt: GroupDeleted];
        NSDictionary *userInfoDict = [[NSDictionary alloc] initWithObjects: [[NSArray alloc] initWithObjects: groupOp, groupIDs, [NSArray arrayWithArray: groupNames], nil] forKeys: [[NSArray alloc] initWithObjects: @"operation", @"groupIDs", @"groupNames", nil]];
        [[NSNotificationCenter defaultCenter] postNotificationName: @"GroupNotification" object: self userInfo: userInfoDict];
    });
}

-(void)updateGroupWithID: (NSString *)groupID andCallbackOperation: (GroupCallbackOperation)callbackOp
{
    dispatch_async(dispatch_get_main_queue(), ^{
        NSNumber *groupOp = [[NSNumber alloc] initWithInt: callbackOp];
        NSDictionary *userInfoDict = [[NSDictionary alloc] initWithObjects: [[NSArray alloc] initWithObjects: groupOp, groupID, nil] forKeys: [[NSArray alloc] initWithObjects: @"operation", @"groupID", nil]];
        [[NSNotificationCenter defaultCenter] postNotificationName: @"GroupNotification" object: self userInfo: userInfoDict];
    });
}

@end
