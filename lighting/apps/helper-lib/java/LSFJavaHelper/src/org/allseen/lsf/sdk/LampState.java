/* Copyright AllSeen Alliance. All rights reserved.
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
 * Provides an interface for developers to implement and create their own LampState object.
 */
public interface LampState {

    /**
     * Returns the power state of the LampState object.
     *
     * @return Returns true if the power is on, false otherwise
     */
    public boolean getPowerOn();

    /**
     * Sets the power state of the LampState object.
     *
     * @param powerOn Specifies the power state
     */
    public void setPowerOn(boolean powerOn);

    /**
     * Returns the HSVT color of the LampState object
     *
     * @return Integer array containing the HSVT color
     */
    public int[] getColorHsvt();

    /**
     * Sets the color of the LampState object using the provided values.
     * <p>
     * <b>Note: If the provided HSVT values are outside the expected range, they will be normalized to the
     * expected range</b>
     *
     * @param hueDegrees The hue component of the desired color (0-360)
     * @param saturationPercent The saturation component of the desired color (0-100)
     * @param brightnessPercent The brightness component of the desired color (0-100)
     * @param colorTempDegrees The color temperature component of the desired color (1000-20000)
     */
    public void setColorHsvt(int hueDegrees, int saturationPercent, int brightnessPercent, int colorTempDegrees);
}
