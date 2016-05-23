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

#import "LSFGroupsChangeNameViewController.h"
#import "LSFDispatchQueue.h"
#import "LSFLampGroupManager.h"
#import "LSFAllJoynManager.h"
#import "LSFGroupModelContainer.h"
#import "LSFGroupModel.h"
#import "LSFUtilityFunctions.h"
#import "LSFGroupModel.h"
#import "LSFEnums.h"

@interface LSFGroupsChangeNameViewController ()

@property (nonatomic) BOOL doneButtonPressed;
@property (nonatomic, strong) LSFGroupModel *groupModel;

-(void)controllerNotificationReceived: (NSNotification *)notification;
-(void)groupNotificationReceived: (NSNotification *)notification;
-(void)reloadGroupName;
-(void)deleteGroupsWithIDs: (NSArray *)groupIDs andNames: (NSArray *)groupNames;
-(BOOL)checkForDuplicateName: (NSString *)name;

@end

@implementation LSFGroupsChangeNameViewController

@synthesize groupID = _groupID;
@synthesize groupModel = _groupModel;
@synthesize groupNameTextField = _groupNameTextField;
@synthesize doneButtonPressed = _doneButtonPressed;

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    LSFGroupModelContainer *groupContainer = [LSFGroupModelContainer getGroupModelContainer];
    NSMutableDictionary *groups = groupContainer.groupContainer;
    self.groupModel = [groups valueForKey: self.groupID];

    //Set notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(controllerNotificationReceived:) name: @"ControllerNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(groupNotificationReceived:) name: @"GroupNotification" object: nil];

    [self.groupNameTextField becomeFirstResponder];
    self.groupNameTextField.text = self.groupModel.name;
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
        [self.navigationController popToRootViewControllerAnimated: YES];
    }
}

/*
 * GroupNotification Handler
 */
-(void)groupNotificationReceived: (NSNotification *)notification
{
    NSString *groupID = [notification.userInfo valueForKey: @"groupID"];
    NSNumber *callbackOp = [notification.userInfo valueForKey: @"operation"];
    NSArray *groupIDs = [notification.userInfo valueForKey: @"groupIDs"];
    NSArray *groupNames = [notification.userInfo valueForKey: @"groupNames"];

    if ([self.groupID isEqualToString: groupID] || [groupIDs containsObject: self.groupID])
    {
        switch (callbackOp.intValue)
        {
            case GroupNameUpdated:
                [self reloadGroupName];
                break;
            case GroupDeleted:
                [self deleteGroupsWithIDs: groupIDs andNames: groupNames];
                break;
            default:
                NSLog(@"Operation not found - Taking no action");
                break;
        }
    }
}

-(void)reloadGroupName
{
    LSFGroupModelContainer *groupsContainer = [LSFGroupModelContainer getGroupModelContainer];
    NSMutableDictionary *groups = groupsContainer.groupContainer;
    self.groupModel = [groups valueForKey: self.groupID];

    self.groupNameTextField.text = self.groupModel.name;
}

-(void)deleteGroupsWithIDs: (NSArray *)groupIDs andNames: (NSArray *)groupNames
{
    int index = [groupIDs indexOfObject: self.groupID];

    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Group Not Found"
                                                    message: [NSString stringWithFormat: @"The group \"%@\" no longer exists.", [groupNames objectAtIndex: index]]
                                                   delegate: nil
                                          cancelButtonTitle: @"OK"
                                          otherButtonTitles: nil];
    [alert show];

    [self.navigationController popToRootViewControllerAnimated: YES];
}

/*
 * UITextFieldDelegate Implementation
 */
-(BOOL)textFieldShouldReturn: (UITextField *)textField
{
    if (![LSFUtilityFunctions checkNameLength: self.groupNameTextField.text entity: @"Group Name"])
    {
        return NO;
    }

    if (![LSFUtilityFunctions checkWhiteSpaces:self.groupNameTextField.text entity: @"Group Name"])
    {
        return NO;
    }

    BOOL nameMatchFound = [self checkForDuplicateName: self.groupNameTextField.text];
    
    if (!nameMatchFound)
    {
        self.doneButtonPressed = YES;
        [textField resignFirstResponder];
        
        dispatch_async(([LSFDispatchQueue getDispatchQueue]).queue, ^{
            LSFLampGroupManager *lampGroupManager = ([LSFAllJoynManager getAllJoynManager]).lsfLampGroupManager;
            [lampGroupManager setLampGroupNameForID: self.groupID andName: self.groupNameTextField.text];
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
        [self.groupNameTextField resignFirstResponder];
        
        dispatch_async(([LSFDispatchQueue getDispatchQueue]).queue, ^{
            LSFLampGroupManager *lampGroupManager = ([LSFAllJoynManager getAllJoynManager]).lsfLampGroupManager;
            [lampGroupManager setLampGroupNameForID: self.groupID andName: self.groupNameTextField.text];
        });
    }
}

/*
 * Private functions
 */
-(BOOL)checkForDuplicateName: (NSString *)name
{
    LSFGroupModelContainer *container = [LSFGroupModelContainer getGroupModelContainer];
    NSDictionary *groups = container.groupContainer;
    
    for (LSFGroupModel *model in [groups allValues])
    {
        if ([name isEqualToString: model.name])
        {
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Duplicate Name"
                                                            message: [NSString stringWithFormat: @"Warning: there is already a group named \"%@.\" Although it's possible to use the same name for more than one group, it's better to give each group a unique name.\n\nKeep duplicate group name \"%@\"?", name, name]
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
