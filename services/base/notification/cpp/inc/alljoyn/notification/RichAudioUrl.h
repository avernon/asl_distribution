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

#ifndef RICHAUDIOURL_H_
#define RICHAUDIOURL_H_

#include <qcc/String.h>

namespace ajn {
namespace services {

/**
 * Class to store RichAudio urls, a url per language
 */
class RichAudioUrl {

  public:

    /**
     * Constructor for RichAudioUrl
     * @param language Language of Audio Content
     * @param url      Url of Audio Content
     */
    RichAudioUrl(qcc::String const& language, qcc::String const& url);

    /**
     * Destructor for RichAudioUrl
     */
    ~RichAudioUrl() { };

    /**
     * Set Language for Audio Content
     * @param language
     */
    void setLanguage(qcc::String const& language);

    /**
     * Get Language for Audio Content
     * @return language
     */
    qcc::String const& getLanguage() const;

    /**
     * Set URL for Audio Content
     * @param url
     */
    void setUrl(qcc::String const& url);

    /**
     * Get URL for Audio Content
     * @return url
     */
    qcc::String const& getUrl() const;
  private:

    /**
     * Audio Content Language String
     */
    qcc::String m_Language;

    /**
     * Audio Content URL
     */
    qcc::String m_Url;
};
} //namespace services
} //namespace ajn

#endif /* RICHAUDIOURL_H_ */
