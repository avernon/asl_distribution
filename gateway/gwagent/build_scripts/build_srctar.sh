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
# Builds a source tar of the gwagent project
#
#   GWAGENT_SRC_DIR - root directory of the gwagent git repo (defaults to relative location if not given)
#   GWAGENT_SDK_VERSION - version name to use in building the archive file (version number left out if not given)
#   ARTIFACTS_DIR - directory to copy build products (default to build/jobs/artifacts)
#   WORKING_DIR - directory for working with files (default to build/jobs/tmp)


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


#========================================

# create the directories needed
mkdir -p ${ARTIFACTS_DIR}
mkdir -p ${WORKING_DIR}

versionString=""
if [ -n "${GWAGENT_SDK_VERSION:-}" ]
then
    versionString="${GWAGENT_SDK_VERSION}-"
fi

outputTarFileName=alljoyn-gwagent-${versionString}src.tar

pushd ${GWAGENT_SRC_DIR}
git archive --prefix=alljoyn-gwagent-${versionString}src/gateway/gwagent/ HEAD^{tree} -o ${WORKING_DIR}/$outputTarFileName

cd ../../core/alljoyn
git archive --prefix=alljoyn-gwagent-${versionString}src/core/alljoyn/ HEAD^{tree} build_core -o ${WORKING_DIR}/core.tar

cd ../../services/base
git archive --prefix=alljoyn-gwagent-${versionString}src/services/base/ HEAD^{tree} sample_apps -o ${WORKING_DIR}/services.tar

cd ../..

tar --concatenate --file=${WORKING_DIR}/$outputTarFileName ${WORKING_DIR}/core.tar
tar --concatenate --file=${WORKING_DIR}/$outputTarFileName ${WORKING_DIR}/services.tar

gzip ${WORKING_DIR}/$outputTarFileName

pushd ${WORKING_DIR}
md5sum $outputTarFileName.gz > md5sum.txt
popd


cp ${WORKING_DIR}/$outputTarFileName.gz ${ARTIFACTS_DIR}
cp ${WORKING_DIR}/md5sum.txt ${ARTIFACTS_DIR}
