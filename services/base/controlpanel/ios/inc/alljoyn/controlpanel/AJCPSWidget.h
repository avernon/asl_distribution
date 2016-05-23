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
#import <AJNBusAttachment.h>

#import "AJCPSLanguageSet.h"
#import "AJCPSControlPanelEnums.h"
#import "AJCPSControlPanelEnums.h"
#import "alljoyn/controlpanel/Widget.h"

@class AJCPSControlPanelDevice;

/**
 * AJCPSWidget is a base class for all Widgets.
 */
@interface AJCPSWidget : NSObject

- (id)initWithHandle:(ajn ::services ::Widget *)handle;

/**
 * Get the widgetType of the Widget
 * @return widgetType
 */
- (AJCPSWidgetType)getWidgetType;

/**
 * Get the name of the Widget
 * @return widgetName
 */
- (NSString *)getWidgetName;

/**
 * Get the mode of the Widget
 * @return controlPanelMode
 */
- (AJCPSControlPanelMode)getControlPanelMode;

/**
 * Get this widget's RootWidget
 * @return rootWidget
 */
- (const AJCPSWidget *)getRootWidget;

/**
 * Get the Device of the widget
 * @return device
 */
- (const AJCPSControlPanelDevice *)getDevice;

/**
 * Get the Interface Version of the Widget
 * @return interface Version
 */
- (const uint16_t)getInterfaceVersion;

/**
 * Get the isSecured boolean
 * @return true/false
 */
- (bool)getIsSecured;

/**
 * Get IsEnabled boolean
 * @return true/false
 */
- (bool)getIsEnabled;

/**
 * Get IsWritable boolean
 * @return true/false
 */
- (bool)getIsWritable;

/**
 * Get the States of the Widget
 * @return states
 */
- (uint32_t)getStates;

/**
 * Get the BgColor of the Widget
 * @return bgColor
 */
- (uint32_t)getBgColor;

/**
 * Get the Label of the Widget
 * @return label
 */
- (NSString *)getLabel;

/**
 * Get the array of Hints for the Widget
 * @return Array of hints
 */
//    const std::vector<uint16_t>& getHints;
- (NSArray *)getHints;

/**
 * Register the BusObjects for this Widget
 * @param bus The bus used to register the busObject
 * @param objectPath The objectPath of the busObject
 * @return ER_OK if successful.
 */
- (QStatus)registerObjects:(AJNBusAttachment *)bus atObjectPath:(NSString *)objectPath;

/**
 * Refresh the Widget
 * @param bus bus used for refreshing the object
 * @return ER_OK if successful.
 */
- (QStatus)refreshObjects:(AJNBusAttachment *)bus;

/**
 * Unregister the BusObjects for this widget
 * @param bus A reference to the AJNBusAttachment.
 * @return ER_OK if successful.
 */
- (QStatus)unregisterObjects:(AJNBusAttachment *)bus;

@property (nonatomic, readonly)ajn::services::Widget * handle;

@end