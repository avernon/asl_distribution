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
 * The FTMProgressDescriptor is utilized when the user requests file transfer status
 * updates from either the sender or the receiver. This class will outline all of
 * the files that are being transferred by specifying how many bytes have already been
 * sent or received and give the total length of the file. This will allow the user to
 * see the current progress of each file transfer.
 * 
 * See [FTMFileTransferModule sendingProgressList and [FTMFileTransferModule receiveProgressList].
 *
 * @warning *Note:* This class is not intended to be used directly. All of the
 * supported functionality of this library is intended to be accessed through the
 * FTMFileTransferModule class.
 */
@interface FTMProgressDescriptor : NSObject

/** @name Class Properties */

/*
 * Defines an enumerated type to determine the current state of the file transfer.
 */
typedef enum
{
    IN_PROGRESS,
    PAUSED,
    TIMED_OUT
} State;

/**
 * Specifies the ID of the file being transferred.
 */
@property (nonatomic, strong) NSData *fileID;

/**
 * Specifies the current state of the file transfer.
 */
@property (nonatomic) State state;

/**
 * Specifies the number of bytes that have been transferred.
 */
@property (nonatomic) int bytesTransferred;

/**
 * Specifies the size of the file.
 */
@property (nonatomic) int fileSize;

@end
