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
import common
import validate
import argdef

class PropertyDef:
    """Contains the description of an AllJoyn property."""
    def __init__(self):
        """Initialize an instance of the PropertyDef class."""
        self.name = ""
        self.access = ""
        self.is_secure = False
        self.no_reply = False
        self.variant_type = None
        self.args = []
        return

    def parse(self, xml):
        """Parse the given AllJoyn property xml element."""
        assert(xml is not None)
        assert(xml.tag == "property")

        self.name = xml.get("name")
        validate.member_name(self.name, xml)

        data_type = xml.get("type")
        validate.data_signature(data_type, xml)

        self.access = xml.get("access")
        validate.property_access(self.access, xml)
        if self.access == "write":
            self.no_reply = True

        if self.access == "write" or self.access == "readwrite":
            a = argdef.ArgDef(xml, "in_value", data_type, "in")
            self.args.append(a)

        if self.access == "read" or self.access == "readwrite":
            a = argdef.ArgDef(xml, "out_value", data_type, "out")
            self.args.append(a)

        common.get_annotations(xml, self)
        return

    def is_readable(self):
        return self.access == "read" or self.access == "readwrite"

    def is_writeable(self):
        return self.access == "write" or self.access == "readwrite"

    def __eq__(self, other):
        """Compares this property to another and returns true if equal."""
        if (self is None and other is not None or
           self is not None and other is None or
           self.name != other.name or
           len(self.args) != len(other.args) or
           self.access != other.access):
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
        if self == other:
            return False
        return True

    def __str__(self):
        """Create and return a string representation of this object."""
        l1 = "  Name: '{0}'\n".format(self.name)
        l2 = "    Type: {0}\n".format(self.args[0].arg_type)
        l3 = "    Access: {0}\n".format(self.access)
        return_value = "".join([l1, l2, l3])

        return return_value


