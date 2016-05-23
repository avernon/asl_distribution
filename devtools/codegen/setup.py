# Copyright (c) 2013-2014 AllSeen Alliance. All rights reserved.
#
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

from distutils.core import setup
from src import config

package_data_files = []

# All files needed for Thin Library support.
thin_library_package = ['tl/GenTL.py', 'tl/__init__.py', 'tl/*.tmpl']
package_data_files.extend(thin_library_package)

# All files needed for Android Java support.
android_package = ['android/GenAndroid.py', 'android/__init__.py', 'android/*.tmpl',
                   'android/.settings/*', 'android/res/*/*']
package_data_files.extend(android_package)

setup(name='AllJoynCodeGenSetup',
      version=config.get_version(),
      description='AllJoyn Code Generator',
      url='https://allseenalliance.org/',
      package_dir={'AllJoynCodeGen': 'src'},
      package_data={'AllJoynCodeGen': package_data_files},
      packages=['AllJoynCodeGen'],
      scripts=['scripts/ajcodegen.py', 'scripts/ajcodegen-compile.py'])
