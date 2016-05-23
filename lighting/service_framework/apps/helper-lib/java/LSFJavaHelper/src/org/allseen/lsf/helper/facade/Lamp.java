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
package org.allseen.lsf.helper.facade;

import org.allseen.lsf.LampState;
import org.allseen.lsf.helper.manager.AllJoynManager;
import org.allseen.lsf.helper.model.ColorItemDataModel;
import org.allseen.lsf.helper.model.ColorStateConverter;
import org.allseen.lsf.helper.model.LampDataModel;

/**
 * A Lamp object represents a lamp in a lighting system, and can be used to send commands
 * to it.
 */
public final class Lamp extends ColorItem {

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
    public Lamp(String lampID) {
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
    public Lamp(String lampID, String lampName) {
        super();

        lampModel = new LampDataModel(lampID, lampName);
    }

    /**
     * Sends a command to turn this Lamp on or off.
     *
     * @param powerOn Pass in true for on, false for off
     */
    @Override
    public void setPowerOn(boolean powerOn) {
        AllJoynManager.lampManager.transitionLampStateOnOffField(lampModel.id, powerOn);
    }

    /**
     * Sends a command to change the color of this Lamp.
     *
     * @param hueDegrees The hue component of the desired color, in degrees (0-360)
     * @param saturationPercent The saturation component of the desired color, in percent (0-100)
     * @param brightnessPercent The brightness component of the desired color, in percent (0-100)
     * @param colorTempDegrees The color temperature component of the desired color, in degrees Kelvin (2700-9000)
     */
    @Override
    public void setColor(int hueDegrees, int saturationPercent, int brightnessPercent, int colorTempDegrees) {
        LampState lampState = new LampState();

        lampState.setOnOff(true);

        ColorStateConverter.convertViewToModel(hueDegrees, saturationPercent, brightnessPercent, colorTempDegrees, lampState);

        AllJoynManager.lampManager.transitionLampState(lampModel.id, lampState, 0);
    }

    @Override
    protected ColorItemDataModel getColorDataModel() {
        return getLampDataModel();
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    public LampDataModel getLampDataModel() {
        return lampModel;
    }
}
