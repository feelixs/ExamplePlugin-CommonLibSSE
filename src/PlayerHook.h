#pragma once

#include <SKSE/SKSE.h>
#include <RE/Skyrim.h>
#include <REL/Relocation.h>
#include <SKSE/Trampoline.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>

namespace Hooks
{
    class PlayerHook
    {
    public:
        static void Hook();

    private:
        static bool HookedIsInMidair(const RE::Actor* actor);
        static inline REL::Relocation<decltype(HookedIsInMidair)> _IsInMidair;
    };

    void Install();
}
