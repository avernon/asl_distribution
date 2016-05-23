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
#import "FTMFileDescriptor.h"

/**
 * The FTMOfferReceivedDelegate can be used by developers to determine the default
 * action taken when a file offer is received from a session peer. The default
 * behavior is to deny all file offers. The function acceptFileOfferFrom:forFile:
 * should be implemented to return to true if you wish to accept files offered by
 * remote session peers.
 * 
 * See [FTMFileTransferModule setOfferReceivedDelegate:].
 */
@protocol FTMOfferReceivedDelegate <NSObject>

@required

/** @name Required Methods */

/**
 * Triggered when a file offer is received. 
 * 
 * If the delegate is not implemented, the offer will be rejected by default.
 *
 * @param peer Specifies the peer offering the file.
 * @param file Specifies the FTMFileDescriptor for the file being offered.
 *
 * @return True to accept the offer, false to reject the offer.
 */
-(BOOL)acceptFileOfferFrom: (NSString *)peer forFile: (FTMFileDescriptor *)file;

@end
