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

#ifndef CONTENTMANAGER_H_
#define CONTENTMANAGER_H_

#include <qcc/String.h>
#include <vector>
#include <Node.h>
#include "MdfContentSource.h"
#include "StructureParser.h"

namespace mdf {

class ContentManager {

  public:

    /*
     * @function ContentManager
     * @description constructor
     */
    ContentManager(const qcc::String& directoryStructure);

    /*
     * @function ~ContentManager
     * @description destructor
     */
    virtual ~ContentManager();


    /*
     * @function BrowseDirectory
     * @description browse the directory whos ID is supplied
     * @param directoryID
     * @param sortByMap a vector of properties that we should sort the return values by
     * @param offset offset in the results to return
     * @param limit the limit is the max amount of results to return
     * @param supportedMimeTypeList a list of supported mime types
     * @param resolution resolution to be supported. 0 if not relevant
     * @param transportTypeList a list of transport types
     * @return std::vector<const mdf::Node> a list of Node pointers returned by the query
     */
    NodeList* Browse(String& itemID, CapabilitiesMap& playerCapabilities, uint64_t offset, uint32_t limit, SortByMap& sortBy);


    /*
     * @function GetItem
     * @param itemID the id of the item to return
     * @retVal Node* a pointer to a node item
     */
    Node* GetItem(const qcc::String& itemID) const;

    NodeList* Search(String search, uint16_t searchMode, CapabilitiesMap& playerCapabilities, uint64_t offset, uint32_t limit, SortByMap& sortBy);

  private:

    StructureParser* m_StructureParser;
};

} //end mdf

#endif /* ContentManager_H_ */
