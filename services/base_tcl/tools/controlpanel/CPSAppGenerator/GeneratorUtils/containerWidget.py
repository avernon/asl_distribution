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
import propertyWidget as pw
import actionWidget as aw
import labelWidget as lw
import commonWidget as common

class Container (common.Widget):

    def __init__(self, generated, containerElement, parentObjectPath, languageSetName, isRoot = 0) :
        common.Widget.__init__(self, generated, containerElement, parentObjectPath, languageSetName)
        self.isRoot = isRoot
        self.widgetName = "ContainerWidget"
        self.widgetType = "WIDGET_TYPE_CONTAINER"
        self.securedInterfaceName = "SecuredContainerInterfaces"
        self.nonSecuredInterfaceName = "ContainerInterfaces"
        self.hintPrefix = "LAYOUT_HINT_"
        if isRoot:
            self.objectPathSuffix = ""  

    def generate(self) :
        common.Widget.generate(self)
        self.generateChildElements()

    def generateChildElements (self) :
        elements = self.element.elements.sub_nodes

        for element in elements:
            elementType = element._name
            self.generated.initFunction += "\n"

            if elementType == "action" :
                action = aw.Action(self.generated, element, (self.parentObjectPath + self.objectPathSuffix), self.languageSetName)
                action.generate()
            elif elementType == "container" :
                container = Container(self.generated, element, (self.parentObjectPath + self.objectPathSuffix), self.languageSetName)
                container.generate()
            elif elementType == "scalarProperty" or elementType == "stringProperty" or elementType == "booleanProperty" :
                propertyW = pw.Property(self.generated, element, (self.parentObjectPath + self.objectPathSuffix), self.languageSetName)
                propertyW.generate()
            elif elementType == "dateProperty" or elementType == "timeProperty" :
                propertyW = pw.Property(self.generated, element, (self.parentObjectPath + self.objectPathSuffix), self.languageSetName)
                propertyW.generate()
            elif elementType == "labelProperty" :
                label = lw.Label(self.generated, element, (self.parentObjectPath + self.objectPathSuffix), self.languageSetName)
                label.generate()
            else :
                print >> sys.stderr, "ERROR - This type is not supported. Exiting " + elementType
                sys.exit(3)




