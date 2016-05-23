/**
 * @file
 * This implements the SecurityApplicationObj class
 */
/******************************************************************************
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
 ******************************************************************************/

#include <alljoyn/Status.h>
#include <alljoyn/AllJoynStd.h>
#include "KeyInfoHelper.h"
#include "SecurityApplicationObj.h"

#define QCC_MODULE "ALLJOYN_SECURITY"

using namespace qcc;
namespace ajn {

const uint16_t SecurityApplicationObj::APPLICATION_VERSION = 1;
const uint16_t SecurityApplicationObj::SECURITY_APPLICATION_VERSION = 1;
const uint16_t SecurityApplicationObj::SECURITY_CLAIMABLE_APPLICATION_VERSION = 1;
const uint16_t SecurityApplicationObj::SECURITY_MANAGED_APPLICATION_VERSION = 1;


SecurityApplicationObj::SecurityApplicationObj(BusAttachment& bus) :
    PermissionMgmtObj(bus, org::alljoyn::Bus::Security::ObjectPath)
{
}

QStatus SecurityApplicationObj::Init()
{
    QStatus status = ER_OK;
    {
        /* Add org.alljoyn.Bus.Application interface */
        const InterfaceDescription* ifc = bus.GetInterface(org::alljoyn::Bus::Application::InterfaceName);
        if (ifc == NULL) {
            QCC_LogError(status, ("Failed to get the %s interface", org::alljoyn::Bus::Application::InterfaceName));
            return ER_BUS_INTERFACE_MISSING;
        }
        status = AddInterface(*ifc);
        if (ER_OK != status) {
            QCC_LogError(status, ("Failed to add the %s interface", org::alljoyn::Bus::Application::InterfaceName));
            return status;
        }
    }
    {
        /* Add org.alljoyn.Bus.Security.Application interface */
        const InterfaceDescription* ifc = bus.GetInterface(org::alljoyn::Bus::Security::Application::InterfaceName);
        if (ifc == NULL) {
            QCC_LogError(status, ("Failed to get the %s interface", org::alljoyn::Bus::Security::Application::InterfaceName));
            return ER_BUS_INTERFACE_MISSING;
        }
        status = AddInterface(*ifc);
        if (ER_OK != status) {
            QCC_LogError(status, ("Failed to add the %s interface", org::alljoyn::Bus::Security::Application::InterfaceName));
        }
    }
    {
        /* Add org.alljoyn.Bus.Security.ClaimableApplication interface */
        const InterfaceDescription* ifc = bus.GetInterface(org::alljoyn::Bus::Security::ClaimableApplication::InterfaceName);
        if (ifc == NULL) {
            QCC_LogError(status, ("Failed to get the %s interface", org::alljoyn::Bus::Security::ClaimableApplication::InterfaceName));
            return ER_BUS_INTERFACE_MISSING;
        }
        status = AddInterface(*ifc);
        if (ER_OK != status) {
            QCC_LogError(status, ("Failed to add the %s interface", org::alljoyn::Bus::Security::Application::InterfaceName));
            return status;
        }
        status = AddMethodHandler(ifc->GetMember("Claim"), static_cast<MessageReceiver::MethodHandler>(&SecurityApplicationObj::Claim));
        if (ER_OK != status) {
            QCC_LogError(status, ("Failed to add method handler for  %s.Claim", org::alljoyn::Bus::Security::ClaimableApplication::InterfaceName));
            return status;
        }
    }
    {
        /* Add org.alljoyn.Bus.Security.ManagedApplication interface */
        const InterfaceDescription* ifc = bus.GetInterface(org::alljoyn::Bus::Security::ManagedApplication::InterfaceName);
        if (ifc == NULL) {
            QCC_LogError(status, ("Failed to get the %s interface", org::alljoyn::Bus::Security::ManagedApplication::InterfaceName));
            return ER_BUS_INTERFACE_MISSING;
        }
        status = AddInterface(*ifc);
        if (ER_OK != status) {
            QCC_LogError(status, ("Failed to add the %s interface", org::alljoyn::Bus::Security::ManagedApplication::InterfaceName));
            return status;
        }
        status = AddMethodHandler(ifc->GetMember("Reset"), static_cast<MessageReceiver::MethodHandler>(&SecurityApplicationObj::Reset));
        if (ER_OK != status) {
            QCC_LogError(status, ("Failed to add method handler for  %s.Reset", org::alljoyn::Bus::Security::ManagedApplication::InterfaceName));
            return status;
        }
        status = AddMethodHandler(ifc->GetMember("UpdateIdentity"), static_cast<MessageReceiver::MethodHandler>(&SecurityApplicationObj::UpdateIdentity));
        if (ER_OK != status) {
            QCC_LogError(status, ("Failed to add method handler for  %s.UpdateIdentity", org::alljoyn::Bus::Security::ManagedApplication::InterfaceName));
            return status;
        }
        status = AddMethodHandler(ifc->GetMember("UpdatePolicy"), static_cast<MessageReceiver::MethodHandler>(&SecurityApplicationObj::UpdatePolicy));
        if (ER_OK != status) {
            QCC_LogError(status, ("Failed to add method handler for  %s.UpdatePolicy", org::alljoyn::Bus::Security::ManagedApplication::InterfaceName));
            return status;
        }
        status = AddMethodHandler(ifc->GetMember("ResetPolicy"), static_cast<MessageReceiver::MethodHandler>(&SecurityApplicationObj::ResetPolicy));
        if (ER_OK != status) {
            QCC_LogError(status, ("Failed to add method handler for  %s.ResetPolicy", org::alljoyn::Bus::Security::ManagedApplication::InterfaceName));
            return status;
        }
        status = AddMethodHandler(ifc->GetMember("InstallMembership"), static_cast<MessageReceiver::MethodHandler>(&SecurityApplicationObj::InstallMembership));
        if (ER_OK != status) {
            QCC_LogError(status, ("Failed to add method handler for  %s.InstallMembership", org::alljoyn::Bus::Security::ManagedApplication::InterfaceName));
            return status;
        }
        status = AddMethodHandler(ifc->GetMember("RemoveMembership"), static_cast<MessageReceiver::MethodHandler>(&SecurityApplicationObj::RemoveMembership));
        if (ER_OK != status) {
            QCC_LogError(status, ("Failed to add method handler for  %s.RemoveMembership", org::alljoyn::Bus::Security::ManagedApplication::InterfaceName));
            return status;
        }
    }
    if (ER_OK == status) {
        status = PermissionMgmtObj::Init();
    }
    return status;
}

QStatus SecurityApplicationObj::State(const qcc::KeyInfoNISTP256& publicKeyInfo, PermissionConfigurator::ApplicationState state)
{
    QCC_DbgTrace(("SecurityApplication::%s", __FUNCTION__));
    QStatus status = ER_OK;
    const InterfaceDescription* ifc = bus.GetInterface(org::alljoyn::Bus::Application::InterfaceName);
    if (!ifc) {
        return ER_BUS_INTERFACE_MISSING;
    }

    const ajn::InterfaceDescription::Member* stateSignalMember = ifc->GetMember("State");
    assert(stateSignalMember);

    size_t stateArgsSize = 2;
    MsgArg stateArgs[2];
    KeyInfoHelper::KeyInfoNISTP256PubKeyToMsgArg(publicKeyInfo, stateArgs[0]);
    status = stateArgs[1].Set("q", static_cast<uint16_t>(state));
    if (status != ER_OK) {
        QCC_DbgPrintf(("SecurityApplication::%s Failed to set state arguments %s", __FUNCTION__, QCC_StatusText(status)));
        return status;
    }

    status = Signal(NULL, 0, *stateSignalMember, stateArgs, stateArgsSize, 0, ALLJOYN_FLAG_SESSIONLESS);
    QCC_DbgPrintf(("Sent org.alljoyn.Bus.Application.State signal from %s  = %s", bus.GetUniqueName().c_str(), QCC_StatusText(status)));

    return status;
}

void SecurityApplicationObj::Claim(const ajn::InterfaceDescription::Member* member, ajn::Message& msg)
{
    QCC_DbgTrace(("SecurityApplicationObj::%s", __FUNCTION__));
    PermissionMgmtObj::Claim(member, msg);
}

void SecurityApplicationObj::Reset(const ajn::InterfaceDescription::Member* member, ajn::Message& msg)
{
    QCC_DbgTrace(("SecurityApplicationObj::%s", __FUNCTION__));
    PermissionMgmtObj::Reset(member, msg);
}

void SecurityApplicationObj::UpdateIdentity(const ajn::InterfaceDescription::Member* member, ajn::Message& msg)
{
    QCC_DbgTrace(("SecurityApplicationObj::%s", __FUNCTION__));
    InstallIdentity(member, msg);
}

void SecurityApplicationObj::UpdatePolicy(const ajn::InterfaceDescription::Member* member, ajn::Message& msg)
{
    QCC_DbgTrace(("SecurityApplicationObj::%s", __FUNCTION__));
    InstallPolicy(member, msg);
}

void SecurityApplicationObj::ResetPolicy(const ajn::InterfaceDescription::Member* member, ajn::Message& msg)
{
    QCC_DbgTrace(("SecurityApplicationObj::%s", __FUNCTION__));
    PermissionMgmtObj::ResetPolicy(member, msg);
}

void SecurityApplicationObj::InstallMembership(const ajn::InterfaceDescription::Member* member, ajn::Message& msg)
{
    QCC_DbgTrace(("SecurityApplicationObj::%s", __FUNCTION__));
    PermissionMgmtObj::InstallMembership(member, msg);
}

void SecurityApplicationObj::RemoveMembership(const ajn::InterfaceDescription::Member* member, ajn::Message& msg)
{
    QCC_DbgTrace(("SecurityApplicationObj::%s", __FUNCTION__));
    PermissionMgmtObj::RemoveMembership(member, msg);
}

QStatus SecurityApplicationObj::Get(const char* ifcName, const char* propName, MsgArg& val)
{
    QCC_DbgTrace(("SecurityApplicationObj::%s", __FUNCTION__));
    QStatus status = ER_BUS_NO_SUCH_PROPERTY;
    if (0 == strcmp(org::alljoyn::Bus::Security::Application::InterfaceName, ifcName)) {
        if (0 == strcmp("Version", propName)) {
            status = val.Set("q", SecurityApplicationObj::SECURITY_APPLICATION_VERSION);
        } else if (0 == strcmp("ApplicationState", propName)) {
            status = val.Set("q", applicationState);
        } else if (0 == strcmp("ManifestTemplateDigest", propName)) {
            status = GetManifestTemplateDigest(val);
            if (ER_MANIFEST_NOT_FOUND == status) {
                status = val.Set("(yay)", qcc::SigInfo::ALGORITHM_ECDSA_SHA_256, 0, NULL);
            }
        } else if (0 == strcmp("EccPublicKey", propName)) {
            KeyInfoNISTP256 keyInfo;
            status = GetPublicKey(keyInfo);
            if (status == ER_OK) {
                KeyInfoHelper::KeyInfoNISTP256PubKeyToMsgArg(keyInfo, val);
            }
        } else if (0 == strcmp("ManufacturerCertificate", propName)) {
            status = val.Set("a(yay)", 0, NULL); /* Currently there is no
                                                    support for manufacturer certificate yet */
        } else if (0 == strcmp("ManifestTemplate", propName)) {
            status = GetManifestTemplate(val);
            if (ER_MANIFEST_NOT_FOUND == status) {
                status = val.Set("a(ssa(syy))", 0, NULL);
            }
        } else if (0 == strcmp("ClaimCapabilities", propName)) {
            status = val.Set("q", claimCapabilities);
        } else if (0 == strcmp("ClaimCapabilityAdditionalInfo", propName)) {
            status = val.Set("q", claimCapabilityAdditionalInfo);
        }
    } else if (0 == strcmp(org::alljoyn::Bus::Security::ManagedApplication::InterfaceName, ifcName)) {
        if (0 == strcmp("Version", propName)) {
            status = val.Set("q", SecurityApplicationObj::SECURITY_MANAGED_APPLICATION_VERSION);
        } else if (0 == strcmp("Identity", propName)) {
            status = GetIdentity(val);
        } else if (0 == strcmp("Manifest", propName)) {
            PermissionPolicy::Rule* manifest = NULL;
            size_t manifestSize = 0;
            /* retrieve the size of the manifest */
            status = RetrieveManifest(NULL, &manifestSize);
            if (ER_OK != status) {
                if (ER_MANIFEST_NOT_FOUND == status) {
                    status = val.Set("a(ssa(syy))", 0, NULL);
                }
            } else {
                if (manifestSize > 0) {
                    manifest = new PermissionPolicy::Rule[manifestSize];
                }
                status = RetrieveManifest(manifest, &manifestSize);
                if (ER_OK != status) {
                    delete [] manifest;
                    if (ER_MANIFEST_NOT_FOUND == status) {
                        status = val.Set("a(ssa(syy))", 0, NULL);
                    }
                } else {
                    status = PermissionPolicy::GenerateRules(manifest, manifestSize, val);
                    delete [] manifest;
                }
            }
        } else if (0 == strcmp("IdentityCertificateId", propName)) {
            qcc::String serial;
            KeyInfoNISTP256 keyInfo;
            status = RetrieveIdentityCertificateId(serial, keyInfo);
            if ((ER_OK == status) || (ER_CERTIFICATE_NOT_FOUND == status)) {
                size_t coordSize = keyInfo.GetPublicKey()->GetCoordinateSize();
                uint8_t* xData = new uint8_t[coordSize];
                uint8_t* yData = new uint8_t[coordSize];
                KeyInfoHelper::ExportCoordinates(*keyInfo.GetPublicKey(), xData, coordSize, yData, coordSize);

                status = val.Set("(ayay(yyayay))",
                                 serial.size(), serial.data(),
                                 keyInfo.GetKeyIdLen(), keyInfo.GetKeyId(),
                                 keyInfo.GetAlgorithm(), keyInfo.GetCurve(),
                                 coordSize, xData, coordSize, yData);
                if (ER_OK == status) {
                    val.Stabilize();
                }
                delete [] xData;
                delete [] yData;
            }
        } else if (0 == strcmp("PolicyVersion", propName)) {
            status = val.Set("u", policyVersion);;
        } else if (0 == strcmp("Policy", propName)) {
            status = GetPolicy(val);
        } else if (0 == strcmp("DefaultPolicy", propName)) {
            status = GetDefaultPolicy(val);
        } else if (0 == strcmp("MembershipSummaries", propName)) {
            status = GetMembershipSummaries(val);
        }
    } else if (0 == strcmp(org::alljoyn::Bus::Application::InterfaceName, ifcName)) {
        if (0 == strcmp("Version", propName)) {
            status = val.Set("q", SecurityApplicationObj::APPLICATION_VERSION);
        }
    } else if (0 == strcmp(org::alljoyn::Bus::Security::ClaimableApplication::InterfaceName, ifcName)) {
        if (0 == strcmp("Version", propName)) {
            status = val.Set("q", SecurityApplicationObj::SECURITY_CLAIMABLE_APPLICATION_VERSION);
        }
    }
    return status;
}

} //namespace ajn
