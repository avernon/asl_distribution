#!/bin/bash

#Copyright AllSeen Alliance. All rights reserved.

#Contributed by Qualcomm Connected Experiences, Inc.,
#with authorization from the AllSeen Alliance, Inc.
#
#Licensed under the Apache License, Version 2.0 (the "License");
#you may not use this file except in compliance with the License.
#You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
#Unless required by applicable law or agreed to in writing, software
#distributed under the License is distributed on an "AS IS" BASIS,
#WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#See the License for the specific language governing permissions and
#limitations under the License.
#
#Pursuant to Section 1 of the License, the work of authorship constituting
#a Work and any Contribution incorporated in the Work shall mean only that
#Contributor's code submissions authored by that Contributor.  Any rights
#granted under the License are conditioned upon acceptance of these
#clarifications.

name="LampServiceDir"
specialChar="*"

rm -r -f $name$specialChar

echo "Please enter number of lamp services (Range: 1 to 100) to run:"
read numLampServices

# Initialize Pid List
pidLst=""

for (( i=1; i <= $numLampServices; i++ ))
do
   dname=$name$i
   mkdir "$dname"
   cd "$dname"
   ../lamp_service &
   pidLst="$pidLst $!"
   echo "Launched Lamp Service $i"
   cd ..
done

# trap ctrl-c and call ctrl_c()
trap ctrl_c INT
trap ctrl_z TSTP

function ctrl_c() {
  echo "Trapped CTRL-C"
  echo "Please press Enter to exit"
}

function ctrl_z() {
  echo "Trapped CTRL-Z"
  echo "Please press Enter to exit"
}

echo "Please press Enter to exit"
read exitKey

for pid in $pidLst
do
        ps | grep $pid
        kill -9 $pid
done

rm -r -f $name$specialChar



