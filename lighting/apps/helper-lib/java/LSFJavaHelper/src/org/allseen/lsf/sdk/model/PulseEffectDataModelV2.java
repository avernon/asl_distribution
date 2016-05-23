/*
 * Copyright (c) AllSeen Alliance. All rights reserved.
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
public class PulseEffectDataModelV2 extends ColorItemDataModel {
    public static final char TAG_PREFIX_PULSE = 'E';

    public static String defaultName = "<Loading pulse effect info...>";
    public static long defaultPeriod = 1000;
    public static long defaultDuration = 500;
    public static long defaultCount = 10;

    private LampState endState;
    private String startPresetID;
    private String endPresetID;
    private long period;
    private long duration;
    private long count;
    private boolean startWithCurrent;

    protected boolean endStateInitialized;
    protected boolean periodInitialized;
    protected boolean durationInitialized;
    protected boolean countInitialized;

    public PulseEffectDataModelV2() {
        this((String)null);
    }

    public PulseEffectDataModelV2(String pulseEffectID) {
        this(pulseEffectID, null);
    }

    public PulseEffectDataModelV2(String pulseEffectID, String pulseEffectName) {
        super(pulseEffectID, TAG_PREFIX_PULSE, pulseEffectName != null ? pulseEffectName : defaultName);

        endState = null;
        startPresetID = null;
        endPresetID = null;
        period = defaultPeriod;
        duration = defaultDuration;
        count = defaultCount;
        startWithCurrent = false;

        endStateInitialized = false;
        periodInitialized = false;
        durationInitialized = false;
        countInitialized = false;
    }

    public PulseEffectDataModelV2(PulseEffectDataModelV2 other) {
        super(other);

        setCapability(LampCapabilities.allCapabilities);

        LampState otherEndState = other.getEndState();
        if (otherEndState != null) {
            endState = new LampState(otherEndState);
        } else {
            endState = null;
        }

        startPresetID = other.startPresetID;
        endPresetID = other.endPresetID;
        period = other.period;
        duration = other.duration;
        count = other.count;
        startWithCurrent = other.startWithCurrent;

        endStateInitialized = other.endStateInitialized;
        periodInitialized = other.periodInitialized;
        durationInitialized = other.durationInitialized;
        countInitialized = other.countInitialized;
    }

    public LampState getEndState() {
        return endState;
    }

    public void setEndState(LampState state) {
        endState = state;
        endStateInitialized = true;
    }

    public String getStartPresetID() {
        return startPresetID;
    }

    public void setStartPresetID(String presetID) {
        startPresetID = presetID;
        // start preset/state share same flag since only one field should be set
        stateInitialized = true;
    }

    public String getEndPresetID() {
        return endPresetID;
    }

    public void setEndPresetID(String endPresetID) {
        this.endPresetID = endPresetID;
        // end preset/state share same flag since only one field should be set
        endStateInitialized = true;
    }

    public long getPeriod() {
        return period;
    }

    public void setPeriod(long period) {
        this.period = period;
        periodInitialized = true;
    }

    public long getDuration() {
        return duration;
    }

    public void setDuration(long duration) {
        this.duration = duration;
        durationInitialized = true;
    }

    public long getCount() {
        return count;
    }

    public void setCount(long count) {
        this.count = count;
        countInitialized = true;
    }

    public boolean isStartWithCurrent() {
        return startWithCurrent;
    }

    public void setStartWithCurrent(boolean startWithCurrent) {
        this.startWithCurrent = startWithCurrent;
    }

    public boolean containsPreset(String presetID) {
        return presetID.equals(startPresetID) || presetID.equals(endPresetID);
    }

    @Override
    public boolean isInitialized() {
        return super.isInitialized() && stateInitialized && endStateInitialized &&
                periodInitialized && durationInitialized && countInitialized;
    }
}
