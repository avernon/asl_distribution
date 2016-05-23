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
 * Container class to hold information about an icon
 */
public class AboutIcon {
    /**
     * Max AllJoyn array length and the largest amount of bytes in an About Icon
     */
    public static final int MAX_CONTENT_LENGTH = 131072;

    /**
     * Set the content for an icon.  The content must fit into a MsgArg so the
     * largest size for the icon data is MAX_CONTENT_LENGTH bytes.
     *
     * Note as long as the MIME type matches it is possible to set both icon content
     * and icon URL
     *
     * If an error is returned the icon content will remain unchanged.
     *
     * @param mimeType a MIME type indicating the icon image type. Typical
     *                     value will be `image/jpeg` or `image/png`
     * @param content  an array of bytes that represent an icon
     *
     * @throws BusException if unable to create AboutIcon
     * <ul>
     *   <li>"MAX_CONTENT_LENGTH exceeded" if icon is too large</li>
     * </ul>
     */
    public AboutIcon(String mimeType, byte[] content) throws BusException {
        if (content.length > MAX_CONTENT_LENGTH) {
            throw new BusException("MAX_CONTENT_LENGTH exceeded");
        }
        m_mimeType = mimeType;
        m_content = content;
        m_url = "";
    }

    /**
     * Set a URL that contains the icon for the application.
     *
     * @param mimeType a MIME type indicating the icon image type. Typical
     *                     value will be `image/jpeg` or `image/png`
     * @param url      A URL that contains the location of the icon hosted in
     *                     the cloud.
     *
     * @throws BusException if unable to create AboutIcon
     */
    public AboutIcon(String mimeType, String url) throws BusException {
        m_mimeType = mimeType;
        m_content = null;
        m_url = url;
    }

    /**
     * Set the URL and content for an icon.  The content must fit into a MsgArg so the
     * largest size for the icon data is MAX_CONTENT_LENGTH bytes.
     *
     * Note the MIME type for the content and the URL must match
     *
     * If an error is returned the icon content will remain unchanged.
     *
     * @param mimeType a MIME type indicating the icon image type. Typical
     *                     value will be `image/jpeg` or `image/png`
     * @param url      A URL that contains the location of the icon hosted in
     *                 the cloud.
     * @param content  an array of bytes that represent an icon
     *
     * @throws BusException if unable to create AboutIcon
     * <ul>
     *   <li>"MAX_CONTENT_LENGTH exceeded" if icon is too large</li>
     * </ul>
     */
    public AboutIcon(String mimeType, String url, byte[] content) throws BusException {
        if (content.length > MAX_CONTENT_LENGTH) {
            throw new BusException("MAX_CONTENT_LENGTH exceeded.");
        }
        m_mimeType = mimeType;
        m_url = url;
        m_content = content;
    }

    /**
     * @return A string indicating the image MIME type
     */
    public String getMimeType() {
        return m_mimeType;
    }

    /**
     * @return A URL indicating the cloud location of the icon
     */
    public String getUrl() {
        return m_url;
    }

    /**
     * @return an array of bytes containing the binary content for the icon
     */
    public byte[] getContent() {
        return m_content;
    }

    /**
     * the mimetype of the image
     */
    private String m_mimeType;

    /**
     * The url for the Icon
     */
    private String m_url;

    /**
     * an array of bytes containing the image
     */
    private byte[] m_content;
}
