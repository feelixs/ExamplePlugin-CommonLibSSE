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

        // Example IDs for SE and AE versions
        REL::Relocation<std::uintptr_t> isInMidairFunc{ REL::ID(36259, 37243) };
        _IsInMidair = trampoline.write_call<5>(isInMidairFunc.address(), HookedIsInMidair);

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
