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
package org.allseen.lsf.sampleapp;

import org.allseen.lsf.sdk.Lamp;
import org.allseen.lsf.sdk.LampAbout;
import org.allseen.lsf.sdk.LampDetails;
import org.allseen.lsf.sdk.LampMake;
import org.allseen.lsf.sdk.LightingDirector;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;
import android.view.ViewGroup;

public class LampDetailsFragment extends PageFrameChildFragment {

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        view = inflater.inflate(R.layout.fragment_lamp_details, container, false);

        Lamp lamp = LightingDirector.get().getLamp(key);

        if (view != null) {
            updateDetailFields(lamp);
        }

        return view;
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        ((SampleAppActivity)getActivity()).updateActionBar(R.string.title_lamp_details, false, false, false, false, true);
    }

    public void updateDetailFields(Lamp lamp) {
        LampDetails lampDetails = lamp != null ? lamp.getDetails() : null;
        LampMake lampMake = lampDetails != null ? lampDetails.getMake() : null;
        String lampMakeName = lampMake != null ? lampMake.name() : null;

        if ("OEM1".equals(lampMakeName)) {
            lampMakeName = "Qualcomm Technologies, Inc.";
        }

        setTextViewValue(view, R.id.lampDetailsTextMake, lampMakeName, 0);
        setTextViewValue(view, R.id.lampDetailsTextModel, lampDetails != null ? lampDetails.getModel() : null, 0);
        setTextViewValue(view, R.id.lampDetailsTextDevice, lampDetails != null ? lampDetails.getType() : null, 0);
        setTextViewValue(view, R.id.lampDetailsTextLamp, lampDetails != null ? lampDetails.getLampType() : null, 0);
        setTextViewValue(view, R.id.lampDetailsTextBase, lampDetails != null ? lampDetails.getLampBaseType() : null, 0);
        setTextViewValue(view, R.id.lampDetailsTextBeam, lampDetails != null ? lampDetails.getLampBeamAngle() : 0, 0);

        setTextViewValue(view, R.id.lampDetailsTextDimmable, lampDetails != null ? lampDetails.isDimmable() : false, 0);
        setTextViewValue(view, R.id.lampDetailsTextHasColor, lampDetails != null ? lampDetails.hasColor() : false, 0);
        setTextViewValue(view, R.id.lampDetailsTextHasTemp, lampDetails != null ? lampDetails.hasVariableColorTemp() : false, 0);
        setTextViewValue(view, R.id.lampDetailsTextHasEffects, lampDetails != null ? lampDetails.hasEffects() : false, 0);

        setTextViewValue(view, R.id.lampDetailsTextVoltageMin, lampDetails != null ? lampDetails.getMinVoltage() : 0, R.string.units_volts);
        setTextViewValue(view, R.id.lampDetailsTextVoltageMax, lampDetails != null ? lampDetails.getMaxVoltage() : 0, R.string.units_volts);
        setTextViewValue(view, R.id.lampDetailsTextWattageActual, lampDetails != null ? lampDetails.getWattage() : 0, R.string.units_watts);
        setTextViewValue(view, R.id.lampDetailsTextWattageEquiv, lampDetails != null ? lampDetails.getIncandescentEquivalent() : 0, R.string.units_watts);
        setTextViewValue(view, R.id.lampDetailsTextLumens, lampDetails != null ? lampDetails.getMaxLumens() : 0, 0);
        setTextViewValue(view, R.id.lampDetailsTextTempMin, lampDetails != null ? lampDetails.getMinTemperature() : LightingDirector.COLORTEMP_MIN, R.string.units_kelvin);
        setTextViewValue(view, R.id.lampDetailsTextTempMax, lampDetails != null ? lampDetails.getMaxTemperature() : LightingDirector.COLORTEMP_MAX, R.string.units_kelvin);

        if (lamp != null) {
            LampAbout lampAbout = lamp.getAbout();

	        setTextViewValue(view, R.id.lampAboutTextDeviceID, lampAbout.aboutDeviceID, 0);
	        setTextViewValue(view, R.id.lampAboutTextAppID, lampAbout.aboutAppID, 0);
	        setTextViewValue(view, R.id.lampAboutTextDeviceName, lampAbout.aboutDeviceName, 0);
	        setTextViewValue(view, R.id.lampAboutTextDefaultLang, lampAbout.aboutDefaultLanguage, 0);
	        setTextViewValue(view, R.id.lampAboutTextAppName, lampAbout.aboutAppName, 0);
	        setTextViewValue(view, R.id.lampAboutTextDescription, lampAbout.aboutDescription, 0);
	        setTextViewValue(view, R.id.lampAboutTextManufacturer, lampAbout.aboutManufacturer, 0);
	        setTextViewValue(view, R.id.lampAboutTextModel, lampAbout.aboutModelNumber, 0);
	        setTextViewValue(view, R.id.lampAboutTextDate, lampAbout.aboutDateOfManufacture, 0);
	        setTextViewValue(view, R.id.lampAboutTextSoftVer, lampAbout.aboutSoftwareVersion, 0);
	        setTextViewValue(view, R.id.lampAboutTextHardVer, lampAbout.aboutHardwareVersion, 0);
	        setTextViewValue(view, R.id.lampAboutTextSuppoerUrl, lampAbout.aboutSupportUrl, 0);
        }
    }
}
