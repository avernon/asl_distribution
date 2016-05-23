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

#import "LSFSamplePresetManagerCallback.h"
#import "LSFAllJoynManager.h"
#import "LSFPresetModelContainer.h"
#import "LSFPresetModel.h"
#import "LSFDispatchQueue.h"

@interface LSFSamplePresetManagerCallback()

@property (nonatomic, strong) dispatch_queue_t queue;

-(void)updateUI;
-(void)updatePresetID: (NSString *)presetID;
-(void)updatePresetName: (NSString *)name forPresetID: (NSString *)presetID;
-(void)updatePresetWithID: (NSString *)presetID andState:(LSFLampState *)preset;
-(void)removePresetWithID: (NSString *)presetID;
-(void)removePresetsWithIDs: (NSArray *)presetIDs;
-(void)updateDefaultLampState: (LSFLampState *)defaultLampState;

@end

@implementation LSFSamplePresetManagerCallback

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
 * Implementation of LSFPresetManagerCallbackDelegate
 */
-(void)getPresetReplyWithCode: (LSFResponseCode)rc presetID: (NSString *)presetID andPreset: (LSFLampState *)preset
{
    //NSLog(@"Get preset callback executing. Preset ID = %@. LSFResponse Code = %u", presetID, rc);
    dispatch_async(self.queue, ^{
        [self updatePresetWithID: presetID andState: preset];
    });
}

-(void)getAllPresetIDsReplyWithCode: (LSFResponseCode)rc andPresetIDs: (NSArray *)presetIDs
{
    //NSLog(@"Get all Preset IDs callback executing");
    LSFPresetManager *presetManager = ((LSFAllJoynManager *)[LSFAllJoynManager getAllJoynManager]).lsfPresetManager;
    
    dispatch_async(self.queue, ^{
        for (NSString *presetID in presetIDs)
        {
            NSLog(@"%@", presetID);
            [self updatePresetID: presetID];
            [presetManager getPresetNameWithID: presetID];
            [presetManager getPresetWithID: presetID];
        }
    });
}

-(void)getPresetNameReplyWithCode: (LSFResponseCode)rc presetID: (NSString *)presetID language: (NSString *)language andPresetName: (NSString *)presetName
{
    //NSLog(@"Get preset name callback executing. Name = %@. LSFResponse Code = %u", presetName, rc);
    dispatch_async(self.queue, ^{
        [self updatePresetName: presetName forPresetID: presetID];
    });
}

-(void)setPresetNameReplyWithCode: (LSFResponseCode)rc presetID: (NSString *)presetID andLanguage: (NSString *)language
{
    //NSLog(@"Set preset name callback executing. PresetID = %@. Language = %@. Response Code = %i", presetID, language, rc);
    dispatch_async(self.queue, ^{
        LSFPresetManager *presetManager = ((LSFAllJoynManager *)[LSFAllJoynManager getAllJoynManager]).lsfPresetManager;
        [presetManager getPresetNameWithID: presetID];
    });
}

-(void)presetsNameChanged: (NSArray *)presetIDs
{
    //NSLog(@"Set preset names changed callback executing.");
    dispatch_async(self.queue, ^{
        LSFPresetManager *presetManager = ((LSFAllJoynManager *)[LSFAllJoynManager getAllJoynManager]).lsfPresetManager;
        
        for (NSString *presetID in presetIDs)
        {
            [presetManager getPresetNameWithID: presetID];
        }
    });
}

-(void)createPresetReplyWithCode: (LSFResponseCode)rc andPresetID: (NSString *)presetID
{
    //NSLog(@"Create preset callback executing. PresetID = %@. Response Code = %i", presetID, rc);
    dispatch_async(self.queue, ^{
        if (rc == LAMP_OK)
        {
            LSFPresetManager *presetManager = ((LSFAllJoynManager *)[LSFAllJoynManager getAllJoynManager]).lsfPresetManager;
            [self updatePresetID: presetID];
            [presetManager getPresetNameWithID: presetID];
            [presetManager getPresetWithID: presetID];
        }
    });
}

-(void)presetsCreated: (NSArray *)presetIDs
{
    //NSLog(@"Presets created callback executing.");
    dispatch_async(self.queue, ^{
        LSFPresetManager *presetManager = ((LSFAllJoynManager *)[LSFAllJoynManager getAllJoynManager]).lsfPresetManager;
        for (NSString *presetID in presetIDs)
        {
            [self updatePresetID: presetID];
            [presetManager getPresetNameWithID: presetID];
            [presetManager getPresetWithID: presetID];
        }
    });
}

-(void)updatePresetReplyWithCode: (LSFResponseCode)rc andPresetID: (NSString *)presetID
{
    //NSLog(@"Update preset callback executing. PresetID = %@. Response Code = %i", presetID, rc);
    dispatch_async(self.queue, ^{
        if (rc == LAMP_OK)
        {
            LSFPresetManager *presetManager = ((LSFAllJoynManager *)[LSFAllJoynManager getAllJoynManager]).lsfPresetManager;
            [self updatePresetID: presetID];
            [presetManager getPresetNameWithID: presetID];
            [presetManager getPresetWithID: presetID];
        }
    });
}

-(void)presetsUpdated: (NSArray *)presetIDs
{
    //NSLog(@"Presets updated callback executing.");
    dispatch_async(self.queue, ^{
        LSFPresetManager *presetManager = ((LSFAllJoynManager *)[LSFAllJoynManager getAllJoynManager]).lsfPresetManager;
        
        for (NSString *presetID in presetIDs)
        {
            [self updatePresetID: presetID];
            [presetManager getPresetNameWithID: presetID];
            [presetManager getPresetWithID: presetID];
        }
    });
}

-(void)deletePresetReplyWithCode: (LSFResponseCode)rc andPresetID: (NSString *)presetID
{
    //NSLog(@"Delete preset callback executing. PresetID = %@. Response Code = %i", presetID, rc);
    dispatch_async(self.queue, ^{
        [self removePresetWithID: (NSString *)presetID];
    });
}

-(void)presetsDeleted: (NSArray *)presetIDs
{
    //NSLog(@"Presets deleted callback executing.");
    dispatch_async(self.queue, ^{
        [self removePresetsWithIDs: presetIDs];
    });
}

-(void)getDefaultLampStateReplyWithCode: (LSFResponseCode)rc andLampState: (LSFLampState *)defaultLampState
{
    //NSLog(@"Get default lamp state callback executing. Response Code = %i", rc);
    dispatch_async(self.queue, ^{
        [self updateDefaultLampState: defaultLampState];
    });
}

-(void)setDefaultLampStateReplyWithCode: (LSFResponseCode)rc
{
    //NSLog(@"Set default lamp state callback executing. Response Code = %i", rc);
    dispatch_async(self.queue, ^{
        LSFPresetManager *presetManager = ((LSFAllJoynManager *)[LSFAllJoynManager getAllJoynManager]).lsfPresetManager;
        [presetManager getDefaultLampState];
    });
}

-(void)defaultLampStateChanged
{
    //NSLog(@"Default lamp state changed callback executing.");
    dispatch_async(self.queue, ^{
        LSFPresetManager *presetManager = ((LSFAllJoynManager *)[LSFAllJoynManager getAllJoynManager]).lsfPresetManager;
        [presetManager getDefaultLampState];
    });
}

/*
 * Private function implementations
 */
-(void)updatePresetID: (NSString *)presetID
{
    NSMutableDictionary *presets = ((LSFPresetModelContainer *)[LSFPresetModelContainer getPresetModelContainer]).presetContainer;
    LSFPresetModel *presetModel = [presets valueForKey: presetID];
    
    if (presetModel == nil)
    {
        presetModel = [[LSFPresetModel alloc] initWithPresetID: presetID];
        [presets setValue: presetModel forKey: presetID];
    }
}

-(void)updatePresetName: (NSString *)name forPresetID: (NSString *)presetID
{
    NSMutableDictionary *presets = ((LSFPresetModelContainer *)[LSFPresetModelContainer getPresetModelContainer]).presetContainer;
    LSFPresetModel *presetModel = [presets valueForKey: presetID];
    
    if (presetModel != nil)
    {
        presetModel.name = name;
    }
    
    [self updateUI];
}

-(void)updatePresetWithID: (NSString *)presetID andState:(LSFLampState *)preset
{
    NSMutableDictionary *presets = ((LSFPresetModelContainer *)[LSFPresetModelContainer getPresetModelContainer]).presetContainer;
    LSFPresetModel *presetModel = [presets valueForKey: presetID];
    
    if (presetModel != nil)
    {
        presetModel.state = preset;
    }
    
    [self updateUI];
}

-(void)removePresetWithID: (NSString *)presetID
{
    NSMutableDictionary *presets = ((LSFPresetModelContainer *)[LSFPresetModelContainer getPresetModelContainer]).presetContainer;
    [presets removeObjectForKey: presetID];
    
    [self updateUI];
}

-(void)removePresetsWithIDs: (NSArray *)presetIDs
{
    NSMutableDictionary *presets = ((LSFPresetModelContainer *)[LSFPresetModelContainer getPresetModelContainer]).presetContainer;
    
    for (NSString *presetID in presetIDs)
    {
        [presets removeObjectForKey: presetID];
    }
    
    [self updateUI];
}

-(void)updateDefaultLampState: (LSFLampState *)defaultLampState
{
    //TODO - implement
}

-(void)updateUI
{
    dispatch_async(dispatch_get_main_queue(), ^{
        [[NSNotificationCenter defaultCenter] postNotificationName: @"PresetNotification" object: self userInfo: nil];
    });
}

@end