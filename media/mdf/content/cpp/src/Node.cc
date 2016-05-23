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

#include <Node.h>
#include <LogModule.h>

using namespace qcc;

namespace mdf {

Node::Node() : m_NodeType(NodeTypeUnknown), m_NodeTypeAsString(s_Unknown) {

}

Node::Node(String itemID, String title, NodeType nodeType, PropertiesMap& properties) :
    m_ItemID(itemID), m_Title(title), m_Properties(properties)
{

    SetType(nodeType);
}

Node::Node(String itemID, String title, NodeType nodeType) :
    m_ItemID(itemID), m_Title(title)
{
    SetType(nodeType);
}

Node::Node(String itemID, String title, String type, PropertiesMap& properties) :
    m_ItemID(itemID), m_Title(title), m_Properties(properties) {
    SetTypeFromString(type);
}

Node::~Node() {

}

String Node::GetItemID() const {
    return m_ItemID;
}

void Node::SetItemID(const String& itemID) {
    m_ItemID = itemID;
}

const String& Node::GetParentID() const {
    return m_ParentID;
}

void Node::SetParentID(const String& itemID) {
    m_ParentID = itemID;
}

const String& Node::GetTitle() const {
    return m_Title;
}

void Node::SetTitle(const String& title) {
    m_Title = String(title.c_str());
}

NodeType Node::GetType() const {
    return m_NodeType;
}

const String& Node::GetTypeAsString() const {
    return m_NodeTypeAsString;
}

void Node::SetType(NodeType type) {

    m_NodeType = type;

    switch (type) {
    case NodeTypeFolder: {
            m_NodeTypeAsString = s_FolderNode;
        } break;

    case  NodeTypeAudio: {
            m_NodeTypeAsString = s_AudioNode;
        } break;

    case  NodeTypeImage: {
            m_NodeTypeAsString = s_ImageNode;
        } break;

    case  NodeTypeVideo: {
            m_NodeTypeAsString = s_VideoNode;
        } break;

    default: {
            m_NodeTypeAsString = s_FolderNode;
        } break;
    }
}

void Node::SetTypeFromString(const String& typeAsString) {

    m_NodeTypeAsString = typeAsString;

    if (typeAsString.compare(s_FolderNode) == 0) {
        m_NodeType = NodeTypeFolder;
    } else if (typeAsString.compare(s_AudioNode) == 0) {
        m_NodeType = NodeTypeAudio;
    } else if (typeAsString.compare(s_VideoNode) == 0) {
        m_NodeType = NodeTypeVideo;
    } else if (typeAsString.compare(s_ImageNode) == 0) {
        m_NodeType = NodeTypeImage;
    } else {
        m_NodeType = NodeTypeUnknown;
        m_NodeTypeAsString = s_Unknown;
    }

}

PropertiesMap& Node::GetProperties()  {
    return m_Properties;
}

void Node::SetProperties(PropertiesMap& properties) {
    m_Properties = properties;
}


} // mdf

