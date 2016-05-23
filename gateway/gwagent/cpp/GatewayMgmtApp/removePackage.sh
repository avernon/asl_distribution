#!/bin/sh 

# Copyright AllSeen Alliance. All rights reserved.
#
#    Contributed by Qualcomm Connected Experiences, Inc.,
#    with authorization from the AllSeen Alliance, Inc.
#    
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#    
#        http://www.apache.org/licenses/LICENSE-2.0
#    
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#    
#    Pursuant to Section 1 of the License, the work of authorship constituting
#    a Work and any Contribution incorporated in the Work shall mean only that
#    Contributor's code submissions authored by that Contributor.  Any rights
#    granted under the License are conditioned upon acceptance of these
#    clarifications.
#

# sample script to remove an application until package manager is available
# 
# this just removes the directory, but also reminds to delete the user

# exit if connectorId wasn't given
if [ -z "$1" ]; then
    echo "Usage: $(basename $0) [connectorId]"
    exit 1
fi

# the base installation directory for alljoyn and the gateway agent
baseDir=/opt/alljoyn
connectorId=$1

connectorAppDir=$baseDir/apps/$connectorId


if [ -d "$connectorAppDir" ]; then
    echo "Removing connectorApp with connectorId: $connectorId"; 
    rm -fr $connectorAppDir || { echo "Error: unable to remove directory: $connectorAppDir" 1>&2; exit 1; }
else
    echo "Error: a connectorApp with connectorId: $connectorId is not installed" 1>&2
    exit 1
fi

echo "Successfully removed connectorApp with connectorId: $connectorId"; 

id -u "$connectorId" 1> /dev/null
if [ $? = 0 ]; then
    echo "To remove user use: userdel $connectorId"
fi

exit 0

