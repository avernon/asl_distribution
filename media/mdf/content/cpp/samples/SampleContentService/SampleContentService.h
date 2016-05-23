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

#ifndef CONTENTSERVERPARAMS_H_
#define CONTENTSERVERPARAMS_H_

#include "MdfContentSource.h"
#include <alljoyn/BusAttachment.h>

#include "alljoyn/about/AboutPropertyStoreImpl.h"

using namespace ajn::services;

namespace mdf {

class ContentServerBusObject;
class ContentBusListener;
class ContentSessionPortListener;

class SampleContentService {
  public:

    /*
     * @function SampleContentService
     * @description constructor. Note that this class must have at least one
     * content source
     * @param contentSource a default content source
     */
    SampleContentService();

    /*
     * @function ~SampleContentService
     * @description default destructor
     */
    virtual ~SampleContentService();

    /*
     * @function Init
     * @description This should not be called by the user of this API. It is called by the content server. Calling this prematurely will cause problems
     * @return ER_OK if ok else a range of errors
     */
    QStatus Init();

  private:

    /*
     * @function CreateAboutPropertyStore
     * @description creates the property store
     * @return AboutPropertyStoreImpl if the property store has been created successfully, otherwise NULL
     */
    AboutPropertyStoreImpl* CreateAboutPropertyStore();


    QStatus InitAboutService(BusAttachment* busAttachment, SessionPort sessionPort);

    QStatus InitContentModel();

    QStatus InitContentComms();

  private:

    SessionPort m_SessionPort;
    BusAttachment* m_BusAttachment;
    SessionOpts* m_sessionOpts;
    AboutPropertyStoreImpl* m_AboutPropertyStore;

    MdfContentSource* m_MdfContentSource;

    ContentServerBusObject* m_ContentServerBusObject;
    AboutServiceApi* m_AboutService;

    ContentBusListener* m_ContentBusListener;
    ContentSessionPortListener* m_ContentSessionPortListener;
};

} /* mdf */

#endif /* CONTENTSERVERPARAMS_H_ */
