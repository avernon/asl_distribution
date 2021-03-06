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

import sys
import subprocess
import glob
import os.path

def as_list(s):
    if isinstance(s, list): return s
    return [s]

class Generator:

    def __init__(self, scriptDir, path):
        self.scriptDir = scriptDir
        self.path = path
        self.languageSetsCode = ""
        self.headerIncludes = ""
        self.initCode = ""
        self.varDecl = ""
        self.varDef = ""
        self.shutdown = ""
        self.srcIncludes = ""
        self.units = {}

    def setControlDeviceData(self, unitName, headerCode) :
        self.unitName = unitName[:1].lower() + unitName[1:]
        self.unitObject = self.unitName + "Unit"
        if unitName in self.units :
            print >> sys.stderr, "\nERROR - an xml with unit name " + unitName + " has already been generated. When generating multiple xmls the unit names must be unique\n"
            sys.exit(3)
        self.units[unitName] = []

        self.ObjectPathPrefix = "/ControlPanel/" + unitName + "/"
        self.srcIncludes += headerCode + "\n"
        
        self.varDecl += """    static ajn::services::ControlPanelControlleeUnit* {0};\n\n""".format(self.unitObject)
        self.varDef += """ControlPanelControlleeUnit* ControlPanelGenerated::{0} = 0;\n""".format(self.unitObject)

        self.initCode += """\n    {0} = new ControlPanelControlleeUnit("{1}");\n""".format(self.unitObject, unitName)
        self.initCode += """    CHECK(controlPanelControllee->addControlPanelUnit({0}));\n""".format(self.unitObject)

        self.shutdown += """    if ({0}) {1}\n        delete ({0});\n        {0} = 0;\n    {2}\n""".format(self.unitObject, "{", "}")        

    def setLanguageSets(self, languageSet) :
        self.languageSets = {}    
        for langElement in languageSet:
            name = langElement.attr["name"]
            deviceLangName = self.unitName + langElement.attr["name"][:1].upper() + langElement.attr["name"][1:]
            self.languageSets[name] = []
            self.languageSetsCode += """    LanguageSet {0}("{0}");\n""".format(deviceLangName)
            languages = as_list(langElement.language)
            for language in languages :
                self.languageSets[name].append(language)
                self.languageSetsCode += """    {0}.addLanguage("{1}");\n""".format(deviceLangName, language.replace("-", "_"))
            self.languageSetsCode += """    LanguageSets::add({0}.getLanguageSetName(), {0});\n\n""".format(deviceLangName)    
    
    def addControlPanel(self, rootElement, languageSet) :
        name = self.unitName + rootElement.name[:1].upper() + rootElement.name[1:] + "ControlPanel"
        self.varDecl += """    static ajn::services::ControlPanel* {0};\n\n""".format(name)
        self.varDef += """ControlPanel* ControlPanelGenerated::{0} = 0;\n""".format(name)

        self.initCode += """\n    {0} = ControlPanel::createControlPanel(LanguageSets::get("{1}"));\n""".format(name, self.unitName + languageSet[:1].upper() + languageSet[1:])
        self.initCode += """    if (!{0})\n        return ER_FAIL;\n""".format(name)
        self.initCode += """    CHECK({0}->addControlPanel({1}));\n""".format(self.unitObject, name)

        self.shutdown += """    if ({0}) {1}\n        delete ({0});\n        {0} = 0;\n    {2}\n""".format(name, "{", "}")

    def addNotificationAction(self, rootElement, languageSet) :
        name = self.unitName + rootElement.name[:1].upper() + rootElement.name[1:] + "NotificationAction"
        self.varDecl += """    static ajn::services::NotificationAction* {0};\n\n""".format(name)
        self.varDef += """NotificationAction* ControlPanelGenerated::{0} = 0;\n""".format(name)

        self.initCode += """\n    {0} = NotificationAction::createNotificationAction(LanguageSets::get("{1}"));\n""".format(name, self.unitName + languageSet[:1].upper() + languageSet[1:])
        self.initCode += """    if (!{0})\n        return ER_FAIL;\n""".format(name)
        self.initCode += """    CHECK({0}->addNotificationAction({1}));\n""".format(self.unitObject, name)

        self.shutdown += """    if ({0}) {1}\n        delete ({0});\n        {0} = 0;\n    {2}\n""".format(name, "{", "}")

    def initializeFiles(self) :

        inputFile = open(self.scriptDir + '/PreGenFiles/PreGenControlPanelGenerated.h', 'r')
        self.genHeaderFile = inputFile.read()
        inputFile.close()

        inputFile = open(self.scriptDir + '/PreGenFiles/PreGenControlPanelGenerated.cc', 'r')
        self.genSrcFile = inputFile.read()
        inputFile.close()

        inputFile = open(self.scriptDir + '/PreGenFiles/PreGenActionImpl.h', 'r')
        self.actionHeaderFile = inputFile.read()
        inputFile.close()

        inputFile = open(self.scriptDir + '/PreGenFiles/PreGenActionImpl.cc', 'r')
        self.actionSrcFile = inputFile.read()
        inputFile.close()

        inputFile = open(self.scriptDir + '/PreGenFiles/PreGenDialogImpl.h', 'r')
        self.dialogHeaderFile = inputFile.read()
        inputFile.close()

        inputFile = open(self.scriptDir + '/PreGenFiles/PreGenDialogImpl.cc', 'r')
        self.dialogSrcFile = inputFile.read()
        inputFile.close()

        inputFile = open(self.scriptDir + '/PreGenFiles/PreGenPropertyImpl.h', 'r')
        self.propertyHeaderFile = inputFile.read()
        inputFile.close()

        inputFile = open(self.scriptDir + '/PreGenFiles/PreGenPropertyImpl.cc', 'r')
        self.propertySrcFile = inputFile.read()
        inputFile.close()


    def writeFiles(self) :

        genH = open(self.path + "/ControlPanelGenerated.h", 'w')
        genH.write(self.genHeaderFile)
        genH.close()

        genC = open(self.path + "/ControlPanelGenerated.cc", 'w')
        genC.write(self.genSrcFile)
        genC.close()


    def replaceInFiles(self) :

        self.genHeaderFile = self.genHeaderFile.replace("//VARIABLE_DECLARATIONS_GO_HERE", self.varDecl)
        self.genHeaderFile = self.genHeaderFile.replace("//NEW_WIDGET_CLASSES_HERE", self.headerIncludes)

        self.genSrcFile = self.genSrcFile.replace("//INCLUDES_GO_HERE", self.srcIncludes)
        self.genSrcFile = self.genSrcFile.replace("//STATIC_DECLARATION_HERE", self.varDef)
        self.genSrcFile = self.genSrcFile.replace("//LANGUAGESET_CODE_HERE", self.languageSetsCode)
        self.genSrcFile = self.genSrcFile.replace("//INITCODE_GO_HERE", self.initCode)
        self.genSrcFile = self.genSrcFile.replace("//SHUTDOWN_GO_HERE", self.shutdown)

    def confirmGenerate(self) :
        confirm = self.confirm()

        if confirm :
            if not os.path.exists(self.path):
                # The directory does not exist, so create and it and return
                # as there is nothing to remove
                os.makedirs(self.path)
                return

            filesToRemove = glob.glob(os.path.join(self.path, "*.h"))
            filesToRemove += glob.glob(os.path.join(self.path, "*.cc"))
            for f in filesToRemove:
                try:
                    os.remove(f)
                except OSError as detail:
                    print >> sys.stderr, "\nERROR - Could not delete the current generated files:", detail
                    sys.exit(4)
        else :
            print "\nStopping the generating process"
            sys.exit(0)   

    def confirm(self):
        default = False
        prompt = "\nGenerating this xml will cause previously generated files to be deleted. Do you wish to continue? (y/n) (Default is n): "
        while True:
            response = raw_input(prompt)
            if not response:
                return default
            if response not in ['y', 'Y', 'n', 'N']:
                print 'Please enter y or n.'
                continue
            if response.upper() == 'Y':
                return True
            if response.upper() == 'N':
                return False

