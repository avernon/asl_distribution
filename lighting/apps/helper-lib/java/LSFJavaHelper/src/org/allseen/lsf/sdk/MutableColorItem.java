/* Copyright (c) AllSeen Alliance. All rights reserved.
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

/**
 * Abstract base class for Lighting items that support modification of power and color state.
 */
public abstract class MutableColorItem extends ColorItem implements LampState {

    /**
     * Sets the Power of the Lighting item to on.
     */
    public void turnOn() {
        setPowerOn(true);
    }

    /**
     * Sets the Power of the Lighting item to off.
     */
    public void turnOff() {
        setPowerOn(false);
    }

    /**
     * Sets the color of the Lighting item to the provided HSVT color.
     * <p>
     * <b>Note: If the provided HSVT values are outside the expected range, they will be normalized to the
     * expected range</b>
     *
     * @param hsvt Array of HSVT values
     */
    public void setColorHsvt(int[] hsvt) {
        String errorContext = "MutableColorItem.setColorHsvt() error";

        if (postInvalidArgIfNull(errorContext, hsvt)) {
            if (hsvt.length != 4) {
                postInvalidArgIfNull(errorContext, null);
            } else {
                setColorHsvt(hsvt[0], hsvt[1], hsvt[2], hsvt[3]);
            }
        }
    }

    /**
     * Toggles the power state of the Lighting item.
     */
    public void togglePower() {
        setPowerOn(isOff());
    }

    /**
     * Sets the Power state of the Lighting item.
     *
     * @param power The desired Power state
     */
    public void setPower(Power power) {
        setPowerOn(power == Power.ON);
    }

    /**
     * Sets the color of the Lighting item to the provided HSVT color.
     *
     * @param color The desired Color
     */
    public void setColor(Color color) {
        String errorContext = "MutableColorItem.setColor() error";

        if (postInvalidArgIfNull(errorContext, color)) {
            setColorHsvt(color.getHue(), color.getSaturation(), color.getBrightness(), color.getColorTemperature());
        }
    }

    /**
     * Changes the power state of the current Group.
     *
     * @param powerOn True for on, false for off
     */
    @Override
    public abstract void setPowerOn(boolean powerOn);

    /**
     * Changes the color state of the current Group to the provided HSVT color.
     *
     * @param hueDegrees The hue component of the desired color (0-360)
     * @param saturationPercent The saturation component of the desired color (0-100)
     * @param brightnessPercent The brightness component of the desired color (0-100)
     * @param colorTempDegrees The color temperature component of the desired color (1000-20000)
     */
    @Override
    public abstract void setColorHsvt(int hueDegrees, int saturationPercent, int brightnessPercent, int colorTempDegrees);

    /**
     * Changes the color state of the current Item to the provided hue.
     *
     * @param hueDegrees The hue component of the desired color (0-360)
     */
    public abstract void setHue(int hueDegrees);

    /**
     * Changes the color state of the current Item to the provided saturation.
     *
     * @param saturationPercent The saturation component of the desired color (0-100)
     */
    public abstract void setSaturation(int saturationPercent);

    /**
     * Changes the color state of the current Item to the provided brightness.
     *
     * @param brightnessPercent The brightness component of the desired color (0-100)
     */
    public abstract void setBrightness(int brightnessPercent);

    /**
     * Changes the color state of the current Item to the provided color temperature.
     *
     * @param colorTempDegrees The color temperature component of the desired color (1000-20000)
     */
    public abstract void setColorTemperature(int colorTempDegrees);
}
