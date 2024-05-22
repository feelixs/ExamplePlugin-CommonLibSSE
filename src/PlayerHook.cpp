#include "PlayerHook.h"
#include <spdlog/spdlog.h>

namespace Hooks
{
    bool PlayerHook::HookedIsInMidair(RE::Actor* actor)
    {
        spdlog::info("HookedIsInMidair called");
        if (actor->IsPlayerRef()) {
            spdlog::info("Actor is player, returning false for IsInMidair check");
            return false;
        }
        return _IsInMidair(actor);
    }

    const REL::Relocation<decltype(&RE::Actor::IsInMidair)>& PlayerHook::GetIsInMidair() noexcept
{
    static REL::Relocation<decltype(&RE::Actor::IsInMidair)> function{ RELOCATION_ID(36259, 37243) };
    return function;
}

void PlayerHook::Hook()
{
    auto& trampoline = SKSE::GetTrampoline();
    _IsInMidair = trampoline.write_call<5>(GetIsInMidair().address(), HookedIsInMidair);
    spdlog::info("Hook installed at address {}", GetIsInMidair().address());
}

void Install()
{
    spdlog::info("Installing hooks...");
    PlayerHook::Hook();
    spdlog::info("Hooks installed successfully");
}
}
