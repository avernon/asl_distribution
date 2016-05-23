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

class Label (common.Widget):

    def __init__(self, generated, labelElement, parentObjectPath, languageSetName) :
        common.Widget.__init__(self, generated, labelElement, parentObjectPath, languageSetName)
        self.widgetName = "LabelWidget"
        self.widgetType = "WIDGET_TYPE_LABEL"
        self.nonSecuredInterfaceName = "LabelPropertyInterfaces"
        self.hintPrefix = "LABEL_HINT_"

    def generateDefines(self, capName) :
        common.Widget.generateDefines(self, capName) 
        self.generated.defines += "#define {0}_LABEL_PROPERTY             AJ_ENCODE_PROPERTY_ID(AJCPS_OBJECT_LIST_INDEX, {1}, 1, 4)\n".format(capName, self.generated.definesIndx)

    def generateIdentify(self, capName, language) :
        common.Widget.generateIdentify(self, capName, language)
        self.generated.identify += """    case {0}_LABEL_PROPERTY:
        *widgetType = WIDGET_TYPE_LABEL;
        *propType = PROPERTY_TYPE_LABEL;
        *language = {2};
        return &{1};\n\n""".format(capName, self.name, language)

    def generateMandatoryVariables (self) :
        self.generated.initFunction  += "    initializeLabelWidget(&{0});\n".format(self.name)
        self.setNumLanguages()
        self.setEnabled()
        self.setLabel(1)
        self.generated.initFunction += "\n"

    def generateOptionalVariables (self) :
        self.setBgColor()
        self.setHints() 
    	

