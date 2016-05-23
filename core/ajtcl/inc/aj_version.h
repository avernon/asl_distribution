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
#ifndef _AJ_VERSION_H
#define _AJ_VERSION_H
/**
 * @file aj_version.h
 * @defgroup aj_version Current AllJoyn Thin Client Version
 * @{
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

#define AJ_RELEASE_YEAR        0        /**< release year */
#define AJ_MAJOR_VERSION       AJ_RELEASE_YEAR /**< deprecated */
#define AJ_RELEASE_MONTH       0        /**< release month */
#define AJ_MINOR_VERSION       AJ_RELEASE_MONTH /**< deprecated */
#define AJ_FEATURE_VERSION     1        /**< feature version */
#define AJ_RELEASE_VERSION     AJ_FEATURE_VERSION /**< deprecated */
#define AJ_BUGFIX_VERSION      0        /**< bugfix version (0=first, 0x61==a, 0x62==b, etc.) */
#define AJ_RELEASE_YEAR_STR    0        /**< release year string (two digits) */
#define AJ_RELEASE_MONTH_STR   0        /**< release month string (two digits) */
#define AJ_FEATURE_VERSION_STR 1        /**< feature version string (00, 01, 02, ...) */
#define AJ_BUGFIX_VERSION_STR           /**< bugfix version string (blank, a, b, ...) */
#define AJ_RELEASE_TAG         "v0.0.1"

#define AJ_VERSION (((AJ_RELEASE_YEAR) << 24) | ((AJ_RELEASE_MONTH) << 16) | ((AJ_FEATURE_VERSION) << 8) | (AJ_BUGFIX_VERSION))  /**< macro to generate the version from major, minor, release, bugfix */

/**
 * @}
 */
#endif
