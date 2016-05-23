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

import org.alljoyn.bus.Status;

public class StatusCodeTest extends TestCase {
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
        assertTrue(checkConvertIntToObj(Status.OK));
        assertTrue(checkConvertIntToObj(Status.FAIL));
        assertTrue(checkConvertIntToObj(Status.WARNING));
        assertTrue(checkConvertIntToObj(Status.BUS_ALREADY_CONNECTED));
    }

    public void testConvertObjToInt()
    {
        assertTrue(checkConvertObjToInt(Status.OK));
        assertTrue(checkConvertObjToInt(Status.FAIL));
        assertTrue(checkConvertObjToInt(Status.WARNING));
        assertTrue(checkConvertObjToInt(Status.BUS_ALREADY_CONNECTED));
    }

    private boolean checkConvertIntToObj(Status sc)
    {
        return sc.equals(convertIntToObj(sc.getErrorCode()));
    }

    private boolean checkConvertObjToInt(Status sc)
    {
        return sc.getErrorCode() == convertObjToInt(sc);
    }

    private native Status convertIntToObj(int sc);
    private native int convertObjToInt(Status sc);
}
