
#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace lpe {

namespace types {
    using int8 = int8_t;
    using int32 = int32_t;
    using uint8 = uint8_t;
    using uint32 = uint32_t;

    using string = std::string;
    using string_view = std::string_view;
}

using namespace types;

}

#define LPE_DECL_INTERFACE_PTR(NAME) \
    class I##NAME;                   \
    using NAME##Ptr = std::shared_ptr<I #NAME>

#define LPE_DECL_CLASS_PTR(NAME) \
    class NAME;                  \
    using NAME##Ptr = std::shared_ptr<NAME>

#define LPE_DECL_STRUCT_PTR(NAME) \
    struct NAME;                  \
    using NAME##Ptr = std::shared_ptr<NAME>
