/**
 * @file KeyInfoECC.cc
 *
 * Class for ECC Public Key Info utilities
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

#include <qcc/platform.h>
#include <qcc/KeyInfoECC.h>
#include <qcc/StringUtil.h>

#include <Status.h>

using namespace std;

namespace qcc {

#define QCC_MODULE "CRYPTO"

const size_t KeyInfo::GetExportSize()
{
    return sizeof(FormatType) + sizeof(uint32_t) + keyIdLen * sizeof(uint8_t);
}

QStatus KeyInfo::Export(uint8_t* buf)
{
    memcpy(buf, &format, sizeof(FormatType));
    buf += sizeof(FormatType);
    memcpy(buf, &keyIdLen, sizeof(uint32_t));
    buf += sizeof(uint32_t);
    if (keyIdLen > 0) {
        memcpy(buf, keyId, keyIdLen);
    }
    return ER_OK;
}

QStatus KeyInfo::Import(const uint8_t* buf, size_t count)
{
    if (count < GetExportSize()) {
        return ER_INVALID_DATA;
    }
    uint8_t* p = (uint8_t*) buf;
    FormatType srcFormat;
    memcpy(&srcFormat, p, sizeof(FormatType));
    if (srcFormat != format) {
        return ER_INVALID_DATA;
    }
    p += sizeof(FormatType);
    uint32_t len;
    memcpy(&len, p, sizeof(uint32_t));
    p += sizeof(uint32_t);
    SetKeyId(p, len);
    return ER_OK;
}

const size_t KeyInfoECC::GetExportSize()
{
    return KeyInfo::GetExportSize() + sizeof(uint8_t);
}

QStatus KeyInfoECC::Export(uint8_t* buf)
{
    KeyInfo::Export(buf);
    buf += KeyInfo::GetExportSize();
    memcpy(buf, &curve, sizeof(curve));
    return ER_OK;
}

QStatus KeyInfoECC::Import(const uint8_t* buf, size_t count)
{
    if (count < GetExportSize()) {
        return ER_INVALID_DATA;
    }
    KeyInfo::Import(buf, count);
    uint8_t* p = (uint8_t*) buf;
    p += KeyInfo::GetExportSize();
    memcpy(&curve, p, sizeof(curve));
    return ER_OK;
}

qcc::String KeyInfoECC::ToString(size_t indent) const
{
    qcc::String str;
    qcc::String in = qcc::String(indent, ' ');
    str += in + "<keyInfo>\n";
    str += in + "  <format>" + U32ToString(GetFormat()) + "</format>\n";
    str += in + "  <algorithm>" + U32ToString(GetAlgorithm()) + "</algorithm>\n";
    str += in + "  <curve>" + U32ToString(GetCurve()) + "</curve>\n";
    if (GetKeyIdLen() > 0) {
        str += in + "  <id>" + BytesToHexString(GetKeyId(), GetKeyIdLen()) + "</id>\n";
    }
    str += in + "</keyInfo>\n";
    return str;
}

qcc::String KeyInfoNISTP256::ToString(size_t indent) const
{
    qcc::String str;
    qcc::String in = qcc::String(indent, ' ');
    str += in + "<NISP256KeyInfo>\n";
    str += in + "  <format>" + U32ToString(GetFormat()) + "</format>\n";
    str += in + "  <algorithm>" + U32ToString(GetAlgorithm()) + "</algorithm>\n";
    str += in + "  <curve>" + U32ToString(GetCurve()) + "</curve>\n";
    if (GetKeyIdLen() > 0) {
        str += in + "  <id>" + BytesToHexString(GetKeyId(), GetKeyIdLen()) + "</id>\n";
    }
    str += in + "  <publickey>";
    str += BytesToHexString((const uint8_t*) GetPublicKey(), sizeof(ECCPublicKey));
    str += "</publickey>\n";
    str += in + "</NISP256KeyInfo>\n";
    return str;
}

const size_t KeyInfoNISTP256::GetExportSize()
{
    return KeyInfoECC::GetExportSize() + sizeof(pubkey.form) + pubkey.key.GetSize();
}

QStatus KeyInfoNISTP256::Export(uint8_t* buf)
{
    KeyInfoECC::Export(buf);
    buf += KeyInfoECC::GetExportSize();
    memcpy(buf, &pubkey.form, sizeof(uint8_t));
    buf += sizeof(uint8_t);
    size_t keySize = pubkey.key.GetSize();
    QStatus status = pubkey.key.Export(buf, &keySize);
    if (ER_OK != status) {
        return status;
    }
    if (keySize != pubkey.key.GetSize()) {
        return ER_INVALID_DATA;
    }
    return ER_OK;
}

QStatus KeyInfoNISTP256::Import(const uint8_t* buf, size_t count)
{
    if (count < GetExportSize()) {
        return ER_INVALID_DATA;
    }
    KeyInfoECC::Import(buf, count);
    uint8_t* p = (uint8_t*) buf;
    p += KeyInfoECC::GetExportSize();
    p += sizeof(uint8_t);
    return pubkey.key.Import(p, pubkey.key.GetSize());
}

} /* namespace qcc */
