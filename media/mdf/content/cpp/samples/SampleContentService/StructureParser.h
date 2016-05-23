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

#ifndef STRUCTUREPARSER_H_
#define STRUCTUREPARSER_H_

#include <Node.h>
#include <qcc/String.h>
#include <vector>

namespace mdf {

class StructureParser {

  public:

    /*
     * @function StructureParser
     * @description constructor
     */
    StructureParser(const qcc::String& directoryStructure);

    /*
     * @function ~StructureParser
     * @description destructor
     */
    virtual ~StructureParser();

    /*
     * @function StartParsing
     * @description This kicks off the process of parsing the folder recursively for media, adding new media
     */
    void StartParsing();

    /*
     * @function GetNodeList
     * @description returns the list of nodes
     * @return std::vector<mdf::Node*>
     */
    NodeList& GetNodeList();

  private:

    /*
     * @function ParseDirRecursive
     * @description used to recursively parse folders and files
     * @param directory a representation of the directory to be parsed
     * @param parentID theParentID
     */
    void ParseDirRecursive(const qcc::String& directory, const qcc::String& parentID, std::vector<mdf::Node*>& m_NodeList);

    /*
     * @function IsDir
     * @description checks a file path to see if it is a directory
     * @return bool true if this is a directory, false if it is a file or does not exists
     */
    bool IsDir(const qcc::String& dir) const;

    /*
     * @function DeleteNodePointer
     * @description cleans up a node pointer
     * @param node the node to clean up
     */
    void DeleteNodePointer(Node* node);

    /*
     * @function DeleteAllNodes
     * @description deletes all nodes
     */
    void DeleteAllNodes();

    /*
     * @function SplitString
     * @description splits the token delimited string into individual strings
     * @return std::vector<qcc::String> the array of split strings
     */
    std::vector<qcc::String> SplitString(const qcc::String& stringToParse, const qcc::String& delimiter);

    /*
     * @function StripFolderBrackets
     * @description strips the enclosing braces from a folder structure
     * @param folder the folder string
     * @return qcc::String the folder with the braces removed
     */
    qcc::String StripFolderBrackets(const qcc::String& folder);

    /*
     * @folder CreateNewName
     * @description creates a new name using a combination of the parent folder ID and the items position in the current folder
     * @param parentName the parent folder name
     * @param indexInCurFolder
     * @return qcc::String the newly generated name
     */
    qcc::String CreateNewName(const qcc::String& parentName, const qcc::String& indexInCurFolder);

  private:

    String m_DirectoryStructure;
    NodeList m_NodeList;

};

} // end MDF

#endif /* StructureParser_H_ */
