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
export ALLJOYN_ROOT="/home/ubuntu/alljoyn"
export ALLJOYN_DIST="$ALLJOYN_ROOT/core/alljoyn/build/linux/x86/debug/dist"

export CXXFLAGS="-I$ALLJOYN_DIST/cpp/inc \
		-I$ALLJOYN_DIST/about/inc \
		-I$ALLJOYN_DIST/services_common/inc \
		-I$ALLJOYN_DIST/notification/inc \
		-I$ALLJOYN_DIST/controlpanel/inc \
		-I$ALLJOYN_ROOT/services/services_common/cpp/inc/alljoyn/services_common/ \
		-I$ALLJOYN_ROOT/services/sample_apps/cpp/samples_common/"

export LDFLAGS="-L$ALLJOYN_DIST/cpp/lib \
		-L$ALLJOYN_DIST/about/lib \
		-L$ALLJOYN_DIST/services_common/lib \
		-L$ALLJOYN_DIST/notification/lib \
		-L$ALLJOYN_DIST/controlpanel/lib"

export LD_LIBRARY_PATH="$ALLJOYN_DIST/cpp/lib:$ALLJOYN_DIST/about/lib:$ALLJOYN_DIST/services_common/lib:$ALLJOYN_DIST/notification/lib:$ALLJOYN_DIST/controlpanel/lib"

for f in $ALLJOYN_ROOT/hackfest/aj_samples/*; do export PATH=$PATH:$f/build; done

build() {
    pushd $1
    scons WS=off
    popd
}

m() {
    if [ "$1" == "hackfest" ]; then
        for f in $ALLJOYN_ROOT/hackfest/linino/*; do build $f; done
        for f in $ALLJOYN_ROOT/hackfest/aj_samples/*; do build $f; done
    elif [ "$1" == "tutorial" ]; then
        for f in $ALLJOYN_ROOT/hackfest/tutorial/*; do build $f; done
    else
        build $ALLJOYN_ROOT/hackfest/aj_samples/$1
    fi
}

