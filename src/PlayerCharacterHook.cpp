#include "PlayerCharacterHook.h"

namespace Hooks
{
	void Install()
	{
		logger::trace("Hooking...");
		PlayerCharacterHook::Hook();
		logger::trace("...success");
	}
};