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

// Bare minimum version of addresses.cpp for ExternalView

#pragma once
#include "platform.h"
#include "stdint.h"
#include "utils/module.h"
#include "utlstring.h"
#include "variant.h"

namespace modules {
inline CModule* server;
} // namespace modules

class CGameConfig;

namespace addresses {
bool Initialize(CGameConfig* g_GameConfig);
} // namespace addresses
