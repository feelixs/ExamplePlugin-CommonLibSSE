#include "PlayerHook.h"
#include <spdlog/spdlog.h>

namespace Hooks
{
    bool HookedIsInMidair(const RE::Actor* actor)
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

        REL::Relocation<decltype(&RE::Actor::IsInMidair)> func{ RELOCATION_ID(36259, 37243) };
        _IsInMidair = func.address(); // Get the address of the original function

        // Hook the function using trampoline
        trampoline.write_call<5>(
                REL::Relocate<uintptr_t>(func.address()), // Use Relocate to handle SE and AE differences
                reinterpret_cast<uintptr_t>(HookedIsInMidair)
        );

        if (!_IsInMidair.address()) {
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
