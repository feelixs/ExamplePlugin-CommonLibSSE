#include "PlayerHook.h"
#include <spdlog/spdlog.h>

namespace Hooks
{
    bool PlayerHook::HookedIsInMidair(RE::Actor* actor)
    {
        if (actor->IsPlayerRef()) {
            spdlog::info("Actor is player, returning false for IsInMidair check");
            return false;
        }
        return _IsInMidair(actor);
    }

    void PlayerHook::Hook()
    {
        auto& trampoline = SKSE::GetTrampoline();
        REL::Relocation<std::uintptr_t> hook{ RELOCATION_ID(36259, 37243) };
        _IsInMidair = trampoline.write_call<5>(hook.address(), HookedIsInMidair);
    }

    void Install()
    {
        spdlog::info("Installing hooks...");
        PlayerHook::Hook();
        spdlog::info("Hooks installed successfully");
    }
}
