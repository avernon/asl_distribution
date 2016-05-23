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

public class ColorAverager {

    protected long sum;
    protected long count;
    protected long initial;
    protected boolean uniform;

    public ColorAverager() {
        super();
        reset();
    }

    public void reset() {
        sum = 0;
        count = 0;
        initial = -1;
        uniform = true;
    }

    public void add(long value) {
        sum += value;
        count++;

        if (initial < 0) {
            initial = value;
        } else if (uniform) {
            uniform = (value == initial);
        }
    }

    public long getSum() {
        return sum;
    }

    public long getCount() {
        return count;
    }

    public long getAverage() {
        double divisor = count > 0 ? count : 1.0;

        return Math.round(sum / divisor);
    }

    public boolean isUniform() {
        return uniform;
    }
}
