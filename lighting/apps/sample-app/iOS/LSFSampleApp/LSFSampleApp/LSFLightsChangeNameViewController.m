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

#import "LSFLightsChangeNameViewController.h"
#import "LSFUtilityFunctions.h"
#import "LSFLightsTableViewController.h"
#import "LSFLightInfoTableViewController.h"
#import <LSFSDKLightingDirector.h>

@interface LSFLightsChangeNameViewController ()

@property (nonatomic) BOOL doneButtonPressed;

-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification;
-(void)lampChangedNotificationReceived: (NSNotification *)notification;
-(void)lampRemovedNotificationReceived: (NSNotification *)notification;
-(BOOL)checkForDuplicateName: (NSString *)name;

@end

@implementation LSFLightsChangeNameViewController

@synthesize lampID = _lampID;
@synthesize lampNameTextField = _lampNameTextField;
@synthesize doneButtonPressed = _doneButtonPressed;

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    //Set notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(lampChangedNotificationReceived:) name: @"LSFLampChangedNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(lampRemovedNotificationReceived:) name: @"LSFLampRemovedNotification" object: nil];


    [self.lampNameTextField becomeFirstResponder];
    self.doneButtonPressed = NO;

    [self reloadLampName];
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
 * Notification Handlers
 */
-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification
{
    LSFSDKController *leaderModel = [notification.userInfo valueForKey: @"leader"];
    if (![leaderModel connected])
    {
        [self dismissViewControllerAnimated: YES completion: nil];
    }
}

-(void)lampChangedNotificationReceived: (NSNotification *)notification
{
    NSString *lampID = [[notification.userInfo valueForKey: @"lamp"] theID];
    if ([self.lampID isEqualToString: lampID])
    {
        [self reloadLampName];
    }
}

-(void)lampRemovedNotificationReceived: (NSNotification *)notification
{
    LSFSDKLamp *lamp = [notification.userInfo valueForKey: @"lamp"];
    if ([self.lampID isEqualToString: [lamp theID]])
    {
        [self deleteLampWithID: [lamp theID] andName: [lamp name]];
    }
}

-(void)reloadLampName
{
    self.lampNameTextField.text = [[[LSFSDKLightingDirector getLightingDirector] getLampWithID: self.lampID] name];
}

-(void)deleteLampWithID: (NSString *)lampID andName: (NSString *)lampName
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

/*
 * UITextFieldDelegate Implementation
 */
-(BOOL)textFieldShouldReturn: (UITextField *)textField
{
    if (![LSFUtilityFunctions checkNameLength: self.lampNameTextField.text entity: @"Lamp Name"])
    {
        return NO;
    }

    if (![LSFUtilityFunctions checkWhiteSpaces: self.lampNameTextField.text entity: @"Lamp Name"])
    {
        return NO;
    }

    BOOL nameMatchFound = [self checkForDuplicateName: self.lampNameTextField.text];
    
    if (!nameMatchFound)
    {
        self.doneButtonPressed = YES;
        [textField resignFirstResponder];
        
        dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
            [[[LSFSDKLightingDirector getLightingDirector] getLampWithID:self.lampID] rename: self.lampNameTextField.text];
        });
        
        return YES;
    }
    
    return NO;
}

-(void)textFieldDidEndEditing: (UITextField *)textField
{
    if (self.doneButtonPressed)
    {
        [self.navigationController popViewControllerAnimated: YES];
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
        [self.lampNameTextField resignFirstResponder];

        dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
            [[[LSFSDKLightingDirector getLightingDirector] getLampWithID:self.lampID] rename: self.lampNameTextField.text];
        });
    }
}

/*
 * Private functions
 */
-(BOOL)checkForDuplicateName: (NSString *)name
{
    for (LSFSDKLamp *lamp in [[LSFSDKLightingDirector getLightingDirector] lamps])
    {
        NSString *lampName = [lamp name];

        if ([name isEqualToString: lampName])
        {
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Duplicate Name"
                                                            message: [NSString stringWithFormat: @"Warning: there is already a lamp named \"%@.\" Although it's possible to use the same name for more than one lamp, it's better to give each lamp a unique name.\n\nKeep duplicate lamp name \"%@\"?", name, name]
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
