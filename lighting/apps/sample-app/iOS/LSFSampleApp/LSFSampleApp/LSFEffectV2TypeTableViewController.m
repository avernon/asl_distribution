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

#import "LSFEffectV2TypeTableViewController.h"
#import "LSFEffectV2PropertiesTableViewController.h"
#import "LSFPresetEffectV2TableViewController.h"
#import "LSFTransitionEffectV2TableViewController.h"
#import "LSFPulseEffectV2TableViewController.h"

@interface LSFEffectV2TypeTableViewController ()

@end

@implementation LSFEffectV2TypeTableViewController

@synthesize pendingScene = _pendingScene;
@synthesize pendingSceneElement = _pendingSceneElement;
@synthesize pendingEffect = _pendingEffect;

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear: animated];

    if (self.pendingEffect.theID)
    {
        self.selectedIndexPath = [NSIndexPath indexPathForRow: self.pendingEffect.type inSection: 0];
        [self nextButtonPressed: nil];
    }
}

-(void)buildTable
{
    [self.data addObject: @"Preset"];
    [self.data addObject: @"Transition"];
    [self.data addObject: @"Pulse"];
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: @"EffectType" forIndexPath:indexPath];

    if (self.selectedIndexPath == nil && indexPath.row == 0)
    {
        self.selectedIndexPath = indexPath;
        cell.accessoryType = UITableViewCellAccessoryCheckmark;
    }

    NSString *effectType = [self.data objectAtIndex: [indexPath row]];
    cell.textLabel.text = effectType;

    if ([effectType isEqualToString: @"Preset"])
    {
        cell.imageView.image = [UIImage imageNamed: @"list_constant_icon.png"];
    }
    else if ([effectType isEqualToString: @"Transition"])
    {
        cell.imageView.image = [UIImage imageNamed: @"list_transition_icon.png"];
    }
    else if ([effectType isEqualToString: @"Pulse"])
    {
        cell.imageView.image = [UIImage imageNamed: @"list_pulse_icon.png"];
    }

    return cell;
}

-(NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    return @"Select the Effect type";
}

-(void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    NSString *identifier = segue.identifier;
    LSFEffectV2PropertiesTableViewController *etvc = [segue destinationViewController];
    etvc.pendingSceneElement = self.pendingSceneElement;
    etvc.pendingScene = self.pendingScene;
    etvc.pendingEffect = self.pendingEffect;

    if ([identifier isEqualToString: @"TransitionEffect"])
    {
        etvc.pendingEffect.duration = 5000;
    }
    else if ([identifier isEqualToString: @"PulseEffect"])
    {
        etvc.pendingEffect.duration = 500;
    }
}

-(IBAction)nextButtonPressed:(id)sender
{
    NSLog(@"%s", __FUNCTION__);
    switch (self.selectedIndexPath.row)
    {
        case 0:
            self.pendingEffect.type = PRESET;
            [self performSegueWithIdentifier: @"PresetEffect" sender: self];
            break;
        case 1:
            self.pendingEffect.type = TRANSITION;
            [self performSegueWithIdentifier: @"TransitionEffect" sender: self];
            break;
        case 2:
            self.pendingEffect.type = PULSE;
            [self performSegueWithIdentifier: @"PulseEffect" sender: self];
            break;
    }
}

-(IBAction)cancelButtonPressed: (id)sender
{
    [self dismissViewControllerAnimated: YES completion: nil];
}

@end
