/*
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
 */
package org.allseen.lsf.test;

import junit.framework.TestCase;

import org.allseen.lsf.sdk.ResponseCode;

public class ResponseCodeTest extends TestCase {
    @Override
    protected void setUp() throws Exception
    {
        super.setUp();
    }

    @Override
    protected void tearDown() throws Exception
    {
        super.tearDown();
    }

    public void testConvertIntToObj()
    {
        assertTrue(checkConvertIntToObj(ResponseCode.OK));
        assertTrue(checkConvertIntToObj(ResponseCode.ERR_NULL));
        assertTrue(checkConvertIntToObj(ResponseCode.ERR_UNEXPECTED));
        assertTrue(checkConvertIntToObj(ResponseCode.ERR_INVALID));
        assertTrue(checkConvertIntToObj(ResponseCode.ERR_UNKNOWN));
        assertTrue(checkConvertIntToObj(ResponseCode.ERR_FAILURE));
        assertTrue(checkConvertIntToObj(ResponseCode.ERR_BUSY));
        assertTrue(checkConvertIntToObj(ResponseCode.ERR_REJECTED));
        assertTrue(checkConvertIntToObj(ResponseCode.ERR_RANGE));

        assertNull(convertIntToObj(-1));
    }

    public void testConvertObjToInt()
    {
        assertTrue(checkConvertObjToInt(ResponseCode.OK));
        assertTrue(checkConvertObjToInt(ResponseCode.ERR_NULL));
        assertTrue(checkConvertObjToInt(ResponseCode.ERR_UNEXPECTED));
        assertTrue(checkConvertObjToInt(ResponseCode.ERR_INVALID));
        assertTrue(checkConvertObjToInt(ResponseCode.ERR_UNKNOWN));
        assertTrue(checkConvertObjToInt(ResponseCode.ERR_FAILURE));
        assertTrue(checkConvertObjToInt(ResponseCode.ERR_BUSY));
        assertTrue(checkConvertObjToInt(ResponseCode.ERR_REJECTED));
        assertTrue(checkConvertObjToInt(ResponseCode.ERR_RANGE));
    }

    private boolean checkConvertIntToObj(ResponseCode rc)
    {
        return rc.equals(convertIntToObj(rc.getValue()));
    }

    private boolean checkConvertObjToInt(ResponseCode rc)
    {
        return rc.getValue() == convertObjToInt(rc);
    }

    private native ResponseCode convertIntToObj(int rc);
    private native int convertObjToInt(ResponseCode rc);
}
