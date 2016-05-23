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

#import "LSFSceneElementV2MembersTableViewController.h"
#import "LSFEffectV2TypeTableViewController.h"
#import "LSFPresetEffectV2TableViewController.h"
#import "LSFUtilityFunctions.h"
#import <LSFSDKLightingDirector.h>

@interface LSFSceneElementV2MembersTableViewController ()

@end

@implementation LSFSceneElementV2MembersTableViewController

@synthesize pendingScene = _pendingScene;
@synthesize pendingSceneElement = _pendingSceneElement;
@synthesize hasNextButton = _hasNextButton;

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear: animated];

    if (self.hasNextButton)
    {
        UIBarButtonItem *nextButton = [[UIBarButtonItem alloc]
                                        initWithTitle: @"Next"
                                        style: UIBarButtonItemStylePlain
                                        target: self
                                        action: @selector(nextButtonPressed)];

        self.navigationItem.rightBarButtonItem = nextButton;
    }

    if (!self.pendingSceneElement.theID)
    {
        self.pendingSceneElement.name = [SCENE_ELEMENT_NAME_PREFIX stringByAppendingString: [LSFUtilityFunctions generateRandomHexStringWithLength: 16]];
    }
}

-(void)buildTable
{
    [self.data addObjectsFromArray: [LSFUtilityFunctions sortLightingItemsByName: [[LSFSDKLightingDirector getLightingDirector] groups]]];
    [self.data addObjectsFromArray: [LSFUtilityFunctions sortLightingItemsByName: [[LSFSDKLightingDirector getLightingDirector] lamps]]];

    NSUInteger allLampsIndex = -1;
    for (int i = 0; i < self.data.count; i++)
    {
        LSFSDKGroupMember *member = [self.data objectAtIndex: i];

        if ([member isKindOfClass: [LSFSDKGroup class]])
        {
            if ([((LSFSDKGroup *)member) isAllLampsGroup])
            {
                allLampsIndex = i;
            }
        }
    }

    if (allLampsIndex != -1)
    {
        [self.data removeObjectAtIndex: allLampsIndex];
    }
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: @"SceneElementMember" forIndexPath:indexPath];
    LSFSDKGroupMember *member = [self.data objectAtIndex: [indexPath row]];

    cell.textLabel.text = member.name;

    if ([member isKindOfClass: [LSFSDKLamp class]])
    {
        cell.imageView.image = [UIImage imageNamed: @"lamps_off_icon.png"];
    }
    else
    {
        cell.imageView.image = [UIImage imageNamed: @"groups_off_icon.png"];
    }

    if ([self.pendingSceneElement.members containsObject: member])
    {
        cell.accessoryType = UITableViewCellAccessoryCheckmark;
        [self.selectedRows addObject: indexPath];
    }

    return cell;
}

-(NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    return @"Tap + to add a new scene element";
}

-(void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue.identifier isEqualToString: @"CreateV2Effect"])
    {
        LSFEffectV2TypeTableViewController *ettvc = [segue destinationViewController];
        ettvc.pendingScene = self.pendingScene;
        ettvc.pendingSceneElement = self.pendingSceneElement;
        ettvc.pendingEffect = (self.pendingSceneElement.pendingEffect) ?  self.pendingSceneElement.pendingEffect : [[LSFPendingEffect alloc] init];
    }
    else if ([segue.identifier isEqualToString: @"PresetEffect"] || [segue.identifier isEqualToString: @"TransitionEffect"] || [segue.identifier isEqualToString: @"PulseEffect"])
    {
        LSFEffectV2TypeTableViewController *etvc = [segue destinationViewController];
        etvc.pendingScene = self.pendingScene;
        etvc.pendingSceneElement = self.pendingSceneElement;
        etvc.pendingEffect = (self.pendingSceneElement.pendingEffect) ?  self.pendingSceneElement.pendingEffect : [[LSFPendingEffect alloc] init];
    }
}

-(void)nextButtonPressed
{
    NSLog(@"%s", __FUNCTION__);
    if ([self processSelections])
    {
        if (self.pendingSceneElement.pendingEffect.theID)
        {
            switch (self.pendingSceneElement.pendingEffect.type)
            {
                case PRESET:
                    [self performSegueWithIdentifier: @"PresetEffect" sender: self];
                    break;
                case TRANSITION:
                    [self performSegueWithIdentifier: @"TransitionEffect" sender: self];
                    break;
                case PULSE:
                    [self performSegueWithIdentifier: @"PulseEffect" sender: self];
                    break;
            }
        }
        else if (self.pendingSceneElement.hasEffect)
        {
            [self performSegueWithIdentifier: @"CreateV2Effect" sender: self];
        }
        else
        {
            [self performSegueWithIdentifier: @"PresetEffect" sender: self];
        }
    }
}

-(BOOL)processSelections
{
    if (self.selectedRows.count > 0)
    {
        self.pendingSceneElement.members = [[NSMutableArray alloc] init];
        self.pendingSceneElement.capability = [[LSFSDKCapabilityData alloc] init];
        for (NSIndexPath *indexPath in self.selectedRows)
        {
            LSFSDKGroupMember *member = [self.data objectAtIndex: indexPath.row];
            [self.pendingSceneElement.members addObject: member];
            [self.pendingSceneElement.capability includeData: [member getCapabilities]];

            if ([member isKindOfClass: [LSFSDKLamp class]])
            {
                self.pendingSceneElement.hasEffect = self.pendingSceneElement.hasEffect || ((LSFSDKLamp *)member).details.hasEffects;
            }
            else if ([member isKindOfClass: [LSFSDKGroup class]])
            {
                for (LSFSDKLamp *lamp in [((LSFSDKGroup *) member) getLamps])
                {
                    self.pendingSceneElement.hasEffect = self.pendingSceneElement.hasEffect || lamp.details.hasEffects;
                }
            }
        }

        return YES;
    }
    else
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Scene Element Error"
                                                        message: [NSString stringWithFormat: @"Error you must select at least one lamp or group to be part of the Scene Element"]
                                                       delegate: self
                                              cancelButtonTitle: @"OK"
                                              otherButtonTitles: nil];
        [alert show];

        return NO;
    }
}

@end
