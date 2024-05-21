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
}