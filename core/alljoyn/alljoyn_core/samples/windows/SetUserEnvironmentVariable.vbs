# Contributed by Qualcomm Connected Experiences, Inc.,
# with authorization from the AllSeen Alliance, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Pursuant to Section 1 of the License, the work of authorship constituting
# a Work and any Contribution incorporated in the Work shall mean only that
# Contributor's code submissions authored by that Contributor.  Any rights
# granted under the License are conditioned upon acceptance of these
# clarifications.
' SetUserEnvironmentVariable.vbs
' intent: this script is used by the SDK installer during the 
'         custom action stage to set the installation path environment variable
' usage:
' SetUserEnvironmentVariable.vbs /InstallPoint=<sdk path>|/AllUsers=<flag>
'
'

Dim bAllUsersInstall : bAllUsersInstall = 0
Dim strInstallPointPath : Set strInstallPointPath = Nothing
Dim strNamedArguments

strNamedArguments = Session.Property("CustomActionData")

' Parse the args from the input format:
Dim arrArgs
arrArgs = Split(strNamedArguments, "|")

' /InstallPoint
arrInstallPointParam = Split(arrArgs(0), "=")
strInstallPointPath = arrInstallPointParam(1)

' /AllUsers
arrAllUsersParam = Split(arrArgs(1), "=")
bAllUsersInstall = arrAllUsersParam(1)

' Choose the right type of environment (user or system)
Set WSHShell = CreateObject("WScript.Shell")

If (bAllUsersInstall = "1") Then
    Set WshEnv = WSHShell.Environment("SYSTEM")
Else 
    Set WshEnv = WSHShell.Environment("USER")
End If

' Use FileSystemObject to get a properly formatted path 
Set fso = CreateObject("Scripting.FileSystemObject")
Dim strInstallPointAbsolutePath
strInstallPointAbsolutePath = fso.GetAbsolutePathName(strInstallPointPath)

' Set the variable
WshEnv("ALLJOYN_SDK_HOME") = strInstallPointAbsolutePath


