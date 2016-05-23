/*
 * Copyright AllSeen Alliance. All rights reserved.
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
package org.allseen.lsf.sdk.model;

import org.allseen.lsf.LampState;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class ColorStateConverter {
    public static final long UINT32_MAX = 0xffffffffL;
    public static final int VIEW_HUE_MIN = 0;
    public static final int VIEW_HUE_MAX = 360;
    public static final int VIEW_HUE_SPAN = VIEW_HUE_MAX - VIEW_HUE_MIN;
    public static final int VIEW_SATURATION_MIN = 0;
    public static final int VIEW_SATURATION_MAX = 100;
    public static final int VIEW_SATURATION_SPAN = VIEW_SATURATION_MAX - VIEW_SATURATION_MIN;
    public static final int VIEW_BRIGHTNESS_MIN = 0;
    public static final int VIEW_BRIGHTNESS_MAX = 100;
    public static final int VIEW_BRIGHTNESS_SPAN = VIEW_BRIGHTNESS_MAX - VIEW_BRIGHTNESS_MIN;
    public static final int VIEW_COLORTEMP_MIN = 1000;
    public static final int VIEW_COLORTEMP_MAX = 20000;
    public static final int VIEW_COLORTEMP_SPAN = VIEW_COLORTEMP_MAX - VIEW_COLORTEMP_MIN;

    public static int convertHueModelToView(long modelHue) {
        return convertModelToView(modelHue, VIEW_HUE_MIN, VIEW_HUE_SPAN);
    }

    public static long convertHueViewToModel(int viewHue) {
        return convertViewToModel(viewHue, VIEW_HUE_MIN, VIEW_HUE_SPAN);
    }

    public static int convertSaturationModelToView(long modelSaturation) {
        return convertModelToView(modelSaturation, VIEW_SATURATION_MIN, VIEW_SATURATION_SPAN);
    }

    public static long convertSaturationViewToModel(int viewSaturation) {
        return convertViewToModel(viewSaturation, VIEW_SATURATION_MIN, VIEW_SATURATION_SPAN);
    }

    public static int convertBrightnessModelToView(LampState lampState) {
        return convertBrightnessModelToView(lampState.getBrightness());
    }

    public static int convertBrightnessModelToView(long modelBrightness) {
        return convertModelToView(modelBrightness, VIEW_BRIGHTNESS_MIN, VIEW_BRIGHTNESS_SPAN);
    }

    public static void convertBrightnessViewToModel(int viewBrightness, LampState lampState) {
        lampState.setBrightness(convertBrightnessViewToModel(viewBrightness));
    }

    public static long convertBrightnessViewToModel(int viewBrightness) {
        return convertViewToModel(viewBrightness, VIEW_BRIGHTNESS_MIN, VIEW_BRIGHTNESS_SPAN);
    }

    public static int convertColorTempModelToView(long modelColorTemp) {
        return convertModelToView(modelColorTemp, VIEW_COLORTEMP_MIN, VIEW_COLORTEMP_SPAN);
    }

    public static long convertColorTempViewToModel(int viewColorTemp) {
        return convertViewToModel(viewColorTemp, VIEW_COLORTEMP_MIN, VIEW_COLORTEMP_SPAN);
    }

    public static int[] convertModelToView(LampState lampState) {
        int viewHue = convertHueModelToView(lampState.getHue());
        int viewSaturation = convertSaturationModelToView(lampState.getSaturation());
        int viewBrightness = convertBrightnessModelToView(lampState.getBrightness());
        int viewColorTemp = convertColorTempModelToView(lampState.getColorTemp());

        return new int[] {viewHue, viewSaturation, viewBrightness, viewColorTemp};
    }

    public static void convertViewToModel(int viewHue, int viewSaturation, int viewBrightness, int viewColorTemp, LampState lampState) {
        lampState.setHue(convertHueViewToModel(boundHueView(viewHue)));
        lampState.setSaturation(convertSaturationViewToModel(boundSaturationView(viewSaturation)));
        lampState.setBrightness(convertBrightnessViewToModel(boundBrightnessView(viewBrightness)));
        lampState.setColorTemp(convertColorTempViewToModel(boundColorTempView(viewColorTemp)));
    }

    public static float[] convertModelToHSV(LampState lampState) {
        int viewHue = convertHueModelToView(lampState.getHue());
        int viewSaturation = convertSaturationModelToView(lampState.getSaturation());
        int viewBrightness = convertBrightnessModelToView(lampState.getBrightness());

        return new float[] {viewHue, (float) (viewSaturation / 100.0), (float) (viewBrightness / 100.0)};
    }

    public static int boundHueView(int viewHue) {
        return boundValue(viewHue, VIEW_HUE_MIN, VIEW_HUE_MAX);
    }

    public static int boundSaturationView(int viewSaturation) {
        return boundValue(viewSaturation, VIEW_SATURATION_MIN, VIEW_SATURATION_MAX);
    }

    public static int boundBrightnessView(int viewBrightness) {
        return boundValue(viewBrightness, VIEW_BRIGHTNESS_MIN, VIEW_BRIGHTNESS_MAX);
    }

    public static int boundColorTempView(int viewColorTemp) {
        return boundValue(viewColorTemp, VIEW_COLORTEMP_MIN, VIEW_COLORTEMP_MAX);
    }

    protected static int convertModelToView(long modelValue, int min, int span) {
        return min + (int)Math.round((modelValue / (double)UINT32_MAX) * span);
    }

    protected static long convertViewToModel(int viewValue, int min, int span) {
        return Math.round(((double)(viewValue - min) / (double)span) * UINT32_MAX);
    }

    private static int boundValue(int value, int min, int max) {
        return Math.max(Math.min(value, max), min);
    }
}