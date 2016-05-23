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
#import <alljoyn/Status.h>
#import "AllJoynFramework/AJNMessageArgument.h"
#import "FTMFileDescriptor.h"

/**
 * The FTMMessageUtility class provides a set of functions that package Objective-C and
 * FTMFileTransferModule data types into an AJNMessageArgument objects. This ensures that
 * the custom objects as well as primitive Objective-C data types can be sent over AllJoyn. 
 * Conversely, this class provides a set of functions that unpackage AJNMessageArgument objects
 * into FTMFileTransferModule and Objective-C data types.
 *
 * @warning *Note:* This class is not intended to be used directly. All of the
 * supported functionality of this library is intended to be accessed through the
 * FTMFileTransferModule class.
 */
@interface FTMMessageUtility : NSObject

/** @name Conversion From Objective-C Type to AllJoyn Message Argument */

/**
 * Converts an NSData file ID object into an AllJoyn message argument.
 *
 * This function handles the conversion from an objective-c type to a C++ type that can
 * be sent over AllJoyn.
 *
 * @param fileID Specifies the ID of a file.
 *
 * @return Instance of AJNMessageArgument.
 */
+ (AJNMessageArgument *)messageArgumentFromFileID: (NSData *)fileID;

/**
 * Converts an NSData object into an AllJoyn message argument.
 *
 * This function handles the conversion from an objective-c type to a C++ type that can
 * be sent over AllJoyn.
 *
 * @param data Specifies the NSData bytes to be converted.
 *
 * @return Instance of AJNMessageArgument.
 */
+ (AJNMessageArgument *)messageArgumentFromData: (NSData *)data;

/**
 * Converts an array of FTMFileDescriptor objects to an AllJoyn message argument.
 *
 * This function handles the conversion from an objective-c type to a C++ type that can
 * be sent over AllJoyn.
 *
 * @param fileList Specifies an array of FTMFileDescriptor objects.
 *
 * @return Instance of AJNMessageArgument.
 */
+ (AJNMessageArgument *)messageArgumentFromFileList: (NSArray *)fileList;

/**
 * Converts a FTMFileDescriptor object to an AllJoyn message argument.
 *
 * This function handles the conversion from an objective-c type to a C++ type that can
 * be sent over AllJoyn.
 *
 * @param fd Specifies a FTMFileDescriptor object.
 *
 * @return Instance of AJNMessageArgument.
 */
+ (AJNMessageArgument *)messageArgumentFromFileDescriptor: (FTMFileDescriptor *)fd;

/** @name Conversion From AllJoyn Message Argument to Objective-C Type */

/**
 * Converts an AllJoyn message argument to an NSData object.
 *
 * This function handles the conversion from a C++ type to an Objective-C type.
 *
 * @param message Specifies an AllJoyn message argument object.
 *
 * @return NSData object that represents the ID of a file.
 */
+ (NSData *)fileIDFromMessageArgument: (AJNMessageArgument *)message;

/**
 * Converts an AllJoyn message argument to an NSData object.
 *
 * This function handles the conversion from a C++ type to an Objective-C type.
 *
 * @param message Specifies an AllJoyn message argument object.
 *
 * @return NSData object that represents the ID of a file.
 */
+ (NSData *)dataFromMessageArgument: (AJNMessageArgument *)message;

/**
 * Converts an AllJoyn message argument to a FTMFileDescriptor object.
 *
 * This function handles the conversion from a C++ type to an Objective-C type.
 *
 * @param message Specifies an AllJoyn message argument object.
 *
 * @return Instance of a FTMFileDescriptor object.
 */
+ (FTMFileDescriptor *)descriptorFromMessageArgument: (AJNMessageArgument *)message;

/**
 * Converts an AllJoyn message argument to an array of FTMFileDescriptor objects.
 *
 * This function handles the conversion from a C++ type to an Objective-C type.
 *
 * @param message Specifies an AllJoyn message argument object.
 *
 * @return Array of FTMFileDescriptor objects.
 */
+ (NSArray *)descriptorArrayFromMessageArgument: (AJNMessageArgument *) message;

@end

