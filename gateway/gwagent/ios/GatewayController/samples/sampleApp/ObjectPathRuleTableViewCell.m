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

#import "ObjectPathRuleTableViewCell.h"


@implementation ObjectPathRuleTableViewCell

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];
}
- (IBAction)configureButtonTouchUpInside:(id)sender {
    [self.rules switchObjectPathConfiguration:_objPathInfo];

    [self updateCell];
}
- (IBAction)allowSubObjectsTouchUpInside:(id)sender {
    [self.rules switchObjectPathAllowSubObjects:_objPathInfo];

    [self updateCell];
}

-(void)setObjPathInfo:(VisualObjPathInfo *)objPathInfo
{
    _objPathInfo = objPathInfo;

    NSString *friendlyName = [objPathInfo.objectPath friendlyName];

    if (![friendlyName isEqual:@""]) {
        self.ruleNameLbl.text = friendlyName;
    } else {
        self.ruleNameLbl.text = [objPathInfo.objectPath path];
    }

    [self updateCell];
}

-(void)updateCell
{
    if (_objPathInfo.configured) {
        [self.configureButton setTitle:@"Added" forState:UIControlStateNormal];
    } else {
        [self.configureButton setTitle:@"Add" forState:UIControlStateNormal];
    }

    if ([_objPathInfo.objectPath isPrefix]) {
        [self.allowSubObjectsButton setTitle:@"Sub Objects Allowed" forState:UIControlStateNormal];
    } else {
        [self.allowSubObjectsButton setTitle:@"Allow Sub Objects" forState:UIControlStateNormal];
    }

    self.configureButton.enabled = _objPathInfo.enabled;
    if (![_objPathInfo.objectPath isPrefixAllowed]) {
        [self.allowSubObjectsButton setTitle:@"Sub Obj Not Allowed" forState:UIControlStateNormal];
        self.allowSubObjectsButton.enabled = NO;
    } else {
        self.allowSubObjectsButton.enabled = _objPathInfo.enabled;
    }
}
@end
