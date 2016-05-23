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

import sys
import parseajxml
import config
import validate
import service
import common
import CheetahCompileExcept as cce

try:
    # All modules that contain Cheetah templates must be placed within this try.
    import tl.GenTL
    import android.GenAndroid
except cce.CheetahCompilationException:
    print("Unable to import compiled template modules.")
    print("Run ajcodegen-compile.py and try again.")
    sys.exit(1)

##################################
# This is the start of execution.
##################################
def main():
    """The entry point for AllJoyn Code Generator."""
    error_format = "\nERROR! {0}"

    try:
        configuration = config.Config()
        register_targets(configuration)
        configuration.parse()
        report_config(configuration)
        parser = parseajxml.ParseAjXml(configuration.command_line.xml_input_file)
        service = parser.parse(configuration.command_line)

        target = configuration.command_line.target_language

        validate.alljoyn_data(service, target)

        if configuration.command_line.xml:
            print(service)

        if target == "android":
            android.GenAndroid.generate_code(configuration.command_line, service)
        elif target == "c":
            # Also must enable this option in config.__validate()
            pass # The 'C' generator has not been implemented.
        elif target == "cpp":
            # Also must enable this option in config.__validate()
            pass # The 'C++' generator has not been implemented.
        elif target == "o":
            # Also must enable this option in config.__validate()
            pass # The Objective C generator has not been implemented.
        elif target == "tl":
            tl.GenTL.generate_code(configuration.command_line, service)
        else:
            print("Unexpected target language option. No code generated.")


    except config.ConfigException as e:
        print(error_format.format(e.message))
        sys.exit(1)

    except validate.ValidateException as e:
        print(error_format.format(e.message))
        sys.exit(1)

    except parseajxml.ParseException as e:
        print(error_format.format(e.message))
        sys.exit(1)

    print("Done.")
    return

def report_config(c):
    """Print the configuration options."""
    input_file = c.command_line.xml_input_file
    print("Input XML file = '{0}'.".format(input_file))

    if c.command_line.object_path is not None:
        path = c.command_line.object_path
        print("Object path = '{0}'.".format(path))

    if c.command_line.lax_naming:
        print("Lax naming enabled.")

    if c.command_line.output_path is not None:
        path = c.command_line.output_path
        print("Output path is '{0}'.".format(path))

    if c.command_line.runnable:
        print("Runnable code will be generated.")

    target = c.command_line.target_language
    print("Target language option is '{0}'.".format(target))

    if c.command_line.well_known_name is not None:
        name = c.command_line.well_known_name
        print("Well known name = '{0}'.".format(name))

    return

def register_targets(c):
    """Register the target languages supported with the configuration 'c'."""
    c.register_target('tl', tl.GenTL.hooks())
    c.register_target('android', android.GenAndroid.hooks())
    c.register_target('ddcpp', ddcpp.GenCPP.hooks())

if __name__=="__main__":
   main()
