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

import org.allseen.lsf.helper.model.ColorItemDataModel;
import org.allseen.lsf.helper.model.ColorStateConverter;
import org.allseen.lsf.helper.model.LightingItemDataModel;

/**
 * Abstract base class for Lighting items that support color.
 * <p>
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public abstract class ColorItem extends LightingItem {

    public void turnOn() {
        setPowerOn(true);
    }

    public void turnOff() {
        setPowerOn(false);
    }

    public void setColor(int[] hsvt) {
        setColor(hsvt[0], hsvt[1], hsvt[2], hsvt[3]);
    }

    public int[] setColor() {
        return ColorStateConverter.convertModelToView(getColorDataModel().state);
    }

    @Override
    protected LightingItemDataModel getItemDataModel() {
        return getColorDataModel();
    }

    public abstract void setPowerOn(boolean powerOn);
    public abstract void setColor(int hueDegrees, int saturationPercent, int brightnessPercent, int colorTempDegrees);

    protected abstract ColorItemDataModel getColorDataModel();
}
