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

import org.allseen.lsf.LampManagerCallback;
import org.allseen.lsf.LampState;
import org.allseen.lsf.sdk.LampDetails;
import org.allseen.lsf.sdk.LampParameters;
import org.allseen.lsf.sdk.ResponseCode;

public class LampManagerCallbackTest extends TestCase {
    private List<Object> results;
    private LampManagerCallback callback;

    @Override
    protected void setUp() throws Exception
    {
        results = new ArrayList<Object>();
        callback = new LampManagerCallback() {
            @Override
            public void getAllLampIDsReplyCB(ResponseCode rc, String[] lampIDs)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampIDs);
            }

            @Override
            public void getLampNameReplyCB(ResponseCode rc, String lampID, String language, String lampName)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
                results.add(language);
                results.add(lampName);
            }

            @Override
            public void setLampNameReplyCB(ResponseCode rc, String lampID, String language)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
                results.add(language);
            }

            @Override
            public void lampNameChangedCB(String lampID, String lampName)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(lampID);
                results.add(lampName);
            }

            @Override
            public void getLampDetailsReplyCB(ResponseCode rc, String lampID, LampDetails details)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
                results.add(details.getMinTemperature());
            }

            @Override
            public void getLampParametersReplyCB(ResponseCode rc, String lampID, LampParameters params)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
                results.add(params.getEnergyUsageMilliwatts());
            }

            @Override
            public void getLampStateReplyCB(ResponseCode rc, String lampID, LampState state)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
                results.add(state.getColorTemp());
            }

            @Override
            public void getLampStateHueFieldReplyCB(ResponseCode rc, String lampID, long hue) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
                results.add(hue);
            }

            @Override
            public void resetLampStateReplyCB(ResponseCode rc, String lampID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
            }

            @Override
            public void lampStateChangedCB(String lampID, LampState lampState)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(lampID);
                results.add(lampState.getColorTemp());
            }

            @Override
            public void clearLampFaultReplyCB(ResponseCode rc, String lampID, long faultCode)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
                results.add(faultCode);
            }

            @Override
            public void getLampManufacturerReplyCB(ResponseCode rc, String lampID, String language, String manufacturer)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
                results.add(language);
                results.add(manufacturer);
            }

            @Override
            public void lampsFoundCB(String[] lampIDs)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(lampIDs);
            }

            @Override
            public void lampsLostCB(String[] lampIDs)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(lampIDs);
            }

            @Override
            public void getLampParametersEnergyUsageMilliwattsFieldReplyCB(ResponseCode rc, String lampID, long energyUsageMilliwatts)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
                results.add(energyUsageMilliwatts);
            }

            @Override
            public void getLampParametersLumensFieldReplyCB(ResponseCode rc, String lampID, long brightnessLumens)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
                results.add(brightnessLumens);
            }

            @Override
            public void getLampStateOnOffFieldReplyCB(ResponseCode rc, String lampID, boolean onOff)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
                results.add(onOff);
            }

            @Override
            public void getLampStateSaturationFieldReplyCB(ResponseCode rc, String lampID, long saturation) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
                results.add(saturation);
            }

            @Override
            public void getLampStateBrightnessFieldReplyCB(ResponseCode rc, String lampID, long brightness) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
                results.add(brightness);
            }

            @Override
            public void getLampStateColorTempFieldReplyCB(ResponseCode rc, String lampID, long colorTemp) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
                results.add(colorTemp);
            }

            @Override
            public void pulseLampWithStateReplyCB(ResponseCode rc, String lampID) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
            }

            @Override
            public void pulseLampWithPresetReplyCB(ResponseCode rc, String lampID) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
            }

            @Override
            public void transitionLampStateOnOffFieldReplyCB(ResponseCode rc, String lampID) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
            }

            @Override
            public void transitionLampStateHueFieldReplyCB(ResponseCode rc, String lampID) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
            }

            @Override
            public void transitionLampStateSaturationFieldReplyCB(ResponseCode rc, String lampID) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
            }

            @Override
            public void transitionLampStateBrightnessFieldReplyCB(ResponseCode rc, String lampID) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
            }

            @Override
            public void transitionLampStateColorTempFieldReplyCB(ResponseCode rc, String lampID) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
            }

            @Override
            public void getLampServiceVersionReplyCB(ResponseCode rc, String lampID, long lampServiceVersion) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
                results.add(lampServiceVersion);
            }

            @Override
            public void resetLampStateOnOffFieldReplyCB(ResponseCode rc, String lampID) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
            }

            @Override
            public void resetLampStateHueFieldReplyCB(ResponseCode rc, String lampID) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
            }

            @Override
            public void resetLampStateSaturationFieldReplyCB(ResponseCode rc, String lampID) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
            }

            @Override
            public void resetLampStateBrightnessFieldReplyCB(ResponseCode rc, String lampID) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
            }

            @Override
            public void resetLampStateColorTempFieldReplyCB(ResponseCode rc, String lampID) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
            }

            @Override
            public void transitionLampStateToPresetReplyCB(ResponseCode rc, String lampID) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
            }

            @Override
            public void getLampSupportedLanguagesReplyCB(ResponseCode rc, String lampID, String[] supportedLanguages) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
                results.add(supportedLanguages);
            }

            @Override
            public void setLampEffectReplyCB(ResponseCode rc, String lampID, String effectID) {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
                results.add(effectID);
            }

            @Override
            public void getLampFaultsReplyCB(ResponseCode rc, String lampID, long[] faultCodes){
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
                results.add(faultCodes);
            }

;
            @Override
            public void transitionLampStateReplyCB(ResponseCode rc, String lampID)
            {
                results.add((new Object() { public String getName() { return getClass().getEnclosingMethod().getName(); }}).getName());
                results.add(rc);
                results.add(lampID);
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

    private native String getAllLampIDsReplyCB(LampManagerCallback lmcb, ResponseCode rc, String[] lampIDs);
    public void testGetAllLampIDsReplyCB()
    {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String[] lampIDs = new String[] { "LampID-1", "LampID-2", "LampID-3" };

        String method = getAllLampIDsReplyCB(callback, rc, lampIDs);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampIDs}, results.toArray()));
    }

    private native String getLampNameReplyCB(LampManagerCallback lmcb, ResponseCode rc, String lampID, String language, String lampName);
    public void testGetLampNameReplyCB()
    {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampID = "LampID-1";
        String language = "EN";
        String lampName = "LampName-1";

        String method = getLampNameReplyCB(callback, rc, lampID, language, lampName);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID, language, lampName}, results.toArray()));
    }

    private native String setLampNameReplyCB(LampManagerCallback lmcb, ResponseCode rc, String lampID, String language);
    public void testSetLampNameReplyCB()
    {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampID = "LampID-1";
        String language = "EN";

        String method = setLampNameReplyCB(callback, rc, lampID, language);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID, language}, results.toArray()));
    }

    private native String getLampStateHueFieldReplyCB(LampManagerCallback lmcb, ResponseCode rc, String lampID, long hue);
    public void testGetLampStateHueFieldReplyCB()
    {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampID = "LampID-1";
        long hue = 3485993300L;

        String method = getLampStateHueFieldReplyCB(callback, rc, lampID, hue);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID, hue}, results.toArray()));
    }

    private native String getLampManufacturerReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID, String language, String manufacturer);
    public void testGetLampManufacturerReplyCB()
    {
        ResponseCode rc = ResponseCode.ERR_REJECTED;
        String lampID = "LampID-1";
        String language = "lang-1";
        String manufacturer = "manufac-1";

        String method = getLampManufacturerReplyCB(callback, rc, lampID, language, manufacturer);

        assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID, language, manufacturer}, results.toArray()));
    }

    private native String lampsFoundCB(LampManagerCallback lmcb, String[] lampIDs);
    public void testLampsFoundCB()
    {
        String[] lampIDs = new String[] { "LampID-1", "LampID-2", "LampID-3" };

        String method = lampsFoundCB(callback, lampIDs);

        assertTrue(Arrays.deepEquals(new Object[] {method, lampIDs}, results.toArray()));
    }

    private native String lampsLostCB(LampManagerCallback lmcb, String[] lampIDs);
    public void testLampsLostCB()
    {
        String[] lampIDs = new String[] { "LampID-1", "LampID-2", "LampID-3" };

        String method = lampsLostCB(callback, lampIDs);

        assertTrue(Arrays.deepEquals(new Object[] {method, lampIDs}, results.toArray()));
    }

    private native String lampNameChangedCB(LampManagerCallback lmcb, String lampID, String lampName);
    public void testLampNameChangedCB()
    {
        String lampID = "LampID-1";
        String lampName = "LampName-1";

        String method = lampNameChangedCB(callback, lampID, lampName);

        assertTrue(Arrays.deepEquals(new Object[] {method, lampID, lampName}, results.toArray()));
    }

  private native String getLampDetailsReplyCB(LampManagerCallback lmcb, ResponseCode rc, String lampID, LampDetails details);
  public void testGetLampDetailsReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";
      LampDetails details = new LampDetails(); //TODO-MOD Make this actually contain some data

      String method = getLampDetailsReplyCB(callback, rc, lampID, details);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID, details.getMinTemperature()}, results.toArray()));
  }

  private native String getLampParametersReplyCB(LampManagerCallback lmcb, ResponseCode rc, String lampID, LampParameters params);
  public void testGetLampParametersReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";
      LampParameters params = new LampParameters(); //TODO-MOD Make this actually contain some data

      String method = getLampParametersReplyCB(callback, rc, lampID, params);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID, params.getEnergyUsageMilliwatts()}, results.toArray()));
  }

  private native String getLampStateOnOffFieldReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID, boolean onOff);
  public void testGetLampStateOnOffFieldReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";
      boolean onOff = false;

      String method = getLampStateOnOffFieldReplyCB(callback, rc, lampID, onOff);
      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID, onOff}, results.toArray()));
  }

  private native String getLampStateSaturationFieldReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID, long saturation);
  public void testGetLampStateSaturationFieldReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";
      long saturation = 2200000500L;

      String method = getLampStateSaturationFieldReplyCB(callback, rc, lampID, saturation);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID, saturation}, results.toArray()));
  }

  private native String getLampStateBrightnessFieldReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID, long brightness);
  public void testGetLampStateBrightnessFieldReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";
      long brightness = 2200000500L;

      String method = getLampStateBrightnessFieldReplyCB(callback, rc, lampID, brightness);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID, brightness}, results.toArray()));
  }

  private native String getLampStateColorTempFieldReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID, long colorTemp);
  public void testGetLampStateColorTempFieldReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";
      long colorTemp = 3485993300L;

      String method = getLampStateColorTempFieldReplyCB(callback, rc, lampID, colorTemp);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID, colorTemp}, results.toArray()));
  }

  private native String pulseLampWithStateReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID);
  public void testPulseLampWithStateReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";

      String method = pulseLampWithStateReplyCB(callback, rc, lampID);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID}, results.toArray()));
  }

  private native String pulseLampWithPresetReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID);
  public void testPulseLampWithPresetReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";

      String method = pulseLampWithPresetReplyCB(callback, rc, lampID);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID}, results.toArray()));
  }

  private native String transitionLampStateOnOffFieldReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID);
  public void testTransitionLampStateOnOffFieldReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";

      String method = transitionLampStateOnOffFieldReplyCB(callback, rc, lampID);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID}, results.toArray()));
  }

  private native String transitionLampStateHueFieldReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID);
  public void testTransitionLampStateHueFieldReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";

      String method = transitionLampStateHueFieldReplyCB(callback, rc, lampID);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID}, results.toArray()));
  }

  private native String transitionLampStateSaturationFieldReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID);
  public void testTransitionLampStateSaturationFieldReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";

      String method = transitionLampStateSaturationFieldReplyCB(callback, rc, lampID);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID}, results.toArray()));
  }
  private native String transitionLampStateBrightnessFieldReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID);
  public void testTransitionLampStateBrightnessFieldReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";

      String method = transitionLampStateBrightnessFieldReplyCB(callback, rc, lampID);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID}, results.toArray()));
  }

  private native String transitionLampStateColorTempFieldReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID);
  public void testTransitionLampStateColorTempFieldReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";

      String method = transitionLampStateColorTempFieldReplyCB(callback, rc, lampID);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID}, results.toArray()));
  }

  private native String resetLampStateOnOffFieldReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID);
  public void testResetLampStateOnOffFieldReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";

      String method = resetLampStateOnOffFieldReplyCB(callback, rc, lampID);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID}, results.toArray()));
  }

  private native String resetLampStateHueFieldReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID);
  public void testResetLampStateHueFieldReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";

      String method = resetLampStateHueFieldReplyCB(callback, rc, lampID);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID}, results.toArray()));
  }

  private native String resetLampStateSaturationFieldReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID);
  public void testResetLampStateSaturationFieldReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";

      String method = resetLampStateSaturationFieldReplyCB(callback, rc, lampID);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID}, results.toArray()));
  }

  private native String resetLampStateBrightnessFieldReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID);
  public void testResetLampStateBrightnessFieldReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";

      String method = resetLampStateBrightnessFieldReplyCB(callback, rc, lampID);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID}, results.toArray()));
  }

  private native String resetLampStateColorTempFieldReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID);
  public void testResetLampStateColorTempFieldReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";

      String method = resetLampStateColorTempFieldReplyCB(callback, rc, lampID);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID}, results.toArray()));
  }

  private native String transitionLampStateToPresetReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID);
  public void testTransitionLampStateToPresetReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";

      String method = transitionLampStateToPresetReplyCB(callback, rc, lampID);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID}, results.toArray()));
  }

  private native String getLampSupportedLanguagesReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID, String[] supportedLanguages);
  public void testGetLampSupportedLanguagesReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";
      String[] supportedLanguages = new String[] { "lang-1", "lang-2", "lang-3" };

      String method = getLampSupportedLanguagesReplyCB(callback, rc, lampID, supportedLanguages);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID, supportedLanguages}, results.toArray()));
  }

  private native String setLampEffectReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID, String effectID);
  public void testSetLampEffectReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";
      String effectID = "EFFECTID-1";

      String method = setLampEffectReplyCB(callback, rc, lampID, effectID);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID, effectID}, results.toArray()));
  }

  private native String getLampStateReplyCB(LampManagerCallback lmcb, ResponseCode rc, String lampID, LampState state);
  public void testGetLampStateReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";

      LampState state = new LampState();
      state.setColorTemp(150);

      String method = getLampStateReplyCB(callback, rc, lampID, state);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID, state.getColorTemp()}, results.toArray()));
  }

  private native String resetLampStateReplyCB(LampManagerCallback lmcb, ResponseCode rc, String lampID);
  public void testResetLampStateReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";

      String method = resetLampStateReplyCB(callback, rc, lampID);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID}, results.toArray()));
  }

  private native String lampStateChangedCB(LampManagerCallback lmcb, String lampID, LampState lampState);
  public void testLampStateChangedCB()
  {
      String lampID = "LampID-1";
      LampState lampState = new LampState();
      lampState.setColorTemp(150);

      String method = lampStateChangedCB(callback, lampID, lampState);

      assertTrue(Arrays.deepEquals(new Object[] {method, lampID, lampState.getColorTemp()}, results.toArray()));
  }

  private native String transitionLampStateReplyCB(LampManagerCallback lmcb, ResponseCode rc, String lampID);
  public void testTransitionLampStateReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";

      String method = transitionLampStateReplyCB(callback, rc, lampID);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID}, results.toArray()));
  }

  private native String getLampFaultsReplyCB(LampManagerCallback lmcb, ResponseCode rc, String lampID, long[] faultCodes);
  public void testGetLampFaultsReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";
      long faultCode1 = 3485993300L;
      long[] faultCodes = {faultCode1, faultCode1, faultCode1};

      String method = getLampFaultsReplyCB(callback, rc, lampID, faultCodes);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID, faultCodes}, results.toArray()));
  }

  private native String clearLampFaultReplyCB(LampManagerCallback lmcb, ResponseCode rc, String lampID, long faultCode);
  public void testClearLampFaultReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";
      long faultCode = 3485993300L;

      String method = clearLampFaultReplyCB(callback, rc, lampID, faultCode);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID, faultCode}, results.toArray()));
  }

  private native String getLampParametersLumensFieldReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID, long brightnessLumens);
  public void testGetLampParametersLumensFieldReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";
      long brightnessLumens = 789;

      String method = getLampParametersLumensFieldReplyCB(callback, rc, lampID, brightnessLumens);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID, brightnessLumens}, results.toArray()));
  }

  private native String getLampParametersEnergyUsageMilliwattsFieldReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID, long energyUsageMilliwatts);
  public void testGetLampParametersEnergyUsageMilliwattsFieldReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";
      long energyUsageMilliwatts = 5000;

      String method = getLampParametersEnergyUsageMilliwattsFieldReplyCB(callback, rc, lampID, energyUsageMilliwatts);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID, energyUsageMilliwatts}, results.toArray()));
  }

  private native String getLampServiceVersionReplyCB(LampManagerCallback lmcb, ResponseCode responseCode, String lampID, long lampServiceVersion);
  public void testGetLampServiceVersionReplyCB()
  {
      ResponseCode rc = ResponseCode.ERR_REJECTED;
      String lampID = "LampID-1";
      long lampServiceVersion = 789;

      String method = getLampServiceVersionReplyCB(callback, rc, lampID, lampServiceVersion);

      assertTrue(Arrays.deepEquals(new Object[] {method, rc, lampID, lampServiceVersion}, results.toArray()));
  }
}
