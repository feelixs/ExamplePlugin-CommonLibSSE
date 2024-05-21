#pragma once

namespace Hooks
{
	class PlayerCharacterHook
	{
	public:
		static void Hook()
		{
			auto& trampoline = SKSE::GetTrampoline();

			// Using the example addresses, replace with actual IDs
			REL::Relocation<std::uintptr_t> shoutFunctionID{ REL::ID(67497, 68808) };
			_ShoutFunction = trampoline.write_call<5>(shoutFunctionID.address(), HookedShoutFunction);
		}

	private:
		static void HookedShoutFunction(int64_t* param_1, int param_2)
		{
			// Unconditionally set param_2 to a value that should bypass the error checks and jump table
			param_2 = 100; // Example value > 99

			// Log the modification for debugging purposes
			logger::info("HookedShoutFunction called, setting param_2 to {}", param_2);

			// Call the original function with the modified param_2
			_ShoutFunction(param_1, param_2);
		}

		static inline REL::Relocation<decltype(HookedShoutFunction)> _ShoutFunction;
	};

	void Install();
}
