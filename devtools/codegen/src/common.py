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

import string
from xml.etree import ElementTree

import validate

target_language = None

def get_annotations(xml, aj_object):
    """Get the annotation value for the AllJoyn object from this xml."""
    annotations = xml.iterfind("annotation")

    for a in annotations:
        name = a.get("name")

        if name == "org.alljoyn.Bus.Item.IsSecure":
            value = __get_true_false_value(xml, a, name)
            aj_object.is_secure = value
        elif name == "org.freedesktop.DBus.Method.NoReply":
            value = __get_true_false_value(xml, a, name)
            aj_object.no_reply = value
        elif name == "org.alljoyn.Bus.Arg.VariantTypes":
            value = a.get("value")
            if value is None:
                __report_missing_value(xml, name)
            validate.data_signature(value)
            aj_object.variant_type = value
        else:
            f = "\nIgnoring interface annotation '{0}'."
            mess = f.format(name)
            mess = validate.get_xml_error(xml, mess)
            print(mess)

    return

def make_camel_case(object_name, separator = "/"):
    """Make an object name into a camel case string and delete the separator.

    If the separator is None this method just makes the first character lower
    case."""

    if separator:
        caps_value = string.capwords(object_name, separator)
        temp = caps_value.replace(separator, "")
    else:
        temp = object_name

    first_char_string = temp[0:1]
    return_value = first_char_string.lower() + temp[1:]

    return return_value

def get_arg_signature(component, direction):
    """Get the signature used to marshal the arguments when making a call."""
    return_value = ""

    for a in component.args:
        if a.direction == direction:
            return_value = "".join([return_value, a.get_flattened_signature()])

    return return_value

def __get_true_false_value(xml, annotation, name):
    """Get a true or false value from the annotation xml.

    xml is the parent xml object to annotation xml.
    annotation is the xml object which should have a attribute of value
    containing the 'true' or 'false' value.
    name is the of the parent AllJoyn object."""
    value = annotation.get("value")

    if value is not None:
        if value == "true":
            value = True
        elif value == "false":
            value = False
        else:
            f = "Unexpected annotation value '{0}' for {1}."
            mess = f.format(value, name)
            f = "{0}\nExpected values are 'true' and 'false'."
            mess = f.format(mess)
            mess = validate.get_xml_error(xml, mess)
            raise validate.ValidateException(mess)
    else:
        __report_missing_value(xml, name)

    return value

def __report_missing_value(xml, name):
    f = "Annotation '{0}' is required to have an attribute of 'value'."
    mess = f.format(name)
    mess = validate.get_xml_error(xml, mess)
    raise validate.ValidateException(mess)
