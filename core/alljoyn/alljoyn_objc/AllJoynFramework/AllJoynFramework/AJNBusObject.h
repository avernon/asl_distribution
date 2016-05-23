////////////////////////////////////////////////////////////////////////////////
// Copyright AllSeen Alliance. All rights reserved.
//
//    Contributed by Qualcomm Connected Experiences, Inc.,
//    with authorization from the AllSeen Alliance, Inc.
//    
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//    
//        http://www.apache.org/licenses/LICENSE-2.0
//    
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//    
//    Pursuant to Section 1 of the License, the work of authorship constituting
//    a Work and any Contribution incorporated in the Work shall mean only that
//    Contributor's code submissions authored by that Contributor.  Any rights
//    granted under the License are conditioned upon acceptance of these
//    clarifications.
////////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import "AJNObject.h"
#import "AJNStatus.h"
#import "AJNSessionOptions.h"
#import "AJNMessage.h"
#import "AJNTranslator.h"

@class AJNBusAttachment;
@class AJNInterfaceDescription;
@class AJNMessageArgument;

/**
 * Message Bus Object base protocol. All application bus object protocols should inherit this.
 */
@protocol AJNBusObject<AJNHandle>

/**
 * Return the path for the object
 *
 * @return Object path
 */
@property (nonatomic, readonly) NSString *path;

/**
 * Get the name of this object.
 * The name is the last component of the path.
 *
 * @return Last component of object path.
 */
@property (nonatomic, readonly) NSString *name;

/**
 * Indicates if this object is secure.
 *
 * @return Return true if authentication is required to emit signals or call methods on this object.
 */
@property (nonatomic, readonly) BOOL isSecure;

/**
 * Flag used to specify if an interface is announced or not here
 * or Alternatively if one uses SetAnnounceFlag function
 * @see AddInterface
 * @see SetAnnounceFlag
 */
typedef enum AJNAnnounceFlag{
    UNANNOUNCED=0,
    ANNOUNCED=1
}AJNAnnounceFlag;

/**
 * AJNBusObject initialization.
 *
 * @param busAttachment  Bus that this object exists on.
 * @param path           Object path for object.
 */
- (id)initWithBusAttachment:(AJNBusAttachment *)busAttachment onPath:(NSString *)path;

/**
 * Called by the message bus when the object has been successfully registered. The object can
 * perform any initialization such as adding match rules at this time.
 */
- (void)objectWasRegistered;

/**
 * Emit PropertiesChanged to signal the bus that this property has been updated
 *
 *
 * @param propertyName  The name of the property being changed
 * @param interfaceName The name of the interface
 * @param value         The new value of the property
 * @param sessionId     ID of the session we broadcast the signal to (0 for all)
 */
- (void)emitPropertyWithName:(NSString *)propertyName onInterfaceWithName:(NSString *)interfaceName changedToValue:(AJNMessageArgument *)value inSession:(AJNSessionId)sessionId;

/**
 * Remove sessionless message sent from this object from local daemon's
 * store/forward cache.
 *
 * @param serialNumber    Serial number of previously sent sessionless signal.
 * @return   ER_OK if successful.
 */
- (QStatus)cancelSessionlessMessageWithSerial:(uint32_t)serialNumber;

/**
 * Remove sessionless message sent from this object from local daemon's
 * store/forward cache.
 *
 * @param message    Message to be removed.
 * @return   ER_OK if successful.
 */
- (QStatus)cancelSessionlessMessageWithMessage:(const AJNMessage *)message;

/**
 * Change the announce flag for an already added interface. Changes in the
 * announce flag are not visible to other devices till Announce is called.
 *
 * @see AboutObj::Announce()
 *
 * @param[in] iface InterfaceDescription for the interface you wish to set
 *                  the the announce flag.
 * @param[in] isAnnounced This interface should be part of the Announce signal
 *                        UNANNOUNCED - this interface will not be part of the Announce
 *                                      signal
 *                        ANNOUNCED - this interface will be part of the Announce
 *                                    signal.
 * @return
 *  - #ER_OK if successful
 *  - #ER_BUS_OBJECT_NO_SUCH_INTERFACE if the interface is not part of the
 *                                     bus object.
 */
- (QStatus)setAnnounceFlagForInterface:(AJNInterfaceDescription *)iface value:(AJNAnnounceFlag)flag;

@end

////////////////////////////////////////////////////////////////////////////////

/**
 * Message Bus Object base class.
 */
@interface AJNBusObject : AJNObject<AJNBusObject>

@property (nonatomic, readonly) NSString *path;

@property (nonatomic, readonly) NSString *name;

@property (nonatomic, readonly) BOOL isSecure;

@property (nonatomic) void *translator;


- (id)initWithPath:(NSString *)path;

- (id)initWithBusAttachment:(AJNBusAttachment *)busAttachment onPath:(NSString *)path;

- (QStatus)registerInterfacesWithBus:(AJNBusAttachment *)busAttachment;

- (void)objectWasRegistered;

- (void)setDescription:(NSString*)description inLanguage:(NSString*)language;

- (void)setDescriptionTranslator:(id<AJNTranslator>)translator;

- (QStatus)setAnnounceFlagForInterface:(AJNInterfaceDescription *)iface value:(AJNAnnounceFlag)flag;

@end
