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
import xml.etree.ElementTree as xml
import commonWidget as common
import dialogWidget as dw

class Action (common.Widget):

    def __init__(self, generated, actionElement, parentObjectPath, languageSetName) :
        common.Widget.__init__(self, generated, actionElement, parentObjectPath, languageSetName)
        if hasattr(self.element.onAction, "executeCode") : 
            self.widgetName = self.name[:1].upper() + self.name [1:]
        else :
            self.widgetName = "ActionWithDialog"

    def generate(self) :
        common.Widget.generate(self)
        self.generateOnAction()

    def generateOnAction (self) :
        onAction = self.element.onAction
        if hasattr(onAction, "executeCode") : 
            actionHeaderFile = self.generated.actionHeaderFile
            actionSrcFile = self.generated.actionSrcFile

            regularName = self.widgetName
            capitalName = self.name.upper()

            actionHeaderFile = actionHeaderFile.replace("CAPITAL_NAME_HERE", capitalName)
            actionHeaderFile = actionHeaderFile.replace("REGULAR_NAME_HERE", regularName)

            actionSrcFile = actionSrcFile.replace("CAPITAL_NAME_HERE", capitalName)
            actionSrcFile = actionSrcFile.replace("REGULAR_NAME_HERE", regularName)
            actionSrcFile = actionSrcFile.replace("ADDITIONAL_INCLUDES_HERE", self.generated.srcIncludes)
            actionSrcFile = actionSrcFile.replace("EXECUTE_ACTION_HERE", onAction.executeCode)

            self.generated.headerIncludes += self.generateHeaderInclude()

            genH = open(self.generated.path + "/" + regularName + ".h", 'w')
            genH.write(actionHeaderFile)
            genH.close()
            genC = open(self.generated.path + "/" + regularName + ".cc", 'w')
            genC.write(actionSrcFile)
            genC.close()

        elif hasattr(onAction, "dialog") : 
            dialog = dw.Dialog(self.generated, onAction.dialog, self.name, self.languageSetName)
            dialog.generate()

