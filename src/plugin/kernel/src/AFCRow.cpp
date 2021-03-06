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

#include "kernel/include/AFCRow.hpp"
#include "kernel/include/AFCData.hpp"
#include "kernel/include/AFCNode.hpp"

namespace ark {

// constructor
AFCRow::AFCRow(
    std::shared_ptr<AFClassMeta> pClassMeta, uint32_t row, const AFIDataList& args, ROW_CALLBACK_FUNCTOR&& func)
    : row_(row)
{
    // data node
    auto function =
        std::bind(&AFCRow::OnNodeCallBack, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    m_pNodeManager = std::make_shared<AFNodeManager>(pClassMeta, args, std::move(function));

    func_ = std::move(func);
}

// get row
uint32_t AFCRow::GetRow() const
{
    return row_;
}

// get row data
bool AFCRow::GetBool(const uint32_t index) const
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, NULL_BOOLEAN);

    return m_pNodeManager->GetBool(index);
}

int32_t AFCRow::GetInt32(const uint32_t index) const
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, NULL_INT);

    return m_pNodeManager->GetInt32(index);
}

uint32_t AFCRow::GetUInt32(const uint32_t index) const
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, NULL_INT);

    return m_pNodeManager->GetUInt32(index);
}

int64_t AFCRow::GetInt64(const uint32_t index) const
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, NULL_INT64);

    return m_pNodeManager->GetInt64(index);
}

uint64_t AFCRow::GetUInt64(const uint32_t index) const
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, NULL_INT64);

    return m_pNodeManager->GetUInt64(index);
}

float AFCRow::GetFloat(const uint32_t index) const
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, NULL_FLOAT);

    return m_pNodeManager->GetFloat(index);
}

double AFCRow::GetDouble(const uint32_t index) const
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, NULL_DOUBLE);

    return m_pNodeManager->GetDouble(index);
}

const std::string& AFCRow::GetString(const uint32_t index) const
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, NULL_STR);

    return m_pNodeManager->GetString(index);
}

const std::wstring& AFCRow::GetWString(const uint32_t index) const
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, NULL_WIDESTR);

    return m_pNodeManager->GetWString(index);
}

const guid_t& AFCRow::GetGUID(const uint32_t index) const
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, NULL_GUID);

    return m_pNodeManager->GetGUID(index);
}

bool AFCRow::GetBool(const std::string& name) const
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, NULL_BOOLEAN);

    return m_pNodeManager->GetBool(name);
}

int32_t AFCRow::GetInt32(const std::string& name) const
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, NULL_INT);

    return m_pNodeManager->GetInt32(name);
}

uint32_t AFCRow::GetUInt32(const std::string& name) const
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, NULL_INT);

    return m_pNodeManager->GetUInt32(name);
}

int64_t AFCRow::GetInt64(const std::string& name) const
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, NULL_INT64);

    return m_pNodeManager->GetInt64(name);
}

uint64_t AFCRow::GetUInt64(const std::string& name) const
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, NULL_INT64);

    return m_pNodeManager->GetUInt64(name);
}

float AFCRow::GetFloat(const std::string& name) const
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, NULL_FLOAT);

    return m_pNodeManager->GetFloat(name);
}

double AFCRow::GetDouble(const std::string& name) const
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, NULL_DOUBLE);

    return m_pNodeManager->GetDouble(name);
}

const std::string& AFCRow::GetString(const std::string& name) const
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, NULL_STR);

    return m_pNodeManager->GetString(name);
}

const std::wstring& AFCRow::GetWString(const std::string& name) const
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, NULL_WIDESTR);

    return m_pNodeManager->GetWString(name);
}

const guid_t& AFCRow::GetGUID(const std::string& name) const
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, NULL_GUID);

    return m_pNodeManager->GetGUID(name);
}

// set row data
bool AFCRow::SetBool(const uint32_t index, bool value)
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, false);

    return m_pNodeManager->SetBool(index, value);
}

bool AFCRow::SetInt32(const uint32_t index, int32_t value)
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, false);

    return m_pNodeManager->SetInt32(index, value);
}

bool AFCRow::SetInt64(const uint32_t index, int64_t value)
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, false);

    return m_pNodeManager->SetInt64(index, value);
}

bool AFCRow::SetUInt32(const uint32_t index, uint32_t value)
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, false);

    return m_pNodeManager->SetUInt32(index, value);
}

bool AFCRow::SetUInt64(const uint32_t index, uint64_t value)
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, false);

    return m_pNodeManager->SetUInt64(index, value);
}

bool AFCRow::SetFloat(const uint32_t index, float value)
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, false);

    return m_pNodeManager->SetFloat(index, value);
}

bool AFCRow::SetDouble(const uint32_t index, double value)
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, false);

    return m_pNodeManager->SetDouble(index, value);
}

bool AFCRow::SetString(const uint32_t index, const std::string& value)
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, false);

    return m_pNodeManager->SetString(index, value);
}

bool AFCRow::SetWString(const uint32_t index, const std::wstring& value)
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, false);

    return m_pNodeManager->SetWString(index, value);
}

bool AFCRow::SetGUID(const uint32_t index, const guid_t& value)
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, false);

    return m_pNodeManager->SetGUID(index, value);
}

bool AFCRow::SetBool(const std::string& name, bool value)
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, false);

    return m_pNodeManager->SetBool(name, value);
}

bool AFCRow::SetInt32(const std::string& name, int32_t value)
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, false);

    return m_pNodeManager->SetInt32(name, value);
}

bool AFCRow::SetUInt32(const std::string& name, uint32_t value)
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, false);

    return m_pNodeManager->SetUInt32(name, value);
}

bool AFCRow::SetInt64(const std::string& name, int64_t value)
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, false);

    return m_pNodeManager->SetInt64(name, value);
}

bool AFCRow::SetUInt64(const std::string& name, uint64_t value)
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, false);

    return m_pNodeManager->SetUInt64(name, value);
}

bool AFCRow::SetFloat(const std::string& name, float value)
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, false);

    return m_pNodeManager->SetFloat(name, value);
}

bool AFCRow::SetDouble(const std::string& name, double value)
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, false);

    return m_pNodeManager->SetDouble(name, value);
}

bool AFCRow::SetString(const std::string& name, const std::string& value)
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, false);

    return m_pNodeManager->SetString(name, value);
}

bool AFCRow::SetWString(const std::string& name, const std::wstring& value)
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, false);

    return m_pNodeManager->SetWString(name, value);
}

bool AFCRow::SetGUID(const std::string& name, const guid_t& value)
{
    ARK_ASSERT_RET_VAL(m_pNodeManager != nullptr, false);

    return m_pNodeManager->SetGUID(name, value);
}

std::shared_ptr<AFNodeManager> AFCRow::GetNodeManager() const
{
    return m_pNodeManager;
}

int AFCRow::OnNodeCallBack(AFINode* pNode, const AFIData& old_data, const AFIData& new_data)
{
    if (func_)
    {
        func_(row_, pNode, old_data, new_data);
    }

    return 0;
}

} // namespace ark
