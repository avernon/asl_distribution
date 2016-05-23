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

#import <Foundation/Foundation.h>
#import "alljoyn/controlpanel/ActionWithDialog.h"
#import "AJCPSWidget.h"
#import "AJCPSDialog.h"

/**
 * AJCPSActionWithDialog is used to display a Button.
 * Upon pressing the button a Dialog is displayed on the Controller side.
 */
@interface AJCPSActionWithDialog : AJCPSWidget

- (id)initWithHandle:(ajn ::services ::ActionWithDialog *)handle;


/**
 * Get the ChildDialog of the Action
 * @return dialog
 */
- (AJCPSDialog *)getChildDialog;

/**
 * Unregister the BusObjects for this and children Widgets
 * @param bus - the bus used to unregister the busObjects
 * @return status - success/failure
 */
- (QStatus)unregisterObjects:(AJNBusAttachment *)bus;

@end
