# Copyright AllSeen Alliance. All rights reserved.
#
#    Contributed by Qualcomm Connected Experiences, Inc.,
#    with authorization from the AllSeen Alliance, Inc.
#    
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#    
#        http://www.apache.org/licenses/LICENSE-2.0
#    
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#    
#    Pursuant to Section 1 of the License, the work of authorship constituting
#    a Work and any Contribution incorporated in the Work shall mean only that
#    Contributor's code submissions authored by that Contributor.  Any rights
#    granted under the License are conditioned upon acceptance of these
#    clarifications.
#
import sys

class HttpControl:

    def __init__(self, generated, url) :
        self.generated = generated
        self.url = url
        self.name = generated.unitName + "HttpControl"
        
    def generate(self) :
        self.generated.varDecl += """    static ajn::services::HttpControl* {0};\n""".format(self.name)
        self.generated.varDef += """HttpControl* ControlPanelGenerated::{0} = 0;\n""".format(self.name)

        self.generated.initCode += """\n    {0} = new HttpControl("{1}");\n""".format(self.name, self.url)
        self.generated.initCode += """    CHECK({0}->setHttpControl({1}));\n""".format(self.generated.unitObject, self.name)

        self.generated.shutdown += """    if ({0}) {1}\n        delete ({0});\n        {0} = 0;\n    {2}\n""".format(self.name, "{", "}")

