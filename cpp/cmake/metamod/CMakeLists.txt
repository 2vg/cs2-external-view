
project(Metamod LANGUAGES CXX)

set(Metamod_ROOT ${Extern_DIR}/metamod)

find_path(Metamod_INCLUDE_DIR
    NAMES ISmmPlugin.h
    HINTS ${Metamod_ROOT}/core
    REQUIRED
)

add_library(${PROJECT_NAME} INTERFACE)
    
target_include_directories(${PROJECT_NAME} INTERFACE
    ${Metamod_INCLUDE_DIR}
    ${Metamod_INCLUDE_DIR}/sourcehook
)
target_link_libraries(${PROJECT_NAME} INTERFACE
    HL2Sdk
)
