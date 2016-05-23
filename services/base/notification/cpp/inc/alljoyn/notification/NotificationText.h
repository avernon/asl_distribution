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

#ifndef NOTIFICATIONTEXT_H_
#define NOTIFICATIONTEXT_H_

#include <qcc/String.h>

namespace ajn {
namespace services {

/**
 * Class NotificationText is used to represent the actual text message of the notification
 * Made up of language and text values
 */
class NotificationText {

  public:

    /**
     * Constructor for NotificationText
     * @param language Language of Notification
     * @param text     Text of Notification
     */
    NotificationText(qcc::String const& language, qcc::String const& text);

    /**
     * Destructor for NotificationText
     */
    ~NotificationText() { };

    /**
     * Set Language for Notification
     * @param language
     */
    void setLanguage(qcc::String const& language);

    /**
     * Get Language for Notification
     * @return language
     */
    qcc::String const& getLanguage() const;

    /**
     * Set Text for Notification
     * @param text
     */
    void setText(qcc::String const& text);

    /**
     * Get Text for Notification
     * @return text
     */
    qcc::String const& getText() const;

  private:

    /**
     * Notification Language
     */
    qcc::String m_Language;

    /**
     * Notification Text
     */
    qcc::String m_Text;
};
} //namespace services
} //namespace ajn

#endif /* NOTIFICATIONTEXT_H_ */
