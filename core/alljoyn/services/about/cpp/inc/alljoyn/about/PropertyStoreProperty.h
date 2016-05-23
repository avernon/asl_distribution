/**
 * @file
 * property of the PropertyStoreImpl class
 * @see PropertyStoreImpl.h
 */
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

#ifndef PROPERTYSTOREPROP_H_
#define PROPERTYSTOREPROP_H_

#include <qcc/String.h>
#include <alljoyn/MsgArg.h>

namespace ajn {
namespace services {

/**
 * Property of Property Store Impl class
 *
 * @deprecated The PropertyStoreProperty class has been deprecated please see the
 * AboutData class.
 */
class PropertyStoreProperty {
  public:
    /**
     * Constructor for PropertyStoreProperty
     *
     * @deprecated The PropertyStoreProperty class has been deprecated please see the
     * AboutData class.
     *
     * @param keyName the name of the property
     */
    QCC_DEPRECATED(PropertyStoreProperty(qcc::String const& keyName));

    /**
     * Constructor for PropertyStoreProperty
     *
     * @deprecated The PropertyStoreProperty class has been deprecated please see the
     * AboutData class.
     *
     * @param keyName the name of the property
     * @param value   MsgArg containing the property value
     */
    QCC_DEPRECATED(PropertyStoreProperty(qcc::String const& keyName, ajn::MsgArg const& value));

    /**
     * Constructor for PropertyStoreProperty
     *
     * @deprecated The PropertyStoreProperty class has been deprecated please see the
     * AboutData class.
     *
     * @param keyName        the name of the property
     * @param value          MsgArg containing the value stored in the property
     * @param isPublic       Is the property public
     * @param isWritable     Is the property writable
     * @param isAnnouncable  Is the property announced
     */
    QCC_DEPRECATED(PropertyStoreProperty(qcc::String const& keyName, ajn::MsgArg const& value,
                                         bool isPublic, bool isWritable, bool isAnnouncable));

    /**
     * Constructor for PropertyStoreProperty
     *
     * @deprecated The PropertyStoreProperty class has been deprecated please see the
     * AboutData class.
     *
     * @param keyName        the name of the property
     * @param value          MsgArg containing the value stored in the property
     * @param language       The language tag identifying the localization language for the property
     * @param isPublic       Is the property public
     * @param isWritable     Is the property writable
     * @param isAnnouncable  Is the property announced
     */
    QCC_DEPRECATED(PropertyStoreProperty(qcc::String const& keyName, ajn::MsgArg const& value, qcc::String const& language,
                                         bool isPublic, bool isWritable, bool isAnnouncable));


    /**
     * Destructor for PropertyStoreProperty
     *
     * @deprecated The PropertyStoreProperty class has been deprecated please see the
     * AboutData class.
     */
    QCC_DEPRECATED(virtual ~PropertyStoreProperty());

    /**
     * Set the flags for the property
     *
     * @deprecated The PropertyStoreProperty class has been deprecated please see the
     * AboutData class.
     *
     * @param isPublic      Is the property public
     * @param isWritable    Is the property writable
     * @param isAnnouncable Is the property announced
     */
    QCC_DEPRECATED(void setFlags(bool isPublic, bool isWritable, bool isAnnouncable));

    /**
     * Set the language of the property
     *
     * @deprecated The PropertyStoreProperty class has been deprecated please see the
     * AboutData class.
     *
     * @param language The language tag identifying the localization language for the property
     */
    QCC_DEPRECATED(void setLanguage(qcc::String const & language));

    /**
     * Get the KeyName of the property
     *
     * @deprecated The PropertyStoreProperty class has been deprecated please see the
     * AboutData class.
     *
     * @return keyname
     */
    QCC_DEPRECATED(const qcc::String & getPropertyName() const);

    /**
     * Get the Value of the Property
     *
     * @deprecated The PropertyStoreProperty class has been deprecated please see the
     * AboutData class.
     *
     * @return value
     */
    QCC_DEPRECATED(const ajn::MsgArg & getPropertyValue() const);

    /**
     * Get the Language of the Property
     *
     * @deprecated The PropertyStoreProperty class has been deprecated please see the
     * AboutData class.
     *
     * @return Language
     */
    QCC_DEPRECATED(const qcc::String & getLanguage() const);

    /**
     * Get the isPublic boolean of the property
     *
     * @deprecated The PropertyStoreProperty class has been deprecated please see the
     * AboutData class.
     *
     * @return isPublic
     */
    QCC_DEPRECATED(bool getIsPublic() const);

    /**
     * Get the isWritable boolean of the Property
     *
     * @deprecated The PropertyStoreProperty class has been deprecated please see the
     * AboutData class.
     *
     * @return isWritable
     */
    QCC_DEPRECATED(bool getIsWritable() const);

    /**
     * Get the isAnnounceable boolean of the Property
     *
     * @deprecated The PropertyStoreProperty class has been deprecated please see the
     * AboutData class.
     *
     * @return isAnnounceable
     */
    QCC_DEPRECATED(bool getIsAnnouncable() const);

    /**
     * Set the isPublic boolean of the Property
     *
     * @deprecated The PropertyStoreProperty class has been deprecated please see the
     * AboutData class.
     *
     * @param value Is the property public
     */
    QCC_DEPRECATED(void setIsPublic(bool value));

    /**
     * set the IsWritable boolean of the Property
     *
     * @deprecated The PropertyStoreProperty class has been deprecated please see the
     * AboutData class.
     *
     * @param value Is the property writable
     */
    QCC_DEPRECATED(void setIsWritable(bool value));

    /**
     * set the isAnnounce of the Property
     *
     * @deprecated The PropertyStoreProperty class has been deprecated please see the
     * AboutData class.
     *
     * @param value is the property announced
     */
    QCC_DEPRECATED(void setIsAnnouncable(bool value));

  private:

    /**
     * private member keyName
     */
    qcc::String m_Keyname;

    /**
     * private member value
     */
    ajn::MsgArg m_Value;

    /**
     * private member isPublic
     */
    bool m_Public;

    /**
     * private member isWritable
     */
    bool m_Writable;

    /**
     * private member isAnnounceable
     */
    bool m_Announcable;

    /**
     * private member language
     */
    qcc::String m_Language;
};
} /* namespace services */
} /* namespace ajn */
#endif /* PROPERTYSTOREPROP */
