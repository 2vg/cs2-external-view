
#pragma once

#include "../common.h"
#include "./detail/soutFormat.h"

namespace lpe {

struct SoutInitParams {
    string name;
    string_view logDir;
};

class SoutManager {
private:
    class SoutManagerImpl;
    static std::unique_ptr<SoutManagerImpl> _pImpl;

private:
    SoutManager();

public:
    static void initialize(SoutInitParams&& params);

    static void log(string_view message);
    static void error(string_view message);
};

template <detail::HasFormat Formatter>
class BasicSout {
public:
    template <typename... Args>
    void log(string_view formatStr, Args&&... args)
    {
        SoutManager::log(Formatter::format(formatStr, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void error(string_view formatStr, Args&&... args)
    {
        SoutManager::log(Formatter::format(formatStr, std::forward<Args>(args)...));
    }
};

}

#define LPE_USE_SOUT(NAME) \
    auto sout = lpe::BasicSout<lpe::detail::FormatWithPrefix<#NAME>>();
