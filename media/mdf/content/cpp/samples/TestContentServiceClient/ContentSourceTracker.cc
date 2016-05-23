/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#include "ContentSourceTracker.h"
#include <iostream>

namespace mdf {


ContentSourceTracker::~ContentSourceTracker()
{
    m_CSLock.Lock(MUTEX_CONTEXT);
    for (std::map<String, ContentSource*>::const_iterator iter = m_ContentSources.begin(); iter != m_ContentSources.end(); ++iter) {
        ContentSource* cs = (*iter).second;
        if (cs) {
            delete cs;
        }
    }
    m_ContentSources.clear();
    m_CSLock.Unlock(MUTEX_CONTEXT);
}

void ContentSourceTracker::ContentSourceAdded(ContentSource& contentSource) {
    //Needed to make the m_ContentSources mutable due to the const at the end.. is that ok?
    m_CSLock.Lock(MUTEX_CONTEXT);
    m_ContentSources.insert(std::pair<String, ContentSource*>(contentSource.GetID(), &contentSource));
    m_CSLock.Unlock(MUTEX_CONTEXT);

    if (!m_ContentSource) {
        //Set the first content source found as selected by default
        m_ContentSource = &contentSource;
    }
}

void ContentSourceTracker::ContentSourceLost(ContentSource& contentSource) {
    cout << "\nContentSource lost: " << contentSource.GetDisplayName() << endl;
    String contentID = contentSource.GetID();
    bool contentSourceFound = false;
    ContentSource* lostContentSource;
    m_CSLock.Lock(MUTEX_CONTEXT);
    for (std::map<String, ContentSource*>::const_iterator iter = m_ContentSources.find(contentID); iter != m_ContentSources.end(); ++iter) {
        contentSourceFound = true;
        lostContentSource = (*iter).second;
        if (contentID.compare(lostContentSource->GetID()) == 0) {
            m_ContentSource = NULL;
        }
        break;
    }

    if (contentSourceFound) {
        m_CSLock.Lock(MUTEX_CONTEXT);
        m_ContentSources.erase(contentID);
        m_CSLock.Unlock(MUTEX_CONTEXT);
        delete lostContentSource;
    }

    if (!m_ContentSource) {
        //Select the next content source as selected if we lost the selected ONE...
        for (std::map<String, ContentSource*>::const_iterator iter = m_ContentSources.begin(); iter != m_ContentSources.end(); ++iter) {
            m_ContentSource = (*iter).second;
            break;
        }
    }
    m_CSLock.Unlock(MUTEX_CONTEXT);
}

map<String, ContentSource*> ContentSourceTracker::GetContentSources() const {
    return m_ContentSources;
}

bool ContentSourceTracker::SetSelectedContentSource(String contentSourceID) {
    bool contentSourceFound = false;
    for (std::map<String, ContentSource*>::const_iterator iter = m_ContentSources.find(contentSourceID); iter != m_ContentSources.end(); ++iter) {
        ContentSource* selectedCS = (*iter).second;
        m_ContentSource = selectedCS;
        contentSourceFound = true;
        break;
    }
    return contentSourceFound;
}

ContentSource* ContentSourceTracker::GetSelectedContentSource() const {
    return m_ContentSource;
}

}
