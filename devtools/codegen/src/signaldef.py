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

from xml.etree import ElementTree
import validate
import argdef
import common

class SignalDef:
    """Contains the description of a AllJoyn signal."""
    def __init__(self):
        """Initialize an instance of the SignalDef class."""
        self.name = None
        self.args = []
        self.is_secure = False
        # Signal always have a "reply". This variable is for consistency with
        # methods and properties.
        self.no_reply = False
        return

    def parse(self, xml, lax_naming):
        """Parse the given AllJoyn signal xml element."""
        assert(xml is not None)
        assert(xml.tag == "signal")

        self.name = xml.get("name")
        validate.member_name(self.name, xml)

        # Make a list of all the objects at this level.
        xml_root_objects = list(xml)

        arg_num = 0
        common.get_annotations(xml, self)

        for o in xml_root_objects:
            if o.tag == "arg":
                a = argdef.ArgDef()

                a.parse(o, lax_naming, "Signal", self, arg_num)
                arg_num += 1

                # The default direction is "out".
                if a.direction is None:
                    a.direction = "out"
                elif a.direction != "out":
                    error = "Signal arguments must have a direction of 'out'."
                    error = validate.get_xml_error(xml, error)
                    raise validate.ValidateException(error)

                self.__add_arg(o, a)
            elif o.tag != "annotation":
                # Just ignore annotations. We got them earlier.
                warn_format = "\nWarning! Ignoring xml object '{0}'."
                print(warn_format.format(o.tag))

        return

    def get_arg(self, name):
        """Get the argument with the name 'name' or None if not found."""
        return_value = None

        for a in self.args:
            if a.name == name:
                return_value = a
                break

        return return_value

    def __add_arg(self, xml, new_arg):
        for a in self.args:
            if a.name == new_arg.name:
                mess = "Duplicate argument name '{0}'.".format(a.name)
                mess = validate.get_xml_error(xml, mess)
                raise validate.ValidateException(mess)

        self.args.append(new_arg)
        return

    def __eq__(self, other):
        """Compares this signal to another and returns true if equal."""
        if (self is None and other is not None or
           self is not None and other is None or
           self.name != other.name or
           len(self.args) != len(other.args)):
            return False

        # Compare the args in the same order.
        index = 0
        max_index = len(self.args)
        while index < max_index:
            if self.args[index] != other.args[index]:
                return False
            index += 1

        return True

    def __ne__(self, other):
        """Implements the '!=' operator."""
        return not self == other

    def __str__(self):
        """Create and return a string representation of this object."""
        return_value = "  Name: {0}\n    Args:\n".format(self.name)

        if len(self.args) > 0:
            for a in self.args:
                return_value = "{0}{1}".format(return_value, a)

        return return_value
