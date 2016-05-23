/******************************************************************************
 * Copyright (c) 2013, AllSeen Alliance. All rights reserved.
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
 * The FTMUnannouncedFileRequestDelegate is required if the developer wishes
 * to allow session peers to request files that have not been explicitly
 * announced or shared. The default behavior is to deny all requests for
 * files that have not been announced or shared.
 * 
 * See [FTMFileTransferModule setUnannouncedFileRequestDelegate:].
 */
@protocol FTMUnannouncedFileRequestDelegate <NSObject>

@required

/** @name Required Methods */

/**
 * Triggered when a request is received for an unannounced file. 
 *
 * @param filePath Specifies the absolute path of file being requested.
 *
 * @return True to allow the request, false to reject the request.
 */
-(BOOL)allowUnannouncedRequestsForFileWithPath: (NSString *) filePath;

@end
