/**
 * @file SmartPointer.h
 *
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

#ifndef _ALLJOYN_SMARTPOINTER_H_
#define _ALLJOYN_SMARTPOINTER_H_

#include <qcc/platform.h>
#include <qcc/atomic.h>

namespace qcc {

template <typename T>
class SmartPointer {
  public:

    ~SmartPointer()
    {
        DecRef();
    }

    SmartPointer() : count(NULL), object(NULL) {   }

    SmartPointer(T* t) : count(new int32_t(1)), object(t)   {   }

    SmartPointer(const SmartPointer<T>& other)
        : count(other.count),
        object(other.object)
    {
        IncrementAndFetch(count);
    }

    SmartPointer<T> operator=(const SmartPointer<T>& other)
    {
        DecRef();

        object = other.object;
        count = other.count;
        IncRef();
        return *this;
    }

    SmartPointer<T> operator=(const T* other)
    {
        DecRef();

        object = other;
        count = new int32_t(0);
        IncRef();
        return *this;
    }

    const T& operator*() const { return *object; }
    const T* operator->() const { return object; }
    T* operator->() { return object; }
    T& operator*() { return *object; }


    const T* Get() const { return object; }
    T* Get() { return object; }

    /** Increment the ref count */
    void IncRef()
    {
        IncrementAndFetch(count);
    }

    /** Decrement the ref count and deallocate if necessary. */
    void DecRef()
    {
        const int32_t refs = DecrementAndFetch(count);
        if (0 == refs) {
            delete object;
            object = NULL;
            delete count;
            count = NULL;
        }
    }

  private:
    volatile int32_t* count;
    T* object;
};

}

#endif /* _ALLJOYN_SMARTPOINTER_H_ */
