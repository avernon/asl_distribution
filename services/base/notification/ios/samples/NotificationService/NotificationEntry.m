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


#import "NotificationEntry.h"
#import "NotificationUtils.h"


@interface NotificationEntry ()
@property (strong, nonatomic) AJNSNotification *ajnsNotification;
@property (weak,nonatomic) ConsumerViewController *consumerViewController;

@end

@implementation NotificationEntry

- (id)initWithAJNSNotification:(AJNSNotification *) ajnsNotification andConsumerViewController:(ConsumerViewController *)consumerViewController
{
    self = [super init];
    if (self) {
        self.consumerViewController = consumerViewController;
        self.ajnsNotification = ajnsNotification;
    }
    return self;
}


-(void)setAjnsNotification:(AJNSNotification *)ajnsNotification
{
  
    _ajnsNotification = ajnsNotification;
  
    //show AJNSNotification on self.notificationTextView
    NSString *nstr = @"";
    NSString *lang;
    bool matchLangFlag = false;
    
    nstr = [nstr stringByAppendingString:[AJNSNotificationEnums AJNSMessageTypeToString:[ajnsNotification messageType]]];
    nstr = [nstr stringByAppendingFormat:@" "];
    
    // get the msg NotificationText

    for (AJNSNotificationText *nt in ajnsNotification.ajnsntArr) {
        lang = [nt getLanguage];
        if ([lang isEqualToString:self.consumerViewController.consumerLang]) {
            nstr = [nstr stringByAppendingString:lang];
            nstr = [nstr stringByAppendingFormat:@": "];
            nstr = [nstr stringByAppendingString:[nt getText]];
            nstr = [nstr stringByAppendingFormat:@" "];
            matchLangFlag = true;
        }
    } //for
    
    if (!matchLangFlag) {
        nstr = [nstr stringByAppendingString:[NSString stringWithFormat:@"\nUnknown language(s) in notification,\n the last one was '%@'",lang]];
        self.text = nstr;
        [self.consumerViewController.logger debugTag:[[self class] description] text:@"The received message lang does not match the consumer lang settings"];
        return;
    }
    
    // get the msg NotificationText
    NSString *richIconUrl = [ajnsNotification richIconUrl];
    if ([NotificationUtils textFieldIsValid:richIconUrl]) {
        nstr = [nstr stringByAppendingFormat:@"\nicon: %@", richIconUrl];
    }
    
    // get the msg richAudioUrl
    __strong NSMutableArray *richAudioUrlArray = [[NSMutableArray alloc] init];
    
    [ajnsNotification richAudioUrl:richAudioUrlArray];
    int i = 0;
    for (int x = 0; x != [richAudioUrlArray count]; x++) {
        [self.consumerViewController.logger debugTag:[[self class] description] text:[NSString stringWithFormat:@"%d", i]];
        i++;
        NSString *lang = [(AJNSRichAudioUrl *)[richAudioUrlArray objectAtIndex:x] language];
        NSString *audiourl = [(AJNSRichAudioUrl *)[richAudioUrlArray objectAtIndex:x] url];
        [self.consumerViewController.logger debugTag:[[self class] description] text:[NSString stringWithFormat:@"lang[%@]", lang]];
        [self.consumerViewController.logger debugTag:[[self class] description] text:[NSString stringWithFormat:@"audiourl[%@]", audiourl]];
        if ([lang isEqualToString:(self.consumerViewController.consumerLang)]) {
            nstr = [nstr stringByAppendingFormat:@"\naudio: %@", audiourl];
        }
    } //for
    
    [self.consumerViewController.logger debugTag:[[self class] description] text:([NSString stringWithFormat:@"Adding notification to view:\n %@", nstr])];
    
    
    self.text = nstr;
}

@end
