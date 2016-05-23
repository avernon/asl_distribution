/*
 * IPTransport.cc
 *
 *  Created on: Jun 4, 2015
 *      Author: erongo
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
#include "IPTransport.h"

#include <algorithm>

namespace nio {

IPTransport::IPTransport(Proactor& proactor, const std::string& name) : TransportBase(proactor, name)
{
    CheckNetworks();
}

IPTransport::~IPTransport()
{
}

std::string IPTransport::NormalizeConnectionData(const qcc::IPAddress& addr, uint16_t port)
{
    const std::string name = GetName();
    char normSpec[256];
    ::snprintf(normSpec, sizeof(normSpec), "%s:addr=%s,port=%u", name.c_str(), addr.ToString().c_str(), port);
    return normSpec;
}

void IPTransport::CheckNetworks()
{
    std::vector<qcc::IfConfigEntry> entries;
    QStatus status = qcc::IfConfig(entries);
    if (status != ER_OK) {
        return;
    }

    for (auto entry : entries) {
        if ((entry.m_flags & qcc::IfConfigEntry::UP) && !entry.m_addr.empty()) {
            ip_addresses[entry.m_name.c_str()].push_back(qcc::IPAddress(entry.m_addr));
        }
    }
}

void IPTransport::OnNetworkEntries(const std::vector<qcc::IfConfigEntry>& entries)
{
    // TODO: when adding or removing an interface/IP, adjust the listeners accordingly

    for (const qcc::IfConfigEntry& entry : entries) {
        auto it = ip_addresses.find(entry.m_name.c_str());
        if (it != ip_addresses.end()) {
            std::list<qcc::IPAddress>& ips = it->second;
            qcc::IPAddress ip(entry.m_addr);

            if (entry.m_flags & qcc::IfConfigEntry::UP) {
                auto iter = std::find(ips.begin(), ips.end(), ip);
                if (iter == ips.end()) {
                    ips.push_back(ip);
                }

            } else {
                auto iter = std::find(ips.begin(), ips.end(), ip);
                if (iter != ips.end()) {
                    ips.erase(iter);

                    // erase any interfaces that no longer have IP's
                    if (ips.empty()) {
                        ip_addresses.erase(it);
                    }
                }
            }
        }
    }
}

bool IPTransport::ParseSpec(const std::string& spec, qcc::IPAddress& ip, uint16_t& port, std::string& normSpec)
{
    const std::string name = GetName();

    if (spec.compare(0, name.length() + 1, name + ":") != 0) {
        return false;
    }

    size_t start = spec.find("addr=");
    if (start != std::string::npos) {
        start += ::strlen("addr=");

        // find the end
        size_t end = spec.find(",", start);
        if (end == std::string::npos) {
            end = spec.length();
        }

        std::string addr = spec.substr(start, end - start);
        ip.SetAddress(addr.c_str(), false);
    } else {
        return false;
    }

    start = spec.find("port=");
    if (start != std::string::npos) {
        start += ::strlen("port=");
        size_t end = spec.find(",", start);
        if (end == std::string::npos) {
            end = spec.length();
        }

        std::string port_str = spec.substr(start, end - start);
        port = ::strtoul(port_str.c_str(), NULL, 10);
    } else {
        return false;
    }

    normSpec = NormalizeConnectionData(ip, port);
    return true;
}

bool IPTransport::ParseSpec(const std::string& spec, ListenEndpoints& endpoints)
{
    const std::string name = GetName();

    if (spec.compare(0, name.length() + 1, name + ":") != 0) {
        return false;
    }

    uint16_t port = 0;

    size_t start = spec.find("port=");
    if (start != std::string::npos) {
        start += ::strlen("port=");
        size_t end = spec.find(",", start);
        if (end == std::string::npos) {
            end = spec.length();
        }

        std::string port_str = spec.substr(start, end - start);
        port = ::strtoul(port_str.c_str(), NULL, 10);
    }

    start = spec.find("iface=");
    if (start != std::string::npos) {
        start += ::strlen("iface=");

        // find the end
        size_t end = spec.find(",", start);
        if (end == std::string::npos) {
            end = spec.length();
        }

        const std::string iface = spec.substr(start, end - start);
        if (iface == "*") {
            for (auto iface : ip_addresses) {
                for (qcc::IPAddress ip : iface.second) {
                    endpoints.push_back(qcc::IPEndpoint(ip, port));
                }
            }
        } else {
            // now iterate through the IP's with this interface
            auto it = ip_addresses.find(iface);
            if (it != ip_addresses.end()) {
                for (auto ip : it->second) {
                    endpoints.push_back(qcc::IPEndpoint(ip, port));
                }
            } else {
                // not found!
                return false;
            }
        }
    } else {
        start = spec.find("addr=");
        if (start != std::string::npos) {
            start += ::strlen("addr=");

            // find the end
            size_t end = spec.find(",", start);
            if (end == std::string::npos) {
                end = spec.length();
            }

            std::string addr = spec.substr(start, end - start);
            qcc::IPEndpoint ep;
            ep.addr.SetAddress(addr.c_str(), false);
            ep.port = port;

            endpoints.push_back(ep);
        } else {
            // must specify ip or interface!
            return false;
        }
    }

    return true;
}

} /* namespace nio */
