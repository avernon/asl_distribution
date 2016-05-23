/**
 * @file
 *
 * This file just provides static initialization for the OpenSSL libraries.
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
#ifndef _QCC_OPENSSL_H
#define _QCC_OPENSSL_H

#include <openssl/aes.h>
#include <openssl/bio.h>
#include <openssl/bn.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/sha.h>
#include <openssl/ssl.h>
#include <openssl/x509.h>

namespace qcc {

/**
 * OpenSSL may not be thread safe so the wrappers must obtain a mutual
 * exclusion lock before making calls into the crypto library. To
 * obtain the lock declare an instance of this class before calling
 * any OpenSSL crypto library APIs.
 *
 * This is a no-op when OpenSSL is compiled with multi-threaded
 * support.
 */
class OpenSsl_ScopedLock {
  public:
    OpenSsl_ScopedLock();
    ~OpenSsl_ScopedLock();
};

}

#endif
