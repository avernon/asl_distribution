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
package org.allseen.lsf.sdk.model;

import org.allseen.lsf.sdk.LampDetails;
import org.allseen.lsf.sdk.LampParameters;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class LampDataModel extends ColorItemDataModel {
    public static final char TAG_PREFIX_LAMP = 'L';

    public static String defaultName = "<Loading lamp info...>";

    protected boolean detailsInitialized;

    private LampDetails details;
    private LampParameters parameters;
    private LampAbout about;

    public LampDataModel(String lampID) {
        this(lampID, null);
    }

    public LampDataModel(String lampID, String lampName) {
        super(lampID, TAG_PREFIX_LAMP, lampName != null ? lampName : defaultName);

        details = new LampDetails();
        parameters = new LampParameters();
        about = new LampAbout();

        detailsInitialized = false;
    }

    public void setDetails(LampDetails details) {
        this.details = details;
        setCapability(new LampCapabilities(details.isDimmable(), details.hasColor(), details.hasVariableColorTemp()));
        detailsInitialized = true;
    }

    public void setParameters(LampParameters parameters) {
        this.parameters = parameters;
    }

    public void setAbout(LampAbout about) {
        this.about = about;
    }

    public LampDetails getDetails() {
        return details;
    }

    public LampParameters getParameters() {
        return parameters;
    }

    public LampAbout getAbout() {
        return about;
    }

    @Override
    public boolean isInitialized() {
        return super.isInitialized() && detailsInitialized;
    }
}
