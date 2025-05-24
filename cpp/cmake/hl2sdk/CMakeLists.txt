
project(HL2Sdk LANGUAGES CXX)

set(HL2Sdk_ROOT ${Extern_DIR}/hl2sdk)

find_path(HL2Sdk_INCLUDE_DIR
    NAMES public/interfaces/interfaces.h
    HINTS ${HL2Sdk_ROOT}
    REQUIRED
)
find_path(HL2Sdk_LIBRARY_DIR
    NAMES interfaces.lib
    HINTS ${HL2Sdk_ROOT}/lib/public/win64
    REQUIRED
)

add_library(${PROJECT_NAME} STATIC)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED true
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    COMPILER_MSVC
    COMPILER_MSVC64
    WIN32
    _WIN32
    WINDOWS
    _WINDOWS
    CRT_SECURE_NO_WARNINGS
    _CRT_SECURE_NO_WARNINGS
    CRT_SECURE_NO_DEPRECATE
    _CRT_SECURE_NO_DEPRECATE
    CRT_NONSTDC_NO_DEPRECATE
    _CRT_NONSTDC_NO_DEPRECATE
    _MBCS
    META_IS_SOURCE2
    X64BITS
    PLATFORM_64BITS
    NDEBUG
)

target_compile_options(${PROJECT_NAME} PUBLIC
    "/wd4819" # Ignores - "The file contains a character that cannot be represented in the current code page"
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${HL2Sdk_INCLUDE_DIR}
    ${HL2Sdk_INCLUDE_DIR}/public
    ${HL2Sdk_INCLUDE_DIR}/public/entity2
    ${HL2Sdk_INCLUDE_DIR}/game/server
    ${HL2Sdk_INCLUDE_DIR}/game/shared
    ${HL2Sdk_INCLUDE_DIR}/common
    ${HL2Sdk_INCLUDE_DIR}/public/engine
    ${HL2Sdk_INCLUDE_DIR}/public/mathlib
    ${HL2Sdk_INCLUDE_DIR}/public/tier0
    ${HL2Sdk_INCLUDE_DIR}/public/tier1
    ${HL2Sdk_INCLUDE_DIR}/public/game/server
)

target_sources(${PROJECT_NAME} PRIVATE
    #${HL2Sdk_ROOT}/public/tier0/memoverride.cpp
    ${HL2Sdk_ROOT}/tier1/convar.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${HL2Sdk_LIBRARY_DIR}/interfaces.lib
    ${HL2Sdk_LIBRARY_DIR}/mathlib.lib
    ${HL2Sdk_LIBRARY_DIR}/tier0.lib
    ${HL2Sdk_LIBRARY_DIR}/tier1.lib
    ${HL2Sdk_LIBRARY_DIR}/steam_api64.lib
    Protobuf
)
