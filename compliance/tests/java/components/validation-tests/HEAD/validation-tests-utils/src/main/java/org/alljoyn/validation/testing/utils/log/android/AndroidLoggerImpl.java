/*******************************************************************************
 *  Copyright AllSeen Alliance. All rights reserved.
 *
 *     Contributed by Qualcomm Connected Experiences, Inc.,
 *     with authorization from the AllSeen Alliance, Inc.
 *     
 *     Licensed under the Apache License, Version 2.0 (the "License");
 *     you may not use this file except in compliance with the License.
 *     You may obtain a copy of the License at
 *     
 *         http://www.apache.org/licenses/LICENSE-2.0
 *     
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 *     
 *     Pursuant to Section 1 of the License, the work of authorship constituting
 *     a Work and any Contribution incorporated in the Work shall mean only that
 *     Contributor's code submissions authored by that Contributor.  Any rights
 *     granted under the License are conditioned upon acceptance of these
 *     clarifications.
 *******************************************************************************/
package org.alljoyn.validation.testing.utils.log.android;

import org.alljoyn.validation.testing.utils.log.Logger;

import android.util.Log;

public class AndroidLoggerImpl implements Logger
{
    private final String tag;

    public AndroidLoggerImpl(String tag)
    {
        this.tag = tag;
        if (tag.length() > 23)
        {
            throw new RuntimeException("Tag too long");
        }
    }

    @Override
    public void error(String format, Object... args)
    {
        Log.e(tag, getMessage(format, args));
    }

    @Override
    public void warn(String format, Object... args)
    {
        Log.w(tag, getMessage(format, args));
    }

    @Override
    public void info(String format, Object... args)
    {
        Log.i(tag, getMessage(format, args));
    }

    @Override
    public void debug(String format, Object... args)
    {
        Log.d(tag, getMessage(format, args));
    }

    private String getMessage(String format, Object[] args)
    {
        String msg = format;
        if (args.length > 0)
        {
            msg = String.format(format, args);
        }
        return msg;
    }

    @Override
    public void error(String message, Throwable t)
    {
        Log.e(tag, message, t);
    }

    @Override
    public void warn(String message, Throwable t)
    {
        Log.w(tag, message, t);
    }

    @Override
    public void info(String message, Throwable t)
    {
        Log.i(tag, message, t);
    }

    @Override
    public void debug(String message, Throwable t)
    {
        Log.d(tag, message, t);
    }

}
