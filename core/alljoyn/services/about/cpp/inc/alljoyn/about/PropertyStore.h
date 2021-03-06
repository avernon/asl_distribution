/**
 * @file
 * User implemented property store responsible for holding the AboutService properties
 * @see AboutPropertyStoreImpl.h
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
#ifndef _PROPERTYSTORE_H
#define _PROPERTYSTORE_H

#include <alljoyn/Status.h>
#include <alljoyn/MsgArg.h>

namespace ajn {
namespace services {
/**
 * The language tag specified is not supported
 */
#define ER_LANGUAGE_NOT_SUPPORTED       ((QStatus)0xb001)
/**
 * The request feature is not available or has not be implemented
 */
#define ER_FEATURE_NOT_AVAILABLE        ((QStatus)0xb002)
/**
 * The value requested is invalid
 */
#define ER_INVALID_VALUE                ((QStatus)0xb003)
/**
 * The maximum allowed size for an element has been exceeded.
 */
#define ER_MAX_SIZE_EXCEEDED            ((QStatus)0xb004)

/**
 * PropertyStore is implemented by the application , it is responsible to store
 * the properties of the AboutServie and ConfigService.
 *
 * @deprecated The PropertyStore class has been deprecated please see the
 * AboutDataListener class for similar functionality as the PropertyStore class.
 */
class PropertyStore {
  public:

    /**
     * Filter has three possible values ANNOUNCE, READ,WRITE
     * READ is for data that is marked as read
     * ANNOUNCE is for data that is marked as announce
     * WRITE is for data that is marked as write
     */
    typedef enum {
        ANNOUNCE,         //!< ANNOUNCE Property that has  ANNOUNCE  enabled
        READ,            //!< READ     Property that has READ  enabled
        WRITE,           //!< WRITE    Property that has  WRITE  enabled
    } Filter;

    /**
     * Calls Reset() implemented only for  ConfigService
     *
     * @deprecated The PropertyStore::Reset function has been deprecated please
     * see the AboutDataListener class. There is not equivalent functionality
     * for the Reset function in the AboutDataListener or the AboutData class.
     * If this functionality is required the developer is responsible for adding
     * it by creating there own AboutdataListener implementation.
     *
     * @return status
     */
    QCC_DEPRECATED(virtual QStatus Reset()) {
        return ER_NOT_IMPLEMENTED;
    }

    /**
     * @deprecated The PropertyStore::Reset function has been deprecated please
     * see the AboutDataListener::GetAboutData function and
     * AboutDataListener::GetAnnouncedAboutData function.
     *
     * @param[in] languageTag is the language to use for the action can be NULL meaning default.
     * @param[in] filter describe which properties to read.
     * @param[out] all reference to MsgArg
     * @return status
     */
    QCC_DEPRECATED(virtual QStatus ReadAll(const char* languageTag, Filter filter, ajn::MsgArg & all)) = 0;

    /**
     * @deprecated The PropertyStore::Update function has been deprecated please
     * see the AboutDataListener class. There is not equivalent functionality
     * for the Update function in the AboutDataListener or the AboutData class.
     * If this functionality is required the developer is responsible for adding
     * it by creating there own AboutdataListener implementation.
     *
     * @param[in] name of the property
     * @param[in] languageTag is the language to use for the action can be NULL meaning default.
     * @param[in] value is a pointer to the data to change.
     * @return status
     */
    QCC_DEPRECATED(virtual QStatus Update(const char* name, const char* languageTag, const ajn::MsgArg * value)) {
        return ER_NOT_IMPLEMENTED;
    }
    /**
     * @deprecated The PropertyStore::Update function has been deprecated please
     * see the AboutDataListener class. There is not equivalent functionality
     * for the Update function in the AboutDataListener or the AboutData class.
     * If this functionality is required the developer is responsible for adding
     * it by creating there own AboutdataListener implementation.
     *
     * @param[in] name of the property
     * @param[in] languageTag is the language to use for the action can't be NULL.
     * @return[in] status
     */
    QCC_DEPRECATED(virtual QStatus Delete(const char* name, const char* languageTag)) {
        return ER_NOT_IMPLEMENTED;
    }
    /**
     * Desctructor of PropertyStore
     *
     * @deprecated The PropertyStore class has been deprecated please see the
     * AboutDataListener class.
     */
    QCC_DEPRECATED(virtual ~PropertyStore()) = 0;
};
inline PropertyStore::~PropertyStore() {
}

}
}

#endif /* _PROPERTYSTORE_H */
