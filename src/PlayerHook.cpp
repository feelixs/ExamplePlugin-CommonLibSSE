#include "PlayerHook.h"
#include <spdlog/spdlog.h>

namespace Hooks
{
    bool PlayerHook::HookedIsInMidair(const RE::Actor* actor)
    {
        // Custom logic: Always return false if the actor is the player
        if (actor->IsPlayerRef()) {
            spdlog::info("OVERRIDING Player to not in midair");
            return false;
        }
        return _IsInMidair(actor);
    }

    void PlayerHook::Hook()
    {
        auto& trampoline = SKSE::GetTrampoline();
        REL::Relocation<std::uintptr_t> isInMidairFunc{ RELOCATION_ID(36259, 37243) };
        _IsInMidair = trampoline.write_call<5>(isInMidairFunc.address(), HookedIsInMidair);
    }

    void Install()
    {
        spdlog::trace("Installing hooks...");
        PlayerHook::Hook();
        spdlog::trace("Hooks installed successfully");
    }
}
