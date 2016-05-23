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

#ifndef NODE_H_
#define NODE_H_

//#include <stdint.h>
#include <vector>

#include <qcc/String.h>
#include "ContentConstants.h"

using namespace qcc;

namespace mdf {

enum NodeType {
    NodeTypeFolder = 0,
    NodeTypeAudio = 100,
    NodeTypeVideo = 101,
    NodeTypeImage = 102,
    NodeTypeUnknown = 103
};


//node type also available as string
static const String s_Unknown = "UNKNOWN";
static const String s_FolderNode = "FOLDER";
static const String s_AudioNode = "AUDIO";
static const String s_ImageNode = "IMAGE";
static const String s_VideoNode = "VIDEO";


class Node {

  private:

    /*
     * @function Node
     * @description constructor
     */
    Node();

  public:
    /*
     * @function Node
     * @description constructor
     * @param itemID the id of the node
     * @param title The title of the node
     * @param nodeType Indicates if this is a folder, audio file, image file pr video file
     * @param properties custom properties
     */
    Node(const String itemID, const String title, NodeType nodeType, PropertiesMap& properties);

    Node(const String itemID, const String title, NodeType nodeType);

    /*
     * @function Node
     * @description constructor
     * @param itemID the id of the node
     * @param title The title of the node
     * @param nodeTypeAsString Indicates if this is a folder, audio file, image file pr video file
     * @param properties custom properties
     */
    Node(String itemID, String title, String type, PropertiesMap& properties);

    /*
     * @function ~Node
     * @description destructor
     */
    virtual ~Node();

    /*
     * @function GetItemID
     * @description returns the item ID
     * @return String the item ID
     */
    virtual String GetItemID() const;

    /*
     * @function SetItemID
     * @description sets the Item ID
     * @param itemID the item ID
     */
    virtual void SetItemID(const String& itemID);

    /*
     * @function GetItemID
     * @description returns the item ID. Note that parent ID is optional an not every node type will have a parent
     * @return String the item ID
     */
    virtual const String& GetParentID() const;

    /*
     * @function SetParentID
     * @description sets the optional parent ID
     * @param itemID the parent ID
     */
    virtual void SetParentID(const String& itemID);

    /*
     * @function GetTitle
     * @description gets the title
     * @return String the title
     */
    virtual const String& GetTitle() const;

    /*
     * @function SetTitle
     * @description sets the item title
     * @param title the title
     */
    virtual void SetTitle(const String& title);

    /*
     * @function GetType
     * @description gets the Item Type
     * @return NodeType the type
     */
    virtual NodeType GetType() const;

    /*
     * @function GetType
     * @description gets the Item Type as a string representation
     * @return NodeType the type. This can be one of "UNKNOWN", "FOLDER", "AUDIO", "IMAGE", "VIDEDO"
     */
    virtual const String& GetTypeAsString() const;

    /*
     * @function SetType
     * @description sets the item type
     * @param type the type
     */
    virtual void SetType(NodeType type);

    /*
     * @function SetType
     * @description sets the item type
     * @param type the type as a string
     */
    virtual void SetTypeFromString(const String& typeAsString);

    /*
     * @function GetProperties
     * @description returns a modifiable list of item properties
     */
    virtual PropertiesMap& GetProperties();

    /*
     * @function SetProperties
     * @description replaces the current properties object with the one supplied
     * @param properties the new properties
     */
    virtual void SetProperties(PropertiesMap& properties);


  protected:

    NodeType m_NodeType;        // the node type
    PropertiesMap m_Properties;        // custom properties

    String m_ItemID;     // the item id
    String m_Title;     // the item title
    String m_NodeTypeAsString; //the node type as a string
    String m_ParentID;     // the parent folcer id
};

} // mdf




#endif /* NODE_H_ */
