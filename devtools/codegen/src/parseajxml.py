# Copyright (c) 2013 AllSeen Alliance. All rights reserved.
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
import sys
import argparse

import config
import interface
import service
import validate
import common

class ParseException(Exception):
    """Parse exceptions"""

class ParseAjXml:
    """Parses the XML and initializes the AllJoyn data structures."""

    def __init__(self, xml_filename):
        """Initialize an instance of the ParseAjXml class."""
        self.filename = xml_filename

        try:
            self.tree = ElementTree.parse(self.filename)
        except:
            f = "Exception parsing '{0}': {1}"
            message = f.format(self.filename, sys.exc_info()[1])
            raise ParseException(message)

        return

    def parse(self, command_line):
        """Fill in the AllJoyn data structures from the XML file."""
        node = self.tree.getroot()
        if node.tag != "node":
            error = "Root xml object must be a 'node'."
            error = AllJoynCodeGenCommon.get_xml_error(node, error)
            raise ValidateException(error)

        xml_bus_object_path = node.get("name")
        cmd_bus_object_path = command_line.object_path

        service_name = self.__get_bus_object_path(xml_bus_object_path,
                                                  cmd_bus_object_path,
                                                  node)
        return_value = service.Service(service_name)
        return_value.parse(node, command_line.lax_naming)

        return return_value

    def __get_bus_object_path(self,
                              xml_bus_object_path,
                              cmd_bus_object_path,
                              xml):
        """Check the xml and command line versions of the bus object path.

        At least one must be present. If both are present they must be the
        same. Return the valid bus-object/object-path or throw an
        exception."""
        if (xml_bus_object_path is not None and
           cmd_bus_object_path is not None and
           xml_bus_object_path != cmd_bus_object_path):

            error1_format = "Command line object path: '{0}'"
            error1 = error1_format.format(cmd_bus_object_path)
            error2_format = "does not match Xml object path: '{0}'."
            error2 = error2_format.format(xml_bus_object_path)

            raise ParseException("{0}\n{1}".format(error1, error2))

        return_value = cmd_bus_object_path

        if return_value is None:
            if xml_bus_object_path is None:
                error = "Bus object path not specified in XML or on command line."
                raise ParseException(error)
            else:
                validate.bus_object_path(xml_bus_object_path, xml)
                return_value = xml_bus_object_path

        return return_value
