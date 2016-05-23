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

#ifndef CONTENTCONSTANTS_H_
#define CONTENTCONSTANTS_H_

#include <map>
#include <vector>
#include <qcc/String.h>
#include "alljoyn/MsgArg.h"

/*
 * Common Macros
 */
#define CHECK(x) if ((status = x))  { break; }

using namespace qcc;
using namespace ajn;

namespace mdf {

class Node;

typedef std::map<String, uint16_t> SortByMap;
typedef std::map<String, String> CapabilitiesMap;
typedef std::map<String, String> SourceInfoMap;
typedef std::map<String, String> PropertiesMap;
typedef std::vector<Node*> NodeList;
typedef std::vector<String> SortableFieldsList;
typedef std::vector<MsgArg> MsgArgList;


static const String s_CONTENT_INTERFACE = "org.alljoyn.media.ContentSource";

static const String s_CONTENT_OBJECT_PATH = "/media/ContentSource";

static const String s_PROPERTY_VERSION = "version";
static const String s_PROPERTY_DISPLAYNAME = "displayName";
static const String s_PROPERTY_ICONURL = "iconURL";
static const String s_PROPERTY_LASTMODIFIED = "lastModified";

static const String s_SIGNAL_CONTENTSOURCEINDEXCHANGED = "ContentSourceIndexChanged";
static const String s_SIGNAL_METADATACHANGED = "MetaDataChanged";

static const String s_METHOD_BROWSE = "Browse";
static const String s_METHOD_GETITEM = "GetItem";
static const String s_METHOD_GETCONTENTSOURCEINFO = "GetContentSourceInfo";
static const String s_METHOD_GETSORTABLEFIELDS = "GetSortableFields";
static const String s_METHOD_MODIFYOPTIONALMETADATA = "ModifyOptionalMetaData";
static const String s_METHOD_SEARCH = "Search";


/** The aDudio interfaces XML. */
static const String s_CONTENT_SOURCE_IF_XML = "\
    <node name=\"\"> \
    <interface name=\"" + s_CONTENT_INTERFACE + "\">\
    <property  name=\"" + s_PROPERTY_VERSION         + "\" type=\"q\" access=\"read\"/>\
    <property  name=\"" + s_PROPERTY_DISPLAYNAME     + "\" type=\"s\" access=\"read\"/>\
    <property  name=\"" + s_PROPERTY_ICONURL         + "\" type=\"s\" access=\"read\"/>\
    <property  name=\"" + s_PROPERTY_LASTMODIFIED    + "\" type=\"i\" access=\"read\"/>\
    <method name=\"" + s_METHOD_BROWSE + "\">\
                        <arg name=\"itemID\" type=\"s\" direction=\"in\" />\
                        <arg name=\"playerCapabilities\" type=\"a{ss}\" direction=\"in\" />\
                        <arg name=\"offset\" type=\"t\" direction=\"in\" />\
                        <arg name=\"limit\" type=\"i\" direction=\"in\" />\
                        <arg name=\"sortBy\" type=\"a{si}\" direction=\"in\" />\
                  <arg name=\"response\" type=\"(ututa(sssa{ss}))\" direction=\"out\" />\
      </method>\
      <method name=\"" + s_METHOD_GETITEM + "\">\
              <arg name=\"itemID\" type=\"s\" direction=\"in\" />\
                  <arg name=\"response\" type=\"(sssa{sv})\" direction=\"out\" />\
      </method>\"\
        <method name=\"" + s_METHOD_GETSORTABLEFIELDS + "\">\
              <arg name=\"response\" type=\"a(s)\" direction=\"out\" />\
     </method>\
     <method name=\"" + s_METHOD_GETCONTENTSOURCEINFO + "\">\
              <arg name=\"response\" type=\"a{ss}\" direction=\"out\" />\
     </method>\
     <method name=\"" + s_METHOD_MODIFYOPTIONALMETADATA + "\">\
              <arg name=\"itemID\" type=\"s\" direction=\"in\" />\
              <arg name=\"properties\" type=\"a{ss}\" direction=\"in\" />\
    </method>\
    <method name=\"" + s_METHOD_SEARCH + "\">\
        <arg name=\"query\" type=\"s\" direction=\"in\" />\
        <arg name=\"searchMode\" type=\"q\" direction=\"in\" />\
        <arg name=\"playerCapabilities\" type=\"a{ss}\" direction=\"in\" />\
        <arg name=\"offset\" type=\"t\" direction=\"in\" />\
        <arg name=\"limit\" type=\"i\" direction=\"in\" />\
        <arg name=\"sortBy\" type=\"a(si)\" direction=\"in\" />\
        <arg name=\"response\" type=\"(ututa(sssa{ss}))\" direction=\"out\" />\
    </method>\
      <signal name=\"" + s_SIGNAL_CONTENTSOURCEINDEXCHANGED + "\">\
           <arg name=\"timestamp\" type=\"s\"/>\
      </signal>\
      <signal name=\"" + s_SIGNAL_METADATACHANGED + "\">\
            <arg name=\"timestamp\" type=\"s\"/>\
      </signal>\
    </interface> \
    </node>";

//custom properties that are returned by a node
static const String s_FILEURL = "FILEURL";

const uint16_t s_CONTENT_SERVICE_VERSION = 1;

/** The Announce interface name. */
static const String s_ABOUT_INTERFACE = "org.alljoyn.About";

/** The match rule for receiving Announce signals. */
const String s_ANNOUNCE_MATCH_RULE = "type='signal',interface='" + s_ABOUT_INTERFACE + "',member='Announce',sessionless='t'";

} //End mdf



#endif /* CONTENTCONSTANTS_H_ */
