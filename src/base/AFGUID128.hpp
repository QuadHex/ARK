/*
 * This source file is part of ArkNX
 * For the latest info, see https://github.com/ArkNX
 *
 * Copyright (c) 2013-2020 ArkNX authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#pragma once

#include "base/AFMacros.hpp"

namespace ark {

class guid_t128
{
public:
    uint64_t nHigh;
    uint64_t nLow;

    guid_t128() = default;

    guid_t128(uint64_t value)
        : nHigh(0)
        , nLow(value)
    {
    }

    guid_t128(uint64_t high, uint64_t low)
        : nHigh(high)
        , nLow(low)
    {
    }

    bool IsNULL()
    {
        return (0 == nHigh) && (0 == nLow);
    }

    bool IsNULL() const
    {
        return (0 == nHigh) && (0 == nLow);
    }

    guid_t128& operator=(const int& rhs)
    {
        nHigh = 0;
        nLow = rhs;
        return *this;
    }

    guid_t128& operator=(const int64_t& rhs)
    {
        nHigh = 0;
        nLow = rhs;
        return *this;
    }

    guid_t128& operator=(const guid_t128& rhs)
    {
        if (this != &rhs)
        {
            nHigh = rhs.nHigh;
            nLow = rhs.nLow;
        }
        return *this;
    }

    bool operator==(const guid_t128& rhs) const
    {
        return (this->nHigh == rhs.nHigh) && (this->nLow == rhs.nLow);
    }

    bool operator!=(const guid_t128& rhs) const
    {
        return !(*this == rhs);
    }

    bool operator<(const guid_t128& rhs) const
    {
        if (this->nHigh == rhs.nHigh)
        {
            return this->nLow < rhs.nLow;
        }

        return this->nHigh < rhs.nHigh;
    }

    std::string ToString() const
    {
        return ARK_LEXICAL_CAST<std::string>(nHigh) + "-" + ARK_LEXICAL_CAST<std::string>(nLow);
    }

    bool FromString(const std::string& strID)
    {
        size_t nStrLength = strID.length();
        size_t nPos = strID.find('-');

        if (nPos == std::string::npos)
        {
            return false;
        }

        std::string strHigh = strID.substr(0, nPos);
        std::string strLow = "";

        if ((nPos + 1) < nStrLength)
        {
            strLow = strID.substr(nPos + 1, nStrLength - nPos);
        }

        try
        {
            nHigh = ARK_LEXICAL_CAST<uint64_t>(strHigh);
            nLow = ARK_LEXICAL_CAST<uint64_t>(strLow);

            return true;
        }
        catch (std::system_error& ex)
        {
            CONSOLE_LOG_NO_FILE << "guid_t from string failed, code = " << ex.code().message() << " msg = " << ex.what()
                                << std::endl;
            ARK_ASSERT_NO_EFFECT(0);
            return false;
        }
    }
};

} // namespace ark
