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

#import "LSFScenesCreatePresetViewController.h"
#import "LSFNoEffectTableViewController.h"
#import "LSFTransitionEffectTableViewController.h"
#import "LSFPulseEffectTableViewController.h"
#import "LSFPresetModelContainer.h"
#import "LSFUtilityFunctions.h"
#import "LSFDispatchQueue.h"
#import "LSFConstants.h"
#import "LSFPresetManager.h"
#import "LSFAllJoynManager.h"
#import "LSFPresetModel.h"
#import "LSFEnums.h"

@interface LSFScenesCreatePresetViewController ()

@property (nonatomic) BOOL doneButtonPressed;

-(void)controllerNotificationReceived: (NSNotification *)notification;
-(void)sceneNotificationReceived: (NSNotification *)notification;
-(void)deleteScenesWithIDs: (NSArray *)sceneIDs andNames: (NSArray *)sceneNames;

@end

@implementation LSFScenesCreatePresetViewController

@synthesize sceneID = _sceneID;
@synthesize lampState = _lampState;
@synthesize presetNameTextField = _presetNameTextField;
@synthesize doneButtonPressed = _doneButtonPressed;

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    //Set notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(controllerNotificationReceived:) name: @"ControllerNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(sceneNotificationReceived:) name: @"SceneNotification" object: nil];

    LSFPresetModelContainer *container = [LSFPresetModelContainer getPresetModelContainer];
    int numPresets = [container.presetContainer count];

    [self.presetNameTextField becomeFirstResponder];
    self.presetNameTextField.text = [NSString stringWithFormat: @"Preset %i", ++numPresets];
    self.doneButtonPressed = NO;
}

-(void)viewWillDisappear: (BOOL)animated
{
    [super viewWillDisappear: animated];

    //Clear notification handler
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
        [self dismissViewControllerAnimated: NO completion: nil];
    }
}

/*
 * SceneNotification Handler
 */
-(void)sceneNotificationReceived: (NSNotification *)notification
{
    NSNumber *callbackOp = [notification.userInfo valueForKey: @"operation"];
    NSArray *sceneIDs = [notification.userInfo valueForKey: @"sceneIDs"];
    NSArray *sceneNames = [notification.userInfo valueForKey: @"sceneNames"];

    if ([sceneIDs containsObject: self.sceneID])
    {
        switch (callbackOp.intValue)
        {
            case SceneDeleted:
                [self deleteScenesWithIDs: sceneIDs andNames: sceneNames];
                break;
            default:
                break;
        }
    }
}

-(void)deleteScenesWithIDs: (NSArray *)sceneIDs andNames: (NSArray *)sceneNames
{
    if ([sceneIDs containsObject: self.sceneID])
    {
        int index = [sceneIDs indexOfObject: self.sceneID];

        [self dismissViewControllerAnimated: NO completion: nil];

        dispatch_async(dispatch_get_main_queue(), ^{
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Scene Not Found"
                                                            message: [NSString stringWithFormat: @"The scene \"%@\" no longer exists.", [sceneNames objectAtIndex: index]]
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

    if (![LSFUtilityFunctions checkWhiteSpaces:self.presetNameTextField.text entity: @"Preset Name"])
    {
        return NO;
    }

    BOOL nameMatchFound = [self checkForDuplicateName: self.presetNameTextField.text];

    if (!nameMatchFound)
    {
        self.doneButtonPressed = YES;
        [textField resignFirstResponder];

        dispatch_async(([LSFDispatchQueue getDispatchQueue]).queue, ^{
            LSFLampState *scaledState = [[LSFLampState alloc] initWithOnOff: self.lampState.onOff brightness: self.lampState.brightness hue: self.lampState.hue saturation: self.lampState.saturation colorTemp: self.lampState.colorTemp];

            LSFPresetManager *presetManager = ([LSFAllJoynManager getAllJoynManager]).lsfPresetManager;
            [presetManager createPresetWithState: scaledState andPresetName: self.presetNameTextField.text];
        });

        return YES;
    }

    return NO;
}

-(void)textFieldDidEndEditing: (UITextField *)textField
{
    if (self.doneButtonPressed)
    {
        //[self.navigationController popViewControllerAnimated: YES];

        for (UIViewController *vc in self.navigationController.viewControllers)
        {
            if ([vc isKindOfClass: [LSFNoEffectTableViewController class]])
            {
                [self.navigationController popToViewController: (LSFNoEffectTableViewController *)vc animated: YES];
            }
            else if ([vc isKindOfClass: [LSFTransitionEffectTableViewController class]])
            {
                [self.navigationController popToViewController: (LSFTransitionEffectTableViewController *)vc animated: YES];
            }
            else if ([vc isKindOfClass: [LSFPulseEffectTableViewController class]])
            {
                [self.navigationController popToViewController: (LSFPulseEffectTableViewController *)vc animated: YES];
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
            LSFPresetManager *presetManager = ([LSFAllJoynManager getAllJoynManager]).lsfPresetManager;
            [presetManager createPresetWithState: self.lampState andPresetName: self.presetNameTextField.text];
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
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Duplicate Name"
                                                            message: [NSString stringWithFormat: @"Warning: there is already a preset named \"%@.\" Although it's possible to use the same name for more than one preset, it's better to give each preset a unique name.\n\nKeep duplicate preset name \"%@\"?", name, name]
                                                           delegate: self
                                                  cancelButtonTitle: @"NO"
                                                  otherButtonTitles: @"YES", nil];
            [alert show];

            return YES;
        }
    }

    return NO;
}

@end
