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

#import "LSFSDKHelperGroupManagerCallback.h"
#import "LSFSDKLightingSystemManager.h"
#import "LSFColorAverager.h"
#import "LSFConstants.h"
#import "LSFSDKAllLampsDataModel.h"
#import "LSFSDKAllJoynManager.h"

@interface LSFSDKHelperGroupManagerCallback()

@property (nonatomic, strong) LSFColorAverager *averageBrightness;
@property (nonatomic, strong) LSFColorAverager *averageHue;
@property (nonatomic, strong) LSFColorAverager *averageSaturation;
@property (nonatomic, strong) LSFColorAverager *averageColorTemp;
@property (nonatomic, strong) NSMutableSet *groupIDsWithPendingMembers;
@property (nonatomic, strong) NSMutableSet *groupIDsWithPendingFlatten;
@property (nonatomic, strong) NSMutableDictionary *creationTrackingIDs;

-(void)postProcessLampGroupID: (NSString *)groupID needName: (BOOL)needName needState: (BOOL)needState;
-(void)postUpdateLampGroupName: (NSString *)groupID groupName: (NSString *)groupName;
-(void)postUpdateLampGroup: (NSString *)groupID lampGroup: (LSFLampGroup *)lampGroup;
-(void)postFlattenLampGroup: (NSString *)groupID;
-(void)postUpdateLampGroupState: (LSFGroupModel *)groupModel;
-(void)postDeleteGroups: (NSArray *)groupIDs;
-(void)postSendGroupChanged: (NSString *)groupID;
-(void)postSendGroupInitialized: (NSString *)groupID;

@end

@implementation LSFSDKHelperGroupManagerCallback

@synthesize manager = _manager;
@synthesize averageBrightness = _averageBrightness;
@synthesize averageHue = _averageHue;
@synthesize averageSaturation = _averageSaturation;
@synthesize averageColorTemp = _averageColorTemp;
@synthesize groupIDsWithPendingMembers = _groupIDsWithPendingMembers;
@synthesize groupIDsWithPendingFlatten = _groupIDsWithPendingFlatten;
@synthesize creationTrackingIDs = _creationTrackingIDs;

-(id)initWithLightingSystemManager: (LSFSDKLightingSystemManager *)manager
{
    self = [super init];

    if (self)
    {
        self.manager = manager;
        self.averageBrightness = [[LSFColorAverager alloc] init];
        self.averageHue = [[LSFColorAverager alloc] init];
        self.averageSaturation = [[LSFColorAverager alloc] init];
        self.averageColorTemp = [[LSFColorAverager alloc] init];
        self.groupIDsWithPendingMembers = [[NSMutableSet alloc] init];
        self.groupIDsWithPendingFlatten = [[NSMutableSet alloc] init];
        self.creationTrackingIDs = [[NSMutableDictionary alloc] init];
    }

    return self;
}

-(void)refreshAllLampGroupIDs
{
    unsigned int count = [self.manager.groupCollectionManager size];
    NSArray *groups = [self.manager.groupCollectionManager getGroups];
    NSMutableArray *groupIDs = [[NSMutableArray alloc] init];

    for (LSFSDKGroup *group in groups)
    {
        [groupIDs addObject: [group theID]];
    }

    if (count > 0)
    {
        [self getAllLampGroupIDsReplyWithCode: LSF_OK andGroupIDs: groupIDs];
    }
}

/*
 * Implementation of LSFLampGroupManagerCallbackDelegate
 */
-(void)getAllLampGroupIDsReplyWithCode: (LSFResponseCode)rc andGroupIDs: (NSArray*)groupIDs
{
    if (rc != LSF_OK)
    {
        [self.manager.groupCollectionManager sendErrorEvent: @"getAllLampGroupIDsReplyCB" statusCode: rc];
    }

    // TODO-FIX reintroduce call and remove lamp delegate
//  [self postProcessLampGroupID: ALL_LAMPS_GROUP_ID needName: YES needState: YES];

    for (NSString *groupID in groupIDs)
    {
        [self postProcessLampGroupID: groupID needName: YES needState: YES];
    }
}

-(void)getLampGroupNameReplyWithCode: (LSFResponseCode)rc groupID: (NSString*)groupID language: (NSString *)language andGroupName: (NSString*)name
{
    if (rc != LSF_OK)
    {
        [self.manager.groupCollectionManager sendErrorEvent: @"getLampGroupNameReplyCB" statusCode: rc itemID: groupID];
        [[LSFSDKAllJoynManager getGroupManager] getLampGroupNameForID: groupID andLanguage: self.manager.defaultLanguage];
    }
    else
    {
        [self postUpdateLampGroupName: groupID groupName: name];
    }
}

-(void)setLampGroupNameReplyWithCode: (LSFResponseCode)rc groupID: (NSString*)groupID andLanguage: (NSString *)language
{
    if (rc != LSF_OK)
    {
        [self.manager.groupCollectionManager sendErrorEvent: @"setLampGroupNameReplyCB" statusCode: rc itemID: groupID];
    }

    [[LSFSDKAllJoynManager getGroupManager] getLampGroupNameForID: groupID andLanguage: self.manager.defaultLanguage];
}

-(void)lampGroupsNameChanged: (NSArray *)groupIDs
{
    for (NSString *groupID in groupIDs)
    {
        [self postProcessLampGroupID: groupID needName: YES needState: NO];
    }
}

-(void)createLampGroupReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID
{
    if (rc != LSF_OK)
    {
        [self.manager.groupCollectionManager sendErrorEvent: @"createLampGroupReplyCB" statusCode: rc itemID: groupID];
    }
}

-(void)createLampGroupTrackingReplyWithCode: (LSFResponseCode)rc groupID: (NSString *)groupID andTrackingID: (unsigned int)trackingID
{
    if (rc != LSF_OK)
    {
        LSFSDKTrackingID *groupTrackingID = [[LSFSDKTrackingID alloc] initWithValue: trackingID];
        [self.manager.groupCollectionManager sendErrorEvent: @"createLampGroupWithTrackingReplyCB" statusCode: rc itemID: groupID withTrackingID: groupTrackingID];
    }
    else
    {
        LSFSDKTrackingID *myTrackingID = [[LSFSDKTrackingID alloc] initWithValue: trackingID];
        [self.creationTrackingIDs setValue: myTrackingID forKey: groupID];
    }
}

-(void)lampGroupsCreated: (NSArray *)groupIDs
{
    for (NSString *groupID in groupIDs)
    {
        [self postProcessLampGroupID: groupID needName: YES needState: YES];
    }
}

-(void)getLampGroupReplyWithCode: (LSFResponseCode)rc groupID: (NSString *)groupID andLampGroup: (LSFLampGroup *)group
{
    if (rc != LSF_OK)
    {
        [self.manager.groupCollectionManager sendErrorEvent: @"getLampGroupReplyCB" statusCode: rc itemID: groupID];
        [[LSFSDKAllJoynManager getGroupManager] getLampGroupWithID: groupID];
    }
    else
    {
        [self postUpdateLampGroup: groupID lampGroup: group];
    }
}

-(void)deleteLampGroupReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID
{
    if (rc != LSF_OK)
    {
        [self.manager.groupCollectionManager sendErrorEvent: @"deleteLampGroupReplyCB" statusCode: rc itemID: groupID];
    }
}

-(void)lampGroupsDeleted: (NSArray *)groupIDs
{
    [self postDeleteGroups: groupIDs];
}

-(void)transitionLampGroupToStateReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID
{
    //TODO - implement, unused at this time
}

-(void)pulseLampGroupWithStateReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID
{
    //TODO - implement, unused at this time
}

-(void)pulseLampGroupWithPresetReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID
{
    //TODO - implement, unused at this time
}

-(void)transitionLampGroupStateOnOffFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID
{
    if (rc != LSF_OK)
    {
        [self.manager.groupCollectionManager sendErrorEvent: @"transitionLampGroupStateOnOffFieldReplyCB" statusCode: rc itemID: groupID];
    }
}

-(void)transitionLampGroupStateHueFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID
{
    if (rc != LSF_OK)
    {
        [self.manager.groupCollectionManager sendErrorEvent: @"transitionLampGroupStateHueFieldReplyCB" statusCode: rc itemID: groupID];
    }
}

-(void)transitionLampGroupStateSaturationFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID
{
    if (rc != LSF_OK)
    {
        [self.manager.groupCollectionManager sendErrorEvent: @"transitionLampGroupStateSaturationFieldReplyCB" statusCode: rc itemID: groupID];
    }
}

-(void)transitionLampGroupStateBrightnessFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID
{
    if (rc != LSF_OK)
    {
        [self.manager.groupCollectionManager sendErrorEvent: @"transitionLampGroupStateBrightnessFieldReplyCB" statusCode: rc itemID: groupID];
    }
}

-(void)transitionLampGroupStateColorTempFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString *)groupID
{
    if (rc != LSF_OK)
    {
        [self.manager.groupCollectionManager sendErrorEvent: @"transitionLampGroupStateColorTempFieldReplyCB" statusCode: rc itemID: groupID];
    }
}

-(void)resetLampGroupStateReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID
{
    //TODO - implement, unused at this time
}

-(void)resetLampGroupStateOnOffFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID
{
    //TODO - implement, unused at this time
}

-(void)resetLampGroupStateHueFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID
{
    //TODO - implement, unused at this time
}

-(void)resetLampGroupStateSaturationFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID
{
    //TODO - implement, unused at this time
}

-(void)resetLampGroupStateBrightnessFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID
{
    //TODO - implement, unused at this time
}

-(void)resetLampGroupStateColorTempFieldReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID
{
    //TODO - implement, unused at this time
}

-(void)updateLampGroupReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID
{
    //TODO - implement, unused at this time
}

-(void)lampGroupsUpdated: (NSArray *)groupIDs
{
    for (NSString *groupID in groupIDs)
    {
        [self postProcessLampGroupID: groupID needName: NO needState: YES];
    }
}

-(void)transitionLampGroupStateToPresetReplyWithCode: (LSFResponseCode)rc andGroupID: (NSString*)groupID
{
    //TODO - implement, unused at this time
}

-(void)setLampGroupEffectReplyWithCode: (LSFResponseCode)rc groupID: (NSString *)groupID andEffectID: (NSString *)effectID
{
    //TODO - implement, unused at this time
}

/*
 * Private function implementations
 */
-(void)postProcessLampGroupID: (NSString *)groupID needName: (BOOL)needName needState: (BOOL)needState
{
    dispatch_async(self.manager.dispatchQueue, ^{
        BOOL getName = needName;
        BOOL getState = needState;

        if (![self.manager.groupCollectionManager hasID: groupID])
        {
            [self.manager.groupCollectionManager addGroupWithID: groupID];

            getName = YES;
            getState = YES;
        }

        if (getName)
        {
            [[LSFSDKAllJoynManager getGroupManager] getLampGroupNameForID: groupID andLanguage: self.manager.defaultLanguage];
        }

        if (getState)
        {
            [self.groupIDsWithPendingMembers addObject: groupID];
            [[LSFSDKAllJoynManager getGroupManager] getLampGroupWithID: groupID];
        }
    });
}

-(void)postUpdateLampGroupName: (NSString *)groupID groupName: (NSString *)groupName
{
    dispatch_async(self.manager.dispatchQueue, ^{
        LSFGroupModel *groupModel = [self.manager.groupCollectionManager getModelWithID: groupID];

        if (groupModel != nil)
        {
            bool wasInitialized = [groupModel isInitialized];
            groupModel.name = groupName;

            if (wasInitialized != [groupModel isInitialized])
            {
                [self postSendGroupInitialized: groupID];
            }
        }
    });

    [self postSendGroupChanged: groupID];
}

-(void)postUpdateLampGroup: (NSString *)groupID lampGroup: (LSFLampGroup *)lampGroup
{
    dispatch_async(self.manager.dispatchQueue, ^{
        LSFGroupModel *groupModel = [self.manager.groupCollectionManager getModelWithID: groupID];
        [self.groupIDsWithPendingMembers removeObject: groupID];

        if (groupModel != nil)
        {
            BOOL wasInitialized = [groupModel isInitialized];
            groupModel.members = lampGroup;

            if (wasInitialized != [groupModel isInitialized])
            {
                [self postSendGroupInitialized: groupID];
            }
        }

        [self.groupIDsWithPendingFlatten addObject: groupID];

        if (self.groupIDsWithPendingMembers.count == 0)
        {
            for (NSString *groupID in self.groupIDsWithPendingFlatten)
            {
                [self postFlattenLampGroup: groupID];
            }

            [self.groupIDsWithPendingFlatten removeAllObjects];

            [self postUpdateLampGroupState: groupModel];
        }
    });
}

-(void)postFlattenLampGroup: (NSString *)groupID
{
    dispatch_async(self.manager.dispatchQueue, ^{
        LSFSDKGroupCollectionManager *groupCollectionManager = self.manager.groupCollectionManager;
        LSFSDKGroup *group = [groupCollectionManager getGroupWithID: groupID];

        if (group != nil)
        {
            [groupCollectionManager flattenGroup: group];
        }
    });
}

-(void)postUpdateDependentLampGroups: (NSString *)lampID
{
    dispatch_async(self.manager.dispatchQueue, ^{
        for (LSFSDKGroup *group in [self.manager.groupCollectionManager getGroups])
        {
            LSFGroupModel *groupModel = [group getLampGroupDataModel];
            NSSet *lampIDs = [groupModel lamps];

            if (lampIDs != nil)
            {
                if ([[LSFSDKAllLampsDataModel getAllLampsGroupID] isEqualToString: groupModel.theID])
                {
                    NSMutableSet *updatedLampIDs = [[NSMutableSet alloc] initWithSet: lampIDs];
                    [updatedLampIDs addObject: lampID];
                    [groupModel setLamps: updatedLampIDs];

                    lampIDs = updatedLampIDs;
                }

                if ([lampIDs containsObject: lampID])
                {
                    [self postUpdateLampGroupState: groupModel];
                }
            }
        }
    });
}

-(void)postUpdateLampGroupState: (LSFGroupModel *)groupModel
{
    dispatch_async(self.manager.dispatchQueue, ^{
        LSFConstants *constants = [LSFConstants getConstants];
        LSFCapabilityData *capability = [[LSFCapabilityData alloc] init];
        int countOn = 0;
        int countOff = 0;
        int colorTempGroupMin = -1;
        int colorTempGroupMax = -1;

        [self.averageBrightness reset];
        [self.averageHue reset];
        [self.averageSaturation reset];
        [self.averageColorTemp reset];

        NSSet *lamps = [groupModel lamps];

        if (lamps != nil)
        {
            for (NSString *lampID in lamps)
            {
                LSFLampModel *lampModel = [self.manager.lampCollectionManager getModelWithID: lampID];

                if (lampModel != nil)
                {
                    LSFSDKLampDetails *lampDetails = [lampModel lampDetails];

                    [capability includeData: lampModel.capability];

                    if (lampModel.state.onOff)
                    {
                        countOn++;
                    }
                    else
                    {
                        countOff++;
                    }

                    if (lampDetails.color)
                    {
                        [self.averageHue add: lampModel.state.hue];
                        [self.averageSaturation add: lampModel.state.saturation];
                    }

                    if (lampDetails.dimmable)
                    {
                        [self.averageBrightness add: lampModel.state.brightness];
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

        groupModel.groupColorTempMin = (colorTempGroupMin != -1 || (colorTempGroupMin >= constants.MIN_COLOR_TEMP && colorTempGroupMin <= constants.MAX_COLOR_TEMP)) ? colorTempGroupMin : constants.MIN_COLOR_TEMP;
        groupModel.groupColorTempMax = (colorTempGroupMax != -1 || (colorTempGroupMax >= constants.MIN_COLOR_TEMP && colorTempGroupMax <= constants.MAX_COLOR_TEMP)) ? colorTempGroupMax : constants.MAX_COLOR_TEMP;

//        NSLog(@"Group Model State - %@", groupModel.name);
//        NSLog(@"OnOff = %@, Uniformity = %@", groupModel.state.onOff ? @"On" : @"Off", groupModel.uniformity.power ? @"True" : @"False");
//        NSLog(@"Brightness = %u, Uniformity = %@", groupModel.state.brightness, groupModel.uniformity.brightness ? @"True" : @"False");
//        NSLog(@"Hue = %u, Uniformity = %@", groupModel.state.hue, groupModel.uniformity.hue ? @"True" : @"False");
//        NSLog(@"Saturation = %u, Uniformity = %@", groupModel.state.saturation, groupModel.uniformity.saturation ? @"True" : @"False");
//        NSLog(@"Color Temp = %u, Uniformity = %@", groupModel.state.colorTemp, groupModel.uniformity.colorTemp ? @"True" : @"False");
//        NSLog(@"Color Temp Group Min = %u", groupModel.groupColorTempMin);
//        NSLog(@"Color Temp Group Max = %u", groupModel.groupColorTempMax);
    });

    [self postSendGroupChanged: [groupModel theID]];
}

-(void)postDeleteGroups: (NSArray *)groupIDs
{
    dispatch_async(self.manager.dispatchQueue, ^{
        for (NSString *groupID in groupIDs)
        {
            [self.manager.groupCollectionManager removeGroupWithID: groupID];
        }
    });
}

-(void)postSendGroupChanged: (NSString *)groupID
{
    dispatch_async(self.manager.dispatchQueue, ^{
        [self.manager.groupCollectionManager sendChangedEvent: groupID];
    });
}

-(void)postSendGroupInitialized: (NSString *)groupID
{
    dispatch_async(self.manager.dispatchQueue, ^{
        LSFSDKTrackingID *trackingID = [self.creationTrackingIDs valueForKey: groupID];

        if (trackingID != nil)
        {
            [self.creationTrackingIDs removeObjectForKey: groupID];
        }

        [self.manager.groupCollectionManager sendInitializedEvent: groupID withTrackingID: trackingID];
    });
}

/*
 * Lamp Delegate to determine when to create/remove the AllLamps virtual group
 */
-(void)onLampInitialized: (LSFSDKLamp *)lamp
{
    // intentionally left blank
}

-(void)onLampChanged: (LSFSDKLamp *)lamp
{
    if (![self.manager.groupCollectionManager hasID: [LSFSDKAllLampsDataModel getAllLampsGroupID]])
    {
        [self postProcessLampGroupID: [LSFSDKAllLampsDataModel getAllLampsGroupID] needName: YES needState: YES];
    }
}

-(void)onLampRemoved: (LSFSDKLamp *)lamp
{
    if ([[self.manager.lampCollectionManager getLamps] count] == 0)
    {
        if ([self.manager.groupCollectionManager hasID: [LSFSDKAllLampsDataModel getAllLampsGroupID]])
        {
            [self lampGroupsDeleted: @[[LSFSDKAllLampsDataModel getAllLampsGroupID]]];
        }
    }
}

-(void)onLampError: (LSFSDKLightingItemErrorEvent *)error
{
    // intentionally left blank
}

@end
