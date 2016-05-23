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
/**
 * AJGWCAnnouncementData - information coming from the announcement
 * The application should create and maintain an array of AJGWCAnnouncementData objects based on the current set of
 * announcement in the network. See sample application for more.
 */
@interface AJGWCAnnouncementData : NSObject

/**
 * Constructor
 * @param port The port used by the service
 * @param busName Bus name for this announcement
 * @param aboutData The data sent with the Announcement
 * @param objectDescs The objectDescriptions received in announce
 */
- (id)initWithPort:(uint16_t) port  busName:(NSString *)busName aboutData:(NSDictionary *)aboutData objectDescriptions:(NSDictionary *)objectDescs;

/**
 * objectDescriptions getter
 * @return objectDescs The objectDescriptions received in announce
 */
- (NSDictionary *)objectDescriptions;

/**
 * aboutData getter
 * @return aboutData The data sent with the Announcement
 */
- (NSDictionary *)aboutData;

/**
 * port getter
 * @return The port used by the service
 */
- (uint16_t)port;

/**
 * busName getter
 * @return The bus name used by the service
 */
- (NSString*)busName;

@end
