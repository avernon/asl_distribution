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

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import junit.framework.TestCase;

import org.allseen.lsf.LampGroup;
import org.allseen.lsf.LampGroupManagerCallback;
import org.allseen.lsf.sdk.ResponseCode;

public class LampGroupManagerCallbackTest extends TestCase {
    private List<Object> results;
    private LampGroupManagerCallback callback;

    @Override
    protected void setUp() throws Exception
    {
        results = new ArrayList<Object>();
        callback = new LampGroupManagerCallback() {

            @Override
            public void getAllLampGroupIDsReplyCB(ResponseCode rc, String[] lampGroupIDs)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupIDs);
            }

            @Override
            public void getLampGroupNameReplyCB(ResponseCode rc, String lampGroupID, String language, String lampName)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
                results.add(language);
                results.add(lampName);
            }

            @Override
            public void setLampGroupNameReplyCB(ResponseCode rc, String lampGroupID, String language)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(language);
                results.add(lampGroupID);
            }

            @Override
            public void lampGroupsNameChangedCB(String[] lampGroupIDs)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(lampGroupIDs);
            }

            @Override
            public void getLampGroupReplyCB(ResponseCode rc, String lampGroupID, LampGroup lampGroup)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
                results.add(lampGroup.getLamps()[0]);
                results.add(lampGroup.getLampGroups()[0]);
            }

            @Override
            public void lampGroupsUpdatedCB(String[] lampGroupIDs)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(lampGroupIDs);
            }

            @Override
            public void transitionLampGroupStateOnOffFieldReplyCB(ResponseCode rc, String lampGroupID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
            }

            @Override
            public void createLampGroupReplyCB(ResponseCode rc, String lampGroupID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
            }

            @Override
            public void lampGroupsCreatedCB(String[] lampGroupIDs)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(lampGroupIDs);
            }

            @Override
            public void deleteLampGroupReplyCB(ResponseCode rc, String lampGroupID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
            }

            @Override
            public void lampGroupsDeletedCB(String[] lampGroupIDs)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(lampGroupIDs);
            }

            @Override
            public void transitionLampGroupStateReplyCB(ResponseCode rc, String lampGroupID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
            }

            @Override
            public void pulseLampGroupWithStateReplyCB(ResponseCode rc, String lampGroupID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
            }

            @Override
            public void pulseLampGroupWithPresetReplyCB(ResponseCode rc, String lampGroupID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
            }

            @Override
            public void transitionLampGroupStateHueFieldReplyCB(ResponseCode rc, String lampGroupID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
            }

            @Override
            public void transitionLampGroupStateSaturationFieldReplyCB(ResponseCode rc, String lampGroupID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
            }

            @Override
            public void transitionLampGroupStateBrightnessFieldReplyCB(ResponseCode rc, String lampGroupID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
            }

            @Override
            public void transitionLampGroupStateColorTempFieldReplyCB(ResponseCode rc, String lampGroupID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
            }

            @Override
            public void resetLampGroupStateReplyCB(ResponseCode rc, String lampGroupID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
            }

            @Override
            public void resetLampGroupStateOnOffFieldReplyCB(ResponseCode rc, String lampGroupID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
            }

            @Override
            public void resetLampGroupStateHueFieldReplyCB(ResponseCode rc, String lampGroupID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
            }

            @Override
            public void resetLampGroupStateSaturationFieldReplyCB(ResponseCode rc, String lampGroupID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
            }

            @Override
            public void resetLampGroupStateBrightnessFieldReplyCB(ResponseCode rc, String lampGroupID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
            }

            @Override
            public void resetLampGroupStateColorTempFieldReplyCB(ResponseCode rc, String lampGroupID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
            }

            @Override
            public void updateLampGroupReplyCB(ResponseCode rc, String lampGroupID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
            }

            @Override
            public void transitionLampGroupStateToPresetReplyCB(ResponseCode rc, String lampGroupID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
            }

            @Override
            public void createLampGroupWithTrackingReplyCB(ResponseCode rc, String lampGroupID, long trackingID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
                results.add(trackingID);
            }

            @Override
            public void setLampGroupEffectReplyCB(ResponseCode rc, String lampGroupID, String effectID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampGroupID);
                results.add(effectID);
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

    private native String getAllLampGroupIDsReplyCB(LampGroupManagerCallback lgmcb, ResponseCode rc, String[] lampGroupIDs);
    public void testGetAllLampGroupIDsReplyCB()
    {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String[] lampGroupIDs = new String[] { "LampGroupID-1", "LampGroupID-2", "LampGroupID-3" };

        String method = getAllLampGroupIDsReplyCB(callback, rc, lampGroupIDs);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupIDs}, results.toArray()));
    }

    private native String getLampGroupNameReplyCB(LampGroupManagerCallback lgmcb, ResponseCode rc, String lampGroupID, String language, String lampGroupName);
    public void testGetLampGroupNameReplyCB()
    {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";
        String language = "EN";
        String lampGroupName = "LampGroupName-1";

        String method = getLampGroupNameReplyCB(callback, rc, lampGroupID, language, lampGroupName);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID, language, lampGroupName}, results.toArray()));
    }

    private native String setLampGroupNameReplyCB(LampGroupManagerCallback lgmcb, ResponseCode rc, String lampGroupID, String language);
    public void testSetLampNameReplyCB()
    {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";
        String language = "EN";

        String method = setLampGroupNameReplyCB(callback, rc, lampGroupID, language);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, language, lampGroupID}, results.toArray()));
    }

    private native String getLampGroupReplyCB(LampGroupManagerCallback lgmcb, ResponseCode rc, String lampGroupID, LampGroup lampGroup);
    public void testGetLampGroupReplyCB()
    {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";
        LampGroup lampGroup = new LampGroup();
        String[] lampIDs = new String[] { "A", "B", "C", "D", "E" };
        String[] lampGroupIDs = new String[] { "F", "G", "H" };

        lampGroup.setLamps(lampIDs);
        lampGroup.setLampGroups(lampGroupIDs);

        String method = getLampGroupReplyCB(callback, rc, lampGroupID, lampGroup);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID, lampIDs[0], lampGroupIDs[0]}, results.toArray()));
    }

    private native String transitionLampGroupStateOnOffFieldReplyCB(LampGroupManagerCallback lgmcb, ResponseCode responseCode, String lampGroupID);
    public void testTransitionLampGroupStateOnOffFieldReplyCB() {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";

        String method = transitionLampGroupStateOnOffFieldReplyCB(callback, rc, lampGroupID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID}, results.toArray()));
    }

    private native String lampGroupsNameChangedCB(LampGroupManagerCallback lgmcb, String[] lampGroupIDs);
    public void testLampGroupsNameChangedCB() {
        String[] lampGroupIDs = {"LampGroupID-1", "LampGroupID-2", "LampGroupID-3"};
        String method = lampGroupsNameChangedCB(callback, lampGroupIDs);

        assertTrue(Arrays.deepEquals(new Object[] {method, lampGroupIDs}, results.toArray()));
    }

    private native String lampGroupsUpdatedCB(LampGroupManagerCallback lgmcb, String[] lampGroupIDs);
    public void testLampGroupsUpdatedCB() {
        String[] lampGroupIDs = {"LampGroupID-1", "LampGroupID-2", "LampGroupID-3"};
        String method = lampGroupsUpdatedCB(callback, lampGroupIDs);

        assertTrue(Arrays.deepEquals(new Object[] {method, lampGroupIDs}, results.toArray()));
    }

    private native String createLampGroupReplyCB(LampGroupManagerCallback lgmcb, ResponseCode responseCode, String lampGroupID);
    public void testCreateLampGroupReplyCB() {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";
        String method = createLampGroupReplyCB(callback, rc, lampGroupID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID}, results.toArray()));
    }

    private native String lampGroupsCreatedCB(LampGroupManagerCallback lgmcb, String[] lampGroupIDs);
    public void testLampGroupsCreatedCB() {
        String[] lampGroupIDs = {"LampGroupID-1", "LampGroupID-2", "LampGroupID-3"};
        String method = lampGroupsCreatedCB(callback, lampGroupIDs);

        assertTrue(Arrays.deepEquals(new Object[] {method, lampGroupIDs}, results.toArray()));
    }

    private native String deleteLampGroupReplyCB(LampGroupManagerCallback lgmcb, ResponseCode responseCode, String lampGroupID);
    public void testDeleteLampGroupReplyCB() {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";

        String method = deleteLampGroupReplyCB(callback, rc, lampGroupID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID}, results.toArray()));
    }

    private native String lampGroupsDeletedCB(LampGroupManagerCallback lgmcb, String[] lampGroupIDs);
    public void testLampGroupsDeletedCB() {
        String[] lampGroupIDs = {"LampGroupID-1", "LampGroupID-2", "LampGroupID-3"};
        String method = lampGroupsDeletedCB(callback, lampGroupIDs);

        assertTrue(Arrays.deepEquals(new Object[] {method, lampGroupIDs}, results.toArray()));
    }

    private native String transitionLampGroupStateReplyCB(LampGroupManagerCallback lgmcb, ResponseCode responseCode, String lampGroupID);
    public void testTransitionLampGroupStateReplyCB() {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";

        String method = transitionLampGroupStateReplyCB(callback, rc, lampGroupID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID}, results.toArray()));

    }

    private native String pulseLampGroupWithStateReplyCB(LampGroupManagerCallback lgmcb, ResponseCode responseCode, String lampGroupID);
    public void testPulseLampGroupWithStateReplyCB() {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";

        String method = pulseLampGroupWithStateReplyCB(callback, rc, lampGroupID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID}, results.toArray()));
    }

    private native String pulseLampGroupWithPresetReplyCB(LampGroupManagerCallback lgmcb, ResponseCode responseCode, String lampGroupID);
    public void testPulseLampGroupWithPresetReplyCB() {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";

        String method = pulseLampGroupWithPresetReplyCB(callback, rc, lampGroupID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID}, results.toArray()));
    }

    private native String transitionLampGroupStateHueFieldReplyCB(LampGroupManagerCallback lgmcb, ResponseCode responseCode, String lampGroupID);
    public void testTransitionLampGroupStateHueFieldReplyCB() {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";

        String method = transitionLampGroupStateHueFieldReplyCB(callback, rc, lampGroupID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID}, results.toArray()));
    }

    private native String transitionLampGroupStateSaturationFieldReplyCB(LampGroupManagerCallback lgmcb, ResponseCode responseCode, String lampGroupID);
    public void testTransitionLampGroupStateSaturationFieldReplyCB() {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";

        String method = transitionLampGroupStateSaturationFieldReplyCB(callback, rc, lampGroupID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID}, results.toArray()));
    }

    private native String transitionLampGroupStateBrightnessFieldReplyCB(LampGroupManagerCallback lgmcb, ResponseCode responseCode, String lampGroupID);
    public void testTransitionLampGroupStateBrightnessFieldReplyCB() {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";

        String method = transitionLampGroupStateBrightnessFieldReplyCB(callback, rc, lampGroupID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID}, results.toArray()));
    }

    private native String transitionLampGroupStateColorTempFieldReplyCB(LampGroupManagerCallback lgmcb, ResponseCode responseCode, String lampGroupID);
    public void testTransitionLampGroupStateColorTempFieldReplyCB() {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";

        String method = transitionLampGroupStateColorTempFieldReplyCB(callback, rc, lampGroupID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID}, results.toArray()));
    }

    private native String resetLampGroupStateReplyCB(LampGroupManagerCallback lgmcb, ResponseCode responseCode, String lampGroupID);
    public void testResetLampGroupStateReplyCB() {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";

        String method = resetLampGroupStateReplyCB(callback, rc, lampGroupID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID}, results.toArray()));
    }

    private native String resetLampGroupStateOnOffFieldReplyCB(LampGroupManagerCallback lgmcb, ResponseCode responseCode, String lampGroupID);
    public void testResetLampGroupStateOnOffFieldReplyCB() {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";

        String method = resetLampGroupStateOnOffFieldReplyCB(callback, rc, lampGroupID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID}, results.toArray()));
    }

    private native String resetLampGroupStateHueFieldReplyCB(LampGroupManagerCallback lgmcb, ResponseCode responseCode, String lampGroupID);
    public void testResetLampGroupStateHueFieldReplyCB() {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";

        String method = resetLampGroupStateHueFieldReplyCB(callback, rc, lampGroupID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID}, results.toArray()));
    }

    private native String resetLampGroupStateSaturationFieldReplyCB(LampGroupManagerCallback lgmcb, ResponseCode responseCode, String lampGroupID);
    public void testResetLampGroupStateSaturationFieldReplyCB() {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";

        String method = resetLampGroupStateSaturationFieldReplyCB(callback, rc, lampGroupID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID}, results.toArray()));
    }

    private native String resetLampGroupStateBrightnessFieldReplyCB(LampGroupManagerCallback lgmcb, ResponseCode responseCode, String lampGroupID);
    public void testResetLampGroupStateBrightnessFieldReplyCB() {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";

        String method = resetLampGroupStateBrightnessFieldReplyCB(callback, rc, lampGroupID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID}, results.toArray()));
    }

    private native String resetLampGroupStateColorTempFieldReplyCB(LampGroupManagerCallback lgmcb, ResponseCode responseCode, String lampGroupID);
    public void testResetLampGroupStateColorTempFieldReplyCB() {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";

        String method = resetLampGroupStateColorTempFieldReplyCB(callback, rc, lampGroupID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID}, results.toArray()));
    }

    private native String updateLampGroupReplyCB(LampGroupManagerCallback lgmcb, ResponseCode responseCode, String lampGroupID);
    public void testUpdateLampGroupReplyCB() {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";

        String method = updateLampGroupReplyCB(callback, rc, lampGroupID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID}, results.toArray()));
    }

    private native String transitionLampGroupStateToPresetReplyCB(LampGroupManagerCallback lgmcb, ResponseCode responseCode, String lampGroupID);
    public void testTransitionLampGroupStateToPresetReplyCB() {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";

        String method = transitionLampGroupStateToPresetReplyCB(callback, rc, lampGroupID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID}, results.toArray()));
    }

    private native String createLampGroupWithTrackingReplyCB(LampGroupManagerCallback lgmcb, ResponseCode responseCode, String lampGroupID, long trackingID);
    public void testCreateLampGroupWithTrackingReplyCB() {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";
        long trackingID = 3485993300L;

        String method = createLampGroupWithTrackingReplyCB(callback, rc, lampGroupID, trackingID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID, trackingID}, results.toArray()));
    }

    private native String setLampGroupEffectReplyCB(LampGroupManagerCallback lgmcb, ResponseCode responseCode, String lampGroupID, String effectID);
    public void testSetLampGroupEffectReplyCB() {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampGroupID = "LampGroupID-1";
        String effectID = "effectID-1";

        String method = setLampGroupEffectReplyCB(callback, rc, lampGroupID, effectID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampGroupID, effectID}, results.toArray()));
    }

}
