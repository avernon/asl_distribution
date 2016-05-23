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

package org.alljoyn.bus;

/**
 */
public abstract class Translator {

    /**
     * Create native resources held by objects of this class.
     */
    public Translator() {
        create();
    }

    /**
     * Destroy native resources held by objects of this class.
     */
    protected void finalize() throws Throwable {
        try {
            destroy();
        } finally {
            super.finalize();
        }
    }

    /**
     * Create any native resources held by objects of this class.  Specifically,
     * we allocate a C++ counterpart of this Translator object.
     */
    private native void create();

    /**
     * Release any native resources held by objects of this class.
     * Specifically, we may delete a C++ counterpart of this Translator object.
     */
    private native void destroy();

    /**
     * Get the number of target languages this Translator supports
     *
     * @return numver of target languages
     */
    public abstract int numTargetLanguages();

    /**
     * Retrieve one of the list of target languages this Translator supports
     *
     * @param index the index of the requested target language within the list
     * @return The requested target language or null if index is out of bounds
     */
    public abstract String getTargetLanguage(int index);

    /**
     * Translate a string into another language
     *
     * @param fromLanguage the language to translate from
     * @param toLanguage the language to translate to
     * @param fromText the text to be translated
     * @return the translated text or null if it can not be translated
     */
    public abstract String translate(String fromLanguage, String toLanguage, String fromText);

    /**
     * The opaque pointer to the underlying C++ object which is actually tied
     * to the AllJoyn code.
     */
    private long handle = 0;
}
