// Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef IOX_POPO_BASE_PORT_DATA_HPP_
#define IOX_POPO_BASE_PORT_DATA_HPP_

#include "iceoryx_posh/capro/service_description.hpp"
#include "iceoryx_posh/iceoryx_posh_types.hpp"
#include "iceoryx_posh/internal/capro/capro_message.hpp"
#include "iceoryx_utils/internal/relocatable_pointer/relative_ptr.hpp"

#include <atomic>

namespace iox
{
namespace runtime
{
struct RunnableData;
}

namespace popo
{
/// @brief the 4 fundamental ports which can further be derived for custom behaviour
enum class BasePortType : uint8_t
{
    NO_PORT,
    SENDER_PORT,
    RECEIVER_PORT,
    INTERFACE_PORT,
    APPLICATION_PORT,
    PUBLISHER_PORT,
    SUBSCRIBER_PORT,
    PORT_TYPE_END,
};

constexpr int32_t MAX_PORT_TYPE_STRING_SIZE = 64;
constexpr char BasePortTypeString[][MAX_PORT_TYPE_STRING_SIZE] = {"NO_PORT",
                                                                  "SENDER_PORT",
                                                                  "RECEIVER_PORT",
                                                                  "INTERFACE_PORT",
                                                                  "APPLICATION_PORT",
                                                                  "PUBLISHER_PORT",
                                                                  "SUBSCRIBER_PORT"};

/// @brief Defines different base port data
struct BasePortData
{
  public:
    /// @brief Constructor for base port data members
    BasePortData() noexcept;

    /// @brief Constructor
    /// @param[in] serviceDescription creates the service service description
    /// @param[in] portType Type of port to be created
    /// @param[in] processName Name of the process
    /// @param[in] runnable The runnable where this port is attached to
    BasePortData(const capro::ServiceDescription& serviceDescription,
                 const BasePortType& portType,
                 const cxx::CString100& processName) noexcept;

    BasePortData(const BasePortData&) = delete;
    BasePortData& operator=(const BasePortData&) = delete;
    BasePortData(BasePortData&&) = delete;
    BasePortData& operator=(BasePortData&&) = delete;


    BasePortType m_portType{BasePortType::NO_PORT};
    capro::ServiceDescription m_serviceDescription;
    cxx::CString100 m_processName;

    static std::atomic<uint64_t> s_uniqueIdCounter;
    std::atomic<uint64_t> m_uniqueId{0};
    std::atomic_bool m_toBeDestroyed{false};
};

} // namespace popo
} // namespace iox

#endif
