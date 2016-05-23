/**
 * @file
 * This file defines the implementation of the Permission Configurator to allow app to setup some permission templates.
 */

/******************************************************************************
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
 ******************************************************************************/

#include <qcc/CryptoECC.h>
#include <qcc/KeyInfoECC.h>
#include <qcc/StringUtil.h>
#include "PermissionConfiguratorImpl.h"
#include "PermissionMgmtObj.h"
#include "BusInternal.h"
#include "CredentialAccessor.h"
#include "KeyInfoHelper.h"

#define QCC_MODULE "PERMISSION_MGMT"

using namespace std;
using namespace qcc;

namespace ajn {

QStatus PermissionConfiguratorImpl::SetPermissionManifest(PermissionPolicy::Rule* rules, size_t count)
{
    PermissionMgmtObj* permissionMgmtObj = bus.GetInternal().GetPermissionManager().GetPermissionMgmtObj();
    if (!permissionMgmtObj || !permissionMgmtObj->IsReady()) {
        QCC_DbgPrintf(("PermissionConfiguratorImpl::SetPermissionManifest does not have PermissionMgmtObj initialized"));
        return ER_FEATURE_NOT_AVAILABLE;
    }
    return permissionMgmtObj->SetManifestTemplate(rules, count);
}

QStatus PermissionConfiguratorImpl::GetApplicationState(ApplicationState& applicationState)
{
    PermissionMgmtObj* permissionMgmtObj = bus.GetInternal().GetPermissionManager().GetPermissionMgmtObj();
    if (!permissionMgmtObj || !permissionMgmtObj->IsReady()) {
        return ER_FEATURE_NOT_AVAILABLE;
    }
    applicationState = permissionMgmtObj->GetApplicationState();
    return ER_OK;
}

QStatus PermissionConfiguratorImpl::SetApplicationState(ApplicationState newState)
{
    PermissionMgmtObj* permissionMgmtObj = bus.GetInternal().GetPermissionManager().GetPermissionMgmtObj();
    if (!permissionMgmtObj || !permissionMgmtObj->IsReady()) {
        return ER_FEATURE_NOT_AVAILABLE;
    }
    return permissionMgmtObj->SetApplicationState(newState);
}

QStatus PermissionConfiguratorImpl::Reset()
{
    PermissionMgmtObj* permissionMgmtObj = bus.GetInternal().GetPermissionManager().GetPermissionMgmtObj();
    if (!permissionMgmtObj || !permissionMgmtObj->IsReady()) {
        return ER_FEATURE_NOT_AVAILABLE;
    }
    return permissionMgmtObj->Reset();
}

QStatus PermissionConfiguratorImpl::GetSigningPublicKey(KeyInfoECC& keyInfo)
{
    if (keyInfo.GetCurve() != Crypto_ECC::ECC_NIST_P256) {
        return ER_NOT_IMPLEMENTED;  /* currently only support NIST P256 curve */
    }
    CredentialAccessor ca(bus);
    ECCPublicKey publicKey;
    QStatus status = PermissionMgmtObj::RetrieveDSAPublicKey(&ca, &publicKey);
    if (status != ER_OK) {
        return status;
    }
    KeyInfoNISTP256* pKeyInfo = (KeyInfoNISTP256*) &keyInfo;
    pKeyInfo->SetPublicKey(&publicKey);
    KeyInfoHelper::GenerateKeyId(*pKeyInfo);
    return ER_OK;
}

QStatus PermissionConfiguratorImpl::SignCertificate(CertificateX509& cert)
{
    CredentialAccessor ca(bus);
    ECCPrivateKey privateKey;
    QStatus status = PermissionMgmtObj::RetrieveDSAPrivateKey(&ca, &privateKey);
    if (status != ER_OK) {
        return status;
    }
    ECCPublicKey publicKey;
    status = ca.GetDSAPublicKey(publicKey);
    if (status != ER_OK) {
        return status;
    }
    return cert.SignAndGenerateAuthorityKeyId(&privateKey, &publicKey);
}

QStatus PermissionConfiguratorImpl::GetConnectedPeerPublicKey(const GUID128& guid, qcc::ECCPublicKey* publicKey)
{
    PermissionMgmtObj* permissionMgmtObj = bus.GetInternal().GetPermissionManager().GetPermissionMgmtObj();
    if (!permissionMgmtObj || !permissionMgmtObj->IsReady()) {
        return ER_FEATURE_NOT_AVAILABLE;
    }
    return permissionMgmtObj->GetConnectedPeerPublicKey(guid, publicKey);
}

QStatus PermissionConfiguratorImpl::SetClaimCapabilities(PermissionConfigurator::ClaimCapabilities claimCapabilities)
{
    PermissionMgmtObj* permissionMgmtObj = bus.GetInternal().GetPermissionManager().GetPermissionMgmtObj();
    if (!permissionMgmtObj || !permissionMgmtObj->IsReady()) {
        return ER_FEATURE_NOT_AVAILABLE;
    }
    return permissionMgmtObj->SetClaimCapabilities(claimCapabilities);
}

QStatus PermissionConfiguratorImpl::SetClaimCapabilityAdditionalInfo(PermissionConfigurator::ClaimCapabilityAdditionalInfo additionalInfo)
{
    PermissionMgmtObj* permissionMgmtObj = bus.GetInternal().GetPermissionManager().GetPermissionMgmtObj();
    if (!permissionMgmtObj || !permissionMgmtObj->IsReady()) {
        return ER_FEATURE_NOT_AVAILABLE;
    }
    return permissionMgmtObj->SetClaimCapabilityAdditionalInfo(additionalInfo);
}

QStatus PermissionConfiguratorImpl::GetClaimCapabilities(PermissionConfigurator::ClaimCapabilities& claimCapabilities)
{
    PermissionMgmtObj* permissionMgmtObj = bus.GetInternal().GetPermissionManager().GetPermissionMgmtObj();
    if (!permissionMgmtObj || !permissionMgmtObj->IsReady()) {
        return ER_FEATURE_NOT_AVAILABLE;
    }
    return permissionMgmtObj->GetClaimCapabilities(claimCapabilities);
}

QStatus PermissionConfiguratorImpl::GetClaimCapabilityAdditionalInfo(PermissionConfigurator::ClaimCapabilityAdditionalInfo& additionalInfo)
{
    PermissionMgmtObj* permissionMgmtObj = bus.GetInternal().GetPermissionManager().GetPermissionMgmtObj();
    if (!permissionMgmtObj || !permissionMgmtObj->IsReady()) {
        return ER_FEATURE_NOT_AVAILABLE;
    }
    return permissionMgmtObj->GetClaimCapabilityAdditionalInfo(additionalInfo);
}

}
