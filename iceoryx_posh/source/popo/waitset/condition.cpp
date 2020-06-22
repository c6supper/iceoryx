// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
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
// limitations under the License

#include "iceoryx_posh/internal/popo/waitset/condition.hpp"

namespace iox
{
namespace popo
{
Condition::Condition(const Condition& rhs) noexcept
{
    m_trigger.store(rhs.m_trigger, std::memory_order_relaxed);
}

bool Condition::hasTrigger() noexcept
{
    return m_trigger;
}

void Condition::setTrigger() noexcept
{
    m_trigger.store(true, std::memory_order_relaxed);
}

bool Condition::operator==(const Condition& rhs) noexcept
{
    /// @todo when is a condition equal to another one?
    return false;
}

} // namespace popo
} // namespace iox
