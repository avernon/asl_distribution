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

#include "SampleContentSource.h"
#include <ContentConstants.h>
#include <stdio.h>
#include <stdlib.h>
#include <LogModule.h>
#include <alljoyn/Status.h>
#include "ContentManager.h"

namespace mdf {

const static qcc::String s_RootDirectory = "0";

SampleContentSource::SampleContentSource()
{
    Init();
}

SampleContentSource::~SampleContentSource() {
    delete m_ContentManager;
}

void SampleContentSource::Init()
{
    String directoryStructure = "{a,v,i,{a,{a,v}}}";
    m_ContentManager = new ContentManager(directoryStructure);

    m_Version = 142;
    m_DisplayName  = "SampleContentSourceDisplay";
    m_IconURL = "http://testUrl/c";
    m_LastModified = 1234;

    m_SortableFields.push_back("SortableField-1");
    m_SortableFields.push_back("SortableField-2");
    m_SortableFields.push_back("SortableField-3");

    m_SourceInfoMap["SourceInfo-key-1"] = "SourceInfo-value-1";
    m_SourceInfoMap["SourceInfo-key-2"] = "SourceInfo-value-2";
    m_SourceInfoMap["SourceInfo-key-3"] = "SourceInfo-value-3";
}

uint16_t SampleContentSource::GetVersion() const
{
    return m_Version;
}

String SampleContentSource::GetDisplayName() const
{
    return m_DisplayName;
}

qcc::String SampleContentSource::GetIconURL() const
{
    return m_IconURL;
}


uint32_t SampleContentSource::GetLastModifiedTime() const
{
    return m_LastModified;
}

NodeList* SampleContentSource::Browse(String itemID,
                                      CapabilitiesMap& playerCapabilities,
                                      uint64_t offset,
                                      uint32_t limit,
                                      SortByMap& sortByMap)
{
    QCC_DbgHLPrintf(("SampleContentSource::Browse"));

    QCC_DbgHLPrintf(("SampleContentSource::Browse itemId=%s", itemID.c_str()));
    NodeList* nodes = m_ContentManager->Browse(itemID, playerCapabilities, offset, limit, sortByMap);

    if (nodes->size() == 0) {
        QCC_DbgHLPrintf(("The node list returned from the query was empty"));
    }

    return nodes;
}

Node* SampleContentSource::GetItem(const qcc::String& itemID) const
{
    Node* node = m_ContentManager->GetItem(itemID);
    if (node == NULL) {
        return NULL;
    }

    return new Node(*node);
}

SortableFieldsList* SampleContentSource::GetSortableFields() {

    return &m_SortableFields;
}

SourceInfoMap* SampleContentSource::GetContentSourceInfo()  {

    return &m_SourceInfoMap;
}

QStatus SampleContentSource::ModifyOptionalMetaData(const qcc::String& nodeID, PropertiesMap& properties) {
    QStatus retVal = ER_OK;
    return retVal;
}

NodeList* SampleContentSource::Search(String& searchString, uint16_t searchMode, CapabilitiesMap& capabilities, uint64_t offset, uint32_t limit, SortByMap& sortByMap)
{
    QCC_DbgHLPrintf(("SampleContentSource::Browse search=%s", searchString.c_str()));
    NodeList* nodes = m_ContentManager->Search(searchString, searchMode, capabilities, offset, limit, sortByMap);

    if (nodes->size() == 0) {
        QCC_DbgHLPrintf(("The node list returned from the query was empty"));
    }
    return nodes;
}

} //mdf
