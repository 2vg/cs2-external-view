
project(Protobuf LANGUAGES CXX)

set(HL2SDK_Protobuf_ROOT ${Extern_DIR}/hl2sdk/thirdparty/protobuf-3.21.8/src)
set(CS2_Protobuf_ROOT ${Extern_DIR}/cs2fixes/protobuf/generated)

find_path(HL2SDK_Protobuf_INCLUDE_DIR
    NAMES google/protobuf/port_def.inc
    HINTS ${HL2SDK_Protobuf_ROOT}
    REQUIRED
)
find_path(CS2_Protobuf_INCLUDE_DIR
    NAMES network_connection.pb.h
    HINTS ${CS2_Protobuf_ROOT}
    REQUIRED
)

add_library(${PROJECT_NAME} STATIC)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED true
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${HL2SDK_Protobuf_INCLUDE_DIR}
    ${CS2_Protobuf_INCLUDE_DIR}
)

target_sources(${PROJECT_NAME} PRIVATE
    ${CS2_Protobuf_ROOT}/cs_usercmd.pb.cc
    ${CS2_Protobuf_ROOT}/networkbasetypes.pb.cc
    ${CS2_Protobuf_ROOT}/network_connection.pb.cc
    ${CS2_Protobuf_ROOT}/usercmd.pb.cc
    ${CS2_Protobuf_ROOT}/usermessages.pb.cc
    ${CS2_Protobuf_ROOT}/cstrike15_gcmessages.pb.cc
    ${CS2_Protobuf_ROOT}/cstrike15_usermessages.pb.cc
    ${CS2_Protobuf_ROOT}/gcsdk_gcmessages.pb.cc
    ${CS2_Protobuf_ROOT}/engine_gcmessages.pb.cc
    ${CS2_Protobuf_ROOT}/netmessages.pb.cc
    ${CS2_Protobuf_ROOT}/steammessages.pb.cc
)
