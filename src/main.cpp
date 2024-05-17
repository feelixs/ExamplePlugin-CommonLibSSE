#include <SKSE/SKSE.h>
#include <RE/Skyrim.h>
#include <REL/Relocation.h>
#include <SKSE/Trampoline.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>

namespace
{
    void InitializeLog()
    {
#ifndef NDEBUG
        auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
#else
        auto path = logger::log_directory();
        if (!path) {
            util::report_and_fail("Failed to find standard logging directory"sv);
        }

        *path /= fmt::format("{}.log"sv, Plugin::NAME);
        auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
#endif

#ifndef NDEBUG
        const auto level = spdlog::level::trace;
#else
        const auto level = spdlog::level::info;
#endif

        auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));
        log->set_level(level);
        log->flush_on(level);

        spdlog::set_default_logger(std::move(log));
        spdlog::set_pattern("%g(%#): [%^%l%$] %v"s);
    }

    using ShoutFunction_t = void(*)(int64_t*, int);

    ShoutFunction_t _ShoutFunction;

    void HookedShoutFunction(int64_t* param_1, int param_2)
    {
        // Unconditionally set param_2 to a value that should bypass the error checks and jump table
        param_2 = 100; // Example value > 99

        // Log the modification for debugging purposes
        logger::info("HookedShoutFunction called, setting param_2 to {}", param_2);

        // Call the original function with the modified param_2
        _ShoutFunction(param_1, param_2);
    }

    void InstallHooks()
    {
        // Initialize the trampoline with a larger buffer size (e.g., 64 KB)
        SKSE::AllocTrampoline(64 * 1024);

        auto& trampoline = SKSE::GetTrampoline();

        // Get the address from the address library
        REL::Relocation<std::uintptr_t> hook{ RELOCATION_ID(67497, 68808) }; // Use appropriate ID

        // Set up the hook to intercept calls to the target function
        _ShoutFunction = trampoline.write_call<5>(hook.address() + 0x13F, HookedShoutFunction); // Adjust offset as needed
    }
}

extern "C" DLLEXPORT constinit auto SKSEPlugin_Version = []() {
    SKSE::PluginVersionData v;

    v.PluginVersion(Plugin::VERSION);
    v.PluginName(Plugin::NAME);

    v.UsesAddressLibrary(true);
    v.CompatibleVersions({ SKSE::RUNTIME_LATEST });

    return v;
}();

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
    InitializeLog();
    logger::info("{} v{}"sv, Plugin::NAME, Plugin::VERSION.string());

    SKSE::Init(a_skse);

    InstallHooks();

    logger::info("Hooks installed successfully");

    return true;
}
