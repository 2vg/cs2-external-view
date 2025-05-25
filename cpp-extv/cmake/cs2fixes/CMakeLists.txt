
project(CS2Fixes LANGUAGES CXX)

set(CS2Fixes_ROOT ${Extern_DIR}/cs2fixes/src)

find_path(CS2Fixes_INCLUDE_DIR
    NAMES cs2fixes.h
    HINTS ${CS2Fixes_ROOT}
    REQUIRED
)

add_library(${PROJECT_NAME} STATIC)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED true
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CS2Fixes_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Metamod
)

target_sources(${PROJECT_NAME} PRIVATE
    ${CS2Fixes_ROOT}/addresses.cpp
    ${CS2Fixes_ROOT}/gameconfig.cpp
    ${CS2Fixes_ROOT}/utils/plat_win.cpp
)
