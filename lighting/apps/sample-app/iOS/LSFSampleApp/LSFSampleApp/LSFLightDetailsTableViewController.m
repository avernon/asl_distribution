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

#import "LSFLightDetailsTableViewController.h"
#import "LSFEnumConversions.h"
#import "LSFUtilityFunctions.h"
#import <LSFSDKLightingDirector.h>
#import <manager/LSFSDKAllJoynManager.h>

@interface LSFLightDetailsTableViewController ()

@property (nonatomic, strong) NSArray *data;
@property (nonatomic, strong) NSArray *detailsFields;
@property (nonatomic, strong) NSArray *aboutFields;
@property (strong, atomic) UIAlertView *loadingAV;

-(void)leaderModelChangedNotificationReceived:(NSNotification *)notification;
-(void)lampRemovedNotificationReceived: (NSNotification *) notification;
-(void)deleteLampWithID: (NSString *)lampID andName: (NSString *)lampName;

@end

@implementation LSFLightDetailsTableViewController

@synthesize lampID = _lampID;
@synthesize data = _data;
@synthesize detailsFields = _detailsFields;
@synthesize aboutFields = _aboutFields;

-(void)viewDidLoad
{
    [super viewDidLoad];

    self.detailsFields = [LSFUtilityFunctions getLampDetailsFields];
    self.aboutFields = [LSFUtilityFunctions getLampAboutFields];
    self.data = [[NSArray alloc] initWithObjects: self.detailsFields, self.aboutFields, nil];
}

-(void)viewWillAppear: (BOOL)animated
{
    [super viewWillAppear: animated];

    //Set notification handler
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(leaderModelChangedNotificationReceived:) name: @"LSFContollerLeaderModelChange" object: nil];
    [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(lampRemovedNotificationReceived:) name: @"LSFLampRemovedNotification" object: nil];

//    [self showLoadingAlert:@"Fetching lamp details..."];

//    [LSFSDKAllJoynManager getAboutDataForLampID: self.lampID];
    [self.tableView reloadData];

//    [self dismissLoadingAlert];
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

-(void)lampRemovedNotificationReceived: (NSNotification *) notification
{
    LSFSDKLamp *lamp = [notification.userInfo valueForKey: @"lamp"];

    if ([self.lampID isEqualToString: [lamp theID]])
    {
        [self deleteLampWithID: [lamp theID] andName:[lamp name]];
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
 * UITableViewDataSource Implementation
 */
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return [self.data count];
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    if (section == 0)
    {
        return @"Details";
    }
    else
    {
        return @"About";
    }
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if (section == 0)
    {
        return [self.detailsFields count];
    }
    else
    {
        return [self.aboutFields count];
    }
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID: self.lampID];
    LSFSDKLampDetails *lampDetails = [lamp details];
    LSFSDKLampAbout *lampAbout = [lamp about];

    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: @"DetailsCell"];
    
    if ([indexPath section] == 0)
    {
        cell.textLabel.text = [self.detailsFields objectAtIndex: [indexPath row]];
    }
    else
    {
        cell.textLabel.text = [self.aboutFields objectAtIndex: [indexPath row]];
    }
    
    if ([indexPath section] == 0)
    {
        switch ([indexPath row])
        {
            case 0:
                cell.detailTextLabel.text = [LSFEnumConversions convertLampMakeToString: lampDetails.lampMake];
                break;
            case 1:
                cell.detailTextLabel.text = [LSFEnumConversions convertLampModelToString: lampDetails.lampModel];
                break;
            case 2:
                cell.detailTextLabel.text = [LSFEnumConversions convertDeviceTypeToString: lampDetails.deviceType];
                break;
            case 3:
                cell.detailTextLabel.text = [LSFEnumConversions convertLampTypeToString: lampDetails.lampType];
                break;
            case 4:
                cell.detailTextLabel.text = [LSFEnumConversions convertBaseTypeToString: lampDetails.baseType];
                break;
            case 5:
                cell.detailTextLabel.text = [NSString stringWithFormat: @"%u", lampDetails.lampBeamAngle];
                break;
            case 6:
                cell.detailTextLabel.text = lampDetails.dimmable ? @"YES" : @"NO";
                break;
            case 7:
                cell.detailTextLabel.text = lampDetails.color ? @"YES" : @"NO";
                break;
            case 8:
                cell.detailTextLabel.text = lampDetails.variableColorTemp ? @"YES" : @"NO";
                break;
            case 9:
                cell.detailTextLabel.text = lampDetails.hasEffects ? @"YES" : @"NO";
                break;
            case 10:
                cell.detailTextLabel.text = [NSString stringWithFormat: @"%u", lampDetails.minVoltage];
                break;
            case 11:
                cell.detailTextLabel.text = [NSString stringWithFormat: @"%u", lampDetails.maxVoltage];
                break;
            case 12:
                cell.detailTextLabel.text = [NSString stringWithFormat: @"%u", lampDetails.wattage];
                break;
            case 13:
                cell.detailTextLabel.text = [NSString stringWithFormat: @"%u", lampDetails.incandescentEquivalent];
                break;
            case 14:
                cell.detailTextLabel.text = [NSString stringWithFormat: @"%u", lampDetails.maxLumens];
                break;
            case 15:
                cell.detailTextLabel.text = [NSString stringWithFormat: @"%u", lampDetails.minTemperature];
                break;
            case 16:
                cell.detailTextLabel.text = [NSString stringWithFormat: @"%u", lampDetails.maxTemperature];
                break;
            case 17:
                cell.detailTextLabel.text = [NSString stringWithFormat: @"%u", lampDetails.colorRenderingIndex];
                break;
        }
    }
    else
    {
        switch ([indexPath row])
        {
            case 0:
                cell.detailTextLabel.text = lampAbout.appID;
                break;
            case 1:
                cell.detailTextLabel.text = lampAbout.defaultLanguage;
                break;
            case 2:
                cell.detailTextLabel.text = lampAbout.deviceName;
                break;
            case 3:
                cell.detailTextLabel.text = lampAbout.deviceID;
                break;
            case 4:
                cell.detailTextLabel.text = lampAbout.appName;
                break;
            case 5:
                cell.detailTextLabel.text = lampAbout.manufacturer;
                break;
            case 6:
                cell.detailTextLabel.text = lampAbout.modelNumber;
                break;
            case 7:
                cell.detailTextLabel.text = lampAbout.supportedLanguages;
                break;
            case 8:
                cell.detailTextLabel.text = lampAbout.description;
                break;
            case 9:
                cell.detailTextLabel.text = lampAbout.dateOfManufacture;
                break;
            case 10:
                cell.detailTextLabel.text = lampAbout.softwareVersion;
                break;
            case 11:
                cell.detailTextLabel.text = lampAbout.ajSoftwareVersion;
                break;
            case 12:
                cell.detailTextLabel.text = lampAbout.hardwareVersion;
                break;
            case 13:
                cell.detailTextLabel.text = lampAbout.supportURL;
                break;
        }
    }
    
    return cell;
}

-(void)showLoadingAlert:(NSString *)message
{
    self.loadingAV = [[UIAlertView alloc] initWithTitle:@"" message:message delegate:nil cancelButtonTitle:nil otherButtonTitles:nil];
    UIActivityIndicatorView *activityIV = [[UIActivityIndicatorView alloc] initWithFrame:CGRectMake(0, 0, 80, 40)];
    activityIV.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
    [activityIV startAnimating];
    [self.loadingAV setValue:activityIV forKey:@"accessoryView"];
    [self.loadingAV show];
}

-(void)dismissLoadingAlert
{
    [self.loadingAV dismissWithClickedButtonIndex:0 animated:YES];
}

@end
