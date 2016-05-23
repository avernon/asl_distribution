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

#import "DetailsCell.h"

@implementation DetailsCell

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {

    }
    return self;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];
    
    if ([self.notificationEntry dismissed]) {
        [self setAccessoryType:UITableViewCellAccessoryNone];
        [self.notificationEntry setChosen:NO];
        return;
    }

    if(selected)
    {
        if (self.accessoryType == UITableViewCellAccessoryNone) {
            [self setAccessoryType:UITableViewCellAccessoryCheckmark];
            [self.notificationEntry setChosen:YES];
        } else {
            [self setAccessoryType:UITableViewCellAccessoryNone];
            [self.notificationEntry setChosen:NO];
        }
    }
}



-(void)setNotificationEntry:(NotificationEntry *)notificationEntry
{
    _notificationEntry = notificationEntry;
    
    self.detailsLabel.text = notificationEntry.text;
    
    if([self.notificationEntry chosen])
    {
        [self setAccessoryType:UITableViewCellAccessoryCheckmark];
    } else {
        [self setAccessoryType:UITableViewCellAccessoryNone];
    }
    
    if([self.notificationEntry dismissed])
    {
        [self setBackgroundColor:[UIColor yellowColor]];
    } else {
        [self setBackgroundColor:[UIColor whiteColor]];
    }
}

@end
