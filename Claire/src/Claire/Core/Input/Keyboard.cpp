#include "Keyboard.h"

#include <Windows.h>

namespace ClaireInput
{
	bool Keyboard::IsKeyPressed(uint32_t key)
	{
		bool result = false;

		if (GetKeyboardState(keys))
		{
			if (keys[key] & 0x80)
			{
				result = true;
			}

			memcpy(oldKeysState, keys, sizeof(unsigned char) * 256);

			return result;
		}
	}

	bool Keyboard::IsKeyReleased(uint32_t key)
	{
		return !IsKeyPressed(key);
	}
}