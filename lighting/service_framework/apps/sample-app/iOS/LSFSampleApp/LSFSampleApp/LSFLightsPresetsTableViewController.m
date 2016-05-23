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

#import "LSFLightsPresetsTableViewController.h"
#import "LSFLightsCreatePresetViewController.h"
#import "LSFLampModelContainer.h"
#import "LSFPresetModelContainer.h"
#import "LSFLampModel.h"
#import "LSFPresetModel.h"
#import "LSFDispatchQueue.h"
#import "LSFAllJoynManager.h"
#import "LSFConstants.h"
#import "LSFEnums.h"

@interface LSFLightsPresetsTableViewController ()

@property (nonatomic, strong) LSFLampModel *lampModel;
@property (nonatomic, strong) NSArray *presetData;
@property (nonatomic, strong) NSMutableArray *presetDataSorted;

-(void)controllerNotificationReceived: (NSNotification *)notification;
-(void)lampNotificationReceived: (NSNotification *)notification;
-(void)deleteLampWithID: (NSString *)lampID andName: (NSString *)lampName;
-(void)presetNotificationReceived: (NSNotification *)notification;
-(void)reloadPresets;
-(BOOL)checkIfLampStateMatchesPreset: (LSFPresetModel *)data;
-(void)sortPresetData;

@end

@implementation LSFLightsPresetsTableViewController

@synthesize lampID = _lampID;
@synthesize lampModel = _lampModel;
@synthesize presetData = _presetData;

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
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(lampNotificationReceived:) name: @"LampNotification" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(presetNotificationReceived:) name: @"PresetNotification" object: nil];
    
    [self reloadPresets];
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
            case LampStateUpdated:
                [self reloadPresets];
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
 * PresetNotification Handler
 */
-(void)presetNotificationReceived: (NSNotification *)notification
{
    [self reloadPresets];
}

-(void)reloadPresets
{
    LSFLampModelContainer *lampsContainer = [LSFLampModelContainer getLampModelContainer];
    NSMutableDictionary *lamps = lampsContainer.lampContainer;
    self.lampModel = [lamps valueForKey: self.lampID];

    LSFPresetModelContainer *container = [LSFPresetModelContainer getPresetModelContainer];
    self.presetData = [container.presetContainer allValues];
    [self sortPresetData];

    [self.tableView reloadData];
}

/*
 * UITableViewDataSource Implementation
 */
-(UITableViewCell *)tableView: (UITableView *)tableView cellForRowAtIndexPath: (NSIndexPath *)indexPath
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

        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: @"PresetCell" forIndexPath: indexPath];
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
        [self performSegueWithIdentifier: @"SavePreset" sender: nil];
        return;
    }

    UITableViewCell *cell = [tableView cellForRowAtIndexPath: indexPath];

    if (cell != nil)
    {
        if (cell.accessoryType == UITableViewCellAccessoryNone)
        {
            cell.accessoryType = UITableViewCellAccessoryCheckmark;
            LSFPresetModel *data = [self.presetDataSorted objectAtIndex: [indexPath row]];

            dispatch_async(([LSFDispatchQueue getDispatchQueue]).queue, ^{
                LSFLampManager *lampManager = ([LSFAllJoynManager getAllJoynManager]).lsfLampManager;
                [lampManager transitionLampID: self.lampID toPresetID: data.theID];
            });

            [self.navigationController popViewControllerAnimated: YES];
        }
        else
        {
            [self.navigationController popViewControllerAnimated: YES];
        }
    }
}

-(NSInteger)numberOfSectionsInTableView: (UITableView *)tableView
{
    return 2;
}

-(NSInteger)tableView: (UITableView *)tableView numberOfRowsInSection: (NSInteger)section
{
    if (section == 0)
    {
        return 1;
    }
    else
    {
        return self.presetDataSorted.count;
    }
}

-(NSString *)tableView: (UITableView *)tableView titleForHeaderInSection: (NSInteger)section
{
    if (section == 1)
    {
        if (![self tableView:self.tableView numberOfRowsInSection:1])
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
        [self.presetDataSorted removeObjectAtIndex: indexPath.row];
        
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
    
    LSFConstants *constants = [LSFConstants getConstants];
    unsigned int scaledBrightness = [constants scaleLampStateValue: self.lampModel.state.brightness withMax: 100];
    unsigned int scaledHue = [constants scaleLampStateValue: self.lampModel.state.hue withMax: 360];
    unsigned int scaledSaturation = [constants scaleLampStateValue: self.lampModel.state.saturation withMax: 100];
    unsigned int scaledColorTemp = [constants scaleColorTemp: self.lampModel.state.colorTemp];

    if ((self.lampModel.state.onOff == data.state.onOff) && (scaledBrightness == data.state.brightness) && (scaledHue == data.state.hue) && (scaledSaturation == data.state.saturation) && (scaledColorTemp == data.state.colorTemp))
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
    self.presetDataSorted = [[NSMutableArray alloc] initWithArray: [self.presetData sortedArrayUsingDescriptors:[NSArray arrayWithObject:sortDesc]]];
}

/*
 * Segue Function
 */
- (void)prepareForSegue: (UIStoryboardSegue *)segue sender: (id)sender
{
    if ([segue.identifier isEqualToString: @"SavePreset"])
    {
        LSFLightsCreatePresetViewController *lcpvc = [segue destinationViewController];
        lcpvc.lampState = self.lampModel.state;
        lcpvc.lampID = self.lampID;
    }
}

@end
