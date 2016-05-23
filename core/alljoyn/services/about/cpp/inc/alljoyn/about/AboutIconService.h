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

#ifndef ABOUTICONSERVICE_H_
#define ABOUTICONSERVICE_H_

#include <alljoyn/BusObject.h>

namespace ajn {
namespace services {

/**
 * AboutIconService is an AllJoyn BusObject that implements the org.alljoyn.Icon standard interface.
 * Applications that provide AllJoyn IoE services to receive info about the Icon of the service.
 *
 * @deprecated The AboutIconService class has been deprecated please see the
 * AboutIconObj class for similar functionality as the AboutIconService class.
 */
class AboutIconService : public ajn::BusObject {
  public:

    /**
     * @deprecated The AboutIconService class has been deprecated please see the
     * AboutIconObj class.
     *
     * @param[in] bus  BusAttachment instance associated with this AboutService
     * @param[in]  mimetype of the icon
     * @param[in]  url of the icon
     * @param[in]  data	is the content of the icon
     * @param[in]  csize is the size of the content in bytes.
     */
    QCC_DEPRECATED(AboutIconService(ajn::BusAttachment& bus, qcc::String const& mimetype, qcc::String const& url, uint8_t* data, size_t csize));

    /**
     * @deprecated The AboutIconService class has been deprecated please see the
     * AboutIconObj class.
     *
     * Desctructor of AboutIconService
     */
    QCC_DEPRECATED(virtual ~AboutIconService()) {
    }

    /**
     * Register the AboutIconService  on the AllJoyn bus.
     *
     * @deprecated The AboutIconService class has been deprecated please see the
     * AboutIconObj class.
     *
     * @return status.
     */
    QCC_DEPRECATED(QStatus Register());

  private:
    /**
     * Handles  GetUrl method
     * @param[in]  member
     * @param[in]  msg reference of AllJoyn Message
     */
    void GetUrl(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);

    /**
     *	Handles  GetContent method
     * @param[in]  member
     * @param[in]  msg reference of AllJoyn Message
     */
    void GetContent(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);

    /**
     * Handles the GetPropery request
     * @param[in]  ifcName  interface name
     * @param[in]  propName the name of the properly
     * @param[in]  val reference of MsgArg out parameter.
     * @return
     */
    QStatus Get(const char* ifcName, const char* propName, MsgArg& val);

    /**
     *  pointer to BusAttachment
     */
    ajn::BusAttachment* m_BusAttachment;
    /**
     *	stores the mime type of the icon.
     */
    qcc::String m_MimeType;
    /**
     *	stores the url of the icon
     */
    qcc::String m_Url;

    /**
     *	stores the content of the icon
     */
    uint8_t* m_Content;

    /**
     *	stores the size of the icon's content
     */
    size_t m_ContentSize;

};

}
}

#endif /* ABOUTICONSERVICE_H_ */
