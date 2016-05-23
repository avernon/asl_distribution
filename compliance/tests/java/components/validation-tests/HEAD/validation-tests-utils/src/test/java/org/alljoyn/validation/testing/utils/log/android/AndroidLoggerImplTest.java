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
import org.alljoyn.validation.testing.utils.log.android.AndroidLoggerImpl;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.powermock.api.mockito.PowerMockito;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;

import android.util.Log;

@RunWith(PowerMockRunner.class)
@PrepareForTest(
{ android.util.Log.class })
public class AndroidLoggerImplTest
{

    private static final String TAG = "tag";
    private static final String FORMAT = "%s %d";
    private static final String ARG1 = "arg1";
    private static final int ARG2 = 1234;
    private static final String MSG = "message";
    private static final String FORMATTED_MSG = "arg1 1234";

    @Before
    public void setup() throws Exception
    {
        PowerMockito.mockStatic(Log.class);
    }

    @Test(expected = RuntimeException.class)
    public void testLoggerWithNameTooLong() throws Exception
    {
        new AndroidLoggerImpl("123456789012345678901234");
    }

    @Test
    public void testLogErrorWithFormatting() throws Exception
    {
        Logger logger = new AndroidLoggerImpl(TAG);

        logger.error(FORMAT, ARG1, ARG2);

        PowerMockito.verifyStatic();
        Log.e(TAG, FORMATTED_MSG);
    }

    @Test
    public void testLogErrorWithNoFormattingArg() throws Exception
    {
        Logger logger = new AndroidLoggerImpl(TAG);

        logger.error(MSG);

        PowerMockito.verifyStatic();
        Log.e(TAG, MSG);
    }

    @Test
    public void testLogWarn() throws Exception
    {
        Logger logger = new AndroidLoggerImpl(TAG);

        logger.warn(MSG);

        PowerMockito.verifyStatic();
        Log.w(TAG, MSG);
    }

    @Test
    public void testLogInfo() throws Exception
    {
        Logger logger = new AndroidLoggerImpl(TAG);

        logger.info(MSG);

        PowerMockito.verifyStatic();
        Log.i(TAG, MSG);
    }

    @Test
    public void testLogDebug() throws Exception
    {
        Logger logger = new AndroidLoggerImpl(TAG);

        logger.debug(MSG);

        PowerMockito.verifyStatic();
        Log.d(TAG, MSG);
    }

    @Test
    public void testLogErrorWithException() throws Exception
    {
        Logger logger = new AndroidLoggerImpl(TAG);
        Exception exception = new Exception("My Exception");

        logger.error(MSG, exception);

        PowerMockito.verifyStatic();
        Log.e(TAG, MSG, exception);
    }

    @Test
    public void testLogWarnWithException() throws Exception
    {
        Logger logger = new AndroidLoggerImpl(TAG);
        Exception exception = new Exception("My Exception");

        logger.warn(MSG, exception);

        PowerMockito.verifyStatic();
        Log.w(TAG, MSG, exception);
    }

    @Test
    public void testLogInfoWithException() throws Exception
    {
        Logger logger = new AndroidLoggerImpl(TAG);
        Exception exception = new Exception("My Exception");

        logger.info(MSG, exception);

        PowerMockito.verifyStatic();
        Log.i(TAG, MSG, exception);
    }

    @Test
    public void testLogDebugWithException() throws Exception
    {
        Logger logger = new AndroidLoggerImpl(TAG);
        Exception exception = new Exception("My Exception");

        logger.debug(MSG, exception);

        PowerMockito.verifyStatic();
        Log.d(TAG, MSG, exception);
    }

}
