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

import argdef

class Container:
    """Describes AllJoyn structure and dictionary containers not arrays."""

    def __init__(self, signature, name = None):
        """Initialize an instance of the Container class.

The expectation is that validate.data_signature() will have been previously
called, and passed, for this signature."""
        self.signature = signature

        if name is not None:
            self.set_name(name)
        else:
            self.name = None

        return

    def get_order(self):
        """Get the sorting key used to order the declaration of the container."""
        # Equal length signatures may be declared in any order.
        return len(self.signature)

    def extract_dictionaries(self, destination_list):
        """If not found in the destination_list put each dictionary in it.

It is assumed that the signature has been validated such that curly braces
match and each '{' is preceeded by 'a'.

The destination_list is a dictionary. The key is the signature and the value
is a Container with no name."""
        self.__extract_containers(destination_list, '{', '}')
        return

    def extract_structures(self, destination_list):
        """If not found in the destination_list put each substructure in it.

The destination_list is a dictionary. The key is the signature and the value
is a Container with no name."""
        self.__extract_containers(destination_list, '(', ')')
        return

    def set_name(self, name):
        temp = argdef.make_clean_name(self.signature)

        if name.find(temp) == -1:
            self.name = "{0}{1}".format(name, temp)
        else:
            self.name = name

        return

    def __extract_containers(self, destination_list, start, end):
        """If not found in the destination_list put each subcontainer in it.

The destination_list is a dictionary. The key is the signature and the value
is a Container with no name.
'start' is the character that represents the start of a container.
'end' is the character that represents the end of a container."""
        stack = []

        index = 0
        max_index = len(self.signature)

        while index < max_index:
            c = self.signature[index]

            if c == start:
                stack.append(index)
            elif c == end:
                start_index = stack[-1]
                result = self.signature[start_index : index + 1]

                if result not in destination_list:
                    c = Container(result)
                    destination_list[result] = c

                stack.pop()

            index += 1

        return

