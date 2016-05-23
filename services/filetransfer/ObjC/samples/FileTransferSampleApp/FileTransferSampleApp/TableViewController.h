/******************************************************************************
 * Copyright (c) 2013, AllSeen Alliance. All rights reserved.
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
#import "SelectionMadeDelegate.h"

/*
 * This class extends UITableViewController and allows us to specify an array of strings to display,
 * a delegate to call when the user selects a given cell, and table type. This allows tremendous 
 * flexibility to reuse the table regardless of whether we are displaying peer names of file names.
 * The delegate allows us to specify a controller class that will receive the callback when a user
 * selects a row.
 */
@interface TableViewController : UITableViewController

@property (nonatomic, strong) NSArray *stringsToDisplay;
@property (nonatomic, strong) id<SelectionMadeDelegate> selectionMadeDelegate;

@end
