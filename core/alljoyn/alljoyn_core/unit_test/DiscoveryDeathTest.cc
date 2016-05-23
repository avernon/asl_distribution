/**
 * @file
 * This program tests the discovery features of Alljoyn.It uses google test as the test
 * automation framework.
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
#ifndef NDEBUG
#include "ns/IpNameServiceImpl.h"

/* Header files included for Google Test Framework */
#include <gtest/gtest.h>
#include "ajTestCommon.h"

using namespace qcc;
using namespace ajn;

class StaticParams {
  public:
    uint32_t powerSource;
    uint32_t mobility;
    uint32_t availability;
    uint32_t nodeConnection;
    StaticParams(uint32_t powerSource, uint32_t mobility, uint32_t availability, uint32_t nodeConnection) :
        powerSource(powerSource), mobility(mobility), availability(availability), nodeConnection(nodeConnection) { }
};

class DynamicParams {
  public:
    uint32_t tcpAvail;
    uint32_t tcpMax;
    uint32_t udpAvail;
    uint32_t udpMax;
    uint32_t tclAvail;
    uint32_t tclMax;
    DynamicParams(uint32_t tcpAvail, uint32_t tcpMax, uint32_t udpAvail, uint32_t udpMax, uint32_t tclAvail, uint32_t tclMax) :
        tcpAvail(tcpAvail), tcpMax(tcpMax), udpAvail(udpAvail), udpMax(udpMax), tclAvail(tclAvail), tclMax(tclMax) { }
};

// This name should end in "DeathTest" so as to run before all other tests.
class DiscoveryStaticDeathTest : public testing::TestWithParam<StaticParams> {
    virtual void SetUp() { }
    virtual void TearDown() { }
};

// This name should end in "DeathTest" so as to run before all other tests.
class DiscoveryDynamicDeathTest : public testing::TestWithParam<DynamicParams> {
    virtual void SetUp() { }
    virtual void TearDown() { }
};

// This name should end in "DeathTest" so as to run before all other tests.
TEST_P(DiscoveryStaticDeathTest, ComputeStaticScoreDeathTest)
{
    // ComputeStaticScore using power_source, mobility, availability and node_type values
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    StaticParams tp = GetParam();
    uint32_t powerSource = tp.powerSource;
    uint32_t mobility = tp.mobility;
    uint32_t availability = tp.availability;
    uint32_t nodeConnection = tp.nodeConnection;
    ASSERT_DEATH(ajn::IpNameServiceImpl::ComputeStaticScore(powerSource, mobility, availability, nodeConnection), "Assertion.*failed");
}

TEST_P(DiscoveryDynamicDeathTest, ComputeDynamicScoreDeathTest)
{
    // ComputeDynamicScore using tcpAvail, tcpMax, udpAvail, udpMax, tclAvail and tclMax values
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    DynamicParams tp = GetParam();
    uint32_t tcpAvail = tp.tcpAvail;
    uint32_t tcpMax = tp.tcpMax;
    uint32_t udpAvail = tp.udpAvail;
    uint32_t udpMax = tp.udpMax;
    uint32_t tclAvail = tp.tclAvail;
    uint32_t tclMax = tp.tclMax;
    ASSERT_DEATH(ajn::IpNameServiceImpl::ComputeDynamicScore(tcpAvail, tcpMax, udpAvail, udpMax, tclAvail, tclMax, tclAvail, tclMax), "Assertion.*failed");
}

INSTANTIATE_TEST_CASE_P(DiscoveryStaticDeath, DiscoveryStaticDeathTest,
                        testing::Values(StaticParams(ajn::IpNameServiceImpl::ROUTER_POWER_SOURCE_MIN - 1, ajn::IpNameServiceImpl::ROUTER_MOBILITY_MIN, ajn::IpNameServiceImpl::ROUTER_AVAILABILITY_MIN, ajn::IpNameServiceImpl::ROUTER_NODE_CONNECTION_MIN),
                                        StaticParams(ajn::IpNameServiceImpl::ROUTER_POWER_SOURCE_MIN, ajn::IpNameServiceImpl::ROUTER_MOBILITY_MIN - 1, ajn::IpNameServiceImpl::ROUTER_AVAILABILITY_MIN, ajn::IpNameServiceImpl::ROUTER_NODE_CONNECTION_MIN),
                                        StaticParams(ajn::IpNameServiceImpl::ROUTER_POWER_SOURCE_MIN, ajn::IpNameServiceImpl::ROUTER_MOBILITY_MIN, ajn::IpNameServiceImpl::ROUTER_AVAILABILITY_MIN - 1, ajn::IpNameServiceImpl::ROUTER_NODE_CONNECTION_MIN),
                                        StaticParams(ajn::IpNameServiceImpl::ROUTER_POWER_SOURCE_MIN, ajn::IpNameServiceImpl::ROUTER_MOBILITY_MIN, ajn::IpNameServiceImpl::ROUTER_AVAILABILITY_MIN, ajn::IpNameServiceImpl::ROUTER_NODE_CONNECTION_MIN - 1),
                                        StaticParams(ajn::IpNameServiceImpl::ROUTER_POWER_SOURCE_MAX + 1, ajn::IpNameServiceImpl::ROUTER_MOBILITY_MAX, ajn::IpNameServiceImpl::ROUTER_AVAILABILITY_MAX, ajn::IpNameServiceImpl::ROUTER_NODE_CONNECTION_MAX),
                                        StaticParams(ajn::IpNameServiceImpl::ROUTER_POWER_SOURCE_MAX, ajn::IpNameServiceImpl::ROUTER_MOBILITY_MAX + 1, ajn::IpNameServiceImpl::ROUTER_AVAILABILITY_MAX, ajn::IpNameServiceImpl::ROUTER_NODE_CONNECTION_MAX),
                                        StaticParams(ajn::IpNameServiceImpl::ROUTER_POWER_SOURCE_MAX, ajn::IpNameServiceImpl::ROUTER_MOBILITY_MAX, ajn::IpNameServiceImpl::ROUTER_AVAILABILITY_MAX + 1, ajn::IpNameServiceImpl::ROUTER_NODE_CONNECTION_MAX),
                                        StaticParams(ajn::IpNameServiceImpl::ROUTER_POWER_SOURCE_MAX, ajn::IpNameServiceImpl::ROUTER_MOBILITY_MAX, ajn::IpNameServiceImpl::ROUTER_AVAILABILITY_MAX, ajn::IpNameServiceImpl::ROUTER_NODE_CONNECTION_MAX + 1)));

INSTANTIATE_TEST_CASE_P(DiscoveryDynamicDeath, DiscoveryDynamicDeathTest,
                        testing::Values(DynamicParams(17, 16, 2, 16, 2, 8),
                                        DynamicParams(2, 16, 17, 16, 2, 8),
                                        DynamicParams(2, 16, 2, 16, 9, 8)));
#endif
