﻿// ****************************************************************************
// Copyright AllSeen Alliance. All rights reserved.
//
//    Contributed by Qualcomm Connected Experiences, Inc.,
//    with authorization from the AllSeen Alliance, Inc.
//    
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//    
//        http://www.apache.org/licenses/LICENSE-2.0
//    
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//    
//    Pursuant to Section 1 of the License, the work of authorship constituting
//    a Work and any Contribution incorporated in the Work shall mean only that
//    Contributor's code submissions authored by that Contributor.  Any rights
//    granted under the License are conditioned upon acceptance of these
//    clarifications.
// ******************************************************************************

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace AllJoynNET {
/// <summary>
/// a Windows Form for Connecting to the AllJoyn bus
/// </summary>
public partial class AllJoynConnectForm : Form {
    #region Constructors


    public AllJoynConnectForm() : this(new AllJoynBus(), null) { }
    public AllJoynConnectForm(AllJoynBus bus, Form owner)
    {
        _ajBus = bus;
        _owner = owner;
        InitializeComponent();
        this.Hide();
    }

    #endregion

    #region Properties
    public bool IsConnected { get { return _connected; } set { _connected = value; } }
    public string SessionName { get { return txtSession.Text; } }
    public string MyHandle { get { return txtHandle.Text; } }
    public bool IsNameOwner { get { return rbAdvertise.Checked; } }

    public AllJoynBus AJBus { get { return _ajBus; } }
    public AllJoynSession AJSession { get { return _session; } }
    #endregion

    #region shared methods

    /// <summary>
    /// This function must be called before displaying the form.
    /// </summary>
    /// <param name="receiver">a ReceiverDelegate for handling output from the AllJoynBusConnection</param>
    /// <param name="subscribe">a SubscriberDelegate that will handle adding "joiners" to the session"</param>
    /// <returns></returns>
    public bool InstallDelegates(ReceiverDelegate receiver, SubscriberDelegate subscribe)
    {
        if (_ajBus != null) {
            _ajBus.SetOutputStream(receiver);
            _ajBus.SetLocalListener(subscribe);
            return true;
        }
        // else do notning
        return false;
    }

    /// <summary>
    /// override to update any local changes
    /// </summary>
    /// <param name="e">unused - passed to base class</param>
    protected override void OnShown(EventArgs e)
    {
        updateUI();
        base.OnShown(e);
    }

    #endregion

    #region private variables

    private Form _owner = null;
    private bool _connected = false;
    private AllJoynBus _ajBus;
    private AllJoynSession _session;

    #endregion

    #region private methods
    /// <summary>
    /// PRIVATE update form fields when visible
    /// </summary>
    private void updateUI()
    {
        if (IsConnected) {
            btnConnect.Text = "Disconnect";
            txtSession.Enabled = false;
            txtHandle.Enabled = false;
            rbAdvertise.Enabled = false;
            rbJoin.Enabled = false;
        } else   {
            btnConnect.Text = "Connect";
            txtSession.Enabled = true;
            txtHandle.Enabled = true;
            rbAdvertise.Enabled = true;
            rbJoin.Enabled = true;
        }
    }

    private void btnConnect_Click(object sender, EventArgs e)
    {
        if (!_connected) {
            if (checkInvariants()) {
                bool success = rbAdvertise.Checked;
                _connected = _ajBus.Connect(txtHandle.Text, ref success);
            } else
                MessageBox.Show("Missing input - handle or session names must not be empty",
                                "AllJoyn Connection", MessageBoxButtons.OK, MessageBoxIcon.Hand);
        } else   {
            _ajBus.Disconnect();
            _connected = false;
        }

        updateUI();
    }

    private bool checkInvariants()
    {
        return ((txtHandle.Text.Length > 0) && (txtSession.Text.Length > 0));
    }
    #endregion
}
}

