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

import org.allseen.lsf.PresetPulseEffect;
import org.allseen.lsf.Scene;
import org.allseen.lsf.SceneManagerCallback;
import org.allseen.lsf.SceneWithSceneElements;
import org.allseen.lsf.sdk.ResponseCode;

public class SceneManagerCallbackTest extends TestCase {
    private List<Object> results;
    private SceneManagerCallback callback;

    @Override
    protected void setUp() throws Exception
    {
        results = new ArrayList<Object>();
        callback = new SceneManagerCallback() {
            @Override
            public void getAllSceneIDsReplyCB(ResponseCode responseCode, String[] sceneIDs)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(responseCode);
                results.add(sceneIDs);
            }
            @Override
            public void getSceneNameReplyCB(ResponseCode responseCode, String sceneID, String language, String sceneName)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(responseCode);
                results.add(sceneID);
                results.add(language);
                results.add(sceneName);

            }

            @Override
            public void setSceneNameReplyCB(ResponseCode responseCode, String sceneID, String language)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(responseCode);
                results.add(sceneID);
                results.add(language);
            }

            @Override
            public void scenesNameChangedCB(String[] sceneIDs)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(sceneIDs);

            }
            @Override
            public void createSceneReplyCB(ResponseCode responseCode, String sceneID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(responseCode);
                results.add(sceneID);
            }

            @Override
            public void scenesCreatedCB(String[] sceneIDs)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(sceneIDs);
            }

            @Override
            public void updateSceneReplyCB(ResponseCode responseCode, String sceneID)
            {
            results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
            results.add(responseCode);
            results.add(sceneID);
            }

            @Override
            public void scenesUpdatedCB(String[] sceneIDs)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(sceneIDs);
            }

            @Override
            public void deleteSceneReplyCB(ResponseCode responseCode, String sceneID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(responseCode);
                results.add(sceneID);
            }

            @Override
            public void scenesDeletedCB(String[] sceneIDs)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(sceneIDs);

            }

            @Override
            public void getSceneReplyCB(ResponseCode responseCode, String sceneID, Scene scene)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(responseCode);
                results.add(sceneID);
                results.add(scene.getPresetPulseEffects()[0].getPulsePeriod());
            }

            @Override
            public void applySceneReplyCB(ResponseCode responseCode, String sceneID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(responseCode);
                results.add(sceneID);
            }

            @Override
            public void scenesAppliedCB(String[] sceneIDs)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(sceneIDs);

            }

            @Override
            public void createSceneWithTrackingReplyCB(ResponseCode responseCode, String sceneID, long trackingID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(responseCode);
                results.add(sceneID);
                results.add(trackingID);
            }

            @Override
            public void createSceneWithSceneElementsReplyCB(ResponseCode responseCode, String sceneID, long trackingID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(responseCode);
                results.add(sceneID);
                results.add(trackingID);
            }

            @Override
            public void updateSceneWithSceneElementsReplyCB(ResponseCode responseCode, String sceneID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(responseCode);
                results.add(sceneID);
            }

            @Override
            public void getSceneWithSceneElementsReplyCB(ResponseCode responseCode, String sceneID, SceneWithSceneElements scene)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(responseCode);
                results.add(sceneID);
                results.add(scene.getSceneElements());
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

    private native String getAllSceneIDsReplyCB(SceneManagerCallback lmcb, ResponseCode rc, String[] sceneIDs);
    public void testGetAllSceneIDsReplyCB()
    {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String[] SceneIDs = new String[] { "SceneID-1", "SceneID-2", "SceneID-3" };

        String method = getAllSceneIDsReplyCB(callback, rc, SceneIDs);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, SceneIDs}, results.toArray()));
    }

    private native String getSceneNameReplyCB(SceneManagerCallback lmcb, ResponseCode responseCode, String sceneID, String language, String sceneName);
    public void testGetSceneNameReplyCB()
    {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String SceneID = "SceneID-1";
        String language = "language-1";
        String sceneName = "sceneName-1";

        String method = getSceneNameReplyCB(callback, rc, SceneID, language, sceneName);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, SceneID, language, sceneName}, results.toArray()));
    }

    private native String setSceneNameReplyCB(SceneManagerCallback lmcb, ResponseCode responseCode, String sceneID, String language);
    public void testSetSceneNameReplyCB()
    {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String SceneID = "SceneID-1";
        String language = "language-1";

        String method = setSceneNameReplyCB(callback, rc, SceneID, language);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, SceneID, language}, results.toArray()));
    }

    private native String createSceneReplyCB(SceneManagerCallback lmcb, ResponseCode responseCode, String sceneID);
    public void testCreateSceneReplyCB()
    {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String SceneID = "SceneID-1";


        String method = createSceneReplyCB(callback, rc, SceneID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, SceneID}, results.toArray()));
    }

    private native String updateSceneReplyCB(SceneManagerCallback lmcb, ResponseCode responseCode, String sceneID);
    public void testUpdateSceneReplyCB()
    {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String SceneID = "SceneID-1";

        String method = updateSceneReplyCB(callback, rc, SceneID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, SceneID}, results.toArray()));
    }

    private native String deleteSceneReplyCB(SceneManagerCallback lmcb, ResponseCode responseCode, String sceneID);
    public void testDeleteSceneReplyCB()
    {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String SceneID = "SceneID-1";

        String method = deleteSceneReplyCB(callback, rc, SceneID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, SceneID}, results.toArray()));
    }

    private native String scenesNameChangedCB(SceneManagerCallback lmcb, String[] sceneIDs);
    public void testScenesNameChangedCB()
    {
        String[] SceneIDs = new String[] { "SceneID-1", "SceneID-2", "SceneID-3" };

        String method = scenesNameChangedCB(callback, SceneIDs);

        assertTrue(Arrays.deepEquals(new Object[] {method, SceneIDs}, results.toArray()));
    }

    private native String scenesCreatedCB(SceneManagerCallback lmcb, String[] sceneIDs);
    public void testScenesCreatedCB()
    {
        String[] SceneIDs = new String[] { "SceneID-1", "SceneID-2", "SceneID-3" };

        String method = scenesCreatedCB(callback, SceneIDs);

        assertTrue(Arrays.deepEquals(new Object[] {method, SceneIDs}, results.toArray()));
    }

    private native String scenesUpdatedCB(SceneManagerCallback lmcb, String[] sceneIDs);
    public void testScenesUpdatedCB()
    {
        String[] SceneIDs = new String[] { "SceneID-1", "SceneID-2", "SceneID-3" };

        String method = scenesUpdatedCB(callback, SceneIDs);

        assertTrue(Arrays.deepEquals(new Object[] {method, SceneIDs}, results.toArray()));
    }

    private native String scenesAppliedCB(SceneManagerCallback lmcb, String[] sceneIDs);
    public void testScenesAppliedCB()
    {
        String[] SceneIDs = new String[] { "SceneID-1", "SceneID-2", "SceneID-3" };

        String method = scenesAppliedCB(callback, SceneIDs);

        assertTrue(Arrays.deepEquals(new Object[] {method, SceneIDs}, results.toArray()));
    }

    private native String scenesDeletedCB(SceneManagerCallback lmcb, String[] sceneIDs);
    public void testScenesDeletedCB()
    {
        String[] SceneIDs = new String[] { "SceneID-1", "SceneID-2", "SceneID-3" };

        String method = scenesDeletedCB(callback, SceneIDs);

        assertTrue(Arrays.deepEquals(new Object[] {method, SceneIDs}, results.toArray()));
    }

    private native String updateSceneWithSceneElementsReplyCB(SceneManagerCallback lmcb, ResponseCode responseCode, String sceneID);
    public void testUpdateSceneWithSceneElementsReplyCB()
    {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String SceneID = "SceneID-1";

        String method = updateSceneWithSceneElementsReplyCB(callback, rc, SceneID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, SceneID}, results.toArray()));
    }


    private native String getSceneWithSceneElementsReplyCB(SceneManagerCallback lmcb, ResponseCode responseCode, String sceneID, SceneWithSceneElements scene);
    public void testGetSceneWithSceneElementsReplyCB()
    {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String SceneID = "SceneID-1";
        SceneWithSceneElements scene = new SceneWithSceneElements();

        String[] sceneElementIDs = {"SceneElementID-1", "SceneElementID-2", "SceneElementID-3"};
        scene.setSceneElements(sceneElementIDs);

        String method = getSceneWithSceneElementsReplyCB(callback, rc, SceneID, scene);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, SceneID, scene.getSceneElements()}, results.toArray()));
    }

    private native String getSceneReplyCB(SceneManagerCallback lmcb, ResponseCode responseCode, String sceneID, Scene scene);
    public void testGetSceneReplyCB()
    {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String SceneID = "SceneID-1";
        Scene scene = new Scene();

        long pulsePeriod1= 3485993300L;
        long pulsePeriod2 = 2185993300L;
        PresetPulseEffect ppe = new PresetPulseEffect();
        PresetPulseEffect ppe2 = new PresetPulseEffect();
        ppe.setPulsePeriod(pulsePeriod1);
        ppe.setPulsePeriod(pulsePeriod2);

        PresetPulseEffect[] effects = {ppe, ppe2};
        scene.setPresetPulseEffects(effects);

        String method = getSceneReplyCB(callback, rc, SceneID, scene);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, SceneID, scene.getPresetPulseEffects()[0].getPulsePeriod()}, results.toArray()));
    }

    private native String applySceneReplyCB(SceneManagerCallback lmcb, ResponseCode responseCode, String sceneID);
    public void testApplySceneReplyCB()
    {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String SceneID = "SceneID-1";

        String method = applySceneReplyCB(callback, rc, SceneID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, SceneID}, results.toArray()));
    }


    private native String createSceneWithTrackingReplyCB(SceneManagerCallback lmcb, ResponseCode responseCode, String sceneID, long trackingID);
    public void testCreateSceneWithTrackingReplyCB()
    {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String SceneID = "SceneID-1";
        long trackingID = 3485993300L;

        String method = createSceneWithTrackingReplyCB(callback, rc, SceneID, trackingID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, SceneID, trackingID}, results.toArray()));
    }

    private native String createSceneWithSceneElementsReplyCB(SceneManagerCallback lmcb, ResponseCode responseCode, String sceneID, long trackingID);
    public void testCreateSceneWithSceneElementsReplyCB()
    {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String SceneID = "SceneID-1";
        long trackingID = 3485993300L;

        String method = createSceneWithSceneElementsReplyCB(callback, rc, SceneID, trackingID);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, SceneID, trackingID}, results.toArray()));
    }
}
