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
# Builds an archive file of the Linux build for gwagent
#
#   GWAGENT_SDK_VERSION - version name ot use in building the archive file (version number left out if not given)
#   GWAGENT_SRC_DIR - root directory of the gwagent git repo (defaults to relative location if not given)
#   ARTIFACTS_DIR - directory to copy build products (defaults to build/jobs/artifacts)
#   WORKING_DIR - directory for working with files (defaults to build/jobs/tmp)


set -o nounset
set -o errexit
set -o verbose
set -o xtrace


#========================================
# Set default values for any unset environment variables

if [ -z "${GWAGENT_SRC_DIR:-}" ]
then
    # set it to the top level directory for the git repo
    # (based on relative position of the build_scripts)
    export GWAGENT_SRC_DIR=$(dirname $(dirname $(readlink -f $0)))
fi

export ARTIFACTS_DIR=${ARTIFACTS_DIR:-$GWAGENT_SRC_DIR/build/jobs/artifacts}
export WORKING_DIR=${WORKING_DIR:-$GWAGENT_SRC_DIR/build/jobs/tmp}

versionString=""
if [ -n "${GWAGENT_SDK_VERSION:-}" ]
then
    versionString="${GWAGENT_SDK_VERSION}-"
fi

#========================================
# set variables for different directories needed
sdkStaging=${WORKING_DIR}/sdk_stage
sdksDir=${ARTIFACTS_DIR}/sdks

# create the directories needed
mkdir -p $sdkStaging
mkdir -p ${ARTIFACTS_DIR}
mkdir -p $sdksDir



#========================================
# generate the docs

md5File=$sdksDir/md5-alljoyn-gwagent-${versionString}docs.txt
rm -f $md5File

generateDocs() {
    docName=$1
    docSrc=$2

    pushd ${GWAGENT_SRC_DIR}
    scons V=1 BINDINGS=cpp DOCS=html VARIANT=release -u ${docName}_docs
    popd

    docArtifacts=$sdkStaging/$docName
    cp -r ${GWAGENT_SRC_DIR}/build/linux/x86_64/release/dist/$2/docs/* $docArtifacts

    # create Manifest.txt file
    pushd ${GWAGENT_SRC_DIR}
    python ${GWAGENT_SRC_DIR}/build_scripts/genversion.py > $docArtifacts/Manifest.txt
    popd

    # create the documentation package
    sdkName=alljoyn-gwagent-${versionString}$docName-docs
    tarFile=$sdksDir/$sdkName.tar.gz

    pushd $docArtifacts
    tar zcvf $tarFile * --exclude=SConscript
    popd

    pushd $sdksDir
    md5sum $sdkName.tar.gz >> $md5File
    popd
}



generateDocs gwma gatewayMgmtApp
generateDocs gwcnc gatewayConnector
generateDocs gwc gatewayController

iosDocsZip=alljoyn-gwagent-${versionString}ios-sdk-docs.zip
androidDocsZip=alljoyn-gwagent-${versionString}android-sdk-docs.zip

pushd $sdksDir
[[ ! -f $iosDocsZip ]] || md5sum $iosDocsZip >> $md5File
[[ ! -f $androidDocsZip ]] || md5sum $androidDocsZip >> $md5File
popd

