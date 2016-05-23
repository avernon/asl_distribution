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

package org.allseen.lsf;

public class LampState extends DefaultNativeClassWrapper {
	public LampState() {
		createNativeObject();
	}

	public LampState(LampState other) {
		this();

		this.setOnOff(other.getOnOff());
		this.setHue(other.getHue());
		this.setSaturation(other.getSaturation());
		this.setBrightness(other.getBrightness());
		this.setColorTemp(other.getColorTemp());

		// The setNull() call currently needs to be last due to the side
		// effects of the other setXXX() calls.
		this.setNull(other.isNull());
	}

    //TODO-FIX The get*() methods returning primitives should return their
    //         Object equivalent so that we can return NULL on failure
    public native void setOnOff(boolean onOff);
    public native boolean getOnOff();

    public native void setHue(long hue);
    public native long getHue();

    public native void setSaturation(long saturation);
    public native long getSaturation();

    public native void setColorTemp(long colorTemp);
    public native long getColorTemp();

    public native void setBrightness(long brightness);
    public native long getBrightness();

    protected native void setNull(boolean isNull);
    public native boolean isNull();

	@Override
	protected native void createNativeObject();

	@Override
	protected native void destroyNativeObject();
}

