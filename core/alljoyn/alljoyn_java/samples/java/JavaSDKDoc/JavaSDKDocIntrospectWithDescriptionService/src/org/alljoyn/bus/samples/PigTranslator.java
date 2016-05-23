/*
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Contributed by Qualcomm Connected Experiences, Inc.,
 *    with authorization from the AllSeen Alliance, Inc.
 *    
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *    
 *        http://www.apache.org/licenses/LICENSE-2.0
 *    
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *    
 *    Pursuant to Section 1 of the License, the work of authorship constituting
 *    a Work and any Contribution incorporated in the Work shall mean only that
 *    Contributor's code submissions authored by that Contributor.  Any rights
 *    granted under the License are conditioned upon acceptance of these
 *    clarifications.
 */

package org.alljoyn.bus.samples;

import org.alljoyn.bus.Translator;

public class PigTranslator extends Translator {

    public int numTargetLanguages(){
        return 1;
    }

    public String getTargetLanguage(int index){
        if(0 == index) {
            return "pig";
        } else {
            return null;
        }
    }

    public String translate(String fromLanguage, String toLanguage, String fromText){
        if(toLanguage.equals("en") || null == fromText) {
            return null;
        }

        StringBuilder res = new StringBuilder();
        String lower = fromText.toLowerCase();

        for(String word : lower.split("\\s", 0)){
            if(word.charAt(0) < 'a' || word.charAt(0) > 'z' || word.length() == 1) {
                res.append(word);
                res.append(' ');
                continue;
            }

            String firstTwoChars = word.substring(0, 2);
            int cutAt = 1;
            if(firstTwoChars.equals("sh") || firstTwoChars.equals("ch") ||
                    firstTwoChars.equals("th") || firstTwoChars.equals("ph") ||
                    firstTwoChars.equals("wh") || firstTwoChars.equals("kn") ||
                    firstTwoChars.equals("tr")){
                cutAt = 2;
            }

            res.append(word.substring(cutAt));
            res.append(word.substring(0, cutAt));
            res.append("ay ");
        }

        res.setLength(res.length() - 1);

        return res.toString();
    }
}
