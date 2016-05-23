REM    Copyright (c) 2014, AllSeen Alliance. All rights reserved.
REM
REM       Contributed by Qualcomm Connected Experiences, Inc.,
REM       with authorization from the AllSeen Alliance, Inc.
REM       
REM       Licensed under the Apache License, Version 2.0 (the "License");
REM       you may not use this file except in compliance with the License.
REM       You may obtain a copy of the License at
REM       
REM           http://www.apache.org/licenses/LICENSE-2.0
REM       
REM       Unless required by applicable law or agreed to in writing, software
REM       distributed under the License is distributed on an "AS IS" BASIS,
REM       WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
REM       See the License for the specific language governing permissions and
REM       limitations under the License.
REM       
REM       Pursuant to Section 1 of the License, the work of authorship constituting
REM       a Work and any Contribution incorporated in the Work shall mean only that
REM       Contributor's code submissions authored by that Contributor.  Any rights
REM       granted under the License are conditioned upon acceptance of these
REM       clarifications.
@echo off

REM Todo: Error handling/Messages need to be compliant to Onboarding HLD

REM Todo: Should be params, not hard coded
set ssid=[mySsid]
set authentication=WPA2PSK
set encryption=AES
set key=[myPassword]

set localDir=[Current_Directory_Where_Scripts_Are_Stored]
REM Todo: need to find the powershell path
set PowerShell=[PowerShell_FullPath]



IF "%1"=="configure" GOTO configure
IF "%1"=="connect" GOTO connect
IF "%1"=="offboard" GOTO offboard

set emptyProfile=EmptyProfile.xml
set newProfile="%localDir%\Wireless Network Connection-%ssid%.xml"

del %newProfile%

echo "starting..."

:configure
echo "Step 1: Enable Profile"

set enableProfiles=netsh wlan set createalluserprofile enable=yes

call %enableProfiles% > quiet
echo errorlevel 1 = %errorlevel%


echo "Step 2: Create Empty Profile"

copy  %emptyProfile% %newProfile% > quiet
echo errorlevel 2 = %errorlevel%


echo "Step 3: Replace text in profile"
%PowerShell% Set-ExecutionPolicy unrestricted
%PowerShell%  -File %localDir%\replaceString.ps1 "%localDir%\Wireless Network Connection-%ssid%.xml" "%ssid%"


echo "Step 4: Add Profile"
netsh wlan add profile filename=%newProfile% > quiet
echo errorlevel 4 = %errorlevel%


echo "Step 5: Edit Profile"

netsh wlan set profileparameter name=%ssid% SSIDName=%ssid% authentication=%authentication% encryption=%encryption% keyMaterial=%key% keyType=passphrase
echo errorlevel 5 = %errorlevel%

:connect

echo "Step 6: Connect To Profile"

netsh wlan connect ssid=%ssid% name=%ssid% > quiet
echo errorlevel 6 = %errorlevel%
goto done

REM Todo complete offboard
REM I could not make my machine an Access Point but this may be due to firewall issues.
:offboard
echo "Step 1: Set hosted network"

REM Get mac address
REM is slow at times, may need to look for an alternative
for /f "tokens=*" %%V in (
    '%PowerShell%  -File %localDir%\getMac.ps1') do set MacAddress=%%V

set hostedSSID=AJ_Windows %MacAddress%
echo %hostedSSID%

netsh wlan set hostednetwork mode=allow ssid="%hostedSSID%"
netsh wlan start hostednetwork

echo "Step 2: Share network"
%PowerShell%  -File %localDir%\setAccessPoint.ps1

REM May need to wait for the hostednetwork. netsh wlan show hosted shows its started but the ControlPanel sees it as "Identifying"

:done
del quiet

