
#pragma once

#include "../../common.h"
#include "./fixedString.h"

#include <fmt/format.h>

namespace lpe {
namespace detail {

    template <typename T>
    concept HasFormat = requires(string_view sv) {
        { T::format(sv) } -> std::convertible_to<string_view>;
        { T::format(sv, 0) } -> std::convertible_to<string_view>;
        { T::format(sv, "message") } -> std ::convertible_to<string_view>;
    };

    struct Format {
        template <typename... Args>
        static string format(string_view formatStr, Args&&... args)
        {
            return fmt::vformat(formatStr, fmt::make_format_args(args...));
        }
    };

    template <FixedString Prefix>
    struct FormatWithPrefix {
        template <typename... Args>
        static string format(string_view formatStr, Args&&... args)
        {
            auto str = Format::format(formatStr, std::forward<Args>(args)...);
            return fmt::format("[{}] {}", Prefix.value, str);
        }
    };

}
}
