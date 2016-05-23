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
#ifndef _CRYPTOECC_H
#define _CRYPTOECC_H
/**
 * @file
 *
 * This file provide wrappers around ECC cryptographic algorithms.
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

#include <Status.h>
#include <qcc/platform.h>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <assert.h>


namespace qcc {

/**
 * The ECC coordinate size
 */

static const size_t ECC_COORDINATE_SZ = 8 * sizeof(uint32_t);

/**
 * Empty ECC coordinate
 */
static const uint8_t ECC_COORDINATE_EMPTY[ECC_COORDINATE_SZ] = { 0 };

/**
 * The ECC private key big endian byte array
 */
struct ECCPrivateKey {
    /**
     * The ECCPrivateKey data
     */
    uint8_t d[ECC_COORDINATE_SZ];

    /**
     * ECCPrivateKey constructor
     */
    ECCPrivateKey() {
        memset(d, 0, ECC_COORDINATE_SZ);
    }

    /**
     * the assign operator for the ECCPrivateKey
     *
     * @param[in] other the ECCPrivate key to assign
     * @return Reference to *this which has just had its values assigned from
     *         the other ECCPrivateKey
     */
    ECCPrivateKey& operator=(const ECCPrivateKey& other)
    {
        if (this != &other) {
            memcpy(d, other.d, ECC_COORDINATE_SZ);
        }
        return *this;
    }

    /**
     * Equals operator for the ECCPrivateKey.
     *
     * @param[in] k the ECCPrivateKey to compare
     *
     * @return true if the ECCPrivateKeys are equal
     */
    bool operator==(const ECCPrivateKey& k) const
    {
        return memcmp(d, k.d, ECC_COORDINATE_SZ) == 0;
    }
};

    /** Support methods for CryptoECCMath **/

    /*
     * Return a buffer containing just the private key value
     *
     * @return Buffer containing the private key value
     */
    const uint8_t* GetD() const
    {
        return this->d;
    }

    /**
     * Get the size of the private key value
     *
     * @return Size of the private key in bytes
     */
    const size_t GetDSize() const
    {
        return this->GetSize();
    }

};

/**
 * The ECC public key big endian byte array
 */
struct ECCPublicKey {
    /**
     * The x coordinate of the elliptic curve
     */
    uint8_t x[ECC_COORDINATE_SZ];
    /**
     * The y coordinate of the elliptic curve
     */
    uint8_t y[ECC_COORDINATE_SZ];

  public:

    /**
     * Clear the key to make it empty.
     */
    void Clear()
    {
        memset(x, 0, GetCoordinateSize());
        memset(y, 0, GetCoordinateSize());
    }

    ECCPublicKey()
    {
        Clear();
    }

    /**
     * Check to see if the ECCPublicKey is empty.
     *
     * @return true if the ECCPublicKey is empty
     */
    bool empty() const
    {
        return (memcmp(x, ECC_COORDINATE_EMPTY, ECC_COORDINATE_SZ) == 0) &&
               (memcmp(y, ECC_COORDINATE_EMPTY, ECC_COORDINATE_SZ) == 0);
    }

    /**
     * Equals operator
     *
     * @param[in] k the ECCPublic key to compare
     *
     * @return true if the compared ECCPublicKeys are equal to each other
     */
    bool operator==(const ECCPublicKey& k) const
    {
        int n = memcmp(x, k.x, ECC_COORDINATE_SZ);
        return (n == 0) && (0 == memcmp(y, k.y, ECC_COORDINATE_SZ));
    }

    /**
     * Not equals operator
     *
     * @param[in] k the ECCPublicKey to compare
     *
     * @return true if the compared ECCPublicKeys are not equal to each other
     */
    bool operator!=(const ECCPublicKey& k) const
    {
        return !(*this == k);
    }

    /**
     * The less than operator for the ECCPublicKey
     *
     * The x coordinate are compared first. If the x coordinates match then
     * the y coordinate is compared.
     *
     * @param[in] k the ECCPublicKey to compare
     *
     * @return True if the left ECCPublicKey is less than the right ECCPublicKey
     * false otherwise.
     */
    bool operator<(const ECCPublicKey& k) const
    {
        int n = memcmp(x, k.x, ECC_COORDINATE_SZ);
        if (n == 0) {
            n = memcmp(y, k.y, ECC_COORDINATE_SZ);
        }
        if (n < 0) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Assign operator for ECCPublicKey
     *
     * @param[in] other the ECCPublicKey to assign
     * @return Reference to *this which has just had its values assigned from
     *         the other ECCPublicKey
     */
    ECCPublicKey& operator=(const ECCPublicKey& other)
    {
        if (this != &other) {
            memcpy(x, other.x, ECC_COORDINATE_SZ);
            memcpy(y, other.y, ECC_COORDINATE_SZ);
        }
        return *this;
    }

    /**
     * Exports the key to a byte array.
     * @param[in] data the array to store the data in
     * @param[in,out] size provides the size of the passed buffer as input. On a  successfull return it
     *   will contain the actual amount of data stored
     *
     * @return ER_OK on success others on failure
     */
    QStatus Export(uint8_t* data, size_t* size) const;

    /**
     * Imports the key from a byte array.
     * @param[in] data the array to store the data in
     * @param[in] size the size of the passed buffer.
     *
     * @return ER_OK  on success others on failure
     */
    QStatus Import(const uint8_t* data, size_t size);
    /**
     * Import the key from two byte arrays, one containing each coordinate
     * @param[in] xData array containing the bytes of the X coordinate
     * @param[in] xSize length of xData
     * @param[in] yData array containing the bytes of the Y coordinate
     * @param[in] ySize length of yData
     *
     * @return ER_OK   on success others on failure
     */
    QStatus Import(const uint8_t* xData, const size_t xSize, const uint8_t* yData, const size_t ySize);

    /**
     * Return the ECCPublicKey to a string
     * @return the ECCPublicKey as a string.
     */
    const String ToString() const;

    /**
     * Return the size of the public key in exported form
     *
     * @return Size of the exported public key
     */
    inline const size_t GetSize() const
    {
        return 2 * GetCoordinateSize();
    }

    /** Support methods for CryptoECCMath **/

    /*
     * Get a buffer containing just the X coordinate of this public key
     *
     * @return Buffer containing the X value
     */
    const uint8_t* GetX() const
    {
        return this->x;
    }

    /**
     * Get a buffer containing just the Y coordinate of this public key
     *
     * @return Buffer containing the Y value
     */
    const uint8_t* GetY() const
    {
        return this->y;
    }

    /**
     * Get the size of a single coordinate
     *
     * @return The size of a single coordinate
     */
    const qcc::String ToString() const;

};

/**
 * The ECC secret
 */
struct ECCSecret {
    uint8_t z[ECC_COORDINATE_SZ];

class ECCSecret {
  public:

    /**
     * Opaque type for the internal state.
     */
    struct ECCSecretState;

    /**
     * Default Constructor;
     */
    ECCSecret();

    /**
     * Set the opaque secret state for this object
     * @param   pEccSecretState the internal secret state to set.
     * @return
     *      ER_OK if the secret is successfully set.
     *      ER_FAIL otherwise.
     *      Other error status.
     */
    QStatus SetSecretState(const ECCSecretState* pEccSecretState);

    /**
     * Derives the PreMasterSecret.
     * Current implementaiton uses SHA256 HASH KDF.
     * @param   pbPreMasterSecret buffer to receive premaster secret.
     * @param   cbPreMasterSecret count of buffer to receive premaster secret.
     * @return
     *      ER_OK if the pre-master secret is successfully computed and put in pbPreMasterSecret.
     *      ER_FAIL otherwise.
     *      Other error status.
     */
    QStatus DerivePreMasterSecret(uint8_t* pbPreMasterSecret, size_t cbPreMasterSecret);

    /**
     * Default Destructor
     */

    ~ECCSecret();

  private:
    /* private copy constructor to prevent double delete of eccSecretState */
    ECCSecret(const ECCSecret&);
    /* private assignment operator to prevent double delete of eccSecretState */
    ECCSecret& operator=(const ECCSecret&);

    /**
     * Private internal state
     */
    ECCSecretState* eccSecretState;

};

/**
 * The ECC signature big endian byte array
 */

struct ECCSignature {
    /**
     * The r value for the Elliptic Curve Digital Signature (r,s) signature pair
     */
    uint8_t r[ECC_COORDINATE_SZ];
    /**
     * The s value for the Elliptic Curve Digital Signature (r,s) signature pair
     */
    uint8_t s[ECC_COORDINATE_SZ];

    /**
     * ECCSignature constructor
     *
     * The Elliptic Curve Digital Signature (r,s) signature initialized to zero.
     */
    ECCSignature() {
        memset(r, 0, ECC_COORDINATE_SZ);
        memset(s, 0, ECC_COORDINATE_SZ);
    }

    /**
     * The ECCSignature assign operator
     * @param[in] other the ECC signature to assign
     * @return Reference to *this which has just had its values assigned from
     *         the other ECCSignature
     */
    ECCSignature& operator=(const ECCSignature& other)
    {
        if (this != &other) {
            memcpy(r, other.r, ECC_COORDINATE_SZ);
            memcpy(s, other.s, ECC_COORDINATE_SZ);
        }
        return *this;
    }
};

struct ECCSignature {
    uint8_t r[ECC_COORDINATE_SZ];
    uint8_t s[ECC_COORDINATE_SZ];
};

/**
 * Elliptic Curve Cryptography
 */
class Crypto_ECC {

  public:

    /**
     * The NIST recommended elliptic curve P-256
     */
    static const uint8_t ECC_NIST_P256 = 0;

    /**
     * Default constructor.
     */
    Crypto_ECC()
    {
    }

    /**
     * Generates the Ephemeral Diffie-Hellman key pair.
     *
     * @return
     *      ER_OK if the key pair is successfully generated.
     *      ER_FAIL otherwise
     *      Other error status.
     */
    QStatus GenerateDHKeyPair();

    /**
     * Generates the Diffie-Hellman shared secret.
     * @param   peerPublicKey the peer's public key
     * @param   secret the output shared secret
     * @return
     *      ER_OK if the shared secret is successfully generated.
     *      ER_FAIL otherwise
     *      Other error status.
     */
    QStatus GenerateSharedSecret(const ECCPublicKey* peerPublicKey, ECCSecret* secret);

    /**
     * Retrieve the DH public key
     * @return  the DH public key.  It's a pointer to an internal buffer. Its lifetime is the same as the object's lifetime.
     */
    const ECCPublicKey* GetDHPublicKey() const
    {
        return &dhPublicKey;
    }

    /**
     * Assign the DH public key
     * @param pubKey the public key to copy
     */
    void SetDHPublicKey(const ECCPublicKey* pubKey)
    {
        dhPublicKey = *pubKey;
    }

    /**
     * Retrieve the DH private key
     * @return  the DH private key.  Same lifetime as the object.
     */
    const ECCPrivateKey* GetDHPrivateKey() const
    {
        return &dhPrivateKey;
    }

    /**
     * Assign the DH private key
     * @param privateKey the private key to copy
     */
    void SetDHPrivateKey(const ECCPrivateKey* privateKey)
    {
        dhPrivateKey = *privateKey;
    }

    /**
     * Retrieve the DSA public key
     * @return  the DSA public key.  Same lifetime as the object.
     */
    const ECCPublicKey* GetDSAPublicKey() const
    {
        return &dsaPublicKey;
    }

    /**
     * Assign the DSA public key
     * @param pubKey the public key to copy
     */
    void SetDSAPublicKey(const ECCPublicKey* pubKey)
    {
        dsaPublicKey = *pubKey;
    }

    /**
     * Retrieve the DSA private key
     * @return  the DSA private key.  Same lifetime as the object.
     */
    const ECCPrivateKey* GetDSAPrivateKey() const
    {
        return &dsaPrivateKey;
    }

    /**
     * Assign the DSA private key
     * @param privateKey the private key to copy
     */
    void SetDSAPrivateKey(const ECCPrivateKey* privateKey)
    {
        dsaPrivateKey = *privateKey;
    }

    /**
     * Generates the DSA key pair.
     *
     * @return
     *      ER_OK if the key pair is successfully generated.
     *      ER_FAIL otherwise
     *      Other error status.
     */
    QStatus GenerateDSAKeyPair();

    /**
     * Sign a digest using the DSA key
     * @param digest The digest to sign
     * @param len The digest len
     * @param sig The output signature
     * @return
     *      ER_OK if the signing process succeeds
     *      ER_FAIL otherwise
     *      Other error status.
     */
    QStatus DSASignDigest(const uint8_t* digest, uint16_t len, ECCSignature* sig);

    /**
     * Sign a buffer using the DSA key
     * @param buf The buffer to sign
     * @param len The buffer len
     * @param sig The output signature
     * @return
     *      ER_OK if the signing process succeeds
     *      ER_FAIL otherwise
     *      Other error status.
     */
    QStatus DSASign(const uint8_t* buf, uint16_t len, ECCSignature* sig);

    /**
     * Verify DSA signature of a digest
     * @param digest The digest to sign
     * @param len The digest len
     * @param sig The signature
     * @return  - ER_OK if the signature verification succeeds
     *          - ER_FAIL otherwise
     *          - Other error status.
     */
    QStatus DSAVerifyDigest(const uint8_t* digest, uint16_t len, const ECCSignature* sig);

    /**
     * Verify DSA signature of a buffer
     * @param buf The buffer to sign
     * @param len The buffer len
     * @param sig The signature
     * @return
     *      ER_OK if the signature verification succeeds
     *      ER_FAIL otherwise
     *      Other error status.
     */
    QStatus DSAVerify(const uint8_t* buf, uint16_t len, const ECCSignature* sig);

    /**
     * Retrieve the ECC curve type.
     * @return the ECC curve type
     */
    const uint8_t GetCurveType()
    {
        return ECC_NIST_P256;
    }

    QStatus ReEncode(const ECCPrivateKey* newenc, ECCPrivateKeyOldEncoding* oldenc);
    QStatus ReEncode(const ECCPublicKey* newenc, ECCPublicKeyOldEncoding* oldenc);
    QStatus ReEncode(const ECCSignature* newenc, ECCSignatureOldEncoding* oldenc);
    QStatus ReEncode(const ECCPrivateKeyOldEncoding* oldenc, ECCPrivateKey* newenc);
    QStatus ReEncode(const ECCPublicKeyOldEncoding* oldenc, ECCPublicKey* newenc);
    QStatus ReEncode(const ECCSignatureOldEncoding* oldenc, ECCSignature* newenc);

    ~Crypto_ECC();

  private:
    /* private copy constructor to prevent double freeing of eccState */
    Crypto_ECC(const Crypto_ECC&);
    /* private assignment operator to prevent double freeing of eccState */
    Crypto_ECC& operator=(const Crypto_ECC&);

    ECCPrivateKey dhPrivateKey;
    ECCPublicKey dhPublicKey;
    ECCPrivateKey dsaPrivateKey;
    ECCPublicKey dsaPublicKey;

};

} /* namespace qcc */


#endif
