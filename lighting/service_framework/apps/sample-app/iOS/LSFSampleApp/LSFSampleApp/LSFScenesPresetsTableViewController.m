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

#import "LSFScenesPresetsTableViewController.h"
#import "LSFAllJoynManager.h"
#import "LSFDispatchQueue.h"
#import "LSFPresetModelContainer.h"
#import "LSFPresetModel.h"
#import "LSFScenesCreatePresetViewController.h"
#import "LSFConstants.h"
#import "LSFNoEffectTableViewController.h"
#import "LSFTransitionEffectTableViewController.h"
#import "LSFPulseEffectTableViewController.h"
#import "LSFEnums.h"

@interface LSFScenesPresetsTableViewController ()

@property (nonatomic, strong) NSArray *presetData;
@property (nonatomic, strong) NSArray *presetDataSorted;

-(void)controllerNotificationReceived: (NSNotification *)notification;
-(void)sceneNotificationReceived: (NSNotification *)notification;
-(void)deleteScenesWithIDs: (NSArray *)sceneIDs andNames: (NSArray *)sceneNames;
-(void)presetNotificationReceived: (NSNotification *)notification;

@end

@implementation LSFScenesPresetsTableViewController

@synthesize sceneID = _sceneID;
@synthesize lampState = _lampState;
@synthesize effectSender = _effectSender;
@synthesize endStateFlag = _endStateFlag;

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];
    self.navigationItem.rightBarButtonItem = self.editButtonItem;

    //Set notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(controllerNotificationReceived:) name: @"ControllerNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(sceneNotificationReceived:) name: @"SceneNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(presetNotificationReceived:) name: @"PresetNotification" object: nil];

    [self reloadPresets];
}

-(void)viewWillDisappear: (BOOL)animated
{
    [super viewWillDisappear: animated];

    if([self.effectSender isKindOfClass:[LSFNoEffectTableViewController class]])
    {
        ((LSFNoEffectTableViewController*)self.effectSender).nedm.state = self.lampState;
    }
    else if ([self.effectSender isKindOfClass:[LSFTransitionEffectTableViewController class]])
    {
        ((LSFTransitionEffectTableViewController*)self.effectSender).tedm.state = self.lampState;
    }
    else if ([self.effectSender isKindOfClass:[LSFPulseEffectTableViewController class]])
    {
        if (self.endStateFlag)
        {
            ((LSFPulseEffectTableViewController*)self.effectSender).pedm.endState = self.lampState;
        }
        else
        {
            ((LSFPulseEffectTableViewController*)self.effectSender).pedm.state = self.lampState;
        }
    }

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
 * PresetNotification Handler
 */
-(void)presetNotificationReceived: (NSNotification *)notification
{
    [self reloadPresets];
}

-(void)reloadPresets
{
    LSFPresetModelContainer *container = [LSFPresetModelContainer getPresetModelContainer];
    self.presetData = [container.presetContainer allValues];
    [self sortPresetData];

    [self.tableView reloadData];
}

/*
 * UITableViewDataSource Implementation
 */
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.section == 0)
    {
        UITableViewCell *cell = [[UITableViewCell alloc] init];
        cell.textLabel.text = @"Save New Preset";
        cell.textLabel.textColor = [UIColor colorWithRed: 0 green: 0.478431 blue: 1.0 alpha: 1.0];
        return cell;
    }
    else
    {
        LSFPresetModel *data = [self.presetDataSorted objectAtIndex: [indexPath row]];
        BOOL stateMatchesPreset = [self checkIfLampStateMatchesPreset: data];

        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: @"ScenePresetCell" forIndexPath:indexPath];
        cell.textLabel.text = data.name;

        if (stateMatchesPreset)
        {
            cell.accessoryType = UITableViewCellAccessoryCheckmark;
        }
        else
        {
            cell.accessoryType = UITableViewCellAccessoryNone;
        }

        return cell;
    }
}

-(void)tableView: (UITableView *)tableView didSelectRowAtIndexPath: (NSIndexPath *)indexPath
{
    if (indexPath.section == 0)
    {
        [self performSegueWithIdentifier: @"SaveScenePreset" sender: nil];
        return;
    }

    UITableViewCell *cell = [tableView cellForRowAtIndexPath: indexPath];

    if (cell != nil)
    {
        if (cell.accessoryType == UITableViewCellAccessoryNone)
        {
            cell.accessoryType = UITableViewCellAccessoryCheckmark;
            LSFPresetModel *data = [self.presetDataSorted objectAtIndex: [indexPath row]];

            self.lampState.brightness = data.state.brightness;
            self.lampState.hue = data.state.hue;
            self.lampState.saturation = data.state.saturation;
            self.lampState.colorTemp = data.state.colorTemp;


            if([self.effectSender isKindOfClass:[LSFNoEffectTableViewController class]])
            {
                ((LSFNoEffectTableViewController*)self.effectSender).nedm.state = self.lampState;
            }
            else if ([self.effectSender isKindOfClass:[LSFTransitionEffectTableViewController class]])
            {
                ((LSFTransitionEffectTableViewController*)self.effectSender).tedm.state = self.lampState;
            }
            else if ([self.effectSender isKindOfClass:[LSFPulseEffectTableViewController class]])
            {
                if (self.endStateFlag)
                {
                    ((LSFPulseEffectTableViewController*)self.effectSender).pedm.endState = self.lampState;
                }
                else
                {
                    ((LSFPulseEffectTableViewController*)self.effectSender).pedm.state = self.lampState;
                }
            }

            [self.navigationController popViewControllerAnimated: YES];
        }
        else
        {
            [self.navigationController popViewControllerAnimated: YES];
        }
    }
    else
    {
        //NSLog(@"Cell is nil");
    }
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 2;
}

/*
 * UITableViewDataSource Implementation
 */
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if (section == 0)
    {
        return 1;
    }
    else
    {
        LSFPresetModelContainer *container = [LSFPresetModelContainer getPresetModelContainer];
        return [container.presetContainer count];
    }
}

-(NSString *)tableView: (UITableView *)tableView titleForHeaderInSection: (NSInteger)section
{
    if (section == 1)
    {
        if (![self tableView: self.tableView numberOfRowsInSection:1])
        {
            return @"No presets have been saved yet";
        }
        else
        {
            return @"Presets";
        }
    }

    return @" ";
}

-(BOOL)tableView: (UITableView *)tableView canEditRowAtIndexPath: (NSIndexPath *)indexPath
{
    return indexPath.section == 1 ? YES : NO;
}

-(void)tableView: (UITableView *)tableView commitEditingStyle: (UITableViewCellEditingStyle)editingStyle forRowAtIndexPath: (NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete)
    {
        LSFPresetModel *data = [self.presetDataSorted objectAtIndex: [indexPath row]];

        LSFPresetModelContainer *container = [LSFPresetModelContainer getPresetModelContainer];
        [container.presetContainer removeObjectForKey: data.theID];

        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];

        dispatch_async(([LSFDispatchQueue getDispatchQueue]).queue, ^{
            LSFPresetManager *presetManager = ([LSFAllJoynManager getAllJoynManager]).lsfPresetManager;
            [presetManager deletePresetWithID: data.theID];
        });
    }
}

-(CGFloat)tableView: (UITableView *)tableView heightForHeaderInSection: (NSInteger)section
{
    if (section == 0)
    {
        return 20.0f;
    }

    return UITableViewAutomaticDimension;
}

/*
 * Private functions
 */
-(BOOL)checkIfLampStateMatchesPreset: (LSFPresetModel *)data
{
    BOOL returnValue = NO;

    if (((self.lampState.onOff == data.state.onOff) && (self.lampState.brightness == data.state.brightness) && (self.lampState.hue == data.state.hue) && (self.lampState.saturation == data.state.saturation) && self.lampState.colorTemp == data.state.colorTemp))
    {
        returnValue = YES;
    }

    return returnValue;
}

-(void)sortPresetData
{
    NSSortDescriptor *sortDesc = [NSSortDescriptor sortDescriptorWithKey:@"name" ascending:YES comparator:^NSComparisonResult(id obj1, id obj2) {
        return [(NSString *)obj1 compare:(NSString *)obj2 options:NSCaseInsensitiveSearch];
    }];
    self.presetDataSorted = [self.presetData sortedArrayUsingDescriptors:[NSArray arrayWithObject:sortDesc]];
}

/*
 * Segue Function
 */
- (void)prepareForSegue: (UIStoryboardSegue *)segue sender: (id)sender
{
    if ([segue.identifier isEqualToString: @"SaveScenePreset"])
    {
        LSFScenesCreatePresetViewController *scpvc = [segue destinationViewController];
        scpvc.lampState = self.lampState;
        scpvc.sceneID = self.sceneID;
    }
}

@end
