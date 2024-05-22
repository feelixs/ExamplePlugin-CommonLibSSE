#pragma once

#include <SKSE/SKSE.h>
#include <RE/Skyrim.h>
#include <REL/Relocation.h>
#include <SKSE/Trampoline.h>

namespace Hooks
{
    class PlayerHook
    {
    public:
        static void Hook();

    private:
        static bool HookedIsInMidair(const RE::Actor* actor);
        static inline REL::Relocation<decltype(&RE::Actor::IsInMidair)> _IsInMidair;
    };

    void Install();
}
