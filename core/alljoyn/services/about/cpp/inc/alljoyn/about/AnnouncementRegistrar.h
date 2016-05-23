/**
 * @file
 * Used to register an AnnounceHandler for the org.alljoyn.About Announce signal
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

#ifndef ANNOUNCEHANDLERIMPL_H_
#define ANNOUNCEHANDLERIMPL_H_

#include <signal.h>

#include <qcc/Log.h>
#include <alljoyn/version.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/about/AnnounceHandler.h>
#include <alljoyn/about/AboutClient.h>
#include <alljoyn/about/AboutIconClient.h>

namespace ajn {
namespace services {
/**
 *  AnnouncementRegistrar is a helper class enable the Application to register
 *  AnnounceHandlers to receive org.alljoyn.about Announce signals.
 *
 * @deprecated The AnnouncementRegistrar class has been deprecated please see the
 * BusAttachment class for similar functionality as the AnnouncementRegistrar class.
 */
class AnnouncementRegistrar {

  public:
    /**
     * Registers a handler to receive the org.alljoyn.about Announce signal.
     *
     * The handler is only called if all the interfaces are implemented.
     * For example, if the handler should be called if both "com.example.Audio"
     * <em>and</em> "com.example.Video" are implemented then call
     * addAnnouncementHandler once:
     * @code
     * const char* interfaces[] = {"com.example.Audio", "com.example.Video"};
     * RegisterAnnounceHandler(busAttachment, handler, interfaces,
     *                         sizeof(interfaces) / sizeof(interfaces[0]));
     * @endcode
     *
     * If the handler should be called if "com.example.Audio" <em>or</em>
     * "com.example.Video" is implemented then call
     * addAnnouncementHandler multiple times:
     * @code
     * const char* audioInterface[] = {"com.example.Audio"};
     * RegisterAnnounceHandler(busAttachment, handler, audioInterface,
     *                         sizeof(audioInterface) / sizeof(audioInterface[0]));
     * const char* videoInterface[] = {"com.example.Video"};
     * RegisterAnnounceHandler(busAttachment, handler, videoInterface,
     *                         sizeof(videoInterface) / sizeof(videoInterface[0]));
     * @endcode
     *
     * The interface name may be a prefix followed by a `*`.  Using
     * this, the example above could be written as:
     * @code
     * const char* exampleInterface[] = {"com.example.*"};
     * RegisterAnnounceHandler(busAttachment, handler, exampleInterface,
     *                         sizeof(exampleInterface) / sizeof(exampleInterface[0]));
     * @endcode
     *
     * The handler will receive any announcement that implements an interface
     * beginning with the "com.example." name.
     *
     * If RegisterAnnounceHandler is called with lists of interfaces that overlap
     * then multiple Announcements will be occur.
     * For example given the following
     *
     * * @code
     * const char* audioInterface[] = {"com.example.Audio"};
     * RegisterAnnounceHandler(busAttachment, handler, audioInterface,
     *                         sizeof(audioInterface) / sizeof(audioInterface[0]));
     * const char* audioVideoInterface[] = {"com.example.Audio", "com.example.Video"};
     * RegisterAnnounceHandler(busAttachment, handler, audioVideoInterface,
     *                         sizeof(audioVideoInterface) / sizeof(audioVideoInterface[0]));
     * @endcode
     *
     * If a BusAttachment is found that implements both `com.example.Audio`  and
     * interface `com.example.Video` the announce handler will be called twice.
     * Once for the first registration that is looking for `com.example.Audio` and
     * again for the second registration that is looking for both audio and video
     * interfaces.
     *
     * If the same handler is used for for multiple interfaces then it is the
     * handlers responsibility to parse through the reported interfaces to
     * figure out what should be done in response to the Announce signal.
     *
     * Note: specifying NULL for the implementsInterfaces parameter could have
     * significant impact on network performance and should be avoided unless
     * its known that all announcements are needed.
     *
     * @deprecated The AnnouncementRegistrar::RegisterAnnounceHandler function
     * has been deprecated please see the BusAttachment::RegisterAboutListener
     * function and the BusAttachment::WhoImplements function.
     *
     * @param[in] bus reference to BusAttachment
     * @param[in] handler reference to AnnounceHandler
     * @param[in] implementsInterfaces a list of interfaces that the Announce
     *               signal reports as implemented. NULL to receive all Announce
     *               signals regardless of interfaces
     * @param[in] numberInterfaces the number of interfaces in the
     *               implementsInterfaces list
     * @return status
     */
    QCC_DEPRECATED(static QStatus RegisterAnnounceHandler(ajn::BusAttachment & bus, AnnounceHandler & handler, const char** implementsInterfaces, size_t numberInterfaces));

    /**
     * @deprecated This function has been deprecated please change your code
     * to use RegisterAnnounceHandler where you specify the interface(s) that you
     * are interested finding.
     *
     * Using this member function could have significant impact on network
     * performance.
     *
     * @see RegisterAnnounceHandler(ajn::BusAttachment&, AnnounceHandler&, const char**, size_t)
     *
     * Registers a handler to receive the org.alljoyn.about Announce signal.
     *
     * @deprecated The AnnouncementRegistrar::RegisterAnnounceHandler function
     * has been deprecated please see the BusAttachment::RegisterAboutListener
     * function and the BusAttachment::WhoImplements function.
     *
     * @param[in] bus reference to BusAttachment
     * @param[in] handler reference to AnnounceHandler
     *
     * @return status
     */
    QCC_DEPRECATED(static QStatus RegisterAnnounceHandler(ajn::BusAttachment & bus, AnnounceHandler & handler));
    /**
     * Unregisters the AnnounceHandler from receiving the org.alljoyn.about Announce signal.
     *
     * @deprecated The AnnouncementRegistrar::UnRegisterAnnounceHandler function
     * has been deprecated please see the BusAttachment::UnregisterAboutListener
     * function and the BusAttachment::CancelWhoImplements function.
     *
     * @param[in] bus reference to BusAttachment
     * @param[in] handler reference to AnnounceHandler
     * @param[in] implementsInterfaces a list of interfaces that the Announce signal
     *               reports as implmented. NULL to recieve all Announce signals
     *               regardless of interfaces
     * @param[in] numberInterfaces the number of interfaces in the
     *               implementsInterfaces list
     * @return status
     */
    QCC_DEPRECATED(static QStatus UnRegisterAnnounceHandler(ajn::BusAttachment & bus, AnnounceHandler & handler, const char** implementsInterfaces, size_t numberInterfaces));

    /**
     * @deprecated This function has been deprecated please change your code
     * to use UnRegisterAnnounceHandler where you specify the interface(s).
     *
     * @see UnRegisterAnnounceHandler(ajn::BusAttachment&, AnnounceHandler&, const char**, size_t)
     *
     * Unregisters the AnnounceHandler from receiving the org.alljoyn.about Announce signal.
     *
     * @deprecated The AnnouncementRegistrar::UnRegisterAnnounceHandler function
     * has been deprecated please see the BusAttachment::UnregisterAboutListener
     * function and the BusAttachment::CancelWhoImplements function.
     *
     * @param[in] bus reference to BusAttachment
     * @param[in] handler reference to AnnounceHandler
     *
     * @return status
     */
    QCC_DEPRECATED(static QStatus UnRegisterAnnounceHandler(ajn::BusAttachment & bus, AnnounceHandler & handler));

    /**
     * Unregisters all AnnounceHandlers from receiving any org.alljoyn.about Announce signal
     *
     * @deprecated The AnnouncementRegistrar::UnRegisterAnnounceHandler function
     * has been deprecated please see the BusAttachment::UnregisterAllAboutListeners
     * function and the BusAttachment::CancelWhoImplements function.
     *
     * @param[in] bus reference to BusAttachment
     * @return status
     */
    QCC_DEPRECATED(static QStatus UnRegisterAllAnnounceHandlers(ajn::BusAttachment & bus));
};

}
}
#endif /* ANNOUNCEHANDLERIMPL_H_ */
