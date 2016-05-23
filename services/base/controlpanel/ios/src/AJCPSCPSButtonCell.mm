/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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

#import "AJCPSCPSButtonCell.h"
#import "AJCPSAction.h"

@implementation CPSButtonCell

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        self.cpsButton = [UIButton buttonWithType:UIButtonTypeSystem];
        
        [self.cpsButton setFrame:CGRectMake(10,0,300,60)];
        [self.cpsButton.titleLabel setFont:[UIFont systemFontOfSize:13]];
        [self.cpsButton addTarget:self action:@selector(touchUpInsideAction:) forControlEvents:UIControlEventTouchUpInside];
        [self.contentView addSubview:self.cpsButton];
        [self reloadInputViews];
    }
    return self;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];
}

- (void)touchUpInsideAction:(id)sender {
    
    NSLog(@"Pressed %@",[self.cpsButton titleLabel].text);
    
    QStatus status = [((AJCPSAction *)self.actionWidget) executeAction];
    if (status != ER_OK) {
        NSLog(@"execute Action returned error %d, %@",status, [AJNStatus descriptionForStatusCode:status]);
    }
}

-(void)setActionWidget:(AJCPSAction *)actionWidget
{
    _actionWidget = actionWidget;
    [self.cpsButton setTitle:[self.actionWidget getLabel] forState:UIControlStateNormal];
    [self.cpsButton setEnabled:[self.actionWidget getIsEnabled]?YES:NO];
    // We do not use [self.actionWidget getBgColor] so the iOS look and feel remain the same
    
}

@end
