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

// Minimum version of addresses.cpp for ExternalView

#include "./addresses.h"
#include "./gameConfig.h"
#include "utils/module.h"

#include "tier0/memdbgon.h"

extern CGameConfig* g_GameConfig;

bool addresses::Initialize(CGameConfig* g_GameConfig)
{
    modules::server = new CModule(GAMEBIN, "server");

    return true;
}
