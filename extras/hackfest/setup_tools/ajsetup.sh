#!/bin/bash

# Copyright (c) 2014 AllSeen Alliance. All rights reserved.
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

if [ -d "allseen" ]; then
   read -p "The folder allseen already exists, running this script will overwrite it. Do you still wish to run it? (Y/N)" yn
   case $yn in
      [Yy]* ) rm -rf allseen;;
      [Nn]* ) exit 1;;
      * ) echo "Quitting"; exit 1;;
   esac
fi

if [ -f "duktape-0.11.0.tar.xz" ]; then
   read -p "The archive duktape-0.11.0.tar.xz already exists, running this script will overwrite it. Do you still wish to run it? (Y/N)" yn
   case $yn in
      [Yy]* ) rm -f duktape-0.11.0.tar.xz;;
      [Nn]* ) exit 1;;
      * ) echo "Quitting"; exit 1;;
   esac
fi

if ! which scons > /dev/null; then
   sudo apt-get install scons
fi

mkdir allseen
mkdir allseen/core
mkdir allseen/services

git clone https://git.allseenalliance.org/gerrit/core/ajtcl.git         allseen/core/ajtcl
git clone https://git.allseenalliance.org/gerrit/services/base_tcl.git  allseen/services/base_tcl
git clone https://git.allseenalliance.org/gerrit/core/alljoyn-js.git    allseen/core/alljoyn-js

wget http://duktape.org/duktape-0.11.0.tar.xz

tar xvfJ duktape-0.11.0.tar.xz -C $PWD/allseen/core/alljoyn-js/external

export DUKTAPE_DIST=$PWD/allseen/core/alljoyn-js/external/duktape-0.11.0

cd allseen/core/ajtcl
scons WS=off

cd ../alljoyn-js
scons WS=off

echo "Add this command to you bash startup script to .bashrc or .bashprofile or manually run it when you startup a terminal"
echo "export LD_LIBRARY_PATH=$PWD/allseen/core/ajtcl:$LD_LIBRARY_PATH"
