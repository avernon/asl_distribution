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
#import "FileTransferBusObject.h"
#import "FTMDirectedAnnouncementManagerDelegate.h"
#import "FTMSendManagerDelegate.h"
#import "FTMOfferManagerDelegate.h"
#import "FTMMessageUtility.h"

/**
 * The FTMFileTransferBusObject is registered with the AllJoyn Bus Attachment and exposes
 * the Data Transfer and File Discovery interfaces to remote session peers. This object
 * listens and responds to remote method calls (not to be confused with signals) made by
 * AllJoyn session peers. Methods are used when a response is needed quickly since signals
 * are too slow. The three methods handled by the bus object are: requestData, requestOffer,
 * and offerFile.
 * 
 * @warning *Note:* This class is not intended to be used directly. All of the
 * supported functionality of this library is intended to be accessed through the
 * FTMFileTransferModule class.
 */
@interface FTMFileTransferBusObject : FileTransferBusObject

/** @name Class Properties */

/**
 * Sets a delegate so the FTMFileTransferBusObject can callback to the FTMDirectedAnnouncementManager.
 *
 * The FTMDirectedAnnouncementManagerDelegate will notify the FTMDirectedAnnouncementManager that an offer
 * request was received.
 *
 * @warning *Note:* This property is write only and does not provide a getter.
 */
@property (nonatomic, strong) id<FTMDirectedAnnouncementManagerDelegate> directedAnnouncementManagerDelegate;

/**
 * Sets a delegate so the FTMFileTransferBusObject can callback to the FTMSendManager.
 *
 * The FTMSendManagerDelegate will notify the FTMSendManager to start sending a file immediately.
 *
 * @warning *Note:* This property is write only and does not provide a getter.
 */
@property (nonatomic, strong) id<FTMSendManagerDelegate> sendManagerDelegate;

/**
 * Sets a delegate so the FTMFileTransferBusObject can callback to the FTMOfferManager.
 *
 * The FTMOfferManagerDelegate will notify the FTMOfferManager when a file offer is received
 * from a remote session peer.
 *
 * @warning *Note:* This property is write only and does not provide a getter.
 */
@property (nonatomic, strong) id<FTMOfferManagerDelegate> offerManagerDelegate;

@end
