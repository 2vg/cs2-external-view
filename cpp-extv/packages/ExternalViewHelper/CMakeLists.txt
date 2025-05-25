
project(ExternalViewHelper LANGUAGES CXX)

find_package(boost_core REQUIRED CONFIG)

include(Files.cmake)
include(Version.cmake)

add_library(${PROJECT_NAME} SHARED ${ExternalViewHelper_FILES})

target_compile_definitions(${PROJECT_NAME} PRIVATE EXTERNALVIEWHELPER_EXPORTS)

function(externalviewhelper_common TARGET_NAME)
    set_target_properties(${TARGET_NAME} PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED true
    )

    target_compile_definitions(${TARGET_NAME} PUBLIC
        EXTERNALVIEWHELPER_VERSION="${ExternalViewHelper_VERSION}"
    )

    target_compile_options(${TARGET_NAME} PRIVATE
        "/MT"
        # C4819: The file contains a character that cannot be represented in the current code page
        "/wd4819"
        # C4828: The file contains a character starting at offset 0x16 that is illegal in the current source character set (codepage 65001).
        "/wd4828"
    )

    target_include_directories(${TARGET_NAME} PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )
    target_include_directories(${TARGET_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

    target_link_libraries(${TARGET_NAME} PUBLIC
        Boost::core
        CS2Fixes
        Lpe
    )
endfunction()

externalviewhelper_common(${PROJECT_NAME})

if(DEFINED ENV{CS2_SERVER_DIR})
    set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "$ENV{CS2_SERVER_DIR}\\game\\bin\\win64"
        VS_DEBUGGER_COMMAND "$ENV{CS2_SERVER_DIR}\\game\\bin\\win64\\cs2.exe"
        VS_DEBUGGER_COMMAND_ARGUMENTS "-dedicated +game_mode 0 +game_type 3 +map de_dust2 +exec autoexec.cfg"
    )

    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE:${PROJECT_NAME}>
                "$ENV{CS2_SERVER_DIR}/game/csgo/addons/externalviewhelper/bin/win64/externalviewhelper.dll"
    )
endif()
