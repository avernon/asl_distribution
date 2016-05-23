# Copyright (c) 2013 -2014, AllSeen Alliance. All rights reserved.
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
import xml.etree.ElementTree as xml
import commonWidget as common
import dialogWidget as dw

class Action (common.Widget):

    def __init__(self, generated, actionElement, parentObjectPath, languageSetName) :
        common.Widget.__init__(self, generated, actionElement, parentObjectPath, languageSetName)
        self.widgetName = "ActionWidget"
        self.widgetType = "WIDGET_TYPE_ACTION"
        self.nonSecuredInterfaceName = "ActionInterfaces"
        self.securedInterfaceName = "SecuredActionInterfaces"
        self.hintPrefix = "ACTION_WIDGET_HINT_"
        self.executeCases = ""

    def generate(self) :
        common.Widget.generate(self)
        self.generateOnAction()

    def generateDefines(self, capName) :
        common.Widget.generateDefines(self, capName) 
        self.generated.defines += "#define {0}_EXEC                       AJ_APP_MESSAGE_ID({1} + NUM_PRECEDING_OBJECTS, 1, 4)\n".format(capName, self.generated.definesIndx)
        self.generated.actionCases += "case {0}_EXEC: \\\n".format(capName)
        self.executeCases += "    case {0}_EXEC:\n".format(capName) 

    def generateTests(self, capName) : 
        common.Widget.generateTests(self, capName) 
        self.generated.initTests += """    testsToRun[{1}].msgId = {0}_EXEC;
    testsToRun[{1}].numParams = 0;\n""".format(capName, self.generated.numTests, self.generated.definesIndx - 1)
        self.generated.numTests = self.generated.numTests + 1
        self.generated.allReplies += "case AJ_REPLY_ID({0}_EXEC): \\\n".format(capName)

    def generateOnAction (self) :
        onAction = self.element.onAction
        if hasattr(onAction, "executeCode") : 
            self.generated.executeAction += self.executeCases + "        {0}\n".format("{")    
            self.generated.executeAction += "            {0}\n        {1}\n        break;\n\n".format(onAction.executeCode, "}")
        elif hasattr(onAction, "dialog") : 
            dialogElem = onAction.dialog
            dialog = dw.Dialog(self.generated, dialogElem, (self.parentObjectPath + self.objectPathSuffix), self.languageSetName)
            dialog.generate()




