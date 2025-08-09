/**
 * =============================================================================
 * CS2Fixes
 * Copyright (C) 2023-2025 Source2ZE
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// Bare minimum version of gameconfig.h for ExternalView

#pragma once

#include "KeyValues.h"

#include <cstdint>
#include <string>
#include <unordered_map>

class CModule;

class CGameConfig {
public:
    CGameConfig(const std::string& gameDir, const std::string& path);
    ~CGameConfig();

    bool Init(IFileSystem* filesystem, char* conf_error, int conf_error_size);
    const std::string GetPath();
    const char* GetLibrary(const std::string& name);
    const char* GetSignature(const std::string& name);
    const char* GetSymbol(const char* name);
    const char* GetPatch(const std::string& name);
    int GetOffset(const std::string& name);
    void* GetAddress(const std::string& name, void* engine, void* server, char* error, int maxlen);
    CModule** GetModule(const char* name);
    bool IsSymbol(const char* name);
    void* ResolveSignature(const char* name);
    static std::string GetDirectoryName(const std::string& directoryPathInput);
    static int HexStringToUint8Array(const char* hexString, uint8_t* byteArray, size_t maxBytes);
    static byte* HexToByte(const char* src, size_t& length);

private:
    std::string m_szGameDir;
    std::string m_szPath;
    KeyValues* m_pKeyValues;
    std::unordered_map<std::string, int> m_umOffsets;
    std::unordered_map<std::string, std::string> m_umSignatures;
    std::unordered_map<std::string, void*> m_umAddresses;
    std::unordered_map<std::string, std::string> m_umLibraries;
    std::unordered_map<std::string, std::string> m_umPatches;
};
