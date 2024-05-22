#include "PlayerHook.h"
#include <spdlog/spdlog.h>

namespace Hooks
{
    bool PlayerHook::HookedIsInMidair(const RE::Actor* actor)
    {
        if (!actor) {
            spdlog::error("Actor is null");
            return false;
        }

        auto name = actor->GetName();
        spdlog::info("HookedIsInMidair called for actor: {}", name ? name : "Unknown");

        // Check if the actor is the player
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

        _IsInMidair = trampoline.write_call<5>(REL::Relocation<decltype(&RE::Actor::IsInMidair)>::address(), HookedIsInMidair);

        if (!_IsInMidair) {
            spdlog::error("Failed to hook IsInMidair function");
        } else {
            spdlog::info("Successfully hooked IsInMidair function");
        }
    }

    void Install()
    {
        spdlog::trace("Installing hooks...");
        PlayerHook::Hook();
        spdlog::trace("Hooks installed successfully");
    }
}
