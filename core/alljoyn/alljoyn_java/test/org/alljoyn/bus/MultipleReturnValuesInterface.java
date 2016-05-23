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

package org.alljoyn.bus;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.Position;

import java.util.Arrays;
import java.util.Map;

@BusInterface
public interface MultipleReturnValuesInterface {

    public class Values {
        public static class Inner {
            @Position(0) public int x;
            public boolean equals(Object obj) {
                return x == ((Inner)obj).x;
            }
        }
        @Position(0) public int a;
        @Position(1) public int b;
        @Position(2) public Map<String, String> c;
        @Position(3) public Map<String, String>[] d;
        @Position(4) public long[] e;
        @Position(5) public Inner f;
        public boolean equals(Object obj) {
            Values v = (Values)obj;
            return a == v.a &&
                b == v.b &&
                c.equals(v.c) &&
                Arrays.equals(d, v.d) &&
                Arrays.equals(e, v.e) &&
                f.equals(v.f);
        }
    }

    @BusMethod(name="Method", replySignature="iia{ss}aa{ss}ax(i)")
    public Values method() throws BusException;
}
