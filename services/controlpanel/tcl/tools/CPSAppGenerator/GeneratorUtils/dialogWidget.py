# Copyright (c) 2013 - 2014, AllSeen Alliance. All rights reserved.
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

class Dialog (common.Widget):

    def __init__(self, generated, dialogElement, parentObjectPath, languageSetName, isRoot = 0) :
        common.Widget.__init__(self, generated, dialogElement, parentObjectPath, languageSetName)
        self.widgetName = "DialogWidget"
        self.widgetType = "WIDGET_TYPE_DIALOG"
        self.nonSecuredInterfaceName = "DialogInterfaces"
        self.securedInterfaceName = "SecuredDialogInterfaces"
        self.hintPrefix = "DIALOG_HINT_"
        self.executeCases = ""
        if isRoot:
            self.objectPathSuffix = ""  

    def generate(self) :
        common.Widget.generate(self)
        self.generateOnAction()

    def generateDefines(self, capName) :
        common.Widget.generateDefines(self, capName) 
        self.generated.defines += "#define {0}_MESSAGE_PROPERTY           AJ_APP_PROPERTY_ID({1} + NUM_PRECEDING_OBJECTS, 1, 4)\n".format(capName, self.generated.definesIndx)
        self.generated.defines += "#define {0}_NUM_ACTIONS_PROPERTY       AJ_APP_PROPERTY_ID({1} + NUM_PRECEDING_OBJECTS, 1, 5)\n".format(capName, self.generated.definesIndx)
        self.generated.defines += "#define {0}_EXEC_ACTION1               AJ_APP_MESSAGE_ID({1} + NUM_PRECEDING_OBJECTS, 1, 6)\n".format(capName, self.generated.definesIndx)
        self.generated.defines += "#define {0}_EXEC_ACTION2               AJ_APP_MESSAGE_ID({1} + NUM_PRECEDING_OBJECTS, 1, 7)\n".format(capName, self.generated.definesIndx)
        self.generated.defines += "#define {0}_EXEC_ACTION3               AJ_APP_MESSAGE_ID({1} + NUM_PRECEDING_OBJECTS, 1, 8)\n".format(capName, self.generated.definesIndx)

        self.generated.actionCases += "case {0}_EXEC_ACTION1: \\\n".format(capName)
        self.generated.actionCases += "case {0}_EXEC_ACTION2: \\\n".format(capName)
        self.generated.actionCases += "case {0}_EXEC_ACTION3: \\\n".format(capName)

        self.executeCases += "    case {0}_EXEC_ACTION{1}:\n".format(capName, '{0}') 

    def generateTests(self, capName) : 
        common.Widget.generateTests(self, capName) 
        self.generated.initTests += """    testsToRun[{1}].msgId = {0}_EXEC_ACTION1;
    testsToRun[{1}].numParams = 0;\n""".format(capName, self.generated.numTests, self.generated.definesIndx - 1)
        self.generated.numTests = self.generated.numTests + 1
        self.generated.allReplies += "case AJ_REPLY_ID({0}_EXEC_ACTION1): \\\n".format(capName)

        self.generated.initTests += """    testsToRun[{1}].msgId = {0}_EXEC_ACTION2;
    testsToRun[{1}].numParams = 0;\n""".format(capName, self.generated.numTests, self.generated.definesIndx - 1)
        self.generated.numTests = self.generated.numTests + 1
        self.generated.allReplies += "case AJ_REPLY_ID({0}_EXEC_ACTION2): \\\n".format(capName)

        self.generated.initTests += """    testsToRun[{1}].msgId = {0}_EXEC_ACTION3;
    testsToRun[{1}].numParams = 0;\n""".format(capName, self.generated.numTests, self.generated.definesIndx - 1)
        self.generated.numTests = self.generated.numTests + 1
        self.generated.allReplies += "case AJ_REPLY_ID({0}_EXEC_ACTION3): \\\n".format(capName)

    def generateMandatoryVariables (self) :
        self.generated.initFunction  += "    initializeDialogWidget(&{0});\n".format(self.name)
        self.setNumLanguages()
        self.setEnabled()
        self.setMessage()
        self.setNumActions() 
        self.generated.initFunction += "\n"

    def setNumActions (self) :
        self.generated.initFunction += "    {0}.numActions = {1};\n".format(self.name, len(self.element.button))

    def generateOnAction (self) :

        error = "AJ_MarshalErrorMsg(msg, &reply, AJ_ErrServiceUnknown);"
        for i in range(0, len(self.element.button)):
            self.generated.executeAction += self.executeCases.format(str(i+1)) + "        {\n"
            self.generated.executeAction += """            {0}\n        {1}\n        break;\n\n""".format(self.element.button[i].executeCode, "}")
            self.setLabelAction(i)
        for i in range(len(self.element.button), 3):    
            self.generated.executeAction += self.executeCases.format(str(i+1)) + "        {0}\n".format("{")    
            self.generated.executeAction += """            {0}\n        {1}\n        break;\n\n""".format(error, "}")

