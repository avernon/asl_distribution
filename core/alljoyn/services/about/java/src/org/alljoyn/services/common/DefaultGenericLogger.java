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

package org.alljoyn.services.common;

import org.alljoyn.services.common.utils.GenericLogger;

/**
 * An Android implementation of the {@link GenericLogger} class
 * @deprecated
 */
@Deprecated
public class DefaultGenericLogger implements GenericLogger {

    @Override
    @Deprecated
    public void warn(String TAG, String msg)
    {
        System.out.println(new StringBuilder(TAG).append(" Warning: ").append(msg).toString());
    }

    @Override
    @Deprecated
    public void info(String TAG, String msg)
    {
        System.out.println(new StringBuilder(TAG).append(" Info: ").append(msg).toString());
    }

    @Override
    @Deprecated
    public void fatal(String TAG, String msg)
    {
        System.out.println(new StringBuilder(TAG).append(" WTF: ").append(msg).toString());
    }

    @Override
    @Deprecated
    public void error(String TAG, String msg)
    {
        System.out.println(new StringBuilder(TAG).append(" Error: ").append(msg).toString());
    }

    @Override
    @Deprecated
    public void debug(String TAG, String msg)
    {
        System.out.println(new StringBuilder(TAG).append(" Debug: ").append(msg).toString());
    }
}