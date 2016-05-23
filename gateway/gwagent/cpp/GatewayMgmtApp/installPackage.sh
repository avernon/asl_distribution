#!/bin/sh 

# Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

# sample script to handle installing of an application until package manager is available

# exit if the tar filename wasn't given
if [ -z "$1" ]; then
    echo "Usage: $(basename $0) [package.tar.gz]"
    exit 1
fi
tarFile=$1

# the base installation directory for alljoyn and the gateway agent
baseDir=/opt/alljoyn
tmpDir=
pkgInstallDir=
connectorId=

# whether install completed successfully
installCompleted=0
# whether we created a user
createdUser=0

# function to clean up files, etc. on exit
cleanup_on_exit() 
{
    # remove our temporary folder
    if [ -n "$tmpDir" ] && [ -d "$tmpDir" ]; then
        rm -fr $tmpDir
    fi

    if [ "$installCompleted" = 0 ]; then
        # remove the install directory (if we created it)
        if [ -n "$pkgInstallDir" ] && [ -d "$pkgInstallDir" ]; then
            rm -fr $pkgInstallDir
        fi
        # remove user (if we created it)
        if [ "$createdUser" != 0 ]; then
            echo userdel "$connectorId"
        fi
    fi
}

# add trap to clean up temp directory on exit
trap 'cleanup_on_exit' EXIT



echo "Trying to install: $tarFile"

# get a temp directory to untar the package
uuid=$(cat /proc/sys/kernel/random/uuid)
tmpDir=$baseDir/app-manager/$uuid

if [ -d "$tmpDir" ]; then
    echo "$tmpDir directory already exists. Should not have happened"; exit 6; 
fi

mkdir "$tmpDir" || exit 7

tar -xzf $tarFile -C $tmpDir

manifestFile=$tmpDir/Manifest.xml
if [ ! -f "$manifestFile" ]; then
    echo "Can not find $manifestFile file. Aborting"; exit 8; 
fi

appBinDir=$tmpDir/bin
if [ ! -d "$appBinDir" ]; then
    echo "Can not find $appBinDir directory. Aborting"; exit 9; 
fi

# get the connectorId from the Manifest.xml
connectorId=$(grep "<connectorId>" $manifestFile | sed -e "s/ *<connectorId>//" | sed -e "s/<\/connectorId *>//")

connectorAppDir=$baseDir/apps/$connectorId
if [ -d "$connectorAppDir" ]; then
    echo "Can not create directory for this app. It already exists: $connectorAppDir"; 
    exit 10; 
fi

pkgInstallDir=$connectorAppDir

mkdir -p $pkgInstallDir || exit 11
mkdir -p $pkgInstallDir/acls || exit 12
mkdir -p "$pkgInstallDir/bin" || exit 13
## TODO mkdir -p "$pkgInstallDir/etc || exit 14
mkdir -p "$pkgInstallDir/lib" || exit 15
## TODO mkdir -p "$pkgInstallDir/res" || exit 16
mkdir -p "$pkgInstallDir/store" || exit 17
## TODO mkdir -p "$pkgInstallDir/tmp" || exit 18

cp -rf $tmpDir/bin/* $pkgInstallDir/bin || exit 19
ls $tmpDir/lib/* &> /dev/null
if [ $? == 0 ]; then
    cp -rf $tmpDir/lib/* $pkgInstallDir/lib || exit 20
fi
cp $tmpDir/Manifest.xml $pkgInstallDir/ || exit 21

# allow package to be installed for an existing user (for testing purposes)
id -u "$connectorId" &> /dev/null
if [ $? != 0 ]; then
    useradd $connectorId || exit 22
    createdUser=1
fi

chown -R "$connectorId" "$pkgInstallDir/store" || exit 23
chmod -R a+rx "$pkgInstallDir/bin" || exit 24
chmod -R a+rx "$pkgInstallDir/lib" || exit 25

installCompleted=1

echo "Successfully installed $tarFile with connectorId: $connectorId"; 
exit 0

