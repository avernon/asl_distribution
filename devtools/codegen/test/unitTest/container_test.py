# Copyright (c) 2013, AllSeen Alliance. All rights reserved.
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

import unittest

import AllJoynCodeGen.container as container

########
# Each entry is ("number of unique structures", "signature").
########
structure_test_cases = ( (0, "b"),
                         (1, "(b)"),
                         (1, "(bad)"),
                         (2, "(bad(bad))"),
                         (4, "(bad(bad(dad))(bad))"),
                         (4, "((((bad)(bad)(bad)))(bad)bad)"),
                         (9, "((((bid)(bud)(bad(bad(bad)))))(dad)qub)")
                       )

########
# Each entry is ("number of unique dictionaries", "signature").
########
dictionary_test_cases = ( (0, "b"),
                          (1, "a{ib}"),
                          (1, "a{iu}"),
                          (2, "a{ia{is}}"),
                        )

########
# Each entry is ("number of unique containers", "signature").
########
mixed_test_cases = ( (0, "b"),
                     (3, "a{i(bib(bad)nib)}"),
                     (6, "(((ba{us})(ba{us}(bad)))(bad)bad)"),
                   )

class TestInterface(unittest.TestCase):
    """Tests the Interface class."""

    def test_structs(self):
        last_order = 0
        for case in structure_test_cases:
            c = container.Container(case[1])
            mess = "Case '{0}'.".format(case[1])
            self.assertTrue(c.get_order() >= last_order, mess)
            last_order = c.get_order()

            structs = {}
            c.extract_structures(structs)
            self.assertEqual(len(structs), case[0], mess)

        return

    def test_dictionaries(self):
        last_order = 0
        for case in dictionary_test_cases:
            c = container.Container(case[1])
            mess = "Case '{0}'.".format(case[1])
            self.assertTrue(c.get_order() >= last_order, mess)
            last_order = c.get_order()

            dicts = {}
            c.extract_dictionaries(dicts)
            self.assertEqual(len(dicts), case[0], mess)

        return

    def test_mixed(self):
        last_order = 0
        for case in mixed_test_cases:
            c = container.Container(case[1])
            mess = "Case '{0}'.".format(case[1])
            self.assertTrue(c.get_order() >= last_order, mess)
            last_order = c.get_order()

            dicts = {}
            structs = {}
            c.extract_dictionaries(dicts)
            c.extract_structures(structs)

            self.assertEqual(len(dicts) + len(structs), case[0], mess)

        return

