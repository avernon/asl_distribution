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

#import "LSFEffectV2NumericPropertyViewController.h"

@interface LSFEffectV2NumericPropertyViewController ()

@end

@implementation LSFEffectV2NumericPropertyViewController

@synthesize pendingEffect = _pendingEffect;
@synthesize effectType = _effectType;
@synthesize effectProperty = _effectProperty;

-(void) viewWillAppear:(BOOL)animated
{
    [super viewWillAppear: animated];
    [self.propertyTextField becomeFirstResponder];

    [self populatePropertyField];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (IBAction)doneButtonPressed:(id)sender
{
    switch (self.effectProperty)
    {
        case DURATION:
        {
            if (![self checkIfValueExceedsMaximum: ([self.propertyTextField.text doubleValue] * 1000.0)])
            {
                self.pendingEffect.duration = ([self.propertyTextField.text doubleValue] * 1000.0);
            }
            else
            {
                return;
            }
            break;
        }
        case PERIOD:
        {
            if (![self checkIfValueExceedsMaximum: ([self.propertyTextField.text doubleValue] * 1000.0)])
            {
                unsigned int pulsePeriod = ([self.propertyTextField.text doubleValue] * 1000.0);
                self.pendingEffect.period = pulsePeriod;
            }
            else
            {
                return;
            }
            break;
        }
        case NUM_PULSES:
        {
            if (![self checkIfValueExceedsMaximum: strtoull([self.propertyTextField.text UTF8String], NULL, 0)])
            {
                self.pendingEffect.pulses = ((unsigned int)strtoull([self.propertyTextField.text UTF8String], NULL, 0));
            }
            else
            {
                return;
            }
            break;
        }
        default:
            NSLog(@"Invalid property type for text field");
            return;
    }

    [self.propertyTextField resignFirstResponder];
    [self.navigationController popViewControllerAnimated: YES];
}

-(void)populatePropertyField
{
    switch (self.effectProperty)
    {
        case DURATION:
            if (self.effectType == TRANSITION)
            {
                self.propertyTextField.placeholder = @"Enter transition duration in seconds";
            }
            else
            {
                self.propertyTextField.placeholder = @"Enter pulse duration in seconds";
            }
            break;
        case PERIOD:
            self.propertyTextField.placeholder = @"Enter pulse period in seconds";
            break;
        case NUM_PULSES:
        {
            self.propertyTextField.placeholder = @"Enter number of pulses";
            self.propertyTextField.keyboardType = UIKeyboardTypeNumberPad;
            break;
        }
        default:
            NSLog(@"EffectProperty is not of a numeric type");
            break;
    }
}

-(BOOL)checkIfValueExceedsMaximum: (unsigned long long)value
{
    if (value > 4294967295)
    {
        [self showErrorMessage];
        return YES;
    }
    else
    {
        return NO;
    }
}

-(void)showErrorMessage
{
    NSString *field;

    switch (self.effectProperty)
    {
        case DURATION:
            if (self.effectType == TRANSITION)
            {
                field = @"transition duration";
            }
            else
            {
                field = @"pulse duration";
            }
            break;
        case PERIOD:
            field = @"pulse period";
            break;
        case NUM_PULSES:
            field = @"number of pulses";
        default:
            NSLog(@"EffectProperty is not of a numeric type");
            break;
    }

    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                    message: [NSString stringWithFormat: @"Value entered for %@ is too large", field]
                                                   delegate: nil
                                          cancelButtonTitle: @"OK"
                                          otherButtonTitles: nil];
    [alert show];
}


@end
