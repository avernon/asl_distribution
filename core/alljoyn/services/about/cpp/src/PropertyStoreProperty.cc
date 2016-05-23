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

#include <alljoyn/about/PropertyStoreProperty.h>

namespace ajn {
namespace services {

PropertyStoreProperty::PropertyStoreProperty(qcc::String const& keyName) :
    m_Keyname(keyName), m_Public(true), m_Writable(false), m_Announcable(true), m_Language("")
{
}

PropertyStoreProperty::PropertyStoreProperty(qcc::String const& keyName, ajn::MsgArg const& value) :
    m_Keyname(keyName), m_Value(value), m_Public(true), m_Writable(false), m_Announcable(true),
    m_Language("")
{
}

PropertyStoreProperty::PropertyStoreProperty(qcc::String const& keyName, ajn::MsgArg const& value,
                                             bool isPublic, bool isWritable, bool isAnnouncable) : m_Keyname(keyName),
    m_Value(value), m_Public(isPublic), m_Writable(isWritable),
    m_Announcable(isAnnouncable), m_Language("")
{
}

PropertyStoreProperty::PropertyStoreProperty(qcc::String const& keyName, ajn::MsgArg const& value, qcc::String const& language,
                                             bool isPublic, bool isWritable, bool isAnnouncable) : m_Keyname(keyName),
    m_Value(value), m_Public(isPublic), m_Writable(isWritable),
    m_Announcable(isAnnouncable), m_Language(language)
{
}

PropertyStoreProperty::~PropertyStoreProperty()
{

}

void PropertyStoreProperty::setFlags(bool isPublic, bool isWritable, bool isAnnouncable)
{
    m_Public = isPublic;
    m_Writable = isWritable;
    m_Announcable = isAnnouncable;
}

void PropertyStoreProperty::setLanguage(qcc::String const& language)
{
    m_Language = language;
}

const qcc::String& PropertyStoreProperty::getPropertyName() const {
    return m_Keyname;
}

const ajn::MsgArg& PropertyStoreProperty::getPropertyValue() const {
    return m_Value;
}

const qcc::String& PropertyStoreProperty::getLanguage() const {
    return m_Language;
}

bool PropertyStoreProperty::getIsPublic() const {
    return m_Public;
}

bool PropertyStoreProperty::getIsWritable() const {
    return m_Writable;
}

bool PropertyStoreProperty::getIsAnnouncable() const {
    return m_Announcable;
}

void PropertyStoreProperty::setIsPublic(bool value) {
    m_Public = value;
}

void PropertyStoreProperty::setIsWritable(bool value) {
    m_Writable = value;
}

void PropertyStoreProperty::setIsAnnouncable(bool value) {
    m_Announcable = value;
}

} /* namespace services */
} /* namespace ajn */
