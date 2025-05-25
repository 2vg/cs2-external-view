
project(Lpe LANGUAGES CXX)

find_package(boost_core CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

include(Files.cmake)

add_library(${PROJECT_NAME} STATIC ${Lpe_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED true
)

target_compile_definitions(${PROJECT_NAME} PRIVATE )

target_link_libraries(${PROJECT_NAME} PUBLIC
    Boost::core
    fmt::fmt-header-only
    spdlog::spdlog_header_only
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#add_subdirectory(test)
