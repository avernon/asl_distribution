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

#import <Foundation/Foundation.h>
#import "alljoyn/controlpanel/Dialog.h"
#import "AJCPSRootWidget.h"

/**
 * AJCPSDialog is used to display a Dialog.
 */
@interface AJCPSDialog : AJCPSRootWidget

- (id)initWithHandle:(ajn ::services ::Dialog *)handle;


/**
 * Get the Number of Actions in the Dialog
 * @return Number of Actions
 */
- (uint16_t)getNumActions;

/**
 * Get the Message of the Dialog
 * @return the message
 */
- (NSString *)getMessage;

/**
 * Get the LabelAction1 of the Dialog
 * @return the message
 */
- (NSString *)getLabelAction1;

/**
 * Get the LabelAction2 of the Dialog
 * @return the message
 */
- (NSString *)getLabelAction2;

/**
 * Get the LabelAction3 of the Dialog
 * @return the message
 */
- (NSString *)getLabelAction3;

/**
 * Call to execute this Dialog's Action 1 remotely
 * @return status - success/failure
 */
- (QStatus)executeAction1;

/**
 * Call to execute this Dialog's Action 2 remotely
 * @return status - success/failure
 */
- (QStatus)executeAction2;

/**
 * Call to execute this Dialog's Action 3 remotely
 * @return status - success/failure
 */
- (QStatus)executeAction3;



@end
