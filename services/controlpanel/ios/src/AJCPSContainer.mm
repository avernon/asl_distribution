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

#import "AJCPSContainer.h"
#import "alljoyn/controlpanel/Container.h"
#import "alljoyn/controlpanel/Widget.h"
#import "AJCPSControlPanelDevice.h"
#import "AJCPSAction.h"
#import "AJCPSActionWithDialog.h"
#import "AJCPSLabel.h"
#import "AJCPSProperty.h"
#import "AJCPSDialog.h"
#import "AJCPSErrorWidget.h"

@interface AJCPSContainer ()
// uses Widget's handle
@end

@implementation AJCPSContainer

- (id)initWithHandle:(ajn::services::Container *)handle
{
	self = [super initWithHandle:handle];
	if (self) {
		//self.handle = handle;
	}
	return self;
}

/**
 * Register the BusObjects for this Widget
 * @param bus - the bus to be used
 * @return status - success/failure
 */
- (QStatus)registerObjects:(AJNBusAttachment *)bus
{
	return ((ajn::services::Container *)self.handle)->registerObjects((ajn::BusAttachment *)[bus handle]);
}

/**
 * Unregister the BusObjects for this widget
 * @param bus
 * @return status - success/failure
 */
- (QStatus)unregisterObjects:(AJNBusAttachment *)bus
{
	return ((ajn::services::Container *)self.handle)->unregisterObjects((ajn::BusAttachment *)[bus handle]);
}

/**
 * Get the ChildWidget Vector
 * @return children widgets
 */
//const std : : vector <Widget *>& getChildWidgets() const;
- (NSArray *)getChildWidgets
{
	const std::vector <ajn::services::Widget *> cpp_childWidgets = ((ajn::services::Container *)self.handle)->getChildWidgets();
    
	NSMutableArray *childWidgets = [[NSMutableArray alloc]init];
    
	for (int i = 0; i != cpp_childWidgets.size(); i++) {
        switch (cpp_childWidgets.at(i)->getWidgetType()) {
            case ajn::services::CONTAINER:
                [childWidgets addObject:[[AJCPSContainer alloc]initWithHandle:(ajn::services::Container *)cpp_childWidgets.at(i)]];

                break;
            case ajn::services::ACTION:
                [childWidgets addObject:[[AJCPSAction alloc]initWithHandle:(ajn::services::Action *)cpp_childWidgets.at(i)]];

                break;

            case ajn::services::ACTION_WITH_DIALOG:
                [childWidgets addObject:[[AJCPSActionWithDialog alloc]initWithHandle:(ajn::services::ActionWithDialog *)cpp_childWidgets.at(i)]];

                break;

            case ajn::services::LABEL:
                [childWidgets addObject:[[AJCPSLabel alloc]initWithHandle:(ajn::services::Label *)cpp_childWidgets.at(i)]];

                break;

            case ajn::services::PROPERTY:
                [childWidgets addObject:[[AJCPSProperty alloc]initWithHandle:(ajn::services::Property *)cpp_childWidgets.at(i)]];

                break;
            case ajn::services::DIALOG:
                [childWidgets addObject:[[AJCPSDialog alloc]initWithHandle:(ajn::services::Dialog *)cpp_childWidgets.at(i)]];

                 break;
                
            case ajn::services::ERROR:
                [childWidgets addObject:[[AJCPSErrorWidget alloc]initWithHandle:(ajn::services::ErrorWidget *)cpp_childWidgets.at(i)]];
                
                break;
                
            default:
                NSLog(@"Error. Request to create a widget of unknown type %d",cpp_childWidgets.at(i)->getWidgetType());
                break;
        }
    }

    
	return childWidgets;
}

- (bool)getIsDismissable
{
	return ((ajn::services::Container *)self.handle)->getIsDismissable();
}

@end