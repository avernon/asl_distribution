# Contributed by Qualcomm Connected Experiences, Inc.,
# with authorization from the AllSeen Alliance, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Pursuant to Section 1 of the License, the work of authorship constituting
# a Work and any Contribution incorporated in the Work shall mean only that
# Contributor's code submissions authored by that Contributor.  Any rights
# granted under the License are conditioned upon acceptance of these
# clarifications.
#ifndef _CERTIFICATE_H_
#define _CERTIFICATE_H_
/**
 * @file
 *
 * Certificate utilities
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

#include <qcc/platform.h>
#include <qcc/String.h>
#include <Status.h>

namespace qcc {


/**
 * Certificate Class
 */
class Certificate {

  public:

    static const size_t SHA256_DIGEST_SIZE = 32; ///< SHA256 digest size - 32 bytes == 256 bits

    /**
     * Certificate format
     */

    typedef enum {
        SPKI_CERTIFICATE = 0,   ///< SPKI certificate format
        X509_CERTIFICATE = 1   ///< X.509 certificate format
    } Format;

    /**
     * encoding format
     */
    typedef enum {
        ENCODING_ALLJOYN = 0,      ///< AllJoyn format
        ENCODING_JWK = 1,          ///< JSON Web Key format
        ENCODING_X509_DER = 2,     ///< X.509 DER format
        ENCODING_X509_DER_PEM = 3  ///< X.509 DER PEM format
    } EncodingType;

    struct ValidPeriod {
        uint64_t validFrom; /* the date time when the cert becomes valid
                                expressed in the number of seconds in EPOCH Jan 1, 1970 */
        uint64_t validTo;  /* the date time after which the cert becomes invalid
                                expressed in the number of seconds in EPOCH Jan 1, 1970 */
    };

    Certificate(uint32_t version, Format format)
    {
        SetVersion(version);
        SetFormat(format);
    }

    Certificate(uint32_t version)
    {
        SetVersion(version);
        SetFormat(SPKI_CERTIFICATE);
    }

    /**
     * Get the certificate version.
     * @return the certificate version
     */
    uint32_t GetVersion()
    {
        return version;
    }

    /**
     * Set the certificate version
     * @param val the certificate version
     */
    virtual void SetVersion(uint32_t val)
    {
        version = val;
    }

    /**
     * Get the certificate format.
     * @return the certificate format
     */
    Format GetFormat()
    {
        return format;
    }

    /**
     * Set the certificate format
     * @param val the certificate format
     */
    virtual void SetFormat(Format val)
    {
        format = val;
    }

    /**
     * Get the encoded bytes for the certificate
     * @return the encoded bytes
     */
    virtual const uint8_t* GetEncoded()
    {
        return NULL;
    }

    /**
     * Get the length of the encoded bytes for the certificate
     * @return the length of the encoded bytes
     */
    virtual size_t GetEncodedLen()
    {
        return 0;
    }
    /**
     * Load the encoded bytes for the certificate
     * @param encodedBytes the encoded bytes
     * @param len the length of the encoded bytes
     * @return ER_OK for sucess; otherwise, error code.
     */
    virtual QStatus LoadEncoded(const uint8_t* encodedBytes, size_t len)
    {
        return ER_NOT_IMPLEMENTED;
    }

    /**
     * Get the PEM encoded bytes for the certificate
     * @return the PEM encoded bytes
     */
    virtual String GetPEM()
    {
        return "";
    }

    /**
     * Load the PEM encoded bytes for the certificate
     * @param encoded the encoded bytes
     * @return ER_OK for sucess; otherwise, error code.
     */
    virtual QStatus LoadPEM(const String& PEM)
    {
        return ER_NOT_IMPLEMENTED;
    }
    /**
     * Get the validity period
     */
    virtual const ValidPeriod* GetValidity()
    {
        return (ValidPeriod* ) NULL;
    }

    /**
     * Retrieve the delegate flag.
     * @return the deleage flag
     */
    virtual const bool IsDelegate()
    {
        return false;
    }

    /**
     * Get the external data digest.
     * @return the pointer to the external digest.  The lifetime of the pointer is the same as the lifetime of the object.
     */
    virtual const uint8_t* GetExternalDataDigest()
    {
        return NULL;
    }
    /**
     * Verify the signature of the certificate.
     * @return true if the signature is valid.
     */
    virtual bool VerifySignature()
    {
        return false;
    }

    virtual String ToString()
    {
        return "";
    }

    virtual ~Certificate()
    {
    }

  private:
    uint32_t version;
    Format format;
};

} /* namespace qcc */

#endif
