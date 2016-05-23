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

#ifndef CONTENTSOURCELISTENER_H_
#define CONTENTSOURCELISTENER_H_

namespace mdf {

class MdfContentSource;

class ContentSourceListener {

  public:

    /*
     * @function ContentSourceAdded
     * @description called when a new content source has been added
     * @param contentSource a reference to the content source that was added
     */
    virtual void ContentSourceAdded(MdfContentSource& contentSource) = 0;

    /*
     * @function ContentSourceLost
     * @description called when a new content source has been removed
     * @param contentSource a reference to the content source that was removed
     */
    virtual void ContentSourceLost(MdfContentSource& contentSource) = 0;

    /*
     * @function ~ContentSourceListener
     * @description virtual destructor
     */
    virtual ~ContentSourceListener() { }

};

} //END mdf

#endif /* CONTENSOURCELISTENER_H_ */
