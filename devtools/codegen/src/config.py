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

import argparse
import os
import validate
import common

class ConfigException(Exception):
    """Configuration exceptions"""

def get_version():
    return "15.09"

class Config:
    """Contains the configuration obtained from the command line.

    This class defines, parses, and validates the command line arguments.
    The configuration values are accessable via the member 'command_line'.
    command_line has the following members and types:

        xml_input_file (string)
        absolute_path_xml_input_file (string)
        object_path (None or string)
        client_only (None or True)
        lax_naming (None or True)
        output_path (string)
        runnable (None or True)
        target_language (string of 'c', 'cpp', 'o', or 'tl')
        well_known_name (None or string)
    """
    def __init__(self):
        """Initialize an instance of the Config class."""
        ver = get_version()
        descrip = "Generate AllJoyn code from XML source. Version {0}.".format(ver)
        parser = argparse.ArgumentParser(description=descrip)

        help_text = """The file containing the xml definition of an object's
            interface(s)."""
        parser.add_argument("xml_input_file", help=help_text)

        help_text = """The object path (including name) of the object being
            defined in the xml input file. If the xml file contains the object
            path it does not match OBJECT_PATH, this tool will exit with an
            error. If the name is not defined either in the XML or using
            this flag, this tool will also exit with an error."""
        parser.add_argument("-b", "--object-path", help=help_text)

        help_text = """Only generate the client side code; if not specified,
            both the client and service code are generated."""
        parser.add_argument("-c", "--client-only", help=help_text,
                            action="store_true")

        help_text = """Relaxes the requirement that all method and signal
            arguments be named. If specified, default names will be generated
            for arguments."""
        parser.add_argument("-l", "--lax-naming", help=help_text,
                            action="store_true")

        help_text = """The path where the generated C++ files will be placed.
            If not specified, they will be output in the current working
            directory."""
        parser.add_argument("-p", "--output-path", help=help_text)

        help_text = """The generated client executable will make method calls
            with default values and the service method handlers will reply
            with default values. This option requires a valid object path to
            be specified (i.e. -b)."""
        parser.add_argument("-R", "--runnable", help=help_text,
                            action="store_true")

        help_text = """The target language. 'android' is for Java code on
            the Android platform. 'tl' is C code for AllJoyn Thin Library."""
        parser.add_argument("-t", "--target-language", required=True,
                            choices=['android', 'tl'],
                            help=help_text)

        ver_text = "Version {0}.".format(ver)
        parser.add_argument("-v", '--version', action='version', version=ver_text)

        help_text = """The well-known name that the interface will use when
            requesting a bus name or advertising a name."""
        parser.add_argument("-w", "--well-known-name", required=True,
                            help=help_text)

        help_text = """Output verbose information about the XML during
             parsing."""
        parser.add_argument("-x", "--xml", help=help_text, action="store_true")

        self.command_line = parser.parse_args()

        self.__validate()
        self.__get_addtions()

    def __get_addtions(self):
        """The target language is sometimes needed in modules that don't have easy
        access to the command line. So this is added to the common module.
        The absolute path of the input xml file is added to the command line as
        "absolute_path_xml_input_file". The path separators are forced to be '/'
        so that Eclipse doesn't claim (even in a COMMENT!) the string has invalid
        unicode escape sequences."""
        common.target_language = self.command_line.target_language
        temp = os.path.abspath(self.command_line.xml_input_file)
        self.command_line.absolute_path_xml_input_file = temp.replace("\\", "/")

    def __validate(self):
        """Validates various command line arguments beyond simple syntax."""

        target = self.command_line.target_language
        if target != 'tl' and target != 'android':
            e1 = "The only target languages supported at this time are 'tl' and 'android'."
            e2 = "Use the option '-ttl' or '-tandroid'."

            raise ConfigException("{0} {1}".format(e1, e2))

        if self.command_line.object_path is not None:
            validate.bus_object_path(self.command_line.object_path)

        validate.well_known_name(self.command_line.well_known_name)

        if self.command_line.output_path is None:
            self.command_line.output_path = "."

        path = self.command_line.output_path

        if path is not None and not os.path.exists(path):
            raise ConfigException("Path '{0}' does not exist.".format(path))

        return
