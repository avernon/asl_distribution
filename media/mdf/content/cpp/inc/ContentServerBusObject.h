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

#ifndef CONTENTSERVERBUSOBJECT_H_
#define CONTENTSERVERBUSOBJECT_H_

#include <alljoyn/BusObject.h>
#include "MdfContentSource.h"

namespace mdf {

class ContentServerBusObject : public ajn::BusObject {

  public:

    /*
     * @function ContentServerBusObject
     * @description constructor
     * @param busObjectPath     object bus path
     * @param MdfContentSource  Source for all the data
     */
    ContentServerBusObject(const String& busObjectPath, MdfContentSource* contentSource);

    /*
     * @function ~ContentServerBusObject
     * @description destructor
     */
    virtual ~ContentServerBusObject();

    /*
     * @function Register
     * @descriptionRegisters the content source transport.
     * @returns ER_OK if successful, otherwise a range of errors.
     */
    QStatus Register();

    /*
     * @function GetContentSource
     * @description returns the content source
     * @return ContentSource* the content source
     */
    MdfContentSource* GetContentSource() { return m_ContentSource; };

  public: //from BusObject

    /*
     * @function Get
     * @description Handle a bus request to read a property from this object.
     * BusObjects that implement properties should override this method.
     *
     * @param ifcName    Identifies the interface that the property is defined on
     * @param propName  Identifies the the property to get
     * @param[out] val        Returns the property value. The type of this value is the actual value
     *                   type.
     * @return ER_OK if the property is retuned ok
     */
    virtual QStatus Get(const char* ifcName, const char* propName, MsgArg& val);

    QStatus CreateInterface(BusAttachment& busAttachment);

  private:

    QStatus CheckInterface(const InterfaceDescription* contentSourceInterface);

    QStatus AddContentMethodHandlers(BusAttachment& busAttachment);

    void ReplySearchMsgArgs(Message& msg, NodeList* nodes, uint64_t offset, uint32_t limit);

    CapabilitiesMap* Capabilities(size_t capabilitiesCount, MsgArg* capablities);


    /*
     * @function ObjectRegistered
     * @description called when an object is registered
     */
    void ObjectRegistered();

    /*
     * @function Browse
     * @discussion bus object implementation of the GetItem method\
     * @param member
     * @param msg
     */
    void Browse(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);

    /*
     * @function GetItem
     * @discussion bus object implementation of the GetItem method\
     * @param member
     * @param msg
     */
    void GetItem(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);

    /*
     * The busobject GetSortableFields method
     * @param member
     * @param msg
     */
    void GetSortableFields(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);

    /*
     * The busobject GetContentSourceInfo method
     * @param member
     * @param msg
     */
    void GetContentSourceInfo(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);

    /*
     * The busobject ModifyOptionalMetaData method
     * @param member
     * @param msg
     */
    void ModifyOptionalMetaData(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);

    /*
     * The busobject Search method
     * @param member
     * @param msg
     */
    void Search(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);

  private:

    MdfContentSource* m_ContentSource;
};

} /* namespace mdf */

#endif
