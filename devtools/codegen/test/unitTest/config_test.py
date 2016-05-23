# Copyright (c) 2013, 2014 AllSeen Alliance. All rights reserved.
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
import fnmatch
import os
import sys

import AllJoynCodeGen.config as config

class TestConfig(unittest.TestCase):
    """Tests the Config class."""
    def test_no_args(self):
        """Test what happens when no arguments are given."""

        sys.argv = ["DummyArg0"]

        with self.assertRaises(SystemExit) as cm:
            config.Config()

        self.assertTrue(sys.exc_info() is not None)
        return

    def test_object_path(self):
        """Test the object path (-b) flag."""
        args = ["arg0", "-b/TestFoo", "-ttl", "-wTest.Foo", "file.xml"]
        sys.argv = args
        c = config.Config()
        self.assertTrue(c.command_line.xml_input_file == "file.xml")
        self.assertTrue(c.command_line.target_language == "tl")
        self.assertTrue(c.command_line.object_path == "/TestFoo")

        args = ["arg0", "-b", "/TestFoo", "-wTest.Foo", "-ttl", "file.xml"]
        sys.argv = args
        c = config.Config()
        self.assertTrue(c.command_line.object_path == "/TestFoo")
        return

    def test_client_only(self):
        """Test the client only (-c) flag."""
        c = self.__one_arg_test("-b/TestFoo")
        self.assertFalse(c.command_line.client_only)

        c = self.__one_arg_test("-c")
        self.assertTrue(c.command_line.client_only)
        return

    def test_lax_naming(self):
        """Test the lax naming (-l) flag."""
        c = self.__one_arg_test("-b/TestFoo")
        self.assertFalse(c.command_line.lax_naming)

        c = self.__one_arg_test("-l")
        self.assertTrue(c.command_line.lax_naming)
        return

    def test_runnable(self):
        """Test the runnable (-R) flag."""
        c = self.__one_arg_test("-b/TestFoo")
        self.assertFalse(c.command_line.runnable)

        c = self.__one_arg_test("-R")
        self.assertTrue(c.command_line.runnable)
        return

    def test_target_language(self):
        """Test the target language (-t) flag."""
        args = ["arg0", "-ttl", "-wTest.foo", "file.xml"]
        sys.argv = args

        c = config.Config()
        self.assertTrue(c.command_line.xml_input_file == "file.xml")
        self.assertTrue(c.command_line.target_language == "tl")

        args[1] = "-tandroid"
        c = util.get_config()
        self.assertTrue(c.command_line.target_language == "android")

        args[1] = "-tddcpp"
        c = util.get_config()
        self.assertTrue(c.command_line.target_language == "ddcpp")

        args[1] = "-tFoo"

        try:
            c = config.Config()
            self.assertTrue(False,
                    "Invalid target language should result in a SystemExit.")
        except SystemExit:
            self.assertTrue(sys.exc_info() is not None)
        return

    def test_well_known_name(self):
        """Test the well known name flag."""
        args = ["arg0", "-ttl", "-wTest.My.Foo", "file.xml"]
        sys.argv = args
        c = config.Config()
        self.assertTrue(c.command_line.well_known_name == "Test.My.Foo")
        args[1] = "-w"

        return

    def test_xml(self):
        """Test the -x (--xml) flag."""
        c = self.__one_arg_test("-b/TestFoo")
        self.assertFalse(c.command_line.xml)

        c = self.__one_arg_test("-x")
        self.assertTrue(c.command_line.xml)
        return

    def __one_arg_test(self, arg_to_test):
        """Test this one argument when creating a configuration."""
        args = ["arg0", arg_to_test, "-ttl", "-wTest.Foo", "file.xml"]
        sys.argv = args
        c = config.Config()
        return c

if __name__ == '__main__':
    unittest.main()


