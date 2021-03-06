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

#import "alljoyn/about/AJNAboutPropertyStoreImpl.h"
#import "AJCFGConfigLogger.h"

/**
 AJCFGPropertyStoreImpl is the default implementation of the objective-c ConfigService(it based on the AJNAboutPropertyStoreImpl class).
 */
@interface AJCFGPropertyStoreImpl : AJNAboutPropertyStoreImpl

/**
 Create a AJCFGPropertyStoreImpl with a reference to a persistent store.
 @param filePath Path to a persistent store file.
 @return AJCFGPropertyStoreImpl if successful.
 */
- (id)initPointerToFactorySettingFile:(NSString *)filePath;

/**
 Reset all property to the factory settings (was Delete).
 </br>factory reset is used only for languageTag = "".
 */
- (void)factoryReset;

/**
 ReadAll populate an AJNMessageArgument according to the given languageTag and filter.
 @param languageTag The language to use for the action (nil means default).
 @param filter Describe which properties to read.
 @param all A reference to AJNMessageArgument [out].
 @return ER_OK if successful.
 */
- (QStatus)readAll:(const char *)languageTag withFilter:(PFilter)filter ajnMsgArg:(AJNMessageArgument **)all;

/**
 Update an AJNMessageArgument according to the given languageTag and filter.
 @param name The property key name.
 @param languageTag The language to use for the action (nil means default).
 @param value The property value.
 @return ER_OK if successful.
 */
- (QStatus)Update:(const char *)name languageTag:(const char *)languageTag ajnMsgArg:(AJNMessageArgument *)value;

/**
 Reset a property to the factory settings (was Delete). Reset is used only for languageTag = "".
 @param name The property key name.
 @param languageTag The language to use for the action (nil means default).
 @return ER_OK if successful.
 */
- (QStatus)reset:(const char *)name languageTag:(const char *)languageTag;

#pragma mark - Persistent getters

/**
 Persistent getter by a key.
 @param key Key to look for in the defaults store(languageTag = "").
 @return the value of the key if key is in the store.
 */
- (NSString *)getPersistentValue:(NSString *)key;

/**
 Get the property store key enum value according to the property key string.
 @param propertyStoreName property key string.
 @return a property key enum value.
 */
- (AJNPropertyStoreKey)getPropertyStoreKeyFromName:(const char *)propertyStoreName;

/**
 Get the service pass code.
 @return the service pass code it has been set.
 */
- (NSString *)getPasscode;

#pragma mark - Persistent setters
/**
 Set the default language property in the property store.
 </br> If the input param is nil - NSUserDefaults entry will be used. If NSUserDefaults entry is not available - factory default is used.
 @param defaultLang New default language to set.
 @return ER_OK if successful.
 */
- (QStatus)setDefaultLang:(NSString *)defaultLang;

/**
 Set the device name property in the property store.
 </br> If the input param is nil - NSUserDefaults entry will be used. If NSUserDefaults entry is not available - factory default is used.
 @param deviceName New device name to set.
 @return ER_OK if successful.
 */
- (QStatus)setDeviceName:(NSString *)deviceName;

/**
 Set the device id property in the property store.
 </br> If the input param is nil - NSUserDefaults entry will be used. If NSUserDefaults entry is not available - factory default is used.
 @param deviceId New device id to set.
 @return ER_OK if successful.
 */
- (QStatus)setDeviceId:(NSString *)deviceId;

/**
 Set the device pass code property in the property store.
 @param passCode New device pass code to set.
 @return ER_OK if successful.
 */
- (QStatus)setPasscode:(NSString *)passCode;

@end

/**
 PropertyStoreImplAdapter enable bind the C++ AboutPropertyStoreImpl API with an objective-c AJCFGPropertyStoreImpl object.
 */

class PropertyStoreImplAdapter : public ajn::services::AboutPropertyStoreImpl
{
public:
	PropertyStoreImplAdapter(AJCFGPropertyStoreImpl * objc_PropertyStoreImpl)
	{
		m_objc_PropertyStoreImpl = objc_PropertyStoreImpl;
	};
    
	void FactoryReset()
	{
		[m_objc_PropertyStoreImpl factoryReset];
	}
    
	virtual QStatus ReadAll(const char *languageTag, Filter filter, ajn::MsgArg& all)
	{
		if (filter == ANNOUNCE || filter == READ) {
			return ajn::services::AboutPropertyStoreImpl::ReadAll(languageTag, filter, all);
		}
        
		if (languageTag[0] != '\0' && languageTag[0] != ' ') {
			[[[AJCFGConfigLogger sharedInstance] logger] debugTag:@"PropertyStoreImplAdapter" text:[NSString stringWithFormat:@"Language tag is not empty!! this may cause issues in the client!! lang tag is : '%s' returning invalid value", languageTag]];
            
            return ER_INVALID_VALUE;
		}
        
		languageTag = ""; // For now, the empty language tag is the only format we support for write. do not try to send other languageTag.
        
		__autoreleasing AJNMessageArgument *objc_all;
		QStatus status = [m_objc_PropertyStoreImpl readAll:languageTag withFilter:(PFilter)filter ajnMsgArg:&objc_all];
        
		all = (*(ajn::MsgArg *)objc_all.handle);
        
		return status;
	}
    
	virtual QStatus Update(const char *name, const char *languageTag, const ajn::MsgArg *value)
	{
    ajn::services::PropertyStoreKey propertyKey = (ajn::services::PropertyStoreKey)[m_objc_PropertyStoreImpl getPropertyStoreKeyFromName : name];
		if (propertyKey >= NUMBER_OF_KEYS)
			return ER_FEATURE_NOT_AVAILABLE;
        
		// Validate that the value is acceptable
    qcc::String languageString = languageTag ? languageTag : "";
		QStatus status = validateValue(propertyKey, *value, languageString);
		if (status != ER_OK) {
			return status;
		}
        
		__autoreleasing AJNMessageArgument *objc_value = [[AJNMessageArgument alloc] initWithHandle:(AJNHandle)value];
		return [m_objc_PropertyStoreImpl Update:name languageTag:languageTag ajnMsgArg:objc_value];
	}
    
	virtual QStatus Delete(const char *name, const char *languageTag)
	{
		return [m_objc_PropertyStoreImpl reset:name languageTag:languageTag];
	}
    
	QStatus isLanguageSupported_Public_Adapter(const char *language)
	{
		return this->isLanguageSupported(language);
	}
    
	long getNumberOfProperties()
	{
		return m_Properties.size();
	}
    
	QStatus populateWritableMsgArgs(const char *languageTag, ajn::MsgArg& all)
	{
		QStatus status = ER_OK;
    ajn::MsgArg * argsWriteData = new ajn::MsgArg[m_Properties.size()];
		uint32_t writeArgCount = 0;
		do {
			for (ajn::services::PropertyMap::const_iterator it = m_Properties.begin(); it != m_Properties.end(); ++it) {
				const ajn::services::PropertyStoreProperty& property = it->second;
                
				if (!property.getIsWritable())
					continue;
                
				// Check that it is from the defaultLanguage or empty.
				if (!(property.getLanguage().empty() || property.getLanguage().compare(languageTag) == 0))
					continue;
                
				status = argsWriteData[writeArgCount].Set("{sv}", property.getPropertyName().c_str(),
				                                          new ajn::MsgArg(property.getPropertyValue()));
                
				if (status != ER_OK) {
					break;
				}
				argsWriteData[writeArgCount].SetOwnershipFlags(ajn::MsgArg::OwnsArgs, true);
				writeArgCount++;
			}
			status = all.Set("a{sv}", writeArgCount, argsWriteData);
            
			if (status != ER_OK) {
				break;
			}
            
			all.SetOwnershipFlags(ajn::MsgArg::OwnsArgs, true);
		}
		while (0);
        
		if (status != ER_OK) {
			delete[] argsWriteData;
		}
        
		return status;
	}
    
	QStatus erasePropertyAccordingToPropertyCode(ajn::services::PropertyStoreKey propertyKey, const char *languageTag)
	{
		bool deleted = false;
    std::pair <ajn::services::PropertyMap::iterator, ajn::services::PropertyMap::iterator> propertiesIter = m_Properties.equal_range(propertyKey);
    ajn::services::PropertyMap::iterator it;
        
		for (it = propertiesIter.first; it != propertiesIter.second; it++) {
			const ajn::services::PropertyStoreProperty& property = it->second;
			if (property.getIsWritable()) {
				if ((languageTag == NULL && property.getLanguage().empty()) ||
				    (languageTag != NULL && property.getLanguage().compare(languageTag) == 0)) {
					m_Properties.erase(it);
					// Insert from backup.
					deleted = true;
					break;
				}
			}
		}
        
		if (!deleted) {
			if (languageTag != NULL) {
				return ER_LANGUAGE_NOT_SUPPORTED;
			}
			else {
				return ER_INVALID_VALUE;
			}
		}
        
		return ER_OK;
	}
    
	QStatus updatePropertyAccordingToPropertyCode(ajn::services::PropertyStoreKey propertyKey, const char *languageTag, ajn::MsgArg *value)
	{
    ajn::services::PropertyStoreProperty * temp = NULL;
    std::pair <ajn::services::PropertyMap::iterator, ajn::services::PropertyMap::iterator> propertiesIter = m_Properties.equal_range(propertyKey);
        
		for (ajn::services::PropertyMap::iterator it = propertiesIter.first; it != propertiesIter.second; it++) {
			const ajn::services::PropertyStoreProperty& property = it->second;
			if (property.getIsWritable()) {
				if ((languageTag == NULL && property.getLanguage().empty()) ||
				    (languageTag != NULL && property.getLanguage().compare(languageTag) == 0)) {
					temp = new ajn::services::PropertyStoreProperty(property.getPropertyName(), *value, property.getIsPublic(),
					                                                      property.getIsWritable(), property.getIsAnnouncable());
					if (languageTag)
						temp->setLanguage(languageTag);
					m_Properties.erase(it);
					break;
				}
			}
		}
        
		if (temp == NULL)
			return ER_INVALID_VALUE;
        
		m_Properties.insert(ajn::services::PropertyPair(propertyKey, *temp));
        
		return ER_OK;
	}
    
private:
	AJCFGPropertyStoreImpl *m_objc_PropertyStoreImpl;
};
