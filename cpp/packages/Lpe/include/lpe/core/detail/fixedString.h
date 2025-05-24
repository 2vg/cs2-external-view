
#pragma once

#include "../../common.h"

#include <algorithm>

namespace lpe {
namespace detail {

    template <size_t N>
    struct FixedString {
        char value[N];

        constexpr FixedString(const char(&str)[N]) {
            std::copy_n(str, N, value);
        }
    };

}
}
