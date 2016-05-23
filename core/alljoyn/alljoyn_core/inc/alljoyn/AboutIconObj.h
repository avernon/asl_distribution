/**
 * @file
 * An Alljoyn BusObject that implements the org.alljoyn.Icon interface
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

#ifndef _ALLJOYN_ABOUTICONOBJ_H
#define _ALLJOYN_ABOUTICONOBJ_H

#include <alljoyn/AboutIcon.h>
#include <alljoyn/BusObject.h>

namespace ajn {

/**
 * AboutIconObj is an AllJoyn BusObject that implements the org.alljoyn.Icon standard interface.
 * Applications that provide AllJoyn IoE services to receive info about the Icon of the service.
 */
class AboutIconObj : public BusObject {
  public:
    /**
     * version of the org.alljoyn.Icon interface
     */
    static const uint16_t VERSION;

    /**
     * Construct an About Icon BusObject.
     *
     * @param[in] bus  BusAttachment instance associated with this BusObject
     * @param[in] icon instance of an AboutIcon which holds the icon image
     */
    AboutIconObj(BusAttachment& bus, AboutIcon& icon);

    /**
     *  Destructor of the About Icon BusObject
     */
    virtual ~AboutIconObj();

  private:
    /**
     * Handles  GetUrl method call for the org.alljoyn.Icon interface
     *
     * @param[in]  member
     * @param[in]  msg reference of AllJoyn Message
     */
    void GetUrl(const InterfaceDescription::Member* member, Message& msg);

    /**
     * Handles  GetContent method call for the org.alljoyn.Icon interface
     *
     * @param[in]  member
     * @param[in]  msg reference of AllJoyn Message
     */
    void GetContent(const InterfaceDescription::Member* member, Message& msg);

    /**
     * Handles the GetPropery request for the org.alljoyn.Icon interface
     *
     * @param[in]  ifcName  interface name
     * @param[in]  propName the name of the properly
     * @param[in]  val reference of MsgArg out parameter.
     * @return
     */
    QStatus Get(const char* ifcName, const char* propName, MsgArg& val);

    /**
     * pointer to BusAttachment
     */
    BusAttachment* m_busAttachment;

    /**
     * pointer to AboutIcon
     */
    AboutIcon* m_icon;
};

}

#endif /* _ALLJOYN_ABOUTICONOBJ_H */
