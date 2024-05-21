#include "Hooks.h"
#include "Settings.h"
#include "DirectionalMovementHandler.h"
#include "Offsets.h"
#include "Utils.h"
#include "RayCast.h"

namespace Hooks
{
	void Install()
	{
		logger::trace("Hooking...");
		PlayerCharacterHook::Hook();
		logger::trace("...success");
	}
};
