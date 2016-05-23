/*******************************************************************************
 *  Copyright AllSeen Alliance. All rights reserved.
 *
 *     Contributed by Qualcomm Connected Experiences, Inc.,
 *     with authorization from the AllSeen Alliance, Inc.
 *     
 *     Licensed under the Apache License, Version 2.0 (the "License");
 *     you may not use this file except in compliance with the License.
 *     You may obtain a copy of the License at
 *     
 *         http://www.apache.org/licenses/LICENSE-2.0
 *     
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 *     
 *     Pursuant to Section 1 of the License, the work of authorship constituting
 *     a Work and any Contribution incorporated in the Work shall mean only that
 *     Contributor's code submissions authored by that Contributor.  Any rights
 *     granted under the License are conditioned upon acceptance of these
 *     clarifications.
 *******************************************************************************/
package org.alljoyn.validation.testing.utils.services;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

import org.alljoyn.services.android.security.SrpAnonymousKeyListener;
import org.alljoyn.validation.testing.utils.MyRobolectricTestRunner;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.annotation.Config;

@RunWith(MyRobolectricTestRunner.class)
@Config(manifest = Config.NONE)
public class AuthPasswordHandlerImplTest
{

    private AuthPasswordHandlerImpl authPasswordHandlerImpl;
    private PasswordStore mockPasswordStore;
    private String authPeer = "authPeer";
    private String mechanism = "mechanism";

    @Before
    public void setup() throws Exception
    {
        mockPasswordStore = mock(PasswordStore.class);
        authPasswordHandlerImpl = new AuthPasswordHandlerImpl(mockPasswordStore);
    }

    @Test
    public void testCompletedAuthenticated() throws Exception
    {
        assertFalse(authPasswordHandlerImpl.isPeerAuthenticationSuccessful(authPeer));
        assertFalse(authPasswordHandlerImpl.isPeerAuthenticated(authPeer));

        authPasswordHandlerImpl.completed(mechanism, authPeer, true);
        assertTrue(authPasswordHandlerImpl.isPeerAuthenticated(authPeer));
        assertTrue(authPasswordHandlerImpl.isPeerAuthenticationSuccessful(authPeer));
    }

    @Test
    public void testCompletedNotAuthenticated() throws Exception
    {
        authPasswordHandlerImpl.completed(mechanism, authPeer, false);
        assertFalse(authPasswordHandlerImpl.isPeerAuthenticationSuccessful(authPeer));
        assertTrue(authPasswordHandlerImpl.isPeerAuthenticated(authPeer));
    }

    @Test
    public void testResetAuthentication() throws Exception
    {
        authPasswordHandlerImpl.completed(mechanism, authPeer, true);
        assertTrue(authPasswordHandlerImpl.isPeerAuthenticated(authPeer));
        assertTrue(authPasswordHandlerImpl.isPeerAuthenticationSuccessful(authPeer));
        authPasswordHandlerImpl.resetAuthentication(authPeer);
        assertFalse(authPasswordHandlerImpl.isPeerAuthenticated(authPeer));
        assertFalse(authPasswordHandlerImpl.isPeerAuthenticationSuccessful(authPeer));
    }

    @Test
    public void testGetPassword() throws Exception
    {
        char[] currentPassword = "111111".toCharArray();
        when(mockPasswordStore.getPassword(authPeer)).thenReturn(currentPassword);

        assertEquals(currentPassword, authPasswordHandlerImpl.getPassword(authPeer));
    }

    @Test
    public void testGetPasswordWhenNull() throws Exception
    {
        when(mockPasswordStore.getPassword(authPeer)).thenReturn(null);

        assertEquals(SrpAnonymousKeyListener.DEFAULT_PINCODE, authPasswordHandlerImpl.getPassword(authPeer));
    }

}
