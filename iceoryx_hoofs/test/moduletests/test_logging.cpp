// Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
// Copyright (c) 2021 - 2022 by Apex.AI Inc. All rights reserved.
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
//
// SPDX-License-Identifier: Apache-2.0

#include "iceoryx_hoofs/log/logging.hpp"

#include "iceoryx_hoofs/testing/logger.hpp"
#include "iceoryx_hoofs/testing/mocks/logger_mock.hpp"
#include "test.hpp"

namespace
{
using namespace ::testing;

class LoggingLogLevelThreshold_test : public TestWithParam<iox::log::LogLevel>
{
};

INSTANTIATE_TEST_SUITE_P(AllLogLevel,
                         LoggingLogLevelThreshold_test,
                         Values(iox::log::LogLevel::OFF,
                                iox::log::LogLevel::FATAL,
                                iox::log::LogLevel::ERROR,
                                iox::log::LogLevel::WARN,
                                iox::log::LogLevel::INFO,
                                iox::log::LogLevel::DEBUG,
                                iox::log::LogLevel::TRACE));

TEST_P(LoggingLogLevelThreshold_test, LogLevel)
{
    ::testing::Test::RecordProperty("TEST_ID", "829a6634-43be-4fa4-94bf-18d53ce816a9");
    const auto loggerLogLevel = GetParam();
    iox::log::Logger::setLogLevel(loggerLogLevel);

    struct LogLevel
    {
        LogLevel(iox::log::LogLevel logLevel, std::string str)
            : value(logLevel)
            , string(str)
        {
        }
        iox::log::LogLevel value;
        std::string string;
    };

    const std::initializer_list<LogLevel> logEntryLogLevels{{iox::log::LogLevel::FATAL, "Fatal"},
                                                            {iox::log::LogLevel::ERROR, "Error"},
                                                            {iox::log::LogLevel::WARN, "Warn"},
                                                            {iox::log::LogLevel::INFO, "Info"},
                                                            {iox::log::LogLevel::DEBUG, "Debug"},
                                                            {iox::log::LogLevel::TRACE, "Trace"}};

    iox::testing::Logger_Mock loggerMock;
    for (const auto& logEntryLogLevel : logEntryLogLevels)
    {
        if (!iox::testing::Logger::doesLoggerSupportLogLevel(logEntryLogLevel.value))
        {
            continue;
        }

        dynamic_cast<iox::testing::Logger&>(iox::log::Logger::get()).clearLogBuffer();
        IOX_LOG_INTERNAL("", 0, "", logEntryLogLevel.value);

        if (logEntryLogLevel.value <= loggerLogLevel)
        {
            ASSERT_THAT(iox::testing::Logger::getNumberOfLogMessages(), Eq(1U));
            auto logMessage = iox::testing::Logger::getLogMessages().back();
            EXPECT_THAT(logMessage.find(logEntryLogLevel.string), Ne(std::string::npos));
        }
        else
        {
            ASSERT_THAT(iox::testing::Logger::getNumberOfLogMessages(), Eq(0U));
        }
    }
}

} // namespace
