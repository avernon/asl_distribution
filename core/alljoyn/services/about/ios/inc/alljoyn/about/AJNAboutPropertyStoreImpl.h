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
#import "alljoyn/Status.h"
#import "AJNMessageArgument.h"
#import "alljoyn/about/AboutPropertyStoreImpl.h"
#import "AJNPropertyStore.h"
#import "AJNPropertyStoreProperty.h"
@class PropertyStoreImpl;
@class AJNMessageArgument;

typedef ajn::services::AboutPropertyStoreImpl * (^HandleAllocationBlock)(void);

/**
 AJNAboutPropertyStoreImpl is the default implementation , it is responsible to store the properties of the AJNAboutService and QCSConfigService in memory.
 */
__deprecated
@interface AJNAboutPropertyStoreImpl : NSObject <AJNPropertyStore>

/**
 List of PropertyStore keys.
 */
typedef enum {
    DEVICE_ID = 0,
    DEVICE_NAME = 1,
    APP_ID = 2,
    APP_NAME = 3,
    DEFAULT_LANG = 4,
    SUPPORTED_LANGS = 5,
    DESCRIPTION = 6,
    MANUFACTURER = 7,
    DATE_OF_MANUFACTURE = 8,
    MODEL_NUMBER = 9,
    SOFTWARE_VERSION = 10,
    AJ_SOFTWARE_VERSION = 11,
    HARDWARE_VERSION = 12,
    SUPPORT_URL = 13,
    NUMBER_OF_KEYS = 14
} AJNPropertyStoreKey;

/**
 Initializer
 */
- (id)init __deprecated;

/**
 Designated initializer
 Create an AJNAboutPropertyStoreImpl Object using the passed parameters.
 @param Block a block that return a pointer to the C++ property store implementation.
 @return AJNAboutPropertyStoreImpl if successful.
 */
- (id)initWithHandleAllocationBlock:(HandleAllocationBlock) Block __deprecated;

/**
 ReadAll populate a AJNMessageArgument according to the given languageTag and filter.
 @param languageTag The language to use for the action (NULL means default).
 @param filter Describe which properties to read.
 @param all A reference to AJNMessageArgument [out].
 @return ER_OK if successful.
 */
- (QStatus)readAll:(const char*)languageTag withFilter:(PFilter)filter ajnMsgArg:(AJNMessageArgument **)all __deprecated;

/**
 Update is not implemented in this class.
 @param name not used
 @param languageTag not used
 @param value not used
 @return ER_NOT_IMPLEMENTED
 */
- (QStatus)Update:(const char *)name languageTag:(const char *)languageTag ajnMsgArg:(AJNMessageArgument *)value __deprecated;

/**
 Delete is not implemented in this class.
 @param name not used
 @param languageTag not used
 @return ER_NOT_IMPLEMENTED
 */
- (QStatus)delete:(const char *)name languageTag:(const char *)languageTag __deprecated;

/**
 property will return a AJNPropertyStoreProperty according to a property key. Each property key defines one kind of properties
 @param propertyKey one of AJNPropertyStoreKey
 @return AJNPropertyStoreProperty*
 */
- (AJNPropertyStoreProperty*) property:(AJNPropertyStoreKey)propertyKey __deprecated;

/**
 property same as above with language
 @param propertyKey one of AJNPropertyStoreKey
 @param language The language to use for the action (NULL means default).
 @return AJNPropertyStoreProperty*
 */
- (AJNPropertyStoreProperty*) property:(AJNPropertyStoreKey)propertyKey withLanguage:(NSString *)language __deprecated;

/**
 setDeviceId sets the device ID property in the property store
 @param deviceId new device ID to set
 @return ER_OK if successful.
 */
- (QStatus)setDeviceId:(NSString *)deviceId __deprecated;

/**
 setDeviceName sets the device name property in the property store
 @param deviceName new device name to set
 @return ER_OK if successful.
 */
- (QStatus)setDeviceName:(NSString *)deviceName __attribute__ ((deprecated)) __deprecated;

/**
 setDeviceName sets the device name property in the property store
 @param deviceName new device name to set
 @param language define this property for a specific language
 @return ER_OK if successful.
 */
- (QStatus)setDeviceName:(NSString *)deviceName language:(NSString *)language __deprecated;

/**
 setAppId sets the app ID property in the property store
 @param appId new app ID to set
 @return ER_OK if successful.
 */
- (QStatus)setAppId:(NSString *)appId __deprecated;
/**
 setAppName sets the app name property in the property store
 @param appName new app name to set
 @return ER_OK if successful.
 */
- (QStatus)setAppName:(NSString *)appName __deprecated;
/**
 setDefaultLang sets the default language property in the property store
 @param defaultLang new default language to set
 @return ER_OK if successful.
 */
- (QStatus)setDefaultLang:(NSString *)defaultLang __deprecated;
/**
 setSupportedLangs sets the suppoerted languages property in the property store
 @param supportedLangs an array of NSStrings with the languages (i.e. @"en",@"ru")
 @return ER_OK if successful.
 */
- (QStatus)setSupportedLangs:(NSArray *)supportedLangs __deprecated;

/**
 setDescription sets the description property in the property store per language
 @param description new description string to set
 @param language the language for this description
 @return ER_OK if successful.
 */
- (QStatus)setDescription:(NSString *)description language:(NSString *)language __deprecated;
/**
 setManufacturer sets the manufacturer property in the property store per language
 @param manufacturer new manufacturer string to set
 @param language the language for this manufacturer
 @return ER_OK if successful.
 */
- (QStatus)setManufacturer:(NSString *)manufacturer  language:(NSString *)language __deprecated;

/**
 setDateOfManufacture sets the date of manufacture property in the property store
 @param dateOfManufacture date of manufacture to set
 @return ER_OK if successful.
 */
- (QStatus)setDateOfManufacture:(NSString *)dateOfManufacture __deprecated;
/**
 setSoftwareVersion sets the software version property in the property store
 @param softwareVersion the new software version to set
 @return ER_OK if successful.
 */
- (QStatus)setSoftwareVersion:(NSString *)softwareVersion __deprecated;
/**
 setAjSoftwareVersion sets the alljoyn software version property in the property store
 @param ajSoftwareVersion alljoyn software version to set
 @return ER_OK if successful.
 */
- (QStatus)setAjSoftwareVersion:(NSString *)ajSoftwareVersion __deprecated;
/**
 setHardwareVersion sets the alljoyn software version property in the property store
 @param hardwareVersion hardware version to set
 @return ER_OK if successful.
 */
- (QStatus)setHardwareVersion:(NSString *)hardwareVersion __deprecated;

/**
 setModelNumber sets the model number property in the property store
 @param modelNumber the model number to set
 @return ER_OK if successful.
 */
- (QStatus)setModelNumber:(NSString *)modelNumber __deprecated;

/**
 setSupportUrl sets the support URL property in the property store
 @param supportUrl support url to set
 @return ER_OK if successful.
 */
- (QStatus)setSupportUrl:(NSString *)supportUrl __deprecated;

/**
 propertyStoreName returns the property store name for a specific property store key
 @param propertyStoreKey one of AJNPropertyStoreKey
 @return the name corresponding to the key
 */
- (NSString*)propertyStoreName:(AJNPropertyStoreKey) propertyStoreKey __deprecated;

/**
 getHandle get the C++ handle of the property store in use
 @return ajn::services::AboutPropertyStoreImpl* or inheriting children
 */
- (ajn::services::AboutPropertyStoreImpl *)getHandle __deprecated;

@end
