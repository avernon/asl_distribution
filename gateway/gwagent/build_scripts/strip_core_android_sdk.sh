#!/bin/bash

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
#
# Strips down the AllJoyn Core Android SDK to the minimum needed for building the gateway project
#
#   DEPENDENCIES_DIR - directory contains the zip files of the dependencies
#   CORE_VERSION - version of AllJoyn core
#   WORKING_DIR - directory for working with files
#   ARTIFACTS_DIR - directory to which to copy the prepared dependencies

set -o nounset
set -o errexit
set -o verbose
set -o xtrace


# check for required env variables
for var in DEPENDENCIES_DIR CORE_VERSION ARTIFACTS_DIR WORKING_DIR
do
    if [ -z "${!var:-}" ]
    then
        printf "$var must be defined!\n"
        exit 1
    fi
done

# set variables for different directories needed
extractedSdks=${WORKING_DIR}/unzipped_sdks
sdkStaging=${WORKING_DIR}/sdk_stage
sdksDir=${ARTIFACTS_DIR}/sdks

mkdir -p $sdksDir
mkdir -p $extractedSdks
mkdir -p $sdkStaging

# Extract subset of Android SDK for dbg and rel variants
for variantString in dbg rel
do
    # determine the name of the SDK
    sdkName=alljoyn-${CORE_VERSION}-android-sdk-$variantString

    # create directory to unzip into
    zipContent=$extractedSdks/$sdkName
    mkdir -p $zipContent

    zipFile=$sdkName.zip

    # unzip the SDK into the directory
    unzip ${DEPENDENCIES_DIR}/$zipFile -d $zipContent

    # create directory for staging content for stripped down zip file
    zipStage=$sdkStaging/$sdkName
    mkdir -p $zipStage

    # determine the source and destination directories for copying files
    javaDir=alljoyn-android/core/alljoyn-${CORE_VERSION}-$variantString/java
    srcJavaDir=$zipContent/$javaDir
    destJavaDir=$zipStage/$javaDir

    # create the destination directory structure and copy a subset of the files from the source
    mkdir -p $destJavaDir
    cp -r  $srcJavaDir/lib $destJavaDir/
    cp -r  $srcJavaDir/jar $destJavaDir/

    # create the stripped down zip file
    cd $zipStage
    zip $sdksDir/$zipFile -r alljoyn-android

done
