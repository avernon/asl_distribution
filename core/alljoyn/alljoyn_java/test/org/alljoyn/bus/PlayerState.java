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
import org.alljoyn.bus.annotation.BusSignal;

/**
 * PlayerState contains the state information of a single player for a fictitional
 * multi-player game. In this game, each player periodially and continuously
 * broadcasts his state to all the other players of the game using signals.
 */
@BusInterface
public interface PlayerState {

    /**
     * Player position information signal. (frequently sent)
     *
     * @param x         X position of character
     * @param y         Y position of character
     * @param rotation  360 rototation of character
     */
    @BusSignal(name="PlayerPosition", signature="uuu")
    public void playerPosition(int x,
                               int y,
                               int rotation) throws BusException;
}

