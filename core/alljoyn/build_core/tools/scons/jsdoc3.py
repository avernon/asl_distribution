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
import SCons.Builder
import SCons.Action
import os
def _jsdoc3_scanner(node, env, path):
    source = []
    # walk the JSDOC_TEMPLATE dir and add the files in the demplate dir to the
    # source list.  This way documentation will be rebuilt if a template file is
    # modified
    template_dir = env.Dir('$JSDOC_TEMPLATE')
    for root, dir, filenames in os.walk(str(template_dir)):
        for f in filenames:
            source.append(os.path.abspath(os.path.join(root, f)))
    return source

def _jsdoc3_emitter(target, source, env):
    if len(target) > 1:
        print('scons: *** Only one target may be specified for the jsdoc3 Builder.')
        exit(1)
    if type(target[0]) != SCons.Node.FS.Dir:
        print('scons: *** Target MUST be a Dir node.')
        exit(1);
    outputDir = target[0];
    # SCons considers directory nodes upto date if they exist. Past the
    # fist run of the script the directory exist preventing it from
    # generating a dependency graph on subsiquent runs. By adding a file
    # to the targets we are able to workaround this issue. Since index.html
    # is always updated with the build date it was chosen.
    target[0] = env.File(str(target[0]) + '/index.html')
    # make sure the output directory is cleaned.
    env.Clean(env.File(source), outputDir)
    return target, source

def generate(env):
    jsdoc3_scanner = env.Scanner(name = 'jsdoc3_scanner',
                                  function = _jsdoc3_scanner)

    _jsdoc3_action = SCons.Action.Action('${JSDOCCOM}', '${JSDOCCOMSTR}')

    _jsdoc3_builder = SCons.Builder.Builder(
        action ='jsdoc ${JSDOC_FLAGS} -t ${JSDOC_TEMPLATE} -d ${TARGET.dir} ${SOURCES}',
        src_suffix = '$JSDOC_SUFFIX',
        emitter = _jsdoc3_emitter,
        source_scanner = jsdoc3_scanner
    )

    env.Append(BUILDERS = {
        'jsdoc3': _jsdoc3_builder,
    })

    env.AppendUnique(
        JSDOCCOM = 'jsdoc ${JSDOC_FLAGS} -t ${JSDOC_TEMPLATE} -d ${TARGET.dir} ${SOURCES}',
        JSDOCCOMSTR = '${JSDOCCOM}',
        # Suffixes/prefixes
        JSDOC_SUFFIX = '.js',
        # JSDoc 2 build flags
        JSDOC_FLAGS = '',
        # directory containing the publish.js and other template files.
        JSDOC_TEMPLATE = env.Dir('templates')
    )

def exists(env):
    """
    Make sure jsDoc exists.
    """
    run_exists = env.Detect('jsdoc')
    return (java_exists and jsrun_exists and run_exists)
