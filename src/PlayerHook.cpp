#pragma once

#include <SKSE/SKSE.h>
#include <RE/Skyrim.h>
#include <REL/Relocation.h>
#include <SKSE/Trampoline.h>

namespace Hooks
{
	class PlayerHook
	{
	public:
		static void Hook();

	private:
		static void HookedShoutFunction(int64_t* param_1, int param_2);
		static inline REL::Relocation<decltype(HookedShoutFunction)> _ShoutFunction;
	};
}#include "PlayerHook.h"
#include <spdlog/spdlog.h>
	
	namespace Hooks
{
	void PlayerHook::Hook()
	{
		auto& trampoline = SKSE::GetTrampoline();

		// Using example addresses, replace with actual IDs
		REL::Relocation<std::uintptr_t> shoutFunctionID{ RELOCATION_ID(67497, 68808) };
		_ShoutFunction = trampoline.write_call<5>(shoutFunctionID.address(), HookedShoutFunction);
	}

	void PlayerHook::HookedShoutFunction(int64_t* param_1, int param_2)
	{
		// Unconditionally set param_2 to a value that should bypass the error checks and jump table
		param_2 = 100; // Example value > 99

		// Log the modification for debugging purposes
		spdlog::info("HookedShoutFunction called, setting param_2 to {}", param_2);

		// Call the original function with the modified param_2
		_ShoutFunction(param_1, param_2);
	}

	// Define the static member
	REL::Relocation<decltype(PlayerHook::HookedShoutFunction)> PlayerHook::_ShoutFunction;

	void Install()
	{
		logger::trace("Hooking...");
		PlayerHook::Hook();
		logger::trace("...success");
	}
}