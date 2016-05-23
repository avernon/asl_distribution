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
 *
 ******************************************************************************/

#ifndef LSF_JNI_JENUM_H_
#define LSF_JNI_JENUM_H_

#include <jni.h>

namespace lsf {

class JEnum {
  public:
    static JEnum * jControllerClientStatusEnum;
    static JEnum * jErrorCodeEnum;
    static JEnum * jResponseCodeEnum;
    static JEnum * jStatusCodeEnum;

    static JEnum * jLampMakeEnum;
    static JEnum * jLampModelEnum;
    static JEnum * jDeviceTypeEnum;
    static JEnum * jLampTypeEnum;
    static JEnum * jBaseTypeEnum;

    JEnum(char const *className);
    JEnum(char const *className, char const *objMethodName, char const *intMethodName);
    virtual ~JEnum();

    char const *getClassName();
    jclass getClass();

    jobject getObject(int value);
    jint getValue(jobject obj);

  protected:
    char const *clsName;
    char const *objMetName;
    char const *intMetName;
    jclass clsEnum;
    jmethodID midFromValue;
    jmethodID midGetValue;

    void init(char const *className, char const *objMethodName, char const *intMethodName);
    void create();
};

} /* namespace lsf */

#endif /* LSF_JNI_JENUM_H_ */
