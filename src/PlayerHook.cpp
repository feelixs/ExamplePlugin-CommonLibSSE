#include "PlayerHook.h"
#include <spdlog/spdlog.h>

namespace Hooks
{
    bool __fastcall PlayerHook::HookedIsInMidair(RE::Actor* actor)
    {
        // Custom logic: Always return false if the actor is the player
        if (actor->IsPlayerRef()) {
            spdlog::info("Player set to not in midair");
            return false;
        }

        // Call the original function for other actors
        return _IsInMidair(actor);
    }

    void PlayerHook::Hook()
    {
        auto& trampoline = SKSE::GetTrampoline();

        // Example IDs for SE and AE versions
        REL::Relocation<func_t> isInMidairFunc{ RELOCATION_ID(36259, 37243) };
        _IsInMidair = trampoline.write_call<5>(isInMidairFunc.address(), HookedIsInMidair);
    }

    void Install()
    {
        spdlog::trace("Installing hooks...");
        PlayerHook::Hook();
        spdlog::trace("Hooks installed successfully");
    }
}
