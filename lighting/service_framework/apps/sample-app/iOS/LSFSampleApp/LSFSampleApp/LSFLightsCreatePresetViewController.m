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

#import "LSFLightsCreatePresetViewController.h"
#import "LSFPresetModelContainer.h"
#import "LSFPresetModel.h"
#import "LSFDispatchQueue.h"
#import "LSFAllJoynManager.h"
#import "LSFConstants.h"
#import "LSFUtilityFunctions.h"
#import "LSFLightInfoTableViewController.h"
#import "LSFEnums.h"

@interface LSFLightsCreatePresetViewController ()

@property (nonatomic) BOOL doneButtonPressed;

-(void)controllerNotificationReceived: (NSNotification *)notification;
-(void)lampNotificationReceived: (NSNotification *)notification;
-(void)deleteLampWithID: (NSString *)lampID andName: (NSString *)lampName;

@end

@implementation LSFLightsCreatePresetViewController

@synthesize lampID = _lampID;
@synthesize lampState = _lampState;
@synthesize presetNameTextField = _presetNameTextField;
@synthesize doneButtonPressed = _doneButtonPressed;

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    LSFPresetModelContainer *container = [LSFPresetModelContainer getPresetModelContainer];
    int numPresets = [container.presetContainer count];

    [self.presetNameTextField becomeFirstResponder];
    self.presetNameTextField.text = [NSString stringWithFormat: @"Preset %i", ++numPresets];
    self.doneButtonPressed = NO;

    //Set lamps notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(controllerNotificationReceived:) name: @"ControllerNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(lampNotificationReceived:) name: @"LampNotification" object: nil];
}

-(void)viewWillDisappear: (BOOL)animated
{
    [super viewWillDisappear: animated];

    //Clear lamps notification handler
    [[NSNotificationCenter defaultCenter] removeObserver: self];
}

-(void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

/*
 * ControllerNotification Handler
 */
-(void)controllerNotificationReceived: (NSNotification *)notification
{
    NSDictionary *userInfo = notification.userInfo;
    NSNumber *controllerStatus = [userInfo valueForKey: @"status"];

    if (controllerStatus.intValue == Disconnected)
    {
        [self.navigationController popToRootViewControllerAnimated: YES];
    }
}

/*
 * LampNotification Handler
 */
-(void)lampNotificationReceived: (NSNotification *)notification
{
    NSString *lampID = [notification.userInfo valueForKey: @"lampID"];
    NSNumber *callbackOp = [notification.userInfo valueForKey: @"operation"];

    if ([self.lampID isEqualToString: lampID])
    {
        switch (callbackOp.intValue)
        {
            case LampDeleted:
                [self deleteLampWithID: lampID andName: [notification.userInfo valueForKey: @"lampName"]];
                break;
            default:
                NSLog(@"Operation not found - Taking no action");
                break;
        }
    }
}

-(void)deleteLampWithID: (NSString *)lampID andName: (NSString *)lampName
{
    if ([self.lampID isEqualToString: lampID])
    {
        [self.navigationController popToRootViewControllerAnimated: YES];

        dispatch_async(dispatch_get_main_queue(), ^{
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Connection Lost"
                                                            message: [NSString stringWithFormat: @"Unable to connect to \"%@\".", lampName]
                                                           delegate: nil
                                                  cancelButtonTitle: @"OK"
                                                  otherButtonTitles: nil];
            [alert show];
        });
    }
}

/*
 * UITextFieldDelegate Implementation
 */
-(BOOL)textFieldShouldReturn: (UITextField *)textField
{

    if (![LSFUtilityFunctions checkNameLength: self.presetNameTextField.text entity: @"Preset Name"])
    {
        return NO;
    }

    if (![LSFUtilityFunctions checkWhiteSpaces: self.presetNameTextField.text entity: @"Preset Name"])
    {
        return NO;
    }
    
    BOOL nameMatchFound = [self checkForDuplicateName: self.presetNameTextField.text];
    
    if (!nameMatchFound)
    {
        self.doneButtonPressed = YES;
        [textField resignFirstResponder];
        
        dispatch_async(([LSFDispatchQueue getDispatchQueue]).queue, ^{
            LSFConstants *constants = [LSFConstants getConstants];
            
            unsigned int scaledBrightness = [constants scaleLampStateValue: self.lampState.brightness withMax: 100];
            unsigned int scaledHue = [constants scaleLampStateValue: self.lampState.hue withMax: 360];
            unsigned int scaledSaturation = [constants scaleLampStateValue: self.lampState.saturation withMax: 100];
            unsigned int scaledColorTemp = [constants scaleColorTemp: self.lampState.colorTemp];
            
            LSFLampState *scaledState = [[LSFLampState alloc] initWithOnOff: self.lampState.onOff brightness: scaledBrightness hue: scaledHue saturation: scaledSaturation colorTemp: scaledColorTemp];
            
            LSFPresetManager *presetManager = ([LSFAllJoynManager getAllJoynManager]).lsfPresetManager;
            [presetManager createPresetWithState: scaledState andPresetName: self.presetNameTextField.text];
        });
        
        return YES;
    }

    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Duplicate Name"
                                                    message: [NSString stringWithFormat: @"Warning: there is already a preset named \"%@.\" Although it's possible to use the same name for more than one preset, it's better to give each preset a unique name.\n\nKeep duplicate preset name \"%@\"?", self.presetNameTextField.text, self.presetNameTextField.text]
                                                   delegate: self
                                          cancelButtonTitle: @"NO"
                                          otherButtonTitles: @"YES", nil];
    [alert show];

    return NO;
}

-(void)textFieldDidEndEditing: (UITextField *)textField
{
    if (self.doneButtonPressed)
    {
        //[self.navigationController popViewControllerAnimated: YES];

        for (UIViewController *vc in self.navigationController.viewControllers)
        {
            if ([vc isKindOfClass: [LSFLightInfoTableViewController class]])
            {
                [self.navigationController popToViewController: (LSFLightInfoTableViewController *)vc animated: YES];
            }
        }
    }
}

/*
 * UIAlertViewDelegate implementation
 */
-(void)alertView: (UIAlertView *)alertView clickedButtonAtIndex: (NSInteger)buttonIndex
{
    if (buttonIndex == 0)
    {
        [alertView dismissWithClickedButtonIndex: 0 animated: NO];
    }
    
    if (buttonIndex == 1)
    {
        [alertView dismissWithClickedButtonIndex: 1 animated: NO];
        
        self.doneButtonPressed = YES;
        [self.presetNameTextField resignFirstResponder];
        
        dispatch_async(([LSFDispatchQueue getDispatchQueue]).queue, ^{
            LSFConstants *constants = [LSFConstants getConstants];

            unsigned int scaledBrightness = [constants scaleLampStateValue: self.lampState.brightness withMax: 100];
            unsigned int scaledHue = [constants scaleLampStateValue: self.lampState.hue withMax: 360];
            unsigned int scaledSaturation = [constants scaleLampStateValue: self.lampState.saturation withMax: 100];
            unsigned int scaledColorTemp = [constants scaleColorTemp: self.lampState.colorTemp];

            LSFLampState *scaledState = [[LSFLampState alloc] initWithOnOff: self.lampState.onOff brightness: scaledBrightness hue: scaledHue saturation: scaledSaturation colorTemp: scaledColorTemp];

            LSFPresetManager *presetManager = ([LSFAllJoynManager getAllJoynManager]).lsfPresetManager;
            [presetManager createPresetWithState: scaledState andPresetName: self.presetNameTextField.text];
        });
    }
}

/*
 * Private functions
 */
-(BOOL)checkForDuplicateName: (NSString *)name
{
    LSFPresetModelContainer *container = [LSFPresetModelContainer getPresetModelContainer];
    NSDictionary *presets = container.presetContainer;
    
    for (LSFPresetModel *model in [presets allValues])
    {
        if ([name isEqualToString: model.name])
        {
            return YES;
        }
    }
    
    return NO;
}

@end
