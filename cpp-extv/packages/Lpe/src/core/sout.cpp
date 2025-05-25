
#include "lpe/core/sout.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace lpe {

namespace {
    template <typename... Args>
    void panic(string_view formatStr, Args&&... args)
    {
        string msg = fmt::vformat(formatStr, fmt::make_format_args(args...));
        fmt::print("[lpe::sout] **PANIC** {}", msg);
    }
}

class SoutManager::SoutManagerImpl {
private:
    string name;
    std::shared_ptr<spdlog::logger> _pLogger;

public:
    SoutManagerImpl(SoutInitParams&& params)
        : name { std::move(params.name) }
    {
        try {
            auto logFilePath = fmt::format("{}/log_{}.txt", params.logDir, name);
            _pLogger = spdlog::basic_logger_mt(name, logFilePath);
            _pLogger->flush_on(spdlog::level::info);
        } catch (const spdlog::spdlog_ex& ex) {
            panic("Log initialization failed: {}", ex.what());
        }
    }

    void log(string_view message)
    {
        if (!_pLogger) {
            return;
        }
        _pLogger->info(message);
    }

    void error(string_view message)
    {
        if (!_pLogger) {
            return;
        }
        _pLogger->error(fmt::format("**ERROR** {}", message));
    }
};

std::unique_ptr<SoutManager::SoutManagerImpl> SoutManager::_pImpl;

SoutManager::SoutManager()
{
}

void SoutManager::initialize(SoutInitParams&& params)
{
    _pImpl = std::make_unique<SoutManagerImpl>(std::move(params));
}

void SoutManager::log(string_view message)
{
    if (!_pImpl) {
        panic("[log] SoutManager is not initialized.");
        return;
    }
    _pImpl->log(message);
}

void SoutManager::error(string_view message)
{
    if (!_pImpl) {
        panic("[error] SoutManager is not initialized.");
        return;
    }
    _pImpl->error(message);
}

}
