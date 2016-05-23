/**
 * @file
 *
 * This file provides definitions for standard Location interfaces
 */

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

#include <qcc/platform.h>
#include <qcc/Debug.h>

#include <alljoyn/location/LocationStd.h>

#define QCC_MODULE "LOCATION"

namespace ajn {

/** org.alljoyn.locationservices Definitions */
const char* org::alljoyn::locationservices::InterfaceName = "org.alljoyn.locationservices";
const char* org::alljoyn::locationservices::InterfaceXml =
    "<interface name=\"org.alljoyn.locationservices\">"
    "  <property name=\"Version\" type=\"q\" access=\"read\"/>"
    "  <method name=\"EntityDiscovery\">"
    "    <arg name=\"entity\" type=\"(ss)\" direction=\"in\"/>"
    "  </method>"
    "  <method name=\"PresenceSubscribe\">"
    "    <arg name=\"filter\" type=\"(ss)\" direction=\"in\"/>"
    "    <arg name=\"tracker\" type=\"o\" direction=\"out\"/>"
    "  </method>"
    "  <method name=\"DistanceSubscribe\">"
    "    <arg name=\"entity\" type=\"(ss)\" direction=\"in\"/>"
    "    <arg name=\"filter\" type=\"(ssi)\" direction=\"in\"/>"
    "    <arg name=\"tracker\" type=\"o\" direction=\"out\"/>"
    "  </method>"
    "  <method name=\"GeofenceSubscribe\">"
    "    <arg name=\"entity\" type=\"(ss)\" direction=\"in\"/>"
    "    <arg name=\"filter\" type=\"(ssi)\" direction=\"in\"/>"
    "    <arg name=\"tracker\" type=\"o\" direction=\"out\"/>"
    "  </method>"
    "  <method name=\"Unsubscribe\">"
    "    <annotation name=\"org.freedesktop.DBus.Method.NoReply\" value=\"true\"/>"
    "    <arg name=\"tracker\" type=\"o\" direction=\"in\"/>"
    "  </method>"
    "</interface>";

/** org.alljoyn.locationservices.PresenceTracker Definitions */
const char* org::alljoyn::locationservices::PresenceTracker::InterfaceName = "org.alljoyn.locationservices.PresenceTracker";
const char* org::alljoyn::locationservices::PresenceTracker::InterfaceXml =
    "<interface name=\"org.alljoyn.locationservices.PresenceTracker\">"
    "  <property name=\"Version\" type=\"q\" access=\"read\"/>"
    "  <property name=\"Tracker\" type=\"s\" access=\"read\"/>"
    "  <property name=\"Matches\" type=\"a(say)\" access=\"read\">"
    "    <annotation name=\"org.freedesktop.DBus.Property.EmitsChangedSignal\" value=\"true\"/>"
    "  </property>"
    "</interface>";

/** org.alljoyn.locationservices.DistanceTracker Definitions */
const char* org::alljoyn::locationservices::DistanceTracker::InterfaceName = "org.alljoyn.locationservices.DistanceTracker";
const char* org::alljoyn::locationservices::DistanceTracker::InterfaceXml =
    "<interface name=\"org.alljoyn.locationservices.DistanceTracker\">"
    "  <property name=\"Version\" type=\"q\" access=\"read\"/>"
    "  <property name=\"Tracker\" type=\"s\" access=\"read\"/>"
    "  <property name=\"Matches\" type=\"a(ssi)\" access=\"read\">"
    "    <annotation name=\"org.freedesktop.DBus.Property.EmitsChangedSignal\" value=\"true\"/>"
    "  </property>"
    "    <signal name=\"Tracking\">"
    "      <arg name=\"entity\" type=\"(ssi)\" direction=\"out\"/>"
    "    </signal>"
    "</interface>";

/** org.alljoyn.locationservices.GeofenceTracker Definitions */
const char* org::alljoyn::locationservices::GeofenceTracker::InterfaceName = "org.alljoyn.locationservices.GeofenceTracker";
const char* org::alljoyn::locationservices::GeofenceTracker::InterfaceXml =
    "<interface name=\"org.alljoyn.locationservices.GeofenceTracker\">"
    "  <property name=\"Version\" type=\"q\" access=\"read\"/>"
    "  <property name=\"Tracker\" type=\"s\" access=\"read\"/>"
    "  <property name=\"Matches\" type=\"a(ssb)\" access=\"read\">"
    "    <annotation name=\"org.freedesktop.DBus.Property.EmitsChangedSignal\" value=\"true\"/>"
    "  </property>"
    "    <signal name=\"Tracking\">"
    "      <arg name=\"entity\" type=\"(ssb)\" direction=\"out\"/>"
    "    </signal>"
    "</interface>";

/** org.alljoyn.locationservices.LocationTracker Definitions */
const char* org::alljoyn::locationservices::LocationTracker::InterfaceName = "org.alljoyn.locationservices.LocationTracker";
const char* org::alljoyn::locationservices::LocationTracker::InterfaceXml =
    "<interface name=\"org.alljoyn.locationservices.LocationTracker\">"
    "  <property name=\"Version\" type=\"q\" access=\"read\"/>"
    "  <property name=\"Tracker\" type=\"s\" access=\"read\"/>"
    "  <property name=\"Matches\" type=\"a(ss)\" access=\"read\">"
    "    <annotation name=\"org.freedesktop.DBus.Property.EmitsChangedSignal\" value=\"true\"/>"
    "  </property>"
    "    <signal name=\"Tracking\">"
    "      <arg name=\"entity\" type=\"(ss)\" direction=\"out\"/>"
    "    </signal>"
    "</interface>";

}
