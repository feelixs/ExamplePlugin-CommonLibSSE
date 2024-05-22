#include "PlayerHook.h"
#include <spdlog/spdlog.h>

namespace Hooks
{
    bool PlayerHook::HookedIsInMidair(const RE::Actor* actor)
    {
        if (!actor) {
            spdlog::info("Actor is null");
            return false;
        }

        spdlog::info("HookedIsInMidair called for actor: {}", actor->GetName());

        // Custom logic: Always return false if the actor is the player
        if (actor->IsPlayerRef()) {
            spdlog::info("Actor is player, returning false for IsInMidair check");
            return false;
        }

        // Call the original function for other actors
        return _IsInMidair(actor);
    }

    void PlayerHook::Hook()
    {
        auto& trampoline = SKSE::GetTrampoline();
        REL::Relocation<func_t> isInMidairFunc{ RELOCATION_ID(36259, 37243) };
        _IsInMidair = trampoline.write_call<5>(isInMidairFunc.address(), &PlayerHook::HookedIsInMidair);
    }

    void Install()
    {
        spdlog::info("Installing hooks...");
        PlayerHook::Hook();
        spdlog::info("Hooks installed successfully");
    }
}
