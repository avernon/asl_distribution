/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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
 ******************************************************************************/

#ifndef GATEWAYCTRLCONSTANTS_H_
#define GATEWAYCTRLCONSTANTS_H_

#import <qcc/String.h>

@interface AJGWCConstants : NSObject

/**
 * The prefix for all the gateway interface names
 */
static NSString* const IFACE_PREFIX = "org.alljoyn.gwagent.ctrl";

/**
 * Port number to connect to a Gateway Configuration Manager
 */
static const uint16_t GATEWAYSERVICE_PORT = 1020;

static NSString* const AJ_OBJECTPATH_PREFIX = "/gw";
static NSString* const AJ_GATEWAYCONTROLLER_APPMGMT_INTERFACE = "org.alljoyn.gwagent.ctrl.AppMgmt";
static NSString* const AJ_GATEWAYCONTROLLERAPP_INTERFACE = "org.alljoyn.gwagent.ctrl.App";

static NSString* const AJ_PROPERTY_VERSION = "Version";

static NSString* const AJ_SIGNAL_APPSTATUSCHANGED = "AppStatusSignal";

static NSString* const AJ_METHOD_GETINSTALLEDAPPS = "GetInstalledApps";
static NSString* const AJ_METHOD_GETMANIFESTFILE = "GetManifestFile";
static NSString* const AJ_METHOD_GETMANIFESTINTERFACES = "GetManifestInterfaces";
static NSString* const AJ_METHOD_GETAPPSTATUS = "GetAppStatus";
static NSString* const AJ_METHOD_RESTARTAPP = "RestartApp";

static NSString* const AJ_GATEWAYCONTROLLER_ACLMGMT_INTERFACE = "org.alljoyn.gwagent.ctrl.AclMgmt";
static NSString* const AJ_METHOD_CREATEACL = "CreateAcl";
static NSString* const AJ_METHOD_DELETEACL = "DeleteAcl";
static NSString* const AJ_METHOD_LISTACLS = "ListAcls";

static NSString* const AJ_GATEWAYCONTROLLERACL_INTERFACE = "org.alljoyn.gwagent.ctrl.Acl";
static NSString* const AJ_METHOD_ACTIVATEACL = "ActivateAcl";
static NSString* const AJ_METHOD_DEACTIVATEACL = "DeactivateAcl";
static NSString* const AJ_METHOD_GETACL = "GetAcl";
static NSString* const AJ_METHOD_GETACLSTATUS = "GetAclStatus";
static NSString* const AJ_METHOD_UPDATEACL = "UpdateAcl";
static NSString* const AJ_METHOD_UPDATEACLMETADATA = "UpdateAclMetadata";

static NSString* const AJPARAM_EMPTY = "";
static NSString* const AJPARAM_VAR = "v";
static NSString* const AJPARAM_STR = "s";
static NSString* const AJPARAM_BOOL = "b";
static NSString* const AJPARAM_UINT16 = "q";
static NSString* const AJPARAM_INT16 = "n";
static NSString* const AJPARAM_UINT32 = "u";
static NSString* const AJPARAM_INT32 = "i";
static NSString* const AJPARAM_UINT64 = "t";
static NSString* const AJPARAM_INT64 = "x";
static NSString* const AJPARAM_DOUBLE = "d";

/**
 * Suffix of the application name that is sent with the ACL metadata
 */
static NSString* const AJSUFFIX_APP_NAME = "_APP_NAME";

/**
 * Suffix of the device name that is sent with the ACL metadata
 */
static NSString* const AJSUFFIX_DEVICE_NAME = "_DEVICE_NAME";


@end

