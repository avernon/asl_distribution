#    Copyright AllSeen Alliance. All rights reserved.
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

#!/bin/bash

set -e
SERVICE_FRAMEWORK_HOME=$1

if [ -d $SERVICE_FRAMEWORK_HOME ]; then
	if [ -d "$SERVICE_FRAMEWORK_HOME/standard_core_library/" ]; then
		cd $SERVICE_FRAMEWORK_HOME/standard_core_library/
		mkdir -p lighting_controller_service/inc/lsf
		ln -s `pwd`/lighting_controller_service/inc lighting_controller_service/inc/lsf/controllerservice
	else
		echo "SERVICE_FRAMEWORK_HOME directory exists but doesn't point to service_framework repo root folder"
		exit 1
	fi
else
	echo "SERVICE_FRAMEWORK_HOME directory doesn't exists"
	exit 1
fi
