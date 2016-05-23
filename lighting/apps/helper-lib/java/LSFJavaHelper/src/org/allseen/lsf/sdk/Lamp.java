/* Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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
package org.allseen.lsf.sdk;

import java.util.Collection;

import org.allseen.lsf.LampState;
import org.allseen.lsf.sdk.manager.AllJoynManager;
import org.allseen.lsf.sdk.model.ColorItemDataModel;
import org.allseen.lsf.sdk.model.ColorStateConverter;
import org.allseen.lsf.sdk.model.EmptyLampDetails;
import org.allseen.lsf.sdk.model.EmptyLampParameters;
import org.allseen.lsf.sdk.model.LampDataModel;

/**
 * This class represents a Lamp that is connected to the lighting controller. This class
 * provides an interface to perform Lamp operations. Supported operations include changing
 * color and power state, renaming, applying effects and presets, and retrieving lamp data.
 * Lamps are considered fully initialized when the name, power and color state, and lamp
 * details have been received. Lamps are still operational even in the uninitialized state.
 * <p>
 * <b>Note: This class is not meant to be instantiated directly. Lamps should be retrieved
 * from the LightingDirector using the {@link LightingDirector#getLamps()} method.</b>
 */
public class Lamp extends GroupMember {
    /**
     * Specifies the default name of the Lamp.
     *
     * @param defaultName Default name of the Lamp
     */
    public static void setDefaultName(String defaultName) {
        if (defaultName != null) {
            LampDataModel.defaultName = defaultName;
        }
    }

    protected LampDataModel lampModel;

    /**
     * Constructs a Lamp using the specified ID.
     * <p>
     * <b>WARNING: This method is intended to be used internally. Client software should not instantiate
     * Lamps directly, but should instead get them from the {@link LightingDirector} using the
     * {@link LightingDirector#getLamps()} method.</b>
     *
     * @param lampID The ID of the lamp
     */
    protected Lamp(String lampID) {
        this(lampID, null);
    }

    /**
     * Constructs a Lamp using the specified ID and name.
     * <p>
     * <b>WARNING: This method is intended to be used internally. Client software should not instantiate
     * Lamps directly, but should instead get them from the {@link LightingDirector} using the
     * {@link LightingDirector#getLamps()} method.</b>
     *
     * @param lampID The ID of the lamp
     * @param lampName The name of the lamp
     */
    protected Lamp(String lampID, String lampName) {
        super();

        lampModel = new LampDataModel(lampID, lampName);
    }

    /**
     * Applies the provided Preset to the current Lamp.
     *
     * @param preset Preset to apply to the current Lamp
     */
    @Override
    public void applyPreset(Preset preset) {
        String errorContext = "Lamp.applyPreset error";

        if (postInvalidArgIfNull(errorContext, preset)) {
            postErrorIfFailure(errorContext,
                    AllJoynManager.lampManager.transitionLampStateToPreset(lampModel.id, preset.getPresetDataModel().id, 0));
        }
    }

    /**
     * Applies the provided Effect to the current Lamp.
     *
     * @param effect Effect to apply to the current Lamp
     */
    @Override
    public void applyEffect(Effect effect) {
        String errorContext = "Lamp.applyEffect() error";

        if (postInvalidArgIfNull(errorContext, effect)) {
            if (effect instanceof Preset) {
                applyPreset((Preset) effect);
            } else if (effect instanceof TransitionEffect) {
                postErrorIfFailure(errorContext,
                        AllJoynManager.transitionEffectManager.applyTransitionEffectOnLamps(effect.getId(), new String[] { lampModel.id }));
            } else if (effect instanceof PulseEffect) {
                postErrorIfFailure(errorContext,
                        AllJoynManager.pulseEffectManager.applyPulseEffectOnLamps(effect.getId(), new String[] { lampModel.id }));
            }
        }
    }

    /**
     * Changes the power state of the current Lamp.
     *
     * @param powerOn True for on, false for off
     */
    @Override
    public void setPowerOn(boolean powerOn) {
        String errorContext = "Lamp.setPowerOn() error";

        postErrorIfFailure(errorContext,
                AllJoynManager.lampManager.transitionLampStateOnOffField(lampModel.id, powerOn));
    }

    /**
     * Changes the color state of the current Lamp to the provided HSVT color.
     * <p>
     * <b>Note: If the provided HSVT values are outside the expected range, they will be normalized to the
     * expected range</b>
     *
     * @param hueDegrees The hue component of the desired color (0-360)
     * @param saturationPercent The saturation component of the desired color (0-100)
     * @param brightnessPercent The brightness component of the desired color (0-100)
     * @param colorTempDegrees The color temperature component of the desired color (1000-20000)
     */
    @Override
    public void setColorHsvt(int hueDegrees, int saturationPercent, int brightnessPercent, int colorTempDegrees) {
        LampState lampState = new LampState(lampModel.getState());

        ColorStateConverter.convertViewToModel(hueDegrees, saturationPercent, brightnessPercent, colorTempDegrees, lampState);

        String errorContext = "Lamp.setColorHsvt() error";

        postErrorIfFailure(errorContext,
                AllJoynManager.lampManager.transitionLampState(lampModel.id, lampState, 0));
    }

    /**
     * Changes the color state of the current Lamp to the provided hue.
     * <p>
     * <b>Note: If the provided hue values are outside the expected range, they will be normalized to the
     * expected range</b>
     *
     * @param hueDegrees The hue component of the desired color (0-360)
     */
    @Override
    public void setHue(int hueDegrees) {
        String errorContext = "Lamp.setHue() error";

        long scaledHue = ColorStateConverter.convertHueViewToModel(hueDegrees);

        postErrorIfFailure(errorContext,
                AllJoynManager.lampManager.transitionLampStateHueField(lampModel.id, scaledHue, 0));
    }

    /**
     * Changes the color state of the current Lamp to the provided saturation.
     * <p>
     * <b>Note: If the provided saturation values are outside the expected range, they will be normalized to the
     * expected range</b>
     *
     * @param saturationPercent The saturation component of the desired color (0-100)
     */
    @Override
    public  void setSaturation(int saturationPercent) {
        String errorContext = "Lamp.setSaturation() error";

        long scaledSaturation = ColorStateConverter.convertSaturationViewToModel(saturationPercent);

        postErrorIfFailure(errorContext,
                AllJoynManager.lampManager.transitionLampStateSaturationField(lampModel.id, scaledSaturation, 0));
    }

    /**
     * Changes the color state of the current Lamp to the provided brightness.
     * <p>
     * <b>Note: If the provided brightness values are outside the expected range, they will be normalized to the
     * expected range</b>
     *
     * @param brightnessPercent The brightness component of the desired color (0-100)
     */
    @Override
    public  void setBrightness(int brightnessPercent) {
        String errorContext = "Lamp.setBrightness() error";

        long scaledBrightness = ColorStateConverter.convertBrightnessViewToModel(brightnessPercent);

        postErrorIfFailure(errorContext,
                AllJoynManager.lampManager.transitionLampStateBrightnessField(lampModel.id, scaledBrightness, 0));
    }

    /**
     * Changes the color state of the current Lamp to the provided color temperature.
     * <p>
     * <b>Note: If the provided color temperature values are outside the expected range, they will be normalized to the
     * expected range</b>
     *
     * @param colorTempDegrees The color temperature component of the desired color (1000-20000)
     */
    @Override
    public  void setColorTemperature(int colorTempDegrees) {
        String errorContext = "Lamp.setColorTemp() error";

        long scaledColorTemp = ColorStateConverter.convertColorTempViewToModel(colorTempDegrees);

        postErrorIfFailure(errorContext,
                AllJoynManager.lampManager.transitionLampStateColorTempField(lampModel.id, scaledColorTemp, 0));
    }

    /**
     * Renames the current Lamp using the provided name.
     *
     * @param lampName The new name for the Lamp
     */
    @Override
    public void rename(String lampName) {
        String errorContext = "Lamp.rename() error";

        if (postInvalidArgIfNull(errorContext, lampName)) {
            postErrorIfFailure(errorContext,
                    AllJoynManager.lampManager.setLampName(lampModel.id, lampName, LightingDirector.get().getDefaultLanguage()));
        }
    }

    /**
     * Returns the Lamp AllJoyn about data for the current Lamp.
     *
     * @return Reference to LampAbout object
     */
    public LampAbout getAbout() {
        return new LampAbout(lampModel.getAbout());
    }

    /**
     * Returns the LampDetails for the current Lamp.
     *
     * @return Reference to LampDetails object
     */
    public LampDetails getDetails() {
        LampDetails lampDetails = lampModel.getDetails();

        return lampDetails != null ? lampDetails : EmptyLampDetails.instance;
    }

    /**
     * Returns the LampParameters for the current Lamp.
     *
     * @return Reference to LampParameters object
     */
    public LampParameters getParameters() {
        LampParameters lampParams = lampModel.getParameters();

        return lampParams != null ? lampParams : EmptyLampParameters.instance;
    }

    /**
     * Returns the minimum color temperature value supported by the current Lamp.
     *
     * @return The Lamps minimum color temperature value
     */
    public int getColorTempMin() {
        return getDetails().getMinTemperature();
    }

    /**
     * Returns the maximum color temperature value supported by the current Lamp.
     *
     * @return The Lamps maximum color temperature value
     */
    public int getColorTempMax() {
        return getDetails().getMaxTemperature();
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected void addTo(Collection<String> lampIDs, Collection<String> groupIDs) {
        lampIDs.add(getId());
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected ColorItemDataModel getColorDataModel() {
        return getLampDataModel();
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected LampDataModel getLampDataModel() {
        return lampModel;
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected void postError(final String name, final ResponseCode status) {
        LightingDirector.get().getLightingSystemManager().getQueue().post(new Runnable() {
            @Override
            public void run() {
                LightingDirector.get().getLampCollectionManager().sendErrorEvent(name, status, getId());
            }
        });
    }
}
