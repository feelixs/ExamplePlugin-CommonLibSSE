#pragma once

#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>
#include <REL/Relocation.h>

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
