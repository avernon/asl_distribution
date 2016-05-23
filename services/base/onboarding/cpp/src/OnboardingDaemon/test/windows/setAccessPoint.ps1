#    Copyright (c) 2014, AllSeen Alliance. All rights reserved.
#
#       Contributed by Qualcomm Connected Experiences, Inc.,
#       with authorization from the AllSeen Alliance, Inc.
#       
#       Licensed under the Apache License, Version 2.0 (the "License");
#       you may not use this file except in compliance with the License.
#       You may obtain a copy of the License at
#       
#           http://www.apache.org/licenses/LICENSE-2.0
#       
#       Unless required by applicable law or agreed to in writing, software
#       distributed under the License is distributed on an "AS IS" BASIS,
#       WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#       See the License for the specific language governing permissions and
#       limitations under the License.
#       
#       Pursuant to Section 1 of the License, the work of authorship constituting
#       a Work and any Contribution incorporated in the Work shall mean only that
#       Contributor's code submissions authored by that Contributor.  Any rights
#       granted under the License are conditioned upon acceptance of these
#       clarifications.

# Register the HNetCfg library and create a NetSharingManager object
regsvr32 hnetcfg.dll
$netSharingMgr = New-Object -ComObject HNetCfg.HNetShare

# Find the LAN connection
$lanConnection = $netSharingMgr.EnumEveryConnection |? { $netSharingMgr.NetConnectionProps.Invoke($_).Name -eq "Local Area Connection" }

# Get sharing configuration
$config = $netSharingMgr.INetSharingConfigurationForINetConnection.Invoke($lanConnection)

# If SharingType==true, enable sharing, parameter 0=public, 1=private
If( $config.SharingType -eq 0) {$config.EnableSharing(0)}

# Disable sharing
#$config.DisableSharing()
