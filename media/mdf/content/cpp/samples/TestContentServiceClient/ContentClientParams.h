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

#ifndef CONTENTCLIENTPARAMS_H_
#define CONTENTCLIENTPARAMS_H_

#include <alljoyn/BusAttachment.h>

using namespace ajn;

namespace mdf {

class ContentClientParams {

  public:

    /*
     * @function ContentClientParams
     * @description constructor.
     */
    ContentClientParams();

    /*
     * @function ~ContentClientParams
     * @description default destructor
     */
    virtual ~ContentClientParams();

    /*
     * @function GetBusAttachment
     * @description gets the bus attachment
     * @return const BusAttachment& the bus attachment associated with the object
     * if one has been added. Note - If none is supplied then the class will create
     * one for you. You should only need to create your own in special circumstances
     */
    BusAttachment* GetBusAttachment();

    /*
     * @function GetSessionOpts
     * @description returns the session opts.
     * @retVal SessionOpts if one was set by the user
     */
    const SessionOpts* GetSessionOpts();

    /*
     * @function Init
     * @description This should not be called by the user of this API. It is called by the content client. Calling this prematurely will cause problems
     * @return ER_OK if ok else a range of errors
     */
    QStatus Init();

  private:

    /*
     * @function CreateBusAttachment
     * @description Creates a bus attachment
     * @return ER_OK if the bus attachment has been created successfully, otherwise a range of errors
     */
    QStatus CreateBusAttachment();

    /*
     * @function CreateSessionOpts
     * @description creates the session opts
     * @return ER_OK if the SessopnOpts have been created successfully, otherwise a range of errors
     */
    QStatus CreateSessionOpts();


  private:

    BusAttachment* m_Bus;
    SessionOpts* m_sessionOpts;
};

} /* mdf */

#endif /* ContentClientParams_H_ */
