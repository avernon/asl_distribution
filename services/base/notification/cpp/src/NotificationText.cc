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

#include <alljoyn/notification/NotificationText.h>

using namespace ajn;
using namespace services;
using namespace qcc;

NotificationText::NotificationText(String const& language, String const& text)
{
    m_Language = language;
    m_Text = text;
}

void NotificationText::setLanguage(String const& language)
{
    m_Language = language;
}

String const& NotificationText::getLanguage() const
{
    return m_Language;
}

void NotificationText::setText(String const& text)
{
    m_Text = text;
}

String const& NotificationText::getText() const
{
    return m_Text;
}
