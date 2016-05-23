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

import os

def ConfigureJNI(env):
    """Configure the environment for building JNI native code. """

    if not env.get('JAVAC'):
        print "Java compiler not found"
        return 0

    java_home = os.environ.get('JAVA_HOME')
    if not java_home:
        print "JAVA_HOME not set"
        return 0

    java_include = [os.path.join(java_home, 'include')]
    java_lib = [os.path.join(java_home, 'lib')]

    java_include.append(os.path.join(java_include[0], 'win32'))
    java_include.append(os.path.join(java_include[0], 'linux'))
        
    env.Append(CPPPATH = java_include)
    env.Append(LIBPATH = java_lib)

    return 1
