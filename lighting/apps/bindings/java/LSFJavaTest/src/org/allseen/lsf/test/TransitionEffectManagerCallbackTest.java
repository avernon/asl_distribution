/*
 * Copyright (c), AllSeen Alliance. All rights reserved.
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

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import junit.framework.TestCase;

import org.allseen.lsf.TransitionEffectManagerCallback;
import org.allseen.lsf.TransitionEffectV2;
import org.allseen.lsf.sdk.ResponseCode;

public class TransitionEffectManagerCallbackTest extends TestCase {
    private List<Object> results;
    private TransitionEffectManagerCallback callback;


    @Override
    protected void setUp() throws Exception
    {
        results = new ArrayList<Object>();
        callback = new TransitionEffectManagerCallback() {

            @Override
            public void getTransitionEffectReplyCB(ResponseCode responseCode, String transitionEffectID, TransitionEffectV2 transitionEffect){
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(responseCode);
                results.add(transitionEffectID);
                results.add(transitionEffect.getTransitionPeriod());

            }


            @Override
            public void applyTransitionEffectOnLampsReplyCB(ResponseCode responseCode, String transitionEffectID, String[] lampIDs){
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(responseCode);
                results.add(transitionEffectID);
                results.add(lampIDs);

            }

            @Override
            public void applyTransitionEffectOnLampGroupsReplyCB(ResponseCode responseCode, String transitionEffectID, String[] lampGroupIDs){
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(responseCode);
                results.add(transitionEffectID);
                results.add(lampGroupIDs);

            }

            @Override
            public void getAllTransitionEffectIDsReplyCB(ResponseCode responseCode, String[] transitionEffectIDs){
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(responseCode);
                results.add(transitionEffectIDs);


            }

            @Override
            public void getTransitionEffectNameReplyCB(ResponseCode responseCode, String transitionEffectID, String language, String transitionEffectName){
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(responseCode);
                results.add(transitionEffectID);
                results.add(language);
                results.add(transitionEffectName);

            }
            @Override
            public void setTransitionEffectNameReplyCB(ResponseCode responseCode, String transitionEffectID, String language){
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(responseCode);
                results.add(transitionEffectID);
                results.add(language);

            }

            @Override
            public void transitionEffectsNameChangedCB(String[] transitionEffectIDs){
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(transitionEffectIDs);

            }

            @Override
            public void createTransitionEffectReplyCB(ResponseCode responseCode, String transitionEffectID, long trackingID){
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(responseCode);
                results.add(transitionEffectID);
                results.add(trackingID);

            }

            @Override
            public void transitionEffectsCreatedCB(String[] transitionEffectIDs){
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(transitionEffectIDs);

            }


            @Override
            public void updateTransitionEffectReplyCB(ResponseCode responseCode, String transitionEffectID){
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(responseCode);
                results.add(transitionEffectID);
            }


            @Override
            public void transitionEffectsUpdatedCB(String[] transitionEffectIDs){
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(transitionEffectIDs);

            }

            @Override
            public void deleteTransitionEffectReplyCB(ResponseCode responseCode, String transitionEffectID){
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(responseCode);
                results.add(transitionEffectID);


            }

            @Override
            public void transitionEffectsDeletedCB(String[] transitionEffectIDs){
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(transitionEffectIDs);

            }

        };

        super.setUp();
    }


    @Override
    protected void tearDown() throws Exception
    {
        results = null;
        callback = null;

        super.tearDown();
    }

    private native String getTransitionEffectReplyCB(TransitionEffectManagerCallback temcb,  ResponseCode responseCode, String transitionEffectID, TransitionEffectV2 transitionEffect);
    public void testGetTransitionEffectReplyCB(){
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String transitionEffectID = "ID -1";
        TransitionEffectV2 tf = new TransitionEffectV2();

        long transitionPeriod = 94859302;
        tf.setTransitionPeriod(transitionPeriod);

        String method = getTransitionEffectReplyCB(callback, rc, transitionEffectID, tf);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, transitionEffectID, tf.getTransitionPeriod()}, results.toArray()));
    }

    private native String applyTransitionEffectOnLampsReplyCB(TransitionEffectManagerCallback temcb,  ResponseCode responseCode, String transitionEffectID, String[] lampIDs);
    public void testApplyTransitionEffectOnLampsReplyCB(){
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String transitionEffectID = "ID -1";
        String[] lampIDs = {"LOOK", "AT", "THESE", "IDS"};

        String method = applyTransitionEffectOnLampsReplyCB(callback, rc, transitionEffectID, lampIDs);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, transitionEffectID, lampIDs}, results.toArray()));
    }

    private native String applyTransitionEffectOnLampGroupsReplyCB(TransitionEffectManagerCallback temcb,  ResponseCode responseCode, String transitionEffectID, String[] lampGroupIDs);
    public void testApplyTransitionEffectOnLampGroupsReplyCB(){
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String transitionEffectID = "ID -1";
        String[] lampIDs = {"LOOK", "AT", "THESE", "IDS"};

        String method = applyTransitionEffectOnLampGroupsReplyCB(callback, rc, transitionEffectID, lampIDs);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, transitionEffectID, lampIDs}, results.toArray()));
    }

    private native String getAllTransitionEffectIDsReplyCB(TransitionEffectManagerCallback temcb,  ResponseCode responseCode, String[] transitionEffectIDs);
    public void testGetAllTransitionEffectIDsReplyCB(){
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String[] transitionEffectIDs = {"LOOK", "AT", "THESE", "IDS"};

        String method = getAllTransitionEffectIDsReplyCB(callback, rc, transitionEffectIDs);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, transitionEffectIDs}, results.toArray()));
    }

    private native String getTransitionEffectNameReplyCB(TransitionEffectManagerCallback temcb,  ResponseCode responseCode, String transitionEffectID, String language, String transitionEffectName);
    public void testGetTransitionEffectNameReplyCB(){
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String transitionEffectID = "ID -1";
        String language = "language-1";
        String transitionEffectName = "transitionEffectname-1";

        String method = getTransitionEffectNameReplyCB(callback, rc, transitionEffectID, language, transitionEffectName);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, transitionEffectID, language, transitionEffectName}, results.toArray()));
    }

    private native String setTransitionEffectNameReplyCB(TransitionEffectManagerCallback temcb,  ResponseCode responseCode, String transitionEffectID, String language);
    public void testSetTransitionEffectNameReplyCB(){
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String transitionEffectID = "ID -1";
        String language = "language-1";

        String method = setTransitionEffectNameReplyCB(callback, rc, transitionEffectID, language);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, transitionEffectID, language}, results.toArray()));
    }

    private native String transitionEffectsNameChangedCB(TransitionEffectManagerCallback temcb,  String[] transitionEffectIDs);
    public void testTransitionEffectsNameChangedCB(){
        String[] transitionEffectIDs = {"LOOK", "AT", "THESE", "IDS"};

        String method = transitionEffectsNameChangedCB(callback, transitionEffectIDs);

        assertTrue(Arrays.deepEquals(new Object[] {method, transitionEffectIDs}, results.toArray()));
    }


    private native String createTransitionEffectReplyCB(TransitionEffectManagerCallback temcb,  ResponseCode responseCode, String transitionEffectID, long trackingID);
    public void testCreateTransitionEffectReplyCB(){
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String transitionEffectID = "ID -1";
        long trackingID = 2200000500L;

        String method = createTransitionEffectReplyCB(callback, rc, transitionEffectID, trackingID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, transitionEffectID, trackingID}, results.toArray()));
    }

    private native String transitionEffectsCreatedCB(TransitionEffectManagerCallback temcb,  String[] transitionEffectIDs);
    public void testTransitionEffectsCreatedCB(){
        String[] transitionEffectIDs = {"LOOK", "AT", "THESE", "IDS"};

        String method = transitionEffectsCreatedCB(callback, transitionEffectIDs);

        assertTrue(Arrays.deepEquals(new Object[] {method, transitionEffectIDs}, results.toArray()));
    }

    private native String updateTransitionEffectReplyCB(TransitionEffectManagerCallback temcb,  ResponseCode responseCode, String transitionEffectID);
    public void testUpdateTransitionEffectReplyCB(){
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String transitionEffectID = "ID -1";

        String method = updateTransitionEffectReplyCB(callback, rc, transitionEffectID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, transitionEffectID}, results.toArray()));
    }

    private native String transitionEffectsUpdatedCB(TransitionEffectManagerCallback temcb,  String[] transitionEffectIDs);
    public void testTransitionEffectsUpdatedCB(){
        String[] transitionEffectIDs = {"LOOK", "AT", "THESE", "IDS"};

        String method = transitionEffectsUpdatedCB(callback, transitionEffectIDs);

        assertTrue(Arrays.deepEquals(new Object[] {method, transitionEffectIDs}, results.toArray()));
    }

    private native String deleteTransitionEffectReplyCB(TransitionEffectManagerCallback temcb,  ResponseCode responseCode, String transitionEffectID);
    public void testDeleteTransitionEffectReplyCB(){
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String transitionEffectID = "ID -1";

        String method = deleteTransitionEffectReplyCB(callback, rc, transitionEffectID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, transitionEffectID}, results.toArray()));
    }

    private native String transitionEffectsDeletedCB(TransitionEffectManagerCallback temcb,  String[] transitionEffectIDs);
    public void testTransitionEffectsDeletedCB(){
        String[] transitionEffectIDs = {"LOOK", "AT", "THESE", "IDS"};

        String method = transitionEffectsDeletedCB(callback, transitionEffectIDs);

        assertTrue(Arrays.deepEquals(new Object[] {method, transitionEffectIDs}, results.toArray()));
    }
}
