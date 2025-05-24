
cmake_minimum_required(VERSION 3.23)
project(external-view-helper-root)

#list(APPEND CMAKE_MODULE_PATH
#    "${CMAKE_CURRENT_LIST_DIR}/cmake"
#)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)

# Runtime library must be either of non-dll versions (/MT or /MTd).
# See: https://wiki.alliedmods.net/Metamod:Source_Development
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

enable_testing()

add_subdirectory(cmake)
add_subdirectory(packages)
