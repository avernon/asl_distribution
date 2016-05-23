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

#include "ContentManager.h"
#include <Node.h>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <functional>
#include <LogModule.h>
#include <alljoyn/Status.h>
#include <ContentConstants.h>

namespace mdf {

ContentManager::ContentManager(const qcc::String& directoryStructure) : m_StructureParser(NULL)
{
    m_StructureParser = new StructureParser(directoryStructure);
    m_StructureParser->StartParsing();
}

ContentManager::~ContentManager()
{
    delete m_StructureParser;
}

NodeList* ContentManager::Browse(String& itemID, CapabilitiesMap& playerCapabilities, uint64_t offset, uint32_t limit, SortByMap& sortBy)
{

    QCC_DbgHLPrintf(("ContentManager::BrowseDirectory: itemID=%s", itemID.c_str()));

//    NodeList* nodeList = new NodeList;
    NodeList& allnodes = m_StructureParser->GetNodeList();
    return &allnodes;

//    for (size_t i = 0; i < allnodes.size(); i++) {
//        if (allnodes.at(i)->GetParentID().compare(itemID) == 0) {
//            nodeList->push_back(allnodes.at(i));
//            QCC_DbgHLPrintf(("Found node called - %s ", allnodes.at(i)->GetTitle().c_str()));
//        }
//    }
//
//    return nodeList;
}

Node* ContentManager::GetItem(const qcc::String& itemID) const
{
    QCC_DbgHLPrintf(("ContentManager::GetItem: Get item with id %s", itemID.c_str()));
//    Node* retVal = NULL;
//    const std::vector<mdf::Node*> allnodes = m_StructureParser->GetNodeList();
//
//    for (size_t i = 0; i < allnodes.size(); i++) {
//        if (allnodes.at(i)->GetItemID().compare(itemID) == 0) {
//            retVal = allnodes.at(i);
//            QCC_DbgHLPrintf(("Found node called - %s ", allnodes.at(i)->GetTitle().c_str()));
//            break;
//        }
//    }
//    return retVal;
    NodeList& allnodes = m_StructureParser->GetNodeList();
    return allnodes.at(0);
}

NodeList* ContentManager::Search(String search, uint16_t searchMode, CapabilitiesMap& playerCapabilities, uint64_t offset, uint32_t limit, SortByMap& sortBy)
{
    NodeList& allnodes = m_StructureParser->GetNodeList();
    return &allnodes;
}

} //end mdf
