/*
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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
package org.allseen.lsf.sdk;


/**
 * This class contains all pertinent information for errors that occur in the Lighting
 * system. This class provides an interface to retrieve the following data: the name of
 * the error, the response code returned by the Lighting operation, the ID of the Lighting
 * item for which the error occured, the tracking ID only if the error occurred during
 * creation, and an array of error codes if the error occurred in the controller.
 */
public class LightingItemErrorEvent {
    /**
     * The name of the error.
     */
    public String name;

    /**
     * The response code of the error.
     */
    public ResponseCode responseCode;

    /**
     * The ID of the Lighting item.
     */
    public String itemID;

    /**
     * The tracking ID of the Lighting item.
     */
    public TrackingID trackingID;

    /**
     * Array of error codes.
     */
    public ErrorCode[] errorCodes;

    /**
     * Constructs a LightingItemErrorEvent object.
     *
     * @param name The name of the error.
     * @param responseCode The response code of the error.
     * @param itemID The ID of the Lighting item.
     * @param trackingID The tracking ID of the Lighting Object.
     * @param errorCodes Array of ErrorCodes.
     */
    public LightingItemErrorEvent(String name, ResponseCode responseCode, String itemID, TrackingID trackingID, ErrorCode[] errorCodes) {
        this.name = name;
        this.responseCode = responseCode;
        this.itemID = itemID;
        this.trackingID = trackingID;
        this.errorCodes = errorCodes;
    }
}
