/*
 * Buffer.cc
 *
 *  Created on: Jun 1, 2015
 *      Author: erongo
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
#include "Buffer.h"

namespace nio {

Buffer::Buffer()
{
    m_buffer = nullptr;
    m_capacity = 0;
    m_length = 0;
}

Buffer::Buffer(uint8_t* buf, uint32_t buflen, uint32_t capacity)
{
    Set(buf, buflen, capacity);
}

Buffer::~Buffer()
{
    printf("~Buffer(%p)\n", this);
    //delete [] m_buffer;
}

void Buffer::Set(uint8_t* buf, uint32_t buflen, uint32_t capacity)
{
    m_buffer = buf;
    m_length = buflen;
    m_capacity = capacity;
}

uint8_t* Buffer::GetBuffer()
{
    return m_buffer;
}

uint32_t Buffer::GetLength()
{
    return m_length;
}

uint32_t Buffer::GetCapacity()
{
    return m_capacity;
}

} /* namespace nio */
