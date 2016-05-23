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

#import "LSFSDKHelperLampManagerCallback.h"
#import "LSFSDKLightingSystemManager.h"
#import "LSFSDKAllJoynManager.h"
#import "LSFConstants.h"
#import <LSFSDKResponseCodes.h>

static const unsigned int RETRY_DELAY = 1;
static const unsigned int ABOUT_DELAY_IN_MS = 250;

@interface LSFSDKHelperLampManagerCallback()

@property (nonatomic) NSTimeInterval prevLampAboutQueryTime;
@property (nonatomic, strong) LSFSDKLightingSystemManager *manager;
@property (nonatomic, strong) NSMutableDictionary *savedLampAbouts;

-(void)postUpdateLampID: (NSString *)lampID withDelay: (unsigned int)delay;
-(void)postRemoveLampID: (NSString *)lampID;
-(void)postGetLampNameForID: (NSString *)lampID withDelay: (unsigned int)delay;
-(void)postUpdateLampNameForID: (NSString *)lampID andLampName: (NSString *)lampName;
-(void)postUpdateLampDetailsForID: (NSString *)lampID withDetails: (LSFSDKLampDetails *)lampDetails;
-(void)postGetLampDetails: (NSString *)lampID withDelay: (unsigned int)delay;
-(void)postUpdateLampParametersForID: (NSString *)lampID withParameters: (LSFSDKLampParameters *)lampParameters;
-(void)postGetLampParameters: (NSString *)lampID withDelay: (unsigned int)delay;
-(void)postUpdateLampStateForID: (NSString *)lampID withState: (LSFLampState *)lampState;
-(void)postGetLampState: (NSString *)lampID withDelay: (unsigned int)delay;
-(void)postUpdateLampStateOnOffForID: (NSString *)lampID withOnOff: (BOOL)onOff;
-(void)postGetLampStateOnOffField: (NSString *)lampID withDelay: (unsigned int)delay;
-(void)postUpdateLampStateHueForID: (NSString *)lampID withHue: (unsigned int)hue;
-(void)postGetLampStateHueField: (NSString *)lampID withDelay: (unsigned int)delay;
-(void)postUpdateLampStateSaturationForID: (NSString *)lampID withSaturation: (unsigned int)saturation;
-(void)postGetLampStateSaturationField: (NSString *)lampID withDelay: (unsigned int)delay;
-(void)postUpdateLampStateBrightnessForID: (NSString *)lampID withBrightness: (unsigned int)brightness;
-(void)postGetLampStateBrightnessField: (NSString *)lampID withDelay: (unsigned int)delay;
-(void)postUpdateLampStateColorTempForID: (NSString *)lampID withColorTemp: (unsigned int)colorTemp;
-(void)postGetLampStateColorTempField: (NSString *)lampID withDelay: (unsigned int)delay;
-(void)postUpdateLampGroupState: (NSString *)lampID;
-(void)postSendLampChanged: (NSString *)lampID;
-(void)postSendLampInitialized: (NSString *)lampID;

@end

@implementation LSFSDKHelperLampManagerCallback

@synthesize prevLampAboutQueryTime = _prevLampAboutQueryTime;
@synthesize manager = _manager;
@synthesize savedLampAbouts = _savedLampAbouts;

-(id)initWithLightingSystemManager: (LSFSDKLightingSystemManager *)manager
{
    self = [super init];

    if (self)
    {
        self.manager = manager;
        self.savedLampAbouts = [[NSMutableDictionary alloc] init];
        self.prevLampAboutQueryTime = 0;
    }

    return self;
}

-(void)clear
{
    [self.savedLampAbouts removeAllObjects];
}

/*
 * Implementation of LSFLampManagerCallbackDelegate
 */
-(void)getAllLampIDsReplyWithCode: (LSFResponseCode)rc andLampIDs: (NSArray *)lampIDs
{
    if (rc != LSF_OK)
    {
        [[self.manager lampCollectionManager] sendErrorEvent: @"getAllLampIDs" statusCode: rc];
    }

    //Process lamp IDs regardless of response code
    for (NSString *lampID in lampIDs)
    {
        [self postUpdateLampID: lampID withDelay: 0];
    }
}

-(void)getLampNameReplyWithCode: (LSFResponseCode)rc lampID: (NSString*)lampID language: (NSString*)language andLampName: (NSString*)name
{
    if (rc != LSF_OK)
    {
        [self postGetLampNameForID: lampID withDelay: RETRY_DELAY];
        [[self.manager lampCollectionManager] sendErrorEvent: @"getLampNameReplyCB" statusCode: rc itemID: lampID];
    }
    else
    {
        [self postUpdateLampNameForID: lampID andLampName: name];
    }
}

-(void)getLampManufacturerReplyWithCode: (LSFResponseCode)rc lampID: (NSString*)lampID language: (NSString*)language andManufacturer: (NSString*)manufacturer
{
    //TODO - implement later, unused at this time
}

-(void)setLampNameReplyWithCode: (LSFResponseCode)rc lampID: (NSString*)lampID andLanguage: (NSString*)language
{
    if (rc != LSF_OK)
    {
        [[self.manager lampCollectionManager] sendErrorEvent: @"setLampNameReplyCB" statusCode: rc itemID: lampID];
    }

    //Read back name regardless of response code
    [self postGetLampNameForID: lampID withDelay: 0];
}

-(void)lampsNameChangedWithID: (NSString *)lampID andName: (NSString *)name
{
    [self postUpdateLampNameForID: lampID andLampName: name];
}

-(void)lampsFound: (NSArray *)lampIDs
{
    for (NSString *lampID in lampIDs)
    {
        [self postUpdateLampID: lampID withDelay: 0];
    }
}

-(void)lampsLost: (NSArray *)lampIDs
{
    for (NSString *lampID in lampIDs)
    {
        [self postRemoveLampID: lampID];
    }
}

-(void)getLampDetailsReplyWithCode: (LSFResponseCode)rc lampID: (NSString *)lampID andLampDetails: (LSFSDKLampDetails *)details
{
    if (rc != LSF_OK)
    {
        [self postGetLampDetails: lampID withDelay: RETRY_DELAY];
        [[self.manager lampCollectionManager] sendErrorEvent: @"getLampDetailsReplyCB" statusCode: rc itemID: lampID];
    }
    else
    {
        [self postUpdateLampDetailsForID: lampID withDetails: details];
    }
}

-(void)getLampParametersReplyWithCode: (LSFResponseCode)rc lampID: (NSString *)lampID andLampParameters: (LSFSDKLampParameters *)params
{
    if (rc != LSF_OK)
    {
        [self postGetLampParameters: lampID withDelay: RETRY_DELAY];
        [[self.manager lampCollectionManager] sendErrorEvent: @"getLampParametersReplyCB" statusCode: rc itemID: lampID];
    }
    else
    {
        [self postUpdateLampParametersForID: lampID withParameters: params];
    }
}

-(void)getLampParametersEnergyUsageMilliwattsFieldReplyWithCode: (LSFResponseCode)rc lampID: (NSString*)lampID andEnergyUsage: (unsigned int)energyUsageMilliwatts
{
    //TODO - implement later, unused at this time
}

-(void)getLampParametersLumensFieldReplyWithCode: (LSFResponseCode)rc lampID: (NSString*)lampID andBrightnessLumens: (unsigned int)brightnessLumens
{
    //TODO - implement later, unused at this time
}

-(void)getLampStateReplyWithCode: (LSFResponseCode)rc lampID: (NSString *)lampID andLampState: (LSFLampState *)state
{
    if (rc != LSF_OK)
    {
        [self postGetLampState: lampID withDelay: RETRY_DELAY];
        [[self.manager lampCollectionManager] sendErrorEvent: @"getLampStateReplyCB" statusCode: rc itemID: lampID];
    }
    else
    {
        [self postUpdateLampStateForID: lampID withState: state];
        [self postGetLampParameters: lampID withDelay: 0];
    }
}

-(void)getLampStateOnOffFieldReplyWithCode: (LSFResponseCode)rc lampID: (NSString *)lampID andOnOff: (BOOL)onOff
{
    if (rc != LSF_OK)
    {
        [self postGetLampStateOnOffField: lampID withDelay: RETRY_DELAY];
        [[self.manager lampCollectionManager] sendErrorEvent: @"getLampStateOnOffFieldReplyCB" statusCode: rc itemID: lampID];
    }
    else
    {
        [self postUpdateLampStateOnOffForID: lampID withOnOff: onOff];
        [self postGetLampParameters: lampID withDelay: 0];
    }
}

-(void)getLampStateHueFieldReplyWithCode: (LSFResponseCode)rc lampID: (NSString *)lampID andHue: (unsigned int)hue
{
    if (rc != LSF_OK)
    {
        [self postGetLampStateHueField: lampID withDelay: RETRY_DELAY];
        [[self.manager lampCollectionManager] sendErrorEvent: @"getLampStateHueFieldReplyCB" statusCode: rc itemID: lampID];
    }
    else
    {
        [self postUpdateLampStateHueForID: lampID withHue: hue];
    }
}

-(void)getLampStateSaturationFieldReplyWithCode: (LSFResponseCode)rc lampID: (NSString *)lampID andSaturation: (unsigned int)saturation
{
    if (rc != LSF_OK)
    {
        [self postGetLampStateSaturationField: lampID withDelay: RETRY_DELAY];
        [[self.manager lampCollectionManager] sendErrorEvent: @"getLampStateSaturationFieldReplyCB" statusCode: rc itemID: lampID];
    }
    else
    {
        [self postUpdateLampStateSaturationForID: lampID withSaturation: saturation];
    }
}

-(void)getLampStateBrightnessFieldReplyWithCode: (LSFResponseCode)rc lampID: (NSString *)lampID andBrightness: (unsigned int)brightness
{
    if (rc != LSF_OK)
    {
        [self postGetLampStateBrightnessField: lampID withDelay: RETRY_DELAY];
        [[self.manager lampCollectionManager] sendErrorEvent: @"getLampStateBrightnessFieldReplyCB" statusCode: rc itemID: lampID];
    }
    else
    {
        [self postUpdateLampStateBrightnessForID: lampID withBrightness: brightness];
        [self postGetLampParameters: lampID withDelay: 0];
    }
}

-(void)getLampStateColorTempFieldReplyWithCode: (LSFResponseCode)rc lampID: (NSString *)lampID andColorTemp: (unsigned int)colorTemp
{
    if (rc != LSF_OK)
    {
        [self postGetLampStateColorTempField: lampID withDelay: RETRY_DELAY];
        [[self.manager lampCollectionManager] sendErrorEvent: @"getLampStateSaturationFieldReplyCB" statusCode: rc itemID: lampID];
    }
    else
    {
        [self postUpdateLampStateColorTempForID: lampID withColorTemp: colorTemp];
    }
}

-(void)resetLampStateReplyWithCode: (LSFResponseCode)rc andLampID: (NSString *)lampID
{
    //TODO - implement later, unused at this time
}

-(void)lampsStateChangedWithID: (NSString *)lampID andLampState: (LSFLampState *)state
{
    [self postUpdateLampStateForID: lampID withState: state];
    [self postGetLampParameters: lampID withDelay: 0];
}

-(void)transitionLampStateReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
//    if (rc != LSF_OK)
//    {
//
//    }
//    [self postGetLampState: lampID withDelay: 0];
}

-(void)pulseLampWithStateReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    //TODO - implement later, unused at this time
}

-(void)pulseLampWithPresetReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    //TODO - implement later, unused at this time
}

-(void)transitionLampStateOnOffFieldReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    if (rc != LSF_OK)
    {
        [self postGetLampStateOnOffField: lampID withDelay: 0];
        [[self.manager lampCollectionManager] sendErrorEvent: @"transitionLampStateOnOffFieldReplyCB" statusCode: rc itemID: lampID];
    }
}

-(void)transitionLampStateHueFieldReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    if (rc != LSF_OK)
    {
        [self postGetLampStateHueField: lampID withDelay: 0];
        [[self.manager lampCollectionManager] sendErrorEvent: @"transitionLampStateHueFieldReplyCB" statusCode: rc itemID: lampID];
    }
}

-(void)transitionLampStateSaturationFieldReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    if (rc != LSF_OK)
    {
        [self postGetLampStateSaturationField: lampID withDelay: 0];
        [[self.manager lampCollectionManager] sendErrorEvent: @"transitionLampStateSaturationFieldReplyCB" statusCode: rc itemID: lampID];
    }
}

-(void)transitionLampStateBrightnessFieldReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    if (rc != LSF_OK)
    {
        [self postGetLampStateBrightnessField: lampID withDelay: 0];
        [[self.manager lampCollectionManager] sendErrorEvent: @"transitionLampStateBrightnessFieldReplyCB" statusCode: rc itemID: lampID];
    }
}

-(void)transitionLampStateColorTempFieldReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    if (rc != LSF_OK)
    {
        [self postGetLampStateColorTempField: lampID withDelay: 0];
        [[self.manager lampCollectionManager] sendErrorEvent: @"transitionLampStateColorTempFieldReplyCB" statusCode: rc itemID: lampID];
    }
}

-(void)getLampFaultsReplyWithCode: (LSFResponseCode)rc lampID: (NSString *)lampID andFaultCodes: (NSArray *)codes
{
    //TODO - implement later, unused at this time
}

-(void)getLampServiceVersionReplyWithCode: (LSFResponseCode)rc lampID: (NSString*)lampID andLampServiceVersion: (unsigned int)lampServiceVersion
{
    //TODO - implement later, unused at this time
}

-(void)clearLampFaultReplyWithCode: (LSFResponseCode)rc lampID: (NSString*)lampID andFaultCode: (LampFaultCode)faultCode
{
    //TODO - implement later, unused at this time
}

-(void)resetLampStateOnOffFieldReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    //TODO - implement later, unused at this time
}

-(void)resetLampStateHueFieldReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    //TODO - implement later, unused at this time
}

-(void)resetLampStateSaturationFieldReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    //TODO - implement later, unused at this time
}

-(void)resetLampStateBrightnessFieldReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    //TODO - implement later, unused at this time
}

-(void)resetLampStateColorTempFieldReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    //TODO - implement later, unused at this time
}

-(void)transitionLampStateToPresetReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    //TODO - implement later, unused at this time
}

-(void)getLampSupportedLanguagesReplyWithCode: (LSFResponseCode)rc lampID: (NSString*)lampID andSupportedLanguages: (NSArray*)supportedLanguages
{
    //TODO - implement later, unused at this time
}

-(void)setLampEffectReplyWithCode: (LSFResponseCode)rc lampID: (NSString *)lampID andEffectID: (NSString *)effectID
{
    //TODO - implement later, unused at this time
}

-(void)getConsolidatedLampDataSetReplyWithCode:(LSFResponseCode)rc lampID:(NSString *)lampID language:(NSString *)language lampName:(NSString *)lampName lampDetails:(LSFSDKLampDetails *)lampDetails lampState:(LSFLampState *)lampState andLampParameters:(LSFSDKLampParameters *)lampParameters
{
    if (rc != LSF_OK)
    {
        [self postGetConsolidatedLampDataSet: lampID withDelay: RETRY_DELAY];
        [[self.manager lampCollectionManager] sendErrorEvent: @"getConsolidatedLampDataSetReplyCB" statusCode: rc itemID: lampID];
    }
    else
    {
        [self postUpdateLampNameForID: lampID andLampName: lampName];
        [self postUpdateLampDetailsForID: lampID withDetails: lampDetails];
        [self postUpdateLampStateForID: lampID withState: lampState];
        [self postUpdateLampParametersForID: lampID withParameters: lampParameters];
    }
}

-(void)postGetLampQueriedAboutDataForID: (NSString *)lampID
{
    NSTimeInterval currentTimeInMs = [[NSDate date] timeIntervalSince1970] * 1000;
    self.prevLampAboutQueryTime = MAX(self.prevLampAboutQueryTime, currentTimeInMs) + ABOUT_DELAY_IN_MS;
    int64_t queryDelay = self.prevLampAboutQueryTime - currentTimeInMs;

    // do not use Lighting thread since fetching Lamp AboutData can take time
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(queryDelay * NSEC_PER_MSEC)), dispatch_get_global_queue(0, 0), ^{
        [LSFSDKAllJoynManager getAboutDataForLampID: lampID];
    });
}

/*
 * Private function implementations
 */
-(void)postUpdateLampID: (NSString *)lampID withDelay: (unsigned int)delay
{
    [self postUpdateLampID: lampID withAboutData: nil andDelay: delay];
}

-(void)postUpdateLampID: (NSString *)lampID withAboutData: (LSFLampAbout *)aboutData andDelay:(unsigned int)delay
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delay * NSEC_PER_SEC)), self.manager.dispatchQueue, ^{
        LSFSDKLamp *lamp = [[self.manager lampCollectionManager] getLampWithID: lampID];

        if (lamp == nil)
        {
            lamp = [[self.manager lampCollectionManager] addLampWithID: lampID];
        }

        LSFLampModel *lampModel = [lamp getLampDataModel];

        if ([lampModel.name isEqualToString: LAMP_DEFAULT_NAME])
        {
            if ([LSFSDKAllJoynManager isControllerServiceLeaderV1])
            {
                // 14.12 and earlier controllers do no support consolidated
                // data set. Thus, we must make individual requests.
                [self postGetLampNameForID: lampID withDelay: 0];
                [self postGetLampState: lampID withDelay: 0];
                [self postGetLampParameters: lampID withDelay: 0];
                [self postGetLampDetails: lampID withDelay: 0];
            }
            else
            {
                [self postGetConsolidatedLampDataSet: lampID withDelay: 0];
            }
        }

        if (aboutData != nil)
        {
            lampModel.aboutData = aboutData;
        }
        else
        {
            [self postGetLampQueriedAboutDataForID:lampID];
        }
    });

    //[self postSendLampChanged: lampID];
}

-(void)postRemoveLampID: (NSString *)lampID
{
    dispatch_async(self.manager.dispatchQueue, ^{
        [[self.manager lampCollectionManager] removeLampWithID: lampID];
    });
}

-(void)postUpdateLampNameForID: (NSString *)lampID andLampName: (NSString *)lampName
{
    dispatch_async(self.manager.dispatchQueue, ^{
        LSFLampModel *lampModel = [[self.manager lampCollectionManager] getModelWithID: lampID];

        if (lampModel != nil)
        {
            BOOL wasInitialized = [lampModel isInitialized];
            lampModel.name = [NSString stringWithString: lampName];

            if (wasInitialized != [lampModel isInitialized])
            {
                [self postSendLampInitialized: lampID];
            }
        }
    });

    [self postSendLampChanged: lampID];
}

-(void)postGetLampNameForID: (NSString *)lampID withDelay: (unsigned int)delay
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delay * NSEC_PER_SEC)), self.manager.dispatchQueue, ^{
        if ([LSFSDKAllJoynManager getControllerConnected])
        {
            [[self.manager lampManager] getLampName: lampID andLanguage: self.manager.defaultLanguage];
        }
    });
}

-(void)postUpdateLampDetailsForID: (NSString *)lampID withDetails: (LSFSDKLampDetails *)lampDetails
{
    dispatch_async(self.manager.dispatchQueue, ^{
        LSFLampModel *lampModel = [[self.manager lampCollectionManager] getModelWithID: lampID];

        if (lampModel != nil)
        {
            BOOL wasInitialized = [lampModel isInitialized];
            lampModel.lampDetails = lampDetails;

            if (wasInitialized != [lampModel isInitialized])
            {
                [self postSendLampInitialized: lampID];
            }
        }
    });

    [self postSendLampChanged: lampID];
}

-(void)postGetLampDetails: (NSString *)lampID withDelay: (unsigned int)delay
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delay * NSEC_PER_SEC)), self.manager.dispatchQueue, ^{
        if ([LSFSDKAllJoynManager getControllerConnected])
        {
            [[self.manager lampManager] getLampDetailsForID: lampID];
        }
    });
}

-(void)postUpdateLampParametersForID: (NSString *)lampID withParameters: (LSFSDKLampParameters *)lampParameters
{
    dispatch_async(self.manager.dispatchQueue, ^{
        LSFLampModel *lampModel = [[self.manager lampCollectionManager] getModelWithID: lampID];

        if (lampModel != nil)
        {
            BOOL wasInitialized = [lampModel isInitialized];
            lampModel.lampParameters = lampParameters;

            if (wasInitialized != [lampModel isInitialized])
            {
                [self postSendLampInitialized: lampID];
            }
        }
    });

    [self postSendLampChanged: lampID];
}

-(void)postGetLampParameters: (NSString *)lampID withDelay: (unsigned int)delay
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delay * NSEC_PER_SEC)), self.manager.dispatchQueue, ^{
        if ([LSFSDKAllJoynManager getControllerConnected])
        {
            [[self.manager lampManager] getLampParametersForID: lampID];
        }
    });
}

-(void)postUpdateLampStateForID: (NSString *)lampID withState: (LSFLampState *)lampState
{
    dispatch_async(self.manager.dispatchQueue, ^{
        LSFConstants *constants = [LSFConstants getConstants];
        LSFLampModel *lampModel = [[self.manager lampCollectionManager] getModelWithID: lampID];

        if (lampModel != nil)
        {
            BOOL wasInitialized = [lampModel isInitialized];

            LSFLampState *newState = [[LSFLampState alloc] initWithOnOff: lampState.onOff brightness: [constants unscaleLampStateValue: lampState.brightness withMax: 100] hue: [constants unscaleLampStateValue: lampState.hue withMax: 360] saturation: [constants unscaleLampStateValue: lampState.saturation withMax: 100] colorTemp: [constants unscaleColorTemp: lampState.colorTemp]];

//            lampModel.state.onOff = lampState.onOff;
//            lampModel.state.brightness = [constants unscaleLampStateValue: lampState.brightness withMax: 100];
//            lampModel.state.hue = [constants unscaleLampStateValue: lampState.hue withMax: 360];
//            lampModel.state.saturation = [constants unscaleLampStateValue: lampState.saturation withMax: 100];
//            lampModel.state.colorTemp = [constants unscaleColorTemp: lampState.colorTemp];

            [lampModel setState: newState];

            if (wasInitialized != [lampModel isInitialized])
            {
                [self postSendLampInitialized: lampID];
            }
        }
    });

    [self postUpdateLampGroupState: lampID];
    [self postSendLampChanged: lampID];
}

-(void)postGetLampState: (NSString *)lampID withDelay: (unsigned int)delay
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delay * NSEC_PER_SEC)), self.manager.dispatchQueue, ^{
        if ([LSFSDKAllJoynManager getControllerConnected])
        {
            [[self.manager lampManager] getLampStateForID: lampID];
        }
    });
}

-(void)postUpdateLampStateOnOffForID: (NSString *)lampID withOnOff: (BOOL)onOff
{
    dispatch_async(self.manager.dispatchQueue, ^{
        LSFLampModel *lampModel = [[self.manager lampCollectionManager] getModelWithID: lampID];

        if (lampModel != nil)
        {
            lampModel.state.onOff = onOff;
        }
    });

    [self postUpdateLampGroupState: lampID];
    [self postSendLampChanged: lampID];
}

-(void)postGetLampStateOnOffField: (NSString *)lampID withDelay: (unsigned int)delay
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delay * NSEC_PER_SEC)), self.manager.dispatchQueue, ^{
        if ([LSFSDKAllJoynManager getControllerConnected])
        {
            [[self.manager lampManager] getLampStateOnOffFieldForID: lampID];
        }
    });
}

-(void)postUpdateLampStateHueForID: (NSString *)lampID withHue: (unsigned int)hue
{
    dispatch_async(self.manager.dispatchQueue, ^{
        LSFLampModel *lampModel = [[self.manager lampCollectionManager] getModelWithID: lampID];

        if (lampModel != nil)
        {
            lampModel.state.hue = [[LSFConstants getConstants] unscaleLampStateValue: hue withMax: 360];;
        }
    });

    [self postUpdateLampGroupState: lampID];
    [self postSendLampChanged: lampID];
}

-(void)postGetLampStateHueField: (NSString *)lampID withDelay: (unsigned int)delay
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delay * NSEC_PER_SEC)), self.manager.dispatchQueue, ^{
        if ([LSFSDKAllJoynManager getControllerConnected])
        {
            [[self.manager lampManager] getLampStateHueFieldForID: lampID];
        }
    });
}

-(void)postUpdateLampStateSaturationForID: (NSString *)lampID withSaturation: (unsigned int)saturation
{
    dispatch_async(self.manager.dispatchQueue, ^{
        LSFLampModel *lampModel = [[self.manager lampCollectionManager] getModelWithID: lampID];

        if (lampModel != nil)
        {
            lampModel.state.saturation = [[LSFConstants getConstants] unscaleLampStateValue: saturation withMax: 100];
        }
    });

    [self postUpdateLampGroupState: lampID];
    [self postSendLampChanged: lampID];
}

-(void)postGetLampStateSaturationField: (NSString *)lampID withDelay: (unsigned int)delay
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delay * NSEC_PER_SEC)), self.manager.dispatchQueue, ^{
        if ([LSFSDKAllJoynManager getControllerConnected])
        {
            [[self.manager lampManager] getLampStateSaturationFieldForID: lampID];
        }
    });
}

-(void)postUpdateLampStateBrightnessForID: (NSString *)lampID withBrightness: (unsigned int)brightness
{
    dispatch_async(self.manager.dispatchQueue, ^{
        LSFLampModel *lampModel = [[self.manager lampCollectionManager] getModelWithID: lampID];

        if (lampModel != nil)
        {
            lampModel.state.brightness = [[LSFConstants getConstants] unscaleLampStateValue: brightness withMax: 100];
        }
    });

    [self postUpdateLampGroupState: lampID];
    [self postSendLampChanged: lampID];
}

-(void)postGetLampStateBrightnessField: (NSString *)lampID withDelay: (unsigned int)delay
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delay * NSEC_PER_SEC)), self.manager.dispatchQueue, ^{
        if ([LSFSDKAllJoynManager getControllerConnected])
        {
            [[self.manager lampManager] getLampStateBrightnessFieldForID: lampID];
        }
    });
}

-(void)postUpdateLampStateColorTempForID: (NSString *)lampID withColorTemp: (unsigned int)colorTemp
{
    dispatch_async(self.manager.dispatchQueue, ^{
        LSFLampModel *lampModel = [[self.manager lampCollectionManager] getModelWithID: lampID];

        if (lampModel != nil)
        {
            lampModel.state.colorTemp = [[LSFConstants getConstants] unscaleColorTemp: colorTemp];
        }
    });

    [self postUpdateLampGroupState: lampID];
    [self postSendLampChanged: lampID];
}

-(void)postGetLampStateColorTempField: (NSString *)lampID withDelay: (unsigned int)delay
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delay * NSEC_PER_SEC)), self.manager.dispatchQueue, ^{
        if ([LSFSDKAllJoynManager getControllerConnected])
        {
            [[self.manager lampManager] getLampStateColorTempFieldForID: lampID];
        }
    });
}

-(void)postGetConsolidatedLampDataSet: (NSString *)lampID withDelay: (unsigned int)delay
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delay * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        if ([LSFSDKAllJoynManager getControllerConnected])
        {
            [[self.manager lampManager] getConsolidatedLampDataSetForID: lampID];
        }
    });
}

-(void)postUpdateLampGroupState: (NSString *)lampID
{
    dispatch_async(self.manager.dispatchQueue, ^{
        [[LSFSDKAllJoynManager getGroupManagerCallback] postUpdateDependentLampGroups: lampID];
    });
}

-(void)postSendLampChanged: (NSString *)lampID
{
    dispatch_async(self.manager.dispatchQueue, ^{
        [[self.manager lampCollectionManager] sendChangedEvent: lampID];
    });
}

-(void)postSendLampInitialized: (NSString *)lampID
{
    dispatch_async(self.manager.dispatchQueue, ^{
        [[self.manager lampCollectionManager] sendInitializedEvent: lampID];
    });
}

@end
