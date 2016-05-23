/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "alljoyn/Status.h"
#import "AJCPSContainer.h"
#import "AJCPSControlPanelListener.h"
#import "AJCPSControllerUpdateEvents.h"
#import "AJCPSControlPanel.h"

@interface ControllerModel : NSObject <AJCPSControlPanelListener>
@property (strong, nonatomic) NSString *unit;
@property (strong, nonatomic) AJCPSControlPanel *controlPanel;
@property (strong, nonatomic) NSArray *widgetsContainer;
@property (strong, nonatomic) id<ControllerUpdateEvents> delegate;
@property (strong, nonatomic,readonly) NSArray *supportedLanguages;

-(void)pushChildContainer:(AJCPSContainer *)containerToMoveTo;

-(NSInteger)popChildContainer;

-(QStatus)switchLanguage:(NSString *)language;

-(QStatus)switchLanguageForNotificationAction:(AJCPSRootWidget *)rootWidget;

-(QStatus)loadRootWidget:(AJCPSRootWidget *)rootWidget;

-(void)setSupportedLanguagesForNotificationAction:(AJCPSNotificationAction *) notificationAction;
@end
