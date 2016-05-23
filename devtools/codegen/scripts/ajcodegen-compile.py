#!/usr/bin/env python
# Copyright (c) 2014 AllSeen Alliance. All rights reserved.
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

# Python script for invoking the Cheetah compiler for the .tmpl files.

import os
import sys
import fnmatch
import subprocess
import platform
import distutils.spawn

import AllJoynCodeGen.CheetahCompileExcept as cce

cheetah_command = []

def __get_cheetah_command():
    global cheetah_command

    if cheetah_command:
        return cheetah_command

    cheetah_py = None
    system_type = platform.system()

    if system_type == "Linux" or system_type == "Darwin":
        cheetah_py = distutils.spawn.find_executable("cheetah")
    elif system_type == "Windows":
        scripts_dir = os.path.dirname(os.path.abspath(sys.argv[0]))
        cheetah_py = os.path.join(scripts_dir, "cheetah.py")
        cheetah_command.append("python.exe")
    else:
        print("Unrecognized system type '{0}'".format(system_type))
        return []

    if cheetah_py:
        cheetah_command.extend([cheetah_py, "compile"]);
    else:
        print("Cheetah compiler was not found.")
        cheetah_command = []

    return cheetah_command

def __cheetah_compile(filename):
    path = os.path.dirname(filename)

    if not os.path.isdir(path):
        print("Template directory '{0}' was not found!".format(path))
        return

    src_files = []

    for dirpath, dirs, files in os.walk(path):
        # The "src" portion of the existing directory is not used in the destination path.
        base = dirpath.replace("src/", "", 1)
        dest = os.path.join("Lib/site-packages/AllJoynCodeGen", base)

        for f in files:
            src = os.path.join(dirpath, f)
            if fnmatch.fnmatch(f, "*.tmpl"):
                python_file = "{0}.py".format(os.path.splitext(src)[0])
                already_compiled = os.path.exists(python_file)

                if already_compiled:
                    template_file_time = os.path.getmtime(src)
                    python_file_time = os.path.getmtime(python_file)

                    if template_file_time > python_file_time:
                        src_files.append(src)
                else:
                    src_files.append(src)

    if src_files:
        cheetah_command = __get_cheetah_command()

        if cheetah_command:
            cheetah_command.extend(src_files)
            try:
                subprocess.check_output(cheetah_command)
            except subprocess.CalledProcessError as e:
                print("Unable to compile Cheetah .tmpl files.")
                print("Command was '{0}'.".format(cheetah_command))
                return

            print("Successfully compiled .tmpl files in '{0}'".format(path))

##############
# All modules that contain Cheetah templates must be placed within a try such as this.
##############
try:
    import AllJoynCodeGen.tl.GenTL
except cce.CheetahCompilationException as e:
    # The message is the complete filename of the module for which the import was attempted.
    __cheetah_compile(e.message)

try:
    import AllJoynCodeGen.android.GenAndroid
except cce.CheetahCompilationException as e:
    # The message is the complete filename of the module for which the import was attempted.
    __cheetah_compile(e.message)
