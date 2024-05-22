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
        static bool HookedIsInMidair(RE::Actor* actor);
        static inline REL::Relocation<decltype(&RE::Actor::IsInMidair)> _IsInMidair;
        static inline const REL::Relocation<decltype(&RE::Actor::IsInMidair)>& GetIsInMidair() noexcept;
    };

    void Install();
}
