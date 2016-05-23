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

#import <UIKit/UIKit.h>
#import "alljoyn/gateway/AJGWCConnectorApp.h"
#import "AJNSessionOptions.h"

static NSDictionary* STATUS_COLOR = [[NSDictionary alloc]
                                     initWithObjectsAndKeys:
                                     //AJGWCConnectionStatus
                                     [UIColor purpleColor], @"Not initialized",
                                     [UIColor blueColor], @"In progress",
                                     [UIColor greenColor],  @"Connected",
                                     [UIColor orangeColor], @"Not connected",
                                     [UIColor redColor], @"Error",
                                     //AJGWCInstallStatus
                                     [UIColor greenColor], @"Installed",
                                     [UIColor blueColor],@"Install in progress",
                                     [UIColor blueColor], @"Upgrade in progress",
                                     [UIColor blueColor], @"Uninstall in progress",
                                     [UIColor redColor], @"Installation failed",
                                     //AJGWCOperationalStatus
                                     [UIColor greenColor], @"Running",
                                     [UIColor orangeColor], @"Stopped",
                                     nil];

@interface ConnectorAppInfoViewController : UIViewController

@property (weak, nonatomic) AJGWCConnectorApp* connectorApp;
@property (nonatomic) AJNSessionId sessionId;
@property (strong, nonatomic) IBOutlet UILabel *friendlyNameLbl;
@property (strong, nonatomic) IBOutlet UILabel *appVersionLbl;

@property (weak, nonatomic) IBOutlet UILabel *connectivityLbl;
@property (weak, nonatomic) IBOutlet UILabel *operationLbl;
@property (weak, nonatomic) IBOutlet UILabel *installationLbl;

@property (weak, nonatomic) IBOutlet UITableView *aclsTableView;


+ (void)setLabelTextColor:(UILabel*) label forStatus:(NSString*) statusString;
@end
